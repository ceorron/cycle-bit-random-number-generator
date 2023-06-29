/*----------------------------------------------------------------------------------*\
 |																					|
 | rcb_generator.h 																	|
 |																					|
 | Copyright (c) 2016-2023 Richard Cookman											|
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
#ifndef RCB_GENERATOR
#define RCB_GENERATOR

#ifdef __cplusplus
extern "C" {
#endif

#define RCG_T_TYPE				unsigned
#define RCG_BIT_POS_LEFT		(((sizeof(RCG_T_TYPE) * 8) / 3) + 1)
#define RCG_BIT_POS_START		(RCG_BIT_POS_LEFT * 2)

typedef struct {
	RCG_T_TYPE val;
	RCG_T_TYPE last;
	RCG_T_TYPE cnt;
	char flags;
} rcb_gen;

void rcb_init(rcb_gen* gen, RCG_T_TYPE rnd, char reseed);
RCG_T_TYPE rcb_rand(rcb_gen* gen);
char rcb_good(const rcb_gen* gen);
char rcb_reseeds(const rcb_gen* gen);

#ifdef __cplusplus
}
#endif

#endif
