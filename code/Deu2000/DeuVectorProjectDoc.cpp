// DeuVectorProjectDoc.cpp : 实现文件
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

// CDeuVectorProjectDoc 诊断
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
// CDeuVectorProjectDoc 序列化

void CDeuVectorProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}
#endif

// CDeuVectorProjectDoc 命令
