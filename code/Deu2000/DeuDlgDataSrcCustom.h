#pragma once

#include "resource.h"
#include "DeuGlobal.h"
#include "DeuDlgDataSrcCustomDetail.h"

class CDeuDlgDataSrcCustom : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDeuDlgDataSrcCustom)

public:
	CDeuDlgDataSrcCustom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgDataSrcCustom();
 
	// 对话框数据
	enum { IDD = IDD_DLG_SOURCE_CUSTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
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
	void OnModifyGeoDetic();
	void OnModifyProjected();

	void CreateGeoDetic();
	void CreateProjected();
	void RefreshTreeCtrl();

public:
	CDeuXmlReader m_rCustDataXml;
	CDeuXmlWriter m_wCustDataXml;
	CListCtrl     m_Listctrl;
	CTreeCtrl     m_Treectrl;

	HTREEITEM     hTreeRoot;
	HTREEITEM     hTreeGeoDetic;
	HTREEITEM     hTreeProjected;
	HTREEITEM     hTreeHandle;

	CMenu         m_menu;
};
