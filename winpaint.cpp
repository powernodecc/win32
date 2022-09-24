#include <Windows.h>

HANDLE output;

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
        case WM_PAINT: {
            PAINTSTRUCT ps = {};
            HDC hdc = BeginPaint(hwnd, &ps);
            MoveToEx(hdc, 100, 100, nullptr);
            EndPaint(hwnd, &ps);
            break;
        }
        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE preInstance, LPTSTR cmdLine, int showCmd) {

    AllocConsole();
    output = GetStdHandle(STD_OUTPUT_HANDLE);

    WNDCLASS w = {};
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;
    w.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    w.hCursor = nullptr;
    w.hIcon = nullptr;
    w.hInstance = hinstance;
    w.lpfnWndProc = WindowProc;
    w.lpszClassName = "Main";
    w.lpszMenuName = nullptr;
    w.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&w);

    HWND hwnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, nullptr, nullptr, hinstance,
                             nullptr);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg = {};

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}