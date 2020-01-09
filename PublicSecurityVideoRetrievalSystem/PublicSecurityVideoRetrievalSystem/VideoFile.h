#pragma once

#include "stdafx.h"
#include <stdio.h>


#include <atomic>
#include "afxwin.h"
#include "afxcmn.h"
#include <queue>
#include <list>
#include <mutex>

using std::queue;
using std::list;
using std::mutex;

#define LOCK_MUTEX(X)	WaitForSingleObject(X, INFINITE); 
#define UNLOCK_MUTEX(X)	ReleaseMutex(X); 

#define  WM_SHOW_BK WM_USER+10 //显示默认背景消息
#define  WM_UPDATE_SLIDER WM_USER+11 //更新进度条消息
#define  WM_ERROR_MSG WM_USER+12 //错误消息
#define  MAX_VQUEUE 300 //图片帧队列饱和值

//错误类型
enum EM_ERROR_TYPE
{
	EM_SEND_PACKET_ERROR,
	EM_AVCODE_OPEN_ERROR,
	EM_SDL_OPENAUDIO_ERROR,
	EM_ERROR_MAX

};

//播放状态
enum EM_PLAY_TYPE
{
	EM_PLAY_TYPE_PLAY,//播放
	EM_PLAY_TYPE_PAUSE,//暂停
	EM_PLAY_TYPE_STOP,//停止
	EM_PLAY_TYPE_MAX
};

struct ST_ABUF
{
	Uint8* buf;
	int buf_len;
	int pts;//当前播放声音的时间戳
};


class VideoFile
{
public:
	VideoFile(CWnd* videoWnd, char *filePath);
	~VideoFile();


private:
	//HICON m_hIcon;
	std::atomic<EM_PLAY_TYPE>     m_playType;//播放状态
	char* filePath;
	CWnd* videoWnd;
	

public:
	//显示视频
	void ShowVideo();
	//释放变量
	void FreeVariable();
	//显示默认背景图片
	void showBk(CString strPath = L"bk.bmp");
	//保存图片
	void saveFrame(AVFrame* pFrame, int width, int height, int iFrame);
	//设置播放状态
	void SetPlayType(EM_PLAY_TYPE type);
	//获取播放状态
	EM_PLAY_TYPE GetPlayType();
	//清空队列
	void ClearQueue();

public:
	//总时间数
	int allTime = 0;


	HANDLE           m_hSupendEvent;//暂停信号
	HANDLE           m_hDecodeEvent;//DecodeThread暂停标志
	HANDLE           m_hVideoEvent;//VideoThread暂停标志
	HANDLE           m_hAudioEvent;//AudioThread暂停标志
	HANDLE           m_hACallEvent;//AudioCallPlay暂停标志
	HANDLE           m_hDecodeHandel;//解码线程句柄
	HANDLE           m_hVPlayHandel;//视频播放线程句柄
	HANDLE           m_hAPlayHandel;//音频播放线程句柄

	//av_read_frame已经读到最后则m_bReadPacketEnd = true，若此时播放还未结束，将进度条向前拉，则m_bReadPacketEnd = false
	bool             m_bReadPacketEnd;

	AVFormatContext* m_pFormatCtx;

	//video
	int              m_videoStream;//视频流索引
	AVCodecContext*  m_pvCodecCtxOrg;
	AVCodecContext*  m_pvCodecCtx;
	AVCodec*         m_pvCodec;
	queue<AVPacket>  m_VList;//存放视频的AVPacket
	mutex            m_VMutex;//对m_VList操作的互斥锁
	mutex            m_pSizeMutex;//对改变窗口大小的互斥锁

	//audio
	int              m_AudioStream;//音频流索引
	AVCodecContext*  m_paCodecCtxOrg;
	AVCodecContext*  m_paCodecCtx;
	AVCodec*         m_paCodec;
	queue<ST_ABUF>   m_qAbuf;//声音队列，存放解码后的数据
	list<AVPacket>   m_AList;//存放音频的AVPacket
	mutex            m_AMutex;//对m_AList操作的互斥锁
	mutex            m_CMutex;//对m_qAbuf操作的互斥锁

	//sdl
	SDL_Window*      m_sdlWindow;
	SDL_Renderer*    m_sdlRenderer;
	SDL_Texture*     m_sdlTexture;

	//控件
	CStatic          m_pic;
	CEdit            m_editFile;
	CStatic          m_group;
};

