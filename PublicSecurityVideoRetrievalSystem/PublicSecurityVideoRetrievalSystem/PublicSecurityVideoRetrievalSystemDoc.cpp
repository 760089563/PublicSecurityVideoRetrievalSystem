
// PublicSecurityVideoRetrievalSystemDoc.cpp : CPublicSecurityVideoRetrievalSystemDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CPublicSecurityVideoRetrievalSystemDoc ����/����

CPublicSecurityVideoRetrievalSystemDoc::CPublicSecurityVideoRetrievalSystemDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CPublicSecurityVideoRetrievalSystemDoc::~CPublicSecurityVideoRetrievalSystemDoc()
{
}

BOOL CPublicSecurityVideoRetrievalSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPublicSecurityVideoRetrievalSystemDoc ���л�

void CPublicSecurityVideoRetrievalSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CPublicSecurityVideoRetrievalSystemDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CPublicSecurityVideoRetrievalSystemDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CPublicSecurityVideoRetrievalSystemDoc ���

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


// CPublicSecurityVideoRetrievalSystemDoc ����


BOOL CPublicSecurityVideoRetrievalSystemDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	// ���浱ǰѡ�е��ļ���ȫ·����
	this->m_filepath = lpszPathName;

	// ��ȡѡ�е��ļ������ļ��е������ļ���·����
	CString FilePath = this->m_filepath.Left(this->m_filepath.ReverseFind('\\'));
	USES_CONVERSION;
	cv::String path = W2A(FilePath);
	glob(path, allFilePath, false);
	return TRUE;
}
