// CShowFileDir.cpp: 实现文件
//
#include "stdafx.h"

#include "CShowFileDir.h"
#include <afxpriv.h>


IMPLEMENT_DYNCREATE(CShowFileDir, CFormView)

CShowFileDir::CShowFileDir()
	: CFormView(IDD_SHOW_FILE_DIR)
{
	TCHAR temp[255];
	SHGetSpecialFolderPath(0, temp, CSIDL_DESKTOPDIRECTORY, 0);
	filePath = temp;
}

CShowFileDir::~CShowFileDir()
{
}

void CShowFileDir::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILE_DIR, m_wndShellList);
}

BEGIN_MESSAGE_MAP(CShowFileDir, CFormView)
//	ON_NOTIFY(NM_CLICK, IDC_LIST_FILE_DIR, &CShowFileDir::OnNMClickListFileDir)
//	ON_WM_CREATE()
//ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILE_DIR, &CShowFileDir::OnDblclkListFileDir)
//ON_NOTIFY(NM_CLICK, IDC_LIST_FILE_DIR, &CShowFileDir::OnClickListFileDir)
//ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILE_DIR, &CShowFileDir::OnDblclkListFileDir)
ON_NOTIFY(NM_CLICK, IDC_LIST_FILE_DIR, &CShowFileDir::OnClickListFileDir)
END_MESSAGE_MAP()


// CShowFileDir 诊断

#ifdef _DEBUG
void CShowFileDir::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowFileDir::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowFileDir 消息处理程序



//做初始化准备
void CShowFileDir::Init() {
	//筛选出主窗口的View类
	CShowFile* view = NULL;
	CView *pView;
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = GetDocument()->GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CShowFile)))
		{
			view = (CShowFile*)pView;
			break;
		}
	}
	//进行图像与视频的分开操作
	view->isPicture = isPicture;
	view->filePath = filePath;
	view->Init();
	
}



void CShowFileDir::OnClickListFileDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	POSITION pos = m_wndShellList.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
	{
		return;
	}
	int index = (int)m_wndShellList.GetNextSelectedItem(pos);
	//得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列）     获取点击的文件
	CString fileName = m_wndShellList.GetItemText(index, 0);
	CString temp = filePath;
	filePath = filePath + "\\" + fileName;
	//如果获取到了视频
	if (fileName.Find(_T(".mp4")) >= 0) {
		isPicture = false;
		Init();
		//重置
		filePath = temp;
	}
	//如果获取到了图片
	else if (fileName.Find(_T(".bmp")) >= 0) {
		isPicture = true;
		Init();
		//重置
		filePath = temp;
	}
	else
	{
		return;
	}
}
