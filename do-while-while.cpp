#include <cstdio>
#include <Windows.h>

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    int i = 0;
    do {
        i++;
    } while (i <= 10);

    printf("%d\n", i);
    return 0;
}