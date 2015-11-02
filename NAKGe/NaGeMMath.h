
 
/***************************************************************************
 *            NaGeMMath.h
 *
 ****************************************************************************/


#ifndef _MMATH_H
#define _MMATH_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Some Useful Math Routines and definitions
//Some Are Directly From Graphics Gems

#ifndef PI
#define PI (double)3.1415926535897932384626433832795
#endif

#ifndef INFINITY
#define INFINITY (double)999999.999f
#endif

#ifndef EPSILON
#define EPSILON (double)0.000001f
#endif

#ifndef MAX
#define MAX(X, Y) (X) > (Y) ? (X) : (Y)
#endif				

#ifndef vsin
#define vsin(x) ((1.0) - (double)(cos(x))) //versine theta (1 - cos theta)
#endif	
				     
NAKGE_API  double degToRad(double ang);

NAKGE_API  double radToDeg(double ang);

NAKGE_API  double sround(const double& );

struct Matrix4 /* 4-by-4 matrix */
{	
	double element[4][4];
};


NAKGE_API  void inverse( Matrix4* in, Matrix4* out );
NAKGE_API  void adjoint(Matrix4 *in, Matrix4 *out);
NAKGE_API  double det2x2( double a, double b, double c, double d);
NAKGE_API  double det3x3( double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3 );
NAKGE_API  double det4x4( Matrix4 *m );

#endif /* _MMATH_H */
