#include "stdafx.h"
#include "projects.h"

double MeridianArcLength(double a , double es , double lat, int N = 5 );
double CalcuBf(double a ,double es,double x );

const double i24		= 1.0 / 24.0;
const double i720		= 1.0 / 720.0;
const double i6			= 1.0 / 6.0;
const double i120		= 1.0 / 120.0;
const double i12		= 1.0 / 12.0;
const double i360		= 1.0 / 360.0;
const double i4			= 1.0 / 4.0;
const double i64		= 1.0 / 64.0;
const double i256		= 1.0 / 256.0;
const double i16384		= 1.0 / 16384.0;
const double i65536		= 1.0 / 65536.0;
const double i1048576	= 1.0 / 1048576.0;
const double i8			= 1.0 / 8.0;
const double i32		= 1.0 / 32.0;
const double i1024		= 1.0 / 1024.0;
const double i4096		= 1.0 / 4096.0;
const double i131072	= 1.0 / 131072.0;
const double i524288	= 1.0 / 524288.0;
const double i8388608	= 1.0 / 8388608.0;
const double i3072		= 1.0 / 3072.0;
const double i262144	= 1.0 / 262144.0;
const double i5242880	= 1.0 / 5242880.0;
const double i1310720	= 1.0 / 1310720.0;

//////////////////////////////////////////////////////////////////////////
//投影到平面
//高斯投影正算
//输入   :a (椭球长半轴 ,类型double ,范围 a>0)
//        f (椭球扁率倒数,类型double ,范围 f>0.5)
//        L0 中央子午线经度,类型 double,范围0=<L0<PI*2       )
//        B L(投影点(经度,纬度),类型 double,范围0<=|B|<=PI/2, 0=<L<=PI*2     )
//输出   :x,y(投影平面坐标(x,y),类型 double *, 范围 x,y为实数)
//        deform(投影变形系数结构,类型tagDEFORM *)
DEUPROJECT_API void Gauss_bl_xy(projPJ  pj_,double lo,double b,double l,double &x,double &y)
{
	PJ* pj = (PJ*)pj_;
	//lo，中央子午线
	//lo -= 1.5 * DEG_TO_RAD; 
	//x = X + 0.5*Nt*M^2 + (1/24)*Nt*m^4*(5-t^2+9*et2+4*et2*et2) + ....

	double B = b;				//纬度（弧度）
	double LO=(l - lo);			//经度差（弧度），l-lo;
	double X;					//克拉索夫斯基椭球中央子午线弧长，计算方法未知
								//X= a(1-e^2) ( _A arcB - _B sin2B + _C sin4B -_Dsin6B +_Esin8B - _F sin10B + _G sin12B )
	double N = pj->get_N(B);	//N = C/sqrt(1+e'^2 cosB ^2) = C/sqrt(1 + et2 );
	double t = tan(B);			//t = tan(B);
	double cosB = cos(B);
	double sinB = sin(B);
	double e2 = pj->es ;
	double et2 = (e2) / (1 - ( e2 )) * pow( cosB ,2);// et2 = lamda^2 = e'2 * cosB^2;

	// 中央子午线弧长 	
	X = MeridianArcLength(pj->a,pj->es,B) ;

	double m;		//m = cosB * LO * iPI ;
	m = cosB * LO ;	// * iPI;

	double x1,x2,x3;
	x1= N * t * pow(m,2) * 0.5;
	x2= N * t * pow(m,4) * (5.0 - pow(t,2) + 9.0 * et2 + 4 * pow(et2,2)) * (i24);
	x3=	N * t * pow(m,6) * (61 - 58 * pow(t,2) +pow (t,4) ) * (i720);

	//double ttt =(5.0 - pow(t,2) + 9.0 * et2 + 4 * pow(et2,2));
	
	// 返回参数
	x = X + x1 + x2 + x3;
	y = N * ( m 
		+ (1.0 - pow(t,2) + et2)*pow(m,3) * ( i6 ) 
		+ (5.0 - 18.0 * pow(t,2) + pow(t,4) + 14.0 * et2 - 58.0 * et2 * pow(t,2)) * pow(m,5) * (i120) );

	return;
}

//高斯投影反算
//输入   :a (椭球长半轴 ,类型double ,范围 a>0)
//        f (椭球扁率,类型double )
//        L0 度带起始经度,类型 double,范围0<|B0|<PI/2, 0=<L0<=PI*2        )
//        x,y(投影平面坐标(x,y),类型 double, 范围 x,y为实数)
//输出   :B L(投影点(经度,纬度),类型 double *,范围0<=|B|<=PI/2, 0=<L<=PI*2   )
DEUPROJECT_API void Gauss_xy_bl(projPJ  pj_,double lo,double x,double y,double &b,double &l)
{
	PJ* pj = (PJ*)pj_;
	//lo,度带起始经度
	//lo -= 1.5*DEG_TO_RAD;
	double Bf = CalcuBf(pj->a,pj->es,x);
	
	//由B 得到t,M,N,et2
	double t = tan(Bf);				//t = tan(B);
	double cosB = cos(Bf);
	double sinB = sin(Bf);
	double et2 = pj->get_et2(cosB); //et2 = lamda^2 = e'2 * cosB^2;
	
	double 	N = pj->get_N(Bf) ;
	double	M = pj->get_M(Bf) ;

	double Y = y ;
	const double i2M = 1.0 /(2.0*M);
	double n = Y/N;

	// 返回参数
	b = Bf - t * i2M  * Y * n
		+ t * i2M  * Y * pow( n,3 ) * (5.0 + 3.0 * pow(t,2) + et2 - 9.0 * et2 * pow(t , 2) ) * i12 
		- t * i2M  * Y * pow( n,5 ) * (61.0+ 90.0 * pow(t,2) + 45.0 * pow(t,4)) * i360;

	l =  (1.0 / cosB) * n 
		-(1.0 / cosB) * pow(n,3) * ( 1 + 2 * pow(t,2) + et2) * i6 
		+(1.0 / cosB) * pow(n,5) * ( 5 + 28 * pow(t,2) + 24 * pow(t,4) + 6 * et2 + 8 * et2 * pow(t,2)) * i120 ;

	b = b ;
	l = l + lo ;

	return;
}

// 中央经线弧长
double MeridianArcLength(double a , double e2 , double B, int N )
{
	double X = 0;
	double _A,_B,_C,_D,_E,_F,_G;

	_A = 1 + e2 * 3.0 * i4  + pow(e2,2) * 45.0 * i64 + pow(e2,3) * 175.0 * i256 + pow(e2,4) * 11025.0 * i16384 + pow(e2,5) * 43659.0 * i65536 + pow(e2,6) * 693693.0 * i1048576 ;

	_B = e2 * 3.0 * i8 + pow(e2,2) * 15.0 * i32 + pow(e2,3) * 525.0 * i1024 + pow(e2,4) * 2205.0 * i4096 + + pow(e2,5) * 72765.0 * i131072 + pow(e2,6) * 297297.0 * i524288 ;

	_C = pow(e2,2) * 15.0 * i256 + pow(e2,3) * 105.0 * i1024 + pow(e2,4) * 2205.0 * i16384 + pow(e2,5) * 10395.0 * i65536 + pow(e2,6) * 1486485.0 * i8388608 ;

	_D = pow(e2,3) * 35.0 * i3072 + pow(e2,4) * 105.0 * i4096 + pow(e2,5) * 10395.0 * i262144 + pow(e2,6) * 55055.0 * i1048576 ;

	_E = pow(e2,4) * 315.0 * i131072 + pow(e2,5) * 3465.0 * i524288 + pow(e2,6) * 99099.0 * i8388608 ;

	_F = pow(e2,5) * 693.0 * i1310720 + pow(e2,6) * 9009.0 * i5242880 ;

	_G = pow(e2,6) * 1001.0 * i8388608;

	double DEFG =   - _D * sin(6*B) + _E * sin(8 * B) - _F * sin(10* B) + _G * sin(12 * B);
	double CC = _C * sin(4.0* B);
	double dd =- _D * sin(6*B);

	//double _X =  ( _A * B - _B * sin(2* B) + _C * sin(4.0* B) /*- _D * sin(6*B) /*+ _E * sin(8 * B) - _F * sin(10* B) + _G * sin(12 * B) */ );
	double _X =  ( _A * B - _B * sin(2* B) + _C * sin(4.0* B) - _D * sin(6*B) + _E * sin(8 * B) - _F * sin(10* B) + _G * sin(12 * B)  );

	X = a * (1 -e2) * _X ;
	
	return X;
}

double CalcuBf(double a ,double e2,double x )
{
	//Bf = x/a(1-e2) + B sin 2Bf/a - C sin 4Bf + D sin 6 Bf /A  -E + F -G
	double Bf0;
	double Bf1;

	double Bf;
	double detal_bf = 100;
	double _A,_B,_C,_D,_E,_F,_G;

	_A = 1 + e2 * 3.0 * i4  + pow(e2,2) * 45.0 * i64 + pow(e2,3) * 175.0 * i256 + pow(e2,4) * 11025.0 * i16384 + pow(e2,5) * 43659.0 * i65536 + pow(e2,6) * 693693.0 * i1048576 ;

	_B = e2 * 3.0 * i8 + pow(e2,2) * 15.0 * i32 + pow(e2,3) * 525.0 * i1024 + pow(e2,4) * 2205.0 * i4096 + + pow(e2,5) * 72765.0 * i131072 + pow(e2,6) * 297297.0 * i524288 ;

	_C = pow(e2,2) * 15.0 * i256 + pow(e2,3) * 105.0 * i1024 + pow(e2,4) * 2205.0 * i16384 + pow(e2,5) * 10395.0 * i65536 + pow(e2,6) * 1486485.0 * i8388608 ;

	_D = pow(e2,3) * 35.0 * i3072 + pow(e2,4) * 105.0 * i4096 + pow(e2,5) * 10395.0 * i262144 + pow(e2,6) * 55055.0 * i1048576 ;

	_E = pow(e2,4) * 315.0 * i131072 + pow(e2,5) * 3465.0 * i524288 + pow(e2,6) * 99099.0 * i8388608 ;

	_F = pow(e2,5) * 693.0 * i1310720 + pow(e2,6) * 9009.0 * i5242880 ;

	_G = pow(e2,6) * 1001.0 * i8388608;

	Bf0 = x/(a*(1-e2)*_A );

	const double _iA = 1 / _A ;

	while ( detal_bf > DEL_TOL )
	{		
		Bf1 = _iA * x/(a*(1-e2))  + ( _B * sin(2* Bf0) - _C * sin(4* Bf0) + _D * sin(6*Bf0) - _E * sin(8 * Bf0) + _F * sin(10* Bf0) - _G * sin(12 * Bf0)) * _iA ;

		detal_bf = Bf1 -Bf0;
		//( _B * sin(2* Bf0) - _C * sin(4* Bf0) + _D * sin(6*Bf0) - _E * sin(8 * Bf0) + _F * sin(10* Bf0) - _G * sin(12 * Bf0)) / _A;

		Bf = Bf1;
		Bf0 = Bf1;
	}

	return Bf;
}

//几个重要参数的意义：
//NN卯酉圈曲率半径，测量学里面用N表示
//M为子午线弧长，测量学里用大X表示
//fai为底点纬度，由子午弧长反算公式得到，测量学里用Bf表示
//R为底点所对的曲率半径，测量学里用Nf表示
//#define MAX_ITER 20
//
//struct GAUSS {
//	double C;
//	double K;
//	double e;
//	double ratexp;
//};
//#define EN ((struct GAUSS *)en)
//#define DEL_TOL 1e-14
//static double
//srat(double esinp, double exp) {
//	return(pow((1.-esinp)/(1.+esinp), exp));
//}
//
//void *
//pj_gauss_ini(double e, double phi0, double *chi, double *rc) {
//	double sphi, cphi, es;
//	struct GAUSS *en;
//
//	if ((en = (struct GAUSS *)malloc(sizeof(struct GAUSS))) == NULL)
//		return (NULL);
//	es = e * e;
//	EN->e = e;
//	sphi = sin(phi0);
//	cphi = cos(phi0);  cphi *= cphi;
//	*rc = sqrt(1. - es) / (1. - es * sphi * sphi);
//	EN->C = sqrt(1. + es * cphi * cphi / (1. - es));
//	*chi = asin(sphi / EN->C);
//	EN->ratexp = 0.5 * EN->C * e;
//	EN->K = tan(.5 * *chi + FORTPI) / (
//		pow(tan(.5 * phi0 + FORTPI), EN->C) *
//		srat(EN->e * sphi, EN->ratexp)  );
//	return ((void *)en);
//}
//LP
//pj_gauss(LP elp, const void *en) {
//	LP slp;
//
//	slp.phi = 2. * atan( EN->K *
//		pow(tan(.5 * elp.phi + FORTPI), EN->C) *
//		srat(EN->e * sin(elp.phi), EN->ratexp) ) - HALFPI;
//	slp.lam = EN->C * (elp.lam);
//	return(slp);
//}
//LP
//pj_inv_gauss(LP slp, const void *en) {
//	LP elp;
//	double num;
//	int i;
//
//	elp.lam = slp.lam / EN->C;
//	num = pow(tan(.5 * slp.phi + FORTPI)/EN->K, 1./EN->C);
//	for (i = MAX_ITER; i; --i) {
//		elp.phi = 2. * atan(num * srat(EN->e * sin(slp.phi), -.5 * EN->e))
//			- HALFPI;
//		if (fabs(elp.phi - slp.phi) < DEL_TOL) break;
//		slp.phi = elp.phi;
//	}	
//	/* convergence failed */
//	if (!i)
//		pj_errno = -17;
//	return (elp);
//}