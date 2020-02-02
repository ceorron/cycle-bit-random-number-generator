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
RCG_T_TYPE rcb_generate(rcb_gen* gen, RCG_T_TYPE inval) {
	//set the flags left and start bit
	char left = get_bit_val(gen->val, RCG_BIT_POS_LEFT) ^ get_bit_char(gen->flags, 1) ^ 1;
	char start_bit = get_bit_val(gen->val, RCG_BIT_POS_START) ^ get_bit_char(gen->flags, 0) ^ 1;
	gen->flags = set_bit_char(gen->flags, 1, left);
	gen->flags = set_bit_char(gen->flags, 0, start_bit);

	RCG_T_TYPE tmpVal = inval;
	RCG_T_TYPE tfrm = generate(inval, left, start_bit);

	inval = tfrm;
	gen->last = tfrm ^ tmpVal ^ ~gen->last;

	return gen->last;
}
RCG_T_TYPE rcb_rand(rcb_gen* gen) {
	RCG_T_TYPE tmp_cnt = gen->cnt++;
	if(gen->cnt == 0) ++gen->cnt;
	return gen->val = rcb_generate(gen, gen->val) ^ (((gen->val = rcb_generate(gen, gen->val)) << 1) * (rcb_generate(gen, tmp_cnt) << 1));
}
void rcb_init(rcb_gen* gen, RCG_T_TYPE rnd) {
	gen->val = (rnd + 10);
	gen->last = ~(rnd - 10);
	gen->cnt = 1;
	gen->flags = 0;
}

