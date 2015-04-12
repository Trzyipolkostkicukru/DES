#include <stdio.h>
#include "toolbox.h"
#include "sboxy.h"
#include "f.h"

pair round(int n, pair in){
    pair out;
    bit* tmp = f(in.R, k(n));
    for(int i=0; i<32 i++){
        tmp[i] = exor(tmp[i], in.L[i]);
    }
    out.L = tmp;
    out.P = in.L;
    // free(in.P);
    return out;
}

bit* encryptBlock(bit* input){
    //pobiera 64 bity i zwraca zaszyfrowany blok

    //initial permutation
    uint* perm; //TODO
    bit* permuted = permute(64, input, 64, perm);
    bit* l = permuted;
    bit* p = permuted+32;

    pair state;
    state.L = l;
    state.P = p;
    for(int i=0; i<16; i++){
        state = round(i, state);
    }

    bit* out = (bit*)calloc(64, sizeof(bit));
    for(int i=0; i<32, i++){
        out[i] = state.P[i];
    }
    for(int i=0; i<32, i++){
        out[i+32] = state.L[i];
    }
    return out;
}


int main(int argc, char const *argv[]){
    bit* bity;
    bity = num2bits(10, 41);
    int test = bits2num(10, bity);
    printf("cokolwiek, %d\n", test);
    return 0;
}