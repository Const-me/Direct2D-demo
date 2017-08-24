#include "stdafx.h"
#include "DemoApp.h"

HRESULT CDemoApp::CreateResources()
{
	// Create a gray brush.
	CHECK( renderTarget->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::LightSlateGray ), &m_pLightSlateGrayBrush ) );

	// Create a blue brush.
	CHECK( renderTarget->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::CornflowerBlue ), &m_pCornflowerBlueBrush ) );

	return S_OK;
}

void CDemoApp::DiscardResources()
{
	m_pLightSlateGrayBrush = nullptr;
	m_pCornflowerBlueBrush = nullptr;
}

void CDemoApp::Draw( const D2D_SIZE_F &rtSize )
{
	renderTarget->Clear( D2D1::ColorF( D2D1::ColorF::White ) );

	// Draw a grid background.
	int width = static_cast<int>( rtSize.width );
	int height = static_cast<int>( rtSize.height );

	for( int x = 0; x < width; x += 10 )
	{
		renderTarget->DrawLine(
			D2D1::Point2F( static_cast<FLOAT>( x ), 0.0f ),
			D2D1::Point2F( static_cast<FLOAT>( x ), rtSize.height ),
			m_pLightSlateGrayBrush,
			0.5f
		);
	}

	for( int y = 0; y < height; y += 10 )
	{
		renderTarget->DrawLine(
			D2D1::Point2F( 0.0f, static_cast<FLOAT>( y ) ),
			D2D1::Point2F( rtSize.width, static_cast<FLOAT>( y ) ),
			m_pLightSlateGrayBrush,
			0.5f
		);
	}

	// Draw two rectangles.
	D2D1_RECT_F rectangle1 = D2D1::RectF(
		rtSize.width / 2 - 50.0f,
		rtSize.height / 2 - 50.0f,
		rtSize.width / 2 + 50.0f,
		rtSize.height / 2 + 50.0f
	);

	D2D1_RECT_F rectangle2 = D2D1::RectF(
		rtSize.width / 2 - 100.0f,
		rtSize.height / 2 - 100.0f,
		rtSize.width / 2 + 100.0f,
		rtSize.height / 2 + 100.0f
	);

	// Draw a filled rectangle.
	renderTarget->FillRectangle( &rectangle1, m_pLightSlateGrayBrush );


	// Draw the outline of a rectangle.
	renderTarget->DrawRectangle( &rectangle2, m_pCornflowerBlueBrush );
}