
// GLDisplayContext.h: interface for the NaGsDisplayContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLDISPLAYCONTEXT_H__D04FD53F_4852_4D6C_957A_44E8AE0C54DB__INCLUDED_)
#define AFX_GLDISPLAYCONTEXT_H__D04FD53F_4852_4D6C_957A_44E8AE0C54DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListOfNaDbObject.h"
#include "ListIteratorOfListOfNaDbObject.h"
#include "ListOfNaDbObjectId.h"
#include "ListIteratorOfListOfNaDbObjectId.h"
#include "NaDbObject.h"
#include "NaGeBoundingBox.h"
#include "NaGsView.h"

class NaGsView;

class NaGsDisplayContext  
{
public:
	NaGsDisplayContext();
	NaGsDisplayContext(CWnd* pDoc);
	virtual ~NaGsDisplayContext();
	void Display(NaDbObject*);
	void Erase(const NaDbObject*);
	void DisplayAll();
	void DisplaySelected();
	void EraseAll();
	void EraseSelected();
	void DeleteAll();
	void DeleteSelected();
	void Render(const GsDisplayMode& = GLWIREFRAME);
	bool Select(NaGsView* aView, const int& x, const int& y);
	bool MultiSelect(NaGsView* aView, const int& x, const int& y);
	bool SweepSelect(NaGsView* aView, const CRect& swRect);
	bool IsEmpty() const;
	bool IsDisplayed(const NaDbObject*) const;
	bool IsErased(const NaDbObject*) const;
	bool IsSelected(const NaDbObject*) const;
	bool IsAllDisplayed() const;
	bool IsAllErased() const;
	bool HasSelected() const;
	void InitSelected() const;
	bool MoreSelected() const;
	void NextSelected() const;
	NaDbObject* CurrentSelected() const;
	NaGeBoundingBox GetBoundingBox() const { return m_viewBox; }
	void SetSensitivity(const int& s) { m_mouseSensitivity = s; }
	//texture effect
	void SelectTriangle(NaGsView* aView, NaGePoint3D& pt);
	//file io
	void SaveObject(LPCTSTR filename);
private:
	void AddToSelection( NaDbObject* pDbObj);
	void RemoveSelection( NaDbObject* pDbObj);
	void EmptySelection();
private:
	CListOfNaDbObject* m_display;
	CListOfNaDbObject* m_erase;
	CListOfNaDbObject* m_select;
	mutable CListIteratorOfListOfNaDbObject m_selListIter;
	CWnd* m_ptrView;
	NaGeBoundingBox m_viewBox;
	int m_mouseSensitivity; //for selection;
	DWORD m_selectRGBA;
};

#endif // !defined(AFX_GLDISPLAYCONTEXT_H__D04FD53F_4852_4D6C_957A_44E8AE0C54DB__INCLUDED_)
