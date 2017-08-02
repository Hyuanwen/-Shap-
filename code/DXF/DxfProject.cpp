#include "stdafx.h"
#include "DXF.H"
#include "DxfProject.h"

extern HWND  m_hwnd;
//long	     lcountprj = 0;
//const double conTrans = 0.00001;	
double conTrans = 0.00001;	


unsigned double gdPrjSumLineCount = 0;
unsigned double gdPrjStepLineCount = 0;
unsigned int  gPrjiStepProgressNum = 0;

void SendPrjProgressMessage()
{
	gdPrjStepLineCount ++;
	unsigned int iTmp = (unsigned int)(gdPrjStepLineCount * 100.0 / gdPrjSumLineCount);
	if (iTmp <= gPrjiStepProgressNum)
	{
		return;
	}

	gPrjiStepProgressNum = iTmp;
	::SendMessage(m_hwnd,0x0500,0,(double)gPrjiStepProgressNum);
}

void DXFProjectNextLine( std::ifstream &sin, std::ofstream &sout, string & strLine, bool bToPlane)
{
	//���ļ�ͷ��ʼ
	//���ļ���β����

    //lrrAdd,20170217��Ͷ�ͷ�Ͷ�Ա����Ĵ���
	if(bToPlane == true)
		conTrans = 100000;
	else 
		conTrans = 0.00001;

	_debug_getline = 0;

	
	::SendMessage(m_hwnd,0x0500,0,(double)0.0);
	string aLine;
	unsigned long nLineCount = 0;
	while (GETLINE(sin,aLine))
	{
		nLineCount ++;
	}

	gdPrjSumLineCount = (double)nLineCount;
	gdPrjStepLineCount = 0.0;
	gPrjiStepProgressNum = 0;

	sin.clear();
	sin.seekg(0,ios::beg);
	
	
	while( GETLINE(sin,strLine) )
	{
		sout<<strLine<<endl ;
		SendPrjProgressMessage();
		while( strLine.compare("  0") == 0 )
		{
			DXFProjectSECTION(sin, sout, strLine);
		}
	}
	::SendMessage(m_hwnd,0x0500,0,(double)100.0);

	/*
	DXF�ļ����ɶ����ɣ�ÿ�ζ�����һ��0�ͺ���ַ���SECTION�����뿪ʼ��0�ͺ���ַ���ENDSEC����
	*/
}


void DXFProjectNextSection( std::ifstream &sin, std::ofstream &sout, string &strLine )
{
	//��Section�ڵĵ�һ�����뿪ʼ
	//��ENDSEC����

	//1.��ȡ����������Ϊ��  2
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendPrjProgressMessage();

	if (strLine.compare("  2") == 0)
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendPrjProgressMessage();

		/*�����
		���ã�
		*/
		if (strLine.compare("HEADER") == 0)
		{
			while ( strLine.compare("ENDSEC") != 0 )
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendPrjProgressMessage();

				//���������Ҫ������
				//1.ͼ�η�Χ���½� $EXTMIN
				if (strLine.compare("$EXTMIN") == 0)
				{
					DXFProjectTransMin(sin, sout, strLine);
				}

				//2.ͼ�η�Χ���Ͻ� $EXTMAX
				if (strLine.compare("$EXTMAX") == 0)
				{
					DXFProjectTransMax(sin, sout, strLine);
				}
			
				//add by chenyong 2013-5-15
				//if (strLine.compare("$TEXTSIZE") == 0)
				//{
				//	DXFProjectTransTextSize(sin, sout, strLine);		//�޸�����Ĭ�ϸ߶�
				//}
			}
		}

		/*���
		����:	
		*/
		else if (strLine.compare("TABLES") == 0)
		{
			while ( strLine.compare("ENDSEC") != 0 )
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendPrjProgressMessage();

				//���������Ҫ������
				while(strLine.compare("  0") == 0)
				{
					DXFProjectTablesSec( sin , sout , strLine );
				}
			}
		}

		/*ʵ���
		����:	
		*/
		else if (strLine.compare("ENTITIES") == 0)
		{
			//lcountprj = 0;
			while ( strLine.compare("ENDSEC") != 0 )
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendPrjProgressMessage();

				//���������Ҫ������5
				while (strLine.compare("  0") == 0)
				{
					DXFProjectEntitiesSec( sin, sout, strLine);

					//lcountprj++;

					//if (lcountprj<9000)
					//{
					//	::SendMessage(m_hwnd,0x0500,0,(double)lcountprj*0.01);
					//}
				}
			}
		}

		/*OBJECTS��
		����:	
		*/
		else if (strLine.compare("OBJECTS") == 0)
		{
			while ( strLine.compare("ENDSEC") != 0 )
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendPrjProgressMessage();

				//���������Ҫ������
			}
		}

		/*���
		����:	
		*/
		else if (strLine.compare("CLASSES") == 0)
		{
			while ( strLine.compare("ENDSEC") != 0 )
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendPrjProgressMessage();

				//���������Ҫ������
			}
		}

		/*���
		����:	
		*/
		else if (strLine.compare("BLOCKS") == 0)
		{
			while ( strLine.compare("ENDSEC") != 0 )
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendPrjProgressMessage();

				//���������Ҫ������
			}
		}
	}
}

/*
���ã��Ż������ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbPolyline( std::ifstream & sin, std::ofstream & sout, string & strLine )
{
	//��AcDbPolyline�ڵĵ�һ�����뿪ʼ
	//��0����

	stringstream							strPoint;
	long									num_write(0);
	double									x(0);
	double									y(0);
	double									z(0);
	vector<double>							vec_x;
	vector<double>							vec_y;
	vector<double>							vec_z;
	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;
	int										iCount = 0;
	double									out_x(0);	
	double									out_y(0);
	double									out_z(0);
	string									tmpLine = "";

	vec_x.clear();
	vec_y.clear();
	vec_z.clear();

	double									dWidth = 0;
	char									*pVal = NULL;
	double									dHight = 0;

	double									dStart = 0;
	double									dEnd = 0;

	//��polyline
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0  )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );

		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
		}
		//add by chenyong 2013-5-17
		else if (strLine.compare(" 43") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dWidth = atof(strLine.c_str());
		}
		/*else if (strLine.compare(" 39") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			dHight = atof(strLine.c_str());
		}*/
		else if (strLine.compare(" 40") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dStart = atof(strLine.c_str());
		}
		else if (strLine.compare(" 41") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dEnd = atof(strLine.c_str());
		}
	}

	iCount = vec_x.size();
	if ( vec_z.size() == 0 )
	{
		vec_z.assign( iCount , 0 );
	}

	for ( int i = 0; i< iCount ; i++)
	{	
		p_transform( vec_y[i] , vec_x[i] , vec_z[i] , out_y , out_x , out_z );

		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		vec_z [i] = out_z ;
	}

	//дPolyline
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);
			ox = DoubleToString( vec_x[num_write-1] );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( vec_y[num_write-1] );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				oz = DoubleToString( vec_z[num_write-1] );	
				sout<<oz<<endl;
				delete oz;
			}	
		}
		//add by chenyong 2013-5-15
		else if (tmpLine.compare(" 43") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidth*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}	
		}
		/*else if (tmpLine.compare(" 39") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dHight*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}	
		}*/
		else if (tmpLine.compare(" 40") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dStart*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
		else if (tmpLine.compare(" 41") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dEnd*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
	}
}

/*
���ã������ͼԪ
ʱ��; 2012/12/13

*/
void DXFProjectNextAcDbPoint( std::ifstream &sin, std::ofstream &sout, string &strLine )
{
	//��AcDbPoint�ڵĵ�һ�����뿪ʼ
	//��0����

	stringstream							strPoint;
	double									x(0);
	double									y(0);
	double									z(0);
	double									dx(0);
	double									dy(0); 
	double									dz(0);
	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;
	string									tmpLine = "";

	//��point
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//�޸�
	p_transform(  y , x, z , dy, dx, dz );

	//дPoint	
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx );

			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( dy );

			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);	
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{				
				oz = DoubleToString( dz );
				sout<<oz<<endl;
				delete oz;
			}
		}
	}
}

//yzg 2012-9-6 ���Ӷ�AcDbLine��֧�� begin DXF������Ϣ���£�
/*
	100
	������ (AcDbLine) 
	39
	��ȣ���ѡ��Ĭ��ֵ = 0��
	10
	��㣨�� WCS �У�
	DXF��X ֵ��APP����ά��
	20, 30
	DXF������ Y ֵ�� Z ֵ���� WCS �У�
	11
	�˵㣨�� WCS �У�
	DXF��X ֵ��APP����ά��
	21, 31
	DXF���˵�� Y ֵ�� Z ֵ���� WCS �У�
	210
	���췽�򣨿�ѡ��Ĭ��ֵ = 0, 0, 1��
	DXF��X ֵ��APP����άʸ��
	220, 230
	DXF�����췽��� Y ֵ�� Z ֵ����ѡ��
*/
/* ����ʾ��
	100
	AcDbLine
	10
	617045.7286052827
	20
	2728478.603991013
	30
	0.0
	11
	617001.2604440658
	21
	2728469.144701108
	31
	0.0
	0
*/
void DXFProjectNextAcDbLine( std::ifstream &sin, std::ofstream &sout, string &strLine )
{
	//��AcDbLine�ڵĵ�һ�����뿪ʼ
	//��0����

	stringstream strPoint;

	//�߶ε���ʼ�� Դ
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	//�߶ε���ֹ�� Դ
	double x2 = 0;
	double y2 = 0;
	double z2 = 0;

	//�߶ε���ʼ�� Ŀ�� 
	double dx1 = 0;
	double dy1 = 0;
	double dz1 = 0;

	//�߶ε���ֹ�� Ŀ�� 
	double dx2 = 0;
	double dy2 = 0;
	double dz2 = 0;

	char *ox;
	char *oy;
	char *oz;

	//��point
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 11") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			z2 = atof( strLine.c_str() );
		}

	}

	//�޸�
	p_transform(  y1 , x1, z1 , dy1, dx1, dz1 );
	p_transform(  y2 , x2, z2 , dy2, dx2, dz2 );

	//дPoint
	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx1 );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( dy1 );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString( z1 );
			sout<<tmpLine<<endl;
		}
		else if ( tmpLine.compare(" 11") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx2 );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( dy2 );
			sout<<oy<<endl;
			delete oy;

		}
		else if ( tmpLine.compare(" 31") == 0 )
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString( dz2 );
			sout<<tmpLine<<endl;
		}
	}

	return;
}

/*
���ã���������ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbText(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//��AcDbText�ڵĵ�һ�����뿪ʼ
	//��0����

	stringstream strPoint;

	//�߶ε���ʼ�� Դ
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	//�߶ε���ֹ�� Դ
	double x2 = 0;
	double y2 = 0;
	double z2 = 0;

	//�߶ε���ʼ�� Ŀ�� 
	double dx1 = 0;
	double dy1 = 0;
	double dz1 = 0;

	//�߶ε���ֹ�� Ŀ�� 
	double dx2 = 0;
	double dy2 = 0;
	double dz2 = 0;

	char *ox;
	char *oy;
	char *oz;

	char*   pVal = NULL;
	double	dWidth = 0;
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 11") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z2 = atof( strLine.c_str() );
		}
		//add by chenyong 2013-5-17
		else if (strLine.compare(" 40") == 0 )
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dWidth = atof(strLine.c_str());
		}
	}

	//�޸�
	p_transform(  y1 , x1, z1 , dy1, dx1, dz1 );
	p_transform(  y2 , x2, z2 , dy2, dx2, dz2 );

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString(  dx1 );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy1 );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);
			sout<<tmpLine<<endl;
		}
		else if ( tmpLine.compare(" 11") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString(  dx2 );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy2 );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 31") == 0 )
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString( dz2 );
			sout<<tmpLine<<endl;
		}

		//add by chenyong 2013-5-15
		else if ( tmpLine.compare(" 40") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidth*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
		/*else if ( tmpLine.compare(" 41") == 0)
		{
			getline(strPoint, tmpLine);
			sout<<pVal<<endl;
		}*/
	}

	return;
}

/*
���ã���������ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbBlockReference(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//��AcDbBlockReference�ڵĵ�һ�����뿪ʼ
	//��0����

	stringstream strPoint;
	double x(0),y(0),z(0);

	char *ox;
	char *oy;
	char *oz;
	char * pVal = NULL;

	//add by chenyong 2013-5-22
	double	dWidthX = 0;
	double	dWidthY = 0;
	double	dWidthZ = 0;

	bool	bX = true;
	bool	bY = true;
	bool	bZ = true;

	//��point
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );

		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
		//add by chenyong 2013-5-17
		else if ( strLine.compare(" 41") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dWidthX = atof( strLine.c_str() );
			bX = false;
		}
		else if ( strLine.compare(" 42") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dWidthY = atof( strLine.c_str() );
			bY = false;
		}
		else if ( strLine.compare(" 43") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dWidthZ = atof( strLine.c_str() );
			bZ = false;
		}
	}

	//�޸�
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	//дPoint
	string tmpLine;
	double	tmpD = 0;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);		
			ox = DoubleToString(  dx );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString(  dz );
			sout<<tmpLine<<endl;

			//add by chenyong 2013-5-22
			if (bX)
			{
				sout<<" 41"<<endl;
				sout<<"0.00001"<<endl;
			}
			if (bY)
			{
				sout<<" 42"<<endl;
				sout<<"0.00001"<<endl;
			}
			if (bZ)
			{
				sout<<" 43"<<endl;
				sout<<"0.00001"<<endl;
			}
		}
		else if ( tmpLine.compare(" 41") == 0)
		{
			getline(strPoint,tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidthX*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
		else if (tmpLine.compare(" 42") == 0)
		{
			getline(strPoint,tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidthY*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
		else if (tmpLine.compare(" 43") == 0)
		{
			getline(strPoint,tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidthZ*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
	}

	return;
}

void DXFProjectTransMin(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);
	char *ox;
	char *oy;
	char *oz;

	//��point
	while( strLine.compare("  9") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//�޸�
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	//дPoint
	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;
		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;			
		}
	}

	return;
}

void DXFProjectTransMax(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);
	char *ox;
	char *oy;
	char *oz;

	//��point
	while( strLine.compare("  9") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//�޸�
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	//дPoint
	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString( dz );

			sout<<tmpLine<<endl;
		}
	}
	return;
}

/*
���ã�������ͼ���ĵ�����
ʱ�䣺2012/12/13

*/
void DXFProjectTransCentre(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);

	char *ox;
	char *oy;
	char *oz;

	char *  pVal = NULL;
	double	dWidth = 0;

	while( strLine.compare("146") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 12") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		} 
		else if ( strLine.compare(" 22") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		//add by chenyong 2013-5-17
		else if (strLine.compare(" 40") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dWidth = atof( strLine.c_str() );
		}
	}

	//�޸�
	double dx ,dy ,dz, tempdx, tempdy, tempdz ;
	p_transform(  y , x, z , dy, dx, dz );

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 12") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString(  dx );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 22") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  dy );
			sout<<oy<<endl;
			delete oy;
		}
		//add by chenyong 2013-5-15
		else if ( tmpLine.compare(" 40") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidth*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
	}

	return;
}

/*
���ã�����ԲͼԪ
ʱ�䣺2012/12/13
*/
void DXFProjectNextAcDbCircle(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	double x(0),y(0),z(0);

	char *ox;
	char *oy;
	char *oz;

	char		*pVal = NULL;
	double		dRadiu = 0;

	while( strLine.compare("  0") != 0 )
	{

		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
		//add by chenyong 2013-5-18 �������ƽ���µ�λת��
		else if ( strLine.compare(" 40") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dRadiu = atof( strLine.c_str() );
		}
	}

	//�޸�
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
		//add by chenyong 2013-5-18
		else if (tmpLine.compare(" 40") == 0)
		{
			getline(strPoint,tmpLine);

			pVal = DoubleToString( dRadiu*conTrans );
			sout<<pVal<<endl;
			delete pVal;
		}
	}

	return;
}

/*
���ã�������ԲͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbEllipse(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	//�߶ε���ʼ�� Դ
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	//�߶ε���ֹ�� Դ
	double x2 = 0;
	double y2 = 0;
	double z2 = 0;

	//�߶ε���ʼ�� Ŀ�� 
	double dx1 = 0;
	double dy1 = 0;
	double dz1 = 0;

	//�߶ε���ֹ�� Ŀ�� 
	double dx2 = 0;
	double dy2 = 0;
	double dz2 = 0;

	char *ox;
	char *oy;
	char *oz;

	//���ᣬ����
	char				*pVal = NULL;
	double				dMaxRadiu_X = 0;
	double				dMinRadiu_Y = 0;

	double				dRadiuX_Des = 0;
	double				dRadiuY_Des = 0;
	double				dRadiuZ_Des = 0;

	string				strF;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z1 = atof( strLine.c_str() );
		}
		//add by chenyong 2013-5-18
		else if ( strLine.compare(" 11") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dMaxRadiu_X = atof( strLine.c_str() );
		}
		else if (strLine.compare(" 21") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dMinRadiu_Y = atof( strLine.c_str() );
		}
	}

	//�޸�
	p_transform(  y1 , x1, z1 , dy1, dx1, dz1 );
	p_transform(y1 + dMinRadiu_Y, x1 + dMaxRadiu_X, 0, dRadiuY_Des, dRadiuX_Des, dRadiuZ_Des);//add by chenyong 

	string tmpLine;
	double tmpD = 0;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString(  dx1 );
			sout<<ox<<endl;

			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  dy1 );
			sout<<oy<<endl;

			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			sout<<tmpLine<<endl;
		}
		//add by chenyong 2013-5-18
		else if (tmpLine.compare(" 11") == 0)
		{
			getline(strPoint,tmpLine);

			pVal = DoubleToString(  dRadiuX_Des - dx1 );
			sout<<pVal<<endl;

			delete pVal;
		}
		else if (tmpLine.compare(" 21") == 0)
		{
			getline(strPoint,tmpLine);

			pVal = DoubleToString( dRadiuY_Des -dy1);
			sout<<pVal<<endl;

			delete pVal;
		}
	}

	return;
}

/*
���ã��������ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbMline(std::ifstream &sin, std::ofstream &sout, string& strLine)
{
	stringstream strPoint;
	long num_write(0);

	vector<double> vec_x;
	vector<double> vec_y;
	vector<double> vec_z;

	double x;
	double y;
	double z;
	double x1(0),y1(0),z1(0);

	char *ox;
	char *oy;
	char *oz;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 11") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );

			vec_x.push_back( x );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
		}
		else if (strLine.compare(" 10") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if (strLine.compare(" 20") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if (strLine.compare(" 30") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z1 = atof( strLine.c_str() );
		}
	}

	int iCount = vec_x.size();
	if ( vec_z.size() == 0 )
	{
		vec_z.assign( iCount , 0 );
	}

	for ( int i = 0; i< iCount ; i++)
	{
		double out_x(0),out_y(0),out_z(0);
		p_transform( vec_y[i] , vec_x[i] , vec_z[i] , out_y , out_x , out_z );

		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		vec_z [i] = out_z ;
	}

	//���
	double	out_x1(0),out_y1(0),out_z1(0);
	p_transform( y1 , x1 , z1 , out_y1 , out_x1 , out_z1 );

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 11") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);

			ox = DoubleToString(  vec_x[num_write-1] );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  vec_y[num_write-1] );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 31") == 0 )
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString(  vec_z[num_write-1] );						
			sout<<tmpLine<<endl;
		}
		else if (tmpLine.compare(" 10") == 0)
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( out_x1 );						

			sout<<ox<<endl;
			delete ox;
		}
		else if (tmpLine.compare(" 20") == 0)
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( out_y1 );						

			sout<<oy<<endl;
			delete oy;
		}
		else if (tmpLine.compare(" 30") == 0)
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString( out_z1 );						

			sout<<tmpLine<<endl;
		}
	}

	return;
}

/*
���ã�����ͼ������MPolygonͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbHatch(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	long num_write(0);

	vector<double> vec_x;
	vector<double> vec_y;
	vector<double> vec_z;

	//11,21
	vector<double> vec_x_o;
	vector<double> vec_y_o;
	long num_write_o(0);

	double x;
	double y;
	double z;

	char *ox;
	char *oy;
	char *oz;

	//add by chenyong 2013-5-17
	char			*pVal = NULL;
	double			dWidth = 0;

	//ͼ�������� X,Y����
	double			dHatchX = 0;
	double			dHatchY = 0;
	char			*pHatchX = NULL;
	char			*pHatchY = NULL;
	double			dHatchX_des = 0;
	double			dHatchY_des = 0;
	double			dHatchZ_des = 0;
	
	double			dHatchX_45 = 0;
	double			dHatchY_46 = 0;
	string			str46 = "";

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );

		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );

		}
		/*else if ( strLine.compare(" 30") == 0 )//˵����ZֵĬ��Ϊ0.0
		{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;

		z = atof( strLine.c_str() );
		vec_z.push_back( z );
		}*/
		else if ( strLine.compare(" 11") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
			vec_x_o.push_back( x );
		}
		else if (strLine.compare(" 21") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
			vec_y_o.push_back( y );

		}
		//add by chenyong 2013-5-17
		else if (strLine.compare(" 41") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dWidth = atof(strLine.c_str());
		}
		else if (strLine.compare(" 43") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dHatchX = atof(strLine.c_str());
		}
		else if (strLine.compare(" 44") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dHatchY = atof(strLine.c_str());
		}
		else if (strLine.compare(" 45") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dHatchX_45 = atof(strLine.c_str());
		}
		else if (strLine.compare(" 46") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dHatchY_46 = atof(strLine.c_str());
		}
	}

	int iCount = vec_x.size();

	/*if ( vec_z.size() == 0 )
	vec_z.assign( iCount , 0 );*/

	for ( int i = 0; i< iCount ; i++)
	{
		double out_x(0),out_y(0),out_z(0);

		p_transform( vec_y[i] , vec_x[i] , /*vec_z[i]*/0.0 , out_y , out_x , out_z );

		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		//vec_z [i] = out_z ;
	}

	//add by chenyong 2013-5-17
	//p_transform(dHatchY, dHatchX, 0.0, dHatchY_des, dHatchX_des, dHatchZ_des);

	//11,21�Ĵ���
	iCount = vec_x_o.size();

	for ( int i = 0; i< iCount ; i++)
	{
		double out_x(0),out_y(0),out_z(0);

		p_transform( vec_y_o[i] , vec_x_o[i] , /*vec_z[i]*/0.0 , out_y , out_x , out_z );

		vec_x_o [i] = out_x ;
		vec_y_o [i] = out_y ;
		//vec_z [i] = out_z ;
	}

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;
		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		
			getline(strPoint,tmpLine);
			
			//alter by chenyong 2013-5-17
			ox = DoubleToString(  vec_x[num_write-1] );
			sout<<ox<<endl;
			delete ox;
			/*if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				ox = DoubleToString(vec_x[num_write-1]);
				sout<<ox<<endl;
				delete ox;
			}*/
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  vec_y[num_write-1] );
			sout<<oy<<endl;	
			delete oy;

		/*	if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				oy = DoubleToString(vec_y[num_write-1]);
				sout<<oy<<endl;
				delete oy;
			}*/
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);
			sout<<tmpLine<<endl;		
		}
		else if (tmpLine.compare(" 11") == 0)
		{
			num_write_o++;		
			getline(strPoint,tmpLine);

			ox = DoubleToString(  vec_x_o[num_write_o-1] );
			sout<<ox<<endl;
			delete ox;

		/*	if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				ox = DoubleToString(vec_x[num_write-1]);
				sout<<ox<<endl;
				delete ox;
			}*/
		}
		else if (tmpLine.compare(" 21") == 0)
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  vec_y_o[num_write_o-1] );
			sout<<oy<<endl;
			delete oy;

	/*		if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				oy = DoubleToString(vec_x[num_write-1]);
				sout<<oy<<endl;
				delete oy;
			}*/
		}
		//add by chenyong 2013-5-17
		else if (tmpLine.compare(" 41") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidth*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
		else if (tmpLine.compare(" 43") == 0)
		{
			/*getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pHatchX = DoubleToString(dHatchX_des);
				sout<<pHatchX<<endl;
				delete pHatchX;
			}*/

			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dHatchX*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
		else if (tmpLine.compare(" 44") == 0)
		{
			/*getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pHatchY = DoubleToString(dHatchY_des);
				sout<<pHatchY<<endl;
				delete pHatchY;
			}*/

			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dHatchY*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
		else if (tmpLine.compare(" 45") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dHatchX_45*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
		else if (tmpLine.compare(" 46") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dHatchY_46*conTrans);
				sout<<pVal<<endl;
				delete pVal;
			}
		}
	}	

	return;
}

/*
���ã�����Բ��ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbArc(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);

	char *ox;
	char *oy;
	char *oz;

	char			*pVal = NULL;
	double			dRadiu = 0;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
		//�����ƽ������ϵͳ��֮�䵥λת�� add by chenyong 2013-5-18
		else if (strLine.compare(" 40") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dRadiu = atof( strLine.c_str() );
		}
	}

	//�޸�
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx );

			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);			
			oy = DoubleToString( dy );

			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;	
		}
		//add by chenyong 2013-5-18
		else if (tmpLine.compare(" 40") == 0)
		{
			getline(strPoint,tmpLine);			
			pVal = DoubleToString( dRadiu*conTrans );

			sout<<pVal<<endl;
			delete pVal;
		}
	}

	return;
}

/*
���ã������ά����ά���߶���ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDb2dOr3dPolylineVertex(std::ifstream &sin, std::ofstream &sout, string& strLine)
{
	stringstream							strPoint;

	double									x(0);
	double									y(0);
	double									z(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;

	double									dStart = 0;
	double									dEnd = 0;
	char									*pVal = NULL;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
		//add by chenyong 2013-5-21
		else if (strLine.compare(" 40") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dStart = atof(strLine.c_str());
		}
		else if (strLine.compare(" 41") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();
			dEnd = atof(strLine.c_str());
		}
	}

	//�޸�
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;	
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
		//��ʼ����ֹ��� add by chenyong 2013-5-21
		else if (tmpLine.compare(" 40") == 0 )
		{
			getline(strPoint,tmpLine);

			pVal = DoubleToString( dStart*conTrans );
			sout<<pVal<<endl;
			delete pVal;
		}
		else if (tmpLine.compare(" 41") == 0 )
		{
			getline(strPoint,tmpLine);

			pVal = DoubleToString( dEnd*conTrans );
			sout<<pVal<<endl;
			delete pVal;
		}
	}

	return;
}

/*
���ã�������������ͼԪ
ʱ�䣺2012/12/13
*/
void DXFProjectNextAcDbSpline(std::ifstream &sin, std::ofstream &sout, string& strLine)
{
	stringstream strPoint;

	long num_write(0);

	vector<double> vec_x;
	vector<double> vec_y;
	vector<double> vec_z;

	double x;
	double y;
	double z;

	char *ox;
	char *oy;
	char *oz;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0  )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
		}
		if( strLine.compare(" 11") == 0  )//������ϵ���Ϣadd201704
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
		}
	}

	int iCount = vec_x.size();

	if ( vec_z.size() == 0 )
		vec_z.assign( iCount , 0 );

	for ( int i = 0; i< iCount ; i++)
	{
		double out_x(0),out_y(0),out_z(0);
		p_transform( vec_y[i] , vec_x[i] , vec_z[i] , out_y , out_x , out_z );

		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		vec_z [i] = out_z ;
	}

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);

			ox = DoubleToString(  vec_x[num_write-1] );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  vec_y[num_write-1] );

			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString(  vec_z[num_write-1] );						
			sout<<tmpLine<<endl;			
		}
		if( tmpLine.compare(" 11") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);

			ox = DoubleToString(  vec_x[num_write-1] );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  vec_y[num_write-1] );

			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 31") == 0 )
		{
			getline(strPoint,tmpLine);					
			sout<<tmpLine<<endl;			
		}
	}

	return;
}

/*
���ã�������ά��ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbFace(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	/*��һ�ǵ�*/
	double									x0(0);
	double									y0(0);
	double									z0(0);

	double									dx0(0);
	double									dy0(0);
	double									dz0(0);

	/*�ڶ��ǵ�*/
	double									x1(0);
	double									y1(0);
	double									z1(0);

	double									dx1(0);
	double									dy1(0);
	double									dz1(0);

	/*�����ǵ�*/
	double									x2(0);
	double									y2(0);
	double									z2(0);

	double									dx2(0);
	double									dy2(0);
	double									dz2(0);

	/*���Ľǵ�*/
	double									x3(0);
	double									y3(0);
	double									z3(0);

	double									dx3(0);
	double									dy3(0);
	double									dz3(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;
	string									tmpLine = "";

	while( strLine.compare("  0") != 0 )
	{
		/*��һ�ǵ�*/
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x0 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y0 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z0 = atof( strLine.c_str() );
		}
		/*�ڶ��ǵ�*/
		else if ( strLine.compare(" 11") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 21") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 31") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z1 = atof( strLine.c_str() );
		}
		/*�����ǵ�*/
		else if ( strLine.compare(" 12") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 22") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 32") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z2 = atof( strLine.c_str() );
		}
		/*���Ľǵ�*/
		else if ( strLine.compare(" 13") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x3 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 23") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y3 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 33") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z3 = atof( strLine.c_str() );
		}
	}

	//����ת��
	p_transform(y0, x0, z0, dy0, dx0, dz0);
	p_transform(y1, x1, z1, dy1, dx1, dz1);
	p_transform(y2, x2, z2, dy2, dx2, dz2);
	p_transform(y3, x3, z3, dy3, dx3, dz3);

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		/*��һ�ǵ�*/
		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx0 );
			sout<<ox<<endl;	
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy0 );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz0 );
			sout<<tmpLine<<endl;
		}
		/*�ڶ��ǵ�*/
		else if ( tmpLine.compare(" 11") == 0)
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx1 );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 21") == 0)
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy1 );
			sout<<oy<<endl;	
			delete oy;
		}
		else if (tmpLine.compare(" 31") == 0)
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz1 );
			sout<<tmpLine<<endl;	
		}
		/*�����ǵ�*/
		else if (tmpLine.compare(" 12") == 0)
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx2 );
			sout<<ox<<endl;
			delete ox;
		}
		else if (tmpLine.compare(" 22") == 0)
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy2 );
			sout<<oy<<endl;
			delete oy;
		}
		else if (tmpLine.compare(" 32") == 0)
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz2 );
			sout<<tmpLine<<endl;	
		}
		/*���Ľǵ�*/
		else if (tmpLine.compare(" 13") == 0)
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx3 );
			sout<<ox<<endl;	
			delete ox;
		}
		else if (tmpLine.compare(" 23") == 0)
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy3 );
			sout<<oy<<endl;
			delete oy;
		}
		else if (tmpLine.compare(" 33") == 0)
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz3 );
			sout<<tmpLine<<endl;	
		}
	}

	return;
}

/*
	���ã������������ͼԪ
	ʱ�䣺2012/12/13
	�޸�ʱ�䣺2013-11-11
*/
void DXFProjectNextAcDbMText(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	double									x(0);
	double									y(0);
	double									z(0);
	double									dx(0);
	double									dy(0);
	double									dz(0);

	double									dTextHeight(0);
	double									dRecWidth(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;
	char*									pVal = NULL;

	string									tmpLine = "";

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 40") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dTextHeight = atof(strLine.c_str());
		}
		else if (strLine.compare(" 41") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dRecWidth = atof(strLine.c_str());
		}

	}

	//����ת��
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
		else if (tmpLine.compare(" 40") == 0)
		{
			getline(strPoint, tmpLine);
			pVal = DoubleToString(dTextHeight*conTrans);
			sout<<pVal<<endl;

			delete pVal;
		}
		else if (tmpLine.compare(" 41") == 0)
		{
			getline(strPoint, tmpLine);
			pVal = DoubleToString(dRecWidth*conTrans);

			sout<<pVal<<endl;

			delete pVal;
		}
	}

	return;
}

/*
���ã�������ͼԪ
ʱ�䣺2012/12/13
*/
void DXFProjectNextAcDbShape(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	double									x(0);
	double									y(0);
	double									z(0);
	double									dx(0);
	double									dy(0);
	double									dz(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;

	string									tmpLine = "";

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//����ת��
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
	}

	return;
}

/*
���ã���������ͼԪ
ʱ�䣺2012/12/13
*/
void DXFProjectNextAcDbRay(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	double									x(0);
	double									y(0);
	double									z(0);
	double									dx(0);
	double									dy(0);
	double									dz(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;

	string									tmpLine = "";

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//����ת��
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
	}

	return;
}

/*
���ã������ά����ά�Ķ����ͼԪ
ʱ�䣺2012/12/13
*/
void DXFProjectNextAcDb2dOr3dPolyline(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream							strPoint;
	long									num_write(0);
	double									x(0);
	double									y(0);
	double									z(0);
	vector<double>							vec_x;
	vector<double>							vec_y;
	vector<double>							vec_z;
	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;
	int										iCount = 0;
	double									out_x(0);	
	double									out_y(0);
	double									out_z(0);
	string									tmpLine = "";

	vec_x.clear();
	vec_y.clear();
	vec_z.clear();

	//add by chenyong 2013-5-15
	char *pVal = NULL;
	double	dWidthX = 0;
	double	dWidthY = 0;

	//��polyline
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0  )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
		}
		else if ( strLine.compare(" 40") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dWidthX = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 41") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			dWidthY = atof( strLine.c_str() );
		}
	}

	iCount = vec_x.size();
	if ( vec_z.size() == 0 )
	{
		vec_z.assign( iCount , 0 );
	}

	for ( int i = 0; i< iCount ; i++)
	{	
		p_transform( vec_y[i] , vec_x[i] , vec_z[i] , out_y , out_x , out_z );

		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		vec_z [i] = out_z ;
	}

	//дPolyline
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);
			ox = DoubleToString(  vec_x[num_write-1] );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  vec_y[num_write-1] );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				oz = DoubleToString(  vec_z[num_write-1] );	
				sout<<oz<<endl;
				delete oz;
			}	
		}
		//add by chenyong 2013-5-15
		else if (tmpLine.compare(" 40") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidthX*conTrans);
				sout<<pVal<<endl;
			}
		}
		else if (tmpLine.compare(" 41") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pVal = DoubleToString(dWidthY*conTrans);
				sout<<pVal<<endl;
			}
		}
	}
}

/*
���ã������ӿ�ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbViewport(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	//WCS
	double									x(0);
	double									y(0);
	double									z(0);
	double									dx(0);
	double									dy(0);
	double									dz(0);

	//DCS
	double									x1(0);
	double									y1(0);
	double									z1(0);
	double									dx1(0);
	double									dy1(0);
	double									dz1(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;

	string									tmpLine = "";

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		/*WCS*/
		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}

		/*DCS*/
		else if (strLine.compare(" 12") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x1 = atof(strLine.c_str());
		}
		else if (strLine.compare(" 22") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y1 = atof(strLine.c_str());
		}
	}

	//����ת��
	p_transform(  y , x, z , dy, dx, dz );
	p_transform(y1, x1, z1, dy1, dx1, dz1);

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;	
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
		else if ( tmpLine.compare(" 12") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx1 );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 22") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy1 );
			sout<<oy<<endl;
			delete oy;
		}
	}

	return;
}

/*
���ã�������ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbXline(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	double									x(0);
	double									y(0);
	double									z(0);
	double									dx(0);
	double									dy(0);
	double									dz(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;

	string									tmpLine = "";

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//����ת��
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;	
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
	}

	return;
}

/*
���ã�������ͼԪ
ʱ�䣺2012/12/13
*/
void DXFProjectNextAcDbFcf(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	double									x(0);
	double									y(0);
	double									z(0);
	double									dx(0);
	double									dy(0);
	double									dz(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;

	string									tmpLine = "";

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//����ת��
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
	}

	return;
}

/*
����: ͼ��ͼԪ
ʱ�䣺2012/12/13
*/
void DXFProjectNextAcDbRasterImage(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream							strPoint;

	double									x(0);
	double									y(0);
	double									z(0);
	double									dx(0);
	double									dy(0);
	double									dz(0);

	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;

	string									tmpLine = "";

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//����ת��
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz );
			sout<<tmpLine<<endl;
		}
	}

	return;
}

/*
���ã���������ͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbLeader(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream							strPoint;
	long									num_write(0);
	double									x(0);
	double									y(0);
	double									z(0);
	vector<double>							vec_x;
	vector<double>							vec_y;
	vector<double>							vec_z;
	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;
	int										iCount = 0;
	double									out_x(0);	
	double									out_y(0);
	double									out_z(0);
	string									tmpLine = "";

	vec_x.clear();
	vec_y.clear();
	vec_z.clear();

	//��polyline
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
		}
	}

	iCount = vec_x.size();
	if ( vec_z.size() == 0 )
	{
		vec_z.assign( iCount , 0 );
	}

	for ( int i = 0; i < iCount; i++)
	{	
		p_transform( vec_y[i] , vec_x[i] , vec_z[i] , out_y , out_x , out_z );

		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		vec_z [i] = out_z ;
	}

	//дPolyline
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);
			ox = DoubleToString( vec_x[num_write-1] );
			sout<<ox<<endl;
			delete ox;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( vec_y[num_write-1] );
			sout<<oy<<endl;
			delete oy;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				oz = DoubleToString( vec_z[num_write-1] );	
				sout<<oz<<endl;
				delete oz;
			}	
		}
	}
}

/*
���ã�����Ole2FrameͼԪ
ʱ�䣺2012/12/13

*/
void DXFProjectNextAcDbOle2Frame(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	//�߶ε���ʼ�� Դ
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	//�߶ε���ֹ�� Դ
	double x2 = 0;
	double y2 = 0;
	double z2 = 0;

	//�߶ε���ʼ�� Ŀ�� 
	double dx1 = 0;
	double dy1 = 0;
	double dz1 = 0;

	//�߶ε���ֹ�� Ŀ�� 
	double dx2 = 0;
	double dy2 = 0;
	double dz2 = 0;

	char *ox = NULL;
	char *oy = NULL;
	char *oz = NULL;


	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendPrjProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 11") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			x2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			y2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendPrjProgressMessage();

			z2 = atof( strLine.c_str() );
		}
	}

	//�޸�
	p_transform(  y1 , x1, z1 , dy1, dx1, dz1 );
	p_transform(  y2 , x2, z2 , dy2, dx2, dz2 );

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString(  dx1 );
			sout<<ox<<endl;
			delete ox;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy1 );
			sout<<oy<<endl;
			delete oy;

		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);
			sout<<tmpLine<<endl;
		}
		else if ( tmpLine.compare(" 11") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString(  dx2 );
			sout<<ox<<endl;
			delete ox;

		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy2 );
			sout<<oy<<endl;
			delete oy;

		}
		else if ( tmpLine.compare(" 31") == 0 )
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString( dz2 );
			sout<<tmpLine<<endl;
		}
	}

	return;
}

void DXFProjectVPORT(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendPrjProgressMessage();

		//��ͼ����
		if ( strLine.compare("*Active") == 0)
		{
			DXFProjectTransCentre(sin, sout, strLine);
		}
	}
}

void DXFProjectSECTION(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//���Object�����
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendPrjProgressMessage();

	if( strLine.compare("SECTION") == 0  )
	{				
		DXFProjectNextSection( sin , sout , strLine );
	}
}

void DXFProjectTablesSec(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendPrjProgressMessage();

	if (strLine.compare("ENDSEC") == 0)
	{
		return;
	}

	while (strLine.compare("ENDTAB") != 0)
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendPrjProgressMessage();

		while (strLine.compare("  0") == 0)  //�������
		{
			DXFProjectTableObjects(sin, sout, strLine);
		}
	}
}

void DXFProjectTableObjects(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	/*
	TABLE�Σ�1.VPORT(�ӿ����ñ�,���ܰ������ͬ������Ŀ����ʾ���ӿ����ã���
	���ӿ��������Ӧ��Ŀ���ƾ�Ϊ*ACTIVE)
	2.APPID(Ӧ�ó����ʶ��)
	3.BLOCK_RECORD(����ձ�)
	4.DIMSTYLE(��ע��ʽ��)
	5.LAYER(ͼ���)
	6.LTYPE(���ͱ�)
	7.STYLE(������ʽ��)
	8.UCS(�û�����ϵ��)
	9.VIEW(��ͼ��)
	*/
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendPrjProgressMessage();

	if (strLine.compare("VPORT") == 0)
	{
		DXFProjectVPORT( sin, sout, strLine);
	}
	/*else if (strLine.compare("LTYPE") == 0)
	{

	}
	else if (strLine.compare("LAYER") == 0)
	{

	}
	else if (strLine.compare("STYLE") == 0)
	{

	}
	else if (strLine.compare("VIEW") == 0)
	{

	}
	else if (strLine.compare("APPID") == 0)
	{

	}
	else if (strLine.compare("BLOCK_RECORD") == 0)
	{

	}
	else if (strLine.compare("DIMSTYLE") == 0)
	{

	}
	else if (strLine.compare("UCS") == 0)
	{

	}*/
}

void DXFProjectEntitiesSec(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	/*
	ENTITIES: 1.HATCH
	2.3DFACE(��ά��ͼԪ)
	3.ARC(Բ��ͼԪ)
	4.ATTDEF(���Զ���ͼԪ)
	5.ATTRIB(����ͼԪ)
	6.CIRCLE(ԲͼԪ)
	7.ELLIPSE(��ԲͼԪ)
	8.IMAGE(ͼ��ͼԪ)
	9.INSERT(�����ͼԪ)
	10.LEADER(����ͼԪ)
	11.LINE(ֱ��ͼԪ)
	12.LWPOLYLINE(�����ͼԪ)
	13.MLINE(����ͼԪ)
	14.MTEXT(��������ͼԪ)
	15.OLE2FRAME(ole2frameͼԪ)
	16.POINT(��ͼԪ)
	17.POLYLINE(�����ͼԪ)
	18.RAY(����ͼԪ)
	19.SHAPE(��ͼԪ)
	20.SOLID(ʵ��ͼԪ)
	21.SPLINE(��������ͼԪ)
	22.TEXT(����ͼԪ)
	23.TOLERANCE(����ͼԪ)
	24.TRACE(����ͼԪ)
	25.VERTEX(����ͼԪ)
	25.VIEWPORT(�ӿ�ͼԪ)
	26.WIPEOUT(����ͼԪ)
	27.XLINE(������ͼԪ)
	*/
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendPrjProgressMessage();

	if (strLine.compare("HATCH") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("3DFACE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("ARC") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("ATTDEF") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("ATTRIB") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("CIRCLE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("ELLIPSE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("IMAGE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("INSERT") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("LEADER") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("LINE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("LWPOLYLINE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("MLINE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("MTEXT") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("OLE2FRAME") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("POINT") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("POLYLINE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("RAY") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("SHAPE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbTrace") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("SPLINE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("TEXT") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("TOLERANCE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("TRACE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("VERTEX") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("VIEWPORT") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("WIPEOUT") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("XLINE") == 0)
	{
		DXFProjectEntiCom(sin, sout, strLine);
	}
}

void DXFProjectEntiCom(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendPrjProgressMessage();

		while( strLine.compare("100") == 0 )
		{
			DXFProjectNextEntiSubClass( sin , sout , strLine );
		}
	}
}

void DXFProjectNextEntiSubClass(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//�����������
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendPrjProgressMessage();

	if( strLine.compare("AcDbEntity") == 0  )
	{				
		DXFProjectNextEntiAcDbEntity( sin , sout , strLine );
	}
}

void DXFProjectNextEntiAcDbEntity(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//add by chenyong 2013-5-20
	string						strtmp = "";
	double						dVal = 0;
	char						*pVal = NULL;
	bool						bAdd = false;
	bool						bExsit = false;
	//bool						bClassName = true;				//���룺8		ͼ����
	//bool						bLineName = false;				//���룺6		������
	//bool						bColorNo = false;				//���룺62		��ɫ��
	std::stringstream			tmpsin;
	std::string					tmpstr = strLine;
	
	while (strLine.compare("100") != 0)
	{
		GETLINE(sin, strLine);
		tmpsin<<strLine<<endl;
		SendPrjProgressMessage();

		if (strLine.compare(" 48") == 0)
		{
			bExsit = true;
		}
		/*else (strLine.compare(" 6") == 0)
		{
			bLineName = true;
		}
		else (strLine.compare(" 62") == 0)
		{
			bColorNo = true;
		}*/
	}

	GETLINE(sin, strLine);
	tmpsin<<strLine<<endl;
	SendPrjProgressMessage();

	if (strLine.compare("AcDbPolyline") == 0 || strLine.compare("AcDbVertex") == 0)
	{
		bAdd = true;
	}
	//end add 

	/*while( strLine.compare("100") != 0 )
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
	}

	GETLINE(sin,strLine);
	sout<<strLine<<endl ;*/

	if (bAdd)
	{
		if (bExsit)
		{
			while( tmpstr.compare("100") != 0 )
			{
				GETLINE(tmpsin,tmpstr);
				sout<<tmpstr<<endl ;

				if (tmpstr.compare(" 48") == 0)
				{
					GETLINE(tmpsin, tmpstr);
					dVal = atof(tmpstr.c_str());
					pVal = DoubleToString(dVal*conTrans);
					sout<<pVal<<endl;
					delete pVal;
				}
			}
		}
		else
		{
			while( tmpstr.compare("100") != 0 )
			{
				GETLINE(tmpsin, tmpstr);
				sout<<tmpstr<<endl ;

				if (tmpstr.compare("  8") == 0)
				{
					GETLINE(tmpsin, tmpstr);
					sout<<tmpstr<<endl;

					//���Ĭ�����ͱ���*0.00001
					sout<<" 48"<<endl;
					sout<<"0.00001"<<endl;
				}
			}

			//if (bColorNo)
			//{
			//	while( tmpstr.compare("100") != 0 )
			//	{
			//		GETLINE(tmpsin, tmpstr);
			//		sout<<tmpstr<<endl ;

			//		if (tmpstr.compare(" 62") == 0)
			//		{
			//			GETLINE(tmpsin, tmpstr);
			//			sout<<tmpstr<<endl;

			//			//���Ĭ�����ͱ���*0.00001
			//			sout<<" 48"<<endl;
			//			sout<<"0.00001"<<endl;
			//		}
			//	}
			//}
			//else
			//{
			//	if (bLineName)
			//	{
			//		while( tmpstr.compare("100") != 0 )
			//		{
			//			GETLINE(tmpsin, tmpstr);
			//			sout<<tmpstr<<endl ;

			//			if (tmpstr.compare("  6") == 0)
			//			{
			//				GETLINE(tmpsin, tmpstr);
			//				sout<<tmpstr<<endl;

			//				//���Ĭ�����ͱ���*0.00001
			//				sout<<" 48"<<endl;
			//				sout<<"0.00001"<<endl;
			//			}
			//		}
			//	}
			//	else
			//	{
			//		while( tmpstr.compare("100") != 0 )
			//		{
			//			GETLINE(tmpsin, tmpstr);
			//			sout<<tmpstr<<endl ;

			//			if (tmpstr.compare("  8") == 0)
			//			{
			//				GETLINE(tmpsin, tmpstr);
			//				sout<<tmpstr<<endl;

			//				//���Ĭ�����ͱ���*0.00001
			//				sout<<" 48"<<endl;
			//				sout<<"0.00001"<<endl;
			//			}
			//		}
			//	}
			//}
		}
	}
	else
	{
		while( tmpstr.compare("100") != 0 )
		{
			GETLINE(tmpsin,tmpstr);
			sout<<tmpstr<<endl ;
		}
	}
	//end add 

	//ENTITIES����
	GETLINE(tmpsin, tmpstr);
	sout<<tmpstr<<endl ;

	if(strLine.compare("AcDbHatch") == 0)
	{
		DXFProjectNextAcDbHatch(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbFace") == 0)
	{
		DXFProjectNextAcDbFace(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbText") == 0)
	{
		DXFProjectNextAcDbText(sin, sout, strLine);
	}
	/*else if (strLine.compare("AcDbAttributeDefinition") == 0)
	{

	}*/
	else if (strLine.compare("AcDbCircle") == 0)
	{
		DXFProjectNextAcDbCircle(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbEllipse") == 0)
	{
		DXFProjectNextAcDbEllipse(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbRasterImage") == 0)
	{
		DXFProjectNextAcDbRasterImage(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbBlockReference") == 0)
	{
		DXFProjectNextAcDbBlockReference(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbLeader") == 0)
	{
		DXFProjectNextAcDbLeader(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbLine") == 0)
	{
		DXFProjectNextAcDbLine(sin , sout , strLine);
	}
	else if (strLine.compare("AcDbPolyline") == 0)
	{
		DXFProjectNextAcDbPolyline( sin , sout , strLine );
	}
	else if (strLine.compare("AcDbMline") == 0)
	{
		DXFProjectNextAcDbMline(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbMText") == 0)
	{
		DXFProjectNextAcDbMText(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbOle2Frame") == 0)
	{
		DXFProjectNextAcDbOle2Frame(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbPoint") == 0)
	{
		DXFProjectNextAcDbPoint( sin , sout , strLine );
	}
	else if (strLine.compare("AcDb2dPolyline") == 0)
	{
		DXFProjectNextAcDb2dOr3dPolyline( sin, sout, strLine);
	}
	else if (strLine.compare("AcDb3dPolyline") == 0)
	{
		DXFProjectNextAcDb2dOr3dPolyline( sin, sout, strLine);
	}
	else if (strLine.compare("AcDbRay") == 0)
	{
		DXFProjectNextAcDbRay(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbShape") == 0)
	{
		DXFProjectNextAcDbShape(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbSpline") == 0)
	{
		DXFProjectNextAcDbSpline(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbFcf") == 0)
	{
		DXFProjectNextAcDbFcf(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbTrace") == 0)
	{
		//AcDbTrace������AcDbFaceһ��
		DXFProjectNextAcDbFace(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbVertex") == 0)
	{
		DXFProjectNextEntiAcDbEntity( sin , sout , strLine );
	}
	else if (strLine.compare("AcDb2dVertex") == 0)
	{
		DXFProjectNextAcDb2dOr3dPolylineVertex(sin, sout, strLine);
	}
	else if (strLine.compare("AcDb3dPolylineVertex") == 0)
	{
		DXFProjectNextAcDb2dOr3dPolylineVertex(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbViewport") == 0)
	{
		DXFProjectNextAcDbViewport(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbXline") == 0)
	{
		DXFProjectNextAcDbXline(sin, sout, strLine);
	}
}

//void DXFProjectTransTextSize(std::ifstream &sin, std::ofstream &sout, string &strLine)
//{
//	stringstream strPoint;
//	const char *pVal = "0.00001";
//
//	//��point
//	while( strLine.compare("  9") != 0 )
//	{
//		GETLINE(sin,strLine);
//		strPoint<<strLine<<endl;
//	}
//
//	//дPoint
//	string tmpLine;
//	while( getline(strPoint,tmpLine) )
//	{
//		sout<<tmpLine<<endl;
//
//		if( tmpLine.compare(" 40") == 0 )
//		{
//			getline(strPoint,tmpLine);
//			
//			sout<<pVal<<endl;
//		}
//	}
//	return;
//}
