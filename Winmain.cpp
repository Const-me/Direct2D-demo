#include "stdafx.h"
#include "DemoApp.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	if( FAILED( CoInitialize( NULL ) ) )
		return 0;

	CDemoApp app;
	if( SUCCEEDED( app.Create( L"Direct2D Demo" ) ) )
	{
		app.RunMessageLoop();
	}

	CoUninitialize();
	return 0;
}