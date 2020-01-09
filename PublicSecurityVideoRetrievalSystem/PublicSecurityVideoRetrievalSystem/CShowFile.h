#pragma once
#include "PublicSecurityVideoRetrievalSystem.h"
#include "PublicSecurityVideoRetrievalSystemDoc.h"

#include "MainFrm.h"
#include "CShowFileDir.h"

#include <core\core.hpp>
#include <opencv.hpp>
#include "opencv2/opencv.hpp"
#include <highgui\highgui.hpp>
#include <highgui\highgui_c.h>

#include "ImageFile.h"
#include "VideoFile.h"

//中间主要窗口的视图区域
// CShowFile 窗体视图

class CShowFile : public CFormView
{
	DECLARE_DYNCREATE(CShowFile)

protected:
	CShowFile();           // 动态创建所使用的受保护的构造函数
	virtual ~CShowFile();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_FILE };
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

	//获取显示窗口句柄
	bool isPicture = false;	//判断是否是图片
	ImageFile* imageControl = NULL;
	VideoFile* videoControl = NULL;
	CString filePath;
	double scale = 1.0;
	
public:
	void Init();

private:
	void Destroy();
	CWnd* GetMainFrameWnd();

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnStnClickedStaticPic();
};


