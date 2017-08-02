typedef struct deuRasterShapeFormat
{
public:
	 double dbLeft;//源栅格左上角点经度值
	 double dbTop; //源栅格左上角点纬度值
	 long lLenght; //源栅格长度
	 long lWidth;  //源栅格宽度
	 double dbPixX;//源栅格X分辨率
	 double dbPixY;//源栅格Y分辨率
}deuRasterShapeFormat;

enum ExcelFormatType
{
	NUM,
	LETTER
};

typedef struct deuColumnFormatNum
{
public:
	int  oriX;//源x所在行
	int  oriY;//源y所在行
	int  oriZ;//源z所在行
	int  desX;//目标x所在行
	int  desY;//目标y所在行
	int  desZ;//目标z所在行
}deuColumnFormatNum;

typedef struct deuColumnFormatLetter
{ 	
public:
	char *  oriX;//源x所在行
	char *  oriY;//源y所在行
	char *  oriZ;//源z所在行
	char *	desX;//目标x所在行
	char *	desY;//目标y所在行
	char *	desZ;//目标z所在行
}deuColumnFormatLetter;

typedef struct deuColumnHeader
{
public:
	bool haveColumnHeader ;//是否包含列头
	int  ColumnHeaderRow  ;//列头所在行	
}deuColumnHeader;


typedef struct deuExcelFormat
{ 	
public:
	ExcelFormatType	sType;//格式类型 0 = FormatNum 1 = FormatLetter
	deuColumnHeader	_ColumnHeader;
	void *	pColFormat;

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