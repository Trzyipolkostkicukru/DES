#include "toolbox.h"
#include <stdlib.h>


int bits2num(uint n, bit* bits){
    //zmienia tablicę n bitów na liczbę
    uint result = 0;
    for (int i = 0; i < n; ++i){
        if(bits[i])
            result += 1 << i;
    }
    return result;
}

//UWAGA ALOKUJE
bit* num2bits(uint n, uint num){
    //zmienia liczbę na tablicę n bitów
    bit* result;
    result = (bit*)calloc(n, sizeof(bit));
    int i = 0;
    while(num){
        if(num % 2){
            result[i] = true;
        }
        i++;
        num >>= 1;
    }
    return result;
}

//UWAGA ALOKUJE
bit* permute(uint n, bit* bits, uint m, uint* permutation){
    // permutuje n bitów według permutacji o długości m
    bit* result = (bit*)calloc(m, sizeof(bit));
    for(int i=0; i<m; i++){
        result[i] = bits[permutation[i]];
    }
    return result;
}

//UWAGA ALOKUJE
bit* exor(uint n, bit* a, uint* b){
    //XORuje n bitów z list A i B
    bit* result = (bit*)calloc(n, sizeof(bit));
    for (int i = 0; i < n; ++i){
        result[i] = a[i] ^ b[i]; //xorowanie bitowe, ale powinno też działać
    }
    return result;
}