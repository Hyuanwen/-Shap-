/////////////////////////////////////////////////////////////////////
//     项目: 德毅智慧转换软件
//     描述:	视图公共接口类，该类由程序对应自动生成
//     作者：	hushichen
//     修改者：	----
//     CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////

#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被改写。

/////////////////////////////////////////////////////////////////////////////
// CDeuDMap 包装类

class CDeuDMap : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDeuDMap)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x54F4C2F7, 0xED40, 0x43B7, { 0x9D, 0x6F, 0xE4, 0x59, 0x65, 0xDF, 0x7F, 0x95 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID, 
		CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
		UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
			pPersist, bStorage, bstrLicKey); 
	}

	// 属性
public:
	enum
	{
		cmZoomIn = 0,
		cmZoomOut = 1,
		cmPan = 2,
		cmSelection = 3,
		cmNone = 4
	}tkCursorMode;
	enum
	{
		crsrMapDefault = 0,
		crsrAppStarting = 1,
		crsrArrow = 2,
		crsrCross = 3,
		crsrHelp = 4,
		crsrIBeam = 5,
		crsrNo = 6,
		crsrSizeAll = 7,
		crsrSizeNESW = 8,
		crsrSizeNS = 9,
		crsrSizeNWSE = 10,
		crsrSizeWE = 11,
		crsrUpArrow = 12,
		crsrWait = 13,
		crsrUserDefined = 14
	}tkCursor;
	enum
	{
		lmUnlock = 0,
		lmLock = 1
	}tkLockMode;
	enum
	{
		dmStandard = 0,
		dmNewWithSelection = 1
	}tkShapeDrawingMethod;
	enum
	{
		hjLeft = 0,
		hjCenter = 1,
		hjRight = 2,
		hjNone = 3,
		hjRaw = 4
	}tkHJustification;
	enum
	{
		dlScreenReferencedList = 0,
		dlSpatiallyReferencedList = 1
	}tkDrawReferenceList;
	enum
	{
		lsNone = 0,
		lsDotted = 1,
		lsDashed = 2,
		lsDashDotDash = 3,
		lsDoubleSolid = 4,
		lsDoubleSolidPlusDash = 5,
		lsTrainTracks = 6,
		lsCustom = 7,
		lsDashDotDot = 8
	}tkLineStipple;
	enum
	{
		fsNone = 0,
		fsVerticalBars = 1,
		fsHorizontalBars = 2,
		fsDiagonalDownRight = 3,
		fsDiagonalDownLeft = 4,
		fsPolkaDot = 5,
		fsCustom = 6,
		fsCross = 7,
		fsRaster = 8
	}tkFillStipple;
	enum
	{
		ptSquare = 0,
		ptCircle = 1,
		ptDiamond = 2,
		ptTriangleUp = 3,
		ptTriangleDown = 4,
		ptTriangleLeft = 5,
		ptTriangleRight = 6,
		ptUserDefined = 7,
		ptImageList = 8,
		ptFontChar = 9
	}tkPointType;
	enum
	{
		rbClassic = 0,
		rbModern = 1,
		rbIntuitive = 2,
		rbWarp = 3,
		rbKeepScale = 4
	}tkResizeBehavior;
	enum
	{
		ShortDataType = 0,
		LongDataType = 1,
		FloatDataType = 2,
		DoubleDataType = 3,
		InvalidDataType = -1,
		UnknownDataType = 4,
		ByteDataType = 5
	}GridDataType;
	enum
	{
		Ascii = 0,
		Binary = 1,
		Esri = 2,
		GeoTiff = 3,
		Sdts = 4,
		PAux = 5,
		PCIDsk = 6,
		DTed = 7,
		Bil = 8,
		Ecw = 9,
		MrSid = 10,
		Flt = 11,
		Dem = 12,
		UseExtension = 13,
		InvalidGridFileType = -1
	}GridFileType;
	enum
	{
		Hillshade = 0,
		Gradient = 1,
		Random = 2
	}ColoringType;
	enum
	{
		Logorithmic = 0,
		Linear = 1,
		Exponential = 2
	}GradientModel;
	enum
	{
		FallLeaves = 0,
		SummerMountains = 1,
		Desert = 2,
		Glaciers = 3,
		Meadow = 4,
		ValleyFires = 5,
		DeadSea = 6,
		Highway1 = 7
	}PredefinedColorScheme;
	enum
	{
		BITMAP_FILE = 0,
		GIF_FILE = 1,
		USE_FILE_EXTENSION = 2,
		TIFF_FILE = 3,
		JPEG_FILE = 4,
		PNG_FILE = 5,
		PPM_FILE = 7,
		ECW_FILE = 8,
		JPEG2000_FILE = 9,
		SID_FILE = 10,
		PNM_FILE = 11,
		PGM_FILE = 12,
		BIL_FILE = 13,
		ADF_FILE = 14,
		GRD_FILE = 15,
		IMG_FILE = 16,
		ASC_FILE = 17,
		BT_FILE = 18,
		MAP_FILE = 19,
		LF2_FILE = 20,
		KAP_FILE = 21,
		DEM_FILE = 22
	}ImageType;
	enum
	{
		SHP_NULLSHAPE = 0,
		SHP_POINT = 1,
		SHP_POLYLINE = 3,
		SHP_POLYGON = 5,
		SHP_MULTIPOINT = 8,
		SHP_POINTZ = 11,
		SHP_POLYLINEZ = 13,
		SHP_POLYGONZ = 15,
		SHP_MULTIPOINTZ = 18,
		SHP_POINTM = 21,
		SHP_POLYLINEM = 23,
		SHP_POLYGONM = 25,
		SHP_MULTIPOINTM = 28,
		SHP_MULTIPATCH = 31
	}ShpfileType;
	enum
	{
		srContains = 0,
		srCrosses = 1,
		srDisjoint = 2,
		srEquals = 3,
		srIntersects = 4,
		srOverlaps = 5,
		srTouches = 6,
		srWithin = 7
	}tkSpatialRelation;
	enum
	{
		clDifference = 0,
		clIntersection = 1,
		clSymDifference = 2,
		clUnion = 3
	}tkClipOperation;
	enum
	{
		INTERSECTION = 0,
		INCLUSION = 1
	}SelectMode;
	enum
	{
		STRING_FIELD = 0,
		INTEGER_FIELD = 1,
		DOUBLE_FIELD = 2
	}FieldType;
	enum
	{
		Z_VALUE = 0,
		DISTANCE_TO_OUTLET = 1,
		NO_RESOLUTION = 2
	}AmbiguityResolution;
	enum
	{
		DIFFERENCE_OPERATION = 0,
		INTERSECTION_OPERATION = 1,
		EXCLUSIVEOR_OPERATION = 2,
		UNION_OPERATION = 3
	}PolygonOperation;
	enum
	{
		InscribedRadius = 0,
		AngleDeviation = 1
	}SplitMethod;


	// 操作
public:

	// _DMap

	// Functions
	//

	void Redraw()
	{
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long AddLayer(LPDISPATCH Object, BOOL Visible)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Object, Visible);
		return result;
	}
	void RemoveLayer(long LayerHandle)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle);
	}
	void RemoveLayerWithoutClosing(long LayerHandle)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle);
	}
	void RemoveAllLayers()
	{
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL MoveLayerUp(long InitialPosition)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, InitialPosition);
		return result;
	}
	BOOL MoveLayerDown(long InitialPosition)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, InitialPosition);
		return result;
	}
	BOOL MoveLayer(long InitialPosition, long TargetPosition)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, InitialPosition, TargetPosition);
		return result;
	}
	BOOL MoveLayerTop(long InitialPosition)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, InitialPosition);
		return result;
	}
	BOOL MoveLayerBottom(long InitialPosition)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, InitialPosition);
		return result;
	}
	void ZoomToMaxExtents()
	{
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ZoomToLayer(long LayerHandle)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle);
	}
	void ZoomToShape(long LayerHandle, long Shape)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, Shape);
	}
	void ZoomIn(double Percent)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Percent);
	}
	void ZoomOut(double Percent)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Percent);
	}
	long ZoomToPrev()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void ProjToPixel(double projX, double projY, double * pixelX, double * pixelY)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, parms, projX, projY, pixelX, pixelY);
	}
	void PixelToProj(double pixelX, double pixelY, double * projX, double * projY)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_PR8 VTS_PR8 ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pixelX, pixelY, projX, projY);
	}
	void ClearDrawing(long DrawHandle)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DrawHandle);
	}
	void ClearDrawings()
	{
		InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH SnapShot(LPDISPATCH BoundBox)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, BoundBox);
		return result;
	}
	BOOL ApplyLegendColors(LPDISPATCH Legend)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Legend);
		return result;
	}
	void LockWindow(long LockMode)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LockMode);
	}
	void Resize(long Width, long Height)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Width, Height);
	}
	void ShowToolTip(LPCTSTR Text, long Milliseconds)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Text, Milliseconds);
	}
	void AddLabel(long LayerHandle, LPCTSTR Text, unsigned long Color, double x, double y, long hJustification)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_UI4 VTS_R8 VTS_R8 VTS_I4 ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, Text, Color, x, y, hJustification);
	}
	void ClearLabels(long LayerHandle)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle);
	}
	void LayerFont(long LayerHandle, LPCTSTR FontName, long FontSize)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, FontName, FontSize);
	}
	LPDISPATCH GetColorScheme(long LayerHandle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerHandle);
		return result;
	}
	long NewDrawing(long Projection)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Projection);
		return result;
	}
	void DrawPoint(double x, double y, long pixelSize, unsigned long Color)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, pixelSize, Color);
	}
	void DrawLine(double x1, double y1, double x2, double y2, long pixelWidth, unsigned long Color)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x1, y1, x2, y2, pixelWidth, Color);
	}
	void DrawCircle(double x, double y, double pixelRadius, unsigned long Color, BOOL fill)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_UI4 VTS_BOOL ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, pixelRadius, Color, fill);
	}
	void DrawPolygon(VARIANT * xPoints, VARIANT * yPoints, long numPoints, unsigned long Color, BOOL fill)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_I4 VTS_UI4 VTS_BOOL ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPoints, yPoints, numPoints, Color, fill);
	}
	CString get_LayerKey(long LayerHandle)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_LayerKey(long LayerHandle, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	long get_LayerPosition(long LayerHandle)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle);
		return result;
	}
	long get_LayerHandle(long LayerPosition)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerPosition);
		return result;
	}
	BOOL get_LayerVisible(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_LayerVisible(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	unsigned long get_ShapeLayerFillColor(long LayerHandle)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerFillColor(long LayerHandle, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	unsigned long get_ShapeFillColor(long LayerHandle, long Shape)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeFillColor(long LayerHandle, long Shape, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	unsigned long get_ShapeLayerLineColor(long LayerHandle)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerLineColor(long LayerHandle, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	unsigned long get_ShapeLineColor(long LayerHandle, long Shape)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeLineColor(long LayerHandle, long Shape, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	unsigned long get_ShapeLayerPointColor(long LayerHandle)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerPointColor(long LayerHandle, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	unsigned long get_ShapePointColor(long LayerHandle, long Shape)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapePointColor(long LayerHandle, long Shape, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	BOOL get_ShapeLayerDrawFill(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerDrawFill(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	BOOL get_ShapeDrawFill(long LayerHandle, long Shape)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeDrawFill(long LayerHandle, long Shape, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	BOOL get_ShapeLayerDrawLine(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerDrawLine(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	BOOL get_ShapeDrawLine(long LayerHandle, long Shape)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeDrawLine(long LayerHandle, long Shape, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	BOOL get_ShapeLayerDrawPoint(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerDrawPoint(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x44, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	BOOL get_ShapeDrawPoint(long LayerHandle, long Shape)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeDrawPoint(long LayerHandle, long Shape, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	float get_ShapeLayerLineWidth(long LayerHandle)
	{
		float result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerLineWidth(long LayerHandle, float newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R4 ;
		InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	float get_ShapeLineWidth(long LayerHandle, long Shape)
	{
		float result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeLineWidth(long LayerHandle, long Shape, float newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x47, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	float get_ShapeLayerPointSize(long LayerHandle)
	{
		float result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerPointSize(long LayerHandle, float newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R4 ;
		InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	float get_ShapePointSize(long LayerHandle, long Shape)
	{
		float result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapePointSize(long LayerHandle, long Shape, float newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x49, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	float get_ShapeLayerFillTransparency(long LayerHandle)
	{
		float result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerFillTransparency(long LayerHandle, float newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R4 ;
		InvokeHelper(0x4a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	float get_ShapeFillTransparency(long LayerHandle, long Shape)
	{
		float result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeFillTransparency(long LayerHandle, long Shape, float newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x4b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	long get_ShapeLayerLineStipple(long LayerHandle)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerLineStipple(long LayerHandle, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	long get_ShapeLineStipple(long LayerHandle, long Shape)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeLineStipple(long LayerHandle, long Shape, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	long get_ShapeLayerFillStipple(long LayerHandle)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerFillStipple(long LayerHandle, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x4e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	long get_ShapeFillStipple(long LayerHandle, long Shape)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeFillStipple(long LayerHandle, long Shape, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x4f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	BOOL get_ShapeVisible(long LayerHandle, long Shape)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeVisible(long LayerHandle, long Shape, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	float get_ImageLayerPercentTransparent(long LayerHandle)
	{
		float result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ImageLayerPercentTransparent(long LayerHandle, float newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R4 ;
		InvokeHelper(0x51, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	CString get_ErrorMsg(long ErrorCode)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ErrorCode);
		return result;
	}
	CString get_DrawingKey(long DrawHandle)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x53, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, DrawHandle);
		return result;
	}
	void put_DrawingKey(long DrawHandle, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x53, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, DrawHandle, newValue);
	}
	long get_ShapeLayerPointType(long LayerHandle)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerPointType(long LayerHandle, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x54, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	long get_ShapePointType(long LayerHandle, long Shape)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapePointType(long LayerHandle, long Shape, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x55, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	BOOL get_LayerLabelsVisible(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_LayerLabelsVisible(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x56, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	long get_UDLineStipple(long LayerHandle)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_UDLineStipple(long LayerHandle, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x57, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	long get_UDFillStipple(long LayerHandle, long StippleRow)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle, StippleRow);
		return result;
	}
	void put_UDFillStipple(long LayerHandle, long StippleRow, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x58, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, StippleRow, newValue);
	}
	LPDISPATCH get_UDPointType(long LayerHandle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, LayerHandle);
		return result;
	}
	void putref_UDPointType(long LayerHandle, LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x59, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	LPDISPATCH get_GetObject(long LayerHandle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, LayerHandle);
		return result;
	}
	CString get_LayerName(long LayerHandle)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_LayerName(long LayerHandle, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x5b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	BOOL SetImageLayerColorScheme(long LayerHandle, LPDISPATCH ColorScheme)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, LayerHandle, ColorScheme);
		return result;
	}
	CString get_GridFileName(long LayerHandle)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_GridFileName(long LayerHandle, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x5d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	void UpdateImage(long LayerHandle)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle);
	}
	BOOL get_LayerLabelsShadow(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_LayerLabelsShadow(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	BOOL get_LayerLabelsScale(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_LayerLabelsScale(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x62, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	void AddLabelEx(long LayerHandle, LPCTSTR Text, unsigned long Color, double x, double y, long hJustification, double Rotation)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_UI4 VTS_R8 VTS_R8 VTS_I4 VTS_R8 ;
		InvokeHelper(0x63, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, Text, Color, x, y, hJustification, Rotation);
	}
	void GetLayerStandardViewWidth(long LayerHandle, double * Width)
	{
		static BYTE parms[] = VTS_I4 VTS_PR8 ;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, Width);
	}
	void SetLayerStandardViewWidth(long LayerHandle, double Width)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, Width);
	}
	long get_LayerLabelsOffset(long LayerHandle)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_LayerLabelsOffset(long LayerHandle, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	unsigned long get_LayerLabelsShadowColor(long LayerHandle)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_LayerLabelsShadowColor(long LayerHandle, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	BOOL get_UseLabelCollision(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_UseLabelCollision(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	BOOL IsTIFFGrid(LPCTSTR Filename)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Filename);
		return result;
	}
	BOOL IsSameProjection(LPCTSTR proj4_a, LPCTSTR proj4_b)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, proj4_a, proj4_b);
		return result;
	}
	void ZoomToMaxVisibleExtents()
	{
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void put_MapResizeBehavior(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MapResizeBehavior()
	{
		long result;
		InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long HWnd()
	{
		long result;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long set_UDPointImageListAdd(long LayerHandle, LPDISPATCH newValue)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LayerHandle, newValue);
		return result;
	}
	long get_ShapePointImageListID(long LayerHandle, long Shape)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapePointImageListID(long LayerHandle, long Shape, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	long get_UDPointImageListCount(long LayerHandle)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LayerHandle);
		return result;
	}
	LPDISPATCH get_UDPointImageListItem(long LayerHandle, long ImageIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x71, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerHandle, ImageIndex);
		return result;
	}
	void ClearUDPointImageList(long LayerHandle)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle);
	}
	void DrawLineEx(long LayerHandle, double x1, double y1, double x2, double y2, long pixelWidth, unsigned long Color)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, x1, y1, x2, y2, pixelWidth, Color);
	}
	void DrawPointEx(long LayerHandle, double x, double y, long pixelSize, unsigned long Color)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, x, y, pixelSize, Color);
	}
	void DrawCircleEx(long LayerHandle, double x, double y, double pixelRadius, unsigned long Color, BOOL fill)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_UI4 VTS_BOOL ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, x, y, pixelRadius, Color, fill);
	}
	void LabelColor(long LayerHandle, unsigned long LabelFontColor)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, LabelFontColor);
	}
	void SetDrawingLayerVisible(long LayerHandle, BOOL Visiable)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, Visiable);
	}
	void ClearDrawingLabels(long DrawHandle)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x79, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DrawHandle);
	}
	void DrawingFont(long DrawHandle, LPCTSTR FontName, long FontSize)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DrawHandle, FontName, FontSize);
	}
	void AddDrawingLabelEx(long DrawHandle, LPCTSTR Text, unsigned long Color, double x, double y, long hJustification, double Rotation)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_UI4 VTS_R8 VTS_R8 VTS_I4 VTS_R8 ;
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DrawHandle, Text, Color, x, y, hJustification, Rotation);
	}
	void AddDrawingLabel(long DrawHandle, LPCTSTR Text, unsigned long Color, double x, double y, long hJustification)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_UI4 VTS_R8 VTS_R8 VTS_I4 ;
		InvokeHelper(0x7c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DrawHandle, Text, Color, x, y, hJustification);
	}
	long get_DrawingLabelsOffset(long DrawHandle)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, DrawHandle);
		return result;
	}
	void put_DrawingLabelsOffset(long DrawHandle, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x7d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, DrawHandle, newValue);
	}
	BOOL get_DrawingLabelsScale(long DrawHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, DrawHandle);
		return result;
	}
	void put_DrawingLabelsScale(long DrawHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, DrawHandle, newValue);
	}
	BOOL get_DrawingLabelsShadow(long DrawHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, DrawHandle);
		return result;
	}
	void put_DrawingLabelsShadow(long DrawHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, DrawHandle, newValue);
	}
	unsigned long get_DrawingLabelsShadowColor(long DrawHandle)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, DrawHandle);
		return result;
	}
	void put_DrawingLabelsShadowColor(long DrawHandle, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, DrawHandle, newValue);
	}
	BOOL get_UseDrawingLabelCollision(long DrawHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, DrawHandle);
		return result;
	}
	void put_UseDrawingLabelCollision(long DrawHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x81, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, DrawHandle, newValue);
	}
	BOOL get_DrawingLabelsVisible(long DrawHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, DrawHandle);
		return result;
	}
	void put_DrawingLabelsVisible(long DrawHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, DrawHandle, newValue);
	}
	void GetDrawingStandardViewWidth(long DrawHandle, double * Width)
	{
		static BYTE parms[] = VTS_I4 VTS_PR8 ;
		InvokeHelper(0x83, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DrawHandle, Width);
	}
	void SetDrawingStandardViewWidth(long DrawHandle, double Width)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DrawHandle, Width);
	}
	void DrawWidePolygon(VARIANT * xPoints, VARIANT * yPoints, long numPoints, unsigned long Color, BOOL fill, short Width)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_I4 VTS_UI4 VTS_BOOL VTS_I2 ;
		InvokeHelper(0x86, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xPoints, yPoints, numPoints, Color, fill, Width);
	}
	void DrawWideCircle(double x, double y, double pixelRadius, unsigned long Color, BOOL fill, short Width)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_UI4 VTS_BOOL VTS_I2 ;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, pixelRadius, Color, fill, Width);
	}
	LPDISPATCH SnapShot2(long ClippingLayerNbr, double Zoom, long pWidth)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_I4 ;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ClippingLayerNbr, Zoom, pWidth);
		return result;
	}
	void LayerFontEx(long LayerHandle, LPCTSTR FontName, long FontSize, BOOL isBold, BOOL isItalic, BOOL isUnderline)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x89, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, FontName, FontSize, isBold, isItalic, isUnderline);
	}
	void set_UDPointFontCharFont(long LayerHandle, LPCTSTR FontName, float FontSize, BOOL isBold, BOOL isItalic, BOOL isUnderline)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_R4 VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, FontName, FontSize, isBold, isItalic, isUnderline);
	}
	long set_UDPointFontCharListAdd(long LayerHandle, long newValue, unsigned long Color)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x8c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LayerHandle, newValue, Color);
		return result;
	}
	void set_UDPointFontCharFontSize(long LayerHandle, float FontSize)
	{
		static BYTE parms[] = VTS_I4 VTS_R4 ;
		InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, FontSize);
	}
	long get_ShapePointFontCharListID(long LayerHandle, long Shape)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapePointFontCharListID(long LayerHandle, long Shape, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x8e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	void ReSourceLayer(long LayerHandle, LPCTSTR newSrcPath)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x8f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, newSrcPath);
	}
	unsigned long get_ShapeLayerStippleColor(long LayerHandle)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerStippleColor(long LayerHandle, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x90, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	unsigned long get_ShapeStippleColor(long LayerHandle, long Shape)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x91, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeStippleColor(long LayerHandle, long Shape, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x91, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	BOOL get_ShapeStippleTransparent(long LayerHandle, long Shape)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle, Shape);
		return result;
	}
	void put_ShapeStippleTransparent(long LayerHandle, long Shape, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x92, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, Shape, newValue);
	}
	BOOL get_ShapeLayerStippleTransparent(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x93, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	void put_ShapeLayerStippleTransparent(long LayerHandle, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x93, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LayerHandle, newValue);
	}
	BOOL get_TrapRMouseDown()
	{
		BOOL result;
		InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_TrapRMouseDown(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x94, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_DisableWaitCursor(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x95, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisableWaitCursor()
	{
		BOOL result;
		InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL AdjustLayerExtents(long LayerHandle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x96, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, LayerHandle);
		return result;
	}
	LPDISPATCH SnapShot3(double left, double right, double top, double bottom, long Width)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 ;
		InvokeHelper(0x99, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, left, right, top, bottom, Width);
		return result;
	}
	void DrawPolygonEx(long LayerHandle, VARIANT * xPoints, VARIANT * yPoints, long numPoints, unsigned long Color, BOOL fill)
	{
		static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_I4 VTS_UI4 VTS_BOOL ;
		InvokeHelper(0x9b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerHandle, xPoints, yPoints, numPoints, Color, fill);
	}

	// Properties
	//

	unsigned long GetBackColor()
	{
		unsigned long result;
		GetProperty(0x1, VT_UI4, (void*)&result);
		return result;
	}
	void SetBackColor(unsigned long propVal)
	{
		SetProperty(0x1, VT_UI4, propVal);
	}
	double GetZoomPercent()
	{
		double result;
		GetProperty(0x2, VT_R8, (void*)&result);
		return result;
	}
	void SetZoomPercent(double propVal)
	{
		SetProperty(0x2, VT_R8, propVal);
	}
	long GetCursorMode()
	{
		long result;
		GetProperty(0x3, VT_I4, (void*)&result);
		return result;
	}
	void SetCursorMode(long propVal)
	{
		SetProperty(0x3, VT_I4, propVal);
	}
	long GetMapCursor()
	{
		long result;
		GetProperty(0x4, VT_I4, (void*)&result);
		return result;
	}
	void SetMapCursor(long propVal)
	{
		SetProperty(0x4, VT_I4, propVal);
	}
	long GetUDCursorHandle()
	{
		long result;
		GetProperty(0x5, VT_I4, (void*)&result);
		return result;
	}
	void SetUDCursorHandle(long propVal)
	{
		SetProperty(0x5, VT_I4, propVal);
	}
	BOOL GetSendMouseDown()
	{
		BOOL result;
		GetProperty(0x6, VT_BOOL, (void*)&result);
		return result;
	}
	void SetSendMouseDown(BOOL propVal)
	{
		SetProperty(0x6, VT_BOOL, propVal);
	}
	BOOL GetSendMouseUp()
	{
		BOOL result;
		GetProperty(0x7, VT_BOOL, (void*)&result);
		return result;
	}
	void SetSendMouseUp(BOOL propVal)
	{
		SetProperty(0x7, VT_BOOL, propVal);
	}
	BOOL GetSendMouseMove()
	{
		BOOL result;
		GetProperty(0x8, VT_BOOL, (void*)&result);
		return result;
	}
	void SetSendMouseMove(BOOL propVal)
	{
		SetProperty(0x8, VT_BOOL, propVal);
	}
	BOOL GetSendSelectBoxDrag()
	{
		BOOL result;
		GetProperty(0x9, VT_BOOL, (void*)&result);
		return result;
	}
	void SetSendSelectBoxDrag(BOOL propVal)
	{
		SetProperty(0x9, VT_BOOL, propVal);
	}
	BOOL GetSendSelectBoxFinal()
	{
		BOOL result;
		GetProperty(0xa, VT_BOOL, (void*)&result);
		return result;
	}
	void SetSendSelectBoxFinal(BOOL propVal)
	{
		SetProperty(0xa, VT_BOOL, propVal);
	}
	double GetExtentPad()
	{
		double result;
		GetProperty(0xb, VT_R8, (void*)&result);
		return result;
	}
	void SetExtentPad(double propVal)
	{
		SetProperty(0xb, VT_R8, propVal);
	}
	long GetExtentHistory()
	{
		long result;
		GetProperty(0xc, VT_I4, (void*)&result);
		return result;
	}
	void SetExtentHistory(long propVal)
	{
		SetProperty(0xc, VT_I4, propVal);
	}
	CString GetKey()
	{
		CString result;
		GetProperty(0xd, VT_BSTR, (void*)&result);
		return result;
	}
	void SetKey(CString propVal)
	{
		SetProperty(0xd, VT_BSTR, propVal);
	}
	BOOL GetDoubleBuffer()
	{
		BOOL result;
		GetProperty(0xe, VT_BOOL, (void*)&result);
		return result;
	}
	void SetDoubleBuffer(BOOL propVal)
	{
		SetProperty(0xe, VT_BOOL, propVal);
	}
	LPDISPATCH GetGlobalCallback()
	{
		LPDISPATCH result;
		GetProperty(0xf, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetGlobalCallback(LPDISPATCH propVal)
	{
		SetProperty(0xf, VT_DISPATCH, propVal);
	}
	long GetNumLayers()
	{
		long result;
		GetProperty(0x10, VT_I4, (void*)&result);
		return result;
	}
	void SetNumLayers(long propVal)
	{
		SetProperty(0x10, VT_I4, propVal);
	}
	LPDISPATCH GetExtents()
	{
		LPDISPATCH result;
		GetProperty(0x11, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetExtents(LPDISPATCH propVal)
	{
		SetProperty(0x11, VT_DISPATCH, propVal);
	}
	long GetLastErrorCode()
	{
		long result;
		GetProperty(0x12, VT_I4, (void*)&result);
		return result;
	}
	void SetLastErrorCode(long propVal)
	{
		SetProperty(0x12, VT_I4, propVal);
	}
	long GetIsLocked()
	{
		long result;
		GetProperty(0x13, VT_I4, (void*)&result);
		return result;
	}
	void SetIsLocked(long propVal)
	{
		SetProperty(0x13, VT_I4, propVal);
	}
	CString GetMapState()
	{
		CString result;
		GetProperty(0x14, VT_BSTR, (void*)&result);
		return result;
	}
	void SetMapState(CString propVal)
	{
		SetProperty(0x14, VT_BSTR, propVal);
	}
	CString GetSerialNumber()
	{
		CString result;
		GetProperty(0x5f, VT_BSTR, (void*)&result);
		return result;
	}
	void SetSerialNumber(CString propVal)
	{
		SetProperty(0x5f, VT_BSTR, propVal);
	}
	long GetLineSeparationFactor()
	{
		long result;
		GetProperty(0x60, VT_I4, (void*)&result);
		return result;
	}
	void SetLineSeparationFactor(long propVal)
	{
		SetProperty(0x60, VT_I4, propVal);
	}
	BOOL GetSendOnDrawBackBuffer()
	{
		BOOL result;
		GetProperty(0x76, VT_BOOL, (void*)&result);
		return result;
	}
	void SetSendOnDrawBackBuffer(BOOL propVal)
	{
		SetProperty(0x76, VT_BOOL, propVal);
	}
	BOOL GetMultilineLabels()
	{
		BOOL result;
		GetProperty(0x85, VT_BOOL, (void*)&result);
		return result;
	}
	void SetMultilineLabels(BOOL propVal)
	{
		SetProperty(0x85, VT_BOOL, propVal);
	}
	BOOL GetUseSeamlessPan()
	{
		BOOL result;
		GetProperty(0x97, VT_BOOL, (void*)&result);
		return result;
	}
	void SetUseSeamlessPan(BOOL propVal)
	{
		SetProperty(0x97, VT_BOOL, propVal);
	}
	double GetMouseWheelSpeed()
	{
		double result;
		GetProperty(0x98, VT_R8, (void*)&result);
		return result;
	}
	void SetMouseWheelSpeed(double propVal)
	{
		SetProperty(0x98, VT_R8, propVal);
	}
	long GetShapeDrawingMethod()
	{
		long result;
		GetProperty(0x9a, VT_I4, (void*)&result);
		return result;
	}
	void SetShapeDrawingMethod(long propVal)
	{
		SetProperty(0x9a, VT_I4, propVal);
	}


};
