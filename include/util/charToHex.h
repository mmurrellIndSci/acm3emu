#ifndef CHAR_TO_HEX_H
#define CHAR_TO_HEX_H
#include <stdint.h>

unsigned int powers[4] = { 1, 16, 256, 4096 };

//Converts A Char array [high][low] into its hex value
//Ex. in = 2A, high = 2 == 32; Low = A == 10. Result = 32 + 10 = 42;
uint8_t charToHex8(const char* in) {
	//Note: 48 = 0 in ascii, 65 = A in ascii
	int high = (in[0] > 64) ? in[0] - 55 : in[0] - 48;
	int low = (in[1] > 64) ? in[1] - 55 : in[1] - 48;
	return high * 16 + low;
}

//Should be obvs what I'm doing based on explanation above
uint16_t charToHex16(const char* in) {
	int out[4];
	uint16_t result = 0;
	for (int i = 0; i < 4; ++i) {
		out[i] = (in[i] > 64) ? in[i] - 55 : in[i] - 48;
		result += out[i] * powers[3 - i];
	}
	return result;
}

#endif // !CHAR_TO_HEX_H