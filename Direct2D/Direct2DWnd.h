#pragma once

// An abstract base class for a Direct2D-painted window.
// Most parts are from there: https://msdn.microsoft.com/en-us/library/windows/desktop/dd370994(v=vs.85).aspx
class CDirect2DWnd:
	public CWindowImpl<CDirect2DWnd, CWindow, CFrameWinTraits>
{
public:
	CDirect2DWnd() = default;
	virtual ~CDirect2DWnd() = default;

	// Declare the windows class
	DECLARE_WND_CLASS_EX( L"CDirect2DWnd", CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, -1 );

	// This ATL message map macros are much more usable compared to the old-school Win32 switch/case stuff.
	BEGIN_MSG_MAP( CDirect2DWnd )
		MESSAGE_HANDLER( WM_SIZE, OnSize )
		MESSAGE_HANDLER( WM_PAINT, OnPaint )
		MESSAGE_HANDLER( WM_DISPLAYCHANGE, OnDisplayChange );
	END_MSG_MAP()

	// Create the window, initialize D2D
	HRESULT Create( LPCTSTR windowTitle );

	void RunMessageLoop();

protected:
	// Override this to create your D2D resources. When this is called, you can assume renderTarget is alive and well.
	virtual HRESULT CreateResources() { return S_FALSE; }

	// Override this to destroy your D2D resources.
	virtual void DiscardResources() {}

	// Override this to actually draw stuff. When this is called, you can assume renderTarget is alive and well.
	virtual void Draw( const D2D_SIZE_F &rtSize ) = 0;

	inline ID2D1HwndRenderTarget* GetRenderTarget() const
	{
		return m_pRenderTarget;
	}
	// Utility method to get ID2D1HwndRenderTarget* fron your derived class.
	__declspec( property( get = GetRenderTarget ) ) ID2D1HwndRenderTarget* renderTarget;

	// The hidden parts of the implementation
private:
	LRESULT OnSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	inline LRESULT OnPaint( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
	{
		OnRender();
		ValidateRect( nullptr );
		return 0;
	}
	inline LRESULT OnDisplayChange( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
	{
		InvalidateRect( nullptr );
		return 0;
	}

	CComPtr<ID2D1Factory> m_pDirect2dFactory;
	CComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;

	// Create the render target. If already created, return S_FALSE and do nothing.
	HRESULT CreateRenderTarget();

	void DiscardResourcesAndRT()
	{
		DiscardResources();
		m_pRenderTarget = nullptr;
	}

	HRESULT OnRender();
};