
/***************************************************************************
 *            NaGeBsp.h
 *
 ****************************************************************************/


#ifndef _BSP_H
#define _BSP_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

struct point
{
  double x;
  double y;
  double z;
};

NAKGE_API  void compute_intervals(int *u, int n, int t);
NAKGE_API  double blend(int k, int t, int *u, double v);
NAKGE_API  void compute_point(int *u, int n, int t, double v, point *control,
		   point *output);
NAKGE_API  void bspline(int n, int t, point *control, point *output, int num_output);

#endif /* _BSP_H */
