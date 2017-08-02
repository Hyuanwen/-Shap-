/////////////////////////////////////////////////////////////////////
//     项目:	德毅智慧转换软件
//     描述:	GeoDataXml映射类
//     作者：	hushichen
//     修改者：	----
//     主要函数：
//     版本: 
//     修改: 
//     CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////

#include "stdafx.h"


namespace DeuXmlMapping
{


//>>>>>>>>>>>>>>>>>>>>>>>>>>> 重用公共部分 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct Name
{
	CString type;
	CString name;
	CString text;
}_Name, p_Name;


typedef struct Value
{
	CString type;
	CString name;
	CString text;
}_Value, p_Value;


typedef struct Remark
{
	CString type;
	CString name;
	CString text;
}_Remark, p_Remark;

//region-------------------------------
/*
<!--数据定义-->
<Envelope type="Envelope" name="Envelope"><!--envelope-->
	<Name type="Name" name="Envelope">China-east of 132DE</Name>
	<Remark type="Remark" name="Envelope Remark">#</Remark>
	<MinPoint type="MinPoint" name="Minimum Point">
		<Long type="Long" name="Longitude">132</Long>
		<Lat type="Lat" name="Latitude">45.02</Lat>
	</MinPoint>
	<MaxPoint type="MaxPoint" name="Maximum Point">
		<Long type="Long" name="Longitude">134.77</Long>
		<Lat type="Lat" name="Latitude">48.39</Lat>
	</MaxPoint>
</Envelope>
*/
typedef struct Long
{
	CString type;
	CString name;
	CString text;
}_Long;


typedef struct Lat
{
	CString type;
	CString name;
	CString text;
}_Lat;


typedef struct MinPoint
{
	CString type;
	CString name;
	
	_Long _long;
	_Lat _lat;

}_MinPoint;

typedef struct MaxPoint
{
	CString type;
	CString name;

	_Long _long;
	_Lat _lat;

}_MaxPoint;

typedef struct Envelope
{
	CString type;
	CString name;

	_Name _name;
	_Remark _remark;
	_MinPoint _minpoint;
	_MaxPoint _maxpoint;
	
}_Envelope;

//endregion----------------------------




//region-------------------------------

typedef struct Dimensions 
{
	CString type;
	CString name;
	CString text;

}_Dimensions;

typedef struct Label
{
	CString type;
	CString name;
	CString text;
}_Label;

//{
typedef struct Abbreviation
{
	CString type;
	CString name;
	CString text;
}_Abbreviation;


typedef struct Per_Meter
{
	CString type;
	CString name;
	CString text;
}_Per_Meter;


//此处为单位节点，区别Units
typedef struct Unit
{
	CString type;
	CString name;
	CString text;

}_Unit;

typedef struct Unit_1
{
	CString type;
	CString name;

	_Name _name;
	_Remark _remark;
	_Abbreviation _abbreviation;
	_Per_Meter _per_Meter;

}_Unit_1;


typedef struct Per_Degree
{
	CString type;
	CString name;
	CString text;
}_Per_Degree;


typedef struct Unit_2
{
	CString type;
	CString name;

	_Name _name;
	_Remark _remark;
	_Abbreviation _abbreviation;
	_Per_Degree _per_Degree;

}_Unit_2;
//	}


typedef struct GeoDeticLong
{
	CString type;
	CString name;

	_Value _value;
	_Unit_2 _unit_2;

}_GeoDeticLong;


typedef struct GeoDeticLat
{
	CString type;
	CString name;

	_Value _value;
	_Unit_2 _unit_2;

}_GeoDeticLat;


typedef struct GeoDeticLongForPS //PointStyle
{
	CString type;
	CString name;

	_Label _label;
	_Unit_2 _unit_2;

}_GeoDeticLongForPS;


typedef struct GeoDeticLatForPS //PointStyle
{
	CString type;
	CString name;

	_Label _label;
	_Unit_2 _unit_2;

}_GeoDeticLatForPS;



typedef struct East
{
	CString type;
	CString name;
	
	_Label _label;
	_Unit_1 _unit_1;

}_East;

typedef struct North
{
	CString type;
	CString name;

	_Label _label;
	_Unit_1 _unit_1;

}_North;

typedef struct EllipsoidHeight
{
	CString type;
	CString name;

	_Label _label;
	_Unit_1 _unit_1;

}_EllipsoidHeight;

typedef struct GeoDeticPointStyle
{
	CString type;
	CString name;
	
	_Name _name;
	_Remark _remark;
	_Dimensions _dimensions;
	_GeoDeticLongForPS _geoDeticLongForPS; //PS == PointStyle
	_GeoDeticLatForPS _geoDeticLatForPS;
	_EllipsoidHeight _ellipsoidHeight;

}_GeoDeticPointStyle;


typedef struct ProjectionPointStyle
{
	CString type;
	CString name;

	_Name _name;
	_Remark _remark;
	_Dimensions _dimensions;
	_East _east;
	_North _north;
	_EllipsoidHeight _ellipsoidHeight;

}_ProjectionPointStyle;


typedef struct CentralMeridian 
{
	CString type;
	CString name;	

	_Name _name;
	_Value _value;
	_Unit _uint;

}_CentralMeridian;


typedef struct FalseEasting 
{
	CString type;
	CString name;

	_Name _name;
	_Value _value;
	_Unit _uint;

}_FalseEasting;


typedef struct FalseNorthing 
{
	CString type;
	CString name;

	_Name _name;
	_Value _value;
	_Unit _uint;

}_FalseNorthing;


typedef struct LatitudeOfOrigin 
{
	CString type;
	CString name;

	_Name _name;
	_Value _value;
	_Unit _uint;

}_LatitudeOfOrigin;


typedef struct ScaleFactor 
{
	CString type;
	CString name;

	_Name _name;
	_Value _value;
	_Unit _uint;

}_ScaleFactor;


//	Semi-Minor-Axis
typedef struct Semi_Minor_Axis
{
	CString type;
	CString name;
	_Value _value;
	_Unit_1 _unit_1;

}_Semi_Minor_Axis;

//	Semi-Major-Axis
typedef struct Semi_Major_Axis
{
	CString type;
	CString name;
	_Value _value;
	_Unit_1 _unit_1;

}_Semi_Major_Axis;


typedef struct InverseFlattening
{
	CString type;
	CString name;
	CString text;

}_InverseFlattening;


typedef struct Ellipsoid
{
	CString type;
	CString name;

	_Name _name;
	_Remark _remark;
	_Semi_Minor_Axis _semi_Minor_Axis;
	_Semi_Major_Axis _semi_Major_Axis;
	_InverseFlattening _inverseFlattening;

}_Ellipsoid;


typedef struct PrimeMeridian
{
	CString type;
	CString name;

	_Name _name;
	_GeoDeticLong _geoDeticLong;

}_PrimeMeridian;



typedef struct Datum
{
	CString type;
	CString name;

	_Name _name;
	_Remark _remark;
	_Ellipsoid _ellipsoid;
	_PrimeMeridian _primeMeridian;

}_Datum;



//endregion----------------------------


//	<CSType type="CSType" name="CSType">projected</CSType>
typedef struct CSType
{
	CString type;
	CString name;
	CString text;

}_CSType;


//   <Projection type="Projection" name="Projection">高斯投影</Projection>
typedef struct Projection
{
	CString type;
	CString name;
	CString text;

}_Projection;


//  <GeodeticPointor type="GeodeticPointor" name="Geodetic">geodeticXiAn80</GeodeticPointor><!--大地指针-->
typedef struct GeodeticPointor
{
	CString type;
	CString name;
	CString text;

}_GeodeticPointor;


typedef struct BaseStruct
{
	CoordinateType _coordinateType;	//坐标类型
	TranStandard   _tranStandard;	//转换标准
}_BaseStruct, *p_BaseStruct;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>> 投影坐标 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//投影坐标
typedef struct ProjectedSeries : BaseStruct
	{
		CString type;
		CString name;

		_Name					_name;
		_Remark					_remark;
		_Envelope				_envelope;
		_ProjectionPointStyle	_pointStyle;
		_GeodeticPointor		_geodeticPointor;
		_Projection				_projection;
		_CentralMeridian		_centralMeridian;
		_FalseEasting			_falseEasting;
		_FalseNorthing			_falseNorthing;
		_LatitudeOfOrigin		_latitudeOfOrigin;
		_ScaleFactor			_scaleFactor;
		_CSType					_csType;

	}_ProjectedSeries, *p_ProjectedSeries;



	//投影坐标结构
	typedef struct Projected
	{
		CString type;
		CString name;

		CArray<_ProjectedSeries>  pProjectedSeries;

	} _Projected, *p_Projected;


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 大地坐标 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	

	//北京80标准
	typedef struct GeodeticSeries : BaseStruct
	{
		CString type;
		CString name;

		_Name					_name;
		_Remark					_remark;
		_Envelope				_envelope;
		_GeoDeticPointStyle		_pointStyle;
		_Datum					_datum;
		_CSType					_csType;

	}_GeodeticSeries, *p_GeodeticSeries;


	//大地坐标结构
	typedef struct Geodetic
	{
		CString type;
		CString name;
		CArray<_GeodeticSeries> pGeodeticSeries;

	} _Geodetic, *p_Geodetic;


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 单位 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//这里定义子节有偏差，暂时不修正
	typedef struct UnitsGeodetic
	{
		CString X;
		CString Y;
		CString Z;

	} _UnitsGeodetic, *p_UnitsGeodetic;

	typedef struct UnitsGeocentric
	{
		CString X;
		CString Y;
		CString Z;

	} _UnitsGeocentric, *p_UnitsGeocentric;

	typedef struct UnitsPlane
	{
		CString X;
		CString Y;
		CString Z;

	} _UnitsPlane, *p_UnitsPlane;

	typedef struct Units
	{
		_UnitsGeodetic Geodetic;
		_UnitsGeocentric Geocentric;
		_UnitsPlane Plane;

	} _Units, *p_Units;


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Xml 根数据 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//GeoDataXml根节点
	typedef struct GeoDataXml
	{
		CString name;
		_Projected  ProjectedNode;
		_Geodetic  GeodeticNode;
		_Units	   UnitsNode;

	} _GeoDataXml, *p_GeoDataXml;


	//CP控制点数据
	typedef struct ControlPointPair
	{
		CString X_SRC;
		CString Y_SRC;
		CString Z_SRC;

		CString X_DEST;
		CString Y_DEST;
		CString Z_DEST;

		CString X_Residual;
		CString Y_Residual;
		CString Z_Residual;

		CString Total_Residual;

	}_ControlPointPair, *p_ControlPointPair;

	typedef struct ControlPointPairs
	{
		CArray<_ControlPointPair*> _controlPointPair;

	}_ControlPointPairs, *p_ControlPointPairs;

	//转换文件格式名 add by chenyong 2013-4-3
	typedef struct StrFormatType
	{
		CString	type;
		CString name;
		CString text;
	}_StrFormatType, *p_StrFormatType;

	typedef struct StrFormatTypeList
	{
		CString type;
		CString name;
		std::vector<_StrFormatType> TypeList;
	}_StrFormatTypeList, *p_StrFormatTypeList;

	typedef struct StrFormatList
	{
		CString type;
		CString name;
		std::vector<p_StrFormatTypeList> FormatTypeList;
	}_StrFormatList, *p_StrFormatList;
	//end


	//=========================== TaskInfo ===========================
	
	/*
	<CDeuTask type="CDeuTask" name="">
		<IN_PATH type="IN_PATH" name="IN_PATH">E:\可写\测评数据\矢量\厦门北</IN_PATH> 
		<OUT_PATH type="OUT_PATH" name="OUT_PATH">D:\daifeng\Batch</OUT_PATH> 
		<IN_DRIVER type="IN_DRIVER" name="IN_DRIVER">ESRI Shapefile</IN_DRIVER> 
		<OUT_DRIVER type="OUT_DRIVER" name="OUT_DRIVER">ESRI Shapefile</OUT_DRIVER> 
		<ELlIP_NAME type="ELlIP_NAME" name="ELlIP_NAME">geodeticbeijing54</ELlIP_NAME> 
		<OUT_ELLIP_NAME type="OUT_ELLIP_NAME" name="OUT_ELLIP_NAME">geodeticXiAn80</OUT_ELLIP_NAME> 
		<COORDTYPE type="COORDTYPE" name="COORDTYPE">1</COORDTYPE> 
		<Out_COORDTYPE type="Out_COORDTYPE" name="Out_COORDTYPE">1</Out_COORDTYPE> 
		<InCentr_long type="InCentr_long" name="InCentr_long">0.0</InCentr_long> 
		<OutCentr_long type="OutCentr_long" name="OutCentr_long">0.0</OutCentr_long> 
		<Type type="Type" name="Type">0</Type> 
		<Status type="Status" name="Status">2</Status> 
		<CurTable type="CurTable" name="CurTable">面状水系</CurTable> 
		- <TableList type="TableList" name="TableList">
		<tab type="tab" name="tab">面状水系</tab> 
		</TableList>
	</CDeuTask>
	*/

	struct BaseTask
	{
		CString type;
		CString name;
		CString text;
	};

	//输入输出文件路径
	typedef struct InPath : BaseTask
	{
	}_InPath, *p_InPath;

	typedef struct OutPath : BaseTask
	{
	}_OutPath, *p_OutPath;

	//输入输出文件驱动
	typedef struct OutDriver : BaseTask
	{
	}_OutDriver, *p_OutDriver;

	typedef struct InDriver : BaseTask
	{
	}_InDriver, *p_InDriver;

	//输入输出椭球
	typedef struct InEllipse : BaseTask
	{
	}_InEllipse, *p_InEllipse;

	typedef struct OutEllipse : BaseTask
	{
	}_OutEllipse, *p_OutEllipse;
	
	// 1-大地 2-暂无 3-平面(投影)
	typedef struct InCoordType : BaseTask
	{
	}_InCoordType, *p_InCoordType;


	typedef struct OutCoordType : BaseTask
	{
	}_OutCoordType, *p_OutCoordType;


	//中央子午线
	typedef struct InCentralMeridian : BaseTask
	{
	}_InCentralMeridian, *p_InCentralMeridian;

	typedef struct OutCentralMeridian : BaseTask
	{
	}_OutCentralMeridian, *p_OutCentralMeridian;


	//类型是矢量或者栅格
	// 0-矢量 1 - 栅格
	typedef struct Type : BaseTask
	{
	}_Type, *p_Type;
	
	//执行状态
	typedef struct Status : BaseTask
	{
	}_Status, *p_Status;
		
	//执行当中的文件或者数据库表
	typedef struct CurPart : BaseTask
	{
	}_CurPart, *p_CurPart;

	//所有的需要执行的文件或者数据库表
	typedef struct Part : BaseTask
	{
	}_Part, *p_Part;

	//控制点文件路径 add by chenyong 2013-3-28
	typedef struct ControlPath : BaseTask
	{

	}_ControlPath, *p_ControlPath;

	//转换模型 add by chenyong 2013-3-28
	typedef struct TransModel : BaseTask
	{

	}_TransModel, *p_TransModel;

	//所有的文件或者数据库表
	typedef struct Parts
	{
		CString type;
		CString name;

		CArray<_Part> m_Part;

	}_Parts, *p_Parts;


	//具体任务
	typedef struct Task
	{
		CString id;
		CString type;
		CString name;

		_InPath _inpath;
		_OutPath _outpath;
		
		_InDriver _inDriver;
		_OutDriver _outDriver;
		
		_InEllipse _inEllipse;
		_OutEllipse _outEllipse;
		
		_InCoordType _inCoordType;
		_OutCoordType _outCoordType;
		
		_InCentralMeridian _inCentralMeridian;
		_OutCentralMeridian _outCentralMeridian;
		
		_Type _type;
		_Status _status;
		
		_CurPart _curPart;
		_Parts _parts;

		//add by chenyong 2013-3-28
		_ControlPath _controlPath;
		_TransModel _transModel;
	}_Task, *p_Task;


	//所有任务
	typedef struct Tasks
	{
		CString type;
		CString name;
		CArray<_Task*> _task;

	}_Tasks, *p_Tasks;
	

}
