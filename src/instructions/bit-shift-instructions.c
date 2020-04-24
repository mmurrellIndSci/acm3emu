#include "../../include/instructions/bit-shift-instructions.h"
#include "../../include/instructions/move-instructions.h"
#include "../../include/util/bitmasks.h"

//16Bit
void LSL_Imm_T1(const Instruction* ins, StateARMCortexM3* m3) {
	uint32_t imm5 = (ins->low & BITM_MULTI_10) >> 6;
	if (imm5 == 0) {
		MOV_Reg_T2(ins, m3);
	}
	else {
		//do stuff

	}

}
void LSL_Reg_T1(const Instruction* ins, StateARMCortexM3* m3){}

void LSR_Imm_T1(const Instruction* ins, StateARMCortexM3* m3){}
void LSR_Reg_T1(const Instruction* ins, StateARMCortexM3* m3){}

void ASR_Imm_T1(const Instruction* ins, StateARMCortexM3* m3){}
void ASR_Reg_T1(const Instruction* ins, StateARMCortexM3* m3){}


//32Bit
void LSL_Imm_T2(const Instruction* ins, StateARMCortexM3* m3){}
void LSL_Reg_T2(const Instruction* ins, StateARMCortexM3* m3){}

void LSR_Imm_T2(const Instruction* ins, StateARMCortexM3* m3){}
void LSR_Reg_T2(const Instruction* ins, StateARMCortexM3* m3){}

void ASR_Imm_T2(const Instruction* ins, StateARMCortexM3* m3){}
void ASR_Reg_T2(const Instruction* ins, StateARMCortexM3* m3){}