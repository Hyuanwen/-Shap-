// DXF.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "DXF.h"
#include "DxfParse.h"
#include "EooParse.h"
#include "CoverageParse.h"
#include <sys/stat.h>

TransFun p_transform ;
DXF_API  DeuProgress* g_pProgress;

const char * g_FileIn ;
const char * g_FileOut;
long		 g_InLength = 0;
long		 g_OutLength = 0;
HWND		 m_hwnd;

long get_filesize(const char *filename)
{
    struct stat f_stat;
    if (stat(filename, &f_stat) == -1) 
	{
        return -1;
    }
    return (long)f_stat.st_size;	//返回文件字节数

	/*
		说明：
			1. 使用stat结构体时，需要包含头文件			
				#include <sys/types.h>
				#include <sys/stat.h>
			2. stat原型为：
				int stat(const char* filename, struct stat* buf);
			3. stat结构如下：
				
				struct stat
				{
					dev_t		st_dev;			--文件所在设备的ID
					ino_t		st_ino;			--节点号
					mode_t		st_mode;		--保护模式
					nlink_t		st_nlink;		--链向此文件的连接数
					uid_t		st_nid;			--用户id
					gid_t		st_gid;			--组id
					dev_t		st_rdev;		--设备号，针对设备文件
					off_t		st_size;		--文件大小，字节为单位
					blksize_t	st_blksize;		--系统块的大小
					blkcnt_t	st_blocks;		--文件所点块数
					time_t		st_atime;		--最近存取时间
					time_t		st_mtime;		--最近修改时间
					time_t		st_ctime;		--最后修改时间
				}
	*/

}

void  InvokeProgressFun()
{
	g_InLength = get_filesize( g_FileIn );
	g_OutLength = get_filesize( g_FileOut );
	::SendMessage(m_hwnd,0x0500,0,(double)g_OutLength * 100.0 / (double) g_InLength);
	//g_pProgress->_Progress( (double)g_OutLength * 100.0 / (double) g_InLength ,"" ,(void*) g_pProgress->hwnd );
}

DXF_API int DXFTransform( const char * FileIn, const char * FileOut, void * transfun, HWND m_phwnd )
{
	g_FileIn  = FileIn;
	g_FileOut = FileOut;
	m_hwnd    = m_phwnd;

	//显示进度条
	//InvokeProgressFun();
//	::SendMessage(m_hwnd,0x0500,0,(double)0.0);

	//转换函数
	p_transform = ( TransFun )transfun ;

	string        strLine;                 //存储文件中的一行数据
	std::locale   loc1 = std::locale::global(std::locale(".936"));
	ifstream      sin(FileIn);             //读取源文件
	std::ofstream sout(FileOut);           //修改目标文件

	DXFParseNextLine(sin , sout , strLine) ;
	sin.close();
	sout.close();

	//显示进度条
	//InvokeProgressFun();
//	::SendMessage(m_hwnd,0x0500,0,(double)100.0);

	return 0;
}

//yzg 增加对E00文件格式读写的支持 begin
DXF_API int EooTransform( const char * FileIn, const char * FileOut, void * transfun, HWND m_phwnd)
{
	g_FileIn  = FileIn;
	g_FileOut = FileOut;
	m_hwnd    = m_phwnd;
	InvokeProgressFun();

	//转换函数
	p_transform = ( TransFun )transfun ;

	string        strLine;           //存储文件中的一行数据
	std::locale   loc1 = std::locale::global(std::locale(".936"));
	ifstream      sin(FileIn);       //读取源文件
	std::ofstream sout(FileOut);     //修改目标文件

	EooParseNextLine( sin , sout , strLine ) ;
	sin.close();
	sout.close();

	return 0;
}

DXF_API int CoverageTransform( const char * FileIn, const char * FileOut, void * transfun, HWND m_phwnd )
{	
	//转换函数
	p_transform = ( TransFun )transfun ;

    CoverageParse(FileIn,FileOut);
   
	return 0;
}

//add by chenyong 2013-5-14 支持dxf投影转换
DXF_API int DXFProject(const char *pFileIn, const char *pFileOut, bool bToPlane, void *ptransfun, HWND pHwnd)
{
	g_FileIn = pFileIn;
	g_FileOut = pFileOut;
	m_hwnd=pHwnd;
//	::SendMessage(m_hwnd,0x0500,0,(double)0.0);

	//转换函数
	p_transform = ( TransFun )ptransfun ;

	string        strLine;                  //存储文件中的一行数据
	std::locale   loc1 = std::locale::global(std::locale(".936"));
	ifstream      sin(pFileIn);             //读取源文件
	std::ofstream sout(pFileOut);           //修改目标文件

	DXFProjectNextLine(sin , sout , strLine, bToPlane) ;
	sin.close();
	sout.close();

	//CDxfProject  DxfProject(pFileIn, pFileOut, ptransfun, pHwnd);
	//DxfProject.DXFParseNextLine();

	//显示进度条
	//InvokeProgressFun();
//	::SendMessage(m_hwnd,0x0500,0,(double)100.0);

	return 0;
}