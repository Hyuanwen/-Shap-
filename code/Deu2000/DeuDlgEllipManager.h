#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define EllipseName "EllipseName"

// CDeuDlgEllipManager 对话框
class CDeuDlgEllipManager : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgEllipManager)

public:
	CDeuDlgEllipManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgEllipManager();

// 对话框数据
	enum { IDD = IDD_DLG_ELLIP_MANAGER };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedBtnFile();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTvnItemexpandingTreeEllip(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

private:
	HRESULT GetXmlPath(std::string * pstrPath);
	HRESULT GreateXmlForSys(std::string strFilePath);  //创建一个用来记录已选择坐标系信息的xml文件
	HRESULT InsertRecordToXml(std::string strPath, std::string strChoice); //插入一个值
	HRESULT DispChoiceByXml();

	HRESULT GetEllipPath(std::string * pEllipPath);
	HRESULT GetItemPath(const HTREEITEM hSelected, std::string * pFilePath);

	HRESULT	ApendNullNode(HTREEITEM hParentItem);
	HRESULT ApendNode(HTREEITEM hParentItem, std::string NodeName);
	HRESULT DelItemByParent(HTREEITEM hParentItem);

public:
	CString        m_strEllipName;
	CListCtrl      m_List;
	CTreeCtrl      m_ViewTree;
	BOOL           m_bManager;

protected:
	std::string   m_EllipPath;
public:
	afx_msg void OnBnClickedButtonGeographic();
	afx_msg void OnBnClickedButtonProjected();
	CButton m_ctlGeographic;
	CButton m_ctlProjected;
	afx_msg void OnNMRClickTreeEllip(NMHDR *pNMHDR, LRESULT *pResult);
};
