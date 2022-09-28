#include <Windows.h>
#include <cstdio>

__declspec(naked) int asm_strcmp(const char *str1, const char *str2) {

    __asm {
            push ebp
            mov ebp, esp
            push ecx
            push edi
            push esi
            push edx
            xor al, al
            mov edi,[ebp+4+4]
            mov ecx, -1
            repnz scasb
            not ecx

            mov edi,[ebp+4+4]
            mov esi,[ebp+4+8]
            repz cmpsb

            xor eax, eax
            xor edx, edx
            mov al,[edi-1]
            mov dl,[esi-1]
            sub eax, edx
            pop edx
            pop esi
            pop edi
            pop ecx
            pop ebp
            retn
    }
}

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    printf("asm_strcmp=%d\n", asm_strcmp("aaabbbddd", "aaabbbddd"));

    return 0;
}