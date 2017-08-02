#ifndef DXFPARSE_H
#define DXFPARSE_H

/*
	˵����֧��DXF�ļ�����ת��
*/

//���ܣ�	ѭ����DXF�ļ�,�ļ���0���뿪ʼ
void DXFParseNextLine(std::ifstream &sin, std::ofstream &sout, string &strLine);

//���ܣ�	�δ���
void DXFParseSECTION(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextSection(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseEntitiesSec(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseTableObjects(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseTablesSec(std::ifstream &sin, std::ofstream &sout, string &strLine);

//���ܣ�	���ദ��
void DXFParseNextAcDbLine(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbSpline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseCommon(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextEntiAcDbEntity(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextEntiSubClass(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseEntiCom(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbArc(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbMline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbHatch(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDb2dOr3dPolylineVertex(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbEntity(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbPoint(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbPolyline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbXrecord(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbText(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbBlockReference(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbFace(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbMText(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbShape(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbRay(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDb2dOr3dPolyline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbViewport(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbXline(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbFcf(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbRasterImage(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbLeader(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbOle2Frame(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbCircle(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseNextAcDbEllipse(std::ifstream &sin, std::ofstream &sout, string &strLine);

//���ܣ�	ͼ�η�Χ
void DXFParseTransMin(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseTransMax(std::ifstream &sin, std::ofstream &sout, string &strLine);

//���ܣ�	��ͼ����
void DXFParseVPORT(std::ifstream &sin, std::ofstream &sout, string &strLine);
void DXFParseTransCentre(std::ifstream &sin, std::ofstream &sout, string &strLine);

#endif