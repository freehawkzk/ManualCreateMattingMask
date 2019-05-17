
// MCMMaskView.h : CMCMMaskView ��Ľӿ�
//

#pragma once
#include "opencv2/opencv.hpp"
#include <string>
class CMCMMaskView : public CView
{
protected: // �������л�����
	CMCMMaskView();
	DECLARE_DYNCREATE(CMCMMaskView)

// ����
public:
	CMCMMaskDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMCMMaskView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);


public:
    cv::Mat m_src;
    const std::string m_cwndName = "wnd";
};

#ifndef _DEBUG  // MCMMaskView.cpp �еĵ��԰汾
inline CMCMMaskDoc* CMCMMaskView::GetDocument() const
   { return reinterpret_cast<CMCMMaskDoc*>(m_pDocument); }
#endif

