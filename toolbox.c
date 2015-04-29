#include "toolbox.h"
#include <stdlib.h>


int bits2num(uint n, bit* bits){
    //zmienia tablicę n bitów na liczbę
    uint result = 0;
    for (int i = 0; i < n; ++i){
        if(bits[n-i-1])
            result += 1 << i;
    }
    return result;
}

//UWAGA ALOKUJE
bit* num2bits(uint n, uint num){
    //zmienia liczbę na tablicę n bitów
    bit* result;
    result = (bit*)calloc(n, sizeof(bit));
    int i = 1;
    while(num){
        if(num % 2){
            result[n-i] = true;
        }
        i++;
        num >>= 1;
    }
    return result;
}
bit* char2bits(uint n, unsigned char num){
    //zmienia liczbę na tablicę n bitów
    bit* result;
    result = (bit*)calloc(n, sizeof(bit));
    int i = 1;
    while(num){
        if(num % 2){
            result[n-i] = true;
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
bit* exor(uint n, bit* a, bit* b){
    //XORuje n bitów z list A i B
    bit* result = (bit*)calloc(n, sizeof(bit));
    for (int i = 0; i < n; ++i){
        result[i] = a[i] ^ b[i]; //xorowanie bitowe, ale powinno też działać
    }
    return result;
}

// char* bits2hex(uint n, bit* bits){
//     char* out = (char*)calloc(n/4, sizeof(char));

//     for (int i = 0; i < n; i=i+4){
//         num = bits2num(4, bits[i]);

//     }
// }

//UWAGA ALOKUJE
bit* hex2bits(uint n, char* hex){
    bit* out = (bit*)calloc(n*4, sizeof(bit));
    for (int i = 0; i < n; ++i){
        switch(hex[i]){
            case '0':
                out[i*4]   = 0;
                out[i*4+1] = 0;
                out[i*4+2] = 0;
                out[i*4+3] = 0;
                break;
            case '1':
                out[i*4]   = 0;
                out[i*4+1] = 0;
                out[i*4+2] = 0;
                out[i*4+3] = 1;
                break;
            case '2':
                out[i*4]   = 0;
                out[i*4+1] = 0;
                out[i*4+2] = 1;
                out[i*4+3] = 0;
                break;
            case '3':
                out[i*4]   = 0;
                out[i*4+1] = 0;
                out[i*4+2] = 1;
                out[i*4+3] = 1;
                break;
            case '4':
                out[i*4]   = 0;
                out[i*4+1] = 1;
                out[i*4+2] = 0;
                out[i*4+3] = 0;
                break;
            case '5':
                out[i*4]   = 0;
                out[i*4+1] = 1;
                out[i*4+2] = 0;
                out[i*4+3] = 1;
                break;
            case '6':
                out[i*4]   = 0;
                out[i*4+1] = 1;
                out[i*4+2] = 1;
                out[i*4+3] = 0;
                break;
            case '7':
                out[i*4]   = 0;
                out[i*4+1] = 1;
                out[i*4+2] = 1;
                out[i*4+3] = 1;
                break;
            case '8':
                out[i*4]   = 1;
                out[i*4+1] = 0;
                out[i*4+2] = 0;
                out[i*4+3] = 0;
                break;
            case '9':
                out[i*4]   = 1;
                out[i*4+1] = 0;
                out[i*4+2] = 0;
                out[i*4+3] = 1;
                break;
            case 'A':
                out[i*4]   = 1;
                out[i*4+1] = 0;
                out[i*4+2] = 1;
                out[i*4+3] = 0;
                break;
            case 'B':
                out[i*4]   = 1;
                out[i*4+1] = 0;
                out[i*4+2] = 1;
                out[i*4+3] = 1;
                break;
            case 'C':
                out[i*4]   = 1;
                out[i*4+1] = 1;
                out[i*4+2] = 0;
                out[i*4+3] = 0;
                break;
            case 'D':
                out[i*4]   = 1;
                out[i*4+1] = 1;
                out[i*4+2] = 0;
                out[i*4+3] = 1;
                break;
            case 'E':
                out[i*4]   = 1;
                out[i*4+1] = 1;
                out[i*4+2] = 1;
                out[i*4+3] = 0;
                break;
            case 'F':
                out[i*4]   = 1;
                out[i*4+1] = 1;
                out[i*4+2] = 1;
                out[i*4+3] = 1;
                break;
        }
    }
    return out;
};

bit* chars2block(char* in){
    bit* out = (bit*)calloc(64, sizeof(bit));
    for (int i = 0; i < 8; ++i){
        bit* num = char2bits(8, (unsigned int)in[i]);
        for (int j = 0; j < 8; ++j){
            out[i*8+j] = num[j];
        }
    }
    return out;
}

char* block2chars(bit* in){
    char* out = (char*)calloc(8, sizeof(char));
    for (int i = 0; i < 8; ++i){
        out[i] = bits2num(8, &in[i*8]);
    }
    return out;
}