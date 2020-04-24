#pragma once
#include "structs.h"
#include "util/bitmasks.h"
#include "instructions/instructions-include.h"

Instruction Create32BitInstruction(uint8_t* ins) {
	Instruction ret;
	ret.size = 32;
	ret.high = ins[1];
	ret.high = ret.high << 8;
	ret.high += ins[0];

	ret.low = ins[3];
	ret.low = ret.low << 8;
	ret.low += ins[2];

	//ret.low = 

	return ret;
}

void IC32_LoadStoreMultiple(const Instruction* ins){};
void IC32_LoadStoreDualOrExc(const Instruction* ins){};
void IC32_DataProcessingShiftedReg(const Instruction* ins, StateARMCortexM3* m3){
	uint_fast16_t op = (ins->high & BITM_MULTI_8) >> 5;
	uint_fast16_t rn = (ins->high & BITM_MULTI_3);
	uint_fast16_t rd = (ins->low & BITM_MULTI_11) >> 8;

	switch (op)
	{
	case 8:
		ADD_Reg_T3(ins, m3);
		break;
	case 10:
		ADC_Reg_T2(ins, m3);
		break;
	case 11:
		SBC_Reg_T2(ins, m3);
		break;
	case 13:
		SUB_Reg_T2(ins, m3);
		break;
	case 14:
		RSB_Reg_T1(ins, m3);
		break;
	default:
		break;
	}
};
void IC32_CoprocessorInstructions(const Instruction* ins){};
void IC32_DataProcessingModImm(const Instruction* ins, StateARMCortexM3* state){
	// 111 10 x0xx xxx ____ 0 ______________
	// high bits  8 - 4 = op
	// high bits  3 - 0 = Rn
	// low  bits 11 - 8 = Rd

	uint16_t op = (ins->high & BITM_MULTI_8) >> 4;
	uint16_t rn = (ins->high & BITM_MULTI_3);
	uint16_t rd = (ins->low & BITM_MULTI_11) >> 8;

	switch (op)
	{
	case 4:
		//if(rn == 15)
		//	MOV_Imm_T2(ins, state);
		//break;
	case 5:
		if(rn == 15)
			MOV_Imm_T2(ins, state);
		break;
	case 6:
		//if (rn == 15)
		//	MVN_Imm_T1(ins, state);
		//break;
	case 7:
		if (rn == 15)
			MVN_Imm_T1(ins, state);
		break;
	case 16:
	case 17:
		if (rn != 15)
			ADD_Imm_T3(ins, state);
		break;
	case 20:
		//ADC_Imm_T1(ins, state);
		//break;
	case 21:
		ADC_Imm_T1(ins, state);
		break;
	case 22:
		SBC_Imm_T1(ins, state);
		break;
	case 23:
		SBC_Imm_T1(ins, state);
		break;
	case 24:
		SUB_Imm_T3(ins, state);
		break;
	case 25:
		SUB_Imm_T3(ins, state);
		break;
	case 26:
		//if (rn != 15)
		//	SUB_Imm_T3(ins, state);
		//break;
	case 27:
		if(rn != 15)
			SUB_Imm_T3(ins, state);
		break;
	case 28:
		RSB_Imm_T2(ins, state);
		break;
	case 29:
		RSB_Imm_T2(ins, state);
		break;
	default:
		break;
	}
};
void IC32_DataProcessingPlainBinImm(const Instruction* ins, StateARMCortexM3* m3){
	// 111 10 _ 1 op(8-4) rn(3-0) | 0 ________________
	uint16_t op = (ins->high & BITM_MULTI_8) >> 4;
	uint16_t rn = (ins->high & BITM_MULTI_3);

	switch (op)
	{
	case 0:
		if (rn != 15)
			ADD_Imm_T4(ins, m3);
		break;
	case 4:
		MOV_Imm_T3(ins, m3);
		break;
	case 10:
		if (rn != 15)
			SUB_Imm_T4(ins, m3);
		break;
	case 12:
		MOVT(ins, m3);
		break;
	default:
		break;
	}
};
void IC32_BranchesAndMisc(const Instruction* ins, StateARMCortexM3* m3){
	// Opcode: 111 10 Op1(10-4) ____ | 1 Op2(14-12) ___________
	uint_fast8_t op1 = (ins->high & BITM_MULTI_10) >> 4;
	uint_fast8_t op2 = (ins->low & BITM_MULTI_14) >> 12;
	uint_fast8_t c1 = (op1 & BITM_MULTI_6) >> 3;
	uint_fast8_t c2 = (op1 & BITM_MULTI_2);

	switch (op2) {
	case 0:
		if (c1 != 7)
			B_T3(ins, m3);
		break;
	case 1:
		B_T4(ins, m3);
		break;
	case 2:
		if (c1 != 7)
			B_T3(ins, m3);
		break;
	case 3:
		B_T4(ins, m3);
		break;
	case 5:
		BL_T1(ins, m3);
		break;
	case 7:
		BL_T1(ins, m3);
		break;
	default:
		break;
	}

};
void IC32_StoreSingleData(const Instruction* ins){};
void IC32_LoadByteMemHints(const Instruction* ins){};
void IC32_LoadHalfwordUnAllMemHints(const Instruction* ins){};
void IC32_LoadWord(const Instruction* ins){};
void IC32_UNDEFINED(const Instruction* ins){};
void IC32_DataProcessingRegister(const Instruction* ins){};
void IC32_MultiplyAndAcc(const Instruction* ins){};
void IC32_LongMult(const Instruction* ins){};


/****************************************************
		This is disgusting.... but whatever
****************************************************/
void InstructionClassSelect32(const Instruction* ins, StateARMCortexM3* state) {
	uint16_t op1 = (ins->high & BITM_MULTI_12) >> 11;
	uint16_t op2 = (ins->high & BITM_MULTI_10) >> 4;
	uint16_t op = (ins->low & BITM_SINGLE_15) >> 15;

	if (op1 == 1) {
		if (op2 > 63)
			IC32_CoprocessorInstructions(ins);
		else if (op2 > 31){
			IC32_DataProcessingShiftedReg(ins, state);
			//ADD_Reg_T3(ins, state);
		}
		else {
			uint16_t temp = ins->high & BITM_SINGLE_6;
			temp == 0 ? IC32_LoadStoreMultiple(ins) : IC32_LoadStoreDualOrExc(ins);
		}
	}
	else if (op1 == 2) {
		if (op == 1)
			IC32_BranchesAndMisc(ins, state);
		else {
			uint16_t temp = ins->high & BITM_SINGLE_9;
			temp == 0 ? IC32_DataProcessingModImm(ins, state) : IC32_DataProcessingPlainBinImm(ins, state);
		}
	}
	else if (op1 == 3) {
		if (op2 > 63)
			IC32_CoprocessorInstructions(ins);
		else if (op2 > 31){
			uint16_t temp = op2 >> 3;
			switch (temp)
			{
				case 4: IC32_DataProcessingRegister(ins); break;
				case 5: IC32_DataProcessingRegister(ins); break;
				case 6: IC32_MultiplyAndAcc(ins); break;
				case 7: IC32_LongMult(ins); break;
				default: break;
			}
		}
		else {
			if ((ins->high & BITM_SINGLE_4) == 0)
				IC32_StoreSingleData(ins);
			else {
				uint16_t temp = op2 & BITM_MULTI_2;
				switch (temp)
				{
					case 1: IC32_LoadByteMemHints(ins); break;
					case 3: IC32_LoadHalfwordUnAllMemHints(ins); break;
					case 4: IC32_LoadWord(ins); break;
					case 5: IC32_UNDEFINED(ins); break;
					default: break;
				}
			}
		}
	}
}