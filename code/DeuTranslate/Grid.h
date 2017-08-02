#pragma once

#include "DeuGridData.h"

//������
class CGrid
{
public:
	CGrid(void);
	~CGrid(void);
};

HMODULE g_hCoordsTransDll;

#include <vector>
using namespace std;

//typedef struct deuGridFormat
//{
//public:
//	char szFrame[12];
//	double  DB_XN;//
//	double	DL_XN;//
//	double	DB_XB;//
//	double	DL_XB;//
//	double	DB_DB;//
//	double	DL_DB;//
//	double	DB_DN;//
//	double	DL_DN;//
//
//}deuGridFormat;

//add by chenyong 20130109
static vector<deuGridFormat> g_vec_vec_GridList_54_2000;
static vector<deuGridFormat> g_vec_vec_GridList_2000_54;

static vector<deuGridFormat> g_vec_vec_GridList_80_2000;
static vector<deuGridFormat> g_vec_vec_GridList_2000_80;

static vector<deuGridFormat> g_vec_vec_GridList_84_2000;
static vector<deuGridFormat> g_vec_vec_GridList_2000_84;

//����dll
void DeuLoadLibrary();

//��������
void DeuLoadGridData();

//��DLL�л�ø���������
typedef void (_stdcall *Func_GetTuFuCoordsTransData)(char*, char*, char*, int, double &, double &, double &, double &, double &, double &, double &, double &);

//��BUFF�л�ø���������
void _GetTuFuCoordsTransData_FromBuf(char*, char*, char*, int, double &, double &, double &, double &, double &, double &, double &, double &);

//��������ڵ������ͼ����
void CalculateFrameByPoint( double x , double y, int coordtype , char Scale = 'D',char * szFrame = "J50B001001");

//����ͼ���ż���4���ǵ�����
void CalculateCoordsByFrame( char * szFrame , int CoordType , double & DB_XN, double & DL_XN,double & DB_XB,double & DL_XB,double & DB_DB,double & DL_DB,double & DB_DN,double & DL_DN  );

//���ݱ����߻�þ��Ȳ��γ�Ȳ�
void GetDetalXY( int iScaleCode , double & detalX , double & detalY );

//ȡ�õ��˫�����ڲ����������
int FetchDetalXY( double x ,double y , int CoordType, const char * szSH  , const char * PWD  , const char * szProName , const char * szFrame ,int FX , double & dx ,double & dy  );

void fun_GridDLL( char * szDLL , char * szSH , char * PWD );