#include "StdAfx.h"
#include "deulib.h"

using namespace std;

CGrid::CGrid(void)
{
}

CGrid::~CGrid(void)
{
}

//各个比例尺下的经度差和纬度差
const double dbdetalXY[8][2] = {
							{6,4},
							{3,2},
							{1.5,1},
							{1.0/2.0,1.0/3.0},
							{1.0/4.0,1.0/6.0},
							{1.0/8.0,1.0/12.0},
							{1.0/16.0,1.0/24.0},
							{1.0/32.0,1.0/48.0},
						};

//enum __COORDTYPE
//{
//	UNKNOWN,
//	GEODETIC,
//	GEOCENTRIC,
//	PLANE
//};

//计算图幅号
void CalculateFrameByPoint( double x ,double y,int coordtype , char Scale ,char * szFrame )
{//xy单位度 ,x 维度，y精度
	
	int a(0) ,b(0),c(0),d(0) ;

	a = (int)( x / 4 ) + 1;
	b = (int)( y / 6 ) + 31;

	//Scale = D
	double dx(0.33333333333) ,dy(0.5) ;
	//double dx(2) ,dy(3) ;

	c = 4 / dx - (int)(  fmod( x , 4 ) / dx ) ;
	d = (int)( fmod(y , 6) /dy) + 1 ;

	char chA[2];
	chA[0] = num2letter( a );
	chA[1] = '\0';

	char chC[3] ={0};
	itoa( c , chC , 10 ) ;

	char chD[3] = {0};
	itoa( d , chD , 10 ) ;

	sprintf( szFrame , "%s%02d%s%03d%03d" , chA , b , "D" , c ,d ) ;

	//delete chA;
	return ;
}

//根据图幅号计算4个角点坐标
void CalculateCoordsByFrame( char * szFrame , int CoordType , double & DB_XN, double & DL_XN,double & DB_XB,double & DL_XB,double & DB_DB,double & DL_DB,double & DB_DN,double & DL_DN  )
{
	//图幅号获得A,B,C,D,dB,dL
	//int a(0) , b(0) , c(0) , d(0) ;
	//double  dB(0) , dL(0) ;

	char szA =szFrame[0] ;	
	char szB[2] ;

	szB[0] = szFrame[1];
	szB[1] = szFrame[2];

	char szScaleCode = szFrame[3];
	char szC[3]  ;
	memcpy( szC , szFrame+4 , 3); 

	char szD[3]  ;
	memcpy( szD , szFrame+7 , 3); 

	double a(0),b(0),c(0),d(0),detalX(0),detalY(0);
	a = letter2num((const char )szA);
	b = atoi((const char *)&szB);
	c = atoi((const char *)&szC);
	d = atoi((const char *)&szD);

	int iScaleCode = letter2num( (const char)szScaleCode ) ;

	//GetDetalXY( int iScaleCode , double & detalX , double & detalY );
	GetDetalXY(  iScaleCode ,  detalY ,  detalX );
	
	DL_XN = ( b - 31 ) * 6 + ( d - 1 ) * detalY ;
	DB_XN = ( a - 1 ) * 4 + ( 4 / detalX - c ) * detalX ;

	DB_XB = DB_XN + detalX ;
	DL_XB = DL_XN ;
	
	DB_DB = DB_XN + detalX ;
	DL_DB = DL_XN + detalY ;
	
	DB_DN = DB_XN ;
	DL_DN = DL_XN + detalY ;

	return ;
}

//根据比例尺获得经度差和纬度差
void GetDetalXY( int iScaleCode , double & detalX , double & detalY )
{
	detalX =  dbdetalXY[iScaleCode - 1][0];
	detalY =  dbdetalXY[iScaleCode - 1][1];
}

void DeuLoadLibrary()
{
	///*HMODULE*/ g_hCoordsTransDll = LoadLibrary("CoordsTransSanXi.dll");

	////山西
	//char szDLL[200] = "CoordsTransSanXi.dll";
	//char szSH[10] = "14"  ;
	//char PWD[200] = "lyjfysxyht197021" ;

	//山东
	//char szDLL[200] = "CoordsTransShanDong.dll";
	//char szSH[10] = "37"  ;
	//char PWD[200] = "FGopwegT^IObvCNP" ;

	//山东84
	char szDLL84[200] = "CoordsTransShanDongET.dll";

	//浙江
	char szDLL[200] = "CoordsTransZheJiang.dll";
	char szSH[10] = "33"  ;
	char PWD[200] = "lyjfyZjyht197021" ;

	fun_GridDLL( szDLL , szSH , PWD );
	fun_GridDLL( szDLL84 , szSH , PWD );
}

void DeuLoadGridData()
{
	//vector<vector<string>> vec_vec_tab_list;
	//g_vec_vec_GridList_54_2000 = DeuReadFile("C:\\Program Files\\Deu2000\\tfgzlgeo_detic54.txt");
	//g_vec_vec_GridList_80_2000 = DeuReadFile("C:\\Program Files\\Deu2000\\tfgzlgeo_detic80.txt");
	//g_vec_vec_GridList_84_2000 = DeuReadFile("C:\\Program Files\\Deu2000\\tfgzlgeo_detic2000.txt");
}

void fun_GridDLL( char * szDLL , char * szSH , char * PWD)
{
	CString strTmp = _T("");

	strTmp.Format(_T("%s"), szDLL);
	HMODULE hDll = LoadLibrary(strTmp);
	//HMODULE hDll = LoadLibrary(szDLL);

	Func_GetTuFuCoordsTransData _GetTuFuCoordsTransData;

	//Func_0 fun0;
	//fun0 = (Func_0) ::GetProcAddress( hDll, "GetTuFuCoordsTransData" );
	_GetTuFuCoordsTransData = (Func_GetTuFuCoordsTransData)::GetProcAddress( hDll, "GetTuFuCoordsTransData" );

	////计算图幅号
	//double y = 114 + 33.0/60.0 + 45.0 / 3600.0 ;
	//double x = 39 + 22.0 / 60.0 + 30.0 /3600.0 ;	
	//char Scale = 'D'  ;
	//char  szFrame [20];
	//CalculateFrameByPoint( x , y , Scale , szFrame ) ;

	char szFrame[12] = {0}/*"J50B001001"*/;
	double w(0) , s(0);
	//char  szBuff [500]; 

	int FX ( 1 );
	FX = 1 ;
	double DB_XN(0), DL_XN(0), DB_XB(0), DL_XB(0), DB_DB(0), DL_DB(0), DB_DN(0), DL_DN(0);

	for( int a = 5 ; a < 15 ; a++ )
	{//E-N
		for( int b = 43 ; b < 53 ; b++ )
		{//43-53
			for( int c = 1 ; c < 12 ; c++ )
			{//1-12
				for( int d = 1 ; d < 12 ; d++ )
				{//1-12
				 //获得每个图幅号
				strcpy ( szFrame ,  "" );

				char chA[2];
				chA[0] = num2letter( a );
				chA[1] = '\0';

				char chC[3] ={0};
				itoa( c , chC , 10 ) ;

				char chD[3] = {0};
				itoa( d , chD , 10 ) ;

				sprintf( szFrame , "%s%02d%s%03d%03d" , chA , b , "D" , c ,d ) ;

				//fun0("14","lyjfysxyht197021", "J49D011005" , FX, DB_XN, DL_XN, DB_XB, DL_XB, DB_DB, DL_DB, DB_DN, DL_DN);
				//_GetTuFuCoordsTransData("14","lyjfysxyht197021", "J49D011005" , FX, DB_XN, DL_XN, DB_XB, DL_XB, DB_DB, DL_DB, DB_DN, DL_DN);

				for( int iFX = 1 ; iFX < 5 ; iFX++  )
				{
					_GetTuFuCoordsTransData(szSH,PWD, (char *)szFrame , iFX, DB_XN, DL_XN, DB_XB, DL_XB, DB_DB, DL_DB, DB_DN, DL_DN);

					if( DB_XN != 99999 )
					{
						deuGridFormat * _GridFormat = new deuGridFormat();

						strcpy( _GridFormat->szFrame , szFrame ) ;

						_GridFormat->DB_DB = DB_DB ;
						_GridFormat->DB_DN = DB_DN ;
						_GridFormat->DB_XB = DB_XB ;
						_GridFormat->DB_XN = DB_XN ;

						_GridFormat->DL_DB = DL_DB ;
						_GridFormat->DL_DN = DL_DN ;
						_GridFormat->DL_XB = DL_XB ;
						_GridFormat->DL_XN = DL_XN ;

						if(iFX == 1)
							g_vec_vec_GridList_80_2000.push_back( *_GridFormat );

						if(iFX == 2)
							g_vec_vec_GridList_2000_80.push_back( *_GridFormat );

						if(iFX == 3)
							g_vec_vec_GridList_54_2000.push_back( *_GridFormat );

						if(iFX == 4)
							g_vec_vec_GridList_2000_54.push_back( *_GridFormat );

						if(iFX == 5)
							g_vec_vec_GridList_84_2000.push_back( *_GridFormat );

						if(iFX == 6)
							g_vec_vec_GridList_2000_84.push_back( *_GridFormat );

						//sprintf( szBuff , "%s\t%.10f\t%.10f\t%.10f\t%.10f\t%.10f\t%.10f\t%.10f\t%.10f" ,szFrame  , DB_XN, DL_XN, DB_XB, DL_XB, DB_DB, DL_DB, DB_DN, DL_DN ); 
					}
				}

				//CalculateWS(vec_vec_tab_list[i][0].c_str(),w,s);				
				//sprintf( szBuff , "%.10f\t%.10f" , w , s ); 
				//fout<<szBuff<<endl;

				}
			}
		}
	}

	return ;
}

//FX：
//  80到2000坐标转换：1
//  2000到80坐标转换：2
//  54到2000坐标转换：3
//  2000到54坐标转换：4

#if 0
int FetchDetalXY( double x ,double y , int CoordType, const char * szSH  , const char * PWD  , const char * szProName , const char * szFrame , int FX , double & dx ,double & dy  )
{
	CString strTmp;

	strTmp.Format(_T("%s"), szProName);
	if (strTmp == _T("上海"))
	{
		strTmp.Format(_T("CoordsTransShangHai.dll"));
	}
	else if (strTmp == _T("山东"))
	{
		strTmp.Format(_T("CoordsTransShanDong.dll"));
	}
	else if (strTmp == _T("山西"))
	{
		strTmp.Format(_T("CoordsTransSanXi.dll"));
	}
	else if (strTmp == _T("天津"))
	{
		strTmp.Format(_T("CoordsTransTianJin.dll"));
	}
	else if (strTmp == _T("浙江"))
	{
		strTmp.Format(_T("CoordsTransZheJiang.dll"));
	}
	else if (strTmp == _T("陕西"))
	{
		strTmp.Format(_T("CoordsTransShannXi.dll"));
	}
	else
	{
		dx = 0 ;
		dy = 0 ;
		return -1;
	}	
	
	HMODULE hDll = LoadLibrary(strTmp);

	//获得格网的四个角点改正量
	/* del
	HMODULE hDll = g_hCoordsTransDll/*LoadLibrary(L"CoordsTransSanXi.dll")*/;
	
	Func_GetTuFuCoordsTransData _GetTuFuCoordsTransData;

	_GetTuFuCoordsTransData = (Func_GetTuFuCoordsTransData)::GetProcAddress( hDll, "GetTuFuCoordsTransData" );

	double DB_XN(0), DL_XN(0), DB_XB(0), DL_XB(0), DB_DB(0), DL_DB(0), DB_DN(0), DL_DN(0);

	_GetTuFuCoordsTransData( (char *)szSH, (char *)PWD, (char *)szFrame , FX, DB_XN, DL_XN, DB_XB, DL_XB, DB_DB, DL_DB, DB_DN, DL_DN);

	//获得四个角点的坐标值
	double B_XN(0), L_XN(0), B_XB(0), L_XB(0), B_DB(0), L_DB(0), B_DN(0), L_DN(0);
	CalculateCoordsByFrame(  (char *)szFrame , CoordType , B_XN, L_XN, B_XB, L_XB, B_DB, L_DB, B_DN, L_DN  );

	//如果是99999，则无法计算改正量
	if( (DB_XN==99999.0) ||  ( DL_XN==99999.0) || ( DB_XB==99999.0) || ( DL_XB==99999.0) || ( DB_DB==99999.0) || ( DL_DB==99999.0) || ( DB_DN==99999.0) || (DL_DN==99999.0)  )
	{
		dx = 0 ;
		dy = 0 ;
		return -1;
	}

	//计算该点改正量，双线性内插法
	dx = ( ( x - B_XN ) / ( B_XB - B_XN ) ) * ( DB_XB - DB_XN ) + DB_XN ;//单位是秒
	dy = ( ( y - L_XN ) / ( L_DN - L_XN ) ) * ( DL_XB - DL_XN ) + DL_XN ;//单位是秒

	//转化为°
	dx /= 3600.0 ;
	dy /= 3600.0 ;
	
	return 0;
}

#else if 1
int FetchDetalXY( double x ,double y , int CoordType, const char * szSH  , const char * PWD  , const char * szProName , const char * szFrame , int FX , double & dx ,double & dy  )
{
	//获得格网的四个角点改正量
	double DB_XN(0), DL_XN(0), DB_XB(0), DL_XB(0), DB_DB(0), DL_DB(0), DB_DN(0), DL_DN(0);

	//_GetTuFuCoordsTransData("14","lyjfysxyht197021", "J49D011005" , FX, DB_XN, DL_XN, DB_XB, DL_XB, DB_DB, DL_DB, DB_DN, DL_DN);
	_GetTuFuCoordsTransData_FromBuf( (char *)szSH, (char *)"lyjfysxyht197021", (char *)szFrame , FX, DB_XN, DL_XN, DB_XB, DL_XB, DB_DB, DL_DB, DB_DN, DL_DN);

	//获得四个角点的坐标值
	double B_XN(0), L_XN(0), B_XB(0), L_XB(0), B_DB(0), L_DB(0), B_DN(0), L_DN(0);
	CalculateCoordsByFrame(  (char *)szFrame , CoordType , B_XN, L_XN, B_XB, L_XB, B_DB, L_DB, B_DN, L_DN  );

	//如果是99999，则无法计算改正量
	if( (DB_XN==99999.0) ||  ( DL_XN==99999.0) || ( DB_XB==99999.0) || ( DL_XB==99999.0) || ( DB_DB==99999.0) || ( DL_DB==99999.0) || ( DB_DN==99999.0) || (DL_DN==99999.0)  )
	{
		dx = 0 ;
		dy = 0 ;
		return -1;
	}

	//计算该点改正量，双线性内插法
	double detalL = L_DN - L_XN ; 
	double detalB = B_DB - B_DN ;
	
	dx = (( L_DN - y ) / detalL ) * (( B_DB - x ) / detalB ) *  DB_XN  +
		 ((L_DN - y ) / detalL ) * (( x - B_XN ) / detalB ) * DB_XB +	
		 ((y - L_XN) / detalL ) * (( x - B_XN ) / detalB ) * DB_DB +
		 ((y - L_XN) / detalL ) * (( B_XB - x ) / detalB ) * DB_DN;
	
	//单位是秒
	dy = (( L_DN - y ) / detalL ) * (( B_DB - x ) / detalB ) *  DL_XN  +
		 ((L_DN - y ) / detalL ) * (( x - B_XN ) / detalB ) * DL_XB +
		 ((y - L_XN) / detalL ) * (( x - B_XN ) / detalB ) * DL_DB +
         ((y - L_XN) / detalL ) * (( B_XB - x ) / detalB ) * DL_DN;

	//转化为°
	dx /= 3600.0 ;
	dy /= 3600.0 ;

	return 0;
}
#endif
//(char *)szSH, (char *)"lyjfysxyht197021", (char *)szFrame , FX, DB_XN, DL_XN, DB_XB, DL_XB, DB_DB, DL_DB, DB_DN, DL_DN
//山西
//山东
//浙江

//从BUFF中获得格网改正量
void _GetTuFuCoordsTransData_FromBuf(char* szSH, char* PWD, char* szFrame, int FX, double & DB_XN, double & DL_XN, double & DB_XB, double & DL_XB, double & DB_DB, double & DL_DB, double & DB_DN, double & DL_DN )
{
	//图幅号不在集合中，直接返回99999
	//在集合中返回改正量	

	int iFinded = -1 ;

#ifdef ShanXi
	int iFrameNum = 112 ;
#endif
#ifdef ShanDong
	int iFrameNum = 122 ;
#endif
#ifdef ZheJiang
	int iFrameNum = 97 ;
#endif
#ifdef TianJin
	int iFrameNum = 19 ;
#endif
#ifdef ShangHai
	int iFrameNum = 11 ;
#endif
	switch(FX)
	{
	case 1://80-2000
		for(int i = 0; i < iFrameNum ; i++)
		{
			if ( strcmp( _Grid_Format_80_2000[i].szFrame ,  szFrame ) == 0 )
			{
				DB_DB = _Grid_Format_80_2000[i].DB_DB ;
				DB_DN = _Grid_Format_80_2000[i].DB_DN ;
				DB_XB = _Grid_Format_80_2000[i].DB_XB ;
				DB_XN = _Grid_Format_80_2000[i].DB_XN ;
				DL_DB = _Grid_Format_80_2000[i].DL_DB ;
				DL_DN = _Grid_Format_80_2000[i].DL_DN ;
				DL_XB = _Grid_Format_80_2000[i].DL_XB ;
				DL_XN = _Grid_Format_80_2000[i].DL_XN ;

				return ; 
			}
		}
		break;

	case 2://2000-80
		for(int i = 0; i < iFrameNum ; i++)
		{
			if ( strcmp( _Grid_Format_2000_80[i].szFrame ,  szFrame ) == 0 )
			{
				DB_DB = _Grid_Format_2000_80[i].DB_DB ;
				DB_DN = _Grid_Format_2000_80[i].DB_DN ;
				DB_XB = _Grid_Format_2000_80[i].DB_XB ;
				DB_XN = _Grid_Format_2000_80[i].DB_XN ;
				DL_DB = _Grid_Format_2000_80[i].DL_DB ;
				DL_DN = _Grid_Format_2000_80[i].DL_DN ;
				DL_XB = _Grid_Format_2000_80[i].DL_XB ;
				DL_XN = _Grid_Format_2000_80[i].DL_XN ;

				return ; 
			}
		}
		break;

	case 3://54-2000
		for(int i = 0; i < iFrameNum ; i++)
		{
			if ( strcmp( _Grid_Format_54_2000[i].szFrame ,  szFrame ) == 0 )
			{
				DB_DB = _Grid_Format_54_2000[i].DB_DB ;
				DB_DN = _Grid_Format_54_2000[i].DB_DN ;
				DB_XB = _Grid_Format_54_2000[i].DB_XB ;
				DB_XN = _Grid_Format_54_2000[i].DB_XN ;
				DL_DB = _Grid_Format_54_2000[i].DL_DB ;
				DL_DN = _Grid_Format_54_2000[i].DL_DN ;
				DL_XB = _Grid_Format_54_2000[i].DL_XB ;
				DL_XN = _Grid_Format_54_2000[i].DL_XN ;

				return ; 
			}
		}
		break;

	case 4://2000-54
		for(int i = 0; i < iFrameNum ; i++)
		{
			if ( strcmp( _Grid_Format_2000_54[i].szFrame ,  szFrame ) == 0 )
			{
				DB_DB = _Grid_Format_2000_54[i].DB_DB ;
				DB_DN = _Grid_Format_2000_54[i].DB_DN ;
				DB_XB = _Grid_Format_2000_54[i].DB_XB ;
				DB_XN = _Grid_Format_2000_54[i].DB_XN ;
				DL_DB = _Grid_Format_2000_54[i].DL_DB ;
				DL_DN = _Grid_Format_2000_54[i].DL_DN ;
				DL_XB = _Grid_Format_2000_54[i].DL_XB ;
				DL_XN = _Grid_Format_2000_54[i].DL_XN ;

				return ; 
			}
		}
		break;
#ifdef ShangHai 

	case 5://84-2000
		for(int i = 0; i < iFrameNum ; i++)
		{
			if ( strcmp( _Grid_Format_84_2000[i].szFrame ,  szFrame ) == 0 )
			{
				DB_DB = _Grid_Format_84_2000[i].DB_DB ;
				DB_DN = _Grid_Format_84_2000[i].DB_DN ;
				DB_XB = _Grid_Format_84_2000[i].DB_XB ;
				DB_XN = _Grid_Format_84_2000[i].DB_XN ;
				DL_DB = _Grid_Format_84_2000[i].DL_DB ;
				DL_DN = _Grid_Format_84_2000[i].DL_DN ;
				DL_XB = _Grid_Format_84_2000[i].DL_XB ;
				DL_XN = _Grid_Format_84_2000[i].DL_XN ;

				return ; 
			}
		}
		break;

	case 6://2000-84	
		for(int i = 0; i < iFrameNum ; i++)
		{
			if ( strcmp( _Grid_Format_2000_84[i].szFrame ,  szFrame ) == 0 )
			{
				DB_DB = _Grid_Format_2000_84[i].DB_DB ;
				DB_DN = _Grid_Format_2000_84[i].DB_DN ;
				DB_XB = _Grid_Format_2000_84[i].DB_XB ;
				DB_XN = _Grid_Format_2000_84[i].DB_XN ;
				DL_DB = _Grid_Format_2000_84[i].DL_DB ;
				DL_DN = _Grid_Format_2000_84[i].DL_DN ;
				DL_XB = _Grid_Format_2000_84[i].DL_XB ;
				DL_XN = _Grid_Format_2000_84[i].DL_XN ;

				return ; 
			}
		}
		break;
#endif
	default:
		DB_DB = 99999 ;
		DB_DN = 99999 ;
		DB_XB = 99999 ;
		DB_XN = 99999 ;
		DL_DB = 99999 ;
		DL_DN = 99999 ;
		DL_XB = 99999 ;
		DL_XN = 99999 ;
		break;
	}

	//for(int i = 0; i < vec_vec_tab_list.size() ; i++)
	//{
	//	if ( strcmp( vec_vec_tab_list[i][0].c_str() ,  szFrame ) == 0 )
	//	{
	//		dx = atof( vec_vec_tab_list[i][1].c_str() );
	//		
	//		dy = atof( vec_vec_tab_list[i][2].c_str() );
	//		return ; 
	//	}
	//}

	DB_DB = 99999 ;
	DB_DN = 99999 ;
	DB_XB = 99999 ;
	DB_XN = 99999 ;
	DL_DB = 99999 ;
	DL_DN = 99999 ;
	DL_XB = 99999 ;
	DL_XN = 99999 ;
}

//void FetchDetalXY(const char * szFrame , double & dx ,double & dy , int CoordType )
//{
//	vector<vector<string>> vec_vec_tab_list;
//
//	if( CoordType == GEODETIC)
//		vec_vec_tab_list = DeuReadFile("C:\\Program Files\\Deu2000\\tfgzlgeo_detic.txt");
//	else
//		vec_vec_tab_list = DeuReadFile("C:\\Program Files\\Deu2000\\tfgzl_plane.txt");
//	
//
//	for(int i = 0; i < vec_vec_tab_list.size() ; i++)
//	{
//		if ( strcmp( vec_vec_tab_list[i][0].c_str() ,  szFrame ) == 0 )
//		{
//			dx = atof( vec_vec_tab_list[i][1].c_str() );
//			
//			dy = atof( vec_vec_tab_list[i][2].c_str() );
//
//			return ; 
//		}
//	}
//
//}