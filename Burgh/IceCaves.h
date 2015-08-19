
#pragma once

#include "Utils.h"
#include "Engine.h"
#include "PlayerControl.h"

#include "d3dx9.h"
#include "StartMenu.h"
#include "GuiLoadGame.h"
#include "ScreenRes.h"
#include "2dcamera.h"

#include "viewport2.h"
#include "Player.h"
#include "Dozer.h"
#include "Map.h"
#include "background.h"

#include "fps.h"
#include "StatDisplay.h"
#include "FileHandler.h"
#include "FindFiles.h"

#include "cpu.h"


const TString dataPath = "data\\";
const TString playerPath = "data\\players\\";
const TString gameDataFileName = "data\\g00.BIN";
const TString fileExt = ".BIN";

class IceCaves : public TGame
{
public:
	IceCaves(HINSTANCE hInstance, WCHAR* winCaption, D3DDEVTYPE devType, DWORD requestedVP, KBControl* kb);
	~IceCaves();

	 HRESULT CreateSprites();
	 HRESULT CreateFonts(UINT index, INT height = 16, UINT style = FW_NORMAL, WCHAR* name = L"Tahoma");
	 virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam)override;
	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void updateScene(float dt);
	void drawScene();
	void buildFX();
	void HandleGameState();
	void SetVSync(bool val)override;
	virtual void ResumeGame()override;
	virtual void LoadGame(TString name)override;
	virtual void LoadPlayerListBox( GuiListBox* lb)override;
	virtual void LoadPlayer(TString ID)override;
	virtual void FillPlayerListBoxDisplayPanel(TString ID, class GuiDisplayPanel* dPanel)override;
	virtual void CreateNewPlayer(TString name)override;
	void GetCurrentScreenResolution()
	{
		Resolutions.GetCurrentScreenResolution(CurrScreenDesc);
	}
	virtual void SetOptions(bool vs, bool fs)override;
	virtual void GetOptions(bool& vs, bool& fs)override;
	void SaveCurrentPlayerFile();

	void buildBackGround();
	void buildStatDisplay();
	void getWorldPickingRay(D3DXVECTOR3& originW, D3DXVECTOR3& dirW);

private:
	float mTime;
	GuiState* pState = NULL;
	PlayerControl *playerControl = NULL;
	
	ScreenRes Resolutions;
	GuiWindow* pWindow1 = NULL;
	// Camera fixed to ground or can fly?
	bool mFreeCamera;
	Camera cam;
	//TViewport vp;
	TTileMap* pCurrMap = NULL;
	Player* player;
	Dozer **pDozer;

	// Default texture if no texture present for subset.
	//IDirect3DTexture9* mWhiteTex = NULL;  <--Not sure if this was accidentally deleted during merge
	Viewport TPort;
	BackGround* bkGround;
	ScreenRes::DisplayResDesc CurrScreenDesc;
	Fps Frames;
	StatDisplay* statDisplay = NULL;
	FileHandler fileHandler;
	FileFinder  fileFinder;
	CpuClass Cpu;

	// I think these got deleted during merge also
	//bool tripVSync = false;
	//bool doVSync = false;

};
