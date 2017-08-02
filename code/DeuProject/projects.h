/******************************************************************************
* $Id: Projects.h 1 2010-08-17 14:38:05Z daifeng $
*
* Project:  DeuProject 1.0
* Purpose:  Primary (private) include file for DeuProject API, and constants.
* Author:   daifeng, <nuistbaker@126.com>
*
******************************************************************************/

#ifndef PROJECTS_H
#define PROJECTS_H

#define C_NAMESPACE extern "C"
#define C_NAMESPACE_VAR extern "C"

////描述一个椭球
//typedef struct PJconsts {
//public:
//	double get_M(double b);
//	double get_N(double b);
//	double get_et2(double b);
//
//public:
//	//double datum_params[7];//dx,dy,dz,rx,ry,rz,m
//	double 
//		a,//长轴
//		b,//短轴
//		f,//扁率
//		//da,//长轴差
//		//df,//扁率差
//		es,//e^2
//		one_es,//1-e^2		
//		false_e;//东假值
//public:
//	double  from_greenwich;/* prime meridian offset (in radians) */
//}PJ;

extern bool g_CanUse;

//变形椭圆类
typedef class tagDEFORM{
public:
	tagDEFORM(); //构造函数
	double aero; //面积变形
	double angle;//角度变形
	double a,b;  //长度变形椭圆长半轴,短半轴
}DEFROM;

#define RAD_TO_DEG			57.29577951308232
#define DEG_TO_RAD			.0174532925199432958
#define HALFPI				1.5707963267948966
#define FORTPI				0.78539816339744833
#define PI					3.14159265358979323846
#define TWOPI				6.2831853071795864769
#define DEL_TOL				1e-14
#define PJD_ERR_GEOCENTRIC	-45       //datum system errors 
const double RPI = 180 * 3600 / PI ;  // 弧度秒
const double iRPI = PI / 180 * 3600 ; 

#include "DeuProject.h"

#endif