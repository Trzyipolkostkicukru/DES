w#include <stdio.h>
#include "toolbox.h"
#include "sboxy.h"
#include "f.h"
#include <assert.h>


//TESTY
void test(){
    int verbose = false;
    {
        // bit* num2bits(uint n, uint num);
        bit* result = num2bits(8, 42);
        bit t[8] = {
            false, false, true, false,
            true, false, true, false
        };
        for(int i=0; i<8; i++){
            if(verbose){
                printf("%d = %d\n", result[i], t[i]);
            }
            assert(result[i] == t[i]);
        }
        printf("%s\n", "num2bits działa");
    }

    {
        bit t[8] = {
            false, false, true, false,
            true, false, true, false
        };
        int result = bits2num(8, t);
        if (verbose){
            printf("%d = %d\n", result, 42);
        }
        assert(result == 42);
        printf("%s\n", "bits2num działa");
    }

    {
        //bit* permute(uint n, bit* bits, uint m, uint* permutation);
        bit input1[4] = {
            true, false, true, false
        };
        int perm1[4] = {
            0, 2, 1, 3
        };
        bit out1[4] = {
            true, true, false, false
        };
        bit* t = permute(4, input1, 4, perm1);
        for (int i = 0; i < 4; ++i){
            // printf("%d\n", t[i]);
            assert(t[i] == out1[i]);
        }


        bit input2[4] = {
            0, 1, 2, 3
        };
        int perm2[4] = {
            3, 2, 1, 0
        };

        t = permute(4, input2, 4, perm2);
        for (int i = 0; i < 4; ++i){
            // printf("%d\n", t[i]);
            assert(t[i] == perm2[i]);
        }

        bit input3[4] = {
            0, 0, 1, 0
        };
        int perm3[1] = {
            2
        };
        t = permute(4, input3, 1, perm3);
        assert(t[0] == 1);


        bit input4[2] = {
            1, 0
        };
        int perm4[6] = {
            1, 0, 1, 0, 0, 1
        };
        t = permute(2, input4, 6, perm4);

        for (int i = 0; i < 6; ++i){
            // printf("%d != %d\n", t[i], perm4[i]);
            assert(t[i] != perm4[i]);
        }
        printf("%s\n", "permute działa");
    }

    {
        //bit* exor(uint n, bit* a, bit* b);
        bit a[4] = {
            1, 1, 0, 0
        };
        bit b[4]= {
            1, 0, 1, 0
        };
        bit t[4] = {
            0, 1, 1, 0
        };

        bit* out = exor(4, a, b);

        for (int i = 0; i < 4; ++i){
            // printf("%d = %d\n", out[i], t[i]);
            assert(t[i] == out[i]);
        }

        printf("%s\n", "exor działa");
    }

    {
        //bit* Sbox(uint n, bit* bits);
        bit bits[6] = {
            0, 1, 0, 1, 0, 1
        };
        bit t[4] = {
            0, 1, 1, 0
        };
        bit* out = Sbox(0, bits);
        for(int i=0; i<4; i++){
            // printf("%d = %d\n", t[i], out[i]);
            assert(t[i] == out[i]);
        }
        printf("%s\n", "Sboxy działają");
    }

    return;
}
//KONIEC TESTÓW
pair runda(int n, pair in){
    pair out;
    bit* tmp = f(in.R, k(n));
    tmp = exor(32, tmp, in.L);
    out.L = tmp;
    out.R = in.L;
    // free(in.P);
    return out;
}

bit* encryptBlock(bit* input){
    //pobiera 64 bity i zwraca zaszyfrowany blok

    //initial permutation
    uint* perm = (uint*)calloc(64, sizeof(uint)); //TODO
    bit* permuted = permute(64, input, 64, perm);
    bit* l = permuted;
    bit* r = permuted+32;

    pair state;
    state.L = l;
    state.R = r;
    for(int i=0; i<16; i++){
        state = runda(i, state);
    }

    bit* out = (bit*)calloc(64, sizeof(bit));
    for(int i=0; i<32; i++){
        out[i] = state.R[i];
    }
    for(int i=0; i<32; i++){
        out[i+32] = state.L[i];
    }
    return out;
}


int main(int argc, char const *argv[]){
    // bit* bity;
    // bity = num2bits(64, 41);
    // bity = encryptBlock(bity);
    // int test = bits2num(64, bity);
    // printf("cokolwiek, %d\n", test);
    test();
    return 0;
}