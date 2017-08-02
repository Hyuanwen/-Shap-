/******************************************************************************
* $Id: DeuProject.h 1 2010-08-17 14:38:05Z daifeng $
*
* Project:  DeuProject 1.0
* Purpose:  Public (application) include file for DeuProject API, and constants.
* Author:   daifeng, <nuistbaker@126.com>
*
******************************************************************************/
#ifndef _DEUPROJECT_H
#define _DEUPROJECT_H

#include <math.h>
#include <stdlib.h>

#ifdef DEUPROJECT_EXPORTS
#define DEUPROJECT_API __declspec(dllexport)
#else
#define DEUPROJECT_API __declspec(dllimport)
#endif

class DEUPROJECT_API CDeuProject 
{
public:
	CDeuProject(void);
};

#if!define(PROJECTS_H)
typedef void *DROM;
typedef void *projPJ;
#else
typedef DEFROM *DROM;
typedef PJ     *projPJ;
#endif

//描述一个椭球
typedef struct PJconsts 
{
public:
	double get_M(double b);
	double get_N(double b);
	double get_et2(double b);

public:
	//double datum_params[7];   //dx,dy,dz,rx,ry,rz,m
	double a,	    //长轴
		   b,		//短轴
		   f,		//扁率
		 //da,		//长轴差
		 //df,      //扁率差
		   es,      //e^2
		   one_es,  //1-e^2		
		   false_e; //东假值
public:
	double  from_greenwich;/* prime meridian offset (in radians) */
}PJ;

extern int pj_errno;	/* global error return code */



//////////////////////////////////////////////////////////////////////////
DEUPROJECT_API projPJ init_PJ(double a,double f,projPJ pj=NULL);
//DEUPROJECT_API int    init_KEY(const char *szKey);
//////////////////////////////////////////////////////////////////////////

//计算二维7参数
DEUPROJECT_API int ComputeParams_2D7PBL(int n,double B1[],double L1[],double B2[],double L2[],projPJ  src,projPJ  des,double Para[]);

//计算二维四参数平面
DEUPROJECT_API int ComputeParams_2D4Pxy(int n,double x1[],double y1[],double x2[],double y2[],double Para[]);

//计算3维布尔莎
DEUPROJECT_API int ComputeParams_3D7PBursa(int n,double X1[],double Y1[],double Z1[],double X2[],double Y2[],double Z2[],double Para[]);

//计算三维7参数BLH
DEUPROJECT_API int ComputeParams_3D7PBLH(int n,double B1[],double L1[],double H1[],double B2[],double L2[],double H2[],projPJ  src,projPJ  des,double Para[] );

//计算多项式展开
DEUPROJECT_API int ComputeParams_Polynomial1(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] );
DEUPROJECT_API int ComputeParams_Polynomial2(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] );
DEUPROJECT_API int ComputeParams_Polynomial3(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] );
DEUPROJECT_API int ComputeParams_Polynomial4(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] );

//二维七参数坐标转换
DEUPROJECT_API void CoorTran_BL7(projPJ  src,projPJ  des,double  Para[] ,double B0,double L0,double & B,double & L);

//平面四参数坐标转换
DEUPROJECT_API void CoorTran_xy4(double  Para[],double X0,double Y0,double & X,double & Y);

//Bursa坐标转换
DEUPROJECT_API void CoorTran_Bursa(double  Para[],double X0,double Y0,double Z0,double & X,double & Y,double & Z);

//三维七参数坐标转换
DEUPROJECT_API void CoorTran_BLH7(projPJ  src,projPJ  des,double  Para[],double B0,double L0,double H0,double & B,double & L,double & H);

//多项式拟合坐标转换
DEUPROJECT_API void CoorTran_Poly1(double  Para[],double X0,double Y0,double & X,double & Y);
DEUPROJECT_API void CoorTran_Poly2(double  Para[],double X0,double Y0,double & X,double & Y);
DEUPROJECT_API void CoorTran_Poly3(double  Para[],double X0,double Y0,double & X,double & Y);
DEUPROJECT_API void CoorTran_Poly4(double  Para[],double X0,double Y0,double & X,double & Y);


//高斯投影正算(投影到平面)
//输入   :a (椭球长半轴 ,类型double ,范围 a>0)
//        f (椭球扁率倒数,类型double ,范围 f>0.5)
//        L0 中央子午线经度,类型 double,范围0=<L0<PI*2       )
//        B L(投影点(经度,纬度),类型 double,范围0<=|B|<=PI/2, 0=<L<=PI*2     )
//输出   :x,y(投影平面坐标(x,y),类型 double *, 范围 x,y为实数)
//        deform(投影变形系数结构,类型tagDEFORM *)
DEUPROJECT_API void Gauss_bl_xy(projPJ  pj,double lo,double b,double l,double &x,double &y);

//高斯投影反算
//输入   :a (椭球长半轴 ,类型double ,范围 a>0)
//        f (椭球扁率倒数,类型double ,范围 f>0.5)
//        L0 中央子午线经度,类型 double,范围0<|B0|<PI/2, 0=<L0<=PI*2        )
//        x,y(投影平面坐标(x,y),类型 double, 范围 x,y为实数)
//输出   :B L(投影点(经度,纬度),类型 double *,范围0<=|B|<=PI/2, 0=<L<=PI*2   )
DEUPROJECT_API void Gauss_xy_bl(projPJ  pj,double lo,double x,double y,double &b,double &l);


//投影到空间直角
DEUPROJECT_API int pj_geocentric_to_geodetic( double a, double f,
											 long point_count, int point_offset,
											 double *x, double *y, double *z );

DEUPROJECT_API int pj_geodetic_to_geocentric( double a, double f,
											 long point_count, int point_offset,
											 double *x, double *y, double *z );
#endif