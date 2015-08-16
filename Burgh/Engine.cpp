
#include "Engine.h"
#include "d3d9.h"

 TGame* TGame::gd3dApp = NULL;
 IDirect3DDevice9* TGame::gd3dDevice = NULL;

//TGame* gd3dApp = NULL;
//IDirect3DDevice9* g_pd3dDevice = NULL;
LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Don't start processing messages until the application has been created.
	if (TGame::gd3dApp != 0)
		return TGame::gd3dApp->msgProc(msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

TGame::TGame(HINSTANCE hInstance, WCHAR* winCaption, D3DDEVTYPE devType, DWORD requestedVP,KBControl* kb)
{
	mMainWndCaption = winCaption;
	mDevType = devType;
	mRequestedVP = requestedVP;

	mhAppInst = hInstance;
	mhMainWnd = 0;
	md3dObject = 0;
	mAppPaused = false;
	ZeroMemory(&md3dPP, sizeof(md3dPP));
	pController = kb;
	initMainWindow();
	initDirect3D();
	pFont = new ID3DXFont*[4];
}

TGame::~TGame()
{
	
	SAFE_RELEASE(pGuiSprite);
	SAFE_RELEASE(pMapSprite);
	SAFE_DELETE(pController);
	for (int c = 0; c < 4; c++)
		SAFE_RELEASE(pFont[c]);

	SAFE_DELETE_ARRAY(pFont);

	SAFE_RELEASE(md3dObject);
	SAFE_RELEASE(gd3dDevice);
}

HINSTANCE TGame::getAppInst()
{
	return mhAppInst;
}

HWND TGame::getMainWnd()
{
	return mhMainWnd;
}

void TGame::initMainWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mhAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"D3DWndClassName";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		PostQuitMessage(0);
	}

	// Default to a window with a client area rectangle of 800x600.

	RECT R = { 0, 0, 1280, 768 };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	GameState.backBufferHeight = 768;
	GameState.backBufferWidth = 1280;
	mhMainWnd = CreateWindow(L"D3DWndClassName", mMainWndCaption,
		WS_OVERLAPPEDWINDOW, 0, 0, R.right, R.bottom,
		0, 0, mhAppInst, 0);

	if (!mhMainWnd)
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(mhMainWnd, SW_MAXIMIZE);// SW_SHOW);
	UpdateWindow(mhMainWnd);
}

void TGame::initDirect3D()
{
	// Step 1: Create the IDirect3D9 object.

	md3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (!md3dObject)
	{
		MessageBox(0, L"Direct3DCreate9 FAILED", 0, 0);
		PostQuitMessage(0);
	}


	// Step 2: Verify hardware support for specified formats in windowed and full screen modes.

	D3DDISPLAYMODE mode;
	
	md3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);

	HR(md3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, mDevType, mode.Format, mode.Format, true));
	HR(md3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, mDevType, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false));

	// Step 3: Check for requested vertex processing and pure device.

	D3DCAPS9 caps;
	HR(md3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, mDevType, &caps));

	DWORD devBehaviorFlags = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		devBehaviorFlags |= mRequestedVP;
	else
		devBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// If pure device and HW T&L supported
	if (caps.DevCaps & D3DDEVCAPS_PUREDEVICE &&
		devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		devBehaviorFlags |= D3DCREATE_PUREDEVICE;

	// Step 4: Fill out the D3DPRESENT_PARAMETERS structure.

	md3dPP.BackBufferWidth = 0;
	md3dPP.BackBufferHeight = 0;
	md3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	md3dPP.BackBufferCount = 1;
	md3dPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	md3dPP.MultiSampleQuality = 0;
	md3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	md3dPP.hDeviceWindow = mhMainWnd;
	md3dPP.Windowed = true;
	md3dPP.EnableAutoDepthStencil = true;
	md3dPP.AutoDepthStencilFormat = D3DFMT_D16;// D3DFMT_D24S8;
	md3dPP.Flags = 0;
	md3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;// D3DPRESENT_RATE_DEFAULT;
	md3dPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //D3DPRESENT_INTERVAL_IMMEDIATE;
	
	// Step 5: Create the device.

	if(FAILED(md3dObject->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		mDevType,           // device type
		mhMainWnd,          // window associated with device
		devBehaviorFlags,   // vertex processing
		&md3dPP,            // present parameters
		&TGame::gd3dDevice)))
		{
			int x = 0;
			
	    };      // return created device
	
	
}

int TGame::run()
{
	MSG  msg;
	msg.message = WM_NULL;

	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			// If the application is paused then free some CPU cycles to other 
			// applications and then continue on to the next frame.
			if (mAppPaused)
			{
				Sleep(20);
				continue;
			}

			if (!isDeviceLost())
			{
				__int64 currTimeStamp = 0;
				QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
				float dt = (currTimeStamp - prevTimeStamp)*secsPerCnt;

				updateScene(dt);
				drawScene();

				// Prepare for next iteration: The current time stamp becomes
				// the previous time stamp for the next iteration.
				prevTimeStamp = currTimeStamp;
			}
		}
	}
	return (int)msg.wParam;
}



void TGame::enableFullScreenMode(bool enable)
{
	// Switch to fullscreen mode.
	if (enable)
	{
		// Are we already in fullscreen mode?
		if (!md3dPP.Windowed)
			return;

		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		md3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
		md3dPP.BackBufferWidth = width;
		md3dPP.BackBufferHeight = height;
		md3dPP.Windowed = false;
		
		// Change the window style to a more fullscreen friendly style.
		SetWindowLongPtr(mhMainWnd, GWL_STYLE, WS_POPUP);

		// If we call SetWindowLongPtr, MSDN states that we need to call
		// SetWindowPos for the change to take effect.  In addition, we 
		// need to call this function anyway to update the window dimensions.
		SetWindowPos(mhMainWnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	// Switch to windowed mode.
	else
	{
		// Are we already in windowed mode?
		if (md3dPP.Windowed)
			return;
		
		RECT R = { 0, 0, (long)GameState.backBufferWidth, (long)GameState.backBufferHeight };// 800, 600 };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		md3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
		md3dPP.BackBufferWidth = GameState.backBufferWidth;
		md3dPP.BackBufferHeight = GameState.backBufferHeight;
		
		md3dPP.Windowed = true;
		
		// Change the window style to a more windowed friendly style.
		SetWindowLongPtr(mhMainWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		// If we call SetWindowLongPtr, MSDN states that we need to call
		// SetWindowPos for the change to take effect.  In addition, we 
		// need to call this function anyway to update the window dimensions.
		SetWindowPos(mhMainWnd, HWND_TOP, 0, 0, R.right, R.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
	}

	// Reset the device with the changes.
	onLostDevice();
	gd3dDevice->Reset(&md3dPP);
	onResetDevice();
}

bool TGame::isDeviceLost()
{
	// Get the state of the graphics device.
	HRESULT hr = gd3dDevice->TestCooperativeLevel();

	// If the device is lost and cannot be reset yet then
	// sleep for a bit and we'll try again on the next 
	// message loop cycle.
	if (hr == D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	// Driver error, exit.
	else if (hr == D3DERR_DRIVERINTERNALERROR)
	{
		MessageBox(0, L"Internal Driver Error...Exiting", 0, 0);
		PostQuitMessage(0);
		return true;
	}
	// The device is lost but we can reset and restore it.
	else if (hr == D3DERR_DEVICENOTRESET)
	{
		onLostDevice();
		if (FAILED(gd3dDevice->Reset(&md3dPP)))
			return true;

		onResetDevice();
		return false;
	}
	else
		return false;
}