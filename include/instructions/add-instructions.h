#ifndef ADD_INSTRUCTIONS_H_
#define ADD_INSTRUCTIONS_H_

#include "../structs.h"

extern uint32_t AddWithCarry(uint32_t a, uint32_t b, uint32_t* carry_in, uint32_t* overflow); 
//{
//
//	//The easy part
//	uint32_t result = (a + b + *carry_in);
//
//	// A Carry happens when: Adding two 32bit numbers requires a 33rd bit
//	// If I convert them to 64 bits and the results are not the same, issa carry
//	uint64_t result64 = ((uint64_t)a + (uint64_t)b + (uint64_t)*carry_in);
//	uint32_t carry_out = result64 >> 32;// !(result == result64);
//	*carry_in = carry_out;
//
//	//An overflow happens when:
//	//- Adding two positives results in a negative
//	//- Subtracting a negative from a negative results in a positive 
//	uint_fast8_t absign = ((a >> 31) == (b >> 31));
//	uint_fast8_t brsign = ((b >> 31) != (result >> 31));
//	*overflow = absign && brsign;
//	return		result;
//}

//16 bit
extern void ADC_Reg_T1(const Instruction* inst, StateARMCortexM3* m3);

extern void ADD_Imm_T1(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_Imm_T2(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_Reg_T1(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_Reg_T2(const Instruction* inst, StateARMCortexM3* m3);

extern void ADD_SPI_T1(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_SPI_T2(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_SPR_T1(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_SPR_T2(const Instruction* inst, StateARMCortexM3* m3);


//32 bit
extern void ADC_Imm_T1(const Instruction* inst, StateARMCortexM3* m3);
extern void ADC_Reg_T2(const Instruction* inst, StateARMCortexM3* m3);

extern void ADD_Imm_T3(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_Imm_T4(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_Reg_T3(const Instruction* inst, StateARMCortexM3* m3);

extern void ADD_SPI_T3(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_SPI_T4(const Instruction* inst, StateARMCortexM3* m3);
extern void ADD_SPR_T3(const Instruction* inst, StateARMCortexM3* m3);

#endif // !ADD_INSTRUCTIONS_H_