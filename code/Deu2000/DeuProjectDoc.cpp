// DeuRasterDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuProjectDoc.h"

IMPLEMENT_DYNCREATE(CDeuProjectDoc, CDocument)
CDeuProjectDoc::CDeuProjectDoc()
{
}

CDeuProjectDoc::~CDeuProjectDoc()
{
}

BOOL CDeuProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDeuProjectDoc, CDocument)
END_MESSAGE_MAP()

// CDeuProjectDoc ���
#ifdef _DEBUG
void CDeuProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDeuProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDeuProjectDoc ���л�

void CDeuProjectDoc::Serialize(CArchive& ar)
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
// CDeuProjectDoc ����
