// DeuVectorDoc.cpp : 实现文件
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

// CDeuVectorDoc 诊断
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
// CDeuVectorDoc 序列化

void CDeuVectorDoc::Serialize(CArchive& ar)
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
// CDeuVectorDoc 命令
