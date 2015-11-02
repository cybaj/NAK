// NaGeObjTexture.h: interface for the NaGeObjTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ObjTexture_H__799994D7_512A_4200_877D_F7AD0B3DF66E__INCLUDED_)
#define AFX_ObjTexture_H__799994D7_512A_4200_877D_F7AD0B3DF66E__INCLUDED_

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NaGeBasicSurface.h"

class NAKGE_API NaGeObjTexture : public NaGeBasicSurface
{
public:
	NaGeObjTexture();
	virtual ~NaGeObjTexture();
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	virtual double FirstUParameter() const;
	virtual double LastUParameter() const;
	virtual double FirstVParameter() const;
	virtual double LastVParameter() const;
	virtual bool IsUClosed() const;
	virtual bool IsVClosed() const;
	virtual NaGeSurface* Copy() const;
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&) ;

};

#endif // !defined(AFX_ObjTexture_H__799994D7_512A_4200_877D_F7AD0B3DF66E__INCLUDED_)
