#include "Windows.h"
#include "cstdio"

int main() {

    DWORD iEax;
    WORD iAx;
    BYTE iAh, iAl;

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    __asm {
            mov eax, 0x87654321;
            mov iEax, eax
            mov iAx, ax
            mov iAh, ah
            mov iAl, al
    }

    printf("EAX=%lx,AX=%x,AH=%x,AL=%x\n", iEax, iAx, iAh, iAl);

    getchar();

    return 0;
}