// GeomException.cpp: implementation of the NaGeGeomException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeGeomException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeGeomException::NaGeGeomException()
{

}

NaGeGeomException::NaGeGeomException(ErrorType type)
{
	msg = new char[50];
	switch (type)
	{
		case DivideByZero:
			msg = "\nDivide By Zero Raised!\n";
			break;
		case ConstructionFailure:
			msg = "\nConstruction Failure Raised!\n";
			break;
		case MaxDegree:
			msg = "\nDegree Greater Than Maximum Degree Allowed!\n";
				break;
		default:
			break;
	}
}

NaGeGeomException::~NaGeGeomException()
{
	delete [] msg;
}

char* NaGeGeomException::ErrorMessage() const
{
	return msg;
}

