#include "renderer.h"

HWND window::InitWindow(HINSTANCE hInstance)
{
	HWND hwnd = NULL;

	// fill out the window class structure

	WNDCLASS wc = { };

	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"overlay";
	


	if (!RegisterClass(&wc))
		return 0;

	hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, L"Overlay", L"Overlay",
		WS_VISIBLE | WS_POPUP,
		0, 0, WIDTH, HEIGHT,
		NULL, NULL, hInstance, NULL);

	SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
	SetLayeredWindowAttributes(hwnd, 0, RGB(0, 0, 0), LWA_COLORKEY);

	return hwnd;
}

bool renderer::init(HWND hwnd)
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
		return false;

	

	// set the presentation parameters
	D3DPRESENT_PARAMETERS d3dpp = {};
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	

	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pDevice)))
		return false;

	if (FAILED(D3DXCreateLine(pDevice, &mLine)))
		return false;

	return true;

}

void renderer::frame()
{
	//pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, NULL, 1.0f, 0);

	pDevice->BeginScene();

	// render here

	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);
}

void renderer::destroy()
{
	if (pDevice)
	{
		pDevice->Release();
		pDevice = NULL;
	}

	if (pD3D)
	{
		pD3D->Release();
		pD3D = NULL;
	}
}

void renderer::draw::line(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DCOLOR color)
{
	const D3DXVECTOR2 list[] = {
		p1,
		p2
	};

	mLine->Begin();
	mLine->Draw(list, 2, color);
	mLine->End();

}

void renderer::draw::box(D3DXVECTOR2 tl, D3DXVECTOR2 br, D3DCOLOR color)
{
	const D3DXVECTOR2 list[] = {
		tl,
		D3DXVECTOR2(tl.x,br.y),
		br,
		D3DXVECTOR2(br.x,tl.y),
		tl
	};

	mLine->Begin();
	mLine->Draw(list, 5, color);
	mLine->End();
}
