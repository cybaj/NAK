// UserSurface.h: interface for the CUserSurface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERSURFACE_H__799994D7_512A_4200_877D_F7AD0B3DF66E__INCLUDED_)
#define AFX_USERSURFACE_H__799994D7_512A_4200_877D_F7AD0B3DF66E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <NaGeBasicSurface.h>

class CUserSurface : public NaGeBasicSurface  
{
public:
	CUserSurface();
	virtual ~CUserSurface();
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

#endif // !defined(AFX_USERSURFACE_H__799994D7_512A_4200_877D_F7AD0B3DF66E__INCLUDED_)
