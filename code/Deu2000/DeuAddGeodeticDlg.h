#pragma once

#include "resource.h"
#include "afxwin.h"
// CDeuAddGeodeticDlg 对话框

class CDeuAddGeodeticDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeuAddGeodeticDlg)

public:
	CDeuAddGeodeticDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuAddGeodeticDlg();

// 对话框数据
	enum { IDD = IDD_DLG_ADD_GEODETIC };

public: 
	double m_pdA[4];
	double m_pdB[4];
	double m_pdK[4];

	void SetRSR(CString szFilePath);
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CComboBox m_ctlComEllipsodi;
	double m_dA;
	double m_dB;
	double m_dK;
	afx_msg void OnCbnSelchangeComboEllipsoidName();
	afx_msg void OnCbnSelchangeCombounit();
	CComboBox m_ctlComUnit;
	double m_dUnitData;
	CString m_szName;
	CEdit m_ctlA;
	CEdit m_ctlB;
	CEdit m_ctlK;
	CEdit m_ctlUnitData;
//	afx_msg void OnCbnEditchangeComboEllipsoidName();
	afx_msg void OnCbnEditupdateComboEllipsoidName();
	afx_msg void OnCbnEditchangeComboEllipsoidName();
};
