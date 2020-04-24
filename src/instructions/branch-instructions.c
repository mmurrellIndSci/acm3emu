#include <stdio.h>
#include "../../include/instructions/branch-instructions.h"
#include "../../include/operations/conditional-operations.h"
#include "../../include/operations/shift-operations.h"
#include "../../include/util/bitmasks.h"

#pragma region //16bit
void B_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Branch (8 bit immediate)
	// Opcode:		1101 cond(11-8) imm8(7-0)
	// Class:		Conditional Branch and Supervisor Call
	uint_fast8_t cond = (ins->low & BITM_MULTI_11) >> 8;
	if (cond == 15) {return;	}//SVC(ins, m3);			//SUPERVISORCALL if 15
	uint32_t imm32 = (ins->low & BITM_MULTI_7) << 1;
	imm32 = SignExtend(imm32, 9);
	uint32_t addr = m3->pc + imm32 + 2;
	if (!InITBlock(m3) && ConditionsPassed(m3, cond)) {
		m3->pc = addr;
		loopCounter++;
	}
#ifdef DISPLAY
	printf("\nB");
	DisplayConditional(cond);
	printf("	%#X", addr + 2);
#endif // DISPLAY
}

void B_T2(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Branch (unconditional)
	// Opcode:		11100 imm11(11-0)
	// Class:		Unconditional branch
	uint32_t imm32 = (ins->low & BITM_MULTI_10) << 1;
	imm32 = SignExtend(imm32, 12);
	uint32_t addr = m3->pc + imm32 + 2;
	if (!InITBlock(m3) && !LastInITBlock(m3)) {
		m3->pc = addr;
		//system("Pause");
	}
#ifdef DISPLAY
	printf("\nB   %#X", addr + 2);
#endif // DISPLAY
}

void BLX_T1(const Instruction* ins, StateARMCortexM3* m3)
{
}

void BX_T1(const Instruction* ins, StateARMCortexM3* m3)
{
}

#pragma endregion //16bit

#pragma region //32bit
void B_T3(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Branch (Conditional) 16bit immediate with some j's up in der
	// Opcode:		11110 S(10) cond(9-6) imm6 (5-0)  |  10 J1(13) 0 J2(11) imm11(10-0)
	// Class:		Branches and Misc Control
	uint_fast16_t J1 = (ins->low & BITM_SINGLE_13) >> 13;
	uint_fast16_t J2 = (ins->low & BITM_SINGLE_11) >> 11;
	uint_fast32_t S = (ins->high & BITM_SINGLE_10) >> 10;

	uint_fast32_t I1 = !(J1 ^ S);
	uint_fast32_t I2 = !(J2 ^ S);

	uint_fast32_t imm6 = (ins->high & BITM_MULTI_5);
	uint_fast32_t imm11 = (ins->low & BITM_MULTI_10);


	uint32_t imm32 = (imm11 << 1) | (imm6 << 12) | (I2 << 18) | (I1 << 19) | (S << 20);
	imm32 = SignExtend(imm32, 21);
	uint32_t addr = m3->pc + imm32 + 2;

	uint_fast8_t cond = (ins->high & BITM_MULTI_9) >> 6;
	if (ConditionsPassed(m3, cond)) {
		m3->pc = addr;
	}

#ifdef DISPLAY
	printf("\nB   %#X", addr + 2);
#endif // DISPLAY
}

void B_T4(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Branch (UnConditional) 
	// Opcode:		11110 S(10) imm10(9-0)  |  10 J1(13) 0 J2(11) imm11(10-0)
	// Class:		Branches and Misc Control

	uint_fast16_t J1 = (ins->low & BITM_SINGLE_13) >> 13;
	uint_fast16_t J2 = (ins->low & BITM_SINGLE_11) >> 11;
	uint_fast32_t S = (ins->high & BITM_SINGLE_10) >> 10;

	uint_fast32_t I1 = !(J1 ^ S);
	uint_fast32_t I2 = !(J2 ^ S);

	uint_fast32_t imm10 = (ins->high & BITM_MULTI_9);
	uint_fast32_t imm11 = (ins->low & BITM_MULTI_10) << 1;

	uint32_t imm32 = (imm11) | (imm10 << 12) | (I2 << 22) | (I1 << 23) | (S << 24);
	imm32 = SignExtend(imm32, 25);
	uint32_t addr = m3->pc + imm32 + 2;

	//if (ConditionsPassed(m3, cond)) {
		m3->pc = addr;
	//}



#ifdef DISPLAY
		printf("\nB   %#X", addr + 2);
#endif // DISPLAY
}
void BL_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Branch with Link
	// Opcode:		?
	// Class:		Branches and Misc Control
}
void TBB_T1(const Instruction* ins, StateARMCortexM3* m3)
{
}
#pragma endregion //32bit