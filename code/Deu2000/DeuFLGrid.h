#pragma once

#include <afx.h>

// DeuFLGrid �Ի���
class DeuFLGrid : public CDialog
{
	DECLARE_DYNAMIC(DeuFLGrid)

public:
	DeuFLGrid(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DeuFLGrid();

	// �Ի�������
	enum { IDD = IDD_DLG_FL_GRID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedButtonBr();
	afx_msg void OnBnClickedButtonBrc();
	afx_msg void OnclickFOK();
	DECLARE_MESSAGE_MAP()
	
private:
	CString									m_EditPath;
	CString									m_EditPathc;
	CString									m_EditSetPd;
	CString									strFileName;
	CString									strFileNamec;
	CFileFind								finder;
	CString									strExtName;
	CString									strPathName;
	CString									strTmpPathName;
};
