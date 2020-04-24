#include "../../include/operations/shift-operations.h"
#include "../../include/util/bitmasks.h"
#include <assert.h>
// Display the shifted type
void DisplaySRType(SRType t, uint32_t shifted) {
	switch (t)
	{
	case SRType_ASR: printf(", ASR, %#X", shifted); break;
	case SRType_LSL: printf(", LSL, %#X", shifted); break;
	case SRType_LSR: printf(", LSR, %#X", shifted); break;
	case SRType_ROR: printf(", ROR, %#X", shifted); break;
	case SRType_RRX: printf(", RRX, %#X", shifted); break;
	default: break;
	}
}

//Logical Shift Left (with carry)
uint32_t LSL_C(uint32_t bitsN, uint32_t shift, uint32_t* carrybit) {
	assert(shift > 0);
	uint32_t result = bitsN << (shift - 1);
	*carrybit = (result & BITM_SINGLE_31) >> 31;
	return result << 1;

}

//Logical Shift Right (with carry)
uint32_t LSR_C(uint32_t bitsN, uint32_t shift, uint32_t* carrybit) {
	assert(shift > 0);
	uint32_t result = bitsN >> (shift - 1);
	*carrybit = (result & BITM_SINGLE_0);
	return result >> 1;
}

//Arithmetic Shift Right (with carry) //if negative, carry the negative, if positive just do a ROR
uint32_t ASR_C(uint32_t bitsN, uint32_t shift, uint32_t* carrybit) {
	assert(shift > 0);
	//uint32_t extended = SignExtend(bitsN, shift);// bitsN >> (shift - 1);
	uint32_t result = bitsN >> (shift - 1);
	*carrybit = (result & BITM_SINGLE_31 >> 31); 
	uint32_t topBits = UINT32_MAX >> (32 - shift);
	return (topBits | (result >> 1));
}

//Rotate Right (with carry)
uint32_t ROR_C(uint32_t bitsN, uint32_t shift, uint32_t* carrybit) {
	assert(shift != 0);
	uint32_t result = (bitsN >> shift) | (bitsN << (32 - shift));
	*carrybit = (result & BITM_SINGLE_31) >> 31;
	return result;
}

//Rotate Right With Extend (with carry)
uint32_t RRX_C(uint32_t bitsN, uint32_t* carrybit) {
	uint32_t result = (bitsN >> 1) | (*carrybit << 31);
	*carrybit = bitsN & BITM_SINGLE_0;
	return result;
}

uint32_t Shift_C(uint32_t rm, SRType st, uint32_t sn, uint32_t* c) {
	if (sn == 0)
		return rm;
	else {
		uint32_t result = 0;
		switch (st)
		{
		case SRType_LSL:
			result = LSL_C(rm, sn, c);
			break;
		case SRType_LSR:
			result = LSR_C(rm, sn, c);
			break;
		case SRType_ASR:
			result = ASR_C(rm, sn, c);
			break;
		case SRType_ROR:
			result = ROR_C(rm, sn, c);
			break;
		case SRType_RRX:
			result = RRX_C(rm, c);
			break;
		default:
			break;
		}

		return result;
	}
}



//Zero Extend: Extend bitstring to left with zero bits
uint32_t ZeroExtend(uint16_t imm12, uint16_t len)
{

}

//https://graphics.stanford.edu/~seander/bithacks.html#VariableSignExtend
uint32_t SignExtend(const uint32_t imm12, const uint16_t len)
{
	uint32_t const m = 1U << (len - 1);
	uint32_t r =  (imm12 ^ m) - m;
	return r;
}

//Thumb Expand Immediate (with carry)
uint32_t ThumbExpandImmWithCarry(uint16_t imm12, uint32_t* c_in) {
	uint16_t bit11n10 = imm12 >> 10;
	uint16_t bit9n8 = (imm12 & BITM_MULTI_9) >> 8;
	uint16_t bit7to0 = imm12 & BITM_MULTI_7;
	uint32_t imm32 = 0;
	if (bit11n10 == 0) {
		switch (bit9n8)
		{
		case 0:
			imm32 = bit7to0;//ZeroExtend(bit7to0, 32);
			break;
		case 1:
			imm32 = bit7to0 | (bit7to0 << 16);
			break;
		case 2:
			imm32 |= (bit7to0 << 24) | (bit7to0 << 8);
			break;
		case 3:
			imm32 = bit7to0 | (bit7to0 << 8) | (bit7to0 << 16) | (bit7to0 << 24);
			break;
		default:
			break;
		}
	}
	else {
		imm32 = bit7to0 | BITM_SINGLE_7;
		uint32_t bit11to7 = imm12 >> 7;
		imm32 = ROR_C(imm32, bit11to7, c_in);
	}
	return imm32;
}

//Decode Imm shift idk why im giving this a commented title its legit uselss rn tbh
SRType DecodeImmShift(uint16_t type, uint16_t imm5) {
	SRType t = SRType_None;
	switch (type)
	{
	case 0:
		t = SRType_LSL;
		break;
	case 1:
		t = SRType_LSR;
		break;
	case 2:
		t = SRType_ASR;
		break;
	case 3:
		t = (imm5 == 0) ? SRType_RRX : SRType_ROR;
		break;
	default:
		break;
	}

	return t;
}

