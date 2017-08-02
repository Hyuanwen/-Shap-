#pragma once
//#include<iostream> 
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

class DeuReadFile
{
public:
	DeuReadFile(const char *szfn);
public:
	~DeuReadFile(void);
public:
	vector<string> vec1,vec2,vec3,vec4,vec5,vec6;

	const char * szfn;
};
