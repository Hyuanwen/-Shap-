// DeuRasterDoc.cpp : 实现文件
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

// CDeuProjectDoc 诊断
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
// CDeuProjectDoc 序列化

void CDeuProjectDoc::Serialize(CArchive& ar)
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
// CDeuProjectDoc 命令
