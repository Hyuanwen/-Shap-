// ChildFrm.h : CChildFrame 类的接口
//

#pragma once
#include "DeuGlobalChildFrame.h"

class CDeuViewerFrame : public CDeuGlobalChildFrame
{
	DECLARE_DYNCREATE(CDeuViewerFrame)
public:
	CDeuViewerFrame();
	virtual ~CDeuViewerFrame();

// 操作
public:
	// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};
