#include <stdio.h>
#include "toolbox.h"
#include "sboxy.h"

int main(int argc, char const *argv[]){
    bit* bity;
    bity = num2bits(10, 41);
    int test = bits2num(10, bity);
    printf("cokolwiek, %d\n", test);
    return 0;
}