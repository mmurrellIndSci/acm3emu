#include "../../include/instructions/sub-instructions.h"
#include "../../include/instructions/add-instructions.h"
#include "../../include/operations/conditional-operations.h"
#include "../../include/operations/shift-operations.h"
#include "../../include/util/bitmasks.h"

#pragma region 
//16bit
void RSB_Imm_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction:	Reverse Subtract from 0
	// OpCode:		010000|1001|Rn(5-3)|Rd(2-0)
	// Class:		Data Processing
	uint_fast8_t rn = (ins->low & BITM_MULTI_5) >> 3;
	uint_fast8_t rd = (ins->low & BITM_MULTI_2);
	uint32_t carry = 1;
	uint32_t overflow = 0;

	m3->r[rd] = AddWithCarry(~(m3->r[rn]), 0, &carry, &overflow);

	if (!InITBlock(m3)) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (!InITBlock(m3))
		printf("\nRSBS   R%d, R%d, 0x0", rd, rn);
	else
		printf("\nRSB   R%d, R%d, 0x0", rd, rn);
#endif // !
}
void SBC_Reg_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract with Carry
	// Opcode:		010000 0110 Rm(5-3) Rdn(2-0)
	// Class:		Data Processing
	
	uint_fast8_t rm = (ins->low & BITM_MULTI_5) >> 3;
	uint_fast8_t rdn = (ins->low & BITM_MULTI_2);
	uint32_t carry = m3->psr.c;
	uint32_t overflow = 0;

	m3->r[rdn] = AddWithCarry(m3->r[rdn], ~m3->r[rm], &carry, &overflow);

	if (!InITBlock(m3)) {
		m3->psr.n = (m3->r[rdn] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rdn] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (!InITBlock(m3))
		printf("\nSBC   R%d, R%d, R%d", rdn, rdn, rm);
	else
		printf("\nSBC   R%d, R%d, R%d", rdn, rdn, rm);
#endif // !
}

void SUB_Imm_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract 3-bit Immediate
	// Opcode:		000 11 1 1 imm3(8-6) Rn(5-3) Rd(2-0)
	// Class:		Shift Immediate

	uint16_t imm3 = (ins->low & BITM_MULTI_8) >> 6;
	uint8_t rn = (ins->low & BITM_MULTI_5) >> 3;
	uint8_t rd = (ins->low & BITM_MULTI_2);

	uint32_t carry = 1;
	uint32_t overflow = 0;
	m3->r[rd] = AddWithCarry(m3->r[rn], ~imm3, &carry, &overflow);

	if (!InITBlock(m3)) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if (!InITBlock(m3))
		printf("\nSUBS   R%d, R%d, %#X", rd, rn, imm3);
	else
		printf("\nSUB   R%d, R%d, %#X", rd, rn, imm3);
#endif // !
}
void SUB_Imm_T2(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract 8-bit Immediate
	// Opcode:		001 11 Rdn(10-8) imm8(7-0)
	// Class:		Shift Immediate

	uint16_t rdn = (ins->low & BITM_MULTI_10) >> 8;
	uint16_t imm8 = (ins->low & BITM_MULTI_7);

	uint32_t carry = 1;
	uint32_t overflow = 0;
	m3->r[rdn] = AddWithCarry(m3->r[rdn], ~imm8, &carry, &overflow);

	if (!InITBlock(m3)) {
		m3->psr.n = (m3->r[rdn] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rdn] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if (!InITBlock(m3))
		printf("\nSUBS   R%d, %#X", rdn, imm8 );
	else
		printf("\nSUB   R%d, %#X", rdn, imm8);

#endif // ! 
}
void SUB_Reg_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract Register
	// Opcode:		000 11 0 1 Rm(8-6) Rn(5-3) Rd(2-0)
	// Class:		Shift Immediate

	uint_fast16_t rd = (ins->low & BITM_MULTI_2);
	uint_fast8_t  rn = (ins->low & BITM_MULTI_5) >> 3;
	uint_fast8_t  rm = (ins->low & BITM_MULTI_8) >> 6;

	uint32_t carry = 1;
	uint32_t overflow = 0;
	m3->r[rd] = AddWithCarry(m3->r[rn], ~m3->r[rm], &carry, &overflow);

	if (!InITBlock(m3)) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if (!InITBlock(m3))
		printf("\nSUBS   R%d, R%d, R%d", rd, rn, rm);
	else
		printf("\nSUB   R%d, R%d, R%d", rd, rn, rm);
#endif // !
}
void SUB_SMI_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtraction Stack Pointer minus Immediate
	// Opcode:		1011 0000 1 imm7(6-0)
	// Class:		Misc 16-bit Instructions

	uint32_t imm7 = (ins->low & BITM_MULTI_6) << 2;
	uint32_t carry = 1;
	uint32_t overflow = 0;
	m3->sp = AddWithCarry(m3->sp, ~imm7, &carry, &overflow);

#ifdef DISPLAY
	printf("\nSUB   SP, SP, %#X", imm7);
#endif // DISPLAY
}
#pragma endregion //16bit

#pragma region //32bit
void RSB_Imm_T2(const Instruction* ins, StateARMCortexM3* m3)
{	
	// Instruction: Reverse Subtract Immediate (12-bit)
	// Opcode:		11110 i(10) 0 1110 S(4) Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm8(7-0)
	// Class:		Data Processing (Modified Immediate)

	uint_fast8_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint_fast8_t s = (ins->high & BITM_SINGLE_4) >> 4;
	uint_fast8_t rn = (ins->high & BITM_MULTI_3);
	uint_fast8_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint_fast8_t imm8 = (ins->low & BITM_MULTI_7);

	uint32_t carry = 0;
	uint32_t overflow = 0;

	uint_fast16_t imm12 = imm8 | (imm3 << 8) | (i << 11);
	uint32_t imm32 = ThumbExpandImmWithCarry(imm12, &carry);
	carry = 1;
	m3->r[rd] = AddWithCarry(~(m3->r[rn]), imm32, &carry, &overflow);

	if (s == 1) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if (s)
		printf("\nRSBS   R%d, R%d, %#X", rd, rn, imm32);
	else
		printf("\nRSB   R%d, R%d, %#X", rd, rn, imm32);
#endif // !
}
void RSB_Reg_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction:	Reverse Subtract 
	// Opcode:		11101 01 1110 S(4) Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm2(7-6) type (5-4) Rm(3-0)
	// Class:		Data Processing (Shifted Register)
	
	uint_fast8_t S  = (ins->high & BITM_SINGLE_4) >> 4;
	uint_fast8_t rn = (ins->high & BITM_MULTI_3);
	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint_fast8_t rm = (ins->low & BITM_MULTI_3);

	uint_fast16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast16_t imm2 = (ins->low & BITM_MULTI_7)  >> 6;
	uint_fast16_t type = (ins->low & BITM_MULTI_5)  >> 4;
	uint_fast16_t imm5 = imm2 | (imm3 << 2);

	SRType shift_t = DecodeImmShift(type, imm5);

	uint32_t carry = 0;
	uint32_t overflow = 0;

	uint32_t shifted = Shift_C(m3->r[rm], shift_t, imm5, &carry);
	carry = 1;
	m3->r[rd] = AddWithCarry(~(m3->r[rn]), shifted, &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (S)
		printf("\nRSBS   R%d, R%d, R%d", rd, rn, rm);
	else
		printf("\nRSB   R%d, R%d, R%d", rd, rn, rm);
	if (imm5 > 0)
		DisplaySRType(shift_t, imm5);
#endif
}
void SBC_Imm_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract Immediate 12-bit
	// Opcode:		11110 i(10) 0 1011 S(4) Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm8(7-0)
	// Class:		Data Processing (Modified Immediate)
	uint_fast8_t S = (ins->high & BITM_SINGLE_4) >> 4;
	uint_fast8_t rn = (ins->high & BITM_MULTI_3);
	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;

	uint_fast16_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint_fast16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast16_t imm8 = (ins->low & BITM_MULTI_7);
	uint_fast16_t imm12 = imm8 | (imm3 << 8) | (i << 11);

	uint32_t carry = m3->psr.c;
	uint32_t overflow = 0;
	uint_fast32_t imm32 = ThumbExpandImmWithCarry(imm12, &carry);
	m3->r[rd] = AddWithCarry(m3->r[rn], ~(imm32), &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (S)
		printf("\nSBCS   R%d, R%d, %#X", rd, rn, imm32);
	else
		printf("\nSBC   R%d, R%d, %#X", rd, rn, imm32);
#endif // !
}
void SBC_Reg_T2(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction:	Subtract Register
	// Opcode:		11101 01 1011 S(4) Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm2(7-6) type(5-4) Rm(3-0)
	// Class:		Data Processing (Shifted Register)
	uint_fast8_t S = (ins->high & BITM_SINGLE_4) >> 4;
	
	uint_fast8_t rn = (ins->high & BITM_MULTI_3);
	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint_fast8_t rm = (ins->low & BITM_MULTI_3);

	uint_fast16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast16_t imm2 = (ins->low & BITM_MULTI_7) >> 6;
	uint_fast16_t type = (ins->low & BITM_MULTI_5) >> 4;

	uint_fast16_t imm5 = imm2 | (imm3 << 2);
	SRType shift_t = DecodeImmShift(type, imm5);

	uint32_t carry = m3->psr.c;
	uint32_t overflow = m3->psr.v;

	uint32_t shifted = Shift_C(m3->r[rm], shift_t, imm5, &carry);
	m3->r[rd] = AddWithCarry(m3->r[rn], ~(shifted), &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (S)
		printf("\nSBCS   R%d, R%d, R%d", rd, rn, rm);
	else
		printf("\nSBC   R%d, R%d, R%d", rd, rn, rm);
	if (imm5 > 0)
		DisplaySRType(shift_t, imm5);
#endif

}
void SUB_Imm_T3(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtraction Immmediate (12 bit thumb)
	// Opcode:		11110 i(10) 0 1101 s(4) Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm8(7-0)
	// Class:		Data Processing (modified Immediate)

	//Check if its a stack pointer
	uint_fast16_t rn = (ins->high & BITM_MULTI_3);
	if (rn == 13) {	SUB_SMI_T2(ins, m3); return; }

	//Check if 
	uint_fast16_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint_fast8_t S = (ins->high & BITM_SINGLE_4) >> 4;
	if (rd == 15 && S) {return;}//CMP (immediate);

	uint_fast16_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint_fast16_t imm8 = (ins->low & BITM_MULTI_7);
	uint_fast16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;


	uint16_t imm12 = (imm8) | (imm3 << 8) | (i << 11);
	uint32_t carry = m3->psr.c;
	uint32_t imm32 = ThumbExpandImmWithCarry(imm12, &carry);
	carry = 1;
	uint32_t overflow = 0;

	m3->r[rd] = AddWithCarry(m3->r[rn], ~imm32, &carry, &overflow);

	if (S == 1) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if(S)
		printf("\nSUBS   R%d, R%d, %#X", rd, rn, imm32);
	else 
		printf("\nSUB   R%d, R%d, %#X", rd, rn, imm32);
#endif // !
}
void SUB_Imm_T4(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract Wide (12-bit)
	// Opcode: 1110 i(10) 1 0101 0 Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm8(7-0)
	// Class: Data Processing (plain binary immediate)

	// TODO: if RD == 1111 then ADR
	// TODO: if RN == '1101' then SUB (SP Minus Immediate)

	uint_fast8_t rn = (ins->high & BITM_MULTI_3);
	if (rn == 13) {
		SUB_SMI_T3(ins, m3);
		return;
	}

	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;
	if (rd == 15) {
		//ADR_SOMETHING_SOMETHINGELSE(ins,m3);
		return;
	}

	uint8_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint8_t imm8 = (ins->low);// & BITM_MULTI_7);

	uint16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;

	uint32_t imm32 = (imm8) | (imm3 << 8) | (i << 11);
	uint32_t carry = 1;
	uint32_t overflow = 0;

	m3->r[rd] = AddWithCarry(m3->r[rn], ~imm32, &carry, &overflow);

#ifdef DISPLAY
	printf("\nSUBW   R%d, R%d, %#X", rd, rn, imm32);
#endif // !
}
void SUB_Reg_T2(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract (register)
	// Opcode:		11101 01 1101 S(4) Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm2(7-6) type(5-4) Rm(3-0)
	// Class:		Data Processing (Shifted Register)

	uint_fast8_t S = (ins->high & BITM_SINGLE_4) >> 4;
	uint_fast8_t rn = (ins->high & BITM_MULTI_3);
	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint_fast8_t rm = (ins->low & BITM_MULTI_3);

	uint_fast16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast16_t imm2 = (ins->low & BITM_MULTI_7) >> 6;
	uint_fast16_t type = (ins->low & BITM_MULTI_5) >> 4;
	uint_fast16_t imm5 = imm2 | (imm3 << 2);

	SRType shift_t = DecodeImmShift(type, imm5);
	uint32_t carry = m3->psr.c;
	uint32_t overflow = 0;
	uint32_t shifted = Shift_C(m3->r[rm], shift_t, imm5, &carry);
	carry = 1;
	m3->r[rd] = AddWithCarry(m3->r[rn], ~shifted, &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (S)
		printf("\nSUBS   R%d, R%d, R%d", rd, rn, rm);
	else
		printf("\nSUB   R%d, R%d, R%d", rd, rn, rm);
	if (imm5 > 0)
		DisplaySRType(shift_t, imm5);
#endif


}
void SUB_SMI_T2(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract Stack Pointer Minus Immediate (thumb)
	// Opcode:		11110 i(10) 0 1101 S(4) 1101 0 | imm3(14-12) Rd(11-8) imm8(7-0)
	// Class:		SUB_IMM_T3 (Rn == 13)
	uint32_t carry = 1;
	uint32_t overflow = 0;

	uint_fast16_t i		= (ins->high & BITM_SINGLE_10) >> 10;
	uint_fast16_t imm3	= (ins->low & BITM_MULTI_14) >> 12;
	uint_fast16_t imm8	= (ins->low & BITM_MULTI_7);
	uint_fast16_t imm12 = imm8 | (imm3 << 8) | (i << 11);
	uint_fast32_t imm32 = ThumbExpandImmWithCarry(imm12, &carry);
	carry = 1;

	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint_fast8_t S = (ins->high & BITM_SINGLE_4);

	m3->r[rd] = AddWithCarry(m3->sp, ~imm32, &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if (S)
		printf("\nSUBS   R%d, SP, %#X", rd, imm32);
	else
		printf("\nSUB   R%d, SP, %#X", rd, imm32);
#endif // DISPLAY
}
void SUB_SMI_T3(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract Stack Pointer Minus Immediate (wide)
	// Opcode:		11110 i(10) 1 0101 0 1101 0 | imm3(14-12) Rd(11-8) imm8(7-0)
	// Class:		SUB_IMM_T4 (Rn == 13)
	uint32_t carry = 1;
	uint32_t overflow = 0;

	uint_fast16_t i = (ins->high & BITM_SINGLE_10) >> 10;
	uint_fast16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast16_t imm8 = (ins->low & BITM_MULTI_7);
	uint_fast32_t imm32 = imm8 | (imm3 << 8) | (i << 11);

	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint_fast8_t S = (ins->high & BITM_SINGLE_4);

	m3->r[rd] = AddWithCarry(m3->sp, ~imm32, &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if (S)
		printf("\nSUBS   R%d, SP, %#X", rd, imm32);
	else
		printf("\nSUB   R%d, SP, %#X", rd, imm32);
#endif // DISPLAY

}
void SUB_SMR_T1(const Instruction* ins, StateARMCortexM3* m3)
{
	// Instruction: Subtract Stack Pointer Minus Register
	// Opcode:		11101 0 1 1101 S(4) 1101 | 0 imm3(14-12) Rd(11-8) imm2(7-6) type(5-4) Rm(3-0)
	// Class:		SUB_Reg_T2 (Rn == 13)

	uint_fast16_t imm3 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast16_t imm2 = (ins->low & BITM_MULTI_7) >> 6;
	uint_fast16_t type = (ins->low & BITM_MULTI_5) >> 4;
	uint_fast16_t imm5 = imm2 | (imm3 << 2);

	uint_fast8_t rd = (ins->low & BITM_MULTI_11) >> 8;
	uint_fast8_t rm = (ins->low & BITM_MULTI_3);

	uint_fast8_t S = (ins->high & BITM_SINGLE_4) >> 4;

	uint32_t carry = m3->psr.c;
	uint32_t overflow = 0;

	SRType shift_t = DecodeImmShift(type, imm5);
	uint32_t shifted = Shift_C(m3->r[rm], shift_t, imm3, &carry);
	carry = 1;
	m3->r[rd] = AddWithCarry(m3->sp, ~shifted, &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if (S)
		printf("\nSUBS   R%d, SP, R%d", rd, rm);
	else
		printf("\nSUB   R%d, SP, R%d", rd, rm);
	if (imm5 > 0)
		DisplaySRType(shift_t, imm5);
#endif
}
#pragma endregion //32bit