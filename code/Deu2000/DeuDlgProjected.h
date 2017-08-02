#pragma once

#include "resource.h"

class CDeuDlgProjected : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgProjected)

public:
	CDeuDlgProjected(BOOL _IsModify=FALSE, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgProjected();

	// 对话框数据
	enum { IDD = IDD_DLG_PROJECTED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_combox;
	CEdit m_Edit_Name;
	CEdit m_Edit_ENVELOPE_NAME;
	CEdit m_Edit_ENVELOPE_MIN_LONG;
	CEdit m_Edit_ENVELOPE_MIN_FLAT;
	CEdit m_Edit_ENVELOPE_MAX_LONG;
	CEdit m_Edit_ENVELOPE_MAX_FLAT;
	CEdit m_Edit_CM;
	CEdit m_Edit_FE;

	CString m_strName;
	CString m_strEnvelopeName;
	CString m_strEnvelopeMinLong;
	CString m_strEnvelopeMinFlat;
	CString m_strEnvelopeMaxLong;
	CString m_strEnvelopeMaxFlat;
	CString m_CM;
	CString m_FE;
	CString m_GeoDetic;

	BOOL IsModify;
	CString m_strCoordName;
};
