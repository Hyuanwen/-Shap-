/******************************************************************************
* $Id: geocent.h 1 2010-08-17 14:38:05Z daifeng $
*
* Project:  DeuProject 1.0
* Purpose:  Primary (private) include file for DeuProject API, and constants.
* Author:   daifeng, <nuistbaker@126.com>
*
******************************************************************************/

/********************************************************************************/
/* ABSTRACT
 *
 *    This component provides conversions between Geodetic coordinates (latitude,
 *    longitude in radians and height in meters) and Geocentric coordinates
 *    (X, Y, Z) in meters.
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *      GEOCENT_NO_ERROR        : No errors occurred in function
 *      GEOCENT_LAT_ERROR       : Latitude out of valid range
 *                                 (-90 to 90 degrees)
 *      GEOCENT_LON_ERROR       : Longitude out of valid range
 *                                 (-180 to 360 degrees)
 *      GEOCENT_A_ERROR         : Semi-major axis less than or equal to zero
 *      GEOCENT_B_ERROR         : Semi-minor axis less than or equal to zero
 *      GEOCENT_A_LESS_B_ERROR  : Semi-major axis less than semi-minor axis
 */

#ifndef _GEOCENT_H_
#define _GEOCENT_H_

#define GEOCENT_NO_ERROR        0x0000
#define GEOCENT_LAT_ERROR       0x0001
#define GEOCENT_LON_ERROR       0x0002
#define GEOCENT_A_ERROR         0x0004
#define GEOCENT_B_ERROR         0x0008
#define GEOCENT_A_LESS_B_ERROR  0x0010

typedef struct 
{
	double Geocent_a;        /* Semi-major axis of ellipsoid in meters */
	double Geocent_b;        /* Semi-minor axis of ellipsoid           */
	double Geocent_a2;       /* Square of semi-major axis */
	double Geocent_b2;       /* Square of semi-minor axis */
	double Geocent_e2;       /* Eccentricity squared  */
	double Geocent_ep2;      /* 2nd eccentricity squared */
} GeocentricInfo;

long pj_Set_Geocentric_Parameters (GeocentricInfo *gi, double a, double b) ;

void pj_Get_Geocentric_Parameters (GeocentricInfo *gi,
								   double *a, 
								   double *b);

long pj_Convert_Geodetic_To_Geocentric (GeocentricInfo *gi,
										double Latitude,
										double Longitude,
										double Height,
										double *X,
										double *Y,
										double *Z);

void pj_Convert_Geocentric_To_Geodetic (GeocentricInfo *gi,
										double X,
										double Y, 
										double Z,
										double *Latitude,
										double *Longitude,
										double *Height);
#endif