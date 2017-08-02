#pragma once

//��Ȩ��
#define AuthCode "AB452E83-6AEB-44f1-81EB-34A21D9FCDD0"

//Dllʹ��Ȩ������
#define E_FAIL_PRIVILEGE_UID 0x0802			//�����к�
#define E_FAIL_PRIVILEGE_EXTENT	0x0803      //ת�����򳬳���Χ

//��������ת��
#define CSTR2DB(str)	_tstof((LPCTSTR)str)

//����
#define VEC(T) std::vector<T>
#define P_VEC(T) std::vector<T> * 
#define VEC_IT(T) std::vector<T>::iterator

#define LIST(T) std::list<T>
#define P_LIST(T) std::list<T> *
#define LIST_IT(T) std::list<T>::iterator

#define PowerError		"�޴˲���Ȩ��"
#define UseAuthError	"ʹ������Ȩ"
#define UseBeyoundError "ת�����ݳ�����Ȩת����Χ"

//��ͼ������
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

//ʸ��ģ��
#define MODEL_D3P7					1  //��ά�߲���
#define MODEL_D2P4					2  //��ά�Ĳ���
#define MODEL_BURSA					3  //��ά����ɳ
#define MODEL_D2P7					4  //��ά�߲���
#define MOD_AFFINE					5  //����任
#define MOD_POLYNOMIAL1				6  //һ�׶���ʽ
#define MOD_POLYNOMIAL2				7  //���׶���ʽ
#define MOD_POLYNOMIAL3				8  //���׶���ʽ
#define MOD_POLYNOMIAL4				9  //�Ľ׶���ʽ
#define MODEL_GAUSS					10 //��˹ͶӰ
#define MODEL_TM					11 //����ī����ͶӰ
#define MODEL_UTM					12 //ͨ�ú���ī����ͶӰ
#define MODEL_TRANS_ALL_GRID		13 //ȫͼ�������ƽ��
#define MODEL_TRANS_ALL_Poly1		14 //ȫͼ��һ�׶���ʽƽ��
#define MODEL_TRANS_ALL_Poly2		15 //ȫͼ����׶���ʽƽ��
#define MODEL_TRANS_ALL_D2P4		16 //ȫͼ��ƽ���Ĳ���ƽ��
#define MODEL_TRANS_ALL_AFFINE		17 //ȫͼ�����ƽ��
#define MODEL_TRANS_ALL_BURSA		18 //ȫͼ����ά����ɯƽ��
#define MODEL_GRID					19 //����
#define MODEL_TRANS_QUICK_GRID		20 //ͼ���������ƽ�� 
#define MODEL_TRANS_QUICK_Poly1		21 //ͼ����һ�׶���ʽƽ�� 
#define MODEL_TRANS_QUICK_Poly2		22 //ͼ������׶���ʽƽ�� 
#define MODEL_TRANS_QUICK_D2P4		23 //ͼ����ƽ���Ĳ���ƽ��
#define MODEL_TRANS_QUICK_AFFINE	24 //ͼ�������ƽ��
#define MODEL_TRANS_QUICK_BURSA		25 //ͼ������ά����ɯƽ��

//�ز�������
#define RESAMPLING_NEAREST	1 //���ڽ���
#define RESAMPLING_BILINEAR	2 //˫���Բ�ֵ
#define RESAMPLING_BICUBIC	3 //˫���ξ��

#define RAD_TO_DEG	57.29577951308232
#define DEG_TO_RAD	.0174532925199432958

#define GlobalMainFrame (*(CDeuGlobalMainFrame*)AfxGetMainWnd());

//ͶӰ����
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

/*----------------- ��Ϣ���ϵ�Ԫ ---------------------*/
#define WM_TASK_VECTOR WM_USER+100
#define WM_TASK_RASTER WM_USER+101

//��������Ƕ��Tab
#define WM_TAB_VECTOR WM_USER+102
#define WM_TAB_RASTER WM_USER+103

//ʸ��֪ͨ��Ϣ�����Ϣ��������޷�����
#define WM_VEC_MSGPANEL WM_USER+103
//#define WM_VEC_MSGPANEL WM_USER+104

//��������
enum __COORDTYPE
{
	UNKNOWN,
	GEODETIC,     
	GEOCENTRIC,   //��������ϵ
	PLANE         //ƽ������ϵ
};

enum TranformType
{
	VECTOR,
	VECTOR_PROJ,
	RASTER,
	RASTER_PROJ
};

//ʸ��ת������������
const char sz_TranType_Vector[7][20] = { "ESRI Shapefile",
										 "MapInfo File",
										 "DXF",
										 "AVCE00",
										 "Oracle",
										 "Excel",
										 "Coverage"};

//դ��
const char sz_TranType_Raster[5][20] = { "GTiff",
                                         "HFA",
                                         "EHdr",
                                         "AAIGrid",
                                         "BMP"};

//ת������������
const int _TranModel_Vector_num = 5 ;
const char sz_TranModel_Vector[_TranModel_Vector_num][20] = {"����ת��ģ��",
															 "����ɯת��ģ��",
															 "��ά�߲���ת��ģ��",
															 "ƽ���Ĳ���ת��ģ��",
															 "��ά�߲���ת��ģ��"
															};

//const char sz_TranModel_Raster[11][20] = {"ƽ��ת��ģ��",
//										 "����ת��ģ��",			
//										 "������ƽ��ת��ģ��",
//										 "����ת��ģ��",
//										 "һ�׶���ʽת��ģ��",
//										 "���׶���ʽת��ģ��",
//										 "���׶���ʽת��ģ��",
//										 "�Ľ׶���ʽת��ģ��",
//										"��˹ͶӰ",
//										"����ī����ͶӰ",
//										"ͨ�ú���ī����ͶӰ"};

const int _TranModel_Raster_num = 7 ;
const char sz_TranModel_Raster[_TranModel_Raster_num][40] = {
															"����ת��ģ��",
															"����ת��ģ��",
															"���׶���ʽת��ģ��",
															"���׶���ʽת��ģ��",
															"�Ľ׶���ʽת��ģ��",
															"����ɯת��ģ��",
															"ƽ���Ĳ���ת��ģ��"
															};
										//"����ת��ģ��ͼ����ƽ�Ʒ�",
										//"����ת��ģ��ȫͼ��ƽ�Ʒ�",
										//"����ת��ģ���ز�����",
										//"����ת��ģ��ͼ����ƽ�Ʒ�",
										//"����ת��ģ��ȫͼ��ƽ�Ʒ�",
										//"����ת��ģ���ز�����",
										//"���׶���ʽת��ģ��ͼ����ƽ�Ʒ�",
										//"���׶���ʽת��ģ��ȫͼ��ƽ�Ʒ�",
										//"���׶���ʽת��ģ���ز�����",
										//"���׶���ʽת��ģ��ͼ����ƽ�Ʒ�",
										//"���׶���ʽת��ģ��ȫͼ��ƽ�Ʒ�",
										//"���׶���ʽת��ģ���ز�����",
										//"�Ľ׶���ʽת��ģ��ͼ����ƽ�Ʒ�",
										//"�Ľ׶���ʽת��ģ��ȫͼ��ƽ�Ʒ�",					
										//"�Ľ׶���ʽת��ģ���ز�����",


const int _TranModel_ReCollect_num = 3 ;
const char sz_TranModel_ReCollect[_TranModel_ReCollect_num][40] = {"���ڽ���",
																   "˫�����ڲ巨",
																   "˫���ξ����"};

const int _TranModel_Transfer_num = 2 ;
const char sz_TranModel_Transfer[_TranModel_Transfer_num][40] = {"ͼ����ƽ�Ʒ�",
																 "ȫͼ��ƽ�Ʒ�",};

const int _TranModel_Project_num = 3 ;
const char sz_TranModel_Project[_TranModel_Project_num][40] = {
																"��˹ͶӰ",
																"����ī����ͶӰ",
																"ͨ�ú���ī����ͶӰ"};	

const char sz_Unit[2][20] = {"��",
							 "��"};

const int  _Proname_num = 24 ;
const char sz_Proname[24][20] = {"����","����","����", "�㶫","����",
								 "����","�ӱ�","����","������","����",
								 "����","����","����","����","����",
								 "�ຣ","ɽ��","ɽ��","����","�Ϻ�",
								 "�Ĵ�","���","����","�㽭" };

const int _Fx_num = 6;
const char sz_Fx[6][20] = { "54-2000",
							"2000-54",
							"80-2000",
							"2000-80",
							"84-2000",
							"2000-84"};

//����ϵ����		
enum CoordinateType
{
	GeoDetic,	   //�������
	GeoCentic,	   //�ռ�ֱ������
	GeoProjected,  //ͶӰ����
	All
};

//ת����׼			
enum TranStandard
{
	Peking54,		//54
	XiAn80,			//80
	WGS84,			//84
	CGCS2000		//2000
};

//����Դ����
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

//�ӿ����ͼ��������
extern CArray<CView*>	 _ViewVectorList;
extern CArray<CView*>	 _ViewRasterList;

//�������ڵ��������
extern CArray<HTREEITEM> _TreeVectorList;
extern CArray<HTREEITEM> _TreeRasterList;

//Tab��Ƕָ�����
extern CArray<CWnd*>     _TabVectorList;
extern CArray<CWnd*>     _TabRasterList;

//��Ϣ
//#define WM_PROGRESS WM_USER+101
#define WM_PROGRESS        0x0500		//��������Ϣ
#define WM_TASK_FINISH     0x0800		//���߳�����ת�������Ϣ
#define WM_TASK_FINISH_ALL 0x0801		//ȫ��ת�������Ϣ
#define WM_LOADWAIT		   WM_USER+140	//�ϴ��ȴ���Ϣadd by chenyong 2014-3-5

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
	string		strName; //���ݼ�����
	enumDTType	Type;	 //���ݼ�����
}STR_SDEINFO;

//ArcSDE���ò��� add by chenyong 2013-12-3
typedef struct _STR_SDE_PARAM
{
	CString		strServer;
	CString		strService;
	CString		strDatabase;
	CString		strUsername;
	CString		strPassword;
	CString		strVersion;
}STR_SDE_PARAM;

//���ܣ���ȡ����ȫ�ָ�·��
CString GetStylesPath();

//���ܣ��ֽ��ַ����й���Oracle��������Ϣ
void PasterDBConn(CString m_str, P_ORACLEINFO pOracleInfo);
void GetSysCurrentTime(char* szTime);

//���ܣ��ж�Ŀ¼�Ƿ����
BOOL IsExistDir(const string& strDir);

//���ܣ�����Ŀ¼
BOOL CreateDir(const string& strDir);

//���ܣ�ɾ��ָ��Ŀ¼�������ļ�
void DeleteAllFile(const string& strDir);