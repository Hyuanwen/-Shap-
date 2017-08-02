// DXF.cpp : ���� DLL Ӧ�ó���ĵ���������
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
    return (long)f_stat.st_size;	//�����ļ��ֽ���

	/*
		˵����
			1. ʹ��stat�ṹ��ʱ����Ҫ����ͷ�ļ�			
				#include <sys/types.h>
				#include <sys/stat.h>
			2. statԭ��Ϊ��
				int stat(const char* filename, struct stat* buf);
			3. stat�ṹ���£�
				
				struct stat
				{
					dev_t		st_dev;			--�ļ������豸��ID
					ino_t		st_ino;			--�ڵ��
					mode_t		st_mode;		--����ģʽ
					nlink_t		st_nlink;		--������ļ���������
					uid_t		st_nid;			--�û�id
					gid_t		st_gid;			--��id
					dev_t		st_rdev;		--�豸�ţ�����豸�ļ�
					off_t		st_size;		--�ļ���С���ֽ�Ϊ��λ
					blksize_t	st_blksize;		--ϵͳ��Ĵ�С
					blkcnt_t	st_blocks;		--�ļ��������
					time_t		st_atime;		--�����ȡʱ��
					time_t		st_mtime;		--����޸�ʱ��
					time_t		st_ctime;		--����޸�ʱ��
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

	//��ʾ������
	//InvokeProgressFun();
//	::SendMessage(m_hwnd,0x0500,0,(double)0.0);

	//ת������
	p_transform = ( TransFun )transfun ;

	string        strLine;                 //�洢�ļ��е�һ������
	std::locale   loc1 = std::locale::global(std::locale(".936"));
	ifstream      sin(FileIn);             //��ȡԴ�ļ�
	std::ofstream sout(FileOut);           //�޸�Ŀ���ļ�

	DXFParseNextLine(sin , sout , strLine) ;
	sin.close();
	sout.close();

	//��ʾ������
	//InvokeProgressFun();
//	::SendMessage(m_hwnd,0x0500,0,(double)100.0);

	return 0;
}

//yzg ���Ӷ�E00�ļ���ʽ��д��֧�� begin
DXF_API int EooTransform( const char * FileIn, const char * FileOut, void * transfun, HWND m_phwnd)
{
	g_FileIn  = FileIn;
	g_FileOut = FileOut;
	m_hwnd    = m_phwnd;
	InvokeProgressFun();

	//ת������
	p_transform = ( TransFun )transfun ;

	string        strLine;           //�洢�ļ��е�һ������
	std::locale   loc1 = std::locale::global(std::locale(".936"));
	ifstream      sin(FileIn);       //��ȡԴ�ļ�
	std::ofstream sout(FileOut);     //�޸�Ŀ���ļ�

	EooParseNextLine( sin , sout , strLine ) ;
	sin.close();
	sout.close();

	return 0;
}

DXF_API int CoverageTransform( const char * FileIn, const char * FileOut, void * transfun, HWND m_phwnd )
{	
	//ת������
	p_transform = ( TransFun )transfun ;

    CoverageParse(FileIn,FileOut);
   
	return 0;
}

//add by chenyong 2013-5-14 ֧��dxfͶӰת��
DXF_API int DXFProject(const char *pFileIn, const char *pFileOut, bool bToPlane, void *ptransfun, HWND pHwnd)
{
	g_FileIn = pFileIn;
	g_FileOut = pFileOut;
	m_hwnd=pHwnd;
//	::SendMessage(m_hwnd,0x0500,0,(double)0.0);

	//ת������
	p_transform = ( TransFun )ptransfun ;

	string        strLine;                  //�洢�ļ��е�һ������
	std::locale   loc1 = std::locale::global(std::locale(".936"));
	ifstream      sin(pFileIn);             //��ȡԴ�ļ�
	std::ofstream sout(pFileOut);           //�޸�Ŀ���ļ�

	DXFProjectNextLine(sin , sout , strLine, bToPlane) ;
	sin.close();
	sout.close();

	//CDxfProject  DxfProject(pFileIn, pFileOut, ptransfun, pHwnd);
	//DxfProject.DXFParseNextLine();

	//��ʾ������
	//InvokeProgressFun();
//	::SendMessage(m_hwnd,0x0500,0,(double)100.0);

	return 0;
}