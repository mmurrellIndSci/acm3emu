#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "../include/instructions16.h"
#include "../include/instructions32.h"
#include "../include/util/getHex.h"

void DisplayI32BHCode(Intel32BitHex code) {
	printf("\n\nRecordLength: %u \nLoadOffset: %#X \nRecordType: %#X \nData: ", code.recordLength, code.loadOffset, code.recordType);
	for (int i = 0; i < code.recordLength; ++i) {
		printf("%#X ", code.data[i]);
	}
	printf("\nCheckSum: %#X\n", code.checkSum);
}

//ensures you only get data by
void GetFirstData(FILE* fp, const char* buff, Intel32BitHex* code) {
	uint8_t rt = 1;
	while ((rt != 0) && (getHex(fp, buff, &code) == 1 )) {
		rt = code->recordType;
	}
}

//Changes the data layout so instea dof it bieng 1234 5678 its.... 3412 7856
void DataFlip(Intel32BitHex* code) {
	assert(code->recordType % 2 == 0);
	//if (code->recordType % 2 != 0)
	//	return;
	for (int i = 0; i < code->recordLength; i += 2) {
		uint8_t temp = code->data[i];			
		code->data[i] = code->data[i + 1];		
		code->data[i + 1] = temp;				
	}
}

void DisplayInstruction(const Instruction instr) {
	printf("\n\nInstruction: ");
	if (instr.size == 32) {
		uint32_t comb = (instr.high << 16) + instr.low;
		printf("%#X ", comb );
	}
	else{
		printf("%#X ", instr.low);
	}
	printf("\nBinary of I: ");
	uint32_t b = 0;
	int i = 31;
	if (instr.size == 32) {
		for (i; i > 15; --i) {
			b = instr.high & bm_Isolate16[i - 16];
			b = b >> i - 16;
			printf("%d", b);
		}
	}
	i = 15;
	for (i; i >= 0; --i) {
		b = instr.low & bm_Isolate16[i];
		b = b >> i;
		printf("%d", b);
	}

}

//This function turns an Intel 32bit Hex code into an instruction
void Instructionize(Intel32BitHex* code, StateARMCortexM3* state) {

	//First make sure it only takes data processing instructions
	if (code->recordType % 2 != 0) 
		return;

	//There are two types of instructions, 16bit and 32bit instructions
	//The first 3bits tells you which. 1110 0000 or greater = 32bit else its 16
	//if its 16bits you want to iterate by 2's, if its 32 then by 4's	
	int skip = 0;
	for (int i = 0; i < code->recordLength; i += skip) {
		skip = (code->data[i] > 231) ? 4 : 2;
		Instruction inst;
		if (skip == 2) {
			inst = Create16BitInstruction(code->data[i], code->data[i + 1]);
#ifdef DISPLAY
			DisplayInstruction(inst);
#endif
			InstructionClassSelect16(&inst, state);
		}
		else { //(skip == 4)
			inst = Create32BitInstruction(&code->data[i]);
#ifdef DISPLAY
			DisplayInstruction(inst);
#endif
			InstructionClassSelect32(&inst, state);
		}
	}
}

void Emulate(StateARMCortexM3* m3) {
	int itr = 2;
	while (m3->pc <= m3->eof) {
  		itr = (m3->mem[m3->pc + 1] > 231) ? 4 : 2;
		Instruction inst;
		if (itr == 2) {
			inst = Create16BitInstruction(m3->mem[m3->pc + 1], m3->mem[m3->pc]);
			DisplayInstruction(inst);
			InstructionClassSelect16(&inst, m3);
		}
		else {
			inst = Create32BitInstruction(&m3->mem[m3->pc]);
			DisplayInstruction(inst);
			InstructionClassSelect32(&inst, m3);
		}

		m3->pc += itr;

		if (loopCounter >= MAXLOOP)
			break;
	}
}

//On Reset, the processor loads the Main stack pointer with the value from address 0x00000000
void LoadStackPointer(StateARMCortexM3* m3) {
	Instruction inst = Create32BitInstruction(&m3->mem[0]);
	m3->sp = inst.high | (inst.low << 16);
}

//On Reset, The processor loads the Program Counter with the value of the reset vector, which is at address 0x00000004
//bit[0] of the value is loaded into the EPSR T-bit at reset and must be 1
void LoadProgramCounter(StateARMCortexM3* m3) {
	Instruction inst = Create32BitInstruction(&m3->mem[4]);
	m3->pc = inst.high | (inst.low << 16);
	m3->pc -= 1;
	m3->psr.t = inst.high & BITM_SINGLE_0;
}

StateARMCortexM3* InitializeM3(void) {
	StateARMCortexM3* m3 = calloc(1, sizeof(StateARMCortexM3));
	//m3->mem = malloc(0x100000);
	return m3;
};

int main(int argc, char* argv[]) {
	//Open the file
	FILE* fp = fopen("C:\\Users\\mmurrell\\Documents\\CM3Tests\\Objects\\tests.hex", "r");
	//FILE* fp = fopen("hextestjtag.hex", "r");

	if (fp == NULL) {
		printf("ERROR! FILE NOT FOUND");
		exit(1);
	}

	//Check the file
	Intel32BitHex code;
	char buff[255];
	StateARMCortexM3* m3 = InitializeM3();

	uint16_t upperAddr = 0x0000;
	static uint32_t addr = 0;

	while (getHex(fp, buff, &code) == 1) {
		uint16_t lowerAddr = code.loadOffset;
		if (code.recordType == 4) //linear address
			upperAddr = (code.data[0] << 8) + code.data[1];
		uint32_t combinedAddr = (upperAddr << 16) + lowerAddr;
		if (code.recordType == 0) {
			for (int i = 0; i < code.recordLength; ++i) {
				addr = combinedAddr + i;
				if (addr > 0xfffff) {
					goto exit;
				}
				assert(addr < 1048575);
				m3->mem[addr] = code.data[i];
			}
		}

		if (code.recordType == 1)
			goto exit;

		//if (code.recordType == 0) {
		//	DataFlip(&code);
		//}
		//DisplayI32BHCode(code);
		//Instructionize(&code, &m3);


	}
exit:

	fclose(fp);

	m3->eof = addr;

	LoadStackPointer(m3);
	LoadProgramCounter(m3);
	Emulate(m3);

	return 0;
}