
// PublicSecurityVideoRetrievalSystemDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include <vector>
#include <iostream>

using namespace std;

// CPublicSecurityVideoRetrievalSystemDlg dialog
class CPublicSecurityVideoRetrievalSystemDlg : public CDialogEx
{
// Construction
public:
	CPublicSecurityVideoRetrievalSystemDlg(CWnd* pParent = NULL);	// standard constructor
	CString filePath;
// Dialog Data
	enum { IDD = IDD_PUBLICSECURITYVIDEORETRIEVALSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
//	afx_msg void OnSetpath();
	CTreeCtrl fileTree;
};