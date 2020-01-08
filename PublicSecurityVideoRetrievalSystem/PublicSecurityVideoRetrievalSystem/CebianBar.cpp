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

	// TODO:  �ڴ������ר�õĴ�������
	ceDlg.Create(IDD_DIALOG1, this);
	ceDlg.ShowWindow(SW_SHOW);
	return 0;
}


void CCebianBar::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (ceDlg.GetSafeHwnd())
	{
		CRect rct;
		GetClientRect(rct);
		ceDlg.MoveWindow(rct);
	}

}
