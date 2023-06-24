/*----------------------------------------------------------------------------------*\
 |																					|
 | rcb_generator.c 																	|
 |																					|
 | Copyright (c) 2016 Richard Cookman												|
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

#include "rcb_generator.h"

inline char get_bit_char(char val, unsigned pos) {
	return (val & ((char)1 << pos)) != 0;
}
inline char set_bit_char(char val, unsigned pos, char to) {
	return (val & ~((char)1 << pos)) | ((char)to << pos);
}
inline char get_bit_val(RCG_T_TYPE val, unsigned pos) {
	return (val & ((RCG_T_TYPE)1 << pos)) != 0;
}
inline RCG_T_TYPE set_bit_val(RCG_T_TYPE val, unsigned pos, char to) {
	return (val & ~((RCG_T_TYPE)1 << pos)) | ((RCG_T_TYPE)to << pos);
}
/*
inline RCG_T_TYPE shift_transform(RCG_T_TYPE val, int i, char* start_bit) {
	val ^= (RCG_T_TYPE)*start_bit << i;
	*start_bit ^= get_bit_val(val, i);
	return val;
}
RCG_T_TYPE generate(RCG_T_TYPE val, char left, char start_bit) {
	if(left)
		for(int i = 0; i < (int)(sizeof(RCG_T_TYPE) * 8); ++i)
			val = shift_transform(val, i, &start_bit);
	else
		for(int i = (sizeof(RCG_T_TYPE) * 8) - 1; i > -1; --i)
			val = shift_transform(val, i, &start_bit);
	return val;
}
*/
RCG_T_TYPE generate(RCG_T_TYPE val, char left, char start_bit) {
	RCG_T_TYPE rtn = 0;
	//bool last_bit = false;
	if(left) {
		//get all of the positions where we see a bit change going left
		//last_bit = (val & (1 << (sizeof(RCG_T_TYPE) * 8 - 1))) != 0;
		RCG_T_TYPE lval = (val << 1) | (RCG_T_TYPE)start_bit;
		rtn = lval ^ val;
	} else {
		//get all of the positions where we see a bit change going right
		//last_bit = (val & 1) != 0;
		RCG_T_TYPE rval = (val >> 1) | ((RCG_T_TYPE)start_bit << (sizeof(RCG_T_TYPE) * 8 - 1));
		rtn = rval ^ val;
	}
	//start_bit = last_bit;
	return rtn;
}
RCG_T_TYPE rcb_generate(rcb_gen* gen, RCG_T_TYPE inval, unsigned BP) {
	//set the flags left and start bit
	char left = get_bit_val(gen->val, (RCG_BIT_POS_LEFT + BP) % (sizeof(RCG_T_TYPE)*8)) ^ get_bit_char(gen->flags, 1) ^ 1;
	char start_bit = get_bit_val(gen->val, (RCG_BIT_POS_START + BP) % (sizeof(RCG_T_TYPE)*8)) ^ get_bit_char(gen->flags, 0) ^ 1;
	gen->flags = set_bit_char(gen->flags, 1, left);
	gen->flags = set_bit_char(gen->flags, 0, start_bit);

	return gen->last = generate(inval, left, start_bit) ^ inval ^ ~gen->last;
}
RCG_T_TYPE rcb_generate_outer(rcb_gen* gen, RCG_T_TYPE tmp_cnt) {
	return gen->val = ((rcb_generate(gen, gen->val, 0) << 1) * (rcb_generate(gen, tmp_cnt, 1) << 1)) ^ rcb_generate(gen, gen->val, 2);
}
void rcb_seed(rcb_gen* gen, RCG_T_TYPE rnd, RCG_T_TYPE offset, char reseed) {
	gen->cnt = 0;
	gen->flags = 0;
	gen->val = rnd + offset;
	gen->last = ~(rnd - offset);
	gen->flags = set_bit_char(gen->flags, 2, reseed);
}
char rcb_good(const rcb_gen* gen) {
	return gen->cnt != ~(RCG_T_TYPE)0;
}
RCG_T_TYPE rcb_rand(rcb_gen* gen) {
	char gd = rcb_good(gen);
	RCG_T_TYPE tmp_cnt = ++gen->cnt;
	if(tmp_cnt == 0) ++tmp_cnt;
	RCG_T_TYPE rtn = rcb_generate_outer(gen, tmp_cnt);

	if(gd == 0 && rcb_reseeds(gen) == 1) {
		RCG_T_TYPE a = rcb_generate_outer(gen, ++tmp_cnt);
		RCG_T_TYPE b = rcb_generate_outer(gen, ++tmp_cnt);
		rcb_seed(gen, a, b, 1);
	}
	return rtn;
}
void rcb_init(rcb_gen* gen, RCG_T_TYPE rnd, char reseed) {
	rcb_seed(gen, rnd, 10, reseed);
}
char rcb_reseeds(const rcb_gen* gen) {
	return get_bit_char(gen->flags, 2) != 0;
}

