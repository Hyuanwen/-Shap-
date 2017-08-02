// Deu2000Doc.cpp : CDeuViewerDoc ���ʵ��
//

#include "stdafx.h"
#include "DeuGlobal.h"
#include "DeuViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDeuViewerDoc
IMPLEMENT_DYNCREATE(CDeuViewerDoc, CDocument)
BEGIN_MESSAGE_MAP(CDeuViewerDoc, CDocument)
END_MESSAGE_MAP()

// CDeuViewerDoc ����/����
CDeuViewerDoc::CDeuViewerDoc()
{
	// TODO: �ڴ����һ���Թ������
	//EnableCompoundFile();

	m_sizeDoc = CSize(450, 450);
}

CDeuViewerDoc::~CDeuViewerDoc()
{
}

BOOL CDeuViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitDocument();

	return TRUE;
}

void CDeuViewerDoc::InitDocument()
{
	// default document size is 2 x 2 inches
	m_sizeDoc = CSize(450,450);
}

// CDeuViewerDoc ���л�
void CDeuViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_sizeDoc;
	}
	else
	{
		ar >> m_sizeDoc;
	}
}

// CDeuViewerDoc ���
#ifdef _DEBUG
void CDeuViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDeuViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CDeuViewerDoc ����
BOOL CDeuViewerDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	InitDocument();

	return TRUE;
}
