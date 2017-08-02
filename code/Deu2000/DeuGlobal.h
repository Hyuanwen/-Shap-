// Deu2000.h : Deu2000 应用程序的主头文件

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
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

	void OnNewView();	       //新视图
	void OnNewVector();        //新矢量
	void OnNewRaster();	       //新栅格
	void OnNewProject();       //新投影
	void OnNewVectorProject(); //矢量投影
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

/* 保存登录成功后的用户名 */
extern char p_cUserName[50];

/* 全局权限保存 */
void LoadPowerInfo(PUSERPOWER pUserInfo);

//保存任务
void SaveRunTask();
void SaveFormatXml();
void LoadFormatXml();
void ReleaseFormatXml(_StrFormatList& Tasks);
void LoadMapping();
void Init_Geodetic(p_GeodeticSeries pGeoDataXml);
void Init_Projected(p_ProjectedSeries pProjectedSeries);

/* 获取平面坐标结构 */
_ProjectedSeries* GetProjectedObject(CString m_strName);

/* 获得对应大地坐标对象结构 */
_GeodeticSeries* GetGeoDeticObject(CString m_strName);

void Release_GeoXml(p_GeoDataXml pGeoXml);

const char* newGUID();