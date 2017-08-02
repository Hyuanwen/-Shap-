#ifndef EOOPARSE_H
#define EOOPARSE_H

void EooParseNextLine( std::ifstream &sin, std::ofstream &sout, string & strLine );

//yzg
void EooParseArc2(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParseArc2_point(std::ifstream &sin, std::ofstream &sout, string & strLine);

//liujun
void EooParseLAB2(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParseLAB_point(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParseLAB2_mark(std::ifstream &sin, std::ofstream &sout, string & strLine);

void EooParseCNT2(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParseCNT2_point(std::ifstream &sin, std::ofstream &sout, string & strLine);

void EooParsePAL2(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParsePAL2_point(std::ifstream &sin, std::ofstream &sout, string & strLine);

void EooParseArc3(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParseArc3_point(std::ifstream &sin, std::ofstream &sout, string & strLine);

void EooParseLAB3(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParseLAB3_point(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParseLAB3_mark(std::ifstream &sin, std::ofstream &sout, string & strLine);

void EooParseCNT3(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParseCNT3_point(std::ifstream &sin, std::ofstream &sout, string & strLine);

void EooParsePAL3(std::ifstream &sin, std::ofstream &sout, string & strLine);
void EooParsePAL3_point(std::ifstream &sin, std::ofstream &sout, string & strLine);

#endif