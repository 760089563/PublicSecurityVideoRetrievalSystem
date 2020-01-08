
// PublicSecurityVideoRetrievalSystemView.cpp : CPublicSecurityVideoRetrievalSystemView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPublicSecurityVideoRetrievalSystemView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPublicSecurityVideoRetrievalSystemView 构造/析构

CPublicSecurityVideoRetrievalSystemView::CPublicSecurityVideoRetrievalSystemView()
{
	// TODO:  在此处添加构造代码

}

CPublicSecurityVideoRetrievalSystemView::~CPublicSecurityVideoRetrievalSystemView()
{
}

BOOL CPublicSecurityVideoRetrievalSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPublicSecurityVideoRetrievalSystemView 绘制

void CPublicSecurityVideoRetrievalSystemView::OnDraw(CDC* /*pDC*/)
{
	CPublicSecurityVideoRetrievalSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CPublicSecurityVideoRetrievalSystemView 打印


void CPublicSecurityVideoRetrievalSystemView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPublicSecurityVideoRetrievalSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPublicSecurityVideoRetrievalSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CPublicSecurityVideoRetrievalSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CPublicSecurityVideoRetrievalSystemView 诊断

#ifdef _DEBUG
void CPublicSecurityVideoRetrievalSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CPublicSecurityVideoRetrievalSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPublicSecurityVideoRetrievalSystemDoc* CPublicSecurityVideoRetrievalSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPublicSecurityVideoRetrievalSystemDoc)));
	return (CPublicSecurityVideoRetrievalSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CPublicSecurityVideoRetrievalSystemView 消息处理程序
