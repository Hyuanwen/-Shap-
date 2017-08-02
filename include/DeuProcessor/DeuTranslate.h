#ifndef _DEU_TRANSLATE_H
#define _DEU_TRANSLATE_H
//#include "stdafx.h"
#include <vector>
//#include <time.h>
#include "oci.h"
#include "ogrsf_frmts.h"
#include "ogr_oci.h"
#include "DeuProject.h"
#include "gdal_priv.h"

#include "../code/DeuTranslate/GridTranslate.h"

//class CGridTranslate;
class CDeuConn;

#define	DEU_CALLBACK if(_callback) _callback
typedef	void (*callback_fun)(long, long, long);

#ifndef _DEU_TRANSLATE_LIB
	#define DeuTranslate_Export_Class _declspec(dllimport)
#else
	#define DeuTranslate_Export_Class _declspec(dllexport)
#endif

/*
	说明：该文件包含如下类的定义
		1. CDeuEllipse
		2. CDeuSpatialReference
		3. CDeuUnits
		4. CDeuCoordType
		5. CSevenParams
		6. CDeuTrans+
		7. CDeuDatabase
		8. CDeuConnPool
		9. CDeuRasterTrans
*/

//*****************************************************************
//类名:			CDeuEllipse
//说明:			该类负责提供或设置椭球参数
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-04
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************
class DeuTranslate_Export_Class CDeuEllipse
{
public:
	 CDeuEllipse();
	 virtual ~CDeuEllipse();
public:
	void	get_Ellip_Name(CString& strEllipName) const;
	void	putref_Ellip_Name(const CString& newEllipName);
	//功能：获取或设置椭球名称

	void	get_Major(double& MajorVal) const;
	void	putref_Major(double newVal);
	//功能：获取或设置椭球长半轴半径

	void	get_Minor(double& MinorVal) const;
	void	putref_Minor(double newVal);
	//功能：获取或设置椭球短半轴半径

	void	get_Flatening(double& FlatenVal) const;
	void	putref_Flatening(double newVal);
	//功能：获取或设置椭球扁率倒数

	void	get_Prj_Name(CString& strPrjName) const;
	void	putref_Prj_Name(const CString& newPrjName);
	//功能：获取或设置椭球投影名称

	void	get_Prj_Type(CString& strPrjType) const;
	void	putref_Prj_Type(const CString& newPrjType);
	//功能：获取或设置椭球投影类型

	void	get_Centrol_Long(double& Val) const;
	void	putref_Centrol_Long(double newVal);
	//功能：获取或设置中央子午线经度

	void	get_We(CString& Val) const;
	void	putref_We(const CString& newVal);
	//功能：获取或设置中央子午线经度

	void	get_Original_Lat(double& Val) const;
	void	putref_Original_Lat(double newVal);
	//功能：获取或设置原点所在的纬度

	void	get_Ns(CString& Val) const;
	void	putref_Ns(const CString& newVal);
	//功能：获取或设置原点所在的纬度

	void	get_False_N(double& Val) const;
	void	putref_False_N(double newVal);
	//功能：获取或设置北坐标假值

	void	get_False_E(double& Val) const;
	void	putref_False_E(double newVal);
	//功能：获取或设置东坐标假值

	void	get_BL_scale(double& Val) const;
	void	putref_BL_scale(double newVal);
	//功能：获取或设置中央子午线/原点纬度比例因子

	void	get_S_Lat(double& Val) const;
	void	putref_S_Lat(double newVal);
	//功能：获取或设置南标准纬线

	void	get_N_Lat(double& Val) const;
	void	putref_N_Lat(double newVal);
	//功能：获取或设置北标准纬线

	//BOOL	IsEmpty();
	////功能：判断椭球是否为空

private:
	CString									m_strEllipName;			//椭球名称
	double									m_SemiMajor;			//椭球长半轴半径
	double									m_SemiMinor;			//椭球短半轴半径
	double									m_Flatening;			//椭球扁率倒数
	CString									m_strProjectName;		//投影名称
	CString									m_strProjectType;		//投影种类
	double									m_CentrolLong;			//中央子午线经度
	CString									m_We;					//
	double									m_OriginalLat;			//原点所在纬度
	CString									m_Ns;					//
	double									m_FalseN;				//北坐标假值
	double									m_FalseE;				//东坐标假值
	double									m_BLScale;				//中央子午线/原点纬度比例因子
	double									m_SLat;					//南标准纬线
	double									m_NLat;					//北标准纬线
};


//*****************************************************************
//类名:			CDeuSpatialReference
//说明:			该类负责提供或设置空间参考参数
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-05
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************

class DeuTranslate_Export_Class CDeuSpatialReference
{
public:
	CDeuSpatialReference();
	virtual ~CDeuSpatialReference();

public:
	//void	get_ProjParm(int&  ncount, std::vector<double>& parm) const;
	//void	putref_ProjParm(int ncount, const std::vector<double>& newParm);
	void	get_ProjParm(int&  ncount, double** parm) const;
	void	putref_ProjParm(int ncount, double* newParm);
	//功能：获取或设置投影参数集合和参数个数

	void	get_Projection(CString& Val) const;
	void	put_Projection(const CString& newVal);
	//功能：获取或设置投影名称

	void	get_Datum(CString& Val) const;
	void	put_Datum(const CString& newVal);
	//功能：获取或设置大地基准面

	void	get_LinearUnit(CString& Val) const;
	void	put_LinearUnit(const CString& newVal);
	//功能：获取或设置投影单位 

	void	get_AngularUnit(CString& Val) const;
	void	put_AngularUnit(const CString& newVal);
	//功能：获取或设置地理坐标系单位

	void	get_PrimeMeridian(CString& Val) const;
	void	put_PrimeMeridian(const CString& newVal);
	//功能：获取或设置起始经度

	void	get_IsProject(BOOL& Val) const;
	void	put_IsProject(BOOL newVal);
	//功能：获取或设置是否是投影坐标

	void	get_ProjeCS(CString& Val) const;
	void	put_ProjeCS(const CString& newVal);
	//功能：获取或设置投影坐标

	void	get_GeogCS(CString& GeogName, CString& Datum, CString& EllipName, double& SemiMajor, double& InvFlattening) const;
	void	put_GeogCS(const CString& GeogName, const CString& Datum, const CString& EllipName, double SemiMajor, double InvFlattening);
	//功能：获取或设置大地坐标系相关参数

private:
	//std::vector<double>						m_ProjParm;				//投影参数集合
	double*									m_ProjParm;
	int										m_ProjCount;			//投影参数个数
	CString									m_Project;				//投影名称
	CString									m_Datum;				//大地基准面
	CString									m_LinearUnit;			//投影坐标系单位
	CString									m_AngularUnit;			//地理坐标系单位
	CString									m_PrimeMeridian;		//本初子午线（起始经度）
	BOOL									m_BIsProject;			//是否是投影坐标系
	CString									m_ProjCSName;			//投影坐标系名称
	CDeuEllipse								m_Ellipse;				//椭球
	CString									m_GeogName;				//地理坐标系名称
};

//*****************************************************************
//类名:			CDeuUnits
//说明:			该类负责提供或设置坐标系单位
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-05
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************
class DeuTranslate_Export_Class CDeuUnits
{
public:
	CDeuUnits();
	virtual ~CDeuUnits();
public:
	void	get_UnitType(CString& Val) const;
	void	putref_UnitType(const CString& newVal);
	//功能：获取或设置单位类型

	static double	TypeToUnit(double oriX, const CString& strType);
	static double	UnitToType(double oriX, const CString& strType);
	//功能：

	void	get_Unit_X(CString& Val) const;
	void	put_Unit_X(const CString& newVal);
	//功能：获取或设置X单位

	void	get_Unit_Y(CString& Val) const;
	void	put_Unit_Y(const CString& newVal);
	//功能：获取或设置Y单位

	void	get_Unit_Z(CString& Val) const;
	void	put_Unit_Z(const CString& newVal);
	//功能：获取或设置Z单位

	void	get_Unit_desX(CString& Val) const;
	void	put_Unit_desX(const CString& newVal);
	//功能：获取或设置目标X单位

	void	get_Unit_desY(CString& Val) const;
	void	put_Unit_desY(const CString& newVal);
	//功能：获取或设置目标Y单位

	void	get_Unit_desZ(CString& Val) const;
	void	put_Unit_desZ(const CString& newVal);
	//功能：获取或设置目标Z单位

private:
	CString									m_sUnit_x;
	CString									m_sUnit_y;
	CString									m_sUnit_Z;
	CString									m_sUnit_des_x;
	CString									m_sUnit_des_y;
	CString									m_sUnit_des_z;
	CString									m_unit_type;
};


//*****************************************************************
//类名:			CDeuCoordType
//说明:			该类负责提供或设置坐标系类型
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-05
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************

class DeuTranslate_Export_Class CDeuCoordType
{
public:
	CDeuCoordType();
	virtual ~CDeuCoordType();
public:
	void	get_CoordType(short& Val) const;
	void	putref_CoordType(short newVal);
	//功能：获取或设置坐标系类型

	void	get_DestCoordType(short& Val) const;
	void	putref_DestCoordType(short newVal);
	//功能：获取或设置目标坐标系类型

	void	get_CtrlPtCoordType(short& Val) const;
	void	putref_CtrlPtCoordType(short newVal);
	//功能：

private:
	short									m_iCoordType;
	short									m_out_CoordType;
	short									m_CtrlPt_CoordType;
};


//*****************************************************************
//类名:			CSevenParams
//说明:			该类负责提供或设置7参数
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-05
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************

class DeuTranslate_Export_Class CSevenParams
{
public:
	CSevenParams();
	virtual ~CSevenParams();
public:
	void	get_DX(double& Val) const;
	void	putref_DX(double newVal);
	//功能：获取或设置平移量X

	void	get_DY(double& Val) const;
	void	putref_DY(double newVal);
	//功能：获取或设置平移量Y

	void	get_DZ(double& Val) const;
	void	putref_DZ(double newVal);
	//功能：获取或设置平移量Z

	void	get_RX(double& Val) const;
	void	putref_RX(double newVal);
	//功能：获取或设置旋转角X

	void	get_RY(double& Val) const;
	void	putref_RY(double newVal);
	//功能：获取或设置旋转角Y

	void	get_RZ(double& Val) const;
	void	putref_RZ(double newVal);
	//功能：获取或设置旋转角Z

	void	get_ScalM(double& Val) const;
	void	putref_ScalM(double newVal);
	//功能：获取或设置比例尺M

private:
	double									m_dx;					//平移量X
	double									m_dy;					//平移量Y
	double									m_dz;					//平移量Z
	double									m_rx;					//旋转角X
	double									m_ry;					//旋转角Y
	double									m_rz;					//旋转角Z
	double									m_ScalM;				//比例尺M
};


//*****************************************************************
//类名:			CDeuConnPool
//说明:			该类负责提供处理数据库连接池
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-06
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************
class DeuTranslate_Export_Class CDeuConnPool
{
public:
	CDeuConnPool();
	virtual ~CDeuConnPool();
public:
	void	get_ConnCount(long& Val) const;
	void	put_ConnCount(long newVal);
	//功能：获取或设置连接数

	HRESULT	Connect(const CString& strConnString, long& ConnId);
	HRESULT	DisConnect(long ConnId);
	//功能：连接数据库或断开数据库

	void	get_Conn(long ConnId, VARIANT** pVal) const;
	void	putref_Conn(long ConnId, VARIANT* newVal);

private:
	std::vector<CDeuConn*>			m_Conn;
};

//*****************************************************************
//类名:			CDeuDatabase
//说明:			该类负责提供处理数据库连接池
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-14
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************
class DeuTranslate_Export_Class CDeuDatabase
{
public:
	CDeuDatabase();
	virtual ~CDeuDatabase();

public:
	void	get_Conn(VARIANT** pVal) const;
	void	putref_Conn(VARIANT* newVal);

	HRESULT	GetTabList(VARIANT** vTabList) const;
	HRESULT	Connect(const CString& strConnString);

	HRESULT get_ConnPool(CDeuConnPool** pVal) const;
	HRESULT putref_ConnPool(CDeuConnPool* newVal);


private:
	CDeuConn*					m_pConn;
	CDeuConnPool*				m_ConnPool;

};

//*****************************************************************
//类名:			CDeuTrans
//说明:			该类负责提供处理矢量数据
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-05
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************

class DeuTranslate_Export_Class CDeuTrans
{
public:
	CDeuTrans();
	virtual ~CDeuTrans();
public:
	HRESULT	CoordTransSingleFile(const CString& strFileName_In, const CString& strDirverName_In,const CString& strFileName_Out,const CString& strDirverName_Out,UINT Id );

	void	get_DeuEllipse(CDeuEllipse& Val) const;
	void	putref_DeuEllipse(const CDeuEllipse& newVal);
	//功能：获取或设置源椭球参数

	void	get_DeuDestEllipse(CDeuEllipse& Val) const;
	void	putref_DeuDestEllipse(const CDeuEllipse& newVal);
	//功能：获取或设置目标椭球参数

	void	get_DeuUnits(CDeuUnits& Val) const;
	void	putref_DeuUnits(const CDeuUnits& newVal);
	//功能：获取或设置坐标系单位

	void	get_DeuCoordType(CDeuCoordType& Val) const;
	void	putref_DeuCoordType(const CDeuCoordType& newVal);
	//功能：获取或设置坐标类型

	void	get_DeuSRS(CDeuSpatialReference** Val) const;
	void	putref_DeuSRS(CDeuSpatialReference* newVal);
	//功能：获取或设置空间参考系

	long	CalculateParam(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* z, DOUBLE* x_2, DOUBLE* y_2, DOUBLE* z_2, DOUBLE* _Param,ULONG* _np);

	void	CoordTransPoints(DOUBLE* _7Param,ULONG n, DOUBLE* oriX, DOUBLE* oriY, DOUBLE* oriZ, DOUBLE* desX, DOUBLE* desY, DOUBLE* desZ);

	void	CalculateResidual(ULONG n, DOUBLE* oriX, DOUBLE* oriY, DOUBLE* oriZ, DOUBLE* desX, DOUBLE* desY, DOUBLE* desZ, DOUBLE* resX, DOUBLE* resY, DOUBLE* resZ, DOUBLE* Residual);

	HRESULT	RegisterWnd(LONGLONG hwnd);

	HRESULT	CoordTransSingleTable(const CString& FileName,UINT SrcConnId,  const CString& outFileName,UINT DesConnId);

	void	get_ConnPool(CDeuConnPool** Val) const;
	void	putref_ConnPool(CDeuConnPool* newVal);
	//功能：获取或设置连接池

	HRESULT CoordTransFileEntry(const CString& SrcTab, const CString& SrcPath, const CString& SrcDriver, const CString& DesTab, const CString& DesPath, const CString& DesDriver, UINT Id);

	HRESULT CoordTransDBEntry(const CString& SrcTab, const CString& SrcPath, const CString& SrcDriver, const CString& DesTab, const CString& DesPath, const CString& DesDriver);

	HRESULT CoordTransDBEntryForBLOB(const CString& SrcTableaName, const CString& SrcConnLink, const CString& SrcUser,  const CString& SrcPwd, const CString& DestTableaName, const CString& DestConnLink, const CString& DestUser,  const CString& DestPwd);

	HRESULT CalcuBLH7P(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* z, DOUBLE* x2, DOUBLE* y2, DOUBLE* z2, DOUBLE* _7Param,ULONG* _np);

	HRESULT Calcuxyh4P(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* _4Param,ULONG* _np);

	HRESULT CalcuXYZ7P(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* z, DOUBLE* x2, DOUBLE* y2, DOUBLE* z2, DOUBLE* _7Param,ULONG* _np);

	HRESULT CalcuBL7P(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2,DOUBLE* _7Param,ULONG* _np);

	HRESULT CoordTransGeometry(DOUBLE* Params, VARIANT oriGeo, VARIANT* desGeo);

	HRESULT CoordTransFileExEntry(const CString& SrcTab, const CString& SrcPath, const CString& SrcDriver, const CString& DesTab, const CString& DesPath, const CString& DesDriver, UINT Id, VARIANT vFormat );


	void get_TransModel(short& Val) const;
	void put_TransModel(short newVal);

	void get_Param(double** Val) const;
	void putref_Param(double* newVal);
	
	void get_Excel(VARIANT& Val) const;
	void putref_Excel(const VARIANT& newVal) const;

	void get_Proid(CString& Val) const;
	void put_Proid(const CString& newVal);

	void get_Pwd(CString& Val) const;
	void put_Pwd(const CString& newVal);

	void get_Proname(CString& Val) const;
	void put_Proname(const CString& newVal);


	HRESULT CDeuTrans::RegisterProc(LONGLONG proc);

	long Use_Gdal_CoordTransSingleFile(const CString& filename,const CString& inDriverName,const CString& filenameout,const CString& outDriverName,UINT Id );

//	HRESULT InitGridTranslate(std::string strFileName);

	HRESULT InitGridTranslate(std::string strFileName);

	//支持ArcSDE矢量转换 add by chenyong 2013-5-7 
	void TransSDEVector(double x1, double y1, double z1, double& x2, double& y2, double& z2);


private:
	int	CoordTransSingleFileExcel(const CString& strFileName_In, const CString& strDirverName_In,const CString& strFileName_Out,const CString& strDirverName_Out, VARIANT vFormat, UINT Id);	
	//功能：支持转换单个Excel文件

	long Use_Deu_CoordTransSingleFile(const CString& strFileName_In, const CString& strDirverName_In,const CString& strFileName_Out,const CString& strDirverName_Out, UINT Id); 
	//功能：支持转换DXF,E00,COVERAGE文件

	void transfun( double x , double y , double z , double & out_x ,double & out_y ,double & out_z );

	int _coordtransf( int fea_FID  , unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);

	void _CoordTransf_D3P7(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);
	void _CoordTransf_D2P4(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);
	void _CoordTransf_BURSA(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);
	void _CoordTransf_D2P7(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);
	void _CoordTransf_GAUSS(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);
	//void _CoordTransf_TM(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);
	void _CoordTransf_UTM(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);
	int _CoordTransf_GRID(unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ);

	double GetRandomDetal(double min_ , double max_);
	/*void	PutStringCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol , double dbVal);
	void	PutStringCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol , double dbVal);
	double	GetDoubleCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol);
	double  GetDoubleCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol);
	char * GetLetter( int iRow , char * szCol);*/
	OGRSpatialReference* SetSRS(CDeuSpatialReference* m_SRS);

	//SDO_geometry * CDeuTrans::CloneGeometry(const SDO_geometry & geo);
private:
	CDeuEllipse								m_ellipse;
	CDeuEllipse								m_des_ellipse;
	CDeuCoordType							m_coordtype;
	CDeuUnits								m_units;
	CDeuSpatialReference*					m_SRS;
	CDeuConnPool*							m_ConnPool;			//该类暂时未定义

	projPJ									m_srcPJ;
	projPJ									m_desPJ;
	double									m_src_a;
	double									m_src_f;
	double									m_src_from_greenwich;
	double									m_src_false_east;
	double									m_des_a;
	double									m_des_f;
	double									m_des_from_greenwich;
	double									m_des_false_east;
	
	//std::vector<double>						m_Params;			//参数集合
	double*									m_Params;
	int										m_TransModel;		//转换模型  注：此处想改成枚举类型，，，

	HWND									m_hwnd;				
	callback_fun							_callback;			

	unsigned long							m_all_fea_count;	//总要素个数
	unsigned long							m_fea_done;			//已经处理要素个数
	unsigned long							m_fea_null_count;	//空要素个数
	unsigned long							m_fea_create_count;	//成功创建要素个数
	unsigned long							m_fea_fail_count;	//创建失败的要素个数

	unsigned long							m_geo_point_count;	//点类型个数
	unsigned long							m_geo_line_count;	//线类型个数
	unsigned long							m_geo_polygon_count;//面类型个数
	unsigned long							m_geo_multi_point_count;		//多点类型个数
	unsigned long							m_geo_multi_line_count;		//多线类型个数
	unsigned long							m_geo_multi_polygon_count;	//多面类型个数
	unsigned long							m_geo_null_count;			//空类型个数
	
	unsigned long							m_error_count;				//错误
	unsigned long							m_geo_ori_error_count;		//原始geometry错误
	unsigned long							m_geo_done;					//已处理的非空geometry个数


public:
	//static TransParams		g_TransParams;

private:
    CGridTranslate                          m_GridTranslate;
};

	//static TransParams		g_TransParams;


//*****************************************************************
//类名:			CDeuRasterTrans
//说明:			该类负责提供处理栅格数据
//责任:			
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		
//制作日期:		2013-01-11
//制作人:	
//版本：		2.0
//修改记录
//*****************************************************************
class CDeuBuffer;
class DeuTranslate_Export_Class CDeuRasterTrans
{
public:
	CDeuRasterTrans();
	virtual ~CDeuRasterTrans();
public:
	void get_SevenParams(CSevenParams& Val) const;
	void putref_SevenParams(const CSevenParams& newVal);
	//获取或设置七参

	void get_DeuEllipse(CDeuEllipse& Val) const;
	void putref_DeuEllipse(const CDeuEllipse& newVal);
	//获取或设置椭球参数

	void get_DeuUnits(CDeuUnits& Val) const;
	void putref_DeuUnits(const CDeuUnits& newVal);
	//获取或设置单位参数

	void get_DeuCoordType(CDeuCoordType& Val) const;
	void putref_DeuCoordType(const CDeuCoordType& newVal);

	void get_DeuDestEllipse(CDeuEllipse& Val) const;
	void putref_DeuDestEllipse(const CDeuEllipse& newVal);

	void get_ConnPool(CDeuConnPool& Val) const;
	void putref_ConnPool(const CDeuConnPool& newVal);
	
	HRESULT CoordTransFile(const CString& FileName, const CString& SrcDriver, const CString& FileNameOut, const CString& DesDriver,UINT Id = 0);

	HRESULT CoordTransFileEntry(const CString& SrcTab, const CString& SrcPath, const CString& SrcDriver, const CString& DesTab, const CString& DesPath, const CString& DesDriver, UINT Id = 0);

	int _coord_transf( double* para,int iTransModel,unsigned long n, double* ori_x, double* ori_y, double* ori_z, double* dest_x, double* dest_y, double* dest_z);

	int _inv_coord_transf( double* para,int iTransModel, unsigned long n, double* ori_x, double* ori_y, double* ori_z, double* dest_x, double* dest_y, double* dest_z);

	HRESULT RegisterWnd(LONGLONG hwnd);

	void get_TransModel(short& pVal) const;
	void put_TransModel(short newVal);

	void get_Resampling(short& pVal) const;
	void put_Resampling(short newVal);

	void get_Param(double**  pVal) const;
	void putref_Param(double* newVal);

	void get_InvParam(double** pVal) const;
	void putref_InvParam(double* newVal);

	void get_DeuSRS(CDeuSpatialReference& pVal) const;
	void putref_DeuSRS(const CDeuSpatialReference& newVal);

	HRESULT CoordTransDEMEntry( const CString& SrcTab,  const CString& SrcPath,  const CString& SrcDriver,  const CString& DesTab,  const CString& DesPath,  const CString& DesDriver);
	HRESULT TransDEM(const CString& FileName,const CString& SrcDriver,  const CString& FileNameOut,const CString& DesDriver);
	HRESULT CalcuPolynomial1(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* dPara);
	HRESULT CalcuPolynomial2(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* dbPara);
	HRESULT CalcuPolynomial3(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* dbPara);
	HRESULT CalcuPolynomial4(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* x2, DOUBLE* y2, DOUBLE* dbPara);

	void _CoordTransf_2D4P( PJ *SrcPJ , PJ *DesPJ , double * dbPara, unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ , bool bInv = false);
	void _CoordTransf_Brusa( PJ *SrcPJ , PJ *DesPJ , double * dbPara, unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ , bool bInv = false);	
	static void _CoordTransf_Poly1(double * dbPara, unsigned long n, double* oriX, double* oriY, double* destX, double* destY ,bool bInv = false);
	static void _CoordTransf_Poly2(double * dbPara, unsigned long n, double* oriX, double* oriY, double* destX, double* destY ,bool bInv = false);
	static void _CoordTransf_Poly3(double * dbPara, unsigned long n, double* oriX, double* oriY, double* destX, double* destY ,bool bInv = false);
	static void _CoordTransf_Poly4(double * dbPara, unsigned long n, double* oriX, double* oriY, double* destX, double* destY ,bool bInv = false);
 	void _CoordTransf_GAUSS( PJ *pj , unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ ,bool bInv = false);
	void _CoordTransf_TM( PJ *pj , unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ ,bool bInv = false);
	void _CoordTransf_UTM( PJ *pj , unsigned long n, double* oriX, double* oriY, double* oriZ, double* destX, double* destY, double* destZ ,bool bInv = false);
	int _CoordTransf_GRID(  unsigned long n, double* oriX, double* oriY, double* destX, double* destY ,bool bInv = false);

	//long Transform_Nearest(BSTR FileName,BSTR SrcDriver, BSTR FileNameOut,BSTR DesDriver);
	//long Transform_BiLinear(BSTR FileName,BSTR SrcDriver, BSTR FileNameOut,BSTR DesDriver);
	//long Transform_BiCubic(BSTR FileName,BSTR SrcDriver, BSTR FileNameOut,BSTR DesDriver);

	HRESULT CalculateParam(ULONG n, DOUBLE* x, DOUBLE* y, DOUBLE* z, DOUBLE* x2, DOUBLE* y2, DOUBLE* z2, DOUBLE* para, ULONG* nPara);
	HRESULT CoordTransPoints(DOUBLE* para, ULONG n, DOUBLE* SrcX, DOUBLE* SrcY, DOUBLE* SrcZ, DOUBLE* DesX, DOUBLE* DesY, DOUBLE* DesZ);
	HRESULT CalculateResidual(ULONG n, DOUBLE* OriX, DOUBLE* OriY, DOUBLE* OriZ, DOUBLE* DesX, DOUBLE* DesY, DOUBLE* DesZ, DOUBLE* ResX, DOUBLE* ResY, DOUBLE* ResZ, DOUBLE* Residual);

	HRESULT RegisterProc(LONGLONG proc);
	HRESULT SpecifiedFrame(  DOUBLE dbLeft ,  DOUBLE dbTop ,LONG lSizeX, LONG lSizeY, DOUBLE dbPixX, DOUBLE dbPixY);
	HRESULT FetchRasterProperty( const CString& FileName ,VARIANT *vFormat  );


	HRESULT InitGridTranslate(std::string strFileName);

private:

	//是否有ige文件	
	bool IsHaveIGE( const CString& SrcTab, const CString& SrcPath );

	//根据定位点信息算detalX,detalY
	int CalculatePixXY(  double adfGeoTransform[6] ,double W,double H , projPJ m_srcPJ ,double & dx ,double & dy );

	void CopyAttributeFile(const CString& FileName, const CString& FileNameOut);

	//设置左上角点和分辨率
	int SetLTPointAndPix( GDALDataset *poDS , GDALDataset *poDSOut,double LTx,double LTy ,double pix_x ,double pix_y);

	//读写栅格文件
	int ReadWriteRasterFile(GDALDataset * poDS , GDALDataset * poDSOut ,int iTransModle ,int iResampling );

	//计算改正量
	int CalculateOffset(double *adfGeoTransform,int nImgSizeX,int nImgSizeY,int iTransModel,double &x,double &y , double &dbDesPix_to_X, double &dbDesPix_to_Y);

	//单点重采样
	int	ResamplingPoint(double *Pt,double* InvPara ,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer & buf,*/void *GrayVal );

	//创建栅格文件
	GDALDataset * CreateRasterFile( const char * szFileNameOut,int iTransModel,GDALDataset *poDS ,const char *pszDesDriver, int nBands,GDALDataType eType, char ** papszOptions,double newPix_to_X, double newPix_to_Y ,double &outNewLT_X, double &outNewLT_Y );

	HRESULT CoordTransDEMFile(const CString& FileName, const CString& SrcDriver, const CString& FileNameOut, const CString& DesDriver,UINT Id);

	int ReadWriteRasterDEMFile(GDALDataset * poDS , GDALDataset * poDSOut ,int iTransModel ,int iResampling );

	int	ResamplingDEMPoint(double *Pt,double* InvPara ,int nImgSizeX , int nImgSizeY ,GDALDataset *poDS,/*CDeuBuffer & buf,*/void *GrayVal );

	BOOL FileFolderExists(CString filename);
public:

	double*						m_Para;
	double*						m_InvPara;
	int							m_TransModel;
	int							m_Resampling;


private:
	CDeuEllipse					m_ellipse;
	CDeuEllipse					m_des_ellipse;
	CDeuCoordType				m_coordtype;
	CDeuUnits					m_units;
	//CDeuSpatialReference*		m_SRS;
	CDeuSpatialReference		m_SRS;
	CDeuConnPool				m_ConnPool;

// 	double*						m_Para;
// 	double*						m_InvPara;
// 	int							m_TransModel;
// 	int							m_Resampling;
	//ANNpointArray				m_pa;
	//ANNbd_tree*					m_bd_tree;
	//ANNpoint					m_q;

	PJ *m_srcPJ ;
	PJ *m_desPJ ;
	double						m_src_a ;
	double						m_src_f ;
	double						m_src_from_greenwich ;
	double						m_src_false_east;
	double						m_des_a ;
	double						m_des_f ;
	double						m_des_from_greenwich ;
	double						m_des_false_east;

	HWND						m_hwnd;
	bool						bCanUse;
	bool						m_bHaveIGE;
	callback_fun				_callback;

	bool						m_bSpecifiedFrame;
	long						m_lSizeX;
	long						m_lSizeY;
	double						m_dbPixX;
	double						m_dbPixY;
	double						m_dbLeft;
	double						m_dbTop;


	CGridTranslate                          m_GridTranslate;

};
/*#ifndef _DEU_TRANSLATE_LIB
	#ifdef _DEBUG
		#pragma comment(lib, "DeuTranslateD.Lib")  
	#else
		#pragma comment(lib, "DeuTranslate.Lib")
	#endif
#endif*/

#endif
