// DeuRasterDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuRasterDoc.h"


// CDeuRasterDoc

IMPLEMENT_DYNCREATE(CDeuRasterDoc, CDocument)

CDeuRasterDoc::CDeuRasterDoc()
{
}

BOOL CDeuRasterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}


CDeuRasterDoc::~CDeuRasterDoc()
{
}


BEGIN_MESSAGE_MAP(CDeuRasterDoc, CDocument)
END_MESSAGE_MAP()


// CDeuRasterDoc ���

#ifdef _DEBUG
void CDeuRasterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDeuRasterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDeuRasterDoc ���л�

void CDeuRasterDoc::Serialize(CArchive& ar)
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


// CDeuRasterDoc ����
