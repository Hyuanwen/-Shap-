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

//����һ������
typedef struct PJconsts 
{
public:
	double get_M(double b);
	double get_N(double b);
	double get_et2(double b);

public:
	//double datum_params[7];   //dx,dy,dz,rx,ry,rz,m
	double a,	    //����
		   b,		//����
		   f,		//����
		 //da,		//�����
		 //df,      //���ʲ�
		   es,      //e^2
		   one_es,  //1-e^2		
		   false_e; //����ֵ
public:
	double  from_greenwich;/* prime meridian offset (in radians) */
}PJ;

extern int pj_errno;	/* global error return code */



//////////////////////////////////////////////////////////////////////////
DEUPROJECT_API projPJ init_PJ(double a,double f,projPJ pj=NULL);
//DEUPROJECT_API int    init_KEY(const char *szKey);
//////////////////////////////////////////////////////////////////////////

//�����ά7����
DEUPROJECT_API int ComputeParams_2D7PBL(int n,double B1[],double L1[],double B2[],double L2[],projPJ  src,projPJ  des,double Para[]);

//�����ά�Ĳ���ƽ��
DEUPROJECT_API int ComputeParams_2D4Pxy(int n,double x1[],double y1[],double x2[],double y2[],double Para[]);

//����3ά����ɯ
DEUPROJECT_API int ComputeParams_3D7PBursa(int n,double X1[],double Y1[],double Z1[],double X2[],double Y2[],double Z2[],double Para[]);

//������ά7����BLH
DEUPROJECT_API int ComputeParams_3D7PBLH(int n,double B1[],double L1[],double H1[],double B2[],double L2[],double H2[],projPJ  src,projPJ  des,double Para[] );

//�������ʽչ��
DEUPROJECT_API int ComputeParams_Polynomial1(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] );
DEUPROJECT_API int ComputeParams_Polynomial2(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] );
DEUPROJECT_API int ComputeParams_Polynomial3(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] );
DEUPROJECT_API int ComputeParams_Polynomial4(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] );

//��ά�߲�������ת��
DEUPROJECT_API void CoorTran_BL7(projPJ  src,projPJ  des,double  Para[] ,double B0,double L0,double & B,double & L);

//ƽ���Ĳ�������ת��
DEUPROJECT_API void CoorTran_xy4(double  Para[],double X0,double Y0,double & X,double & Y);

//Bursa����ת��
DEUPROJECT_API void CoorTran_Bursa(double  Para[],double X0,double Y0,double Z0,double & X,double & Y,double & Z);

//��ά�߲�������ת��
DEUPROJECT_API void CoorTran_BLH7(projPJ  src,projPJ  des,double  Para[],double B0,double L0,double H0,double & B,double & L,double & H);

//����ʽ�������ת��
DEUPROJECT_API void CoorTran_Poly1(double  Para[],double X0,double Y0,double & X,double & Y);
DEUPROJECT_API void CoorTran_Poly2(double  Para[],double X0,double Y0,double & X,double & Y);
DEUPROJECT_API void CoorTran_Poly3(double  Para[],double X0,double Y0,double & X,double & Y);
DEUPROJECT_API void CoorTran_Poly4(double  Para[],double X0,double Y0,double & X,double & Y);


//��˹ͶӰ����(ͶӰ��ƽ��)
//����   :a (���򳤰��� ,����double ,��Χ a>0)
//        f (������ʵ���,����double ,��Χ f>0.5)
//        L0 ���������߾���,���� double,��Χ0=<L0<PI*2       )
//        B L(ͶӰ��(����,γ��),���� double,��Χ0<=|B|<=PI/2, 0=<L<=PI*2     )
//���   :x,y(ͶӰƽ������(x,y),���� double *, ��Χ x,yΪʵ��)
//        deform(ͶӰ����ϵ���ṹ,����tagDEFORM *)
DEUPROJECT_API void Gauss_bl_xy(projPJ  pj,double lo,double b,double l,double &x,double &y);

//��˹ͶӰ����
//����   :a (���򳤰��� ,����double ,��Χ a>0)
//        f (������ʵ���,����double ,��Χ f>0.5)
//        L0 ���������߾���,���� double,��Χ0<|B0|<PI/2, 0=<L0<=PI*2        )
//        x,y(ͶӰƽ������(x,y),���� double, ��Χ x,yΪʵ��)
//���   :B L(ͶӰ��(����,γ��),���� double *,��Χ0<=|B|<=PI/2, 0=<L<=PI*2   )
DEUPROJECT_API void Gauss_xy_bl(projPJ  pj,double lo,double x,double y,double &b,double &l);


//ͶӰ���ռ�ֱ��
DEUPROJECT_API int pj_geocentric_to_geodetic( double a, double f,
											 long point_count, int point_offset,
											 double *x, double *y, double *z );

DEUPROJECT_API int pj_geodetic_to_geocentric( double a, double f,
											 long point_count, int point_offset,
											 double *x, double *y, double *z );
#endif