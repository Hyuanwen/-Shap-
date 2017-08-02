#include "stdafx.h"
#include "projects.h"
#include <atltrace.h>
#include "newmat.h"

#define TRACE ATLTRACE

//计算参数
//二维7参数
DEUPROJECT_API int ComputeParams_2D7PBL(int n,double B1[],double L1[],double B2[],double L2[],projPJ  src_,projPJ  des_,double Para[])
{
	PJ*     src   = (PJ*)src_;
	PJ*     des   = (PJ*)des_;
	double* _a    = new double[n*18];
	double* _bVal = new double[n*2];
	if ( _a == NULL || _bVal == NULL)
	{
		return -1;
	}
	for (int i = 0 ; i < n * 18 ; i++)
	{
		_a[i] = 0;
	}
	for (int i = 0 ; i < n * 2 ; i++)
	{
		_bVal[i] = 0;
	}

	// 得到A矩阵
	// 说明：该矩阵为点对数X2行，7列。按行依次存入下面数组	
	//TRACE("\n--------A阵各元素--------\n");
	for (int i=0; i<n; i++)
	{
		double _b=B1[i];          // 纬度
		double _l=L1[i];          // 精度

		double _bb=B2[i]-_b;      // 纬度差
		double _ll=L2[i]-_l;      // 精度差

		double cos_l = cos(_l);
		double sin_l = sin(_l);
		double cos_b = cos(_b);
		double sin_b = sin(_b);
		double tan_l = tan(_l);
		double tan_b = tan(_b);

		double N=src->get_N(_b);   // 卯酉圈曲率半径
		double M=src->get_M(_b);   // 子午圈曲率半径    
		double _es=src->es;		   // 偏心率

		//double _da = src->a - des->a ;
		//double _df = src->f - des->f ;

		_a[18*i]=-RPI*sin_l/(N*cos_b);
		_a[18*i+1]=RPI*cos_l/(N*cos_b);
		_a[18*i+2]=0;
		_a[18*i+3]=tan_b*cos_l;
		_a[18*i+4]=tan_b*sin_l;
		_a[18*i+5]=-1;
		_a[18*i+6]=0;
		_a[18*i+7]=0;
		_a[18*i+8]=0;

		_a[18*i+9]=-RPI*sin_b*cos_l/M;
		_a[18*i+10]=-RPI*sin_b*sin_l/M;
		_a[18*i+11]=RPI*cos_b/M;
		_a[18*i+12]=-sin_l;
		_a[18*i+13]=cos_l;
		_a[18*i+14]=0;
		_a[18*i+15]=-N*_es*sin_b*cos_b*RPI/M;
		_a[18*i+16]=N*_es*sin_b*cos_b*RPI/(M*src->a);
		_a[18*i+17]=(2-_es*sin_b*sin_b)*sin_b*cos_b*RPI/(1-src->f); 

		// 得到b阵    b阵为点对数X2行，1列
		_bVal[2*i]=_ll;
		_bVal[2*i+1]=_bb;//-N*_es*sin_b*cos_b*RPI*_da/(M*des->a)-(2-_es*sin_b*sin_b)*sin_b*cos_b*RPI*_df/(1-src->f);

		//TRACE("\n%f %f %f %f %f %f %f %f %f",_a[18*i],_a[18*i+1],_a[18*i+2],_a[18*i+3],_a[18*i+4],_a[18*i+5],_a[18*i+6],_a[18*i+7],_a[18*i+8]);
		//TRACE("\n%f %f %f %f %f %f %f %f %f",_a[18*i+9],_a[18*i+10],_a[18*i+11],_a[18*i+12],_a[18*i+13],_a[18*i+14],_a[18*i+15],_a[18*i+16],_a[18*i+17]);
	}

	// 求解方程组
	int    _n = n*2;
	Matrix A(_n,9);
	A<<_a;

	// 求AT方阵
	Matrix AT(9,_n);
	AT=A.t();
	
	// 求AT*A阵
	Matrix ATA(9,9);
	ATA=AT*A;

	// 求ATAi阵
	Matrix iATA(9,9);
	iATA=ATA.i();

	// 求单位阵
	Matrix test(9,9);
	test=iATA*ATA;

	// 求B阵
	Matrix B(_n,1);
	B<<_bVal;

	// 求D阵
	Matrix D(9,_n);
	D=iATA*AT;

	// 求V阵
	Matrix V(9,1);
	V=D*B;
	
	// 返回结果
	Para[0]=V(1,1);
	Para[1]=V(2,1);
	Para[2]=V(3,1);
	Para[3]=V(4,1);
	Para[4]=V(5,1);
	Para[5]=V(6,1);
	Para[6]=V(7,1);
	Para[7]=V(8,1);
	Para[8]=V(9,1);

	// 求AT*A方阵
	// 判断是否可逆
	// 两边都左乘AT*A的逆阵
	// 返回结果
	if (_a !=NULL)
	{
		delete[] _a;
	}
	if (_bVal !=NULL)
	{
		delete[] _bVal;
	}

	return 0;
}

//二维四参数平面
DEUPROJECT_API int ComputeParams_2D4Pxy(int n,double x1[],double y1[],double x2[],double y2[],double Para[])
{
	double* _a    = new double[n*8];
	double* _bVal = new double[n*2];
	if ( _a == NULL || _bVal == NULL)
	{
		return -1;
	}
	// 得到A矩阵
	// 说明：该矩阵为点对数X3行，7列。按行依次存入下面数组
	//TRACE("\n--------A阵各元素--------\n");
	for (int i=0; i<n; i++)
	{
		_a[8*i]			=	1;
		_a[8*i+1]		=	0;
		_a[8*i+2]		=	x1[i];
		_a[8*i+3]		=	-y1[i];
		_a[8*i+4]		=	0;
		_a[8*i+5]		=	1;
		_a[8*i+6]		=	y1[i];
		_a[8*i+7]		=	x1[i];
		
		// 得到b阵    b阵为点对数X3行，1列
		_bVal[2*i]		=	x2[i];
		_bVal[2*i+1]	=	y2[i];
	}

	// 求解方程组
	int    _n = n*2;
	Matrix A(_n,4);
	A<<_a;
	/*for (int j=0; j<_n; j++)
	{
		A.row(j+1)<<_a[7*j]<<_a[7*j+1]<<_a[7*j+2]<<_a[7*j+3]<<_a[7*j+4]<<_a[7*j+5]<<_a[7*j+6];
	}*/

	// 求AT阵
	Matrix AT(4,_n);
	AT=A.t();
	
	// 求AT*A方阵
	Matrix ATA(4,4);
	ATA=AT*A;
	
	// 求iATA阵
	Matrix iATA(4,4);	
	iATA=ATA.i();
	
	// 求单位阵
	Matrix test(4,4);
	test=iATA*ATA;
	
	// 求B阵
	Matrix B(_n,1);
	B<<_bVal;
	
	// 求D阵
	Matrix D(4,_n);
	D=iATA*AT;
	
	// 求V阵
	Matrix V(4,1);
	V=D*B;
	
	// 返回结果
	Para[0]=V(1,1);
	Para[1]=V(2,1);
	Para[2]=V(3,1);
	Para[3]=V(4,1);

	delete[] _a;
	delete[] _bVal;

	return 0;
}

//3维布尔莎
DEUPROJECT_API int ComputeParams_3D7PBursa(int n,double X1[],double Y1[],double Z1[],double X2[],double Y2[],double Z2[],double Para[])
{
	double* _a    = new double[n*21];
	double* _bVal = new double[n*3];
	if ( _a == NULL || _bVal == NULL)
	{
		return -1;
	}

	// 得到A矩阵
	// 说明：该矩阵为点对数X3行，7列。按行依次存入下面数组
	////TRACE("\n--------A阵各元素--------\n");
	for (int i=0; i<n; i++)
	{
		_a[21*i]=1;
		_a[21*i+1]=0;
		_a[21*i+2]=0;
		_a[21*i+3]=0;
		_a[21*i+4]=-1*Z1[i];
		_a[21*i+5]=Y1[i];
		_a[21*i+6]=X1[i];
		_a[21*i+7]=0;
		_a[21*i+8]=1;
		_a[21*i+9]=0;
		_a[21*i+10]=Z1[i];
		_a[21*i+11]=0;
		_a[21*i+12]=-1*X1[i];
		_a[21*i+13]=Y1[i];
		_a[21*i+14]=0;
		_a[21*i+15]=0;
		_a[21*i+16]=1;
		_a[21*i+17]=-1*Y1[i];
		_a[21*i+18]=X1[i];
		_a[21*i+19]=0;
		_a[21*i+20]=Z1[i];

		// 得到b阵    b阵为点对数X3行，1列
		_bVal[3*i]=X2[i]-X1[i];
		_bVal[3*i+1]=Y2[i]-Y1[i];
		_bVal[3*i+2]=Z2[i]-Z1[i];
	}

	// 求解方程组
	int    _n=n*3;
	Matrix A(_n,7);
	A<<_a;
	/*for (int j=0; j<_n; j++)
	{
		A.row(j+1)<<_a[7*j]<<_a[7*j+1]<<_a[7*j+2]<<_a[7*j+3]<<_a[7*j+4]<<_a[7*j+5]<<_a[7*j+6];
	}*/

	// 求AT阵
	Matrix AT(7,_n);
	AT=A.t();
	
	// 求AT*A方阵
	Matrix ATA(7,7);
	ATA=AT*A;
	
	// 求iATA阵
	Matrix iATA(7,7);
	iATA=ATA.i();
	
	// 求单位阵
	Matrix test(7,7);
	test=iATA*ATA;
	
	// 求B阵
	Matrix B(_n,1);
	B<<_bVal;

	// 求D阵
	Matrix D(7,_n);
	D=iATA*AT;
	
	// 求V阵
	Matrix V(7,1);
	V=D*B;
	
	// 返回结果
	Para[0]=V(1,1);
	Para[1]=V(2,1);
	Para[2]=V(3,1);
	Para[3]=V(4,1);
	Para[4]=V(5,1);
	Para[5]=V(6,1);
	Para[6]=V(7,1);

	delete[] _a;
	delete[] _bVal;

	return 0;
}

//三维7参数BLH
DEUPROJECT_API int ComputeParams_3D7PBLH(int n,double B1[],double L1[],double H1[],double B2[],double L2[],double H2[],projPJ  src_,projPJ  des_,double Para[] )
{
	PJ*     src   = (PJ*)src_;
	PJ*     des   = (PJ*)des_;
	double* _a    = new double[n*27];
	double* _bVal = new double[n*3];
	if ( _a == NULL || _bVal == NULL)
	{
		return -1;
	}

	// 得到A矩阵
	// 说明：该矩阵为点对数X3行，7列。按行依次存入下面数组
	for (int i=0; i < n; i++)
	{
		double _b=B1[i];				// 纬度
		double _l=L1[i];				// 经度
		double _h=H1[i];				// 高程

		double _bb=B2[i]-_b;			// 纬度差
		double _ll=L2[i]-_l;			// 精度差
		double _hh=H2[i]-_h;			// 高程差

		double _n=src->get_N(_b);		// 子午圈曲率半径
		double _m=src->get_M(_b);       // 卯酉圈曲率半径
		double _es=src->es;             // 偏心率

		double _da = src->a - des->a ;
		double _df = src->f - des->f ;

		double sin_l = sin(_l);
		double cos_l = cos(_l);
		double sin_b = sin(_b);
		double cos_b = cos(_b);
		double tan_b = tan(_b);

		//_a[21*i]=-RPI*sin(_l)/((_n+_h)*cos(_b));
		//_a[21*i+1]=RPI*cos(_l)/((_n+_h)*cos(_b));
		//_a[21*i+2]=0;							
		///*_a[21*i+3]=tan(_b)*cos(_l);*/				_a[21*i+3]=tan(_b)*cos(_l)*(1 - _n*_es/(_n + _h));
		///*_a[21*i+4]=tan(_b)*sin(_l);*/				_a[21*i+4]=tan(_b)*sin(_l)*(1 - _n*_es/(_n + _h));
		//_a[21*i+5]=-1;							
		//_a[21*i+6]=0;							
		//_a[21*i+7]=-RPI*sin(_b)*cos(_l)/(_m+_h);
		//_a[21*i+8]=-RPI*sin(_b)*sin(_l)/(_m+_h);
		//_a[21*i+9]=RPI*cos(_b)/(_m+_h);
		///*_a[21*i+10]=-sin(_l);*/					_a[21*i+10]=-sin(_l) * (_n*(1-_es*sin(_b)*sin(_b))+_h)/(_m + _h);
		///*_a[21*i+11]=cos(_l);*/					_a[21*i+11]=cos(_l) * (_n*(1-_es*sin(_b)*sin(_b))+_h)/(_m + _h);
		//_a[21*i+12]=0;
		//_a[21*i+13]=-_n*_es*sin(_b)*cos(_b)*RPI/(_m+_h);
		//_a[21*i+14]=cos(_b)*cos(_l);
		//_a[21*i+15]=cos(_b)*sin(_l);
		//_a[21*i+16]=sin(_b);
		//_a[21*i+17]=-_n*_es*sin(_b)*cos(_b)*sin(_l)/RPI;
		//_a[21*i+18]=_n*_es*sin(_b)*cos(_b)*cos(_l)/RPI;
		//_a[21*i+19]=0;
		//_a[21*i+20]=_n+_h-_n*_es*sin(_b)*sin(_b);

		//9个参数
		_a[27*i]=-RPI*sin_l/((_n+_h)*cos_b);
		_a[27*i+1]=RPI*cos_l/((_n+_h)*cos_b);
		_a[27*i+2]=0;							
		_a[27*i+3]=tan_b*cos_l;				/*_a[27*i+3]=tan(_b)*cos(_l)*(1 - _n*_es/(_n + _h));*/
		_a[27*i+4]=tan_b*sin_l;				/*_a[27*i+4]=tan(_b)*sin(_l)*(1 - _n*_es/(_n + _h));*/
		_a[27*i+5]=-1;							
		_a[27*i+6]=0;		
		_a[27*i+7]=0;
		_a[27*i+8]=0; 

		_a[27*i+9]=-RPI*sin_b*cos_l/(_m+_h);
		_a[27*i+10]=-RPI*sin_b*sin_l/(_m+_h);
		_a[27*i+11]=RPI*cos_b/(_m+_h);
		_a[27*i+12]=-sin_l;					/*_a[27*i+12]=-sin(_l) * (_n*(1-_es*sin(_b)*sin(_b))+_h)/(_m + _h);*/
		_a[27*i+13]=cos_l;					/*_a[27*i+13]=cos(_l) * (_n*(1-_es*sin(_b)*sin(_b))+_h)/(_m + _h);*/
		_a[27*i+14]=0;
		_a[27*i+15]=-_n*_es*sin_b*cos_b*RPI/(_m+_h);
		_a[27*i+16]=_n*_es*sin_b*cos_b*RPI/((_m+_h)*src->a);
		_a[27*i+17]=_m*(2-_es*sin_b*sin_b)*sin_b*cos_b*RPI/((_m+_h)*(1-src->f)); 
		
		_a[27*i+18]=cos_b*cos_l;
		_a[27*i+19]=cos_b*sin_l;
		_a[27*i+20]=sin_b;
		_a[27*i+21]=-_n*_es*sin_b*cos_b*sin_l/RPI;
		_a[27*i+22]=_n*_es*sin_b*cos_b*cos_l/RPI;
		_a[27*i+23]=0;
		_a[27*i+24]=_n+_h-_n*_es*sin_b*sin_b;
		_a[27*i+25]=-_n*(1-_es*sin_b*sin_b)/src->a;
		_a[27*i+26]=_m*(1-_es*sin_b*sin_b)*sin_b*sin_b/(1-src->f);

		// 得到b阵    b阵为点对数X3行，1列
		_bVal[3*i]=_ll;
		_bVal[3*i+1]=_bb;//-_n*_es*sin(_b)*cos(_b)*RPI*_da/((_m+_h)*src->a)-_m*(2-_es*sin(_b)*sin(_b))*sin(_b)*cos(_b)*RPI*_df/((_m+_h)*(1-src->f));
		_bVal[3*i+2]=_hh;//+_n*(1-_es*sin(_b)*sin(_b))*_da/src->a-_df*_m*(1-_es*sin(_b)*sin(_b))*sin(_b)/(1-src->f);
	}

	// 求解方程组
	int _n=n*3;
	Matrix A(_n,9);
	A<<_a;
	/*for (int j=0; j<_n; j++)
	{
		A.row(j+1)<<_a[7*j]<<_a[7*j+1]<<_a[7*j+2]<<_a[7*j+3]<<_a[7*j+4]<<_a[7*j+5]<<_a[7*j+6];
	}*/

	// AT阵
	Matrix AT(9,_n);
	AT=A.t();

	// 求AT*A方阵
	Matrix ATA(9,9);
	ATA=AT*A;

	// iATA阵
	Matrix iATA(9,9);
	iATA=ATA.i();
	
	// 单位阵
	Matrix test(9,9);
	test=iATA*ATA;
	
	// B阵
	Matrix B(_n,1);
	B<<_bVal;

	// D阵
	Matrix D(9,_n);
	D=iATA*AT;
	
	// V阵
	Matrix V(9,1);
	V=D*B;
	
	// 返回结果
	Para[0]=V(1,1);
	Para[1]=V(2,1);
	Para[2]=V(3,1);
	Para[3]=V(4,1);
	Para[4]=V(5,1);
	Para[5]=V(6,1);
	Para[6]=V(7,1);
	Para[7]=V(8,1);
	Para[8]=V(9,1);

	delete[] _a;
	delete[] _bVal;
	
	return 0;
}

DEUPROJECT_API int ComputeParams_Polynomial1(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] )
{
	double *arr_A = new double[12*n];
	double *arr_B = new double[2*n];

	for (int i = 0 ; i < 12*n ; i++)
	{
		arr_A[i]	=	0;
	}
	for (int i = 0 ; i < 2*n ; i++)
	{
		arr_B[i]	=	0;
	}

	//AX=B,输入A(2，6),B(2,1)
	for (int i = 0 ; i < n ; i++)
	{
		arr_A[0+12*i]	=	1		;
		arr_A[1+12*i]	=	X1[i]	;
		arr_A[2+12*i]	=	Y1[i]	;
		arr_A[3+12*i]	=	0		;
		arr_A[4+12*i]	=	0		;
		arr_A[5+12*i]	=	0		;

		arr_A[6+12*i]	=	0		;
		arr_A[7+12*i]	=	0		;
		arr_A[8+12*i]	=	0		;
		arr_A[9+12*i]	=	1		;
		arr_A[10+12*i]	=	X1[i]	;
		arr_A[11+12*i]	=	Y1[i]	;
		
		arr_B[0+2*i]	=	X2[i] - X1[i];
		arr_B[1+2*i]	=	Y2[i] - Y1[i];
	}

	// 求解方程组
	int _n=n*2;
	Matrix A(_n,6);
	A<<arr_A;

	// B阵
	Matrix B(_n,1);
	B<<arr_B;

	// 求AT
	Matrix AT(6,_n);
	AT = A.t();

	// 求AT*A
	Matrix ATA(6,6);
	ATA	= AT*A;

	// 求iATA
	Matrix iATA(6,6);
	iATA = ATA.i();

	//验证单位阵
	Matrix testMat(6,6);
	testMat	= ATA * iATA;

	// D阵
	Matrix D(6,_n);
	D =	iATA * AT ;

	// X阵
	Matrix X(6,1);
	X = D * B;

	// 返回结果
	Para[0]	=	X(1,1);
	Para[1]	=	X(2,1);
	Para[2]	=	X(3,1);
	Para[3]	=	X(4,1);
	Para[4]	=	X(5,1);
	Para[5]	=	X(6,1);

	if (arr_A != NULL)
	{
		delete[] arr_A;
	}
	if (arr_B != NULL)
	{
		delete[] arr_B;
	}
	
	return 0;
}

DEUPROJECT_API int ComputeParams_Polynomial2(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] )
{
	double *arr_A = new double[24*n];
	double *arr_B = new double[2*n];

	for (int i = 0 ; i < 20*n ; i++)
	{
		arr_A[i]	=	0;
	}
	for (int i = 0 ; i < 2*n ; i++)
	{
		arr_B[i]	=	0;
	}

	//AX=B,输入A(2，12),B(2,1)
	for (int i = 0 ; i < n ; i++)
	{
		arr_A[0+24*i]	=	1		;
		arr_A[1+24*i]	=	X1[i]	;
		arr_A[2+24*i]	=	Y1[i]	;
		arr_A[3+24*i]	=	X1[i] * Y1[i]		;
		arr_A[4+24*i]	=	X1[i] * X1[i]		;
		arr_A[5+24*i]	=	Y1[i] * Y1[i]		;

		arr_A[6+24*i]	=	0		;
		arr_A[7+24*i]	=	0		;
		arr_A[8+24*i]	=	0		;
		arr_A[9+24*i]	=	0		;
		arr_A[10+24*i]	=	0		;
		arr_A[11+24*i]	=	0		;

		arr_A[12+24*i]	=	0		;
		arr_A[13+24*i]	=	0		;
		arr_A[14+24*i]	=	0		;
		arr_A[15+24*i]	=	0		;
		arr_A[16+24*i]	=	0		;
		arr_A[17+24*i]	=	0		;

		arr_A[18+24*i]	=	1		;
		arr_A[19+24*i]	=	X1[i]		;
		arr_A[20+24*i]	=	Y1[i]		;
		arr_A[21+24*i]	=	X1[i] * Y1[i]		;
		arr_A[22+24*i]	=	X1[i] * X1[i]		;
		arr_A[23+24*i]	=	Y1[i] * Y1[i]		;

		arr_B[0+2*i]	=	X2[i] - X1[i];
		arr_B[1+2*i]	=	Y2[i] - Y1[i];
	}

	// 求解方程组
	int _n=n*2;

	// A阵
	Matrix A(_n,12);
	A<<arr_A;

	// B阵
	Matrix B(_n,1);
	B<<arr_B;

	// 求AT阵
	Matrix AT(12,_n);
	AT	=	A.t();
	
	// 求AT*A阵
	Matrix ATA(12,12);
	ATA	= AT*A;

	// 求iATA阵
	Matrix iATA(12,12);
	iATA = ATA.i();

	//验证单位阵
	Matrix testMat(12,12);
	testMat	= ATA * iATA;

	// D阵,D=iATA*AT;
	Matrix D(12,_n);
	D =	iATA * AT ;

	// X阵
	Matrix X(12,1);
	X = D * B;

	// 返回结果
	Para[0]	=	X(1,1);
	Para[1]	=	X(2,1);
	Para[2]	=	X(3,1);
	Para[3]	=	X(4,1);
	Para[4]	=	X(5,1);
	Para[5]	=	X(6,1);
	Para[6]	=	X(7,1);
	Para[7]	=	X(8,1);
	Para[8]	=	X(9,1);
	Para[9]	=	X(10,1);
	Para[10]	=	X(11,1);
	Para[11]	=	X(12,1);

	if (arr_A != NULL)
	{
		delete[] arr_A;
	}
	if (arr_B != NULL)
	{
		delete[] arr_B;
	}

	return 0;
}

DEUPROJECT_API int ComputeParams_Polynomial3(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] )
{
	double *arr_A = new double[40*n];
	double *arr_B = new double[2*n];

	for (int i = 0 ; i < 40*n ; i++)
	{
		arr_A[i]	=	0;
	}
	for (int i = 0 ; i < 2*n ; i++)
	{
		arr_B[i]	=	0;
	}

	//AX=B,输入A(2，20),B(2,1)
	for (int i = 0 ; i < n ; i++)
	{
		arr_A[0+40*i]	=	1		;
		arr_A[1+40*i]	=	X1[i]	;
		arr_A[2+40*i]	=	Y1[i]	;
		arr_A[3+40*i]	=	X1[i] * X1[i]		;
		arr_A[4+40*i]	=	X1[i] * Y1[i]		;
		arr_A[5+40*i]	=	Y1[i] * Y1[i]		;
		arr_A[6+40*i]	=	X1[i] * X1[i] * X1[i]		;
		arr_A[7+40*i]	=	X1[i] * X1[i] * Y1[i]		;
		arr_A[8+40*i]	=	X1[i] * Y1[i] * Y1[i]		;
		arr_A[9+40*i]	=	Y1[i] * Y1[i] * Y1[i]		;
		arr_A[10+40*i]	=	0		;
		arr_A[11+40*i]	=	0		;
		arr_A[12+40*i]	=	0		;
		arr_A[13+40*i]	=	0		;
		arr_A[14+40*i]	=	0		;
		arr_A[15+40*i]	=	0		;
		arr_A[16+40*i]	=	0		;
		arr_A[17+40*i]	=	0		;
		arr_A[18+40*i]	=	0		;
		arr_A[19+40*i]	=	0		;
		arr_A[20+40*i]	=	0		;
		arr_A[21+40*i]	=	0		;
		arr_A[22+40*i]	=	0		;
		arr_A[23+40*i]	=	0		;
		arr_A[24+40*i]	=	0		;
		arr_A[25+40*i]	=	0		;
		arr_A[26+40*i]	=	0		;
		arr_A[27+40*i]	=	0		;
		arr_A[28+40*i]	=	0		;
		arr_A[29+40*i]	=	0		;
		arr_A[30+40*i]	=	1		;
		arr_A[31+40*i]	=	X1[i]		;
		arr_A[32+40*i]	=	Y1[i]		;
		arr_A[33+40*i]	=	X1[i] * X1[i]		;
		arr_A[34+40*i]	=	X1[i] * Y1[i]		;
		arr_A[35+40*i]	=	Y1[i] * Y1[i] 		;
		arr_A[36+40*i]	=	X1[i] * X1[i] * X1[i]		;
		arr_A[37+40*i]	=	X1[i] * X1[i] * Y1[i]		;
		arr_A[38+40*i]	=	X1[i] * Y1[i] * Y1[i]		;
		arr_A[39+40*i]	=	Y1[i] * Y1[i] * Y1[i]		;
		
		arr_B[0+2*i]	=	X2[i] - X1[i];
		arr_B[1+2*i]	=	Y2[i] - Y1[i];
	}

	// 求解方程组
	int _n=n*2;

	// A阵
	Matrix A(_n,20);
	A<<arr_A;

	// B阵
	Matrix B(_n,1);
	B<<arr_B;

	// 求AT
	Matrix AT(20,_n);
	AT = A.t();

	// 求AT*A
	Matrix ATA(20,20);
	ATA	= AT*A;

	// 求iATA
	Matrix iATA(20,20);
	iATA = ATA.i();

	// 验证单位阵
	Matrix testMat(20,20);
	testMat	= ATA * iATA;

	// D阵,D=iATA*AT;
	Matrix D(20,_n);
	D =	iATA * AT ;

	// X阵
	Matrix X(20,1);
	X	= D * B;

	// 返回结果
	Para[0]	=	X(1,1);
	Para[1]	=	X(2,1);
	Para[2]	=	X(3,1);
	Para[3]	=	X(4,1);
	Para[4]	=	X(5,1);
	Para[5]	=	X(6,1);
	Para[6]	=	X(7,1);
	Para[7]	=	X(8,1);
	Para[8]	=	X(9,1);
	Para[9]	=	X(10,1);
	Para[10]	=	X(11,1);
	Para[11]	=	X(12,1);
	Para[12]	=	X(13,1);
	Para[13]	=	X(14,1);
	Para[14]	=	X(15,1);
	Para[15]	=	X(16,1);
	Para[16]	=	X(17,1);
	Para[17]	=	X(18,1);
	Para[18]	=	X(19,1);
	Para[19]	=	X(20,1);
	
	if (arr_A != NULL)
	{
		delete[] arr_A;
	}
	if (arr_B != NULL)
	{
		delete[] arr_B;
	}

	return 0;
}

DEUPROJECT_API int ComputeParams_Polynomial4(int n,double X1[],double Y1[],double X2[],double Y2[],double Para[] )
{
	double *arr_A = new double[60*n];
	double *arr_B = new double[2*n];

	for (int i = 0 ; i < 60*n ; i++)
	{
		arr_A[i]	=	0;
	}
	for (int i = 0 ; i < 2*n ; i++)
	{
		arr_B[i]	=	0;
	}

	//AX=B,输入A(2，30),B(2,1)
	for (int i = 0 ; i < n ; i++)
	{
		arr_A[0+60*i]	=	1		;
		arr_A[1+60*i]	=	X1[i]	;
		arr_A[2+60*i]	=	Y1[i]	;
		arr_A[3+60*i]	=	X1[i] * Y1[i]		;
		arr_A[4+60*i]	=	X1[i] * X1[i]		;
		arr_A[5+60*i]	=	Y1[i] * Y1[i]		;
		arr_A[6+60*i]	=	Y1[i] * Y1[i] * Y1[i]		;
		arr_A[7+60*i]	=	Y1[i] * Y1[i] * Y1[i]		;
		arr_A[8+60*i]	=	Y1[i] * Y1[i] * Y1[i]		;
		arr_A[9+60*i]	=	Y1[i] * Y1[i] * Y1[i]		;
		arr_A[10+60*i]	=	Y1[i] * Y1[i] * Y1[i] * Y1[i]		;
		arr_A[11+60*i]	=	Y1[i] * Y1[i] * Y1[i] * Y1[i]		;
		arr_A[12+60*i]	=	Y1[i] * Y1[i] * Y1[i] * Y1[i]		;
		arr_A[13+60*i]	=	Y1[i] * Y1[i] * Y1[i] * Y1[i]		;
		arr_A[14+60*i]	=	Y1[i] * Y1[i] * Y1[i] * Y1[i]		;
		arr_A[15+60*i]	=	0		;
		arr_A[16+60*i]	=	0		;
		arr_A[17+60*i]	=	0		;
		arr_A[18+60*i]	=	0		;
		arr_A[19+60*i]	=	0		;
		arr_A[20+60*i]	=	0		;
		arr_A[21+60*i]	=	0		;
		arr_A[22+60*i]	=	0		;
		arr_A[23+60*i]	=	0		;
		arr_A[24+60*i]	=	0		;
		arr_A[25+60*i]	=	0		;
		arr_A[26+60*i]	=	0		;
		arr_A[27+60*i]	=	0		;
		arr_A[28+60*i]	=	0		;
		arr_A[29+60*i]	=	0		;
		arr_A[30+60*i]	=	0		;
		arr_A[31+60*i]	=	0		;
		arr_A[32+60*i]	=	0		;
		arr_A[33+60*i]	=	0		;
		arr_A[34+60*i]	=	0		;
		arr_A[35+60*i]	=	0		;
		arr_A[36+60*i]	=	0		;
		arr_A[37+60*i]	=	0		;
		arr_A[38+60*i]	=	0		;
		arr_A[39+60*i]	=	0		;
		arr_A[40+60*i]	=	0		;
		arr_A[41+60*i]	=	0		;
		arr_A[42+60*i]	=	0		;
		arr_A[43+60*i]	=	0		;
		arr_A[44+60*i]	=	0		;
		arr_A[45+60*i]	=	1		;
		arr_A[46+60*i]	=	X1[i] 	;
		arr_A[47+60*i]	=	Y1[i] 	;
		arr_A[48+60*i]	=	X1[i] * X1[i]		;
		arr_A[49+60*i]	=	X1[i] * Y1[i]		;
		arr_A[50+60*i]	=	Y1[i] * Y1[i] 		;
		arr_A[51+60*i]	=	X1[i] * X1[i] * X1[i]		;
		arr_A[52+60*i]	=	X1[i] * X1[i] * Y1[i] 		;
		arr_A[53+60*i]	=	X1[i] * Y1[i] * Y1[i] 		;
		arr_A[54+60*i]	=	Y1[i] * Y1[i] * Y1[i] 		;
		arr_A[55+60*i]	=	X1[i] * X1[i] * X1[i] * X1[i]		;
		arr_A[56+60*i]	=	X1[i] * X1[i] * X1[i] * Y1[i]		;
		arr_A[57+60*i]	=	X1[i] * X1[i] * Y1[i] * Y1[i]		;
		arr_A[58+60*i]	=	X1[i] * Y1[i] * Y1[i] * Y1[i]		;
		arr_A[59+60*i]	=	Y1[i] * Y1[i] * Y1[i] * Y1[i]		;

		arr_B[0+2*i]	=	X2[i] - X1[i];
		arr_B[1+2*i]	=	Y2[i] - Y1[i];
	}

	// 求解方程组
	int _n=n*2;

	// A阵
	Matrix A(_n,30);
	A<<arr_A;

	// B阵
	Matrix B(_n,1);
	B<<arr_B;

	// 求AT
	Matrix AT(30,_n);
	AT	=	A.t();

	// 求AT*A
	Matrix ATA(30,30);
	ATA	=	AT*A;

	// 求iATA
	Matrix iATA(30,30);
	iATA	=	ATA.i();

	// 验证单位阵
	Matrix testMat(30,30);
	testMat	=	ATA * iATA;

	// D阵，D=iATA*AT;
	Matrix D(30,_n);
	D	=	iATA * AT ;

	// X阵
	Matrix X(30,1);
	X	= D * B;

	//返回结果
	Para[0]	=	X(1,1);
	Para[1]	=	X(2,1);
	Para[2]	=	X(3,1);
	Para[3]	=	X(4,1);
	Para[4]	=	X(5,1);
	Para[5]	=	X(6,1);
	Para[6]	=	X(7,1);
	Para[7]	=	X(8,1);
	Para[8]	=	X(9,1);
	Para[9]	=	X(10,1);
	Para[10]	=	X(11,1);
	Para[11]	=	X(12,1);
	Para[12]	=	X(13,1);
	Para[13]	=	X(14,1);
	Para[14]	=	X(15,1);
	Para[15]	=	X(16,1);
	Para[16]	=	X(17,1);
	Para[17]	=	X(18,1);
	Para[18]	=	X(19,1);
	Para[19]	=	X(20,1);
	Para[20]	=	X(21,1);
	Para[21]	=	X(22,1);
	Para[22]	=	X(23,1);
	Para[23]	=	X(24,1);
	Para[25]	=	X(26,1);
	Para[26]	=	X(27,1);
	Para[27]	=	X(28,1);
	Para[28]	=	X(29,1);
	Para[29]	=	X(30,1);

	if (arr_A != NULL)
	{
		delete[] arr_A;
	}
	if (arr_B != NULL)
	{
		delete[] arr_B;
	}

	return 0;
}
