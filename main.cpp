#ifndef UNICODE
#define UNICODE
#endif

#include "tchar.h"
#include <iostream>
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CREATE:
            break;
        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPTSTR lpCmdLine, IN int nShowCmd) {

    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.cbWndExtra = 0;
    wc.cbClsExtra = 0;
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0, CLASS_NAME, L"window", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                               CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
