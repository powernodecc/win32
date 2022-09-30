#include "Windows.h"

// Copy from MSDN
#pragma comment(linker, "\"/manifestdependency:type='win32' "\
                        "name='Microsoft.Windows.Common-Controls' "\
                        "version='6.0.0.0' processorArchitecture='*' "\
                        "publicKeyToken='6595b64144ccf1df' language='*'\"")


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindowExW(0, L"Button", L"无线阳光",
                            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                            20, 20, 100, 30, hwnd, reinterpret_cast<HMENU>(1),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
            break;
        }
        case WM_COMMAND :
            switch (LOWORD(wparam)) {
                case 1: {
                    HWND plant = ::FindWindowW(nullptr, L"植物大战僵尸中文版");
                    if (nullptr == plant) {
                        MessageBox(nullptr, L"FindWindowW Error", L"Error", MB_OK);
                        break;
                    }
                    DWORD pid = 0;
                    GetWindowThreadProcessId(plant, &pid);
                    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
                    if (nullptr == hProcess) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"OpenProcess Error", L"Error", MB_OK);
                        break;
                    }
                    DWORD t = 0;
                    if (!ReadProcessMemory(hProcess, (LPCVOID) 0x6A9EC0, (LPVOID)&t, sizeof(DWORD), &pid)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"ReadProcessMemory Error", L"Error1", MB_OK);
                        break;
                    }
                    t += 0x768;
                    if (!ReadProcessMemory(hProcess, (LPVOID)t, (LPVOID)&t, sizeof(DWORD), nullptr)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"ReadProcessMemory Error", L"Error2", MB_OK);
                        break;
                    }
                    t += 0x5560;
                    DWORD sun = 88888;
                    if (!WriteProcessMemory(hProcess, (LPVOID) t, (LPVOID)&sun, sizeof(DWORD), nullptr)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"WriteProcessMemory Error", L"Error", MB_OK);
                        break;
                    }
                    CloseHandle(hProcess);
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

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE preInstance, LPTSTR cmd, int show) {

    WNDCLASS w = {};
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