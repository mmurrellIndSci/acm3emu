#include "../../include/instructions/move-instructions.h"
#include "../../include/operations/shift-operations.h"
#include "../../include/util/bitmasks.h"

#pragma region //16bit

void MOV_Imm_T1(const Instruction* ins, StateARMCortexM3* m3) {
	// Class: Shift(immediate)
	// 0 0 1 0 0 Rd(3) 	
	uint16_t rd = (ins->low & BITM_MULTI_10) >> 8;
	uint32_t imm8 = (ins->low & BITM_MULTI_7);
	m3->r[rd] = imm8;

#ifdef DISPLAY
	printf("\nMOV   R%d, %#X", rd, imm8);
#endif // DISPLAY

}

void MOV_Reg_T2(const Instruction* ins, StateARMCortexM3* m3) {
	// Class: Special Data Instructions
	// 000 00 00000 Rm(3) Rd(3)

	uint32_t rm = (ins->low & BITM_MULTI_5) >> 3;
	uint32_t rd = (ins->low & BITM_MULTI_2);
	m3->r[rd] = m3->r[rm];

#ifdef DISPLAY
	printf("\nMOV   R%d, R%d", rd, rm);
#endif // DISPLAY
}

#pragma endregion //16bit

#pragma region //32bit
void MOV_Imm_T2(const Instruction* ins, StateARMCortexM3* m3) { 
	// Class: Data Processing Mod Immediate
	// 11110 i(1) 0 0010 S(4) 1111 | 0 imm3(14-12) Rd(11-8) imm8(7-0)

	uint16_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint16_t imm8 = (ins->low & BITM_MULTI_7);
	uint32_t imm12 = imm8 | (imm3 << 8) | (i << 11);

	uint32_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint32_t carry = m3->psr.c;
	uint32_t immExp = ThumbExpandImmWithCarry(imm12, &carry);

	m3->r[rd] = immExp;
	
#ifdef DISPLAY
	printf("\nMOV   R%d, %#X", rd, immExp);
#endif // DISPLAY
}

void MOV_Imm_T3(const Instruction* ins, StateARMCortexM3* m3)
{
	//Class: Data Processing Plain Binary Imm
	// 11110 i 10 0 1 0 0 imm4(3-0) | 0 imm3(14-12) Rd(11-8) imm8(7-0)
	uint32_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint16_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint16_t imm4 = (ins->high & BITM_MULTI_3);
	uint16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint16_t imm8 = ins->low & BITM_MULTI_7;
	uint16_t imm32 = imm8 | (imm3 << 8) | (i << 11) | (imm4 << 12);

	m3->r[rd] = imm32;

#ifdef DISPLAY
	printf("\nMOV   R%d, %#X", rd, imm32);
#endif // DISPLAY

}

void MOVT(const Instruction* ins, StateARMCortexM3* m3)
{
	// Class: Data Procesing (Plain Binary Immediate) : OP = 01100(12)
	// 11110 i(10) 10 1 1 0 0 imm4(3-0) | 0 imm3(14-12) Rd(11-8) imm8(7-0)
	uint_fast16_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint_fast16_t imm4 = (ins->high & BITM_MULTI_3);
	uint_fast16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast16_t imm8 = (ins->low & BITM_MULTI_7);

	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;

	//imm16 = imm4:i:imm3:imm8
	uint_fast16_t imm16 = imm8 | (imm3 << 8) | (i << 11) | (imm4 << 12);
	m3->r[rd] |= (imm16 << 16);

#ifdef DISPLAY
	printf("\nMOVT   R%d, %#X", rd, imm16);
#endif // DISPLAY
}

void MVN_Imm_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Class: Data Processing Mod Imm
	// 11110 i(10) 0 0011 S(4) 1111 | 0 imm3(14-12) Rd(11-8) Imm8(7-0)

	uint16_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint16_t imm8 = (ins->low & BITM_MULTI_7);
	uint32_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint16_t S = (ins->high & BITM_SINGLE_4) >> 4;
	imm8 |= (imm3 << 8) | (i << 11);

	uint32_t carry = 0;
	uint32_t imm12 = ThumbExpandImmWithCarry(imm8, &carry);
	m3->r[rd] = ~imm12;
	if (S) {
		m3->psr.c = carry;
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
	}

#ifdef DISPLAY
	printf("\nMVN   R%d, %#X", rd, imm12);
#endif // DISPLAY
}
#pragma endregion //32bit