#pragma once

// NAKCorePropPage.h : Declaration of the CNAKCorePropPage property page class.


// CNAKCorePropPage : See NAKCorePropPage.cpp for implementation.

class CNAKCorePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CNAKCorePropPage)
	DECLARE_OLECREATE_EX(CNAKCorePropPage)

// Constructor
public:
	CNAKCorePropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_NAKCORE };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

