#include "stdafx.h"
#include "VideoFile.h"


//线程声明
DWORD WINAPI DecodeThread(LPVOID lpParam);
DWORD WINAPI VideoThread(LPVOID lpParam);
DWORD WINAPI AudioThread(LPVOID lpParam);
void  SDL_AudioCallPlay(void *udata, Uint8 *stream, int len);
int GetSampleCount(AVSampleFormat out_sample_fmt);


int GetSampleCount(AVSampleFormat out_sample_fmt)
{
	int count = 0;
	switch (out_sample_fmt)
	{
	case AV_SAMPLE_FMT_S32:count = 4; break;
	case AV_SAMPLE_FMT_S16:count = 2; break;
	case AV_SAMPLE_FMT_U8: count = 1; break;
	}
	return count;
}


void  SDL_AudioCallPlay(void *udata, Uint8 *stream, int len)
{
	VideoFile* pThis = (VideoFile*)udata;
	SDL_memset(stream, 0, len);

	std::lock_guard<mutex> mtx_locker(pThis->m_CMutex);
	if (!pThis->m_qAbuf.empty())
	{
		static int send_len = 0;

		ST_ABUF* st_buf = &pThis->m_qAbuf.front();
		int cp_len = (len > st_buf->buf_len ? st_buf->buf_len : len);
		if (cp_len > 0)
		{
			memcpy(stream, st_buf->buf + send_len, cp_len);
			send_len += cp_len;
			st_buf->buf_len -= cp_len;
			if (st_buf->buf_len == 0)
			{
				send_len = 0;
				delete[] st_buf->buf;
				pThis->m_qAbuf.pop();
			}
		}
		SetEvent(pThis->m_hACallEvent);
		WaitForSingleObject(pThis->m_hSupendEvent, INFINITE);//暂停后，此处会一直等待，直到SetEvent(m_hSupendEvent)
		ResetEvent(pThis->m_hACallEvent);
	}
}


VideoFile::VideoFile(CWnd* videoWnd, char *filePath)
{
	this->filePath = filePath;
	this->videoWnd = videoWnd;

	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pFormatCtx = nullptr;
	m_pvCodecCtxOrg = nullptr;
	m_pvCodecCtx = nullptr;
	m_pvCodec = nullptr;
	m_videoStream = -1;
	m_paCodecCtxOrg = nullptr;
	m_paCodecCtx = nullptr;
	m_paCodec = nullptr;

	m_sdlWindow = nullptr;
	m_sdlRenderer = nullptr;
	m_sdlTexture = nullptr;

	m_AudioStream = -1;
	m_hSupendEvent = CreateEvent(NULL, TRUE, TRUE, NULL); //初始有信号
	m_hDecodeEvent = CreateEvent(NULL, TRUE, TRUE, NULL); //初始有信号
	m_hVideoEvent = CreateEvent(NULL, TRUE, TRUE, NULL); //初始有信号
	m_hAudioEvent = CreateEvent(NULL, TRUE, TRUE, NULL); //初始有信号
	m_hACallEvent = CreateEvent(NULL, TRUE, TRUE, NULL); //初始有信号
	m_hSupendEvent = CreateEvent(NULL, TRUE, TRUE, NULL); //初始有信号
	m_hDecodeHandel = INVALID_HANDLE_VALUE;
	m_hVPlayHandel = INVALID_HANDLE_VALUE;
	m_hAPlayHandel = INVALID_HANDLE_VALUE;
}

//销毁回收   线程回收
VideoFile::~VideoFile()
{
	SetPlayType(EM_PLAY_TYPE_STOP);
	if (m_hDecodeHandel != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject(m_hDecodeHandel, INFINITE);
		m_hDecodeHandel = INVALID_HANDLE_VALUE;
	}
	if (m_hVPlayHandel != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject(m_hVPlayHandel, INFINITE);
		m_hVPlayHandel = INVALID_HANDLE_VALUE;
	}
	if (m_hAPlayHandel != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject(m_hAPlayHandel, INFINITE);
		m_hAPlayHandel = INVALID_HANDLE_VALUE;
	}
	FreeVariable();
	if (m_sdlWindow)
	{
		SDL_DestroyWindow(m_sdlWindow);
	}
	SDL_Quit();
}



void VideoFile::ShowVideo()
{

	av_register_all(); // 注册支持的文件格式及对应的codec
	SetPlayType(EM_PLAY_TYPE_STOP);
	//PostMessage(WM_SHOW_BK, NULL, 0);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		//MessageBox(L"sdl init error");
		printf("sdl init error");
	}

	m_sdlWindow = SDL_CreateWindowFrom(videoWnd->GetSafeHwnd());
	if (!m_sdlWindow)
	{
		//MessageBox(L"SDL_CreateWindowFrom error");
		printf("SDL_CreateWindowFrom error");
		return;
	}

	//获取路径
	FreeVariable();
	// 读取文件头，将格式相关信息存放在AVFormatContext结构体中
	if (avformat_open_input(&m_pFormatCtx, filePath, nullptr, nullptr) != 0)
	{
		//MessageBox(L"avformat open input failed !", L"错误");
		printf("avformat open input failed!");
		return;
	}

	// 检测文件的流信息
	if (avformat_find_stream_info(m_pFormatCtx, nullptr) < 0)
	{
		//MessageBox(L"avformat find stream info failed !", L"错误");
		printf("avformat find stream info failed!");
		return;
	}

	//查找视频流 音频流
	for (int i = 0; i < m_pFormatCtx->nb_streams; i++)
	{
		if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			m_videoStream = i;
		else if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
			m_AudioStream = i;
	}
	if (m_videoStream == -1)
	{
		//MessageBox(L"没有找到视频流!", L"错误");
		printf("没有找到视频流!");
		return;
	}

	//video
	AVStream* vStream = m_pFormatCtx->streams[m_videoStream];
	m_pvCodecCtxOrg = vStream->codec;

	// 找到视频解码器
	m_pvCodec = avcodec_find_decoder(m_pvCodecCtxOrg->codec_id);
	if (!m_pvCodec)
	{
		//MessageBox(L"查找视频解码器失败!", L"错误");
		printf("查找视频解码器失败!");
		return;
	}

	// 不直接使用从AVFormatContext得到的CodecContext，要复制一个
	m_pvCodecCtx = avcodec_alloc_context3(m_pvCodec);
	if (avcodec_copy_context(m_pvCodecCtx, m_pvCodecCtxOrg) != 0)
	{
		//MessageBox(L"Could not copy vcodec context!", L"错误");
		printf("Could not copy vcodec context!");
		return;
	}

	//audio
	if (m_AudioStream >= 0)
	{
		AVStream* aStream = m_pFormatCtx->streams[m_AudioStream];
		m_paCodecCtxOrg = aStream->codec;

		// 找到音频解码器
		m_paCodec = avcodec_find_decoder(m_paCodecCtxOrg->codec_id);
		if (!m_paCodec)
		{
			//MessageBox(L"查找音频解码器失败!", L"错误");
			printf("查找音频解码器失败!");
			return;
		}

		m_paCodecCtx = avcodec_alloc_context3(m_paCodec);
		if (avcodec_copy_context(m_paCodecCtx, m_paCodecCtxOrg) != 0)
		{
			//MessageBox(L"Could not copy acodec context!", L"错误");
			printf("Could not copy acodec context!");
			return;
		}

		//声道数
		int channel = m_paCodecCtx->channels;
		//strTmp.Format(L"%d", channel);
		//GetDlgItem(IDC_EDIT_SDS)->SetWindowText(strTmp);
		//采样率
		int rate = m_paCodecCtx->sample_rate;
		//strTmp.Format(L"%d", rate);
		//GetDlgItem(IDC_EDIT_RATE)->SetWindowText(strTmp);
	}
	else
	{
		//GetDlgItem(IDC_EDIT_SDS)->SetWindowText(L"");
		//GetDlgItem(IDC_EDIT_RATE)->SetWindowText(L"");
	}

	double time = (double)(m_pFormatCtx->duration) / AV_TIME_BASE;//时长
	int us = (m_pFormatCtx->duration) % AV_TIME_BASE;
	int sec = (int)time % 60;
	int min = (int)time / 60 % 60;
	int h = (int)time / 60 / 60;
	//strTmp.Format(L"%02d时%02d分%02d秒%02d", h, min, sec, (100 * us) / AV_TIME_BASE);
	//GetDlgItem(IDC_EDIT_TIME)->SetWindowTextW(strTmp);

	int ml = m_pFormatCtx->bit_rate;//码率
	//strTmp.Format(L"%d", ml);
	//GetDlgItem(IDC_EDIT_ML)->SetWindowTextW(strTmp);

	AVInputFormat* avPtFmt = m_pFormatCtx->iformat;
	//GetDlgItem(IDC_EDIT_FORMAT_NAME)->SetWindowTextW(A2T(avPtFmt->name));
	//GetDlgItem(IDC_EDIT_FORMAT_LNAME)->SetWindowTextW(A2T(avPtFmt->long_name));
	//GetDlgItem(IDC_EDIT_FORMAT_EXNAME)->SetWindowTextW(A2T(avPtFmt->extensions));

	int frame_rate = 0;//帧率
	if (vStream->r_frame_rate.den > 0)
		frame_rate = av_q2d(vStream->r_frame_rate);//avStream->r_frame_rate.num / avStream->r_frame_rate.den;
	else if (m_pvCodecCtxOrg->framerate.den > 0)
		frame_rate = av_q2d(m_pvCodecCtxOrg->framerate);//m_pvCodecCtxOrg->framerate.num / m_pvCodecCtxOrg->framerate.den;

	int zs = vStream->nb_frames;
	if (zs == 0)
	{
		zs = time * frame_rate;
	}
	//strTmp.Format(L"%d", zs);
	//GetDlgItem(IDC_EDIT_ZS)->SetWindowTextW(strTmp);
	//strTmp.Format(L"%d", frame_rate);
	allTime = frame_rate;
	//GetDlgItem(IDC_EDIT_ZL)->SetWindowTextW(strTmp);
	//strTmp.Format(L"%d", m_pvCodecCtxOrg->width);
	//GetDlgItem(IDC_EDIT_WIDTH)->SetWindowTextW(strTmp);
	//strTmp.Format(L"%d", m_pvCodecCtxOrg->height);
	//GetDlgItem(IDC_EDIT_HEIGHT)->SetWindowTextW(strTmp);

	//这个是滚动条的设置
	//m_slider.SetRange(0, time * 1000);
	//m_slider.SetTicFreq(1);
	//m_slider.SetPos(0);

	//if (m_playType == EM_PLAY_TYPE_PAUSE)
	//{
	//	SetPlayType(EM_PLAY_TYPE_PLAY);
	//}
	//else if (m_playType == EM_PLAY_TYPE_STOP)
	//{
	//播放
	SetPlayType(EM_PLAY_TYPE_PLAY);
	m_hDecodeHandel = CreateThread(NULL, NULL, DecodeThread, this, 0, 0);
	//}

}

void VideoFile::FreeVariable()
{
	m_videoStream = -1;
	m_AudioStream = -1;
	if (m_pvCodecCtxOrg)
	{
		avcodec_close(m_pvCodecCtxOrg);
		m_pvCodecCtxOrg = nullptr;
	}
	if (m_pvCodecCtx)
	{
		avcodec_close(m_pvCodecCtx);
		m_pvCodecCtx = nullptr;
	}
	if (m_paCodecCtxOrg)
	{
		avcodec_close(m_paCodecCtxOrg);
		m_paCodecCtxOrg = nullptr;
	}
	if (m_paCodecCtx)
	{
		avcodec_close(m_paCodecCtx);
		m_paCodecCtx = nullptr;
	}
	if (m_pFormatCtx)
	{
		avformat_close_input(&m_pFormatCtx);
		m_pFormatCtx = nullptr;
	}
	if (m_sdlRenderer)
	{
		SDL_DestroyRenderer(m_sdlRenderer);
		m_sdlRenderer = nullptr;
	}
	if (m_sdlTexture)
	{
		SDL_DestroyTexture(m_sdlTexture);
		m_sdlTexture = nullptr;
	}
}

void VideoFile::SetPlayType(EM_PLAY_TYPE type)
{
	m_playType = type;
	switch (type)
	{
	case EM_PLAY_TYPE_PLAY:
	{
		//GetDlgItem(IDC_BTN_OPEN)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_DECODE_ONE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_PAUSE)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
		SetEvent(m_hSupendEvent);
		break;
	}
	case EM_PLAY_TYPE_PAUSE:
	{
		//GetDlgItem(IDC_BTN_DECODE_ONE)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_PAUSE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
		ResetEvent(m_hSupendEvent);
		break;
	}
	case EM_PLAY_TYPE_STOP:
	{
		SetEvent(m_hSupendEvent);
		if (m_hDecodeHandel != INVALID_HANDLE_VALUE)
		{
			WaitForSingleObject(m_hDecodeHandel, INFINITE);
			m_hDecodeHandel = INVALID_HANDLE_VALUE;
		}
		if (m_hVPlayHandel != INVALID_HANDLE_VALUE)
		{
			WaitForSingleObject(m_hVPlayHandel, INFINITE);
			m_hVPlayHandel = INVALID_HANDLE_VALUE;
		}
		if (m_hAPlayHandel != INVALID_HANDLE_VALUE)
		{
			WaitForSingleObject(m_hAPlayHandel, INFINITE);
			m_hAPlayHandel = INVALID_HANDLE_VALUE;
		}

		ClearQueue();
		//GetDlgItem(IDC_BTN_OPEN)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_DECODE_ONE)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_PAUSE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
		break;
	}
	}
}

EM_PLAY_TYPE VideoFile::GetPlayType()
{
	return m_playType;
}

void VideoFile::ClearQueue()
{
	while (!m_qAbuf.empty())
	{
		ST_ABUF* stBuf = &m_qAbuf.front();
		delete[] stBuf->buf;
		m_qAbuf.pop();
	}
	while (!m_VList.empty())
	{
		AVPacket* pkt = &m_VList.front();
		av_free_packet(pkt);
		m_VList.pop();
	}
	while (!m_AList.empty())
	{
		AVPacket* pkt = &m_AList.front();
		av_free_packet(pkt);
		m_AList.pop_front();
	}
}


DWORD __stdcall DecodeThread(LPVOID lpParam)
{
	VideoFile* pThis = (VideoFile*)lpParam;

	do
	{
		if (!pThis->m_pvCodecCtxOrg || !pThis->m_pvCodec)
		{
			break;
		}
		if (avcodec_open2(pThis->m_pvCodecCtx, pThis->m_pvCodec, nullptr) < 0)
		{
			//异步通信
			//pThis->PostMessageW(WM_ERROR_MSG, EM_AVCODE_OPEN_ERROR);
			break;
		}

		//打开音视频播放线程
		pThis->m_hVPlayHandel = CreateThread(NULL, NULL, VideoThread, pThis, 0, 0);
		pThis->m_hAPlayHandel = CreateThread(NULL, NULL, AudioThread, pThis, 0, 0);

		//播放前先seek到起点
		av_seek_frame(pThis->m_pFormatCtx, pThis->m_videoStream, 0, AVSEEK_FLAG_BACKWARD);

		while (true)
		{
			SetEvent(pThis->m_hDecodeEvent);//若为暂停状态，执行到此处才表示该线程真正暂停了
			WaitForSingleObject(pThis->m_hSupendEvent, INFINITE);//暂停后，此处会一直等待，直到SetEvent(m_hSupendEvent)
			ResetEvent(pThis->m_hDecodeEvent);
			if (pThis->GetPlayType() == EM_PLAY_TYPE_STOP)
			{
				break;
			}

			{
				std::lock_guard<mutex> mtx_locker(pThis->m_VMutex);
				int v_size = pThis->m_VList.size();
				if (v_size >= MAX_VQUEUE)
				{
					//当队列饱和时等待播放线程消耗再继续解码放入，否则内存占用越来越大
					continue;
				}
			}

			AVPacket packet;
			if (av_read_frame(pThis->m_pFormatCtx, &packet) >= 0)
			{
				pThis->m_bReadPacketEnd = false;
				if (packet.stream_index == pThis->m_videoStream)
				{
					std::lock_guard<mutex> mtx_locker(pThis->m_VMutex);
					pThis->m_VList.push(packet);
				}
				else if (packet.stream_index == pThis->m_AudioStream)
				{
					std::lock_guard<mutex> mtx_locker(pThis->m_AMutex);
					pThis->m_AList.push_back(packet);

				}
			}
			else
				pThis->m_bReadPacketEnd = true; //若此时播放还未结束，将进度条向前拉，则m_bReadPacketEnd = false
		}
	} while (0);
	return 0;
}

DWORD __stdcall VideoThread(LPVOID lpParam)
{
	VideoFile* pThis = (VideoFile*)lpParam;

	//------------SDL----------------
	if (!pThis->m_sdlRenderer && !pThis->m_sdlTexture)
	{
		pThis->m_sdlRenderer = SDL_CreateRenderer(pThis->m_sdlWindow, -1, 0);
		pThis->m_sdlTexture = SDL_CreateTexture(pThis->m_sdlRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, pThis->m_pvCodecCtx->width, pThis->m_pvCodecCtx->height);
	}
	//----------------------------------

	AVFrame* pFrame = av_frame_alloc();
	AVFrame* pFrameYUV420 = av_frame_alloc();

	// 使用的缓冲区的大小
	int numBytes = 0;
	uint8_t* buffer = nullptr;

	//AV_PIX_FMT_BGR24 / AV_PIX_FMT_YUV420P
	numBytes = avpicture_get_size(AV_PIX_FMT_YUV420P, pThis->m_pvCodecCtx->width, pThis->m_pvCodecCtx->height);
	buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));

	avpicture_fill((AVPicture*)pFrameYUV420, buffer, AV_PIX_FMT_YUV420P, pThis->m_pvCodecCtx->width, pThis->m_pvCodecCtx->height);

	struct SwsContext* sws_ctx = nullptr;
	sws_ctx = sws_getContext(pThis->m_pvCodecCtx->width, pThis->m_pvCodecCtx->height, pThis->m_pvCodecCtx->pix_fmt,
		pThis->m_pvCodecCtx->width, pThis->m_pvCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BILINEAR, nullptr, nullptr, nullptr);

	while (true)
	{
		SetEvent(pThis->m_hVideoEvent);//若为暂停状态，执行到此处才表示真正暂停了
		WaitForSingleObject(pThis->m_hSupendEvent, INFINITE);//暂停后，此处会一直等待，直到SetEvent(m_hSupendEvent)
		ResetEvent(pThis->m_hVideoEvent);
		if (pThis->GetPlayType() == EM_PLAY_TYPE_STOP)
		{
			break;
		}

		if (!pThis->m_VList.empty())
		{
			AVPacket* packet = &pThis->m_VList.front();
			if (packet->buf == NULL)
			{
				av_free_packet(packet);
				std::lock_guard<mutex> mtx_locker(pThis->m_VMutex);
				pThis->m_VList.pop();
				continue;
			}
			//视频处理
			int ret = avcodec_send_packet(pThis->m_pvCodecCtx, packet);
			if (ret < 0)
			{
				av_free_packet(packet);
				//pThis->PostMessage(WM_ERROR_MSG, NULL, EM_SEND_PACKET_ERROR);
				break;
			}
			while (ret >= 0)
			{
				ret = avcodec_receive_frame(pThis->m_pvCodecCtx, pFrame);
				if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
				{
					ret = 0;
					break;
				}
				else if (ret < 0)
					continue;

				//图像转换
				sws_scale(sws_ctx, (uint8_t const * const *)pFrame->data, pFrame->linesize, 0,
					pThis->m_pvCodecCtx->height, pFrameYUV420->data, pFrameYUV420->linesize);

				int pts = packet->pts > 0 ? packet->pts : packet->dts;

				//当前帧显示时间
				double sec = pts * av_q2d(pThis->m_pFormatCtx->streams[pThis->m_videoStream]->time_base);

				{
					std::lock_guard<mutex> mtx_locker(pThis->m_pSizeMutex);
					//通过SDL来显示
					SDL_UpdateTexture(pThis->m_sdlTexture, NULL, pFrameYUV420->data[0], pFrameYUV420->linesize[0]);
					SDL_RenderClear(pThis->m_sdlRenderer);
					SDL_RenderCopy(pThis->m_sdlRenderer, pThis->m_sdlTexture, NULL, NULL);
					SDL_RenderPresent(pThis->m_sdlRenderer);
				}

				//更新进度条
				//pThis->PostMessageW(WM_UPDATE_SLIDER, NULL, sec * 1000);
				int zl = pThis->allTime;
				//每一帧显示时间
				Sleep(1000 / zl);
			}
			av_free_packet(packet);
			std::lock_guard<mutex> mtx_locker(pThis->m_VMutex);
			pThis->m_VList.pop();
		}
		else if (pThis->m_bReadPacketEnd)
		{
			//解码结束且队列为空则播放完成
			break;
		}
	}

	av_free(buffer);
	av_frame_free(&pFrameYUV420);
	av_frame_free(&pFrame);

	if (pThis->GetPlayType() != EM_PLAY_TYPE_STOP)
	{
		pThis->m_hVPlayHandel = INVALID_HANDLE_VALUE;
		pThis->SetPlayType(EM_PLAY_TYPE_STOP);
	}
	//pThis->PostMessage(WM_SHOW_BK, NULL, 0);
	return 0;
}

DWORD __stdcall AudioThread(LPVOID lpParam)
{
	VideoFile* pThis = (VideoFile*)lpParam;

	do
	{
		CoInitialize(NULL);
		if (!pThis->m_paCodecCtxOrg || !pThis->m_paCodec)
		{
			break;
		}
		if (avcodec_open2(pThis->m_paCodecCtx, pThis->m_paCodec, nullptr) != 0)
		{
			break;
		}

		//输入的采样格式
		enum AVSampleFormat in_sample_fmt = pThis->m_paCodecCtx->sample_fmt;
		//输出的采样格式 16bit PCM
		enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
		//输入的采样率
		int in_sample_rate = pThis->m_paCodecCtx->sample_rate;
		//输出的采样率
		int out_sample_rate = in_sample_rate;
		//输入的声道布局
		uint64_t in_ch_layout = av_get_default_channel_layout(pThis->m_paCodecCtx->channels);
		//输出的声道布局
		uint64_t out_ch_layout = av_get_default_channel_layout(2);

		//输出通道数
		int out_channels = av_get_channel_layout_nb_channels(out_ch_layout);
		int out_nb_samples = pThis->m_paCodecCtx->frame_size;

		//SDL_AudioSpec
		SDL_AudioSpec wanted_spec;
		wanted_spec.freq = out_sample_rate;
		wanted_spec.format = AUDIO_S16SYS;
		wanted_spec.channels = out_channels;
		wanted_spec.silence = 0;
		wanted_spec.samples = out_nb_samples;
		wanted_spec.callback = SDL_AudioCallPlay;
		wanted_spec.userdata = pThis;

		if (SDL_OpenAudio(&wanted_spec, NULL) < 0)
		{
			//pThis->PostMessageW(WM_ERROR_MSG, EM_SDL_OPENAUDIO_ERROR);
			break;
		}

		//Swr
		struct SwrContext *au_convert_ctx;
		au_convert_ctx = swr_alloc();
		au_convert_ctx = swr_alloc_set_opts(
			au_convert_ctx,
			out_ch_layout,
			out_sample_fmt,
			out_sample_rate,
			in_ch_layout,
			pThis->m_paCodecCtx->sample_fmt,
			pThis->m_paCodecCtx->sample_rate,
			0,
			NULL);
		swr_init(au_convert_ctx);

		//Play
		SDL_PauseAudio(0);

		int ret = 0;
		AVPacket packet;
		uint8_t *out_buffer = (uint8_t *)av_malloc(2 * out_sample_rate);
		AVFrame* pFrame = av_frame_alloc();

		while (true)
		{
			SetEvent(pThis->m_hAudioEvent);
			WaitForSingleObject(pThis->m_hSupendEvent, INFINITE);
			ResetEvent(pThis->m_hAudioEvent);
			if (pThis->GetPlayType() == EM_PLAY_TYPE_STOP)
			{
				av_seek_frame(pThis->m_pFormatCtx, pThis->m_AudioStream, 0, AVSEEK_FLAG_BACKWARD);
				break;
			}


			AVPacket* packet = nullptr;
			{
				std::lock_guard<mutex> mtx_locker(pThis->m_AMutex);
				if (!pThis->m_AList.empty())
				{
					packet = &pThis->m_AList.front();
					if (packet->buf == NULL)
					{
						av_free_packet(packet);
						pThis->m_AList.pop_front();
						continue;
					}
				}
				else
					continue;
			}

			ret = avcodec_send_packet(pThis->m_paCodecCtx, packet);
			if (ret < 0)
			{
				//pThis->PostMessage(WM_ERROR_MSG, NULL, EM_SEND_PACKET_ERROR);
				break;
			}
			while (ret >= 0)
			{
				ret = avcodec_receive_frame(pThis->m_paCodecCtx, pFrame);
				if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
				{
					break;
				}
				else if (ret < 0)
					continue;
				else
				{
					int nRet = swr_convert(au_convert_ctx, &out_buffer, 2 * out_sample_rate, (const uint8_t**)pFrame->data, pFrame->nb_samples);
					int buf_len = nRet * out_channels * GetSampleCount(out_sample_fmt);

					ST_ABUF st_buf;
					st_buf.buf = new Uint8[2 * out_sample_rate];
					memset(st_buf.buf, 0, 2 * out_sample_rate);
					memcpy(st_buf.buf, out_buffer, buf_len);
					st_buf.buf_len = buf_len;
					st_buf.pts = packet->pts > 0 ? packet->pts : packet->dts;

					//将解码的音频数据放入队列
					std::lock_guard<mutex> mtx_locker(pThis->m_CMutex);
					pThis->m_qAbuf.push(st_buf);
				}
			}

			av_free_packet(packet);
			std::lock_guard<mutex> mtx_locker(pThis->m_AMutex);
			pThis->m_AList.pop_front();
		}
		av_free(out_buffer);
		SDL_CloseAudio();
		swr_free(&au_convert_ctx);
	} while (0);
	return 0;
}
