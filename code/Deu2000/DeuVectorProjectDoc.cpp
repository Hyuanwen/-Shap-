// DeuVectorProjectDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuVectorProjectDoc.h"

// CDeuVectorProjectDoc
IMPLEMENT_DYNCREATE(CDeuVectorProjectDoc, CDocument)
CDeuVectorProjectDoc::CDeuVectorProjectDoc()
{
}

BOOL CDeuVectorProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDeuVectorProjectDoc::~CDeuVectorProjectDoc()
{
}

BEGIN_MESSAGE_MAP(CDeuVectorProjectDoc, CDocument)
END_MESSAGE_MAP()

// CDeuVectorProjectDoc ���
#ifdef _DEBUG
void CDeuVectorProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDeuVectorProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDeuVectorProjectDoc ���л�

void CDeuVectorProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
#endif

// CDeuVectorProjectDoc ����
