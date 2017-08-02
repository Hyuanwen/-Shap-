#include "stdafx.h"
#include "DXF.h"
#include "EooParse.h"

void EooParseNextLine( std::ifstream &sin, std::ofstream &sout, string & strLine )
{
	//循环逐行读取源文件中每行的数据
	while( GETLINE(sin,strLine) )
	{
		InvokeProgressFun();
		//读取以后既可以写入到目标数据中
		sout<<strLine<<endl ;

		if (strLine.compare("ARC  2") == 0)  //如果单精度浮点型
		{
			EooParseArc2(sin, sout, strLine);
		}
		else if(strLine.compare("LAB  2") == 0)
		{
			EooParseLAB2(sin, sout, strLine);
		}
		else if(strLine.compare("CNT  2")== 0)
		{
			EooParseCNT2(sin,sout,strLine);
		}
		else if (strLine.compare("PAL  2") == 0)
		{
			EooParsePAL2(sin,sout,strLine);
		}
		else if (strLine.compare("ARC  3") == 0)
		{
			EooParseArc3(sin,sout,strLine);
		}
		else if (strLine.compare("LAB  3") == 0)
		{
			EooParseLAB3(sin,sout,strLine);
		}
		else if (strLine.compare("CNT  3") == 0)
		{
			EooParseCNT3(sin,sout,strLine);
		}
		else if (strLine.compare("PAL  3") == 0)
		{
			EooParsePAL3(sin,sout,strLine);
		}
	}

	return;
}

void EooParsePAL3(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	while (strLine.compare("        -1         0         0         0         0         0         0") !=0.)
	{
		GETLINE(sin,strLine);

		//取得下一行 这里必须要判断是记录头 还是线坐标点列表
		int i = strLine.size();
		if (i == 60||i==30)  
		{
			sout<<strLine<<endl;
		}
		else if (i == 42||i == 52) 
		{
			//点列表中的组数
			EooParsePAL3_point(sin, sout, strLine);
		}
		else
		{
			//无法处理
			sout<<strLine<<endl;
		}
	}
}

void EooParsePAL3_point(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;
	string          prvstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;

	if (strLine.size() == 52) //有两组坐标
	{
		prvstr = strLine.substr(0,10);

		tmpstr = strLine.substr(11,31);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(32,52);
		Scientific_notationtoDouble(tmpstr, &y1);

		p_transform(y1, x1, z, dy1, dx1, dz);

		//得两组点之后需要再转换为科学计数法构建成字符串写入
		//格式化成科学计数法
		SDoubletoScientific_notation(dx1, tmpstr);
		outstr = prvstr + " " +tmpstr;

		SDoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;
	}
	else if(strLine.size() == 42)
	{
		tmpstr = strLine.substr(1,21);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(22,42);
		Scientific_notationtoDouble(tmpstr, &y1);

		p_transform(y1, x1, z, dy1, dx1, dz);

		SDoubletoScientific_notation(dx1, tmpstr);
		outstr = " " + tmpstr;

		SDoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;
	}

	sout<<outstr<<endl;
} 

//处理单精度浮点型的函数
void EooParseCNT3(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	//如果不到LAB的最后一组 则进行递归处理
	while (strLine.compare("        -1         0         0         0         0         0         0") != 0 )
	{
		GETLINE(sin,strLine);

		//取得下一行 这里必须要判断是记录头 还是线坐标点列表
		int i = strLine.size();

		if (i == 10) //如果为10的长度则为记录头 否则认定为线坐标列表
		{
			sout<<strLine<<endl;
		}
		else if (i == 52) 
		{
			//点列表中的组数
			EooParseCNT3_point(sin, sout, strLine);
		}
		else
		{
			//无法处理
			sout<<strLine<<endl;
		}
	}

	return;
}

//单精度浮点数ARC的点列表的函数 每个类别的点列表均有不同 所以需要函数 单独处理
void EooParseCNT3_point(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;

	//char  * oxy;
	tmpstr = strLine.substr(0,10);
	if(tmpstr.compare("         0")==0)
	{
		tmpstr = strLine.substr(11,31);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(32,52);
		Scientific_notationtoDouble(tmpstr, &y1);

		p_transform(y1, x1, z, dy1, dx1, dz);

		SDoubletoScientific_notation(dx1, tmpstr);
		outstr = "         0 " + tmpstr;

		SDoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;
	}
	else
	{
		tmpstr = strLine.substr(11,31);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(32,52);
		Scientific_notationtoDouble(tmpstr, &y1);

		p_transform(y1, x1, z, dy1, dx1, dz);

		SDoubletoScientific_notation(dx1, tmpstr);
		outstr = "         1 " + tmpstr;

		SDoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;
	}

	sout<<outstr<<endl;
} 

//专门用于处理单精度浮点型的函数
void EooParseLAB3(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	while(strLine.compare("        -1         0 0.00000000000000E+00 0.00000000000000E+00") != 0 )
	{
		GETLINE(sin,strLine);

		int i = strLine.size();

		if (i == 62&&strLine.compare("        -1         0 0.00000000000000E+00 0.00000000000000E+00") != 0) 
		{
			EooParseLAB3_mark(sin,sout,strLine);
			//sout<<strLine<<endl;
		}
		else if (i == 42) 
		{
			EooParseLAB3_point(sin, sout, strLine);
		}
	}

	sout<<strLine<<endl;

	return;
}

void EooParseLAB3_point(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;

	tmpstr = strLine.substr(1,21);
	Scientific_notationtoDouble(tmpstr, &x1);

	tmpstr = strLine.substr(22,42);
	Scientific_notationtoDouble(tmpstr, &y1);

	p_transform(y1, x1, z, dy1, dx1, dz);

	SDoubletoScientific_notation(dx1, tmpstr);
	outstr = " " + tmpstr;

	SDoubletoScientific_notation(dy1, tmpstr);
	outstr = outstr + " " + tmpstr;

	sout<<outstr<<endl;
} 

//单精度浮点数ARC的点列表的函数 每个类别的点列表均有不同 所以需要函数 单独处理
void EooParseLAB3_mark(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;
	string          prvstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;

	prvstr = strLine.substr(0,21);

	tmpstr = strLine.substr(21,41);
	Scientific_notationtoDouble(tmpstr, &x1);

	tmpstr = strLine.substr(42,62);
	Scientific_notationtoDouble(tmpstr, &y1);

	p_transform(y1, x1, z, dy1, dx1, dz);

	SDoubletoScientific_notation(dx1, tmpstr);
	outstr = prvstr + tmpstr;

	SDoubletoScientific_notation(dy1, tmpstr);
	outstr = outstr + " " + tmpstr;

	sout<<outstr<<endl;
} 

void EooParseArc3(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	while (strLine.compare("        -1         0         0         0         0         0         0") !=0.)
	{
		GETLINE(sin,strLine);

		//取得下一行 这里必须要判断是记录头 还是线坐标点列表
		int i = strLine.size();

		if (i == 70)  
		{
			sout<<strLine<<endl;
		}
		else if (i == 42) 
		{
			//点列表中的组数
			EooParseArc3_point(sin, sout, strLine);
		}
		else
		{
			//无法处理
			sout<<strLine<<endl;
		}
	}
}

void EooParseArc3_point(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;

	tmpstr = strLine.substr(1,20);
	Scientific_notationtoDouble(tmpstr, &x1);

	tmpstr = strLine.substr(22,42);
	Scientific_notationtoDouble(tmpstr, &y1);

	p_transform(y1, x1, z, dy1, dx1, dz);

	SDoubletoScientific_notation(dx1, tmpstr);
	outstr = " " + tmpstr;

	SDoubletoScientific_notation(dy1, tmpstr);
	outstr = outstr + " " + tmpstr;

	sout<<outstr<<endl;
} 

void EooParsePAL2(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	while (strLine.compare("        -1         0         0         0         0         0         0") !=0.)
	{
		GETLINE(sin,strLine);

		//取得下一行 这里必须要判断是记录头 还是线坐标点列表
		int i = strLine.size();

		if (i == 60||i==30)  
		{
			sout<<strLine<<endl;
		}
		else if (i == 66) 
		{
			//点列表中的组数
			EooParsePAL2_point(sin, sout, strLine);
		}
		else
		{
			//无法处理
			sout<<strLine<<endl;
		}
	}
}

void EooParsePAL2_point(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;
	string          prvstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;

	prvstr = strLine.substr(0,10);

	tmpstr = strLine.substr(11,24);
	Scientific_notationtoDouble(tmpstr, &x1);

	tmpstr = strLine.substr(25,38);
	Scientific_notationtoDouble(tmpstr, &y1);

	tmpstr = strLine.substr(39,52);
	Scientific_notationtoDouble(tmpstr, &x2);

	tmpstr = strLine.substr(53,66);
	Scientific_notationtoDouble(tmpstr, &y2);

	p_transform(y1, x1, z, dy1, dx1, dz);
	p_transform(y2, x2, z, dy2, dx2, dz);

	//得两组点之后需要再转换为科学计数法构建成字符串写入
	//格式化成科学计数法
	DoubletoScientific_notation(dx1, tmpstr);
	outstr = prvstr + " " +tmpstr;

	DoubletoScientific_notation(dy1, tmpstr);
	outstr = outstr + " " + tmpstr;

	DoubletoScientific_notation(dx2, tmpstr);
	outstr = outstr + " " + tmpstr;

	DoubletoScientific_notation(dy2, tmpstr);
	outstr = outstr + " " + tmpstr;

	sout<<outstr<<endl;
} 

//处理单精度浮点型的函数
void EooParseCNT2(std::ifstream &sin, std::ofstream &sout, string & strLine)
{

	//如果不到LAB的最后一组 则进行递归处理
	while (strLine.compare("        -1         0         0         0         0         0         0") != 0 )
	{
		GETLINE(sin,strLine);

		//取得下一行 这里必须要判断是记录头 还是线坐标点列表
		int i = strLine.size();

		if (i == 10) //如果为10的长度则为记录头 否则认定为线坐标列表
		{
			sout<<strLine<<endl;
		}
		else if (i == 38) 
		{
			//点列表中的组数
			EooParseCNT2_point(sin, sout, strLine);
		}
		else
		{
			//无法处理
			sout<<strLine<<endl;
		}
	}

	return;
}

//单精度浮点数ARC的点列表的函数 每个类别的点列表均有不同 所以需要函数 单独处理
void EooParseLAB2_mark(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;
	string          prvstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;


	prvstr = strLine.substr(0,21);

	tmpstr = strLine.substr(21,34);
	Scientific_notationtoDouble(tmpstr, &x1);

	tmpstr = strLine.substr(35,48);
	Scientific_notationtoDouble(tmpstr, &y1);

	p_transform(y1, x1, z, dy1, dx1, dz);

	DoubletoScientific_notation(dx1, tmpstr);
	outstr = prvstr + tmpstr;

	DoubletoScientific_notation(dy1, tmpstr);
	outstr = outstr + " " + tmpstr;

	sout<<outstr<<endl;
} 

//单精度浮点数ARC的点列表的函数 每个类别的点列表均有不同 所以需要函数 单独处理
void EooParseCNT2_point(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;

	//char  * oxy;
	tmpstr = strLine.substr(0,10);
	if(tmpstr.compare("         0")==0)
	{
		tmpstr = strLine.substr(11,24);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(25,38);
		Scientific_notationtoDouble(tmpstr, &y1);

		p_transform(y1, x1, z, dy1, dx1, dz);

		DoubletoScientific_notation(dx1, tmpstr);
		outstr = "         0 " + tmpstr;

		DoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;

	}
	else
	{
		tmpstr = strLine.substr(11,24);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(25,38);
		Scientific_notationtoDouble(tmpstr, &y1);

		p_transform(y1, x1, z, dy1, dx1, dz);

		DoubletoScientific_notation(dx1, tmpstr);
		outstr = "         1 " + tmpstr;

		DoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;
	}

	sout<<outstr<<endl;
} 

//专门用于处理单精度浮点型的函数
void EooParseArc2(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	while (strLine.compare("        -1         0         0         0         0         0         0") != 0 )
	{
		GETLINE(sin,strLine);

		int i = strLine.size();

		if (i == 70) 
		{
			sout<<strLine<<endl;
		}
		else if (i == 56) 
		{

			EooParseArc2_point(sin, sout, strLine);
		}
		else if (i == 28)
		{

			EooParseArc2_point(sin, sout, strLine);
		}
		else
		{
			sout<<strLine<<endl;
		}
	}

	return;
}

//专门用于处理单精度浮点型的函数
void EooParseLAB2(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	while(strLine.compare("        -1         0 0.0000000E+00 0.0000000E+00") != 0 )
	{
		GETLINE(sin,strLine);

		int i = strLine.size();

		if (i == 48&&strLine.compare("        -1         0 0.0000000E+00 0.0000000E+00") != 0) 
		{
			EooParseLAB2_mark(sin,sout,strLine);
			//sout<<strLine<<endl;
		}
		else if (i == 56) 
		{
			EooParseLAB_point(sin, sout, strLine);
		}
	}

	sout<<strLine<<endl;

	return;
}

void EooParseLAB_point(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;


	if (strLine.size() == 56) //有两组坐标
	{
		tmpstr = strLine.substr(1,13);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(15,27);
		Scientific_notationtoDouble(tmpstr, &y1);

		tmpstr = strLine.substr(29,41);
		Scientific_notationtoDouble(tmpstr, &x2);

		tmpstr = strLine.substr(43,55);
		Scientific_notationtoDouble(tmpstr, &y2);

		p_transform(y1, x1, z, dy1, dx1, dz);
		p_transform(y2, x2, z, dy2, dx2, dz);

		//得两组点之后需要再转换为科学计数法构建成字符串写入
		//格式化成科学计数法
		DoubletoScientific_notation(dx1, tmpstr);
		outstr = " " + tmpstr;

		DoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;

		DoubletoScientific_notation(dx2, tmpstr);
		outstr = outstr + " " + tmpstr;

		DoubletoScientific_notation(dy2, tmpstr);
		outstr = outstr + " " + tmpstr;
	}
	else if (strLine.size() == 28)
	{
		tmpstr = strLine.substr(1,13);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(15,27);
		Scientific_notationtoDouble(tmpstr, &y1);

		p_transform(y1, x1, z, dy1, dx1, dz);

		DoubletoScientific_notation(dx1, tmpstr);
		outstr = " " + tmpstr;

		DoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;
	}

	sout<<outstr<<endl;
} 

void EooParseArc2_point(std::ifstream &sin, std::ofstream &sout, string & strLine)
{
	string          outstr;
	string          tmpstr;

	double          x1 = 0;
	double          y1 = 0;
	double          x2 = 0;
	double          y2 = 0;
	double          z = 0;

	double          dx1 = 0;
	double          dy1 = 0;
	double          dx2 = 0;
	double          dy2 = 0;
	double          dz = 0;


	if (strLine.size() == 56) //有两组坐标
	{
		tmpstr = strLine.substr(1,13);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(15,27);
		Scientific_notationtoDouble(tmpstr, &y1);

		tmpstr = strLine.substr(29,41);
		Scientific_notationtoDouble(tmpstr, &x2);

		tmpstr = strLine.substr(43,55);
		Scientific_notationtoDouble(tmpstr, &y2);

		p_transform(y1, x1, z, dy1, dx1, dz);
		p_transform(y2, x2, z, dy2, dx2, dz);

		//得两组点之后需要再转换为科学计数法构建成字符串写入
		//格式化成科学计数法
		DoubletoScientific_notation(dx1, tmpstr);
		outstr = " " + tmpstr;

		DoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;

		DoubletoScientific_notation(dx2, tmpstr);
		outstr = outstr + " " + tmpstr;

		DoubletoScientific_notation(dy2, tmpstr);
		outstr = outstr + " " + tmpstr;
	}
	else if (strLine.size() == 28)
	{
		tmpstr = strLine.substr(1,13);
		Scientific_notationtoDouble(tmpstr, &x1);

		tmpstr = strLine.substr(15,27);
		Scientific_notationtoDouble(tmpstr, &y1);

		p_transform(y1, x1, z, dy1, dx1, dz);

		DoubletoScientific_notation(dx1, tmpstr);
		outstr = " " + tmpstr;

		DoubletoScientific_notation(dy1, tmpstr);
		outstr = outstr + " " + tmpstr;
	}

	sout<<outstr<<endl;
} 





