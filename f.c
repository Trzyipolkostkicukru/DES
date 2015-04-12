//[32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1]

#include "toolbox.h"
#include "sboxy.h"

//UWAGA ALOKUJE
bit* e(bit* R){
    uint permutation[48] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
    };
    return permute(32, R, 48, permutation);
}

//UWAGA ALOKUJE
bit* p(bit* in){
    uint permutation[32] = {
        15, 6, 19, 20,
        28, 11, 27, 16,
        0, 14, 22, 25,
        4, 17, 30, 9,
        1, 7, 23, 13,
        31, 26, 2, 8,
        18, 12, 29, 5,
        21, 10, 3, 24
    };
    return permute(32, in, 32, permutation);
}

//UWAGA ALOKUJE
bit* f(bit* R, bit* K){
    bit* tmp = e(R);
    bit* sBoxInput = exor(48, tmp, K);
    free(tmp);

    tmp = (bit*)calloc(32, sizeof(bit));
    //przepuść dane przez S-boxy
    for (int i = 0; i < 8; ++i){
        bit* out = Sbox(i, sBoxInput+(i*6));
        for (int j = 0; j < 4; ++j){
            tmp[i*6+j] = out[j];
        }
        free(out);
    }
    free(sBoxInput);

    bit* result;
    result = p(tmp);
    free(tmp);

    return result;

}

bit* k(int n, bit* key){
    bit* out = (bit*)calloc(32, sizeof(bit));
    int PC1a[28] = {
        56, 48, 40, 32, 24, 16, 8,
        0, 57, 49, 41, 33, 25, 17,
        9, 1, 58, 50, 42, 34, 26,
        18, 10, 2, 59, 51, 43, 35
    };

    int PC1b[28] = {
        62, 54, 46, 38, 30, 22, 14,
        6, 61, 53, 45, 37, 29, 21,
        13, 5, 60, 52, 44, 36, 28,
        20, 12, 4, 27, 19, 11, 3
    };

    bit* C = permute(28, key, 28, PB1a);
    bit* D = permute(28, key, 28, PB1b);
    return out;
}