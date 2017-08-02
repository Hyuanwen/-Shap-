#pragma once

//授权码
#define AuthCode "AB452E83-6AEB-44f1-81EB-34A21D9FCDD0"

//Dll使用权限问题
#define E_FAIL_PRIVILEGE_UID 0x0802			//无序列号
#define E_FAIL_PRIVILEGE_EXTENT	0x0803      //转换区域超出范围

//数据类型转换
#define CSTR2DB(str)	_tstof((LPCTSTR)str)

//数据
#define VEC(T) std::vector<T>
#define P_VEC(T) std::vector<T> * 
#define VEC_IT(T) std::vector<T>::iterator

#define LIST(T) std::list<T>
#define P_LIST(T) std::list<T> *
#define LIST_IT(T) std::list<T>::iterator

#define PowerError		"无此操作权限"
#define UseAuthError	"使用无授权"
#define UseBeyoundError "转换数据超出授权转换范围"

//视图工具栏
#define _TOOL_ADD					0
#define _TOOL_ZOOMIN				1
#define _TOOL_ZOOMOUT				2
#define _TOOL_PAN					3
#define _TOOL_ZOOMTOVISIABLEEXTENTS	4
#define _TOOL_PREVIEW				5
#define _TOOL_NEXTVIEW				6
#define _TOOL_SELECT				7
#define _TOOL_REMOVESELECTIONS		8
#define _TOOL_NONE					9
#define _TOOL_REMOVELAYERS			10	

//#define PAGE_VIEW					0
//#define PAGE_VECTOR				1
//#define PAGE_RASTER				2

//矢量模型
#define MODEL_D3P7					1  //三维七参数
#define MODEL_D2P4					2  //二维四参数
#define MODEL_BURSA					3  //三维布尔沙
#define MODEL_D2P7					4  //二维七参数
#define MOD_AFFINE					5  //仿射变换
#define MOD_POLYNOMIAL1				6  //一阶多项式
#define MOD_POLYNOMIAL2				7  //二阶多项式
#define MOD_POLYNOMIAL3				8  //三阶多项式
#define MOD_POLYNOMIAL4				9  //四阶多项式
#define MODEL_GAUSS					10 //高斯投影
#define MODEL_TM					11 //横轴墨卡托投影
#define MODEL_UTM					12 //通用横轴墨卡托投影
#define MODEL_TRANS_ALL_GRID		13 //全图点格网法平移
#define MODEL_TRANS_ALL_Poly1		14 //全图点一阶多项式平移
#define MODEL_TRANS_ALL_Poly2		15 //全图点二阶多项式平移
#define MODEL_TRANS_ALL_D2P4		16 //全图点平面四参数平移
#define MODEL_TRANS_ALL_AFFINE		17 //全图点仿射平移
#define MODEL_TRANS_ALL_BURSA		18 //全图点三维布尔莎平移
#define MODEL_GRID					19 //格网
#define MODEL_TRANS_QUICK_GRID		20 //图廓点格网法平移 
#define MODEL_TRANS_QUICK_Poly1		21 //图廓点一阶多项式平移 
#define MODEL_TRANS_QUICK_Poly2		22 //图廓点二阶多项式平移 
#define MODEL_TRANS_QUICK_D2P4		23 //图廓点平面四参数平移
#define MODEL_TRANS_QUICK_AFFINE	24 //图廓点仿射平移
#define MODEL_TRANS_QUICK_BURSA		25 //图廓点三维布尔莎平移

//重采样方法
#define RESAMPLING_NEAREST	1 //最邻近法
#define RESAMPLING_BILINEAR	2 //双线性插值
#define RESAMPLING_BICUBIC	3 //双三次卷积

#define RAD_TO_DEG	57.29577951308232
#define DEG_TO_RAD	.0174532925199432958

#define GlobalMainFrame (*(CDeuGlobalMainFrame*)AfxGetMainWnd());

//投影定义
#define NAME				"Name"
#define PRJNAME				"Projection"
#define REMARK				"Remark"
#define ENVELOPE			"Envelope"
#define POINTSTYLE			"PointStyle"
#define GEODETICPOINTOR		"GeodeticPointor"
#define PROJECTION			"Projection"
#define CENTRALMERIDIAN		"CentralMeridian"
#define FALSEEASTING		"FalseEasting"
#define FALSENORTHING		"FalseNorthing"
#define LATITUDEOFORIGIN	"LatitudeOfOrigin"
#define SCALEFACTOR			"ScaleFactor"
#define CSTYPE				"CSType"
#define DATUM				"Datum"
#define ELLIPSOID			"Ellipsoid"
#define MAJOR				"Semi-Major-Axis"
#define MINOR				"Semi-Minor-Axis"
#define VALUE				"Value"
#define INVERSEFLATTENING	"InverseFlattening"
#define PRIMEMERIDIAN		"PrimeMeridian"
#define CENTRALMERIDIAN		"CentralMeridian"
#define SLONG				"Long"
#define SLAT				"Lat"
#define FALSEEASTING		"FalseEasting"
#define PROJECTED			"projected"
#define GEODATIC			"geodetic"
#define MINPOINT			"MinPoint"
#define MAXPOINT			"MaxPoint"
#define ABBREVIATION		"Abbreviation"
#define PER_METER			"Per_Meter"
#define PER_DEGREE			"Per_Degree"
#define EAST				"East"
#define NORTH				"North"	
#define BASEUNITS			"Units"
#define LABEL				"Label"
#define ELLIPSOIDHEIGHT		"EllipsoidHeight"
#define DIM					"Dimensions"
#define UNITS				"Units"

//#define PRJTYPE			"projected"
//#define GEODETICTYPE		"geodetic"

/*----------------- 消息集合单元 ---------------------*/
#define WM_TASK_VECTOR WM_USER+100
#define WM_TASK_RASTER WM_USER+101

//增加任务嵌套Tab
#define WM_TAB_VECTOR WM_USER+102
#define WM_TAB_RASTER WM_USER+103

//矢量通知消息面板消息，因对象无法访问
#define WM_VEC_MSGPANEL WM_USER+103
//#define WM_VEC_MSGPANEL WM_USER+104

//坐标类型
enum __COORDTYPE
{
	UNKNOWN,
	GEODETIC,     
	GEOCENTRIC,   //地心坐标系
	PLANE         //平面坐标系
};

enum TranformType
{
	VECTOR,
	VECTOR_PROJ,
	RASTER,
	RASTER_PROJ
};

//矢量转换的数据类型
const char sz_TranType_Vector[7][20] = { "ESRI Shapefile",
										 "MapInfo File",
										 "DXF",
										 "AVCE00",
										 "Oracle",
										 "Excel",
										 "Coverage"};

//栅格
const char sz_TranType_Raster[5][20] = { "GTiff",
                                         "HFA",
                                         "EHdr",
                                         "AAIGrid",
                                         "BMP"};

//转换的数据类型
const int _TranModel_Vector_num = 5 ;
const char sz_TranModel_Vector[_TranModel_Vector_num][20] = {"格网转换模型",
															 "布尔莎转换模型",
															 "二维七参数转换模型",
															 "平面四参数转换模型",
															 "三维七参数转换模型"
															};

//const char sz_TranModel_Raster[11][20] = {"平移转换模型",
//										 "格网转换模型",			
//										 "格网法平移转换模型",
//										 "仿射转换模型",
//										 "一阶多项式转换模型",
//										 "二阶多项式转换模型",
//										 "三阶多项式转换模型",
//										 "四阶多项式转换模型",
//										"高斯投影",
//										"横轴墨卡托投影",
//										"通用横轴墨卡托投影"};

const int _TranModel_Raster_num = 7 ;
const char sz_TranModel_Raster[_TranModel_Raster_num][40] = {
															"格网转换模型",
															"仿射转换模型",
															"二阶多项式转换模型",
															"三阶多项式转换模型",
															"四阶多项式转换模型",
															"布尔莎转换模型",
															"平面四参数转换模型"
															};
										//"格网转换模型图廓点平移法",
										//"格网转换模型全图点平移法",
										//"格网转换模型重采样法",
										//"仿射转换模型图廓点平移法",
										//"仿射转换模型全图点平移法",
										//"仿射转换模型重采样法",
										//"二阶多项式转换模型图廓点平移法",
										//"二阶多项式转换模型全图点平移法",
										//"二阶多项式转换模型重采样法",
										//"三阶多项式转换模型图廓点平移法",
										//"三阶多项式转换模型全图点平移法",
										//"三阶多项式转换模型重采样法",
										//"四阶多项式转换模型图廓点平移法",
										//"四阶多项式转换模型全图点平移法",					
										//"四阶多项式转换模型重采样法",


const int _TranModel_ReCollect_num = 3 ;
const char sz_TranModel_ReCollect[_TranModel_ReCollect_num][40] = {"最邻近法",
																   "双线性内插法",
																   "双三次卷积法"};

const int _TranModel_Transfer_num = 2 ;
const char sz_TranModel_Transfer[_TranModel_Transfer_num][40] = {"图廓点平移法",
																 "全图点平移法",};

const int _TranModel_Project_num = 3 ;
const char sz_TranModel_Project[_TranModel_Project_num][40] = {
																"高斯投影",
																"横轴墨卡托投影",
																"通用横轴墨卡托投影"};	

const char sz_Unit[2][20] = {"米",
							 "度"};

const int  _Proname_num = 24 ;
const char sz_Proname[24][20] = {"安徽","福建","甘肃", "广东","贵州",
								 "海南","河北","河南","黑龙江","湖北",
								 "湖南","吉林","江苏","江西","辽宁",
								 "青海","山东","山西","陕西","上海",
								 "四川","天津","云南","浙江" };

const int _Fx_num = 6;
const char sz_Fx[6][20] = { "54-2000",
							"2000-54",
							"80-2000",
							"2000-80",
							"84-2000",
							"2000-84"};

//坐标系类型		
enum CoordinateType
{
	GeoDetic,	   //大地坐标
	GeoCentic,	   //空间直角坐标
	GeoProjected,  //投影坐标
	All
};

//转换标准			
enum TranStandard
{
	Peking54,		//54
	XiAn80,			//80
	WGS84,			//84
	CGCS2000		//2000
};

//数据源类型
enum DataSrcType
{
	Files,
	Oracle
};

typedef struct UserPower
{
	CString strName;
	
	BOOL IsVectorView;
	BOOL IsRasterView;
	BOOL IsDataBaseView;

	BOOL IsVectorConvert;
	BOOL IsRasterConvert;
	BOOL IsDataBaseConvert;

} USERPOWER, *PUSERPOWER;

typedef struct OracleInfo
{
	CString strSID;
	CString strUser;
	CString strPwd;

}ORACLEINFO, *P_ORACLEINFO;

#define BEFOREBEGIN   "0"
#define RUNNING		  "1"
#define FINISHED	  "2"

#define VECTOR_TRANS  "0"
#define RASTER_TRANS  "1"

//子框架视图对象数组
extern CArray<CView*>	 _ViewVectorList;
extern CArray<CView*>	 _ViewRasterList;

//任务树节点对象数组
extern CArray<HTREEITEM> _TreeVectorList;
extern CArray<HTREEITEM> _TreeRasterList;

//Tab内嵌指针对象
extern CArray<CWnd*>     _TabVectorList;
extern CArray<CWnd*>     _TabRasterList;

//消息
//#define WM_PROGRESS WM_USER+101
#define WM_PROGRESS        0x0500		//进度条消息
#define WM_TASK_FINISH     0x0800		//单线程任务转换完成消息
#define WM_TASK_FINISH_ALL 0x0801		//全部转换完成消息
#define WM_LOADWAIT		   WM_USER+140	//上传等待消息add by chenyong 2014-3-5

enum enumDTType
{
	deuUnknownType	= 0x0000,
	deuRasterDataset,
	deuRasterBand,
	deuRasterCatalog,
	deuFeatureClass,
	deuFeatureDataset
};

//add by chenyong 2013-4-28
typedef struct SdeDataInfo
{
	string		strName; //数据集名称
	enumDTType	Type;	 //数据集类型
}STR_SDEINFO;

//ArcSDE配置参数 add by chenyong 2013-12-3
typedef struct _STR_SDE_PARAM
{
	CString		strServer;
	CString		strService;
	CString		strDatabase;
	CString		strUsername;
	CString		strPassword;
	CString		strVersion;
}STR_SDE_PARAM;

//功能：获取程序全局根路径
CString GetStylesPath();

//功能：分解字符串中关于Oracle的连接信息
void PasterDBConn(CString m_str, P_ORACLEINFO pOracleInfo);
void GetSysCurrentTime(char* szTime);

//功能：判断目录是否存在
BOOL IsExistDir(const string& strDir);

//功能：创建目录
BOOL CreateDir(const string& strDir);

//功能：删除指定目录下所有文件
void DeleteAllFile(const string& strDir);