#pragma once

#include "resource.h"
#include "DeuGlobal.h"
#include "DeuDlgDataSrcCustomDetail.h"

class CDeuDlgDataSrcCustom : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDeuDlgDataSrcCustom)

public:
	CDeuDlgDataSrcCustom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgDataSrcCustom();
 
	// �Ի�������
	enum { IDD = IDD_DLG_SOURCE_CUSTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
	//�������ListCtrl����
	void InitListCtrl(CoordinateType _CoodinateType);

	//������ݵ��б�
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
