
// CP_GraphView.cpp: CCPGraphView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CP_Graph.h"
#endif

#include "CP_GraphDoc.h"
#include "CP_GraphView.h"
#include "CP_Pentagram2D.h"

#include "CP_Circle2D.h"
#include "CP_Rectangle2D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCPGraphView

IMPLEMENT_DYNCREATE(CCPGraphView, CView)

BEGIN_MESSAGE_MAP(CCPGraphView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCPGraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCPGraphView 构造/析构

CCPGraphView::CCPGraphView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCPGraphView::~CCPGraphView()
{
}

BOOL CCPGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCPGraphView 绘图
#include <cstdlib>
#include <ctime>
void CCPGraphView::OnDraw(CDC* pDC)
{
	CCPGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CP_Rectangle2D stripeBlue(0, 0, 144 * 4, 12 * 4);
	gb_brushRectangle(pDC, stripeBlue, 0xA24F02); // 绘制最上面的蓝条
	stripeBlue.gb_moveRectangle(0, 60 * 4);
	gb_brushRectangle(pDC, stripeBlue, 0xA24F02); // 绘制最下面的蓝条

	CP_Rectangle2D stripeWhite(0, 12 * 4, 144 * 4, 2 * 4);
	gb_brushRectangle(pDC, stripeWhite, 0xFFFFFF); // 绘制上面的白条
	stripeWhite.gb_moveRectangle(0, 46 * 4);
	gb_brushRectangle(pDC, stripeWhite, 0xFFFFFF); // 绘制下面的白条

	CP_Rectangle2D stripeRed(0, 14 * 4, 144 * 4, 44 * 4);
	gb_brushRectangle(pDC, stripeRed, 0x271CED); // 绘制中间的红条

	CP_Circle2D circleWhite(48 * 4, 36 * 4, 16 * 4);
	gb_brushCircle(pDC, circleWhite, 0xFFFFFF); // 绘制中间的白圆

	CP_Pentagram2D pentagramRed(48 * 4, 36 * 4, 31 * 4 / 2, 0);
	gb_brushPentagram(pDC, pentagramRed, 0x271CED); // 绘制中间的红五角星

	CP_Rectangle2D frame(0, 0, 144 * 4, 72 * 4);
	gb_drawRectangle(pDC, frame, 0x000000);
	
	// TODO: 在此处为本机数据添加绘制代码
}


// CCPGraphView 打印


void CCPGraphView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCPGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCPGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCPGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CCPGraphView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCPGraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCPGraphView 诊断

#ifdef _DEBUG
void CCPGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CCPGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCPGraphDoc* CCPGraphView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCPGraphDoc)));
	return (CCPGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CCPGraphView 消息处理程序
