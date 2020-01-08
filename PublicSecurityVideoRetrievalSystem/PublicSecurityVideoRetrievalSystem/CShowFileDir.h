#pragma once
#include "ImageFile.h"
#include "VideoFile.h"
#include "PublicSecurityVideoRetrievalSystem.h"
#include "PublicSecurityVideoRetrievalSystemDoc.h"
#include "CShowFile.h"
#include "MainFrm.h"

//整个窗口考左边的资源视图
// CShowFileDir 窗体视图

class CShowFileDir : public CFormView
{
	DECLARE_DYNCREATE(CShowFileDir)

protected:
	CShowFileDir();           // 动态创建所使用的受保护的构造函数
	virtual ~CShowFileDir();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_FILE_DIR };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMFCShellListCtrl m_wndShellList;

public:
	CString filePath;		//当前选中的文件路径
	bool isPicture = false;
private:
	void Init();
	afx_msg void OnClickListFileDir(NMHDR *pNMHDR, LRESULT *pResult);
};


