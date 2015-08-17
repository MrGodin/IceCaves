
#include "IceCaves.h"
#include "GuiExitMenu.h"
#include "GuiDisplayPanel.h"
#include "LevelHandler.h"

IceCaves::IceCaves(HINSTANCE hInstance, WCHAR* winCaption, D3DDEVTYPE devType, DWORD requestedVP, KBControl* kb)
	: TGame(hInstance, winCaption, devType, requestedVP, kb),
	TPort( {0, 0, 800, 600 }),
	cam(TPort)
{
	playerControl = (PlayerControl*)pController;
	if (!checkDeviceCaps())
	{
		MessageBox(0, L"checkDeviceCaps() Failed", 0, 0);
		PostQuitMessage(0);
	}
	
	if (!fileHandler.LoadGameFile(gameDataFileName))
	{
		
		
	}
	if (gd3dDevice)
	{
		CreateSprites();
		CreateFonts(0);
		CreateFonts(1,16,FW_BOLD,L"Tahoma");
		CreateFonts(2,22,FW_NORMAL,L"Tahoma");
		CreateFonts(3);
	}
	GameObject::SetDrawTools(gd3dDevice, pMapSprite);
	GuiState::SetArrayFonts(pFont[0]);
	GuiFrame::SetDrawTools(TGame::gd3dDevice, pGuiSprite);
	GameState.pWindow = new GuiStartMenu(&GameState);
	GameState.game_state = gsPaused;

	pCurrMap = new TTileMap(TString("media\\levelsprite2.png"), pLevel2String, iLevel2Width, iLevel2Height, 64, 64);
	pCurrMap->Create(pLevel2String,0,0);
	cam.SetBindingBox(pCurrMap->GetBoundary());
	player = new Player(&cam,32, 32, { 100.0f, 300.0f });
	player->SetImages(pCurrMap->SpriteSheet());
	player->SetImageindex(23);
	TPort.SetDevice(gd3dDevice);
	TPort.ResetCenter(GameState.backBufferWidth, GameState.backBufferHeight, 1024, 600);
	Cpu.Initialize();
	buildBackGround();
	buildStatDisplay();
	onResetDevice();
	if (fileHandler.GameData()->vsync)
		SetVSync(true);
	else
		SetVSync(false);

	if (fileHandler.GameData()->fullscreen)
	    enableFullScreenMode(true);
}

IceCaves::~IceCaves()
{
	Cpu.Shutdown();
	if (player)
		SaveCurrentPlayerFile();

	SAFE_DELETE(GameState.pWindow);
	SAFE_DELETE(pCurrMap);
	SAFE_DELETE(player);
	SAFE_DELETE(bkGround);
	SAFE_DELETE(statDisplay);
	fileHandler.WriteGameFile(gameDataFileName);

	///DestroyAllVertexDeclarations();
}
LRESULT IceCaves::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Is the application in a minimized or maximized state?
	static bool minOrMaxed = false;
	
	pController->MsgProc(0, msg, wParam, lParam);
	
	if (GameState.game_state != gsRunning && GameState.pWindow != NULL)
	{
		switch (GameState.pWindow->msgProcState(getMainWnd(), msg, wParam, lParam))
		{
		case KILL_APP:
			DestroyWindow(mhMainWnd);
			return 0;
		case CB_VSYNC:
		{
			static bool trip = true;
			enableFullScreenMode(trip);
			//SetVSync(trip);
			trip = !trip;

		}
		default:
			break;
		}
		
	}
	RECT clientRect = { 0, 0, 0, 0 };
	switch (msg)
	{
	
		// WM_ACTIVE is sent when the window is activated or deactivated.
		// We pause the game when the main window is deactivated and 
		// unpause it when it becomes active.
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
			mAppPaused = true;
		else
			mAppPaused = false;
		return 0;


		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		if (gd3dDevice)
		{
			md3dPP.BackBufferWidth = LOWORD(lParam);
			md3dPP.BackBufferHeight = HIWORD(lParam);
			

			if (wParam == SIZE_MINIMIZED)
			{
				mAppPaused = true;
				minOrMaxed = true;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				mAppPaused = false;
				minOrMaxed = true;
				onLostDevice();
				HR(gd3dDevice->Reset(&md3dPP));
				onResetDevice();
			}
			// Restored is any resize that is not a minimize or maximize.
			// For example, restoring the window to its default size
			// after a minimize or maximize, or from dragging the resize
			// bars.
			else if (wParam == SIZE_RESTORED)
			{
				mAppPaused = false;

				// Are we restoring from a mimimized or maximized state, 
				// and are in windowed mode?  Do not execute this code if 
				// we are restoring to full screen mode.
				if (minOrMaxed && md3dPP.Windowed)
				{
					onLostDevice();
					HR(gd3dDevice->Reset(&md3dPP));
					onResetDevice();
				}
				else
				{
					// No, which implies the user is resizing by dragging
					// the resize bars.  However, we do not reset the device
					// here because as the user continuously drags the resize
					// bars, a stream of WM_SIZE messages is sent to the window,
					// and it would be pointless (and slow) to reset for each
					// WM_SIZE message received from dragging the resize bars.
					// So instead, we reset after the user is done resizing the
					// window and releases the resize bars, which sends a
					// WM_EXITSIZEMOVE message.
				}
				minOrMaxed = false;
			}
		}
		return 0;


		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		GetClientRect(mhMainWnd, &clientRect);
		md3dPP.BackBufferWidth = clientRect.right;
		md3dPP.BackBufferHeight = clientRect.bottom;
		
		onLostDevice();
		HR(gd3dDevice->Reset(&md3dPP));
		onResetDevice();

		return 0;

		// WM_CLOSE is sent when the user presses the 'X' button in the
		// caption bar menu.
	case WM_CLOSE:
	{
		SAFE_DELETE(GameState.pWindow);
		GameState.game_state = gsPaused;
		GameState.pWindow = new GuiExitMenu(&GameState);
		return 0;
	}
		//DestroyWindow(mhMainWnd);


		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
	{
		
	}
	break;
	case WM_LBUTTONDOWN:
	{
		
	}
		break;
		
	case WM_LBUTTONUP:
		GuiControl::SetMouseCapture(false);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)// escape key
		{
			
			if (!GameState.pWindow)
			{
				GameState.pWindow = new GuiStartMenu(&GameState);

			}
			GameState.game_state = gsPaused;
		}
		else if (wParam == 'F')
			enableFullScreenMode(true);
		return 0;
	}
	return DefWindowProc(mhMainWnd, msg, wParam, lParam);
}
HRESULT IceCaves::CreateFonts(UINT index, INT height, UINT style, WCHAR* name )
{
	return D3DXCreateFont(TGame::gd3dDevice, height, 0, style, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		name, &pFont[index]);
	
};
HRESULT IceCaves::CreateSprites()
{
	
	D3DXCreateSprite(gd3dDevice, &pGuiSprite);
	D3DXCreateSprite(gd3dDevice, &pMapSprite);
	 return S_OK;
	
};

bool IceCaves::checkDeviceCaps()
{
	D3DCAPS9 caps;
	gd3dDevice->GetDeviceCaps(&caps);

	// Check for vertex shader version 2.0 support.
	if (caps.VertexShaderVersion < D3DVS_VERSION(2, 0))
		return false;

	// Check for pixel shader version 2.0 support.
	if (caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
		return false;

	return true;
}

void IceCaves::onLostDevice()
{
	if (pMapSprite)
		pMapSprite->OnLostDevice();
	if (pGuiSprite)
		pGuiSprite->OnLostDevice();

	if (pFont)
	{
		pFont[0]->OnLostDevice();
		pFont[1]->OnLostDevice();
		pFont[2]->OnLostDevice();
		pFont[3]->OnLostDevice();
	}
}

void IceCaves::onResetDevice()
{
	
	if (pMapSprite)
		pMapSprite->OnResetDevice();
	if (pGuiSprite)
		pGuiSprite->OnResetDevice();

	if (pFont)
	{
		pFont[0]->OnResetDevice();
		pFont[1]->OnResetDevice();
		pFont[2]->OnResetDevice();
		pFont[3]->OnResetDevice();
	}
	
	float w = (float)md3dPP.BackBufferWidth;
	float h = (float)md3dPP.BackBufferHeight;

	
	GameObject::SetDrawTools(gd3dDevice, pMapSprite);
	

	GameState.backBufferHeight = md3dPP.BackBufferHeight;
	GameState.backBufferWidth = md3dPP.BackBufferWidth;
	if (GameState.pWindow)
		GameState.pWindow->ReDraw();

	TPort.SetDevice(gd3dDevice);
	TPort.ResetCenter(GameState.backBufferWidth, GameState.backBufferHeight,1024, 600);
	pCurrMap->SetScreenWidthHeight( GameState.backBufferHeight - TPort.GetY(), GameState.backBufferWidth - TPort.GetX());
	cam.SetBindingBox(pCurrMap->GetBoundary());
	bkGround->Redraw(TPort.GetX()+2, TPort.GetY()+2, TPort.GetHeight()-4, TPort.GetWidth()-4);
	statDisplay->Resize(TPort.GetX() + 8, TPort.GetY() + (TPort.GetHeight() - (64 + 8)), TPort.GetWidth() - 16, 64);
	
}

void IceCaves::updateScene(float dt)
{
#ifdef M_DEBUG
	dt = 1.0f / 60.0f;
#endif
	Cpu.Frame();
	
	switch (GameState.game_state)
	{
		case gsRunning:
		{
			mTime += dt;
			playerControl->Poll(player);
			player->Update(dt);
			cam.SetPosition(player->GetPos().x, player->GetPos().y);
			pCurrMap->Update(cam, dt, TPort.GetX(), TPort.GetY());
			pCurrMap->DoCollision(player);
			pCurrMap->DoSupport(player);
			bkGround->Update(dt);
			statDisplay->Update(Frames.Update(dt),(float)Cpu.GetCpuPercentage(), player->GetPos(),mTime);
		}
		case gsPaused:
		{
			if (GameState.pWindow)
			{
				GameState.pWindow->Update();
						
			}
		}

	default:
		break;
	}

	
	
	
	
		
	

		
	
	
}

void IceCaves::drawScene()
{
	// Clear the backbuffer and depth buffer.
	HR(gd3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Color(255,0,0,0), 1.0f, 0));

	HR(gd3dDevice->BeginScene());

	HR(gd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	HR(gd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL));
	HR(gd3dDevice->SetRenderState(D3DRS_ALPHAREF, 150));
	HR(gd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false));
	
	
	
	
	if (pGuiSprite && GameState.game_state == gsPaused)
	{
		
		pGuiSprite->Begin(D3DXSPRITE_ALPHABLEND);
		bkGround->Rasterize();
		if (GameState.pWindow)
			  GameState.pWindow->Rasterize();
			
		pGuiSprite->End();
		
		
		
	}
	else if (GameState.game_state == gsRunning)
	{
		pGuiSprite->Begin(D3DXSPRITE_ALPHABLEND);
		  bkGround->Rasterize();
		pGuiSprite->End();

		pMapSprite->Begin(D3DXSPRITE_ALPHABLEND);
		 pCurrMap->Draw();
		 player->Rasterize();
		 pMapSprite->End();
		 pGuiSprite->Begin(D3DXSPRITE_ALPHABLEND);
		 statDisplay->Rasterize();
		pGuiSprite->End();
	}

	HR(gd3dDevice->EndScene());

	// Present the backbuffer.
	HR(gd3dDevice->Present(0, 0, 0, 0));
}

void IceCaves::HandleGameState()
{
	if (!GameState.pWindow)
		return;

	UINT Act = GameState.pWindow->Poll();
	switch (Act)
	{
	case KILL_APP:
		break;
	default:
		break;
	}
}
void IceCaves::buildFX()
{
	// Create the generic Light & Tex FX from a .fx file.
	/*
	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(gd3dDevice, L"DirLightTex.fx",
	0, 0, 0, 0, &mFX, &errors));
	if (errors)
	MessageBox(0, (WCHAR*)errors->GetBufferPointer(), 0, 0);

	// Obtain handles.
	mhTech = mFX->GetTechniqueByName("DirLightTexTech");
	mhWVP = mFX->GetParameterByName(0, "gWVP");
	mhWorldInvTrans = mFX->GetParameterByName(0, "gWorldInvTrans");
	mhMtrl = mFX->GetParameterByName(0, "gMtrl");
	mhLight = mFX->GetParameterByName(0, "gLight");
	mhEyePosW = mFX->GetParameterByName(0, "gEyePosW");
	mhWorld = mFX->GetParameterByName(0, "gWorld");
	mhTex = mFX->GetParameterByName(0, "gTex");
	mLight.dirW = { 0.0f, 32.0f, 1.0f };
	D3DXVec3Normalize(&mLight.dirW, &mLight.dirW);
	mLight.ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mLight.diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	mLight.spec = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	HR(mFX->SetValue(mhLight, &mLight, sizeof(DirLight)));

	// Create the grass FX from a .fx file.
	HR(D3DXCreateEffectFromFile(gd3dDevice, L"grass.fx",
	0, 0, 0, 0, &mGrassFX, &errors));
	if (errors)
	MessageBox(0, (WCHAR*)errors->GetBufferPointer(), 0, 0);

	// Obtain handles.
	mhGrassTech = mGrassFX->GetTechniqueByName("GrassTech");
	mhGrassViewProj = mGrassFX->GetParameterByName(0, "gViewProj");
	mhGrassTex = mGrassFX->GetParameterByName(0, "gTex");
	mhGrassTime = mGrassFX->GetParameterByName(0, "gTime");
	mhGrassEyePosW = mGrassFX->GetParameterByName(0, "gEyePosW");
	mhGrassDirToSunW = mGrassFX->GetParameterByName(0, "gDirToSunW");

	HR(mGrassFX->SetTechnique(mhGrassTech));
	HR(mGrassFX->SetTexture(mhGrassTex, mGrassTex));
	*/
}
void IceCaves::buildBackGround()
{
	GuiFrame::GuiFrameDesc desc;
	desc.baseColor = QVCWhite;
	bkGround = new BackGround(desc);
	bkGround->CreateTexture(L"media\\splash2.png");


};
void IceCaves::buildStatDisplay()
{
	GuiFrame::GuiFrameDesc desc;
	desc.width = TPort.GetWidth() - (22 * 2);
	desc.height = 64;
	desc.originX = abs((long)TPort.GetX()) + 64;
	desc.originY = ((TPort.GetY()+ 64) + TPort.GetHeight()) - (desc.height );
	desc.baseColor = QVCBlackTrans1;
	desc.innerBorderColor = desc.outerBorderColor = QVCBlue;
	statDisplay = new StatDisplay(desc);
	statDisplay->SetFont(pFont[3]);
	statDisplay->Create();
}

//===========================================
void IceCaves::SaveCurrentPlayerFile()
{
	playerFileData data = player->GetFileData();
	fileHandler.WritePlayerFile(data.filename, data);
}
void IceCaves::SetVSync(bool val)
{
	
	
	if (val)
		md3dPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE; 
	else
		md3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	onLostDevice();
	gd3dDevice->Reset(&md3dPP);
	onResetDevice();
	
}
void IceCaves::ResumeGame()
{
	SAFE_DELETE(GameState.pWindow);
	GameState.game_state = gsRunning;
}
void IceCaves::LoadGame(TString name)
{
	SAFE_DELETE(GameState.pWindow);
	GameState.game_state = gsRunning;
}

void IceCaves::LoadPlayerListBox(GuiListBox* lb)
{
	for (int c = 0; c < maxPlayersInFile; c++)
	{
		TString str = fileHandler.GameData()->games[c];
		if (str == TString("\0"))
			continue;

		lb->AddString(str);
		
	}
	lb->UpdateStrings(0);// set to top-most ie: index 0
}
void IceCaves::LoadPlayer(TString ID)
{
	TString filename = playerPath; filename += ID; filename += fileExt;
	playerFileData playerData;
	if (fileHandler.LoadPlayerFile(filename, playerData))
	{
		player->SetFileData(playerData);
		GameState.gameLoaded = true;
		ResumeGame();
	}
}
void IceCaves::FillPlayerListBoxDisplayPanel(TString ID, GuiDisplayPanel* dPanel)
{
	TString filename = playerPath; filename += ID; filename += fileExt;
	playerFileData playerData;

	if (fileHandler.LoadPlayerFile(filename, playerData))
	{

		TString str = "Level : "; str += TString(playerData.level);
		dPanel->SetDisplayText(str, 0, 0);
		str = "Tokens : "; str += TString(playerData.tokens);
		dPanel->SetDisplayText(str, 1, 0);
		str = "Shields : "; str += TString((float)playerData.shieldstrength);
		dPanel->SetDisplayText(str, 2, 0);
		str = "Traction : "; str += TString(playerData.traction);
		dPanel->SetDisplayText(str, 3, 0);
		str = "Thrust : "; str += TString(playerData.thrust);
		dPanel->SetDisplayText(str, 4, 0);
		str = "Speed : "; str += TString(playerData.speed);
		dPanel->SetDisplayText(str, 0, 1);
	}
}
void IceCaves::CreateNewPlayer(TString name)
{
	playerFileData playerdata;
	playerdata.shieldstrength = 100;
	playerdata.thrust = 0.0f;
	playerdata.tokens = 0;
	playerdata.traction = 0.989f;
	playerdata.accX = 2.0f;
	playerdata.accY = 2.0f;
	playerdata.speed = 4.0f;
	playerdata.posX = 100.0f;
	playerdata.posY = 300.0f;
	name.Trim();
	TString filename = playerPath; filename += name; filename += fileExt;
	sprintf_s(playerdata.filename, "%s", filename.c_str());

	LevelHandler lh;
	lh.GetLevel(1, playerdata.Level);

	fileHandler.WritePlayerFile(filename, playerdata);
	for (int c = 0; c < maxPlayersInFile; c++)
	{
		if (TString(fileHandler.GameData()->games[c]) == TString("\0"))
		{
			sprintf_s(fileHandler.GameData()->games[c], "%s", name.c_str());
			break;
		}
	}
	player->SetFileData(playerdata);
	fileHandler.WriteGameFile(gameDataFileName);
	SAFE_DELETE(GameState.pWindow);
	GameState.pWindow = new GuiLoadGame(&GameState);
}
void IceCaves::SetOptions(bool vs, bool fs)
{
	fileHandler.GameData()->fullscreen = fs;
	fileHandler.GameData()->vsync = vs;
}
void IceCaves::GetOptions(bool& vs, bool& fs)
{
	vs = fileHandler.GameData()->vsync;
	fs = fileHandler.GameData()->fullscreen;
}