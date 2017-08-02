typedef struct deuRasterShapeFormat
{
public:
	 double dbLeft;//Դդ�����Ͻǵ㾭��ֵ
	 double dbTop; //Դդ�����Ͻǵ�γ��ֵ
	 long lLenght; //Դդ�񳤶�
	 long lWidth;  //Դդ����
	 double dbPixX;//Դդ��X�ֱ���
	 double dbPixY;//Դդ��Y�ֱ���
}deuRasterShapeFormat;

enum ExcelFormatType
{
	NUM,
	LETTER
};

typedef struct deuColumnFormatNum
{
public:
	int  oriX;//Դx������
	int  oriY;//Դy������
	int  oriZ;//Դz������
	int  desX;//Ŀ��x������
	int  desY;//Ŀ��y������
	int  desZ;//Ŀ��z������
}deuColumnFormatNum;

typedef struct deuColumnFormatLetter
{ 	
public:
	char *  oriX;//Դx������
	char *  oriY;//Դy������
	char *  oriZ;//Դz������
	char *	desX;//Ŀ��x������
	char *	desY;//Ŀ��y������
	char *	desZ;//Ŀ��z������
}deuColumnFormatLetter;

typedef struct deuColumnHeader
{
public:
	bool haveColumnHeader ;//�Ƿ������ͷ
	int  ColumnHeaderRow  ;//��ͷ������	
}deuColumnHeader;


typedef struct deuExcelFormat
{ 	
public:
	ExcelFormatType	sType;//��ʽ���� 0 = FormatNum 1 = FormatLetter
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