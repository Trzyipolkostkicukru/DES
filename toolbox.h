#ifndef toolbox_H
#define toolbox_H

// #include <stdlib.h>
typedef char bit;
typedef char byte;
typedef unsigned int uint;
#define true 1
#define false 0


int bits2num(uint n, bit* bits);
bit* num2bits(uint n, uint num);
bit* permute(uint n, bit* bits, uint m, uint* permutation);
bit* exor(uint n, bit* a, uint* b);

#endif