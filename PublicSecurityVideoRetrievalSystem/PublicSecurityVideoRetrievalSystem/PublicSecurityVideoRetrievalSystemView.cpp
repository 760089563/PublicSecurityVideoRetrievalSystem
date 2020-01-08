
// PublicSecurityVideoRetrievalSystemView.cpp : CPublicSecurityVideoRetrievalSystemView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PublicSecurityVideoRetrievalSystem.h"
#endif

#include "PublicSecurityVideoRetrievalSystemDoc.h"
#include "PublicSecurityVideoRetrievalSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPublicSecurityVideoRetrievalSystemView

IMPLEMENT_DYNCREATE(CPublicSecurityVideoRetrievalSystemView, CView)

BEGIN_MESSAGE_MAP(CPublicSecurityVideoRetrievalSystemView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPublicSecurityVideoRetrievalSystemView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPublicSecurityVideoRetrievalSystemView ����/����

CPublicSecurityVideoRetrievalSystemView::CPublicSecurityVideoRetrievalSystemView()
{
	// TODO:  �ڴ˴���ӹ������

}

CPublicSecurityVideoRetrievalSystemView::~CPublicSecurityVideoRetrievalSystemView()
{
}

BOOL CPublicSecurityVideoRetrievalSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPublicSecurityVideoRetrievalSystemView ����

void CPublicSecurityVideoRetrievalSystemView::OnDraw(CDC* /*pDC*/)
{
	CPublicSecurityVideoRetrievalSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPublicSecurityVideoRetrievalSystemView ��ӡ


void CPublicSecurityVideoRetrievalSystemView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPublicSecurityVideoRetrievalSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPublicSecurityVideoRetrievalSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPublicSecurityVideoRetrievalSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CPublicSecurityVideoRetrievalSystemView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPublicSecurityVideoRetrievalSystemView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPublicSecurityVideoRetrievalSystemView ���

#ifdef _DEBUG
void CPublicSecurityVideoRetrievalSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CPublicSecurityVideoRetrievalSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPublicSecurityVideoRetrievalSystemDoc* CPublicSecurityVideoRetrievalSystemView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPublicSecurityVideoRetrievalSystemDoc)));
	return (CPublicSecurityVideoRetrievalSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CPublicSecurityVideoRetrievalSystemView ��Ϣ�������
