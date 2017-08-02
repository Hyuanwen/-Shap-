//#pragma once 
#ifndef _DEUDEF_H
#define _DEUDEF_H

#include <vector>

//const double DEG_TO_RAD = 0.0174532925199432958;
//const double RAD_TO_DEG = 57.29577951308232;

#define		DEG_TO_RAD  0.0174532925199432958
#define		RAD_TO_DEG  57.29577951308232

#define		ERR_CroodInfoError "坐标信息错误"

//excel
#define		E_FAIL_OPENFILE				0x0804
#define		E_FAIL_TRANSPOINT			0x0805
#define		E_FAIL_SAVEFILE				0x0806
#define		E_FAIL_SETRSR				0x0807

//PRIVILEGE
#define		E_FAIL_PRIVILEGE_UID		0x0802
#define		E_FAIL_PRIVILEGE_EXTENT		0x0803

#define		WM_PROGRESS					0x0500//进度条消息
#define		WM_TASK_FINISH				0x0800
#define		WM_TASK_FINISH_ALL			0x0801

#define		WM_NO_PRIVILEGE_UID			0x0802//错误的序列号
#define		WM_NO_PRIVILEGE_EXTENT		0x0803//错误的数据范围

#define		WM_TICKCOUNT				0x0804 //计时

//重采样方法
#define		RESAMPLING_NEAREST			1 //最邻近法
#define		RESAMPLING_BILINEAR			2 //双线性插值
#define		RESAMPLING_BICUBIC			3 //双三次卷积

//矢量模型
#define		MODEL_D3P7					1 //三维七参数
#define		MODEL_D2P4					2 //二维四参数
#define		MODEL_BURSA					3 //三维布尔沙
#define		MODEL_D2P7					4 //二维七参数
#define		MOD_AFFINE					5 //仿射变换
#define		MOD_POLYNOMIAL1				6 //一阶多项式
#define		MOD_POLYNOMIAL2				7 //二阶多项式
#define		MOD_POLYNOMIAL3				8 //三阶多项式
#define		MOD_POLYNOMIAL4				9 //四阶多项式
#define		MODEL_GAUSS					10 //高斯投影
#define		MODEL_TM					11 //横轴墨卡托投影
#define		MODEL_UTM					12 //通用横轴墨卡托投影
#define		MODEL_TRANS_ALL_GRID		13 //全图点格网法平移
#define		MODEL_TRANS_ALL_Poly1		14// 全图点一阶多项式平移
#define		MODEL_TRANS_ALL_Poly2		15// 全图点二阶多项式平移
#define		MODEL_TRANS_ALL_D2P4		16// 全图点平面四参数平移
#define		MODEL_TRANS_ALL_AFFINE		17// 全图点仿射平移
#define		MODEL_TRANS_ALL_BURSA		18// 全图点三维布尔莎平移
#define		MODEL_GRID					19// 格网
#define		MODEL_TRANS_QUICK_GRID		20//图廓点格网法平移 
#define		MODEL_TRANS_QUICK_Poly1		21//图廓点一阶多项式平移 
#define		MODEL_TRANS_QUICK_Poly2		22//图廓点二阶多项式平移 
#define		MODEL_TRANS_QUICK_D2P4		23//图廓点平面四参数平移
#define		MODEL_TRANS_QUICK_AFFINE	24//图廓点仿射平移
#define		MODEL_TRANS_QUICK_BURSA		25//图廓点三维布尔莎平移


#define TOL1 0.000001
#define TOL2 70
#define TOL3 0.001
#define TOL4 100

//栅格
#define PIX2X(pix,OriginX,Pix_to_X)		(OriginX + Pix_to_X*pix)
#define X2PIX(x,OriginX,X_to_Pix)		((x - OriginX )*X_to_Pix)

#define MINISIZE  256
#define MAXSIZE   256
#define BUFFSIZE  4

#define THREADNUM 6

CRITICAL_SECTION g_cs;

#define TIME_WAIT 0.5

enum __COORDTYPE //暂未发现用处
{
	UNKNOWN,			//未知
	GEODETIC,			//地理坐标
	GEOCENTRIC,			//地心坐标
	PLANE				//投影坐标
};

enum ExcelFormatType
{
	NUM,
	LETTER
};

typedef struct 
{
	short		_TransModel;				
	short		SrcCoordType;
	short		DesCoordType;

	CString		SrcUnitX;
	CString		SrcUnitY;
	CString		SrcUnitZ;

	CString		DesUnitX;
	CString		DesUnitY;
	CString		DesUnitZ;

	//增量用于格网的设置信息   yzg 2012-9-28 begin
	CString    SrcProId;  //区号 调用具体函数时传入
	CString    SrcPwd;    //密码 调用具体函数时传入
	CString    SrcProName;//省号 决定调用哪个动态库
	//增量用于格网的设置信息   yzg 2012-9-28 end

	double  _src_a ;
	double	_src_f ;
	double	_src_from_greenwich;
	double	_src_false_east;
	double	_des_a;
	double	_des_f;
	double	_des_from_greenwich;
	double	_des_false_east;

	void * _srcPJ;
	void * _desPJ;

	double* _Para;
	//std::vector<double> _Para;
	//增加用于Excel的设置信息  yzg 2012-9-25 begin
	VARIANT _Excel;
	//增加用于Excel的设置信息  yzg 2012-9-25 end
}TransParams;

typedef struct deuColumnFormatNum
{
	int  oriX;//源x所在行
	int  oriY;//源y所在行
	int  oriZ;//源z所在行
	int  desX;//目标x所在行
	int  desY;//目标y所在行
	int  desZ;//目标z所在行
}deuColumnFormatNum;

typedef struct deuColumnFormatLetter
{ 	
	char *  oriX;//源x所在行
	char *  oriY;//源y所在行
	char *  oriZ;//源z所在行
	char *	desX;//目标x所在行
	char *	desY;//目标y所在行
	char *	desZ;//目标z所在行
}deuColumnFormatLetter;

typedef struct deuColumnHeader
{
	bool haveColumnHeader ;//是否包含列头
	int  ColumnHeaderRow  ;//列头所在行	
}deuColumnHeader;

typedef struct deuExcelFormat
{ 	
	ExcelFormatType	sType;//格式类型 0 = FormatNum 1 = FormatLetter
	deuColumnHeader	_ColumnHeader;
	void *	        pColFormat;

	deuExcelFormat()
	{
	}

	deuExcelFormat( int ox_ , int oy_ , int oz_, int dx_, int dy_,int dz_,  bool haveColumnHeader = false, int ColumnHeaderRow = 0)
	{
		_ColumnHeader.haveColumnHeader = haveColumnHeader;
		_ColumnHeader.ColumnHeaderRow = ColumnHeaderRow;
		
		sType = ExcelFormatType::NUM ; 		
		deuColumnFormatNum *pdeuNum = new deuColumnFormatNum;
		deuColumnFormatNum &deuNum =  *pdeuNum ;
		
		deuNum.oriX = ox_;
		deuNum.oriY = oy_;
		deuNum.oriZ = oz_;
		deuNum.desX = dx_;
		deuNum.desY = dy_;
		deuNum.desZ = dz_;		
		
		pColFormat = (void*)pdeuNum;
	}

	deuExcelFormat(char * ox_ , char * oy_ , char * oz_, char * dx_, char * dy_,char * dz_,  bool haveColumnHeader = false, int ColumnHeaderRow = 0)
	{
		_ColumnHeader.haveColumnHeader = haveColumnHeader;
		_ColumnHeader.ColumnHeaderRow = ColumnHeaderRow;
		
		sType = ExcelFormatType::LETTER ; 
		deuColumnFormatLetter *pdeuLetter = new deuColumnFormatLetter;
		deuColumnFormatLetter &deuLetter = *pdeuLetter;

		deuLetter.oriX = (char*)malloc( sizeof(char) * strlen(ox_) );
		deuLetter.oriY = (char*)malloc( sizeof(char) * strlen(oy_) );
		deuLetter.oriZ = (char*)malloc( sizeof(char) * strlen(oz_) );
		deuLetter.desX = (char*)malloc( sizeof(char) * strlen(dx_) );
		deuLetter.desY = (char*)malloc( sizeof(char) * strlen(dy_) );
		deuLetter.desZ = (char*)malloc( sizeof(char) * strlen(dz_) );

		pColFormat = (void*)pdeuLetter;
	}

	~deuExcelFormat()
	{
		if(sType == ExcelFormatType::LETTER)
		{
			//deuColumnFormatLetter *pdeuLetter = (deuColumnFormatLetter *)pColFormat;
			//deuColumnFormatLetter &deuLetter = *pdeuLetter ;

			//free(deuLetter.oriX);
			//free(deuLetter.oriY);
			//free(deuLetter.oriZ);
			//free(deuLetter.desX);
			//free(deuLetter.desY);
			//free(deuLetter.desZ);
		}
	}
}deuExcelFormat;

//栅格格式
typedef struct deuRasterShapeFormat
{
	 double			dbLeft;		//源栅格左上角点经度值
	 double			dbTop;		//源栅格左上角点纬度值
	 long			lLenght;	//源栅格长度
	 long			lWidth;		//源栅格宽度
	 double			dbPixX;		//源栅格X分辨率
	 double			dbPixY;		//源栅格Y分辨率
}deuRasterShapeFormat;

//#define	VEC(T)	std::vector<T>
#define	DEU_CALLBACK if(_callback) _callback
typedef	void (*callback_fun)(long, long, long);

//获取成员函数地址
template<typename ToType, typename FromType>
void GetMemberFuncAddr_VC6(ToType& addr, FromType f)
{
	union
	{
		FromType	_f;
		ToType		_t;
	}ut;
	ut._f = f;
	addr = ut._t;
}

//otlv4_2.h
typedef struct  sdo_point
{
	double  x;
	double  y;
	double  z;
}sdo_point;

typedef struct  sdo_point_ind
{
	bool  x;
	bool  y;
	bool  z;
}sdo_point_ind;

typedef struct sdo_geometry_obj
{ 
	int         gtype_;
	int         srid_;
	sdo_point   point_;
	int			elemInfoSize;
	int			ordinatesSize;
	int         *elemInfoQueue_;
	double		*ordinatesQueue_;
}sdo_geometry_obj;

typedef struct sdo_geometry_ind
{
	bool        geometryNull_;
	bool        typeNull_;
	bool        sridNull_;
	bool        pointNull_;
	sdo_point_ind point_;
	bool        elemInfoNull_;
	bool        ordinatesNull_;
}sdo_geometry_ind;

typedef struct tagSDO_geometry
{ 
	sdo_geometry_obj obj;
	sdo_geometry_ind ind;
}SDO_geometry;

//SDO_geometry * CloneGeometry(const SDO_geometry & geo)
//{
//	SDO_geometry  *poutGeo = new SDO_geometry ;
//	SDO_geometry  &outGeo  = * poutGeo; 
//
//	memcpy( poutGeo , &geo ,sizeof(SDO_geometry) );
//
//	int eleSize = outGeo.obj.elemInfoSize;
//	int ordiSize = outGeo.obj.ordinatesSize;
//
//	outGeo.obj.elemInfoQueue_ = new int[eleSize];
//	outGeo.obj.ordinatesQueue_= new double[ordiSize];
//
//	memcpy( poutGeo->obj.elemInfoQueue_ , geo.obj.elemInfoQueue_ , geo.obj.elemInfoSize * sizeof(int) );
//
//	return poutGeo;
//}

#define RESET_COUNT \
	m_fea_done = 0;\
	m_fea_null_count = 0;\
	m_fea_create_count = 0;\
	m_fea_fail_count = 0;\
	\
	m_geo_point_count = 0;\
	m_geo_line_count = 0;\
	m_geo_polygon_count = 0;\
	m_geo_multi_point_count = 0;\
	m_geo_multi_line_count = 0;\
	m_geo_multi_polygon_count = 0;\
	m_geo_null_count = 0;\
	\
	m_error_count = 0;\
	m_geo_ori_error_count = 0;\
	m_geo_done = 0;

#define LOG_ALL_FEA \
	char *fea_all=(char*)malloc(100);\
	itoa(m_all_fea_count,fea_all,10);\
	LOG("总的feature:",fea_all,100);\
	free(fea_all);

#define LOG_FEA_DONE \
	char *fea_done=(char*)malloc(100);\
	itoa(m_fea_done,fea_done,10);\
	LOG("已处理的feature:",fea_done,100);\
	free(fea_done);

#define LOG_FEA_NULL \
	char *fea_null=(char*)malloc(100);\
	itoa(m_fea_null_count,fea_null,10);\
	LOG("feature为空的个数：",fea_null,100);\
	free(fea_null);

#define LOG_FEA_CREATE \
	char *fea_create=(char*)malloc(100);\
	itoa(m_fea_create_count,fea_create,10);\
	LOG("已创建的feature：",fea_create,100);\
	free(fea_create);

#define LOG_FEA_FAIL \
	char *fea_fail=(char*)malloc(100);\
	itoa(m_fea_fail_count,fea_fail,10);\
	LOG("创建失败的feature：",fea_fail,100);\
	free(fea_fail);

#define LOG_GEO_PT \
	char *geo_pt=(char*)malloc(100);\
	itoa(m_geo_point_count,geo_pt,10);\
	LOG("已处理的point:",geo_pt,100);\
	free(geo_pt);

#define LOG_GEO_LINE \
	char *geo_line=(char*)malloc(100);\
	itoa(m_geo_line_count,geo_line,10);\
	LOG("已处理的line:",geo_line,100);\
	free(geo_line);

#define LOG_GEO_POLYGON \
	char *geo_polygon=(char*)malloc(100);\
	itoa(m_geo_polygon_count,geo_polygon,10);\
	LOG("已处理的polygon:",geo_polygon,100);\
	free(geo_polygon);

#define LOG_GEO_MPT \
	char *geo_MPt=(char*)malloc(100);\
	itoa(m_geo_multi_point_count,geo_MPt,10);\
	LOG("已处理的MultiPoint:",geo_MPt,100);\
	free(geo_MPt);

#define LOG_GEO_MLINE \
	char *geo_MLine=(char*)malloc(100);\
	itoa(m_geo_multi_line_count,geo_MLine,10);\
	LOG("已处理的MultiLine:",geo_MLine,100);\
	free(geo_MLine);

#define LOG_GEO_MPOLYGON \
	char *geo_MPolygon=(char*)malloc(100);\
	itoa(m_geo_multi_polygon_count,geo_MPolygon,10);\
	LOG("已处理的MultiPolygon:",geo_MPolygon,100);\
	free(geo_MPolygon);

#define LOG_GEO_NULL \
	char *geo_null=(char*)malloc(100);\
	itoa(m_geo_null_count,geo_null,10);\
	LOG("为空的geometry：",geo_null,100);\
	free(geo_null);

#define LOG_ERR_OTHER \
	char *err_Other=(char*)malloc(100);\
	itoa(m_error_count,err_Other,10);\
	LOG("其他的错误个数：",err_Other,100);\
	free(err_Other);

#define LOG_ORI_ERROR \
	char *geo_Ori_Error=(char*)malloc(100);\
	itoa(m_geo_ori_error_count,geo_Ori_Error,10);\
	LOG("原始数据错误的feature：",geo_Ori_Error,100);\
	free(geo_Ori_Error);

#define LOG_GEO_DONE \
	char *geo_done=(char*)malloc(100);\
	itoa(m_geo_done,geo_done,10);\
	LOG("已处理的geometry:",geo_done,100);\
	free(geo_done);

#define LOG_START_HEADER(szlyrname) \
	LOG("开始转换图层:",szlyrname,strlen("开始转换图层:")+strlen(szlyrname));

#define LOG_WRITE_OUT(szlyrname2)\
	LOG("输出转换图层:",szlyrname2,strlen("输出转换图层:")+strlen(szlyrname2));

#define LOG_START \
	{char *start_t=(char*)malloc(100);\
	SYSTEMTIME sys; \
	GetLocalTime( &sys ); \
	char * shour = (char *)malloc(20);\
	itoa(sys.wHour,shour,10);\
	\
	char * sMinute = (char *)malloc(20);\
	itoa(sys.wMinute,sMinute,10);\
	\
	char * sSecond = (char *)malloc(20);\
	itoa(sys.wSecond,sSecond,10);\
	\
	strcpy(start_t,shour);\
		strcat(start_t,":");\
	strcat(start_t,sMinute);\
		strcat(start_t,":");\
	strcat(start_t,sSecond); \
	LOG("开始转换时间:",start_t,strlen("开始转换时间:")+ 100); \
	free(shour);\
	free(sMinute);\
	free(sSecond);\
	free(start_t);}

#define LOG_END \
	{char *end_t=(char*)malloc(100);\
	SYSTEMTIME sys; \
	GetLocalTime( &sys ); \
	char * shour = (char *)malloc(20);\
	itoa(sys.wHour,shour,10);\
	\
	char * sMinute = (char *)malloc(20);\
	itoa(sys.wMinute,sMinute,10);\
	\
	char * sSecond = (char *)malloc(20);\
	itoa(sys.wSecond,sSecond,10);\
	\
	strcpy(end_t,shour);\
		strcat(end_t,":");\
	strcat(end_t,sMinute);\
		strcat(end_t,":");\
	strcat(end_t,sSecond); \
	LOG("结束转换时间:",end_t,100); \
	free(end_t);}

	/*clock_t start;
	clock_t end;
#define START_TIME 	start = clock();
#define END_TIME	end	  = clock();	

#define SEC_PER_CLOCKS 0.001

#define LOG_USED_TIME \
	int time_i=(start-end)*SEC_PER_CLOCKS;\
	char * time = (char *)malloc(20);\
	itoa(time_i,time,10);\
	LOG("总共用时(秒):",time,100);\
	free(time);*/

#define LOG_NO_TABLE 

#define LOG_EXTENT(x,y,x2,y2) \
	{char * extent = (char*)malloc(100);\
	sprintf(extent,"图层范围:%f,%f,%f,%f",x,y,x2,y2);\
	LOGSTR(extent);\
	free(extent);}

#define  LOGSTR(s) \
	{	\
		FILE   *_pfile=fopen("C:\\log.txt","a+");\
		char * strLog = s;\
		fwrite(strLog,strlen(strLog),1,_pfile);\
		fwrite("\r\n",2,1,_pfile);\
		fclose(_pfile);\
	}

#define  LOG(strLog1,strLog2,n) \
	{\
		char *strlog=new char[1000];\
		memset(strlog,0,1000);\
		sprintf(strlog,"%s%s",strLog1,strLog2);\
		LOGSTR(strlog);\
		delete[] strlog;\
	}

#endif