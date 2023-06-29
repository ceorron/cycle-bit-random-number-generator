/*----------------------------------------------------------------------------------*\
 |																					|
 | rcb_fast_generator.hpp 															|
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
#pragma once

#include "rcb_generator.hpp"

namespace rcbg {

template<typename T>
T circular_shift_right(T val, T count) {
	count %= sizeof(T) * 8;
	return (val << (sizeof(T) * 8) - count) | (val >> count);
}
template<typename T>
T circular_shift_left(T val, T count) {
	count %= sizeof(T) * 8;
	return (val << count) | (val >> (sizeof(T) * 8) - count);
}
template<typename T>
T get_one_bits(unsigned count) {
	//make a string of one bits
    return ~((T)-1 << count);
}

//the random cycle bit generator - random number generator
template<typename T,
		 unsigned CntN = sizeof(T)>
class rcb_fast_generator {
private:
	T val;
	rcb_generator_count<CntN> cnt;
	//only first one flags used (0 is whether reseed enabled)
	char flags;

	static T generate(T val) {
		//take the lower count bits
		T tmp = ((val + ((val & get_one_bits<T>((sizeof(T)*8)/2 - 1)) << 1)) % ((sizeof(T)*8) - 1)) | 1;

		//circular shift by one to the right
		val ^= circular_shift_right(val, (T)1);

		val ^= val >> sizeof(T)*8 / 2;
		val ^= val << sizeof(T)*8 / 2;

		//circular shift by that many bits
		return val ^ circular_shift_right(val, tmp);
	}
	T generate_outer(T tmp_cnt) {
		T val2 = (~val << 1) * (generate(~val) << 1);
		return val = generate(val) ^ val2 ^ generate(val2) ^ generate(~generate(tmp_cnt));
	}
	void seed(T rnd, T offset, bool reseed) {
		flags = 0;
		val = ~(rnd + offset);
		flags = set_bit(flags, 0, reseed);
	}
public:
	rcb_fast_generator(T rnd, bool reseed = false) {
		seed(rnd, 10, reseed);
	}
	T rand() {
		bool gd = cnt.increment();
		T tmp_cnt = cnt;
		if(tmp_cnt == 0) ++tmp_cnt;
		T rtn = generate_outer(tmp_cnt);

		if(!gd && reseeds()) {
			T a = generate_outer(++tmp_cnt);
			T b = generate_outer(++tmp_cnt);
			seed(a, b, true);
		}
		return rtn;
	}
	bool good() const {
		return cnt.good();
	}
	bool reseeds() const {
		return get_bit(flags, 0);
	}
};

}
