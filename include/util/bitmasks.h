#include <stdint.h>

//BM_isolate16\[(?<val>\d\d)\]
//BITM_MULTI_${val}
#define BITM_SINGLE_0  0b1
#define BITM_SINGLE_1  0b10
#define BITM_SINGLE_2  0b100
#define BITM_SINGLE_3  0b1000
#define BITM_SINGLE_4  0b10000
#define BITM_SINGLE_5  0b100000
#define BITM_SINGLE_6  0b1000000
#define BITM_SINGLE_7  0b10000000
#define BITM_SINGLE_8  0b100000000
#define BITM_SINGLE_9  0b1000000000
#define BITM_SINGLE_10 0b10000000000
#define BITM_SINGLE_11 0b100000000000
#define BITM_SINGLE_12 0b1000000000000
#define BITM_SINGLE_13 0b10000000000000
#define BITM_SINGLE_14 0b100000000000000
#define BITM_SINGLE_15 0b1000000000000000
#define BITM_SINGLE_16 0b10000000000000000
#define BITM_SINGLE_17 0b100000000000000000
#define BITM_SINGLE_18 0b1000000000000000000
#define BITM_SINGLE_19 0b10000000000000000000
#define BITM_SINGLE_20 0b100000000000000000000
#define BITM_SINGLE_21 0b1000000000000000000000
#define BITM_SINGLE_22 0b10000000000000000000000
#define BITM_SINGLE_23 0b100000000000000000000000
#define BITM_SINGLE_24 0b1000000000000000000000000
#define BITM_SINGLE_25 0b10000000000000000000000000
#define BITM_SINGLE_26 0b100000000000000000000000000
#define BITM_SINGLE_27 0b1000000000000000000000000000
#define BITM_SINGLE_28 0b10000000000000000000000000000
#define BITM_SINGLE_29 0b100000000000000000000000000000
#define BITM_SINGLE_30 0b1000000000000000000000000000000
#define BITM_SINGLE_31 0b10000000000000000000000000000000

#define BITM_MULTI_0  0b1
#define BITM_MULTI_1  0b11
#define BITM_MULTI_2  0b111
#define BITM_MULTI_3  0b1111
#define BITM_MULTI_4  0b11111
#define BITM_MULTI_5  0b111111
#define BITM_MULTI_6  0b1111111
#define BITM_MULTI_7  0b11111111
#define BITM_MULTI_8  0b111111111
#define BITM_MULTI_9  0b1111111111
#define BITM_MULTI_10 0b11111111111
#define BITM_MULTI_11 0b111111111111
#define BITM_MULTI_12 0b1111111111111
#define BITM_MULTI_13 0b11111111111111
#define BITM_MULTI_14 0b111111111111111
#define BITM_MULTI_15 0b1111111111111111
#define BITM_MULTI_16 0b11111111111111111
#define BITM_MULTI_17 0b111111111111111111
#define BITM_MULTI_18 0b1111111111111111111
#define BITM_MULTI_19 0b11111111111111111111
#define BITM_MULTI_20 0b111111111111111111111
#define BITM_MULTI_21 0b1111111111111111111111
#define BITM_MULTI_22 0b11111111111111111111111
#define BITM_MULTI_23 0b111111111111111111111111
#define BITM_MULTI_24 0b1111111111111111111111111
#define BITM_MULTI_25 0b11111111111111111111111111
#define BITM_MULTI_26 0b111111111111111111111111111
#define BITM_MULTI_27 0b1111111111111111111111111111
#define BITM_MULTI_28 0b11111111111111111111111111111
#define BITM_MULTI_29 0b111111111111111111111111111111
#define BITM_MULTI_30 0b1111111111111111111111111111111
#define BITM_MULTI_31 0b11111111111111111111111111111111

extern const uint_fast16_t bm_Isolate16[16];
extern const uint_fast32_t bm_Isolate32[32];

#define MAXLOOP 10
extern int loopCounter;