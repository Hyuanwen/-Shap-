// Deu2000Doc.h : CDeuViewerDoc ��Ľӿ�
//

#pragma once

class CDeuViewerDoc : public CDocument
{
protected: // �������л�����
	CDeuViewerDoc();
	DECLARE_DYNCREATE(CDeuViewerDoc)
	CSize           m_sizeDoc;

// ����
public:
	CSize GetDocSize() { return m_sizeDoc; }

// ��д
public:     
	void InitDocument();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CDeuViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};


