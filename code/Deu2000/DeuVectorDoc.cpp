// DeuVectorDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuVectorDoc.h"

// CDeuVectorDoc
IMPLEMENT_DYNCREATE(CDeuVectorDoc, CDocument)
CDeuVectorDoc::CDeuVectorDoc()
{
}

BOOL CDeuVectorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDeuVectorDoc::~CDeuVectorDoc()
{
}

BEGIN_MESSAGE_MAP(CDeuVectorDoc, CDocument)
END_MESSAGE_MAP()

// CDeuVectorDoc ���
#ifdef _DEBUG
void CDeuVectorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDeuVectorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDeuVectorDoc ���л�

void CDeuVectorDoc::Serialize(CArchive& ar)
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
// CDeuVectorDoc ����
