
// MCMMaskView.cpp : CMCMMaskView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MCMMask.h"
#endif

#include "MCMMaskDoc.h"
#include "MCMMaskView.h"


#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui_c.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMCMMaskView

IMPLEMENT_DYNCREATE(CMCMMaskView, CView)

BEGIN_MESSAGE_MAP(CMCMMaskView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMCMMaskView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_CREATE()
END_MESSAGE_MAP()

// CMCMMaskView 构造/析构

CMCMMaskView::CMCMMaskView()
{
	// TODO: 在此处添加构造代码

}

CMCMMaskView::~CMCMMaskView()
{
}

BOOL CMCMMaskView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMCMMaskView 绘制

void CMCMMaskView::OnDraw(CDC* /*pDC*/)
{
	CMCMMaskDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
    if (!pDoc->m_src.empty())
    {
        RECT rt;
        GetClientRect(&rt);
        int width = rt.right - rt.left;
        int height = rt.bottom - rt.top;
        cv::resize(pDoc->m_src, pDoc->m_src, cv::Size(width, height));
        cv::imshow(m_cwndName, pDoc->m_src);
    }
}


// CMCMMaskView 打印


void CMCMMaskView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMCMMaskView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMCMMaskView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMCMMaskView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMCMMaskView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMCMMaskView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMCMMaskView 诊断

#ifdef _DEBUG
void CMCMMaskView::AssertValid() const
{
	CView::AssertValid();
}

void CMCMMaskView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMCMMaskDoc* CMCMMaskView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMCMMaskDoc)));
	return (CMCMMaskDoc*)m_pDocument;
}
#endif //_DEBUG


// CMCMMaskView 消息处理程序


int CMCMMaskView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    //pic = string(name);
    cv::namedWindow(m_cwndName.c_str(), 1);
    HWND hWnd = (HWND)cvGetWindowHandle(m_cwndName.c_str());
    HWND hParent = ::GetParent(hWnd);
    ::SetParent(hWnd, this->m_hWnd);
    ::ShowWindow(hParent, SW_HIDE);
    
    CMCMMaskDoc* pDoc = GetDocument();
    pDoc->m_src = cv::imread("1.png");
    pDoc->m_mask = cv::Mat::zeros(pDoc->m_src.rows, pDoc->m_src.cols, CV_8UC1);

    cv::transpose(pDoc->m_src, pDoc->m_src);
    cv::transpose(pDoc->m_mask, pDoc->m_mask);
    
    Invalidate();
    return 0;
}
