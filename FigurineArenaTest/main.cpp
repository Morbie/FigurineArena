#include "WindowApp.h"

class InitDirect3DApp : public CWindowApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	void initApp();
	void onResize();
	void updateScene(float dt);
	void drawScene();
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	InitDirect3DApp theApp(hInstance);

	theApp.initApp();

	return theApp.run();
}

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
	: CWindowApp(hInstance)
{
}

InitDirect3DApp::~InitDirect3DApp()
{
	if (md3dDevice)
		md3dDevice->ClearState();
}

void InitDirect3DApp::initApp()
{
	CWindowApp::initApp();
}

void InitDirect3DApp::onResize()
{
	CWindowApp::onResize();
}

void InitDirect3DApp::updateScene(float dt)
{
	CWindowApp::updateScene(dt);
}

void InitDirect3DApp::drawScene()
{
	CWindowApp::drawScene();

	// We specify DT_NOCLIP, so we do not care about width/height of the rect.
	RECT R = { 5, 5, 0, 0 };
	mFont->DrawText(0, mFrameStats.c_str(), -1, &R, DT_NOCLIP, BLACK);

	mSwapChain->Present(0, 0);
}
