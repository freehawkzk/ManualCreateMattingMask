
// MCMMaskView.cpp : CMCMMaskView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMCMMaskView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_CREATE()
END_MESSAGE_MAP()

// CMCMMaskView ����/����

CMCMMaskView::CMCMMaskView()
{
	// TODO: �ڴ˴���ӹ������

}

CMCMMaskView::~CMCMMaskView()
{
}

BOOL CMCMMaskView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMCMMaskView ����

void CMCMMaskView::OnDraw(CDC* /*pDC*/)
{
	CMCMMaskDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CMCMMaskView ��ӡ


void CMCMMaskView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMCMMaskView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMCMMaskView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMCMMaskView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CMCMMaskView ���

#ifdef _DEBUG
void CMCMMaskView::AssertValid() const
{
	CView::AssertValid();
}

void CMCMMaskView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMCMMaskDoc* CMCMMaskView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMCMMaskDoc)));
	return (CMCMMaskDoc*)m_pDocument;
}
#endif //_DEBUG


// CMCMMaskView ��Ϣ�������


int CMCMMaskView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������
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
