/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     作者：	hushichen
//     描述:	Tab容器
//     版本:v1.0
//
//		CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////
#pragma once

#include "Resource.h"
#include "deuctrltab.h"

#include "DeuData.h"


class CDeuDlgContainer : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDeuDlgContainer)

public:
	CDeuDlgContainer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgContainer();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDeuCtrlTab m_DeuTab;
	virtual BOOL OnInitDialog();

	afx_msg void OnSize(UINT nType, int cx, int cy);


	void InitExistTask();


	//增加tab组函数

	/* 单转 */
	void AddTabForSingle();
	void DelTabForSingle(int _Index);

	/* 批转 */
	void AddTabForBatRechange();
	void DelTabForBatRechange(int _Index);


	/* 视图 */
	void AddTabForView();
	void DelTabForView(int _Index);


	/* 矢量 */
	void AddTabForVector(TreeData* p_treedata);
	void DelTabForVector(int _Index);

	//更新在tab子窗口的全局索引值
	void ResetTabOrder();

	//更新矢量容器中子窗口的容器索引值
	void ResetVectorAyOrder();

	//更新栅格容器中子窗口的容器索引值
	void ResetRasterAyOrder();
	

	/* 栅格 */
	void AddTabForRaster(TreeData* p_treedata);
	void DelTabForRaster(int _Index);

	//一不做，二不休，重新加载控件树的数据
	void ResetTree();

	

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
