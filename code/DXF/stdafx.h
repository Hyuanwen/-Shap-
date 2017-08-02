// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#include "targetver.h"

// 从 Windows 头中排除极少使用的资料
#define WIN32_LEAN_AND_MEAN             
// Windows 头文件:
#include <windows.h>

// 某些 CString 构造函数将是显式的
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      
#include <atlbase.h>
#include <atlstr.h>

// TODO: 在此处引用程序需要的其他头文件
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
