// CShowFile.cpp: 实现文件
//
#include "stdafx.h"
#include "CShowFile.h"

// CShowFile

IMPLEMENT_DYNCREATE(CShowFile, CFormView)

using namespace cv;

CShowFile::CShowFile()
	: CFormView(IDD_SHOW_FILE)
{

}

CShowFile::~CShowFile()
{
}

void CShowFile::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShowFile, CFormView)
//	ON_BN_CLICKED(IDC_BUTTON1, &CShowFile::OnBnClickedShowPicture)
ON_WM_MOUSEWHEEL()
ON_WM_KEYDOWN()
// ON_STN_CLICKED(IDC_STATIC_PIC, &CShowFile::OnStnClickedStaticPic)
END_MESSAGE_MAP()


// CShowFile 诊断

#ifdef _DEBUG
void CShowFile::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowFile::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


//返回主要的窗口句柄
CWnd* CShowFile::GetMainFrameWnd()
{
	//CWnd* temp = this->GetDlgItem(IDC_STATIC_PIC);
	return this;
}

//鼠标滚轮事件实现放大缩小的操作
BOOL CShowFile::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (isPicture && imageControl!=NULL)
	{
		//刷新pictureControl
		GetMainFrameWnd()->ShowWindow(FALSE);
		GetMainFrameWnd()->ShowWindow(TRUE);
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if (zDelta > 0)//滚轮上滚   放大
		{
			scale += 0.1;
			this->imageControl->SetScale(scale);
		}
		else if (zDelta < 0 && scale>0)//滚轮下滚 缩小
		{
			scale -= 0.1;
			this->imageControl->SetScale(scale);
		}
	}
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}

//当点击左边的文件名的时候就调用
void CShowFile::Init()
{
	Destroy();//先进行内存回收

	USES_CONVERSION;
	char *path = T2A(filePath);

	if (isPicture)
	{
		imageControl = new ImageFile(GetMainFrameWnd(), path);
		imageControl->ShowImage();
	}
	else
	{
		videoControl = new VideoFile(GetMainFrameWnd(), path);
		videoControl->ShowVideo();
	}

}

//进行内存回收防止泄露
void CShowFile::Destroy() {
	if (imageControl!=NULL)
	{
		delete imageControl;
		imageControl = NULL;
	}
	if (videoControl!=NULL)
	{
		delete videoControl;
		videoControl = NULL;
	}
}

//判断是否键盘按下了
void CShowFile::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (videoControl!=NULL && !isPicture)//有视频并且不显示图片的时候
	{
		switch (nChar)
		{
		case VK_SPACE:		//判断是否按下空格键
			videoControl->SetPlayType(EM_PLAY_TYPE_PAUSE);
			break;
		case VK_LEFT:		//判断是否按下左箭头
			//videoControl->isBack = true;
			break;
		case VK_RIGHT:		//判断是否按下右箭头
			//videoControl->isForward = true;
			break;
		default:
			break;
		}
	}
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}


//void CShowFile::OnStnClickedStaticPic()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}
