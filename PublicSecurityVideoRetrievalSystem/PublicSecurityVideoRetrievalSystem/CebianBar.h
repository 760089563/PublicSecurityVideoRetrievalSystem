#pragma once


//窗口左边的按钮控制
#include "afxdockablepane.h"
#include "CebianDlg.h"

class CCebianBar :
	public CDockablePane
{
public:
	CCebianBar();
	~CCebianBar();
public:
	static CCebianDlg ceDlg;
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CRect m_rect;
};

