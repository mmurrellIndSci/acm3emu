#include "structs.h"
#include "util/bitmasks.h"
#include "operations/conditional-operations.h"
#include "instructions/instructions-include.h"

//void IC16_Shift(Instruction ins) {}
//void IC16_DataProc(Instruction ins) {}
//void IC16_MiscInstr(Instruction ins) {}
//void IC16_SpecialDataProc(Instruction ins) {}

Instruction Create16BitInstruction(uint8_t hi, uint8_t lo) {
	Instruction ret;
	ret.size = 16;
	ret.low = hi;
	ret.low = ret.low << 8;
	ret.low += lo;

	return ret;
}

void IC16_Shift(const Instruction* ins, StateARMCortexM3* m3) {
	//Get the bits 00_xxxxx 
	uint16_t bit5 = (ins->low >> 9) & BITM_MULTI_5;

	switch (bit5)
	{
	case 0: LSL_Imm_T1(ins, m3); break;
	case 1: LSL_Imm_T1(ins, m3); break;
	case 2: LSL_Imm_T1(ins, m3); break;
	case 3: LSL_Imm_T1(ins, m3); break;

	//case 4: SHFT16_LogicalShiftRight(instr); break;
	//case 5: SHFT16_LogicalShiftRight(instr); break;
	//case 6: SHFT16_LogicalShiftRight(instr); break;
	//case 7: SHFT16_LogicalShiftRight(instr); break;

	//case 8:  SHFT16_ArithmeticShiftRight(instr); break;
	//case 9:  SHFT16_ArithmeticShiftRight(instr); break;
	//case 10: SHFT16_ArithmeticShiftRight(instr); break;
	//case 11: SHFT16_ArithmeticShiftRight(instr); break;

	case 12: ADD_Reg_T1(ins, m3); break;

	case 13: SUB_Reg_T1(ins, m3); break;

	case 14: ADD_Imm_T1(ins, m3); break;

	case 15: SUB_Imm_T1(ins, m3); break;

	case 16: MOV_Imm_T1(ins, m3); break;
	case 17: MOV_Imm_T1(ins, m3); break;
	case 18: MOV_Imm_T1(ins, m3); break;
	case 19: MOV_Imm_T1(ins, m3); break;

	//case 20: SHFT16_Compare(instr); break;
	//case 21: SHFT16_Compare(instr); break;
	//case 22: SHFT16_Compare(instr); break;
	//case 23: SHFT16_Compare(instr); break;

	case 24: ADD_Imm_T2(ins, m3); break;
	case 25: ADD_Imm_T2(ins, m3); break;
	case 26: ADD_Imm_T2(ins, m3); break;
	case 27: ADD_Imm_T2(ins, m3); break;

	case 28: SUB_Imm_T2(ins, m3); break;
	case 29: SUB_Imm_T2(ins, m3); break;
	case 30: SUB_Imm_T2(ins, m3); break;
	case 31: SUB_Imm_T2(ins, m3); break;

	default:
		break;
	}

}
void IC16_DataProc(Instruction* ins, StateARMCortexM3* m3) {
	uint_fast8_t bits4 = (ins->low & BITM_MULTI_9) >> 6;

	switch (bits4)
	{
	//case 0: DATA16_BitwiseAND(inst); break;
	//case 1: DATA16_ExclusiveOR(inst); break;
	//case 2: DATA16_LogicalShiftLeft(inst); break;
	//case 3: DATA16_LogicalShiftRight(inst); break;
	//case 4: DATA16_ArithmeticShiftRight(inst); break;
	case 5: ADC_Reg_T1(ins, m3); break;
	case 6: SBC_Reg_T1(ins, m3); break;
	//case 7: DATA16_RotateRight(inst); break;
	//case 8: DATA16_SetFlagsOnBitwiseAND(inst); break;
	case 9: RSB_Imm_T1(ins, m3); break;
	//case 10: DATA16_CompareRegisters(inst); break;
	//case 11: DATA16_CompareNegative(inst); break;
	//case 12: DATA16_LogicalOR(inst); break;
	//case 13: DATA16_MultiplyTwoRegisters(inst); break;
	//case 14: DATA16_BitClear(inst); break;
	//case 15: DATA16_BitwiseNOT(inst); break;

	default:
		break;
	}

}
//void IC16_SpecialDataProc(Instruction ins, StateARMCortexM3* m3) {
//	uint16_t bit4 = (ins.low & BITM_MULTI_9) >> 6;
//
//	switch (bit4)
//	{
//
//	case 8:  MOV_Reg_T2(ins, m3); break;
//	case 9:  MOV_Reg_T2(ins, m3); break;
//	case 10: MOV_Reg_T2(ins, m3); break;
//	case 11: MOV_Reg_T2(ins, m3); break;
//
//	default:
//		break;
//	}
//}
void IC16_MiscInstruction(const Instruction* ins, StateARMCortexM3* m3) {
	uint16_t bits7 = (ins->low & BITM_MULTI_11) >> 5;

	switch (bits7)
	{
	case 0: ADD_SPI_T2(ins, m3); break;
	case 1: ADD_SPI_T2(ins, m3); break;
	case 2: ADD_SPI_T2(ins, m3); break;
	case 3: ADD_SPI_T2(ins, m3); break;

	case 4:	SUB_SMI_T1(ins, m3); break;
	case 5:	SUB_SMI_T1(ins, m3); break;
	case 6:	SUB_SMI_T1(ins, m3); break;
	case 7:	SUB_SMI_T1(ins, m3); break;

	//case 8:  MISC16_CompareAndBranchOnZero(inst); break;
	//case 9:  MISC16_CompareAndBranchOnZero(inst); break;
	//case 10: MISC16_CompareAndBranchOnZero(inst); break;
	//case 11: MISC16_CompareAndBranchOnZero(inst); break;
	//case 12: MISC16_CompareAndBranchOnZero(inst); break;
	//case 13: MISC16_CompareAndBranchOnZero(inst); break;
	//case 14: MISC16_CompareAndBranchOnZero(inst); break;
	//case 15: MISC16_CompareAndBranchOnZero(inst); break;

	//case 16: MISC16_SignedExtendHalfword(inst); break;
	//case 17: MISC16_SignedExtendHalfword(inst); break;

	//case 18: MISC16_SignedExtendBye(inst); break;
	//case 19: MISC16_SignedExtendBye(inst); break;

	//case 20: MISC16_UnsignedExtendHalfword(inst); break;
	//case 21: MISC16_UnsignedExtendHalfword(inst); break;

	//case 22: MISC16_UnsignedExtendByte(inst); break;
	//case 23: MISC16_UnsignedExtendByte(inst); break;

	//case 24: MISC16_CompareAndBranchOnZero(inst); break;
	//case 25: MISC16_CompareAndBranchOnZero(inst); break;
	//case 26: MISC16_CompareAndBranchOnZero(inst); break;
	//case 27: MISC16_CompareAndBranchOnZero(inst); break;
	//case 28: MISC16_CompareAndBranchOnZero(inst); break;
	//case 29: MISC16_CompareAndBranchOnZero(inst); break;
	//case 30: MISC16_CompareAndBranchOnZero(inst); break;
	//case 31: MISC16_CompareAndBranchOnZero(inst); break;

	//case 32: MISC16_PushMultipleRegisters(inst); break;
	//case 33: MISC16_PushMultipleRegisters(inst); break;
	//case 34: MISC16_PushMultipleRegisters(inst); break;
	//case 35: MISC16_PushMultipleRegisters(inst); break;
	//case 36: MISC16_PushMultipleRegisters(inst); break;
	//case 37: MISC16_PushMultipleRegisters(inst); break;
	//case 38: MISC16_PushMultipleRegisters(inst); break;
	//case 39: MISC16_PushMultipleRegisters(inst); break;
	//case 40: MISC16_PushMultipleRegisters(inst); break;
	//case 41: MISC16_PushMultipleRegisters(inst); break;
	//case 42: MISC16_PushMultipleRegisters(inst); break;
	//case 43: MISC16_PushMultipleRegisters(inst); break;
	//case 44: MISC16_PushMultipleRegisters(inst); break;
	//case 45: MISC16_PushMultipleRegisters(inst); break;
	//case 46: MISC16_PushMultipleRegisters(inst); break;
	//case 47: MISC16_PushMultipleRegisters(inst); break;

	//case 72: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 73: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 74: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 75: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 76: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 77: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 78: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 79: MISC16_CompareAndBranchOnNonZero(inst); break;

	//case 80: MISC16_ByteReverseWord(inst); break;
	//case 81: MISC16_ByteReverseWord(inst); break;

	//case 82: MISC16_ByteReversePackedHalfword(inst); break;
	//case 83: MISC16_ByteReversePackedHalfword(inst); break;

	//case 86: MISC16_ByteReverseSignedHalfword(inst); break;
	//case 87: MISC16_ByteReverseSignedHalfword(inst); break;

	//case 88: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 89: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 90: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 91: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 92: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 93: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 94: MISC16_CompareAndBranchOnNonZero(inst); break;
	//case 95: MISC16_CompareAndBranchOnNonZero(inst); break;

	//case 96:  MISC16_PopMultipleRegisters(inst); break;
	//case 97:  MISC16_PopMultipleRegisters(inst); break;
	//case 98:  MISC16_PopMultipleRegisters(inst); break;
	//case 99:  MISC16_PopMultipleRegisters(inst); break;
	//case 100: MISC16_PopMultipleRegisters(inst); break;
	//case 101: MISC16_PopMultipleRegisters(inst); break;
	//case 102: MISC16_PopMultipleRegisters(inst); break;
	//case 103: MISC16_PopMultipleRegisters(inst); break;
	//case 104: MISC16_PopMultipleRegisters(inst); break;
	//case 105: MISC16_PopMultipleRegisters(inst); break;
	//case 106: MISC16_PopMultipleRegisters(inst); break;
	//case 107: MISC16_PopMultipleRegisters(inst); break;
	//case 108: MISC16_PopMultipleRegisters(inst); break;
	//case 109: MISC16_PopMultipleRegisters(inst); break;
	//case 110: MISC16_PopMultipleRegisters(inst); break;
	//case 111: MISC16_PopMultipleRegisters(inst); break;

	//case 112: MISC16_BreakPoint(inst); break;
	//case 113: MISC16_BreakPoint(inst); break;
	//case 114: MISC16_BreakPoint(inst); break;
	//case 115: MISC16_BreakPoint(inst); break;
	//case 116: MISC16_BreakPoint(inst); break;
	//case 117: MISC16_BreakPoint(inst); break;
	//case 118: MISC16_BreakPoint(inst); break;
	//case 119: MISC16_BreakPoint(inst); break;

	//case 120: MISC16_IfThenElseHints(inst); break;
	//case 121: MISC16_IfThenElseHints(inst); break;
	//case 122: MISC16_IfThenElseHints(inst); break;
	//case 123: MISC16_IfThenElseHints(inst); break;
	//case 124: MISC16_IfThenElseHints(inst); break;
	//case 125: MISC16_IfThenElseHints(inst); break;
	//case 126: MISC16_IfThenElseHints(inst); break;
	//case 127: MISC16_IfThenElseHints(inst); break;

	default:
		break;
	}
}
void IC16_SpecialDataProc(const Instruction* ins, StateARMCortexM3* m3) {
	uint16_t bit4 = (ins->low & BITM_MULTI_9) >> 6;

	switch (bit4)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		ADD_Reg_T2(ins, m3);
		break;
	//case 8:  SCDP16_MoveRegisters(ins); break;
	//case 9:  SCDP16_MoveRegisters(ins); break;
	//case 10: SCDP16_MoveRegisters(ins); break;
	//case 11: SCDP16_MoveRegisters(ins); break;

	default:
		break;
	}
}

void IC16_LoadLiteralPool(Instruction ins) {}
void IC16_LoadStoreData(Instruction ins) {}
void IC16_GeneratePCAdr(Instruction ins){}
void IC16_StoreMult(Instruction ins) {}
void IC16_LoadMult(Instruction ins) {}
void IC16_CondBranch(Instruction ins) {
	enum Conditional c = (ins.low & BITM_MULTI_7) >> 4;
	printf("\nB");
	DisplayConditional(c);
	printf("    ");
}
void IC16_UnCondBranch(Instruction ins) {
}

void InstructionClassSelect16(const Instruction* ins, StateARMCortexM3* m3) {
	uint16_t bit6 = ins->low >> 10;
	switch (bit6)
	{
	case 0:  IC16_Shift(ins, m3); break;
	case 1:  IC16_Shift(ins, m3); break;
	case 2:  IC16_Shift(ins, m3); break;
	case 3:  IC16_Shift(ins, m3); break;
	case 4:  IC16_Shift(ins, m3); break;
	case 5:  IC16_Shift(ins, m3); break;
	case 6:  IC16_Shift(ins, m3); break;
	case 7:  IC16_Shift(ins, m3); break;
	case 8:  IC16_Shift(ins, m3); break;
	case 9:  IC16_Shift(ins, m3); break;
	case 10: IC16_Shift(ins, m3); break;
	case 11: IC16_Shift(ins, m3); break;
	case 12: IC16_Shift(ins, m3); break;
	case 13: IC16_Shift(ins, m3); break;
	case 14: IC16_Shift(ins, m3); break;
	case 15: IC16_Shift(ins, m3); break;

	case 16: IC16_DataProc(ins, m3); break;

	case 17: IC16_SpecialDataProc(ins, m3); break;

	//case 18: IC16_LoadLiteralPool(ins, m3); break;
	//case 19: IC16_LoadLiteralPool(ins, m3); break;

	//case 20: IC16_LoadStoreData(ins, m3); break;
	//case 21: IC16_LoadStoreData(ins, m3); break;
	//case 22: IC16_LoadStoreData(ins, m3); break;
	//case 23: IC16_LoadStoreData(ins, m3); break;
	//case 24: IC16_LoadStoreData(ins, m3); break;
	//case 25: IC16_LoadStoreData(ins, m3); break;
	//case 26: IC16_LoadStoreData(ins, m3); break;
	//case 27: IC16_LoadStoreData(ins, m3); break;
	//case 28: IC16_LoadStoreData(ins, m3); break;
	//case 29: IC16_LoadStoreData(ins, m3); break;
	//case 30: IC16_LoadStoreData(ins, m3); break;
	//case 31: IC16_LoadStoreData(ins, m3); break;
	//case 32: IC16_LoadStoreData(ins, m3); break;
	//case 33: IC16_LoadStoreData(ins, m3); break;
	//case 34: IC16_LoadStoreData(ins, m3); break;
	//case 35: IC16_LoadStoreData(ins, m3); break;
	//case 36: IC16_LoadStoreData(ins, m3); break;
	//case 37: IC16_LoadStoreData(ins, m3); break;
	//case 38: IC16_LoadStoreData(ins, m3); break;
	//case 39: IC16_LoadStoreData(ins, m3); break;

	//case 40: IC16_GeneratePCAdr(ins, m3); break;
	//case 41: IC16_GeneratePCAdr(ins, m3); break;

	case 42: ADD_SPI_T1(ins, m3); break;
	case 43: ADD_SPI_T1(ins, m3); break;

	case 44: IC16_MiscInstruction(ins, m3); break;
	case 45: IC16_MiscInstruction(ins, m3); break;
	case 46: IC16_MiscInstruction(ins, m3); break;
	case 47: IC16_MiscInstruction(ins, m3); break;

	//case 48: IC16_StoreMult(ins, m3); break;
	//case 49: IC16_StoreMult(ins, m3); break;

	//case 50: IC16_LoadMult(ins, m3); break;
	//case 51: IC16_LoadMult(ins, m3); break;

	case 52: B_T1(ins, m3); break; //Conditional Branch
	case 53: B_T1(ins, m3); break; //Conditional Branch
	case 54: B_T1(ins, m3); break; //Conditional Branch
	case 55: B_T1(ins, m3); break; //Conditional Branch

	case 56: B_T2(ins, m3); break; //Unconditional Branch
	case 57: B_T2(ins, m3); break; //Unconditional Branch

	default:
		break;
	}
}