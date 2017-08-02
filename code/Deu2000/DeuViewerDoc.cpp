// Deu2000Doc.cpp : CDeuViewerDoc 类的实现
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

// CDeuViewerDoc 构造/析构
CDeuViewerDoc::CDeuViewerDoc()
{
	// TODO: 在此添加一次性构造代码
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

// CDeuViewerDoc 序列化
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

// CDeuViewerDoc 诊断
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

// CDeuViewerDoc 命令
BOOL CDeuViewerDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	InitDocument();

	return TRUE;
}
