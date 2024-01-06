#pragma once

#include "../memory/memory.h"
#include <d3d9.h>
#include <d3dx9.h>

#include "../math/vector.h"

#define WIDTH 1920
#define HEIGHT 1080	

namespace window
{
	HWND InitWindow(HINSTANCE hInstance);
	inline LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}


}

namespace renderer
{
	inline IDirect3D9* pD3D = nullptr;
	inline IDirect3DDevice9* pDevice = nullptr;
	inline ID3DXLine* mLine = nullptr;

	bool init(HWND hwnd);
	void destroy();

	void frame();

	namespace draw
	{
		void line(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DCOLOR color);
		void box(D3DXVECTOR2 tl, D3DXVECTOR2 br, D3DCOLOR color);
	}



};

