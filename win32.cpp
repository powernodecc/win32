#include <Windows.h>

HANDLE output;
// Copy from MSDN
#pragma comment(linker, "\"/manifestdependency:type='win32' "\
                        "name='Microsoft.Windows.Common-Controls' "\
                        "version='6.0.0.0' processorArchitecture='*' "\
                        "publicKeyToken='6595b64144ccf1df' language='*'\"")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CREATE:
            CreateWindowEx(0, "Button", "button1",
                           WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                           20, 20, 100, 30,
                           hwnd, reinterpret_cast<HMENU>(1), (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                           nullptr);
            CreateWindowEx(0, "Button", "button2",
                           WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                           200, 20, 100, 30,
                           hwnd, reinterpret_cast<HMENU>(2), (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                           nullptr);
            break;
        case WM_PAINT: {
            const char *str = "WM_PAINT\n";
//            WriteConsole(output, str, strlen(str), nullptr, nullptr);
            break;
        }
        case WM_COMMAND : {
            auto l = LOWORD(wParam);
            auto h = HIWORD(wParam);
            switch (l) {
                case 1:
                    MessageBox(hwnd, "1", "1", MB_OK);
                    break;
                case 2:
                    MessageBox(hwnd, "2", "2", MB_OK);
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE preInstance, LPTSTR cmdLine, int showCmd) {

//    AllocConsole();
//    output = GetStdHandle(STD_OUTPUT_HANDLE);

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