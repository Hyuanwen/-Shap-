// Deu2000.h : Deu2000 Ӧ�ó������ͷ�ļ�

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       
#include "DeuDlgBackground.h"
#include "DeuTaskProcess.h"
#include "DeuFunction.h"
#include "DeuFLGrid.h"
#include "DeuXmlReader.h"
#include "DeuXmlWriter.h"
#include "DeuDlgGridSetting.h"
#include "FileFormatSet.h"

#import "../../dll/ado/msado15.dll" rename("EOF", "_EOF")

using namespace DeuXmlMapping;
using namespace ADODB;

class CDeuGlobalApp : public CWinApp
{
public:
	CDeuGlobalApp();
	virtual BOOL InitInstance();

	void OnNewView();	       //����ͼ
	void OnNewVector();        //��ʸ��
	void OnNewRaster();	       //��դ��
	void OnNewProject();       //��ͶӰ
	void OnNewVectorProject(); //ʸ��ͶӰ
	void OnGridSet();
	void OnFormatSet();
	virtual int ExitInstance();

	afx_msg void OnAppAbout();
	afx_msg void OnContextHelp();
	afx_msg void OnFlAdd();
	DECLARE_MESSAGE_MAP()

protected:
	CDeuDlgBackground m_BackDlg;

public:
	CDeuDlgGridSetting m_GridSettingDlg;

private:
	DeuFLGrid	m_FLGrid;
};

AFX_INLINE BOOL CreateImageList(CImageList& il, UINT nID)
{
	if (!il.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1))
	{
		return FALSE;
	}

	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(nID));
	il.Add(&bmp, CXTPImageManager::GetBitmapMaskColor(bmp, CPoint(0, 0)));

	return TRUE;
}

class CDeuCtrlTaskTree : public CXTPOfficeBorder<CTreeCtrl>
{
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
	{
		NMHDR* pNMHDR = (NMHDR*)lParam;
		switch (pNMHDR->code)
		{
		case TTN_SHOW:
			{
				HWND hWnd = TreeView_GetToolTips(m_hWnd);
				if (hWnd != NULL)
				{
					::SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
				}
			}
			break;
		}
		return CXTPOfficeBorder<CTreeCtrl>::OnNotify(wParam, lParam, pResult);
	}	
};

extern CDeuGlobalApp   theApp;
extern CDeuTaskProcess TaskProc;
extern _GeoDataXml     GeoDataMapping;
extern _GeoDataXml     CustDataMapping;
extern _Tasks          TasksMapping;
extern USERPOWER       GobalUserInfo;
extern _StrFormatList  GobalFormat;

/* �����¼�ɹ�����û��� */
extern char p_cUserName[50];

/* ȫ��Ȩ�ޱ��� */
void LoadPowerInfo(PUSERPOWER pUserInfo);

//��������
void SaveRunTask();
void SaveFormatXml();
void LoadFormatXml();
void ReleaseFormatXml(_StrFormatList& Tasks);
void LoadMapping();
void Init_Geodetic(p_GeodeticSeries pGeoDataXml);
void Init_Projected(p_ProjectedSeries pProjectedSeries);

/* ��ȡƽ������ṹ */
_ProjectedSeries* GetProjectedObject(CString m_strName);

/* ��ö�Ӧ����������ṹ */
_GeodeticSeries* GetGeoDeticObject(CString m_strName);

void Release_GeoXml(p_GeoDataXml pGeoXml);

const char* newGUID();