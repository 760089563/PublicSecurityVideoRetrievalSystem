// CebianDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PublicSecurityVideoRetrievalSystem.h"
#include "CebianDlg.h"
#include "afxdialogex.h"


// CCebianDlg 对话框

IMPLEMENT_DYNAMIC(CCebianDlg, CDialogEx)

CCebianDlg::CCebianDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCebianDlg::IDD, pParent)
{

}

CCebianDlg::~CCebianDlg()
{
}

void CCebianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON1, b_AI_Save);
	DDX_Control(pDX, IDC_MFCBUTTON2, b_AI_Start);
	DDX_Control(pDX, IDC_MFCBUTTON3, b_Numbers);
	DDX_Control(pDX, IDC_MFCBUTTON5, b_TakePicture);
	DDX_Control(pDX, IDC_MFCBUTTON4, b_Seconds);
	DDX_Control(pDX, IDC_MFCBUTTON7, b_VideoShooting);
	DDX_Control(pDX, IDC_MFCBUTTON6, b_PhotoHistory);
	DDX_Control(pDX, IDC_MFCBUTTON8, b_CameraShooting);
	DDX_Control(pDX, IDC_MFCBUTTON9, b_ESS_3);
	DDX_Control(pDX, IDC_MFCBUTTON12, b_ESS);
	DDX_Control(pDX, IDC_MFCBUTTON10, b_ISO_3);
	DDX_Control(pDX, IDC_MFCBUTTON13, b_IOS_A);
	DDX_Control(pDX, IDC_MFCBUTTON11, b_Shutdown);
	DDX_Control(pDX, IDC_MFCBUTTON14, b_SetUp);
	DDX_Control(pDX, IDC_MFCBUTTON15, b_Bottom_1);
	DDX_Control(pDX, IDC_MFCBUTTON16, b_Bottom_2);
	DDX_Control(pDX, IDC_MFCBUTTON17, b_Bottom_3);
	DDX_Control(pDX, IDC_MFCBUTTON18, b_Bottom_4);
}


BEGIN_MESSAGE_MAP(CCebianDlg, CDialogEx)
//	ON_WM_CREATE()
//	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCebianDlg 消息处理程序




BOOL CCebianDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HICON m_hicn1 = AfxGetApp()->LoadIcon(IDI_ICON2);
	b_AI_Save.SetIcon(m_hicn1);
	b_AI_Start.SetIcon(m_hicn1);
	b_CameraShooting.SetIcon(m_hicn1);
	b_ESS.SetIcon(m_hicn1);
	b_ESS_3.SetIcon(m_hicn1);
	b_IOS_A.SetIcon(m_hicn1);
	b_ISO_3.SetIcon(m_hicn1);
	b_Numbers.SetIcon(m_hicn1);
	b_PhotoHistory.SetIcon(m_hicn1);
	b_Seconds.SetIcon(m_hicn1);
	b_SetUp.SetIcon(m_hicn1);
	b_Shutdown.SetIcon(m_hicn1);
	b_TakePicture.SetIcon(m_hicn1);
	b_VideoShooting.SetIcon(m_hicn1);

	HICON m_hicn2 = AfxGetApp()->LoadIcon(IDI_ICON1);
	b_Bottom_1.SetIcon(m_hicn2);
	b_Bottom_2.SetIcon(m_hicn2);
	b_Bottom_3.SetIcon(m_hicn2);
	b_Bottom_4.SetIcon(m_hicn2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
