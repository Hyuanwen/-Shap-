#pragma once
#include "afxcmn.h"
#include "DeuGlobal.h"

// CFileFormatSet �Ի���
class CFileFormatSet : public CDialog
{
	DECLARE_DYNAMIC(CFileFormatSet)

public:
	CFileFormatSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileFormatSet();

// �Ի�������
	enum { IDD = IDD_DLG_FROMATSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
