#include "stdafx.h"
#include "Direct2DWnd.h"

#pragma comment(lib, "D2d1.lib")

HRESULT CDirect2DWnd::Create( LPCTSTR windowTitle )
{
	CHECK( D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory ) );
	HWND wnd = __super::Create( nullptr, nullptr, windowTitle );
	if( nullptr == wnd )
		return HRESULT_FROM_WIN32( GetLastError() );
	ShowWindow( SW_SHOW );
	return S_OK;
}

LRESULT CDirect2DWnd::OnSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if( m_pRenderTarget )
	{
		CSize size( (DWORD)lParam );
		// Note: This method can fail, but it's okay to ignore the error here, because the error will be returned again the next time EndDraw is called.
		m_pRenderTarget->Resize( D2D1::SizeU( size.cx, size.cy ) );
	}
	return 0;
}

HRESULT CDirect2DWnd::CreateRenderTarget()
{
	if( m_pRenderTarget )
		return S_FALSE;

	CRect rc;
	GetClientRect( &rc );

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top
	);

	// Create a Direct2D render target.
	CHECK( m_pDirect2dFactory->CreateHwndRenderTarget( D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties( m_hWnd, size ), &m_pRenderTarget ) );
	return S_OK;
}

// Same as CHECK(), but if the code is D2DERR_RECREATE_TARGET, discards resources and returns S_OK
#define CHECK_RECREATE( hr ) { const HRESULT __hr = ( hr ); if( FAILED( __hr ) ) { if( D2DERR_RECREATE_TARGET == __hr ) { DiscardResourcesAndRT(); return S_OK; } return __hr; } }

HRESULT CDirect2DWnd::OnRender()
{
	HRESULT hr = CreateRenderTarget();
	CHECK_RECREATE( hr );
	if( hr != S_FALSE )
	{
		hr = CreateResources();
		if( FAILED( hr ) )
		{
			m_pRenderTarget = nullptr;
			CHECK_RECREATE( hr );
			return hr;
		}
	}

	m_pRenderTarget->BeginDraw();

	m_pRenderTarget->SetTransform( D2D1::Matrix3x2F::Identity() );

	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

	Draw( rtSize );

	CHECK_RECREATE( m_pRenderTarget->EndDraw() );

	return S_OK;
}

void CDirect2DWnd::RunMessageLoop()
{
	MSG msg;
	while( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}