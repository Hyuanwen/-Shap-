// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

//#include <windows.h>
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类
#include <afxcview.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <OleAcc.h>
using namespace std;
#include <afxdlgs.h>
#include <vector>
//#include <string>
#include <map>
#include <list>
#include <limits>
#include <algorithm>

#include "XTToolkitPro.h"


/* 全局公共数据 */
#include "DeuGlobalParam.h"
//using namespace XTPREPORTADODB;
#include "DeuUserDefineObject.h"
#include "DeuDlgExcel.h"

#include "GridCtrl.h"
#include "tppubbas.h"

#include<iostream> 
#include<fstream>
#include<sstream>

#include "DeuTranslate.h"
#include "DeuEllipList.h"
#include "EllipManager.h"
#include "DeuEllipList.h"
#include "DeuDlgEllipManager.h"

#define DEULIC		//授权验证
#define ARCSDE		//支持ArcSDE转换
#ifdef ARCSDE
	#define ARCGIS_VERSION 10.0
	#define ESRI_WINDOWS			
	#define ESRI_QUICK

	#include "ArcSDEDefine.h"
	#include "ArcGISAuthorization.h"
	#include "ArcSDEConnection.h"
	#include "DeuSDEConnectProperty.h"
	#include "ArcSDERaster.h"
	#include "ArcSDeVector.h"
	#include "SdeSelect.h"
	#include "ArcGDBTest.h"
#endif


#include "TinyXml/tinyxml.h"

//add by chenyong 2014-3-25
#include "ComLib.h"

//#import "C:\Program Files (x86)\Common Files\Microsoft Shared\OFFICE12\mso.dll" rename("RGB", "MSRGB"), rename("IAccessible", "IExcelAccessible")
//#import "C:\Program Files (x86)\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB" raw_interfaces_only, \
//	rename("Reference", "ignorethis"), rename("VBE", "JOEVBE")
//#import "D:\install\office 2007\Office12\excel.exe" exclude("IFont", "IPicture") \
//	rename("RGB", "ignorethis"), rename("DialogBox", "ignorethis"), rename("VBE", "JOEVBE"), \
//	rename("ReplaceText", "JOEReplaceText"), rename("CopyFile","JOECopyFile"), \
//	rename("FindText", "JOEFindText"), rename("NoPrompt", "JOENoPrompt"), rename("IPoint", "excelIPoint")
//
//using namespace Office;
//using namespace VBIDE;
//using namespace Excel;

#define  LOGSTR(s) \
{	\
	FILE   *_pfile=fopen("C:\\log.txt","a+");\
	char * strLog = s;\
	fwrite(strLog,strlen(strLog),1,_pfile);\
	fwrite("\r\n",2,1,_pfile);\
	fclose(_pfile);\
}

#define LOG_START \
{char *start_t=(char*)malloc(100);\
	SYSTEMTIME sys; \
	GetLocalTime( &sys ); \
	char * shour = (char *)malloc(20);\
	itoa(sys.wHour,shour,10);\
	\
	char * sMinute = (char *)malloc(20);\
	itoa(sys.wMinute,sMinute,10);\
	\
	char * sSecond = (char *)malloc(20);\
	itoa(sys.wSecond,sSecond,10);\
	\
	strcpy(start_t,shour);\
	strcat(start_t,":");\
	strcat(start_t,sMinute);\
	strcat(start_t,":");\
	strcat(start_t,sSecond); \
	LOG("开始转换时间:",start_t,strlen("开始转换时间:")+ 100); \
	free(shour);\
	free(sMinute);\
	free(sSecond);\
	free(start_t);}

#define LOG_END \
{char *end_t=(char*)malloc(100);\
	SYSTEMTIME sys; \
	GetLocalTime( &sys ); \
	char * shour = (char *)malloc(20);\
	itoa(sys.wHour,shour,10);\
	\
	char * sMinute = (char *)malloc(20);\
	itoa(sys.wMinute,sMinute,10);\
	\
	char * sSecond = (char *)malloc(20);\
	itoa(sys.wSecond,sSecond,10);\
	\
	strcpy(end_t,shour);\
	strcat(end_t,":");\
	strcat(end_t,sMinute);\
	strcat(end_t,":");\
	strcat(end_t,sSecond); \
	LOG("结束转换时间:",end_t,100); \
	free(end_t);}

#define  LOG(strLog1,strLog2,n) \
	{\
	char *strlog=new char[1000];\
	memset(strlog,0,1000);\
	sprintf(strlog,"%s%s",strLog1,strLog2);\
	LOGSTR(strlog);\
	delete[] strlog;\
	}

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#pragma warning(disable : 4244)
#pragma warning(disable : 4018)
#pragma warning(disable : 4996)
#pragma warning(disable : 4482)
#pragma warning(disable : 4067)
