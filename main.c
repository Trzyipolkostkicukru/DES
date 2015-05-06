#include <stdio.h>
#include "toolbox.h"
#include "sboxy.h"
#include "f.h"
#include <assert.h>
#include <string.h>

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

        bit t2[8] = {
            false, false, true, false,
            true, true, true, false
        };
        int result2 = bits2num(8, t2);
        if (verbose){
            printf("%d = %d\n", result2, 46);
        }
        assert(result2 == 46);
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
            0, 1, 1, 0, 1, 1
        };
        bit t[4] = {
            0, 1, 0, 1
        };
        bit* out = Sbox(0, bits);
        for(int i=0; i<4; i++){
            // printf("%d = %d\n", t[i], out[i]);
            assert(t[i] == out[i]);
        }
        printf("sadpoiyusaidyas\n");
        bit bits2[6] = {
            1, 0, 1, 0, 0, 1
        };
        bit t2[4] = {
            0, 0, 1, 1
        };
        out = Sbox(1, bits2);
        for(int i=0; i<4; i++){
            // printf("%d = %d\n", t2[i], out[i]);
            assert(t2[i] == out[i]);
        }
        printf("%s\n", "Sboxy działają");
    }

    {
        //bit* k(int n, bit* key)
        //TODO
    }

    return;
}
//KONIEC TESTÓW
void printbits(bit* bits){
    for (int i = 0; i < 64; ++i){
        if (i%8 == 0){
            printf(" ");
        }
        printf("%d", bits[i]);
    }
}
pair runda(int n, pair in){
    pair out;

    bit* tmp = f(in.R, k(n));
    tmp = exor(32, tmp, in.L);
    out.R = tmp;
    out.L = in.R;
    return out;
}


bit* encryptBlock(bit* input){
    //pobiera 64 bity i zwraca zaszyfrowany blok

    //initial permutation
    uint perm[64] = {
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7,
        56, 48, 40, 32, 24, 16, 8, 0,
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6
    };
    uint permodwrotna[64] = {
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25,
        32, 0, 40, 8, 48, 16, 56, 24
    };
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
    out = permute(64, out, 64, permodwrotna);
    return out;
}
bit* decryptBlock(bit* input){
    //pobiera 64 bity i zwraca zaszyfrowany blok

    //initial permutation
    uint perm[64] = {
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7,
        56, 48, 40, 32, 24, 16, 8, 0,
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6
    };
    uint permodwrotna[64] = {
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25,
        32, 0, 40, 8, 48, 16, 56, 24
    };
    bit* permuted = permute(64, input, 64, perm);
    bit* l = permuted;
    bit* r = permuted+32;

    pair state;
    state.L = l;
    state.R = r;
    for(int i=0; i<16; i++){
        state = runda(15-i, state);
    }

    bit* out = (bit*)calloc(64, sizeof(bit));
    for(int i=0; i<32; i++){
        out[i] = state.R[i];
    }
    for(int i=0; i<32; i++){
        out[i+32] = state.L[i];
    }
    out = permute(64, out, 64, permodwrotna);
    return out;
}

char** readFile(char* filename){
    FILE *fp = fopen(filename, "r");
    int blocks = 0;
    int tail = 0;
    char** output = (char**)calloc(2560, sizeof(char*));
    do{
        blocks++;
        output[blocks] = (char*)calloc(9, sizeof(char));
        tail = fread(output[blocks], 1, 8, fp);
        output[blocks][8] = '\0';
    } while(tail == 8);
    fclose(fp);
    output[0] = (char*)calloc(8, sizeof(char));
    output[0][0] = tail; //długość ostatniego bloku
    output[0][1] = (blocks >> 24) & 0xFF; //ilość bloków zapisana w 4 bajtach
    output[0][2] = (blocks >> 16) & 0xFF;
    output[0][3] = (blocks >> 8) & 0xFF;
    output[0][4] = blocks & 0xFF;
    return output;
}
//size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)

void encryptFile(char* filename){
    //SKOPIOWANE Z READFILE
    FILE *fp = fopen(filename, "rb");
            // printf("fp: %d\n", *fp);
    unsigned int blocks = 0;
    int tail = 0;
    char** output = (char**)calloc(2000000, sizeof(char*));
    do{
        blocks++;
        output[blocks] = (char*)calloc(9, sizeof(char));
        tail = fread(output[blocks], 1, 8, fp);
        output[blocks][8] = '\0';
        // if (tail != 9){
        //     for (int i = 0; i < 8; ++i){
        //         printf("[]%c\n", output[blocks][i]);
        //     }
        // } printf("\n");

    } while(tail == 8);
    // printf("fp: %d\n", *fp);
    fclose(fp);
    output[0] = (char*)calloc(8, sizeof(char));
    output[0][0] = tail; //długość ostatniego bloku
    output[0][1] = (blocks >> 24) & 0xFF; //ilość bloków zapisana w 4 bajtach
    output[0][2] = (blocks >> 16) & 0xFF;
    output[0][3] = (blocks >> 8) & 0xFF;
    output[0][4] = blocks & 0xFF;
    //KONIEC SKOPIOWANEGO

    char fn[200];
    strcpy(fn, filename);
    strcat(fn, ".encrypted");
    fp = fopen(fn, "wb");
    for (int i = 0; i < blocks+1; ++i){
        bit* encrypted = encryptBlock(chars2block(output[i]));
        char* enc = block2chars(encrypted);
        fwrite(enc, 8, 1, fp);
    }
    fclose(fp);
    printf("tail to %d\n", tail);
    printf("blocks to %d\n", blocks);
    for (int i = 0; i < 2000000; ++i){
        free(output[i]);
    }
    free(output);
}

void decryptFile(char* filename){
    FILE *fp = fopen(filename, "rb");
    unsigned int blocks = 0;
    unsigned int tail = 0;
    unsigned char** output = (unsigned char**)calloc(2000000, sizeof(char*));
    do{
        output[blocks] = (char*)calloc(9, sizeof(char));
        tail = fread(output[blocks], 8, 1, fp);
        output[blocks][8] = '\0';
        // printf("out block%u\n", (unsigned char)output[blocks][0]);

        blocks++;
    } while(tail);
    fclose(fp);

    char fn[200];
    strcpy(fn, filename);
    strcat(fn, ".decrypted");
    fp = fopen(fn, "wb");
    // printf("%s\n", output[0]);
    bit* block = chars2block(output[0]);
    bit* decrypted = decryptBlock(block);
    unsigned char* dec = block2chars(decrypted);
    tail = dec[0];
    blocks = dec[4];
    blocks += ((unsigned int)dec[3]) << 8;
    blocks += ((unsigned int)dec[2]) << 16;
    blocks += ((unsigned int)dec[1]) << 24;



    printf("bb = %d\n", blocks);
    for (int i = 1; i < blocks; ++i){
        bit* block = chars2block(output[i]);
        bit* decrypted = decryptBlock(block);
        char* dec = block2chars(decrypted);
        fwrite(dec, 8, 1, fp);
        // for (int j = 0; j < 8; ++j){
        //     printf("{}%c\n", dec[j]);

        // }
        // printf("\n");
    }
    {
        bit* block = chars2block(output[blocks]);
        bit* decrypted = decryptBlock(block);
        char* dec = block2chars(decrypted);
        fwrite(dec, tail, 1, fp);
        // for (int j = 0; j < tail; ++j){
        //     printf("[]%c \n", dec[j]);
        // }
    }



    // printf("%s\n", dec);
    return;
}
int main(int argc, char **argv){
    // bit* bity;
    // bity = num2bits(64, 41);
    // bity = encryptBlock(bity);
    // int test = bits2num(64, bity);
    // printf("cokolwiek, %d\n", test);
    // test();
    // bit* bits = hex2bits(16, "85E813540F0AB405");
    // printf("ZZZ\n");
    // bits = decryptBlock(bits);
    // printbits(hex2bits(16, "0123456789ABCDEF"));
    // printf("\n");
    // printbits(bits);
    // char** text = readFile("./main.c");
    // printf("%u, %u, %u, %u, %u\n", text[0][0], text[0][1], text[0][2], text[0][3], text[0][4]);
    // for (int i = 1; i < 20; ++i){
    //     printf("%s\n", block2chars(chars2block(text[i])));
    // }
    encryptFile(argv[1]);
    printf("zzz\n");
    decryptFile(argv[2]);
    return 0;
}

//plaintext 0123456789ABCDEF
//szyfr 85E813540F0AB405