#pragma once
#include "resource.h"
#include "afxbutton.h"

// CCebianDlg 对话框

class CCebianDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCebianDlg)

public:
	CCebianDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCebianDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	CMFCButton b_AI_Save;
	CMFCButton b_AI_Start;
	CMFCButton b_Numbers;
	CMFCButton b_TakePicture;
	CMFCButton b_Seconds;
	CMFCButton b_VideoShooting;
	CMFCButton b_PhotoHistory;
	CMFCButton b_CameraShooting;
	CMFCButton b_ESS_3;
	CMFCButton b_ESS;
	CMFCButton b_ISO_3;
	CMFCButton b_IOS_A;
	CMFCButton b_Shutdown;
	CMFCButton b_SetUp;
	virtual BOOL OnInitDialog();

	CMFCButton b_Bottom_1;
	CMFCButton b_Bottom_2;
	CMFCButton b_Bottom_3;
	CMFCButton b_Bottom_4;
};
