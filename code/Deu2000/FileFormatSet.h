#pragma once
#include "afxcmn.h"
#include "DeuGlobal.h"

// CFileFormatSet 对话框
class CFileFormatSet : public CDialog
{
	DECLARE_DYNAMIC(CFileFormatSet)

public:
	CFileFormatSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileFormatSet();

// 对话框数据
	enum { IDD = IDD_DLG_FROMATSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchangeTabFromat(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();

private:
	void InitVectorList();
	void InitRasterList();

private:
	CTabCtrl								m_TabFormat;
	CListCtrl								m_ListVector;
	CListCtrl								m_ListRaster;
};
