 // DeuDlgBackground.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuDlgBackground.h"

// CDeuDlgBackground �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgBackground, CDialog)

CDeuDlgBackground::CDeuDlgBackground(CWnd* pParent /*=NULL*/)
				 : CDialog(CDeuDlgBackground::IDD, pParent)
{
}

CDeuDlgBackground::~CDeuDlgBackground()
{
}

void CDeuDlgBackground::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAPPIC, m_staticGear);
}

BEGIN_MESSAGE_MAP(CDeuDlgBackground, CDialog)
END_MESSAGE_MAP()

// CDeuDlgBackground ��Ϣ�������
BOOL CDeuDlgBackground::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set animation properties
	m_staticGear.SetAnimationDelay(0);
	m_staticGear.SetAnimationType(6);
	m_staticGear.SetAnimationSteps(0);

	// draw animation
	m_staticGear.Animate();
	
	return TRUE;
}
