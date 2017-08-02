/**
*		功能：支持dxf投影转换
*		
*		时间：2013-5-14
*/

#ifndef _DXFPROJECT_H
#define _DXFPROJECT_H

//功能：	循环读DXF文件,文件以0组码开始
void DXFProjectNextLine( std::ifstream &sin, std::ofstream &sout, string & strLine, bool bToPlane);

/*
说明：支持DXF文件坐标转换
*/

//功能：	段处理
void DXFProjectSECTION(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextSection(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectEntitiesSec(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectTableObjects(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectTablesSec(std::ifstream &sin, std::ofstream &sout, string &strLine);

//功能：	子类处理
void DXFProjectNextAcDbLine(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbSpline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectCommon(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextEntiAcDbEntity(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextEntiSubClass(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectEntiCom(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbArc(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbMline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbHatch(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDb2dOr3dPolylineVertex(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbEntity( std::ifstream &sin, std::ofstream &sout, string &strLine );
void DXFProjectNextAcDbPoint( std::ifstream &sin, std::ofstream &sout, string &strLine );
void DXFProjectNextAcDbPolyline( std::ifstream &sin, std::ofstream &sout, string &strLine );
void DXFProjectNextAcDbXrecord( std::ifstream &sin, std::ofstream &sout, string &strLine );
void DXFProjectNextAcDbText(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbBlockReference(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbFace(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbMText(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbShape(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbRay(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDb2dOr3dPolyline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbViewport(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbXline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbFcf(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbRasterImage(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbLeader(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbOle2Frame(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbCircle(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectNextAcDbEllipse(std::ifstream &sin, std::ofstream &sout, string &strLine);

//功能：	图形范围
void DXFProjectTransMin(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFProjectTransMax(std::ifstream &sin, std::ofstream &sout, string &strLine);

//功能：	视图中心
void DXFProjectVPORT(std::ifstream &sin, std::ofstream &sout, string& strLine);
void DXFProjectTransCentre(std::ifstream &sin, std::ofstream &sout, string & strLine);

//void DXFProjectTransTextSize(std::ifstream &sin, std::ofstream &sout, string &strLine);

#endif