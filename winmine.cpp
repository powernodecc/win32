#include <cstdlib>
#include "Windows.h"

// Copy from MSDN
#pragma comment(linker, "\"/manifestdependency:type='win32' "\
                        "name='Microsoft.Windows.Common-Controls' "\
                        "version='6.0.0.0' processorArchitecture='*' "\
                        "publicKeyToken='6595b64144ccf1df' language='*'\"")

HANDLE output;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindowEx(0, "Button", "btn1",
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 20, 20, 100, 30,
                           hwnd, reinterpret_cast<HMENU>(1),
                           (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            CreateWindowEx(0, "Button", "读取基地址",
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 130, 20, 100, 30,
                           hwnd, reinterpret_cast<HMENU>(2),
                           (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            CreateWindowEx(0, "Edit", nullptr,
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 250, 20, 100, 30,
                           hwnd, reinterpret_cast<HMENU>(3),
                           (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            break;
        }
        case WM_COMMAND:
            switch (LOWORD(wparam)) {
                case 1: {
                    HWND mine = ::FindWindow(nullptr, "扫雷");
                    if (nullptr == mine) {
                        MessageBox(nullptr, "not found window", "error", MB_OK);
                        return 1;
                    }
                    SendMessage(mine, WM_COMMAND, 0x20A, 0);
                    break;
                }
                case 2: {
                    DWORD pid;
                    HWND mine = ::FindWindow(nullptr, "扫雷"); // 获取游戏的窗口句柄
                    if (nullptr == mine) {
                        MessageBox(nullptr, "not found mine window", "error", MB_OK);
                        return 1;
                    }
                    GetWindowThreadProcessId(mine, &pid); // 通过窗口句柄拿到进程ID
                    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); // 通过进程ID拿到进程句柄
                    if (nullptr == hProcess) {
                        MessageBox(nullptr, "open mine window error", "error", MB_OK);
                        return 1;
                    }
                    int editStr = 0;
                    unsigned long number = 0;
                    ReadProcessMemory(hProcess, (LPCVOID) 0x1005194, &editStr, sizeof editStr, &number);
                    char str[5];
                    _itoa_s(editStr, str, 10);
                    SetDlgItemText(hwnd, 3, str);
                    break;
                }
                default:
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE preInstance, LPTSTR cmdLine, int showCmd) {

    //AllocConsole();
    //output = GetStdHandle(STD_OUTPUT_HANDLE);
    //WriteConsole(output, "1234", sizeof(int), nullptr, nullptr);

    WNDCLASS w = {};
    w.hInstance = hinstance;
    w.lpfnWndProc = WindowProc;
    w.lpszClassName = "Main";

    w.hCursor = LoadCursor(nullptr, IDC_ARROW);

    ::RegisterClass(&w);

    HWND hwnd = CreateWindow("Main", "main", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
                             100, 100, 500, 500,
                             nullptr, nullptr, hinstance, nullptr);

    ShowWindow(hwnd, SW_SHOW);

    MSG m = {};

    while (GetMessage(&m, nullptr, 0, 0)) {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }

    return 0;
}