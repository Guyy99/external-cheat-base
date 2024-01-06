#include "renderer/renderer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{

    HWND hwnd = window::InitWindow(hInstance);
    if (!hwnd) return -1;
    
    if (!renderer::init(hwnd))
    {
        renderer::destroy();
        return -1;
    }

    while (!GetAsyncKeyState(VK_F9))
    {
        renderer::frame();
    }

    renderer::destroy();
    UnregisterClass(L"overlay", hInstance);

    return 0;


}