// DeuRasterDoc.cpp : 实现文件
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


// CDeuRasterDoc 诊断

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
// CDeuRasterDoc 序列化

void CDeuRasterDoc::Serialize(CArchive& ar)
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


// CDeuRasterDoc 命令
