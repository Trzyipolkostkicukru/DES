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

bit* p(bit* in){
    return in;
}

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


}