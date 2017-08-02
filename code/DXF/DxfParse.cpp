#include "stdafx.h"
#include "DXF.h"
#include "DxfParse.h"
//#include "DeuOCSTransformer.h"

extern char* g_SRSWkt;
BOOL         HasWriteSRS = FALSE ;
extern HWND  m_hwnd;
long	     lcout = 0;

unsigned double gdSumLineCount = 0;
unsigned double gdStepLineCount = 0;
unsigned int  giStepProgressNum = 0;

void SendProgressMessage()
{
	gdStepLineCount ++;
	unsigned int iTmp = (unsigned int)(gdStepLineCount * 100.0 / gdSumLineCount);
	if (iTmp <= giStepProgressNum)
	{
		return;
	}

	giStepProgressNum = iTmp;
	::SendMessage(m_hwnd,0x0500,0,(double)giStepProgressNum);
}

void DXFParseNextLine(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//从文件头开始
	//到文件结尾结束
	_debug_getline = 0;
	HasWriteSRS = FALSE; 
	::SendMessage(m_hwnd,0x0500,0,(double)0.0);
	string aLine;
	unsigned long nLineCount = 0;
	while (GETLINE(sin,aLine))
	{
		nLineCount ++;
	}

	gdSumLineCount = (double)nLineCount;
	gdStepLineCount = 0.0;
	giStepProgressNum = 0;

	sin.clear();
	sin.seekg(0,ios::beg);


	while (GETLINE(sin,strLine))
	{
		sout<<strLine<<endl ;

		SendProgressMessage();
		while (strLine.compare("  0") == 0)
		{
			DXFParseSECTION(sin, sout, strLine);
		}
	}
	::SendMessage(m_hwnd,0x0500,0,(double)100.0);

	/*
	DXF文件是由多段组成，每段都是以一个0和后跟字符串SECTION的组码开始，0和后跟字符串ENDSEC结束
	*/
}

void DXFParseSECTION(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//获得Object的类别
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendProgressMessage();

	if (strLine.compare("SECTION") == 0)
	{				
		DXFParseNextSection(sin, sout, strLine);
	}
}

void DXFParseNextSection(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//从Section内的第一个组码开始
	//到ENDSEC结束

	//1.获取段名，组码为：  2
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendProgressMessage();

	if (strLine.compare("  2") == 0)
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendProgressMessage();

		if (strLine.compare("HEADER") == 0)
		{
			/*标题段
				作用：
			*/
			while (strLine.compare("ENDSEC") != 0)
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendProgressMessage();

				//如下添加需要处理部分
				//1.图形范围左下角 $EXTMIN
				if (strLine.compare("$EXTMIN") == 0)
				{
					DXFParseTransMin(sin, sout, strLine);
				}

				//2.图形范围右上角 $EXTMAX
				if (strLine.compare("$EXTMAX") == 0)
				{
					DXFParseTransMax(sin, sout, strLine);
				}
			}
		}
		else if (strLine.compare("TABLES") == 0)
		{
			/*表段
				作用:	
			*/
			while (strLine.compare("ENDSEC") != 0)
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendProgressMessage();

				//如下添加需要处理部分
				while(strLine.compare("  0") == 0)
				{
					DXFParseTablesSec(sin, sout , strLine);
				}
			}
		}
		else if (strLine.compare("ENTITIES") == 0)
		{
			/*实体段
				作用:	
			*/
			lcout = 0;
			while (strLine.compare("ENDSEC") != 0)
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendProgressMessage();

				//如下添加需要处理部分5
				while (strLine.compare("  0") == 0)
				{
					DXFParseEntitiesSec(sin, sout, strLine);

					//lcout++;
					//if (lcout<9000)
					//{
					//	::SendMessage(m_hwnd,0x0500,0,(double)lcout*0.01);
					//}
				}
			}
		}
		else if (strLine.compare("OBJECTS") == 0)
		{
			/*OBJECTS段
				作用:	
			*/
			while (strLine.compare("ENDSEC") != 0)
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendProgressMessage();

				//如下添加需要处理部分
			}
		}
		else if (strLine.compare("CLASSES") == 0)
		{
			/*类段
				作用:	
			*/
			while (strLine.compare("ENDSEC") != 0)
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendProgressMessage();

				//如下添加需要处理部分
			}
		}
		else if (strLine.compare("BLOCKS") == 0)
		{
			/*块段
				作用:	
			*/
			while (strLine.compare("ENDSEC") != 0)
			{
				GETLINE(sin,strLine);
				sout<<strLine<<endl ;
				SendProgressMessage();

				//如下添加需要处理部分
			}
		}
	}
}

/*
	作用：优化多段线图元
	时间：2012/12/13
	
*/
void DXFParseNextAcDbPolyline(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//从AcDbPolyline内的第一个组码开始
	//到0结束
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

	//读polyline
	while (strLine.compare("  0") != 0)
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if (strLine.compare(" 10") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof(strLine.c_str());
			vec_x.push_back( x );
		} 
		else if (strLine.compare(" 20") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof(strLine.c_str());
			vec_y.push_back( y );
		}
		else if (strLine.compare(" 30") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof(strLine.c_str());
			vec_z.push_back( z );
		}
	}

	iCount = vec_x.size();
	if (vec_z.size() == 0)
	{
		vec_z.assign(iCount, 0);
	}

	for (int i = 0; i< iCount ; i++)
	{	
		p_transform( vec_y[i] , vec_x[i] , vec_z[i] , out_y , out_x , out_z );

		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		vec_z [i] = out_z ;
	}

	//写Polyline
	while (getline(strPoint, tmpLine))
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);
			ox = DoubleToString( vec_x[num_write-1] );
			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( vec_y[num_write-1] );
			sout<<oy<<endl;
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
			}	
		}
	}
}

/*
	作用：处理点图元
	时间; 2012/12/13

*/
void DXFParseNextAcDbPoint(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//从AcDbPoint内的第一个组码开始
	//到0结束
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

	//读point
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//修改
	p_transform(  y , x, z , dy, dx, dz );

	//写Point	
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx );

			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( dy );

			sout<<oy<<endl;		
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
			}
		}
	}
}

//yzg 2012-9-6 增加对AcDbLine的支持 begin DXF编码信息如下：
/*
	100
	子类标记 (AcDbLine) 
	39
	厚度（可选；默认值 = 0）
	10
	起点（在 WCS 中）
	DXF：X 值；APP：三维点
	20, 30
	DXF：起点的 Y 值和 Z 值（在 WCS 中）
	11
	端点（在 WCS 中）
	DXF：X 值；APP：三维点
	21, 31
	DXF：端点的 Y 值和 Z 值（在 WCS 中）
	210
	拉伸方向（可选；默认值 = 0, 0, 1）
	DXF：X 值；APP：三维矢量
	220, 230
	DXF：拉伸方向的 Y 值和 Z 值（可选）
*/
/* 组码示例
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
void DXFParseNextAcDbLine(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//从AcDbLine内的第一个组码开始
	//到0结束
	stringstream strPoint;

	//线段的起始端 源
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	//线段的终止端 源
	double x2 = 0;
	double y2 = 0;
	double z2 = 0;

	//线段的起始端 目标 
	double dx1 = 0;
	double dy1 = 0;
	double dz1 = 0;

	//线段的终止端 目标 
	double dx2 = 0;
	double dy2 = 0;
	double dz2 = 0;

	char *ox;
	char *oy;
	char *oz;

	//读point
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 11") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z2 = atof( strLine.c_str() );
		}
	}

	//修改
	p_transform(  y1 , x1, z1 , dy1, dx1, dz1 );
	p_transform(  y2 , x2, z2 , dy2, dx2, dz2 );

	//写Point
	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx1 );
			sout<<ox<<endl;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( dy1 );
			sout<<oy<<endl;
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
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( dy2 );
			sout<<oy<<endl;
			
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
	作用：处理文字图元
	时间：2012/12/13

*/
void DXFParseNextAcDbText(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	//从AcDbText内的第一个组码开始
	//到0结束
	stringstream strPoint;

	//线段的起始端 源
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	//线段的终止端 源
	double x2 = 0;
	double y2 = 0;
	double z2 = 0;

	//线段的起始端 目标 
	double dx1 = 0;
	double dy1 = 0;
	double dz1 = 0;

	//线段的终止端 目标 
	double dx2 = 0;
	double dy2 = 0;
	double dz2 = 0;

	char *ox;
	char *oy;
	char *oz;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0   )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0   )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 11") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z2 = atof( strLine.c_str() );
		}
	}

	//修改
	p_transform(  y1 , x1, z1 , dy1, dx1, dz1 );
	p_transform(  y2 , x2, z2 , dy2, dx2, dz2 );

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0   )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString(  dx1 );
			sout<<ox<<endl;		
		} 
		else if ( tmpLine.compare(" 20") == 0   )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy1 );
			sout<<oy<<endl;
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
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy2 );
			sout<<oy<<endl;
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
	作用：处理块参照图元
	时间：2012/12/13

*/
void DXFParseNextAcDbBlockReference(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	//从AcDbBlockReference内的第一个组码开始
	//到0结束

	stringstream strPoint;
	double x(0),y(0),z(0);

	char *ox;
	char *oy;
	char *oz;

	//读point
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//修改
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	//写Point
	string tmpLine;
	double tmpD = 0;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);		
			ox = DoubleToString(  dx );
			sout<<ox<<endl;

		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy );
			sout<<oy<<endl;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);
			//oz = DoubleToString(  dz );
			sout<<tmpLine<<endl;
		}
	}

	return;
}

void DXFParseTransMin(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);
	char *ox;
	char *oy;
	char *oz;

	//读point
	while( strLine.compare("  9") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0   )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0   )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0   )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//修改
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	//写Point
	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;
		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			
			oy = DoubleToString( dy );
			sout<<oy<<endl;
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

void DXFParseTransMax(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);
	char *ox;
	char *oy;
	char *oz;

	//读point
	while( strLine.compare("  9") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//修改
	double dx ,dy ,dz ;
	p_transform(  y , x, z , dy, dx, dz );

	//写Point
	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx );

			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( dy );

			sout<<oy<<endl;
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
	作用：处理视图中心点坐标
	时间：2012/12/13

*/
void DXFParseTransCentre(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);

	char *ox;
	char *oy;
	char *oz;

	while( strLine.compare("146") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 12") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		} 
		else if ( strLine.compare(" 22") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
	}

	//修改
	double dx ,dy ,dz, tempdx, tempdy, tempdz ;
	p_transform(  y , x, z , dy, dx, dz );
	
	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 12") == 0 )
		{
			getline(strPoint,tmpLine);
			
			ox = DoubleToString( dx );
			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 22") == 0 )
		{
			getline(strPoint,tmpLine);
			
			oy = DoubleToString( dy );
			sout<<oy<<endl;
		}
	}

	return;
}

/*
	作用：处理圆图元
	时间：2012/12/13

*/
void DXFParseNextAcDbCircle(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);

	char *ox;
	char *oy;
	char *oz;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//修改
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
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
	作用：处理椭圆图元
	时间：2012/12/13

*/
void DXFParseNextAcDbEllipse(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	//线段的起始端 源
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	//线段的终止端 源
	double x2 = 0;
	double y2 = 0;
	double z2 = 0;

	//线段的起始端 目标 
	double dx1 = 0;
	double dy1 = 0;
	double dz1 = 0;

	//线段的终止端 目标 
	double dx2 = 0;
	double dy2 = 0;
	double dz2 = 0;

	char *ox;
	char *oy;
	char *oz;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z1 = atof( strLine.c_str() );
		}
	}

	//修改
	p_transform( y1 , x1, z1 , dy1, dx1, dz1 );

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
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  dy1 );
			sout<<oy<<endl;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			sout<<tmpLine<<endl;
		}
	}

	return;
}

/*
	作用：处理多线图元
	时间：2012/12/13

*/
void DXFParseNextAcDbMline(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
		SendProgressMessage();

		 if( strLine.compare(" 11") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );

			vec_z.push_back( z );
		}
		else if (strLine.compare(" 10") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if (strLine.compare(" 20") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if (strLine.compare(" 30") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

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

	//起点
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

			ox = DoubleToString( vec_x[num_write-1] );
			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  vec_y[num_write-1] );
			sout<<oy<<endl;
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
		}
		else if (tmpLine.compare(" 20") == 0)
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( out_y1 );						

			sout<<oy<<endl;
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
	作用：处理图案填充和MPolygon图元
	时间：2012/12/13

*/
void DXFParseNextAcDbHatch(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
	//char			   *pVal = NULL;
	//double			dWidth = 0;
	////图案填充基点 X,Y分量
	//double			dHatchX = 0;
	//double			dHatchY = 0;
	//char			   *pHatchX = NULL;
	//char			   *pHatchY = NULL;
	//double			dHatchX_des = 0;
	//double			dHatchY_des = 0;
	//double			dHatchZ_des = 0;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();
			
			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		/*else if ( strLine.compare(" 30") == 0 )//说明：Z值默认为0.0
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
			SendProgressMessage();

			x = atof( strLine.c_str() );
			vec_x_o.push_back( x );
		}
		else if (strLine.compare(" 21") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
			vec_y_o.push_back( y );
		}
		/*else if (strLine.compare(" 43") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			dHatchX = atof(strLine.c_str());
		}
		else if (strLine.compare(" 44") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			dHatchY = atof(strLine.c_str());
		}*/
	}

	int iCount = vec_x.size();
	/*if ( vec_z.size() == 0 )
	{
		vec_z.assign( iCount , 0 );
	}*/

	for ( int i = 0; i< iCount ; i++)
	{
		double out_x(0),out_y(0),out_z(0);
		
		p_transform( vec_y[i] , vec_x[i] , /*vec_z[i]*/0.0 , out_y , out_x , out_z );
	
		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		//vec_z [i] = out_z ;
	}

	//11,21的处理
	iCount = vec_x_o.size();
	for ( int i = 0; i< iCount ; i++)
	{
		double out_x(0),out_y(0),out_z(0);

		p_transform( vec_y_o[i] , vec_x_o[i] , /*vec_z[i]*/0.0 , out_y , out_x , out_z );

		vec_x_o [i] = out_x ;
		vec_y_o [i] = out_y ;
		//vec_z [i] = out_z ;
	}

	//add by chenyong 2013-5-17
	// p_transform(dHatchY, dHatchX, 0.0, dHatchY_des, dHatchX_des, dHatchZ_des);

	string tmpLine;
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;
		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		
			getline(strPoint,tmpLine);

			ox = DoubleToString( vec_x[num_write-1] );
			sout<<ox<<endl;	
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( vec_y[num_write-1] );
			sout<<oy<<endl;			
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
			
			ox = DoubleToString( vec_x_o[num_write_o-1] );
			sout<<ox<<endl;	
		}
		else if (tmpLine.compare(" 21") == 0)
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( vec_y_o[num_write_o-1] );
			sout<<oy<<endl;
		}
		/*else if (tmpLine.compare(" 43") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pHatchX = DoubleToString(dHatchX_des);
				sout<<pHatchX<<endl;
				delete pHatchX;
			}
		}
		else if (tmpLine.compare(" 44") == 0)
		{
			getline(strPoint, tmpLine);
			if (tmpLine.compare("0.0") == 0)
			{
				sout<<tmpLine<<endl;
			}
			else
			{
				pHatchY = DoubleToString(dHatchY_des);
				sout<<pHatchY<<endl;
				delete pHatchY;
			}
		}*/
	}	

	return;

}

/*
	作用：处理圆弧图元
	时间：2012/12/13

*/
void DXFParseNextAcDbArc(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;
	double x(0),y(0),z(0);

	char *ox;
	char *oy;
	char *oz;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//修改
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
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);			
			oy = DoubleToString( dy );

			sout<<oy<<endl;
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
	作用：处理二维或三维多线顶点图元
	时间：2012/12/13

*/
void DXFParseNextAcDb2dOr3dPolylineVertex(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream							strPoint;

	double									x(0);
	double									y(0);
	double									z(0);
	
	char*									ox = NULL;
	char*									oy = NULL;
	char*									oz = NULL;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//修改
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
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
	作用：处理样条曲线图元
	时间：2012/12/13
*/
void DXFParseNextAcDbSpline(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
		SendProgressMessage();

		if( strLine.compare(" 10") == 0  )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
		}
		else if ( strLine.compare(" 11") == 0 )//处理拟合点信息add201704
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
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
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  vec_y[num_write-1] );

			sout<<oy<<endl;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString(  vec_z[num_write-1] );						
			sout<<tmpLine<<endl;			
		}

		if( tmpLine.compare(" 11") == 0 )//处理拟合点信息add201704
		{
			num_write++;		

			getline(strPoint,tmpLine);

			ox = DoubleToString(  vec_x[num_write-1] );
			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString(  vec_y[num_write-1] );

			sout<<oy<<endl;
		}
		else if ( tmpLine.compare(" 31") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString(  vec_z[num_write-1] );						
			sout<<tmpLine<<endl;			
		}
	}

	return;
}

/*
	作用：处理三维面图元
	时间：2012/12/13

*/
void DXFParseNextAcDbFace(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	/*第一角点*/
	double									x0(0);
	double									y0(0);
	double									z0(0);

	double									dx0(0);
	double									dy0(0);
	double									dz0(0);

	/*第二角点*/
	double									x1(0);
	double									y1(0);
	double									z1(0);

	double									dx1(0);
	double									dy1(0);
	double									dz1(0);

	/*第三角点*/
	double									x2(0);
	double									y2(0);
	double									z2(0);

	double									dx2(0);
	double									dy2(0);
	double									dz2(0);

	/*第四角点*/
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
		/*第一角点*/
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x0 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y0 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z0 = atof( strLine.c_str() );
		}

		/*第二角点*/
		else if ( strLine.compare(" 11") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 21") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 31") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z1 = atof( strLine.c_str() );
		}

		/*第三角点*/
		else if ( strLine.compare(" 12") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 22") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 32") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z2 = atof( strLine.c_str() );
		}

		/*第四角点*/
		else if ( strLine.compare(" 13") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x3 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 23") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y3 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 33") == 0)
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z3 = atof( strLine.c_str() );
		}
	}

	//坐标转换
	p_transform(y0, x0, z0, dy0, dx0, dz0);
	p_transform(y1, x1, z1, dy1, dx1, dz1);
	p_transform(y2, x2, z2, dy2, dx2, dz2);
	p_transform(y3, x3, z3, dy3, dx3, dz3);

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		/*第一角点*/
		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx0 );
			sout<<ox<<endl;		
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy0 );
			sout<<oy<<endl;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz0 );
			sout<<tmpLine<<endl;
		}

		/*第二角点*/
		else if ( tmpLine.compare(" 11") == 0)
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx1 );
			sout<<ox<<endl;	
		}
		else if ( tmpLine.compare(" 21") == 0)
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy1 );
			sout<<oy<<endl;	
		}
		else if (tmpLine.compare(" 31") == 0)
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz1 );
			sout<<tmpLine<<endl;	
		}

		/*第三角点*/
		else if (tmpLine.compare(" 12") == 0)
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx2 );
			sout<<ox<<endl;	
		}
		else if (tmpLine.compare(" 22") == 0)
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy2 );
			sout<<oy<<endl;	
		}
		else if (tmpLine.compare(" 32") == 0)
		{
			getline(strPoint,tmpLine);

			//oz = DoubleToString( dz2 );
			sout<<tmpLine<<endl;	
		}

		/*第四角点*/
		else if (tmpLine.compare(" 13") == 0)
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx3 );
			sout<<ox<<endl;	
		}
		else if (tmpLine.compare(" 23") == 0)
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy3 );
			sout<<oy<<endl;	
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
	作用：处理多行文字图元
	时间：2012/12/13

*/
void DXFParseNextAcDbMText(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}
	
	//坐标转换
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;		
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
	作用：处理形图元
	时间：2012/12/13

*/
void DXFParseNextAcDbShape(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//坐标转换
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;		
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
	作用：处理射线图元
	时间：2012/12/13
*/
void DXFParseNextAcDbRay(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//坐标转换
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;		
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
	作用：处理二维或三维的多段线图元
	时间：2012/12/13

*/
void DXFParseNextAcDb2dOr3dPolyline(std::ifstream &sin, std::ofstream &sout, string &strLine)
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

	//读polyline
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
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

	//写Polyline
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);
			ox = DoubleToString( vec_x[num_write-1] );
			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( vec_y[num_write-1] );
			sout<<oy<<endl;
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
			}	
		}
	}
}

/*
	作用：处理视口图元
	时间：2012/12/13

*/
void DXFParseNextAcDbViewport(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream							strPoint;

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
		SendProgressMessage();

		/*WCS*/
		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}

		/*DCS*/
		else if (strLine.compare(" 12") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x1 = atof(strLine.c_str());
		}
		else if (strLine.compare(" 22") == 0)
		{
			GETLINE(sin, strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y1 = atof(strLine.c_str());
		}
	}

	//坐标转换
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
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
		}
		else if ( tmpLine.compare(" 22") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy1 );
			sout<<oy<<endl;
		}
	}

	return;
}

/*
	作用：构造线图元
	时间：2012/12/13

*/
void DXFParseNextAcDbXline(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//坐标转换
	p_transform( y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;		
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
	作用：处理公差图元
	时间：2012/12/13

*/
void DXFParseNextAcDbFcf(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//坐标转换
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;		
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
	作用: 图像图元
	时间：2012/12/13

*/
void DXFParseNextAcDbRasterImage(std::ifstream &sin, std::ofstream &sout, string &strLine)
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
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
		}
	}

	//坐标转换
	p_transform(  y , x, z , dy, dx, dz );

	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			getline(strPoint,tmpLine);

			ox = DoubleToString( dx );
			sout<<ox<<endl;		
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( dy );
			sout<<oy<<endl;
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
	作用：处理引线图元
	时间：2012/12/13

*/
void DXFParseNextAcDbLeader(std::ifstream &sin, std::ofstream &sout, string &strLine)
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

	//读polyline
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x = atof( strLine.c_str() );
			vec_x.push_back( x );
		} 
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y = atof( strLine.c_str() );
			vec_y.push_back( y );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z = atof( strLine.c_str() );
			vec_z.push_back( z );
		}
	}

	iCount = vec_x.size();

	if ( vec_z.size() == 0 )
		vec_z.assign( iCount , 0 );

	for ( int i = 0; i< iCount ; i++)
	{	
		p_transform( vec_y[i] , vec_x[i] , vec_z[i] , out_y , out_x , out_z );

		vec_x [i] = out_x ;
		vec_y [i] = out_y ;
		vec_z [i] = out_z ;
	}

	//写Polyline
	while( getline(strPoint,tmpLine) )
	{
		sout<<tmpLine<<endl;

		if( tmpLine.compare(" 10") == 0 )
		{
			num_write++;		

			getline(strPoint,tmpLine);
			ox = DoubleToString(  vec_x[num_write-1] );
			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);

			oy = DoubleToString( vec_y[num_write-1] );
			sout<<oy<<endl;
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
			}	
		}
	}
}

/*
	作用：处理Ole2Frame图元
	时间：2012/12/13

*/
void DXFParseNextAcDbOle2Frame(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	stringstream strPoint;

	//线段的起始端 源
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;

	//线段的终止端 源
	double x2 = 0;
	double y2 = 0;
	double z2 = 0;

	//线段的起始端 目标 
	double dx1 = 0;
	double dy1 = 0;
	double dz1 = 0;

	//线段的终止端 目标 
	double dx2 = 0;
	double dy2 = 0;
	double dz2 = 0;

	char *ox;
	char *oy;
	char *oz;

	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		strPoint<<strLine<<endl;
		SendProgressMessage();

		if( strLine.compare(" 10") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 20") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 30") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z1 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 11") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			x2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 21") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			y2 = atof( strLine.c_str() );
		}
		else if ( strLine.compare(" 31") == 0 )
		{
			GETLINE(sin,strLine);
			strPoint<<strLine<<endl;
			SendProgressMessage();

			z2 = atof( strLine.c_str() );
		}
	}

	//修改
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
		} 
		else if ( tmpLine.compare(" 20") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString(  dy1 );
			sout<<oy<<endl;
		}
		else if ( tmpLine.compare(" 30") == 0 )
		{
			getline(strPoint,tmpLine);
			sout<<tmpLine<<endl;
		}
		else if ( tmpLine.compare(" 11") == 0 )
		{
			getline(strPoint,tmpLine);
			ox = DoubleToString( dx2 );
			sout<<ox<<endl;
		}
		else if ( tmpLine.compare(" 21") == 0 )
		{
			getline(strPoint,tmpLine);
			oy = DoubleToString( dy2 );
			sout<<oy<<endl;
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

void DXFParseVPORT(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendProgressMessage();

		//视图中心
		if ( strLine.compare("*Active") == 0)
		{
			DXFParseTransCentre(sin, sout, strLine);
		}
	}
}

void DXFParseTablesSec(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendProgressMessage();

	if (strLine.compare("ENDSEC") == 0)
	{
		return;
	}

	while (strLine.compare("ENDTAB") != 0)
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendProgressMessage();

		while (strLine.compare("  0") == 0)  //解决连续
		{
			DXFParseTableObjects(sin, sout, strLine);
		}
	}
}

void DXFParseTableObjects(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	/*
	TABLE段：1.VPORT(视口配置表,可能包含多个同名的条目（表示多视口配置），
				与活动视口配置相对应条目名称均为*ACTIVE)
			 2.APPID(应用程序标识表)
			 3.BLOCK_RECORD(块参照表)
			 4.DIMSTYLE(标注样式表)
			 5.LAYER(图层表)
			 6.LTYPE(线型表)
			 7.STYLE(文字样式表)
			 8.UCS(用户坐标系表)
			 9.VIEW(视图表)
	*/
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendProgressMessage();

	if (strLine.compare("VPORT") == 0)
	{
		DXFParseVPORT(sin, sout, strLine);
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

void DXFParseEntitiesSec(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	/*
		ENTITIES: 1.HATCH
				  2.3DFACE(三维面图元)
				  3.ARC(圆弧图元)
				  4.ATTDEF(属性定义图元)
				  5.ATTRIB(属性图元)
				  6.CIRCLE(圆图元)
				  7.ELLIPSE(椭圆图元)
				  8.IMAGE(图像图元)
				  9.INSERT(块参照图元)
				  10.LEADER(引线图元)
				  11.LINE(直线图元)
				  12.LWPOLYLINE(多段线图元)
				  13.MLINE(多线图元)
				  14.MTEXT(多行文字图元)
				  15.OLE2FRAME(ole2frame图元)
				  16.POINT(点图元)
				  17.POLYLINE(多段线图元)
				  18.RAY(射线图元)
				  19.SHAPE(形图元)
				  20.SOLID(实体图元)
				  21.SPLINE(样条曲线图元)
				  22.TEXT(文字图元)
				  23.TOLERANCE(公差图元)
				  24.TRACE(跟踪图元)
				  25.VERTEX(顶点图元)
				  25.VIEWPORT(视口图元)
				  26.WIPEOUT(擦除图元)
				  27.XLINE(构造线图元)
	*/
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendProgressMessage();
	
	if (strLine.compare("HATCH") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("3DFACE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("ARC") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("ATTDEF") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("ATTRIB") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("CIRCLE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("ELLIPSE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("IMAGE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("INSERT") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("LEADER") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("LINE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("LWPOLYLINE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("MLINE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("MTEXT") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("OLE2FRAME") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("POINT") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("POLYLINE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("RAY") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("SHAPE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbTrace") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("SPLINE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("TEXT") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("TOLERANCE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("TRACE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("VERTEX") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("VIEWPORT") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("WIPEOUT") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
	else if (strLine.compare("XLINE") == 0)
	{
		DXFParseEntiCom(sin, sout, strLine);
	}
}

void DXFParseEntiCom(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	while( strLine.compare("  0") != 0 )
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendProgressMessage();

		while( strLine.compare("100") == 0   )
		{
			DXFParseNextEntiSubClass( sin , sout , strLine );
		}
	}
}

void DXFParseNextEntiSubClass(std::ifstream &sin, std::ofstream &sout, string& strLine)
{
	//获得子类的类别
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendProgressMessage();

	if( strLine.compare("AcDbEntity") == 0  )
	{				
		DXFParseNextEntiAcDbEntity( sin , sout , strLine );
	}
}

void DXFParseNextEntiAcDbEntity(std::ifstream &sin, std::ofstream &sout, string &strLine)
{
	while( strLine.compare("100") != 0 )
	{
		GETLINE(sin,strLine);
		sout<<strLine<<endl ;
		SendProgressMessage();
	}

	//ENTITIES子类
	GETLINE(sin,strLine);
	sout<<strLine<<endl ;
	SendProgressMessage();

	if(strLine.compare("AcDbHatch") == 0)
	{
		DXFParseNextAcDbHatch(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbFace") == 0)
	{
		DXFParseNextAcDbFace(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbText") == 0)
	{
		DXFParseNextAcDbText(sin, sout, strLine);
	}
	/*else if (strLine.compare("AcDbAttributeDefinition") == 0)
	{

	}*/
	else if (strLine.compare("AcDbCircle") == 0)
	{
		DXFParseNextAcDbCircle(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbEllipse") == 0)
	{
		DXFParseNextAcDbEllipse(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbRasterImage") == 0)
	{
		DXFParseNextAcDbRasterImage(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbBlockReference") == 0)
	{
		DXFParseNextAcDbBlockReference(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbLeader") == 0)
	{
		DXFParseNextAcDbLeader(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbLine") == 0)
	{
		DXFParseNextAcDbLine(sin , sout , strLine);
	}
	else if (strLine.compare("AcDbPolyline") == 0)
	{
		DXFParseNextAcDbPolyline( sin , sout , strLine );
	}
	else if (strLine.compare("AcDbMline") == 0)
	{
		DXFParseNextAcDbMline(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbMText") == 0)
	{
		DXFParseNextAcDbMText(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbOle2Frame") == 0)
	{
		DXFParseNextAcDbOle2Frame(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbPoint") == 0)
	{
		DXFParseNextAcDbPoint( sin , sout , strLine );
	}
	else if (strLine.compare("AcDb2dPolyline") == 0)
	{
		DXFParseNextAcDb2dOr3dPolyline( sin, sout, strLine);
	}
	else if (strLine.compare("AcDb3dPolyline") == 0)
	{
		DXFParseNextAcDb2dOr3dPolyline( sin, sout, strLine);
	}
	else if (strLine.compare("AcDbRay") == 0)
	{
		DXFParseNextAcDbRay(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbShape") == 0)
	{
		DXFParseNextAcDbShape(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbSpline") == 0)
	{
		DXFParseNextAcDbSpline(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbFcf") == 0)
	{
		DXFParseNextAcDbFcf(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbTrace") == 0)
	{
		//AcDbTrace组码与AcDbFace一致
		DXFParseNextAcDbFace(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbVertex") == 0)
	{
		DXFParseNextEntiAcDbEntity( sin , sout , strLine );
	}
	else if (strLine.compare("AcDb2dVertex") == 0)
	{
		DXFParseNextAcDb2dOr3dPolylineVertex(sin, sout, strLine);
	}
	else if (strLine.compare("AcDb3dPolylineVertex") == 0)
	{
		DXFParseNextAcDb2dOr3dPolylineVertex(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbViewport") == 0)
	{
		DXFParseNextAcDbViewport(sin, sout, strLine);
	}
	else if (strLine.compare("AcDbXline") == 0)
	{
		DXFParseNextAcDbXline(sin, sout, strLine);
	}
}