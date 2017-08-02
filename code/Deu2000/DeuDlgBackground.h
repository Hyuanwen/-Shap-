#pragma once

#include "resource.h"
#include "AnimateStatic.h"

class CDeuDlgBackground : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgBackground)

public:
	CDeuDlgBackground(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgBackground();

	// �Ի�������
	enum { IDD = IDD_DLG_BACKGROUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CDeuAnimateStatic	m_staticGear;
};
