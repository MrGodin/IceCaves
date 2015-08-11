

#include "IceCaves.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	srand((UINT)time(0));


	IceCaves app(hInstance, L"Caves of Burgh", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING,new PlayerControl());
	
	TGame::gd3dApp = &app;
	

	

	return  TGame::gd3dApp->run();
}

