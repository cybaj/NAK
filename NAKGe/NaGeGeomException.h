
/***************************************************************************
 *            NaGeGeomException.h
 *
 *  Thu Jun 29 22:17:54 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _GEOMEXCEPTION_H
#define _GEOMEXCEPTION_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

enum ErrorType { DivideByZero, ConstructionFailure, MaxDegree, InvalidRange};

class NAKGE_API NaGeGeomException  
{
public:
	NaGeGeomException();
	NaGeGeomException(ErrorType type);
	virtual ~NaGeGeomException();
	char* ErrorMessage() const;
private:
	char* msg;

};

#endif /* _GEOMEXCEPTION_H */
