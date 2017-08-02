#include "StdAfx.h"
#include "DeuReadFile.h"


DeuReadFile::DeuReadFile(const char * szfn)
{
	ifstream infile(szfn);
	//ifstream infile("E:\\可写\\测试结果\\精度测试\\Config.ini");
	//ifstream infile("Config.ini");
    //默认是输出模式,附加模式(即不破坏原有内容)则: ofstream outfile   ("d:\\bbb.txt",ios_base::app)
    //ofstream outfile("d:\\bbb.txt");  
    string sline;//每一行
    string s1,s2,s3,s4,s5,s6;
    /*vector<string> vec1,vec2;*/
    while(getline(infile,sline))
    {
        istringstream sin(sline);
        sin>>s1>>s2>>s3>>s4>>s5>>s6;
        vec1.push_back(s1);
        vec2.push_back(s2);
		vec3.push_back(s3);
		vec4.push_back(s4);
		vec5.push_back(s5);
		vec6.push_back(s6);


    }
}

DeuReadFile::~DeuReadFile(void)
{
}
