// DeuCtrlButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Deu2000.h"
#include "DeuCtrlButton.h"


// CDeuCtrlButton

IMPLEMENT_DYNAMIC(CDeuCtrlButton, CBCGPButton)

CDeuCtrlButton::CDeuCtrlButton(CDeuCtrlTab *p_tabctrl):p_mTabctrl(p_tabctrl)
{
	 this->m_bTransparent = FALSE;
}

CDeuCtrlButton::~CDeuCtrlButton()
{
}


BEGIN_MESSAGE_MAP(CDeuCtrlButton, CBCGPButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CDeuCtrlButton::OnBnClicked)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CDeuCtrlButton 消息处理程序
void CDeuCtrlButton::OnBnClicked()
{	
	char sz[10];
	itoa(index, sz,10);
	
	p_mTabctrl->DeleteFlags(index);

	/*if(MessageBox(sz, NULL, MB_OKCANCEL|MB_ICONEXCLAMATION) == IDOK)
	{
		
	}*/

}

void CDeuCtrlButton::OnPaint()
{
	CPaintDC dc(this);
	
	this->GetClientRect(&m_rect);
	dc.DrawText("×", m_rect, 1);

	CDC MemDc;
	MemDc.CreateCompatibleDC(&dc);
	
	CBitmap m_bitmap, *m_oldbitmap;
	m_bitmap.LoadBitmap(IDB_CROSS);

	BITMAP bitamp;
	m_bitmap.GetBitmap(&bitamp);

	m_oldbitmap = MemDc.SelectObject(&m_bitmap);

	dc.StretchBlt(0,0, m_rect.Width(), m_rect.Height(), &MemDc, 0, 0, bitamp.bmWidth, bitamp.bmHeight, SRCCOPY);
	
	dc.SelectObject(m_oldbitmap);
}

