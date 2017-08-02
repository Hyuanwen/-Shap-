/////////////////////////////////////////////////////////////////////
//
//     项目: 德毅智慧转换软件
//
//     作者：   hushichen
//
//     描述:	任务浮动面板类
//
//     版本:	V1.0
//	   CopyRight 2010-2011 ljdy Corporation All Rights Reserved
//
/////////////////////////////////////////////////////////////////////
#pragma once

#include "DeuGlobal.h"

class CDeuPanelTask : public CWnd
{
	DECLARE_DYNAMIC(CDeuPanelTask)

public:
	CDeuCtrlTaskTree m_wndSolutionView;
	CImageList       m_ilSolutionView;
	CDeuPanelTask();
	virtual ~CDeuPanelTask();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	LRESULT OnInsertVectorNode(WPARAM wParam, LPARAM lParam);
	LRESULT OnInsertRasterNode(WPARAM wParam, LPARAM lParam);

protected:
	HTREEITEM htiParent;
	HTREEITEM htiVector, htiRaster;
	int nVecIndex, nRasterIndex;

public:
	void OnDeleteNode(TranformType _TranType, int nIndex);
	void KeepIndex(TranformType _TranType);

};


