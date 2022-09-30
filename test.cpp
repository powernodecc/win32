#ifndef UNICODE
#define UNICODE
#endif

#include "Windows.h"
#include <iostream>

int main() {

    HWND hwnd = ::FindWindow(nullptr, L"计算器"); // 获取游戏的窗口句柄
    std::cout << hwnd << std::endl;
    itoa()
    if (nullptr == hwnd) {
        return 1;
    }
    return 0;
}