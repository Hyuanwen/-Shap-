// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#include "targetver.h"

// �� Windows ͷ���ų�����ʹ�õ�����
#define WIN32_LEAN_AND_MEAN             
// Windows ͷ�ļ�:
#include <windows.h>

// ĳЩ CString ���캯��������ʽ��
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      
#include <atlbase.h>
#include <atlstr.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "StringFunction.h"
#include "DeuDebug.h"
#include "avc.h"
#include "DxfProject.h"

#define  LOGSTR(s) \
{	\
	FILE   *_pfile=fopen("C:\\log.txt","a+");\
	char * strLog = s;\
	fwrite(strLog,strlen(strLog),1,_pfile);\
	fwrite("\r\n",2,1,_pfile);\
	fclose(_pfile);\
}

#define  LOG(strLog1,strLog2,n) \
{	\
	char *strlog=new char[1000];\
	memset(strlog,0,1000);\
	sprintf(strlog,"%s%s",strLog1,strLog2);\
	LOGSTR(strlog);\
	delete strlog;\
}
