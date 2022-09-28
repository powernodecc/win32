#include <cstdio>
#include <Windows.h>

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    int a = 0x19;

    switch (a) {
        case 0x10:
            printf("0x10\n");
            break;
        case 0x20:
            printf("0x20\n");
            break;
        case 0x30:
            printf("0x30\n");
            break;
        case 0x22:
            printf("0x22\n");
            break;
        case 0x19:
            printf("0x19\n");
            break;
        default:
            printf("default\n");
            break;
    }
    printf("switch end\n");
    return 0;
}