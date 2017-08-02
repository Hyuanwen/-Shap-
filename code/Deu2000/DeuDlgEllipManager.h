#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define EllipseName "EllipseName"

// CDeuDlgEllipManager �Ի���
class CDeuDlgEllipManager : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgEllipManager)

public:
	CDeuDlgEllipManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgEllipManager();

// �Ի�������
	enum { IDD = IDD_DLG_ELLIP_MANAGER };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedBtnFile();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTvnItemexpandingTreeEllip(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

private:
	HRESULT GetXmlPath(std::string * pstrPath);
	HRESULT GreateXmlForSys(std::string strFilePath);  //����һ��������¼��ѡ������ϵ��Ϣ��xml�ļ�
	HRESULT InsertRecordToXml(std::string strPath, std::string strChoice); //����һ��ֵ
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
