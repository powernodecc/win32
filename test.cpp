#include <cstdio>
#include "Windows.h"
#include <cstdlib>

int main() {


    int i = 39;
    char str[4];
    itoa(i,str,10);

    printf("%s\n",str);
    return 0;
}