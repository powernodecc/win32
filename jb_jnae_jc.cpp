#include <cstdio>
#include "Windows.h"

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    unsigned int a = 0x10;
    unsigned int b = 0x20;

//    if (a >= b) {
//        printf("a >= b\n");
//        return 0;
//    }
//
//    printf("a < b\n");

    __asm {
            mov eax, a
            cmp eax, b
            JNAE end
    }
    printf("a < b\n");
    getchar();
    return 0;
    end:
    printf("a >= b\n");
    return 0;
}