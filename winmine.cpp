#include <cstdlib>
#include <iostream>
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
            CreateWindowExW(0, L"Button", L"btn1",
                            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 20, 20, 100, 30,
                            hwnd, reinterpret_cast<HMENU>(1),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            CreateWindowExW(0, L"Button", L"读取基地址",
                            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 20, 60, 100, 30,
                            hwnd, reinterpret_cast<HMENU>(2),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            CreateWindowExW(0, L"Edit", nullptr,
                            WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 130, 60, 100, 30,
                            hwnd, reinterpret_cast<HMENU>(3),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            CreateWindowEx(0, L"Button", L"快速通关",
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 20, 100, 100, 30,
                           hwnd, reinterpret_cast<HMENU>(4),
                           (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            CreateWindowEx(0, L"Edit", nullptr,
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_MULTILINE, 20, 140, 200, 200,
                           hwnd, reinterpret_cast<HMENU>(5),
                           (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            break;
        }
        case WM_COMMAND:
            switch (LOWORD(wparam)) {
                case 1: {
                    HWND mine = ::FindWindowW(nullptr, L"扫雷");
                    if (nullptr == mine) {
                        MessageBoxW(nullptr, L"not found window", L"error", MB_OK);
                        return 1;
                    }
                    SendMessage(mine, WM_COMMAND, 0x20A, 0);
                    break;
                }
                case 2: {
                    DWORD pid;
                    HWND mine = ::FindWindowW(nullptr, L"扫雷"); // 获取游戏的窗口句柄
                    if (nullptr == mine) {
                        MessageBoxW(nullptr, L"not found mine window", L"error", MB_OK);
                        return 1;
                    }
                    GetWindowThreadProcessId(mine, &pid); // 通过窗口句柄拿到进程ID
                    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); // 通过进程ID拿到进程句柄
                    if (nullptr == hProcess) {
                        MessageBoxW(nullptr, L"open mine window error", L"error", MB_OK);
                        return 1;
                    }
                    int editStr = 0;
                    unsigned long number = 0;
                    ReadProcessMemory(hProcess, (LPCVOID) 0x1005194, &editStr, sizeof editStr, &number);
                    char str[5];
                    _itoa_s(editStr, str, 10);
                    SetDlgItemTextA(hwnd, 3, str);
                    break;
                }
                case 4: {
                    HWND mine = ::FindWindow(nullptr, L"扫雷");
                    if (nullptr == mine) {
                        ::MessageBox(nullptr, L"game unopened", L"error", MB_OK);
                        return 1;
                    }

                    DWORD pid = 0;
                    GetWindowThreadProcessId(mine, &pid);
                    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
                    if (nullptr == hProcess) {
                        ::MessageBox(nullptr, L"open game failed", L"error", MB_OK);
                        return 1;
                    }

                    unsigned char data[24][32] = {0};
                    unsigned long n = 0;
                    if (!ReadProcessMemory(hProcess, (LPCVOID) 0x1005361, &data, 24 * 32, &n)) {
                        ::MessageBox(nullptr, L"read data failed 1 ", L"error", MB_OK);
                        return 1;
                    }

                    DWORD h = 0;
                    if (!ReadProcessMemory(hProcess, (LPCVOID) 0x1005338, &h, sizeof h, nullptr)) {
                        ::MessageBox(nullptr, L"read data failed 2 ", L"error", MB_OK);
                        return 1;
                    }

                    short x = 20;
                    short y = 60;
                    unsigned short xy[2] = {0};
                    for (int i = 0; i < h; i++) {
                        for (int j = 0; i < 32; j++) {
                            if (0x10 == data[i][j]) {
                                break;
                            }
                            xy[0] = x + j * 16;
                            xy[1] = y + i * 16;
                            if (0x8F != data[i][j]) {
                                ::PostMessage(mine, WM_LBUTTONDOWN, MK_LBUTTON, *(int *) xy);
                                ::PostMessage(mine, WM_LBUTTONUP, MK_LBUTTON, *(int *) xy);
                            }
                        }
                    }
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

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE preInstance, LPTSTR cmdLine, int showCmd) {

    //AllocConsole();
    //output = GetStdHandle(STD_OUTPUT_HANDLE);
    //WriteConsole(output, "1234", sizeof(int), nullptr, nullptr);

    WNDCLASSW w = {};
    w.hInstance = hinstance;
    w.lpfnWndProc = WindowProc;
    w.lpszClassName = L"Main";

    w.hCursor = LoadCursor(nullptr, IDC_ARROW);

    ::RegisterClassW(&w);

    HWND hwnd = CreateWindowW(L"Main", L"main", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
                              100, 100, 500, 500,
                              nullptr, nullptr, hinstance, nullptr);

    ShowWindow(hwnd, SW_SHOW);

    MSG m = {};

    while (GetMessageW(&m, nullptr, 0, 0)) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }

    return 0;
}