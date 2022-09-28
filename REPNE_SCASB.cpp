#include <Windows.h>

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    const char *s1 = "s123456789";

    __asm {
            mov al, 0
            mov edi, s1
            mov ecx, -1
            repnz scasb // repne scas byte ptr [edi]
            mov eax, -1
            sub eax, ecx
//            sub eax, 1
    }

    return 0;
}