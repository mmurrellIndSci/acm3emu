#ifndef IF_THEN_OPERATIONS_H_
#define IF_THEN_OPERATIONS_H_
#include <stdbool.h>
#include <stdio.h>
#include "../structs.h"

extern bool InITBlock		 (const StateARMCortexM3* m3);
extern bool LastInITBlock	 (const StateARMCortexM3* m3);
extern bool ConditionsPassed (const StateARMCortexM3* m3, uint_fast8_t conditional);
extern void DisplayConditional(uint_fast8_t c);

enum Conditional
{
	EQ,// = 0x0, Equal
	NE,// = 0x1, Not Equal
	CS,// = 0x2, Carry Set
	CC,// = 0x3, Carry Clear
	MI,// = 0x4, Negative
	PL,// = 0x5, Positive or Zero
	VS,// = 0x6, Overflow
	VC,// = 0x7, No overflow
	HI,// = 0x8, Unsigned higher
	LS,// = 0x9, Unsigned lower or same
	GE,// = 0xA, Signed greater than or equal
	LT,// = 0xB, Signed less than
	GT,// = 0xC, Signed greater than
	LE,// = 0xD, Signed lessthan or equal
	AL// = 0xE,  Always
};


#endif // !IF_THEN_OPERATIONS_H_
