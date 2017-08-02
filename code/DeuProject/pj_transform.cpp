#include "stdafx.h"
#include "projects.h"

bool g_CanUse = false;

double PJconsts::get_M(double b)
{
	// 子午圈曲率半径
	return a*(1-es)/((1-es*sin(b)*sin(b))*sqrt(1-es*sin(b)*sin(b)));  
}

double PJconsts::get_N(double b)
{
	// 卯酉圈曲率半径
	return a/(sqrt(1-es*sin(b)*sin(b)));       
}

double PJconsts::get_et2(double cosB)
{	
	return es / (1 -  es ) * pow( cosB ,2)  ;
}

//初始化
DEUPROJECT_API projPJ init_PJ(double a,double f,projPJ pj_)
{
	PJ* pj = (PJ*) pj_;
	if (pj == NULL)
	{
		pj = new PJ;
	}
	pj->a		= a;
	pj->es		= 2 * f - f * f;
	pj->f		= f;
	pj->one_es	= 1 - pj->es;
	pj->b		= pj->a * sqrt (pj->one_es);

	return pj;
}

//DEUPROJECT_API int init_KEY(const char *szKey)
//{
//	if( strcmp( szKey ,"B7AA7521-3F3A-4411-A50A-FECC8C9DD4F8" ) == 0 )
//	{
//		g_CanUse = true ;
//	}
//	else
//	{
//		g_CanUse = false ;
//	}
//
//	return 0;
//}

//坐标转换
//二维七参数
DEUPROJECT_API void CoorTran_BL7(projPJ src_, projPJ des_, double Para[], double B0, double L0, double &B, double &L)
{
	if(!g_CanUse)
	{
		return;
	}

	PJ*	   src			=  (PJ*)src_;
	PJ*	   des			=  (PJ*)des_;
	double dx			=	Para[0];
	double dy			=	Para[1];
	double dz			=	Para[2];
	double rx			=	Para[3];
	double ry			=	Para[4];
	double rz			=	Para[5];
	double m			=	Para[6];
	double da			=	Para[7];
	double df			=	Para[8];

	double cos_b		=	cos(B0);
	double sin_b		=	sin(B0);
	double cos_l		=	cos(L0);
	double sin_l		=	sin(L0);
	double tan_b		=	tan(B0);

	//double da			=	src->a - des->a;
	double e2			=	des->es;
	double a			=	des->a;
	double f			=	des->f;
	//double df			=	src->f - des->f;
	double N			=	src->get_N(B0);
	double M			=	src->get_M(B0);

	double detal_B;
	double detal_L;

	detal_B	=   -sin_b * cos_l * RPI /M * dx 
				-sin_b * sin_l * RPI /M * dy
				+cos_b * RPI /M * dz
				-sin_l * rx 
				+ cos_l * ry 
				-sin_b * cos_b * N * e2 * RPI /M * m  
				+sin_b * cos_b * N * e2 * RPI *da / (a * M)
				+sin_b * cos_b * RPI * ( 2-e2 * sin_b * sin_b ) * df/ (1-f) ;
				
	detal_L =   - sin_l * RPI /(N*cos_b) * dx
				+ cos_l * RPI /(N*cos_b) * dy
				+(tan_b) * cos_l * rx
				+(tan_b) * sin_l * ry
				-rz;

	B = B0 + detal_B;
	L = L0 + detal_L;
}

//平面四参数
DEUPROJECT_API void CoorTran_xy4(double  Para[],double X0,double Y0,double & X,double & Y)
{
	//if(!g_CanUse) {return;}
	
	//改过的公式
	double	dx			=	Para[0];
	double	dy			=	Para[1];
	double	C			=	Para[2];
	double	D			=	Para[3];

	//技术指南
	//double dx			=	Para[0];
	//double dy			=	Para[1];
	//double cos_a		=	Para[2];
	//double sin_a		=	Para[3];
	//double n			=	Para[4];

	//技术指南
	//X = dx + n * ( cos_a * X0 - sin_a * Y0 );
	//Y = dy + n * ( sin_a * X0 - cos_a * Y0 );

	//改过的公式
	X = dx + C * X0 - D * Y0 ;
	Y = dy + D * X0 + C * Y0 ;
}

//Bursa
DEUPROJECT_API void CoorTran_Bursa(double  Para[],double X0,double Y0,double Z0,double & X,double & Y,double & Z)
{
	//if(!g_CanUse) {return;}

	double dx			=	Para[0];
	double dy			=	Para[1];
	double dz			=	Para[2];
	double rx			=	Para[3];
	double ry			=	Para[4];
	double rz			=	Para[5];
	double n			=	Para[6];

	//技术指南
	//double X2,Y2,Z2;
	//X2 = dx - Z0 * ry + Y0 * rz + n * X0 + X0;
	//Y2 = dy + Z0 * rx - X0 * rz + n * Y0 + Y0;
	//Z2 = dz - Y0 * rx + X0 * ry + n * Z0 + Z0;
	
	//书上的
	double X3,Y3,Z3;
	X = dx + ( 1 + n ) * ( X0 + rz * Y0 - ry * Z0 );
	Y = dy + ( 1 + n ) * ( -rz * X0 + Y0 + rx * Z0 );
	Z = dz + ( 1 + n ) * ( ry * X0 - rx * Y0 + Z0 );

	//PROJ4
	//x_out = M_BF*(       x[io] - Rz_BF*y[io] + Ry_BF*z[io]) + Dx_BF;
	//y_out = M_BF*( Rz_BF*x[io] +       y[io] - Rx_BF*z[io]) + Dy_BF;
	//z_out = M_BF*(-Ry_BF*x[io] + Rx_BF*y[io] +       z[io]) + Dz_BF;
	//X = (1+n)*(       X0 - rz*Y0 + ry*Z0) + dx;
	//Y = (1+n)*( rz*X0 +       Y0 - rx*Z0) + dy;
	//Z = (1+n)*(-ry*X0 + rx*Y0 +       Z0) + dz;
}

//三维七参数
DEUPROJECT_API void CoorTran_BLH7(projPJ  src_,projPJ  des_,double  Para[],double B0,double L0,double H0,double & B,double & L,double & H)
{
	//if(!g_CanUse) {return;}

	PJ*	   src          =  (PJ*)src_;
	PJ*    des          =  (PJ*)des_;

	double dx			=	Para[0];
	double dy			=	Para[1];
	double dz			=	Para[2];
	double rx			=	Para[3];
	double ry			=	Para[4];
	double rz			=	Para[5];
	double m			=	Para[6];
	double da			=	Para[7];
	double df			=	Para[8];

	double sin_l		=	sin(L0);
	double cos_l		=	cos(L0);
	double sin_b		=	sin(B0);
	double cos_b		=	cos(B0);

	double N			=	src->get_N(B0);
	double M			=	src->get_M(B0);
	double e2			=	src->es;
	double a			=	src->a;
	double f			=	src->f;
	//double da			=	src->a - des->a;
	//double df			=	src->f - des->f;

	double detal_L;
	double detal_B;
	double detal_H;

	//书上的
	detal_L =   - sin_l * RPI / ((N + H0) * cos_b) * dx
				+ cos_l * RPI /((N + H0) * cos_b) * dy
				+ ( sin_b / cos_b ) * cos_l *  rx
				+ ( sin_b / cos_b ) * sin_l *  ry
				- rz;

	detal_B =   - sin_b * cos_l * RPI / (M + H0) * dx
				- sin_b * sin_l * RPI / (M + H0) * dy
				+ cos_b * RPI /(M + H0) * dz
				- sin_l * rx
				+ cos_l * ry
				- N * e2 * sin_b * cos_b * RPI / (M+H0) * m
				+ N * e2 * sin_b * cos_b * RPI * da / ((M + H0)*a)				
				+ M * (2 - e2 * sin_b * sin_b) / ((M + H0) * (1 - f)) * sin_b * cos_b * df * RPI; 

	detal_H =     cos_b * cos_l * dx
				+ cos_b * sin_l * dy
				+ sin_b * dz
				- N * e2 * sin_b * cos_b * sin_l * rx * (iRPI)
				+ N * e2 * sin_b * cos_b * cos_l * ry * (iRPI)
				+ N * (1 - e2 * sin_b * sin_b) * m 
				+ H0 * m
				- N / a *(1-e2 * sin_b * sin_b) * da
				+ M / (1 - f) * (1 - e2 * sin_b * sin_b) * sin_b * sin_b * df;

	//网上的
	//detal_L = - sin_l * RPI / ((N + H0) * cos_b) * dx
	//	+ cos_l * RPI /((N + H0) * cos_b) * dy
	//	+ ( sin_b / cos_b ) * cos_l * (1- N * e2 / (N + H0)) * rx
	//	+ ( sin_b / cos_b ) * sin_l * (1- N * e2 / (N + H0)) * ry
	//	- rz;

	//detal_B = - sin_b * cos_l * RPI / (M + H0) * dx
	//	- sin_b * sin_l * RPI / (M + H0) * dy
	//	+ cos_b * RPI /(M + H0) * dz
	//	- sin_l * rx * (N*(1-e2*sin_b*sin_b)+H0) / (M+H0)
	//	+ cos_l * ry * (N*(1-e2*sin_b*sin_b)+H0) / (M+H0)
	//	- N * e2 * sin_b * cos_b * RPI / (M+H0) * m
	//	+ N * e2 * sin_b * cos_b * RPI * da / ((M + H0)*a)				
	//	+ M * (2 - e2 * sin_b * sin_b) / ((M + H0) * (1 - f)) * sin_b * cos_b * df * RPI; 

	//detal_H = cos_b * cos_l * dx
	//	+ cos_b * sin_l * dy
	//	+ sin_b * dz
	//	- N * e2 * sin_b * cos_b * sin_l * rx / (RPI)
	//	+ N * e2 * sin_b * cos_b * cos_l * ry / (RPI)
	//	+ N * (1 - e2 * sin_b * sin_b) * m 
	//	+ H0 * m
	//	- N / a *(1-e2 * sin_b * sin_b) * da
	//	+ M / (1 - f) * (1 - e2 * sin_b * sin_b) * sin_b * sin_b * df;

	//9个参数
	B = B0 + detal_B;
	L = L0 + detal_L;
	H = H0 + detal_H;
}

//多项式拟合
DEUPROJECT_API void CoorTran_Poly1(double  Para[],double X0,double Y0,double & X,double & Y)
{
	//if(!g_CanUse) {return;}

	double A0			=	Para[0];
	double A1			=	Para[1];
	double A2			=	Para[2];
	double B0			=	Para[3];
	double B1			=	Para[4];
	double B2			=	Para[5];
	
	double detalX ;
	double detalY ;

	detalX	=	A0 + A1 * X0 + A2 * Y0;
	detalY	=	B0 + B1 * X0 + B2 * Y0;

	X = X0 + detalX;
	Y = Y0 + detalY;

	return;
}

//多项式拟合 2阶
DEUPROJECT_API void CoorTran_Poly2(double  Para[],double X0,double Y0,double & X,double & Y)
{
	/*
	if(!g_CanUse) return;
	
	double A0			=	Para[0];
	double A1			=	Para[1];
	double A2			=	Para[2];
	double A3			=	Para[3];
	double A4			=	Para[4];
	double A5			=	Para[5];
	double B0			=	Para[0];
	double B1			=	Para[1];
	double B2			=	Para[2];
	double B3			=	Para[3];
	double B4			=	Para[4];
	double B5			=	Para[5];

	double detalX ;
	double detalY ;


	detalX	=	A0 + A1 * X0 + A2 * Y0 + A3 * X0 * Y0 + A4 * X0 * X0 + A5 * Y0 * Y0;

	detalY	=	B0 + B1 * X0 + B2 * Y0 + B3 * X0 * Y0 + B4 * X0 * X0 + B5 * Y0 * Y0;


	X = X0 + detalX;

	Y = Y0 + detalY;

	return;
	*/

	//yzg 2012-8-23 修改代码 begin
	//if(!g_CanUse) {return;}

	double A0			=	Para[0];
	double A1			=	Para[1];
	double A2			=	Para[2];
	double A3			=	Para[3];
	double A4			=	Para[4];
	double A5			=	Para[5];

	double B0			=	Para[6];
	double B1			=	Para[7];
	double B2			=	Para[8];
	double B3			=	Para[9];
	double B4			=	Para[10];
	double B5			=	Para[11];

	double detalX ;
	double detalY ;

	detalX	=	A0 + A1 * X0 + A2 * Y0 + A3 * X0 * Y0 + A4 * X0 * X0 + A5 * Y0 * Y0;
	detalY	=	B0 + B1 * X0 + B2 * Y0 + B3 * X0 * Y0 + B4 * X0 * X0 + B5 * Y0 * Y0;

	X = X0 + detalX;
	Y = Y0 + detalY;

	//yzg 2012-8-23 修改代码 end

	return;
}

DEUPROJECT_API void CoorTran_Poly3(double  Para[],double X0,double Y0,double & X,double & Y)
{
	//if(!g_CanUse) {return;}

	double A0			=	Para[0];
	double A1			=	Para[1];
	double A2			=	Para[2];
	double A3			=	Para[3];
	double A4			=	Para[4];
	double A5			=	Para[5];
	double A6			=	Para[6];
	double A7			=	Para[7];
	double A8			=	Para[8];
	double A9			=	Para[9];

	double B0			=	Para[0];
	double B1			=	Para[1];
	double B2			=	Para[2];
	double B3			=	Para[3];
	double B4			=	Para[4];
	double B5			=	Para[5];
	double B6			=	Para[6];
	double B7			=	Para[7];
	double B8			=	Para[8];
	double B9			=	Para[9];

	double detalX ;
	double detalY ;

	detalX	=	A0 + A1 * X0 + A2 * Y0 + A3 * X0 * Y0 + A4 * X0 * X0 + A5 * Y0 * Y0 + A6 * X0 * X0 * Y0 + A7 * X0 * Y0 * Y0 + A8 * X0 * X0 * X0 + A9 * Y0 * Y0 * Y0;
	detalY	=	B0 + B1 * X0 + B2 * Y0 + B3 * X0 * Y0 + B4 * X0 * X0 + B5 * Y0 * Y0 + B6 * X0 * X0 * Y0 + B7 * X0 * Y0 * Y0 + B8 * X0 * X0 * X0 + B9 * Y0 * Y0 * Y0;

	X = X0 + detalX;
	Y = Y0 + detalY;

	return;
}

DEUPROJECT_API void CoorTran_Poly4(double  Para[],double X0,double Y0,double & X,double & Y)
{
	//if(!g_CanUse) {return;}

	double A0			=	Para[0];
	double A1			=	Para[1];
	double A2			=	Para[2];
	double A3			=	Para[3];
	double A4			=	Para[4];
	double A5			=	Para[5];
	double A6			=	Para[6];
	double A7			=	Para[7];
	double A8			=	Para[8];
	double A9			=	Para[9];
	double A10			=	Para[10];
	double A11			=	Para[11];
	double A12			=	Para[12];
	double A13			=	Para[13];
	double A14			=	Para[14];
	
	double B0			=	Para[0];
	double B1			=	Para[1];
	double B2			=	Para[2];
	double B3			=	Para[3];
	double B4			=	Para[4];
	double B5			=	Para[5];
	double B6			=	Para[6];
	double B7			=	Para[7];
	double B8			=	Para[8];
	double B9			=	Para[9];
	double B10			=	Para[10];
	double B11			=	Para[11];
	double B12			=	Para[12];
	double B13			=	Para[13];
	double B14			=	Para[14];

	double detalX ;
	double detalY ;

	detalX	=	A0 + A1 * X0 + A2 * Y0 
				+ A3 * X0 * Y0 + A4 * X0 * X0 + A5 * Y0 * Y0 
				+ A6 * X0 * X0 * Y0 + A7 * X0 * Y0 * Y0 + A8 * X0 * X0 * X0 + A9 * Y0 * Y0 * Y0 
				+ A10 * X0 * X0 * X0 * X0 + A11 * X0 * X0 * X0 * Y0 + A12 * X0 * X0 * Y0 * Y0 + A13 * X0 * Y0 * Y0 * Y0 + A14 * Y0 * Y0 * Y0 * Y0;

	detalY	=	B0 + B1 * X0 + B2 * Y0 
				+ B3 * X0 * Y0 + B4 * X0 * X0 + B5 * Y0 * Y0 
				+ B6 * X0 * X0 * Y0 + B7 * X0 * Y0 * Y0 + B8 * X0 * X0 * X0 + B9 * Y0 * Y0 * Y0 
				+ B10 * X0 * X0 * X0 * X0 + B11 * X0 * X0 * X0 * Y0 + B12 * X0 * X0 * Y0 * Y0 + B13 * X0 * Y0 * Y0 * Y0 + B14 * Y0 * Y0 * Y0 * Y0;

	X = X0 + detalX;
	Y = Y0 + detalY;
	
	return;
}
