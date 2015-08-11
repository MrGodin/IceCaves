
#pragma once
#include "Utils.h"
#include "keyboardController.h"
#include "PlayerControl.h"
#include "GuiState.h"
class TGame
{
protected:
	KBControl* pController = NULL;
	ID3DXSprite* pGuiSprite = NULL;
	ID3DXSprite* pMapSprite = NULL;
	ID3DXFont** pFont = NULL;
	GuiCore GameState;
public:
	static class TGame* gd3dApp;
	static IDirect3DDevice9* gd3dDevice;
public:
	TGame(HINSTANCE hInstance, WCHAR* winCaption, D3DDEVTYPE devType, DWORD requestedVP,KBControl* kb );
	virtual ~TGame();

	HINSTANCE getAppInst();
	HWND      getMainWnd();

	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.
	virtual void SetVSync(bool val){}
	virtual bool checkDeviceCaps()     { return true; }
	virtual void onLostDevice()        {}
	virtual void onResetDevice()       {}
	virtual void updateScene(float dt) {}
	virtual void drawScene()           {}
	virtual HRESULT CreateSprites(){ return 0; };
	virtual HRESULT CreateFonts(UINT index, INT height = 16, UINT style = FW_NORMAL, WCHAR* name = L"Tahoma"){
		return 0;
	};

	

	
	virtual void initMainWindow();
	virtual void initDirect3D();
	virtual int run();
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam){
		return 0;
	};

	void enableFullScreenMode(bool enable);
	bool isDeviceLost();

protected:
	// Derived client class can modify these data members in the constructor to 
	// customize the application.  
	WCHAR* mMainWndCaption;
	D3DDEVTYPE  mDevType;
	DWORD       mRequestedVP;

	
	HINSTANCE             mhAppInst;
	HWND                  mhMainWnd;
	IDirect3D9*           md3dObject;
	bool                  mAppPaused;
	D3DPRESENT_PARAMETERS md3dPP;
};

// Globals for convenient access.
 