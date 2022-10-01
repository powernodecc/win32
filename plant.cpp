#include "Windows.h"

// Copy from MSDN
#pragma comment(linker, "\"/manifestdependency:type='win32' "\
                        "name='Microsoft.Windows.Common-Controls' "\
                        "version='6.0.0.0' processorArchitecture='*' "\
                        "publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND plant;
HANDLE hProcess;

VOID FindPlantWindow() {
    plant = ::FindWindowW(nullptr, L"植物大战僵尸中文版");
    if (nullptr == plant) {
        MessageBox(nullptr, L"FindWindowW Error", L"Error", MB_OK);
        return;
    }
}

VOID OpenPlantProcess() {
    DWORD pid = 0;
    GetWindowThreadProcessId(plant, &pid);
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (nullptr == hProcess) {
        CloseHandle(hProcess);
        MessageBox(nullptr, L"OpenProcess Error", L"Error", MB_OK);
        return;
    }
}

bool IsReady() {
    if (nullptr == plant || nullptr == hProcess) {
        return false;
    }
    return true;
}

__declspec(naked) void PutPlant() {
    __asm{
            pushad
            push -1
            push 2
            mov eax, 0
            push 0
            mov ebx, ds:[0x006A9EC0]
            mov ebx, ds:[ebx+0x768]
            push ebx
            mov edx, 0x40D120
            call edx
            popad
            ret
    }
}

bool EnableDebugPrivilege() {
    HANDLE hToken;
    LUID seDebugNameValue;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return false;
    }

    if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &seDebugNameValue)) {
        CloseHandle(hToken);
        return false;
    }
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = seDebugNameValue;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, nullptr, nullptr)) {
        CloseHandle(hToken);
        return false;
    }

    return true;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindowExW(0, L"Button", L"刷新",
                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                            20, 300, 80, 60, hwnd, reinterpret_cast<HMENU>(0),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Button", L"无线阳光",
                            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                            20, 20, 100, 30, hwnd, reinterpret_cast<HMENU>(1),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Button", L"无线金币",
                            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                            20, 70, 100, 30, hwnd, reinterpret_cast<HMENU>(2),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Button", L"植物无冷却",
                            WS_CHILD | WS_GROUP | WS_TABSTOP | BS_CHECKBOX | BS_PUSHBUTTON | WS_VISIBLE,
                            20, 130, 100, 30, hwnd, reinterpret_cast<HMENU>(3),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Button", L"大嘴花一直吞",
                            WS_CHILD | WS_GROUP | WS_TABSTOP | BS_CHECKBOX | BS_PUSHBUTTON | WS_VISIBLE,
                            20, 190, 130, 30, hwnd, reinterpret_cast<HMENU>(4),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Edit", L"0",
                            WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER,
                            280, 20, 100, 20, hwnd, reinterpret_cast<HMENU>(5),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Edit", L"0",
                            WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER,
                            280, 70, 100, 20, hwnd, reinterpret_cast<HMENU>(6),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Static", L"x坐标",
                            WS_CHILD | WS_VISIBLE,
                            230, 20, 50, 20, hwnd, reinterpret_cast<HMENU>(7),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Static", L"y坐标",
                            WS_CHILD | WS_VISIBLE,
                            230, 70, 50, 20, hwnd, reinterpret_cast<HMENU>(8),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            CreateWindowExW(0, L"Button", L"使用一个樱桃",
                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                            250, 110, 130, 30, hwnd, reinterpret_cast<HMENU>(9),
                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            HWND comboBox = CreateWindowExW(0, L"COMBOBOX", L"",
                                            WS_CHILD | WS_VISIBLE,
                                            250, 210, 130, 50, hwnd, reinterpret_cast<HMENU>(10),
                                            (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);

            const TCHAR *plants[]{L"豌豆射手", L"樱桃炸弹", L"大嘴花"};
            for (int i = 0; i < 3; i++) {
                SendMessage(comboBox, CB_ADDSTRING, i, (LPARAM) plants[i]);
            }
            break;
        }
        case WM_COMMAND :
            if (!IsReady()) {
                break;
            }
            switch (LOWORD(wparam)) {
                case 0: {
                    FindPlantWindow();
                    OpenPlantProcess();
                    break;
                }
                case 1: {
                    DWORD t = 0;
                    if (!ReadProcessMemory(hProcess, (LPCVOID) 0x6A9EC0, (LPVOID) &t, sizeof(DWORD), nullptr)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"ReadProcessMemory Error", L"Error1", MB_OK);
                        break;
                    }
                    t += 0x768;
                    if (!ReadProcessMemory(hProcess, (LPVOID) t, (LPVOID) &t, sizeof(DWORD), nullptr)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"ReadProcessMemory Error", L"Error2", MB_OK);
                        break;
                    }
                    t += 0x5560;
                    DWORD sun = 88888;
                    if (!WriteProcessMemory(hProcess, (LPVOID) t, (LPVOID) &sun, sizeof(DWORD), nullptr)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"WriteProcessMemory Error", L"Error", MB_OK);
                        break;
                    }
                    break;
                }
                case 2: {
                    DWORD t = 0;
                    if (!ReadProcessMemory(hProcess, (LPCVOID) 0x6A9EC0, (LPVOID) &t, sizeof(DWORD), nullptr)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"ReadProcessMemory Error", L"Error1", MB_OK);
                        break;
                    }
                    t += 0x82c;
                    if (!ReadProcessMemory(hProcess, (LPVOID) t, (LPVOID) &t, sizeof(DWORD), nullptr)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"ReadProcessMemory Error", L"Error2", MB_OK);
                        break;
                    }
                    t += 0x28;
                    DWORD sun = 88888;
                    if (!WriteProcessMemory(hProcess, (LPVOID) t, (LPVOID) &sun, sizeof(DWORD), nullptr)) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"WriteProcessMemory Error", L"Error", MB_OK);
                        break;
                    }
                    break;
                }
                case 3: {
                    unsigned char strong[2] = {0x90, 0x90};
                    unsigned char normal[2] = {0x7E, 0x14};
                    UINT status = IsDlgButtonChecked(hwnd, 3);
                    if (status == BST_UNCHECKED) {
                        WriteProcessMemory(hProcess, (LPVOID) 0x00487296, strong, 2, nullptr);
                        CheckDlgButton(hwnd, 3, BST_CHECKED);
                    } else if (status == BST_CHECKED) {
                        WriteProcessMemory(hProcess, (LPVOID) 0x00487296, normal, 2, nullptr);
                        CheckDlgButton(hwnd, 3, BST_UNCHECKED);
                    }
                    break;
                }
                case 4: {
                    unsigned char strong[2] = {0x90, 0x90};
                    unsigned char normal[2] = {0x75, 0x5F};
                    UINT status = IsDlgButtonChecked(hwnd, 4);
                    if (status == BST_UNCHECKED) {
                        WriteProcessMemory(hProcess, (LPVOID) 0x00461565, strong, 2, nullptr);
                        CheckDlgButton(hwnd, 4, BST_CHECKED);
                    } else if (status == BST_CHECKED) {
                        WriteProcessMemory(hProcess, (LPVOID) 0x00461565, normal, 2, nullptr);
                        CheckDlgButton(hwnd, 4, BST_UNCHECKED);
                    }
                    break;
                }
                case 9: {
                    PVOID ad = VirtualAllocEx(hProcess, nullptr, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
                    if (ad == nullptr) {
                        CloseHandle(hProcess);
                        MessageBox(nullptr, L"VirtualAllocEx Error", L"Error", MB_OK);
                        break;
                    }

                    DWORD number = 0;
                    WriteProcessMemory(hProcess, ad, (LPCVOID) PutPlant, 4096, &number);

                    CreateRemoteThread(hProcess, nullptr, NULL,
                                       (LPTHREAD_START_ROUTINE) ad, nullptr, NULL, nullptr);
                    break;
                }
                case 10: {
                    if (HIWORD(wparam) == CBN_SELCHANGE) {
                        LRESULT r = SendMessageW(GetDlgItem(hwnd, 10), CB_GETCURSEL, 0, 0);
                        if (r == 2) {
                            MessageBoxW(nullptr, L"!", L"!", MB_OK);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        case WM_CLOSE:
            CloseHandle(hProcess);
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

    EnableDebugPrivilege();
    FindPlantWindow();
    OpenPlantProcess();

    WNDCLASS w = {};
    w.hInstance = hinstance;
    w.lpfnWndProc = WindowProc;
    w.lpszClassName = L"Main";
    w.hbrBackground = (HBRUSH) COLOR_WINDOW;
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