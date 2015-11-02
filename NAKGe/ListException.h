
/***************************************************************************
 *            ListException.h
 *
 ****************************************************************************/

#ifndef _LISTEXCEPTION_H
#define _LISTEXCEPTION_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

enum LIST_ERROR{ LIST_OUT_OF_MEMORY, LIST_BOUND_LOWER, LIST_BOUND_UPPER, LIST_EMPTY, ERROR_UNKNOWN };

class NAKGE_API CListException  
{
public:
	CListException(){}
	CListException(LIST_ERROR type);
	virtual ~CListException();
	char* ErrorMessage();
private:
	char* msg;

};

#endif /* _LISTEXCEPTION_H */
