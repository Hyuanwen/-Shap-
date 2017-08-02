#pragma once

#include "resource.h"
#include "DeuGlobalParam.h"
#include <list>

#define CDialogSampleDlgBase CXTPDialogBase<CXTResizeDialog>
class CDeuDlgDataSrc : public CDialogSampleDlgBase
{
	DECLARE_DYNAMIC(CDeuDlgDataSrc)

public:
	CDeuDlgDataSrc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgDataSrc();

// 对话框数据
	enum { IDD = IDD_DLG_SOURCE };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnNMDblclkListUroleSrc(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListUroleSrc(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl     m_Listctrl;
	CTreeCtrl     m_Treectrl;
	CXTPStatusBar m_wndStatusBar;
	CMenu		  m_menu;
	CString       m_strSelectItem;
	
protected:
	//定义各个ListCtrl的列
	void InitListCtrl(CoordinateType _CoodinateType);

	//填充数据到列表
	void FillListCtrl(CoordinateType _CoodinateType);

	void LoadGeodeticPeking54Data();
	void LoadGeodeticXiAn80Data();
	void LoadGeodeticWGS84Data();
	void LoadGeodeticCGCS2000Data();

	void LoadSelectedPorjected(CString strGeoDetic);
	void LoadAllPorjected();
	void OnShowDetail();
	void RefreshTreeCtrl();

	typedef list<HTREEITEM>           TreeList;
	typedef list<HTREEITEM>::iterator TreeListIt;
	TreeList						  m_treelist;
	TreeListIt                        m_treelistIt;
	HTREEITEM 						  hTreeRoot;
	HTREEITEM 						  hTreeGeoDetic;
	HTREEITEM 						  hTreeProjected;
	HTREEITEM 					      hTreeHandle;
};
