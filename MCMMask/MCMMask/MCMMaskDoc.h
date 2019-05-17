
// MCMMaskDoc.h : CMCMMaskDoc ��Ľӿ�
//


#pragma once
#include "opencv2/core.hpp"

class CMCMMaskDoc : public CDocument
{
protected: // �������л�����
	CMCMMaskDoc();
	DECLARE_DYNCREATE(CMCMMaskDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMCMMaskDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
    cv::Mat m_src;
//    afx_msg void OnFileOpen();
};
