
// PublicSecurityVideoRetrievalSystemDoc.h : CPublicSecurityVideoRetrievalSystemDoc 类的接口
//
#include "opencv.hpp"

#pragma once
using namespace cv;
using namespace std;

class CPublicSecurityVideoRetrievalSystemDoc : public CDocument
{
protected: // 仅从序列化创建
	CPublicSecurityVideoRetrievalSystemDoc();
	DECLARE_DYNCREATE(CPublicSecurityVideoRetrievalSystemDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CPublicSecurityVideoRetrievalSystemDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// 在打开窗口选中的文件的全路径
	CString m_filepath;
	// 打开窗口的文件所在的文件夹中所有的路径
	vector<String> allFilePath;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
