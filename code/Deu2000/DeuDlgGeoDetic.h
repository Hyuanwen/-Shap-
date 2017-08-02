#pragma once

#include "resource.h"

class CDeuDlgGeoDetic : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgGeoDetic)

public:
	CDeuDlgGeoDetic(BOOL _IsModify=FALSE, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgGeoDetic();

	// 对话框数据
	enum { IDD = IDD_DLG_GEODETIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	DECLARE_MESSAGE_MAP()

	CEdit m_Edit_Name;
	CEdit m_Edit_EnvelopeName;
	CEdit m_Edit_EnvelopeMinLong;
	CEdit m_Edit_EnvelopeMinFlat;
	CEdit m_Edit_EnvelopeMaxLong;
	CEdit m_Edit_EnvelopeMaxFlat;

	CEdit m_Edit_EllipsoidName;
	CEdit m_Edit_EllipsoidLong;
	CEdit m_Edit_EllipsoidFlat;
	CEdit m_Edit_EllipsoidPianXin;
	BOOL  IsModify;

public:
	CString m_strName;
	CString m_strEnvelopeName;
	CString m_strEnvelopeMinLong;
	CString m_strEnvelopeMinFlat;
	CString m_strEnvelopeMaxLong;
	CString m_strEnvelopeMaxFlat;

	CString m_strEllipsoidName;
	CString m_strEllipsoidLong;
	CString m_strEllipsoidFlat;
	CString m_strEllipsoidPianXin;
	CString m_strCoordName;
};
