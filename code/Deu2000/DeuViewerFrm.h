// ChildFrm.h : CChildFrame ��Ľӿ�
//

#pragma once
#include "DeuGlobalChildFrame.h"

class CDeuViewerFrame : public CDeuGlobalChildFrame
{
	DECLARE_DYNCREATE(CDeuViewerFrame)
public:
	CDeuViewerFrame();
	virtual ~CDeuViewerFrame();

// ����
public:
	// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};
