// Deu2000Doc.h : CDeuViewerDoc 类的接口
//

#pragma once

class CDeuViewerDoc : public CDocument
{
protected: // 仅从序列化创建
	CDeuViewerDoc();
	DECLARE_DYNCREATE(CDeuViewerDoc)
	CSize           m_sizeDoc;

// 操作
public:
	CSize GetDocSize() { return m_sizeDoc; }

// 重写
public:     
	void InitDocument();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CDeuViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};


