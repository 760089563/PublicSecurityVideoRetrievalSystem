#include "stdafx.h"
#include "CebianBar.h"

CCebianDlg CCebianBar::ceDlg;

CCebianBar::CCebianBar()
{
}


CCebianBar::~CCebianBar()
{
}
BEGIN_MESSAGE_MAP(CCebianBar, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


int CCebianBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ceDlg.Create(IDD_DIALOG1, this);
	ceDlg.ShowWindow(SW_SHOW);
	return 0;
}


void CCebianBar::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (ceDlg.GetSafeHwnd())
	{
		CRect rct;
		GetClientRect(rct);
		ceDlg.MoveWindow(rct);
	}

}
