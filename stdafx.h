#pragma once
#include "targetver.h"

// Windows and D2D
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <d2d1.h>

// ATL
#include <atlbase.h>
#include <atlwin.h>
#include <atltypes.h>

// Misc.
#ifdef DEBUG
#define CHECK( hr ) { const HRESULT __hr = ( hr ); if( FAILED( __hr ) ) { __debugbreak(); return __hr; } }
#else
#define CHECK( hr ) { const HRESULT __hr = ( hr ); if( FAILED( __hr ) ) return __hr; }
#endif