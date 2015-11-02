// NAKCorePropPage.cpp : Implementation of the CNAKCorePropPage property page class.

#include "stdafx.h"
#include "NAKCore.h"
#include "NAKCorePropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CNAKCorePropPage, COlePropertyPage)

// Message map

BEGIN_MESSAGE_MAP(CNAKCorePropPage, COlePropertyPage)
END_MESSAGE_MAP()

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CNAKCorePropPage, "NAKCORE.NAKCorePropPage.1",
	0x9578425a, 0x810e, 0x433d, 0xa6, 0x87, 0xa6, 0xe4, 0xda, 0x9e, 0xbf, 0x2a)

// CNAKCorePropPage::CNAKCorePropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CNAKCorePropPage

BOOL CNAKCorePropPage::CNAKCorePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_NAKCORE_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CNAKCorePropPage::CNAKCorePropPage - Constructor

CNAKCorePropPage::CNAKCorePropPage() :
	COlePropertyPage(IDD, IDS_NAKCORE_PPG_CAPTION)
{
}

// CNAKCorePropPage::DoDataExchange - Moves data between page and properties

void CNAKCorePropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CNAKCorePropPage message handlers
