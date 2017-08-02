#pragma once
#include <string>
class ShapeData
{
public:
	ShapeData(void);
	~ShapeData(void);
	int id;
	double x;
	double y;
	double z;
	//const char[20] position;
	//const char[20] num;
	std::string position;
	std::string num;
};
