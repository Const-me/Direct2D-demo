#pragma once
#include "Direct2D/Direct2DWnd.h"

class CDemoApp: public CDirect2DWnd
{
public:
	CDemoApp() = default;
	virtual ~CDemoApp() = default;

	BEGIN_MSG_MAP( CDemoApp )
		MESSAGE_HANDLER( WM_DESTROY, OnDestoy )
		CHAIN_MSG_MAP( CDirect2DWnd );
	END_MSG_MAP()

protected:
	HRESULT CreateResources() override;
	void DiscardResources() override;
	void Draw( const D2D_SIZE_F &rtSize ) override;

private:
	CComPtr<ID2D1SolidColorBrush> m_pLightSlateGrayBrush;
	CComPtr<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;

	inline LRESULT OnDestoy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
	{
		// Quit running the message loop when this window is destroyed.
		::PostQuitMessage( 0 );
		return 1;
	}
};