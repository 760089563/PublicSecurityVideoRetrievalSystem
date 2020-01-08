
// PublicSecurityVideoRetrievalSystemDoc.h : CPublicSecurityVideoRetrievalSystemDoc ��Ľӿ�
//
#include "opencv.hpp"

#pragma once
using namespace cv;
using namespace std;

class CPublicSecurityVideoRetrievalSystemDoc : public CDocument
{
protected: // �������л�����
	CPublicSecurityVideoRetrievalSystemDoc();
	DECLARE_DYNCREATE(CPublicSecurityVideoRetrievalSystemDoc)

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
	virtual ~CPublicSecurityVideoRetrievalSystemDoc();
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
	// �ڴ򿪴���ѡ�е��ļ���ȫ·��
	CString m_filepath;
	// �򿪴��ڵ��ļ����ڵ��ļ��������е�·��
	vector<String> allFilePath;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
