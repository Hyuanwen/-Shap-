// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

//#include <windows.h>
#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����
#include <afxcview.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
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


/* ȫ�ֹ������� */
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

#define DEULIC		//��Ȩ��֤
#define ARCSDE		//֧��ArcSDEת��
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
	LOG("��ʼת��ʱ��:",start_t,strlen("��ʼת��ʱ��:")+ 100); \
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
	LOG("����ת��ʱ��:",end_t,100); \
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
