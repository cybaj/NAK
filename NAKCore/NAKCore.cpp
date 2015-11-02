// NAKCore.cpp : Implementation of CNAKCoreApp and DLL registration.

#include "stdafx.h"
#include "NAKCore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CNAKCoreApp theApp;

const GUID CDECL _tlid = { 0xAACB2826, 0xE956, 0x43E2, { 0xBA, 0xB1, 0x6, 0xDC, 0xBA, 0x87, 0x6E, 0xF8 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CNAKCoreApp::InitInstance - DLL initialization

BOOL CNAKCoreApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CNAKCoreApp::ExitInstance - DLL termination

int CNAKCoreApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
