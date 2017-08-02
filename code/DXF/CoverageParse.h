#ifndef COVERAGEPARSE_H
#define COVERAGEPARSE_H

#include "dxf.h"

void CoverageParse(const char * FileIn, const char * FileOut);

void CoverageParseARC2(const char * FileIn, const char * FileOut);

void CoverageParseARC3(const char * FileIn, const char * FileOut);

void CoverageParseLAB2(const char * FileIn, const char * FileOut);

void CoverageParseLAB3(const char * FileIn, const char * FileOut);

void CoverageParsePAL2(const char * FileIn, const char * FileOut);

void CoverageParsePAL3(const char * FileIn, const char * FileOut);

void CoverageParseCNT2(const char * FileIn, const char * FileOut);

void CoverageParseCNT3(const char * FileIn, const char * FileOut);

void CoverageParseTX6_7_3(const char * FileIn, const char * FileOut);

void CoverageParseTX6_7_2(const char * FileIn, const char * FileOut);

void CoverageParseTXT3(const char * FileIn, const char * FileOut);

void CoverageParseTXT2(const char * FileIn, const char * FileOut);

void CoverageParseBND(const char * FileIn, const char * FileOut);

void CoverageParseEx(const char * FileIn, const char * FileOut);

#endif