#pragma once


// CExplorer 对话框

class CExplorer : public CDialogEx
{
	DECLARE_DYNAMIC(CExplorer)

public:
	CExplorer(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CExplorer();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPLORER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
