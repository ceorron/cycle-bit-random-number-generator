/*----------------------------------------------------------------------------------*\
 |																					|
 | rcb_fast_generator.c 															|
 |																					|
 | Copyright (c) 2020-2023 Richard Cookman											|
 |																					|
 | Permission is hereby granted, free of charge, to any person obtaining a copy		|
 | of this software and associated documentation files (the "Software"), to deal	|
 | in the Software without restriction, including without limitation the rights		|
 | to use, copy, modify, merge, publish, distribute, sublicense, and/or sell		|
 | copies of the Software, and to permit persons to whom the Software is			|
 | furnished to do so, subject to the following conditions:							|
 |																					|
 | The above copyright notice and this permission notice shall be included in all	|
 | copies or substantial portions of the Software.									|
 |																					|
 | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR		|
 | IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,			|
 | FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE		|
 | AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER			|
 | LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	|
 | OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	|
 | SOFTWARE.																		|
 |																					|
\*----------------------------------------------------------------------------------*/

#include "rcb_fast_generator.h"

inline char get_bit_char(char val, unsigned pos) {
	return (val >> pos) & 1;
}
inline char set_bit_char(char val, unsigned pos, char to) {
	return (val & ~((char)1 << pos)) | ((char)to << pos);
}
RCG_FAST_T_TYPE rcb_fast_circular_shift_right(RCG_FAST_T_TYPE val, RCG_FAST_T_TYPE count) {
	count %= sizeof(RCG_FAST_T_TYPE) * 8;
	return (val << (sizeof(RCG_FAST_T_TYPE) * 8) - count) | (val >> count);
}
RCG_FAST_T_TYPE rcb_fast_circular_shift_left(RCG_FAST_T_TYPE val, RCG_FAST_T_TYPE count) {
	count %= sizeof(RCG_FAST_T_TYPE) * 8;
	return (val << count) | (val >> (sizeof(RCG_FAST_T_TYPE) * 8) - count);
}
RCG_FAST_T_TYPE rcb_fast_get_one_bits(unsigned count) {
	//make a string of one bits
	return ~((RCG_FAST_T_TYPE)-1 << count);
}

RCG_FAST_T_TYPE rcb_fast_generate(RCG_FAST_T_TYPE val) {
	//take the lower count bits
	RCG_FAST_T_TYPE tmp = ((val + ((val & rcb_fast_get_one_bits((sizeof(RCG_FAST_T_TYPE)*8)/2 - 1)) << 1)) % ((sizeof(RCG_FAST_T_TYPE)*8) - 1)) | 1;

	//circular shift by one to the right
	val ^= rcb_fast_circular_shift_right(val, (RCG_FAST_T_TYPE)1);

	val ^= val >> sizeof(RCG_FAST_T_TYPE)*8 / 2;
	val ^= val << sizeof(RCG_FAST_T_TYPE)*8 / 2;

	//circular shift by that many bits
	return val ^ rcb_fast_circular_shift_right(val, tmp);
}
RCG_FAST_T_TYPE rcb_fast_generate_outer(rcb_fast_gen* gen, RCG_FAST_T_TYPE tmp_cnt) {
	RCG_FAST_T_TYPE val2 = (~gen->val << 1) * (rcb_fast_generate(~gen->val) << 1);
	return gen->val = rcb_fast_generate(gen->val) ^ val2 ^ rcb_fast_generate(val2) ^ rcb_fast_generate(~rcb_fast_generate(tmp_cnt));
}
void rcb_fast_seed(rcb_fast_gen* gen, RCG_FAST_T_TYPE rnd, RCG_FAST_T_TYPE offset, char reseed) {
	gen->cnt = 0;
	gen->flags = 0;
	gen->val = ~(rnd + offset);
	gen->flags = set_bit_char(gen->flags, 0, reseed);
}
void rcb_fast_init(rcb_fast_gen* gen, RCG_FAST_T_TYPE rnd, char reseed) {
	rcb_fast_seed(gen, rnd, 10, reseed);
}
RCG_FAST_T_TYPE rcb_fast_rand(rcb_fast_gen* gen) {
	char gd = rcb_fast_good(gen);
	RCG_FAST_T_TYPE tmp_cnt = ++gen->cnt;
	if(tmp_cnt == 0) ++tmp_cnt;
	RCG_FAST_T_TYPE rtn = rcb_fast_generate_outer(gen, tmp_cnt);

	if(gd == 0 && rcb_reseeds(gen) == 1) {
		RCG_FAST_T_TYPE a = rcb_fast_generate_outer(gen, ++tmp_cnt);
		RCG_FAST_T_TYPE b = rcb_fast_generate_outer(gen, ++tmp_cnt);
		rcb_fast_seed(gen, a, b, 1);
	}
	return rtn;
}
char rcb_fast_good(const rcb_fast_gen* gen) {
	return gen->cnt != ~(RCG_FAST_T_TYPE)0;
}
char rcb_fast_reseeds(const rcb_fast_gen* gen) {
	return get_bit_char(gen->flags, 0) != 0;
}
