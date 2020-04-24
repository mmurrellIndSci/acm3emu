#ifndef SHIFT_OPERATIONS_H
#define SHIFT_OPERATIONS_H
#include <stdint.h>
#include <stdio.h>

enum SRType {
	SRType_None, SRType_LSL, SRType_LSR,
	SRType_ASR, SRType_ROR, SRType_RRX
}typedef SRType;

extern void		DisplaySRType(SRType t, uint32_t shifted);
extern uint32_t LSL_C(uint32_t bitsN, uint32_t shift, uint32_t* carrybit);
extern uint32_t LSR_C(uint32_t bitsN, uint32_t shift, uint32_t* carrybit);
extern uint32_t ASR_C(uint32_t bitsN, uint32_t shift, uint32_t* carrybit);
extern uint32_t ROR_C(uint32_t bitsN, uint32_t shift, uint32_t* carrybit);
extern uint32_t RRX_C(uint32_t bitsN,				  uint32_t* carrybit);

extern uint32_t Shift_C(uint32_t rm, SRType st, uint32_t sn, uint32_t* c);
extern uint32_t Shift(uint32_t rm, uint32_t st, uint32_t sn, uint32_t* c);

extern uint32_t ZeroExtend(uint16_t imm12, uint16_t len);
extern uint32_t SignExtend(const uint16_t imm12, const uint16_t len);
extern uint32_t ThumbExpandImmWithCarry(uint16_t imm12, uint32_t* c_in);
extern SRType	DecodeImmShift(uint16_t type, uint16_t imm5);

#endif // !SHIFT_FUNCTIONS_H