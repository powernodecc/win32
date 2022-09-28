#include <cstdio>
#include <Windows.h>

int main() {

    MessageBox(nullptr, nullptr, nullptr, MB_OK);

    float f = 10.8642f;
//    f = f / 2;
    f++;
    printf("f=%f\n", f);
    return 0;
}