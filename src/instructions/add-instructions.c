#include "../../include/instructions/add-instructions.h"
#include "../../include/operations/shift-operations.h"
#include "../../include/operations/conditional-operations.h"
#include "../../include/util/bitmasks.h"

uint32_t AddWithCarry(uint32_t a, uint32_t b, uint32_t* carry_in, uint32_t* overflow) {
	
	// The easy part... a + b + c = result
	uint64_t result64 = ((uint64_t)a + (uint64_t)b + (uint64_t)*carry_in);
	uint32_t result = result64;

	// A Carry happens when: Adding two 32bit numbers requires a 33rd bit
	*carry_in = result64 >> 32;

	//An overflow happens when:
	//- Adding two positives results in a negative
	//- Subtracting a negative from a negative results in a positive 
	uint_fast8_t absign = ((a >> 31) == (b >> 31));
	uint_fast8_t brsign = ((b >> 31) != (result >> 31));
	*overflow = absign && brsign;
	return		result;
}

#pragma region //16bit
void ADC_Reg_T1(const Instruction* inst, StateARMCortexM3* m3) {
	//010000|0101|Rm_|Rdn
	uint32_t rdn = (inst->low & BITM_MULTI_2);
	uint32_t rm  = (inst->low & BITM_MULTI_5) >> 3;

	uint32_t carry = m3->psr.c;
	uint32_t overflow = m3->psr.v;
	//uint32_t shifted = Shift_C(rm, SRType_LSL, 0, &carry); shifts only for T2

	m3->r[rdn] = AddWithCarry(m3->r[rdn], m3->r[rm], &carry, &overflow);

	if (!InITBlock(m3)) {
		m3->psr.n = (m3->r[rdn] & BITM_SINGLE_31) >> 31;
		m3->psr.c = carry;
		m3->psr.v = overflow;
		m3->psr.z = (m3->r[rdn] == 0);
	}

#ifdef DISPLAY
	if (!InITBlock(m3))
		printf("\nADCS   R%d, R%d, R%d", rdn, rdn, rm);
	else
		printf("\nADC   R%d,  R%d, R%d", rdn, rdn, rm);
	//DisplaySRType(SRType_LSL, 0);
#endif
}

void ADD_Imm_T1(const Instruction* inst, StateARMCortexM3* m3) {
	//000 11 1 0 imm3(3) rn(3) rd(3)
	uint32_t imm3 = (inst->low & BITM_MULTI_8) >> 6;
	uint16_t rn = (inst->low & BITM_MULTI_5) >> 3;
	uint16_t rd = (inst->low & BITM_MULTI_2);

	uint32_t carry = 0;
	uint32_t overflow = 0;

	m3->r[rd] = AddWithCarry(m3->r[rn], imm3, &carry, &overflow);
	if (!InITBlock(m3)) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if(!InITBlock(m3))
		printf("\nADDS   R%d, R%d, %#X", rd, rn, imm3);
	else
		printf("\nADD   R%d, R%d, %#X", rd, rn, imm3);	
#endif

}
void ADD_Imm_T2(const Instruction* inst, StateARMCortexM3* m3) {
	// Class: Shift (imm)
	// 001 10 rdn(10-8) imm8(7-0)
	uint32_t rd = (inst->low & BITM_MULTI_10) >> 8;
	uint32_t imm8 = inst->low & BITM_MULTI_7;

	uint32_t carry = 0;
	uint32_t overflow = 0;

	m3->r[rd] = AddWithCarry(m3->r[rd], imm8, &carry, &overflow);
	if (!InITBlock(m3)) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (InITBlock(m3))
		printf("\nADD   R%d, %#X", rd, imm8);
	else
		printf("\nADDS   R%d, %#X", rd, imm8);
#endif
}
void ADD_Reg_T1(const Instruction* inst, StateARMCortexM3* m3) {
	// Class: 
	// 000 11 0 0 Rm(8-6) Rn(5-3) Rd(2-0)
	
	uint32_t rm = (inst->low & BITM_MULTI_8) >> 6;
	uint32_t rn = (inst->low & BITM_MULTI_3) >> 3;
	uint32_t rd = (inst->low & BITM_MULTI_2);

	uint32_t carry = m3->psr.c;
	uint32_t overflow = 0;
	//uint32_t shifted = Shift_C(m3->r[rm], SRType_LSL, 0, &carry); shifts only for T3
			 carry = 0;

	m3->r[rd] = AddWithCarry(m3->r[rd], m3->r[rm], &carry, &overflow);
	// if d == 15 then ALUWritePC(result)
	if (!InITBlock(m3)) {
		m3->psr.n = m3->r[rd] & BITM_SINGLE_31 >> 31;
		m3->psr.c = carry;
		m3->psr.v = overflow;
		m3->psr.z = (m3->r[rd] == 0);
	}

#ifdef DISPLAY
	if (InITBlock(m3))
		printf("\nADDS   R%d, R%d, R%d", rd, rn, rm);
	else
		printf("\nADD   R%d,  R%d, R%d", rd, rn, rm);
	//DisplaySRType(SRType_LSL, 0);
#endif
}
void ADD_Reg_T2(const Instruction* inst, StateARMCortexM3* m3) {
	// Class: Special data and branch and exchange // No Flags
	// 010001 00 DN(7) Rm(6-3) Rdn(2-0)

	// TODO: if d == 1101 || rm == 1101 then ADD(SP plus register)
	// TODO: if d == 15 && initblock && ! lastinitblock then UNPREDICTABLE
	// TODO: if d == 15 && m == 15 then UNPREDICTABLE

	uint32_t dn = (inst->low & BITM_SINGLE_7) >> 7;
	uint32_t rm = (inst->low & BITM_MULTI_6) >> 3;
	uint32_t rdn = (inst->low & BITM_MULTI_2);

	uint32_t d = rdn | (dn << 3);
	uint32_t n = rdn | (dn << 3);

	if (rm == 13) {
		ADD_SPR_T1(inst, m3);
		return;
	}
	if (d == 13) {
		ADD_SPR_T2(inst, m3);
		return;
	}
	uint32_t carry = m3->psr.c;
	uint32_t overflow = 0;
	//uint32_t shifted = Shift_C(m3->r[rm], SRType_LSL, 0, &carry); shifts are only for t3
	carry = 0;
	m3->r[d] = AddWithCarry(m3->r[n], m3->r[rm], &carry, &overflow);

#ifdef DISPLAY
		printf("\nADD   R%d,  R%d, R%d", d, n, rm);
		//DisplaySRType(SRType_LSL, 0);
#endif
}

void ADD_SPI_T1(const Instruction* inst, StateARMCortexM3* m3)
{
	// Class: Generate SP-relative address | 10101x(42/43) also Misc 16???
	// 1010 1 Rd(10-8) imm8(7-0)
	uint32_t rd = (inst->low & BITM_MULTI_10) >> 8;
	uint32_t imm8 = (inst->low & BITM_MULTI_7) << 2;
	
	uint32_t carry = 0; 
	uint32_t overflow = 0;

	m3->r[rd] = AddWithCarry(m3->sp, imm8, &carry, &overflow);
	
	//Set flags == false :)

#ifdef DISPLAY
	printf("\nADD   R%d,  SP, %#X", rd, imm8);
#endif
}
void ADD_SPI_T2(const Instruction* inst, StateARMCortexM3* m3)
{
	// Class: Misc 16 bit inst
	// 1011 0000 0 imm7(6-0)

	uint32_t imm7 = (inst->low & BITM_MULTI_6) << 2;

	uint32_t carry = 0;
	uint32_t overflow = 0;

	m3->sp = AddWithCarry(m3->sp, imm7, &carry, &overflow);
	
	//Setflags == false :)
#ifdef DISPLAY
	printf("\nADD   SP,  SP, %#X", imm7);
#endif

}
void ADD_SPR_T1(const Instruction* inst, StateARMCortexM3* m3)
{
	// Class: ADD_Reg_T2 with Rm == 13
	// 01000100 DM(7) 1101 Rdm(2-0)
	uint_fast8_t rdm = (inst->low & BITM_MULTI_2);
	uint_fast8_t dm = (inst->low & BITM_SINGLE_7) >> 7;
	uint_fast8_t rd = rdm | (dm << 3);

	uint32_t carry = 0;
	uint32_t overflow = 0;

	//uint_fast32_t shifted = Shift_C(m3->r[rd], SRType_LSL, 0, &carry); shifts are only for T3
	m3->r[rd] = AddWithCarry(m3->sp, m3->r[rd], &carry, &overflow);
#ifdef DISPLAY
	printf("\nADD   R%d,  SP", rd );
	//DisplaySRType(SRType_LSL, 0);
#endif
}
void ADD_SPR_T2(const Instruction* inst, StateARMCortexM3* m3)
{
	// Class: ADD_Reg_T2 with Rd == 13
	// 01000100 1 Rm(6-3) 101

	uint_fast8_t rm = (inst->low & BITM_MULTI_6) >> 3;
	uint32_t carry = 0;
	uint32_t overflow = 0;

	//uint_fast32_t shifted = Shift_C(m3->r[rm], SRType_LSL, 0, &carry); shifts are only for T3
	m3->sp = AddWithCarry(m3->sp, m3->r[rm], &carry, &overflow);
#ifdef DISPLAY
	printf("\nADD   SP,  SP, R%d", rm);
	//DisplaySRType(SRType_LSL, 0);
#endif
}
#pragma endregion //16bit

#pragma region //32bit
void ADC_Imm_T1(const Instruction* inst, StateARMCortexM3* m3) {
	/*	Add With Carry (Immediate)
	*	11110|i|0|1010|S|Rn(3-0)|0|imm3(14-12)|Rd(11-8)|imm8(7-0)
	*	Adds Immediate value + register value + carry Value to Destination Register
	*/

	uint16_t S = (inst->high & BITM_SINGLE_4) >> 4;
	uint16_t i = (inst->high & BITM_SINGLE_10) >> 10;
	uint16_t Rn = (inst->high & BITM_MULTI_3);
	uint16_t imm3 = (inst->low & BITM_MULTI_14) >> 12;
	uint16_t Rd = (inst->low & BITM_MULTI_11) >> 8;
	uint16_t imm8 = (inst->low & BITM_MULTI_7);

	uint16_t imm12 = (i << 11) | (imm3 << 8) | imm8;

	uint32_t carry = m3->psr.c;
	uint32_t overflow = 0;

	uint32_t imm32 = ThumbExpandImmWithCarry(imm12, &carry);
	m3->r[Rd] = AddWithCarry(m3->r[Rn], imm32, &carry, &overflow);
	if (S) {
		m3->psr.n = (m3->r[Rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[Rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if(S)
		printf("\nADCS   R%d, R%d, %#X", Rd, Rn, imm32);
	else
		printf("\nADC   R%d, R%d, %#X", Rd, Rn, imm32);
#endif // !
}
void ADC_Reg_T2(const Instruction* inst, StateARMCortexM3* m3) {
	// Class: Data Processing shifted reg
	// 11101|01|1010|S|Rn__    0|imm3|Rd__|imm2|type|Rm__
	// 11101|01|1010|S(10)|Rn(3-0) | 0|imm3(14-12)|rd(11-8)|imm2(7-6)|type(5-4)|rm(3-0)
	uint16_t S = (inst->high & BITM_SINGLE_4)>> 4;
	uint16_t rn = (inst->high & BITM_MULTI_3);
	uint16_t imm3 = (inst->low & BITM_MULTI_14) >> 12;
	uint16_t rd = (inst->low & BITM_MULTI_11) >> 8;
	uint16_t imm2 = (inst->low & BITM_MULTI_7) >> 6;
	uint16_t type = (inst->low & BITM_MULTI_5) >> 4;
	uint16_t rm = (inst->low & BITM_MULTI_3);

	uint32_t imm5 = imm2 | (imm3 << 2);
	SRType shift_t = DecodeImmShift(type, imm5);

	uint32_t carry = m3->psr.c;
	uint32_t overflow = m3->psr.v;

	uint32_t shifted = Shift_C(m3->r[rm], shift_t, imm5, &carry);
	m3->r[rd] = AddWithCarry(m3->r[rn], shifted, &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (S)
		printf("\nADCS   R%d, R%d, R%d", rd, rn, rm);
	else
		printf("\nADC   R%d, R%d, R%d", rd, rn, rm);
	if(imm5 > 0)
		DisplaySRType(shift_t, imm5);
#endif
}

void ADD_Imm_T3(const Instruction* inst, StateARMCortexM3* m3) {
	// Class: Data Processing (modified immediate) | OP == 16/17, Rn != 15
	// 11110 i(10) 0 1000 S(4) Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm8(7-0)

	//TODO: if rd == 15 && s == 1 then CMN (immediate)
	//TODO: if rn == 13 then ADD (SP plus immediate)

	uint_fast16_t rn = (inst->high & BITM_MULTI_3);
	if (rn == 13) {	ADD_SPI_T3(inst, m3);return;}

	uint_fast16_t i = (inst->high & BITM_SINGLE_10) >> 10;
	uint_fast16_t S = (inst->high & BITM_SINGLE_4) >> 4;

	uint_fast16_t imm3 = (inst->low & BITM_MULTI_14) >> 12;

	uint_fast16_t rd = (inst->low & BITM_MULTI_11) >> 8;
	uint_fast16_t imm8 = (inst->low & BITM_MULTI_7);
	uint_fast16_t imm12 = (imm8 | (imm3 << 8) | (i << 11));

	uint32_t carry = 0;
	uint32_t overflow = 0;
	uint32_t imm32 = ThumbExpandImmWithCarry(imm12, &carry);
	carry = 0;
	m3->r[rd] = AddWithCarry(m3->r[rn], imm32, &carry, &overflow);

	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}
#ifdef DISPLAY
	if (S)
		printf("\nADDS   R%d, R%d, %#X", rd, rn, imm32);
	else
		printf("\nADD   R%d, R%d, %#X", rd, rn, imm32);
#endif
}
void ADD_Imm_T4(const Instruction* inst, StateARMCortexM3* m3) {
	// Class: Data Processing (plain binary immediate) | OP == 0, Rn != 15
	// 11110 i(10) 1 0000 0 Rn(3-0) | 0 imm3(14-12) Rd(11-8) imm8(7-0)

	// TODO: if rn == 15 then ADR
	// TODO: if rn == 13 then ADD (Sp plus immediate)
	uint_fast8_t rn = (inst->high & BITM_MULTI_3);
	if (rn == 13) {	ADD_SPI_T4(inst, m3);return;}
	uint_fast8_t imm8 = (inst->low & BITM_MULTI_7);

	uint_fast16_t i = (inst->high & BITM_SINGLE_10) >> 10;
	uint_fast16_t imm3 = (inst->low & BITM_MULTI_14) >> 12;
	uint_fast16_t rd = (inst->low & BITM_MULTI_11) >> 8;



	uint32_t imm32 = (imm8 | (imm3 << 8) | (i << 11));

	uint32_t carry = 0;
	uint32_t overflow = 0;
	m3->r[rd] = AddWithCarry(m3->r[rn], imm32, &carry, &overflow);

#ifdef DISPLAY
		printf("\nADDW   R%d, R%d, %#X", rd, rn, imm32);
#endif
}
void ADD_Reg_T3(const Instruction* inst, StateARMCortexM3* m3) {
	// Class: Data Processing Shifted Register EB00
	// 11101 01 1000 S(4) Rn(3-0) 0 imm3(14-12) Rd(11-8) imm2(7-6) type(5-4) Rm(3-0)
	uint16_t S = (inst->high & BITM_SINGLE_4) >> 4;
	uint16_t Rn = inst->high & BITM_MULTI_3;
	uint16_t imm3 = (inst->low & BITM_MULTI_14) >> 12;
	uint16_t Rd = (inst->low & BITM_MULTI_11) >> 8;
	uint16_t imm2 = (inst->low & BITM_MULTI_7) >> 6;
	uint16_t type = (inst->low & BITM_MULTI_5) >> 4;
	uint16_t Rm = inst->low & BITM_MULTI_3;

	//if(Rd == 15 && S == 1) //go to CMD(register)
	//if(Rn == 13) // go to ADD (SP Plus register)
	uint32_t imm5 = (imm3 << 2) | imm2;
	uint32_t carry = 0;
	uint32_t overflow = 0;

	SRType st = DecodeImmShift(type, imm5);
	uint32_t shifted = Shift_C(m3->r[Rm], st, imm5, &carry);


	//uint32_t res = AddWithCarry(Rn, shifted, carry, overflow);
	m3->r[Rd] = AddWithCarry(m3->r[Rn], shifted, &carry, &overflow);
	if (S == 1) {
		m3->psr.n = (m3->r[Rd] & BITM_SINGLE_31) >> 31;
		m3->psr.c = carry;
		m3->psr.v = overflow;
		m3->psr.z = (m3->r[Rd] == 0);
	}

#ifdef DISPLAY
	if(S)
		printf("\nADDS   R%d, R%d, R%d", Rd, Rn, Rm);
	else
		printf("\nADD   R%d, R%d, R%d", Rd, Rn, Rm);
	if (imm5 > 0)
		DisplaySRType(st, imm5);
#endif // !
}

void ADD_SPI_T3(const Instruction* inst, StateARMCortexM3* m3)
{
	// Class: ADD Imm (with Rn == 1101(13))
	// 11110 i(10) 0 1000 S(4) 1101 | 0 imm3(14-12) Rd(11-8) imm8(7-0)
	// TODO: if Rd == 16 && s == 1 then CMN (immediate)
	uint32_t i = (inst->high & BITM_SINGLE_10) >> 10;
	uint32_t S = (inst->high & BITM_SINGLE_4) >> 4;
	uint32_t imm3 = (inst->low & BITM_MULTI_14) >> 12;
	uint32_t rd = (inst->low & BITM_MULTI_11) >> 8;
	uint32_t imm8 = (inst->low & BITM_MULTI_7);

	uint32_t imm32 = imm8 | (imm3 << 8) | (i << 11);
	uint32_t carry = 0;
	uint32_t overflow = 0;

	imm32 =  ThumbExpandImmWithCarry(imm32, &carry);
	m3->r[rd] = AddWithCarry(m3->sp, imm32, &carry, &overflow);


	if (S) {
		m3->psr.n = (m3->r[rd] & BITM_SINGLE_31) >> 31;
		m3->psr.z = m3->r[rd] == 0;
		m3->psr.c = carry;
		m3->psr.v = overflow;
	}

#ifdef DISPLAY
	if (S)
		printf("\nADDS   R%d, SP, %#X", rd, imm32);
	else
		printf("\nADD   R%d, SP, %#X", rd, imm32);
#endif // DISPLAY

}
void ADD_SPI_T4(const Instruction* inst, StateARMCortexM3* m3)
{
	// Class: Add Imm (with Rn == 1101(13))
	// 11110 i(10) 1 0000 0 1101 | 0 imm3(14-12) Rd(11-8) imm8(7-0)
	uint32_t i = (inst->high & BITM_SINGLE_10) >> 10;
	uint32_t imm3 = (inst->low & BITM_MULTI_14) >> 12;
	uint32_t rd = (inst->low & BITM_MULTI_11) >> 8;
	uint32_t imm8 = (inst->low & BITM_MULTI_7);

	uint32_t imm32 = imm8 | (imm3 << 8) | (i << 11);
	uint32_t carry = 0;
	uint32_t overflow = 0;

	m3->r[rd] = AddWithCarry(m3->sp, imm32, &carry, &overflow);

#ifdef  DISPLAY
	printf("\nADDW   R%d, SP, %#X", rd, imm32);
#endif //  DISPLAY

}
void ADD_SPR_T3(const Instruction* inst, StateARMCortexM3* m3)
{
	// Class: ADD_Reg_T3 (with Rn == 13)
	// 11101011000 S(4) 1101 | 0 imm3(14-12) rd(11-8) imm2(7-6) type(5-4) Rm(3-0)
	uint_fast8_t S    = (inst->high & BITM_SINGLE_4) >> 4;
	uint_fast8_t imm3 = (inst->low  & BITM_MULTI_14) >> 12;
	uint_fast8_t rd   = (inst->low  & BITM_MULTI_11) >> 8;
	uint_fast8_t imm2 = (inst->low  & BITM_MULTI_7) >> 6;
	uint_fast8_t type = (inst->low  & BITM_MULTI_5) >> 4;
	uint_fast8_t rm   = (inst->low  & BITM_MULTI_3);

	uint32_t imm5 = imm2 | (imm3 << 2);
	uint32_t carry = 0;
	uint32_t overflow = 0;

	SRType shift_t =  DecodeImmShift(type, imm5);
	uint32_t shifted = Shift_C(m3->r[rm], shift_t, imm5, &carry);
	carry = 0;
	m3->r[rd] = AddWithCarry(m3->sp, shifted, &carry, &overflow);

	if (S == 1) {
		m3->psr.n = m3->r[rd] & BITM_SINGLE_31 >> 31;
		m3->psr.c = carry;
		m3->psr.v = overflow;
		m3->psr.z = (m3->r[rd] == 0);
	}

#ifdef DISPLAY
	if (S)
		printf("\nADDS   R%d, SP", rd);
	else
		printf("\nADD   R%d, SP", rd);
	if (imm5 > 0)
		DisplaySRType(shift_t, imm5);
#endif // !

}
#pragma endregion //32bit

