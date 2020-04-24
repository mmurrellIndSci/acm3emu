#ifndef STRUCTS_H_
#define STRUCTS_H_
#include <stdint.h>
//#include "bitmasks.h"

//Program Status Register
typedef struct PSR {
	//Application PSR (APSR)
	uint32_t n : 1;
	uint32_t z : 1;
	uint32_t c : 1;
	uint32_t v : 1;
	uint32_t q : 1;

	//Execution PSR (EPSR)
	uint32_t it : 2;
	uint32_t t : 1;
	uint32_t reserved : 8;
	uint32_t it2 : 6;
	uint32_t r2 : 1;

	//Interrupt PSR (IPSR)
	uint32_t isr : 9;
}PSR;


typedef struct StateARMCortexM3 {
	uint32_t r[13];
	uint32_t sp;
	uint32_t lr;
	uint32_t pc;
	PSR		 psr;
	uint32_t eof;

	uint8_t mem[0xfffff];

} StateARMCortexM3;

typedef struct Intel32BitHex {
	uint8_t  recordLength;
	uint16_t loadOffset;
	uint8_t  recordType;
	uint8_t  checkSum;
	uint8_t  data[32];
} Intel32BitHex;

typedef struct Instruction {
	uint_fast8_t size;
	uint32_t high : 16;
	uint32_t low : 16;
} Instruction;


#endif // !STRUCTS_H_