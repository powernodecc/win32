#include <cstdio>
#include "Windows.h"

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    int a = 0x0a;
    int b = 0x20;

    if (a >= b) {
        printf("a >= b\n");
        return 0;
    }
    printf("a < b\n");
    return 0;
}