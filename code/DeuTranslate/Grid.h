#pragma once

#include "DeuGridData.h"

//格网法
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

//加载dll
void DeuLoadLibrary();

//加载数据
void DeuLoadGridData();

//从DLL中获得格网改正量
typedef void (_stdcall *Func_GetTuFuCoordsTransData)(char*, char*, char*, int, double &, double &, double &, double &, double &, double &, double &, double &);

//从BUFF中获得格网改正量
void _GetTuFuCoordsTransData_FromBuf(char*, char*, char*, int, double &, double &, double &, double &, double &, double &, double &, double &);

//计算点所在的网格的图幅号
void CalculateFrameByPoint( double x , double y, int coordtype , char Scale = 'D',char * szFrame = "J50B001001");

//根据图幅号计算4个角点坐标
void CalculateCoordsByFrame( char * szFrame , int CoordType , double & DB_XN, double & DL_XN,double & DB_XB,double & DL_XB,double & DB_DB,double & DL_DB,double & DB_DN,double & DL_DN  );

//根据比例尺获得经度差和纬度差
void GetDetalXY( int iScaleCode , double & detalX , double & detalY );

//取得点的双线性内插格网改正量
int FetchDetalXY( double x ,double y , int CoordType, const char * szSH  , const char * PWD  , const char * szProName , const char * szFrame ,int FX , double & dx ,double & dy  );

void fun_GridDLL( char * szDLL , char * szSH , char * PWD );