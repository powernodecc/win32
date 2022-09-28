#include "cstdio"
#include <cstdlib>

int main() {

    int a[0x22];
    a[0] = 0x1122;
    a[0x21] = 0x3388;

    __asm {
        mov ecx,0x22
        xor eax,eax
        lea edi,a
        rep stosd
    }
    return 0;
}