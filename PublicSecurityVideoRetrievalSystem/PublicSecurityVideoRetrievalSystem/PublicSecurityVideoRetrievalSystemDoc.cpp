
// PublicSecurityVideoRetrievalSystemDoc.cpp : CPublicSecurityVideoRetrievalSystemDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PublicSecurityVideoRetrievalSystem.h"
#endif

#include "PublicSecurityVideoRetrievalSystemDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPublicSecurityVideoRetrievalSystemDoc

IMPLEMENT_DYNCREATE(CPublicSecurityVideoRetrievalSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CPublicSecurityVideoRetrievalSystemDoc, CDocument)
END_MESSAGE_MAP()


// CPublicSecurityVideoRetrievalSystemDoc 构造/析构

CPublicSecurityVideoRetrievalSystemDoc::CPublicSecurityVideoRetrievalSystemDoc()
{
	// TODO:  在此添加一次性构造代码

}

CPublicSecurityVideoRetrievalSystemDoc::~CPublicSecurityVideoRetrievalSystemDoc()
{
}

BOOL CPublicSecurityVideoRetrievalSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPublicSecurityVideoRetrievalSystemDoc 序列化

void CPublicSecurityVideoRetrievalSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CPublicSecurityVideoRetrievalSystemDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CPublicSecurityVideoRetrievalSystemDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CPublicSecurityVideoRetrievalSystemDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPublicSecurityVideoRetrievalSystemDoc 诊断

#ifdef _DEBUG
void CPublicSecurityVideoRetrievalSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPublicSecurityVideoRetrievalSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPublicSecurityVideoRetrievalSystemDoc 命令


BOOL CPublicSecurityVideoRetrievalSystemDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	// 保存当前选中的文件的全路径名
	this->m_filepath = lpszPathName;

	// 获取选中的文件所在文件夹的所有文件的路径名
	CString FilePath = this->m_filepath.Left(this->m_filepath.ReverseFind('\\'));
	USES_CONVERSION;
	cv::String path = W2A(FilePath);
	glob(path, allFilePath, false);
	return TRUE;
}
