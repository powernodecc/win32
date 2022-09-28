#include <cstdio>
#include <Windows.h>

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    int a = 0x20, b = 0x10, c = 0x30;

    if (a > b) {
        printf("a > b\n");
        if (b > c) {
            printf("a > b,b > c\n");
        }
    } else {
        printf("a <= b\n");
    }
    return 0;
}