#include <Windows.h>

int main() {

    MessageBox(nullptr, nullptr, nullptr,MB_OK);

    __asm {
            mov eax, -0x3333
            movsx ecx, ah
            movzx ebx, al
    }
    return 0;
}
