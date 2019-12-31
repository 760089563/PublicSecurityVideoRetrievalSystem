
// PublicSecurityVideoRetrievalSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PublicSecurityVideoRetrievalSystem.h"
#include "PublicSecurityVideoRetrievalSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPublicSecurityVideoRetrievalSystemDlg dialog



CPublicSecurityVideoRetrievalSystemDlg::CPublicSecurityVideoRetrievalSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPublicSecurityVideoRetrievalSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPublicSecurityVideoRetrievalSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE2FilePath, fileTree);
}

BEGIN_MESSAGE_MAP(CPublicSecurityVideoRetrievalSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_COMMAND(ID_SETPATH, &CPublicSecurityVideoRetrievalSystemDlg::OnSetpath)
END_MESSAGE_MAP()


// CPublicSecurityVideoRetrievalSystemDlg message handlers

BOOL CPublicSecurityVideoRetrievalSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//����λ�ö���������
	this->filePath = _T("C:/Users/76008/Desktop/test/");
	CFileFind find;
	CString fileName = _T("");
	vector<CString> fullName;
	BOOL IsFind = find.FindFile(this->filePath + _T("/*.*"));
	while (IsFind)
	{
		IsFind = find.FindNextFile();
		if (find.IsDots())
		{
			continue;
		}
		else
		{
			fileName = find.GetFileName();
			fullName.push_back(fileName);
		}
	}
	//����
	HTREEITEM hRoot,secondRoot;
	hRoot = this->fileTree.InsertItem(_T("test"), TVI_ROOT);
	vector<CString>::iterator iter;
	for (iter = fullName.begin(); iter != fullName.end(); ++iter)
	{
		//�ж��Ƿ����. �����ж��Ƿ����ļ���
		if ((*iter).Find('.')!=NULL)
		{
			this->fileTree.InsertItem((*iter), hRoot);
		}
		else
		{
			secondRoot = this->fileTree.InsertItem((*iter), hRoot);
		}
	}
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPublicSecurityVideoRetrievalSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPublicSecurityVideoRetrievalSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPublicSecurityVideoRetrievalSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


