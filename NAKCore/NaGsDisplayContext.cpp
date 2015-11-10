// GLDisplayContext.cpp: implementation of the NaGsDisplayContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NaGsDisplayContext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGsDisplayContext::NaGsDisplayContext()
{
}

NaGsDisplayContext::NaGsDisplayContext(CWnd* pWnd)
{
	m_display = new CListOfNaDbObject;
	m_erase = new CListOfNaDbObject;
	m_select = new CListOfNaDbObject;
	m_selListIter.SetList(m_select);
	m_selListIter.Init();
	m_ptrView = pWnd;
	m_viewBox.SetLimits(-1, 1, -1, 1, -1, 1);
	m_mouseSensitivity = 5; //5 pixels sensitivity
}

NaGsDisplayContext::~NaGsDisplayContext()
{
	if(!m_display->IsEmpty())
		m_display->Clear();
	if(!m_erase->IsEmpty())
		m_erase->Clear();
	if(!m_select->IsEmpty())
		m_select->Clear();

	delete m_display;
	delete m_erase;
	delete m_select;
}

void NaGsDisplayContext::Display(NaDbObject* pObj)
{
	if(pObj == NULL)
		return;

	//속도 및 메모리 처리 향상 copy -> ref
	NaDbObject* pDbObj = (NaDbObject*)pObj->Copy();
	if(m_display->IsEmpty())
		m_viewBox = pDbObj->GetBoundingBox();
	else
		m_viewBox.AddBox(pDbObj->GetBoundingBox());

	m_display->Append((NaDbObject*)pDbObj);
	m_ptrView->RedrawWindow();
}

void NaGsDisplayContext::Erase(const NaDbObject* aO)
{
	m_erase->Append(m_display->Remove(aO));
}

void NaGsDisplayContext::DisplayAll()
{
	CListIteratorOfListOfNaDbObject listIter(m_erase);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		NaDbObject* eO = listIter.Current();
		if(m_display->IsEmpty())
			m_viewBox = eO->GetBoundingBox();
		else
			m_viewBox.AddBox(eO->GetBoundingBox());
		m_display->Append(eO);
		listIter.SetCurrent(0);
	}
	m_erase->Clear();
}

void NaGsDisplayContext::DisplaySelected()
{
	if(!HasSelected())
		return;

	EraseAll();

	CListIteratorOfListOfNaDbObject listIterDel(m_erase);
	CListIteratorOfListOfNaDbObject listIterSel(m_select);
	NaDbObject* eO, *sO;
	for(listIterSel.Init(); listIterSel.More(); listIterSel.Next())
	{
		sO = listIterSel.Current();
		for(listIterDel.Init(); listIterDel.More(); listIterDel.Next())
		{
			eO = listIterDel.Current();
			if(eO->GetObjID() == sO->GetObjID())
				break;
		}
		if(m_display->IsEmpty())
			m_viewBox = eO->GetBoundingBox();
		else
			m_viewBox.AddBox(eO->GetBoundingBox());
		m_display->Append(m_erase->Remove(eO));
	}
	EmptySelection();
}

void NaGsDisplayContext::EraseAll()
{
	CListIteratorOfListOfNaDbObject listIter(m_display);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		m_erase->Append(listIter.Current());
		listIter.SetCurrent(0);
	}
	m_display->Clear();
}

void NaGsDisplayContext::EraseSelected()
{
	if(!HasSelected())
		return;
	CListIteratorOfListOfNaDbObject listIterD(m_display);
	CListIteratorOfListOfNaDbObject listIterSel(m_select);
	NaDbObject* eO, *sO;
	for(listIterSel.Init(); listIterSel.More(); listIterSel.Next())
	{
		sO = listIterSel.Current();
		for(listIterD.Init(); listIterD.More(); listIterD.Next())
		{
			eO = listIterD.Current();
			if(eO->GetObjID() == sO->GetObjID())
				break;
		}
		Erase(eO);
	}
	EmptySelection();
	m_viewBox.SetLimits(-1,1,-1,1,-1,1);
	for(listIterD.Init(); listIterD.More(); listIterD.Next())
		m_viewBox.AddBox(listIterD.Current()->GetBoundingBox());
}

void NaGsDisplayContext::DeleteAll()
{
	if(!m_display->IsEmpty())
		m_display->Clear();
	if(!m_erase->IsEmpty())
		m_erase->Clear();
	EmptySelection();
	m_viewBox.SetLimits(-1, 1, -1, 1, -1, 1);
}

void NaGsDisplayContext::DeleteSelected()
{
	if(!HasSelected())
		return;
	CListIteratorOfListOfNaDbObject listIterD(m_display);
	CListIteratorOfListOfNaDbObject listIterSel(m_select);
	NaDbObject* eO, *sO;
	for(listIterSel.Init(); listIterSel.More(); listIterSel.Next())
	{
		sO = listIterSel.Current();
		for(listIterD.Init(); listIterD.More(); listIterD.Next())
		{
			eO = listIterD.Current();
			if(eO->GetObjID() == sO->GetObjID())
				break;
		}
		delete m_display->Remove(eO);
	}
	EmptySelection();
	m_viewBox.SetLimits(-1,1,-1,1,-1,1);
	for(listIterD.Init(); listIterD.More(); listIterD.Next())
		m_viewBox.AddBox(listIterD.Current()->GetBoundingBox());
}

void NaGsDisplayContext::Render(const GsDisplayMode& mode)
{
	if(IsEmpty())
		return;

	NaDbObject* pDbObj;

	// Initialize the names stack
	glInitNames();
	glPushName(0);

	CListIteratorOfListOfNaDbObject listIter(m_display);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		pDbObj = listIter.Current();
		if(pDbObj)
		{
			glLoadName(pDbObj->GetObjID());
//!
//pDbObj->SetColor(m_nRed, m_nGreen, m_nBlue);
			pDbObj->Display(mode);
		}
	}

	listIter.SetList(m_select);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		pDbObj = listIter.Current();
		if(pDbObj)
			pDbObj->Hilight(mode);
	}
}

bool NaGsDisplayContext::Select(NaGsView* aView, const int& x, const int& y)
{
	bool res = false;
	NaDbObject* pDbObj = 0;
	unsigned long int id = aView->ProcessSelection(x, y, m_mouseSensitivity);
	if(id)
		res = true;
	else
	{
		EmptySelection();
		return false;
	}

	CListIteratorOfListOfNaDbObject listIter(m_display);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		pDbObj = listIter.Current();
		if(pDbObj)
		{
			if(id == pDbObj->GetObjID())
			{
				if(!IsSelected(pDbObj))
				{
					m_select->Clear();
					AddToSelection(pDbObj);
				}
				else
					RemoveSelection(pDbObj);
			}
		}
	}
	return res;
}

bool NaGsDisplayContext::MultiSelect(NaGsView* aView, const int& x, const int& y)
{
	bool res = false;
	NaDbObject* pDbObj = 0;
	unsigned long int id = aView->ProcessSelection(x, y, m_mouseSensitivity);
	if(id)
		res = true;
	CListIteratorOfListOfNaDbObject listIter(m_display);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		pDbObj = listIter.Current();
		if(pDbObj)
		{
			if(id == pDbObj->GetObjID())
			{
				if(!IsSelected(pDbObj))
					AddToSelection(pDbObj);
				else
					RemoveSelection(pDbObj);
			}
		}
	}
	return res;
}

bool NaGsDisplayContext::SweepSelect(NaGsView* aView, const CRect& swRect)
{
	bool res = false;
	NaDbObject* pDbObj = 0;
	unsigned long int *id = new unsigned long int[100];
	int no_of_objs = aView->ProcessSweepSelection(swRect, id);
	if(no_of_objs)
		res = true;
	CListIteratorOfListOfNaDbObject listIter(m_display);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		pDbObj = listIter.Current();
		if(pDbObj)
		{
			for(int i = 0; i < no_of_objs; i++)
			{
				if(id[i] == pDbObj->GetObjID())
					AddToSelection(pDbObj);
			}
		}
	}
	delete [] id;
	return res;
}

//선택한 포인트의 위치에 해당하는 삼각형 정보를 리턴한다.
void NaGsDisplayContext::SelectTriangle(NaGsView* aView, NaGePoint3D& pt)
{
	NaDbObject* pDbObj = 0;
	CListIteratorOfListOfNaDbObject listIter(m_display);
	for (listIter.Init(); listIter.More(); listIter.Next())
	{
		pDbObj = listIter.Current();
		if (pDbObj->GLObjType()==DbObjectType::GLTEXTURE)
		{
			m_selectRGBA = 0L;
			((NaDbTexture*)pDbObj)->GetRGBfromVertex(pt, m_selectRGBA);
		}
	}
}

bool NaGsDisplayContext::IsEmpty() const
{
	return (m_display->IsEmpty() && m_erase->IsEmpty());
}

bool NaGsDisplayContext::IsDisplayed(const NaDbObject* pDbObj) const
{
	if(pDbObj == NULL)
		return false;
	CListIteratorOfListOfNaDbObject li(m_display);
	return li.IsFound(pDbObj);
}

bool NaGsDisplayContext::IsErased(const NaDbObject* pDbObj) const
{
	if(pDbObj == NULL)
		return false;
	CListIteratorOfListOfNaDbObject li(m_erase);
	return li.IsFound(pDbObj);
}

bool NaGsDisplayContext::IsSelected(const NaDbObject* pDbObj) const
{
	bool b = false;
	if(pDbObj == NULL)
		return false;
	CListIteratorOfListOfNaDbObject li(m_select);
	for(li.Init(); li.More(); li.Next())
	{
		if(pDbObj->GetObjID() == li.Current()->GetObjID())
		{
			b = true;
			break;
		}
	}
	return b;
}

bool NaGsDisplayContext::IsAllDisplayed() const
{
	return m_erase->IsEmpty();
}

bool NaGsDisplayContext::IsAllErased() const
{
	return m_display->IsEmpty();
}

bool NaGsDisplayContext::HasSelected() const
{
	return !m_select->IsEmpty();
}

void NaGsDisplayContext::InitSelected() const
{
	m_selListIter.Init();
}

bool NaGsDisplayContext::MoreSelected() const
{
	return m_selListIter.More();
}

void NaGsDisplayContext::NextSelected() const
{
	m_selListIter.Next();
}

NaDbObject* NaGsDisplayContext::CurrentSelected() const
{
	NaDbObject* sO = m_selListIter.Current();
	NaDbObject* pDbObj = 0;
	CListIteratorOfListOfNaDbObject listIter(m_display);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		if(sO->GetObjID() == listIter.Current()->GetObjID())
		{
			pDbObj = listIter.Current();
			break;
		}
	}
	return pDbObj;
}

//Private
void NaGsDisplayContext::AddToSelection(NaDbObject* pDbObj)
{
	m_select->Append(pDbObj->Copy());
}

void NaGsDisplayContext::RemoveSelection(NaDbObject* pDbObj)
{
	CListIteratorOfListOfNaDbObject listIter(m_select);
	for(listIter.Init(); listIter.More(); listIter.Next())
	{
		if(pDbObj->GetObjID() == listIter.Current()->GetObjID())
		{
			/*delete*/ m_select->Remove(listIter.Current());
			break;
		}
	}
}

void NaGsDisplayContext::EmptySelection()
{
	if(!m_select->IsEmpty())
		m_select->Clear();
}
