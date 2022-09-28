#include "Windows.h"
#include "cstdio"

int aaa = 1;

int add(int a, int b) {
    return a + b;
}

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);
    printf("hello");

    int i = 0;
    i = i + 100;
    i = i + 0x222;

    __asm {
            mov eax, 0x222
            mov ebx, 0x100
            add ebx, eax
    }

    return 0;
}