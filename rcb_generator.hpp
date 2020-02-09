/*----------------------------------------------------------------------------------*\
 |																					|
 | rcb_generator.hpp 																|
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
#pragma once

namespace rcbg {

template<typename U>
inline bool get_bit(U val, unsigned pos) {
	return val & ((U)1 << pos);
}
template<typename U>
inline U set_bit(U val, unsigned pos, bool to) {
	return (val & ~((U)1 << pos)) | ((U)to << pos);
}

template<unsigned int N>
struct rcb_generator_count {
private:
	uint8_t dat[N];
public:
	rcb_generator_count() {
		//init to zero
		for(unsigned i = 0; i < N; ++i)
			dat[i] = 0;
	}
	bool increment() {
		//increment this
		for(unsigned i = 0; i < N; ++i) {
			if(dat[i] == std::numeric_limits<uint8_t>::max())
				dat[i] = 0;
			else {
				++dat[i];
				return true;
			}
		}
		return false;
	}
	bool good() const {
		//have we gone around the whole set of numbers
		for(unsigned i = 0; i < N; ++i)
			if(dat[i] != std::numeric_limits<uint8_t>::max())
				return true;
		return false;
	}
	template<typename T>
	operator T() const {
		//get the value of this
		T rtn = 0;
		unsigned j = 0;
		for(unsigned i = 0; i < N; ++i) {
			rtn ^= ((T)dat[i]) << (8 * j);
			++j;
			if(j == sizeof(T))
				j = 0;
		}
		return rtn;
	}
};

//the random cycle bit generator - random number generator
template<typename T,
		 unsigned int CntN = sizeof(T),
		 unsigned int bit_pos_left = ((sizeof(T) * 8) / 3) + 1,
		 unsigned int bit_pos_start = bit_pos_left * 2>
class rcb_generator {
private:
	T val;
	T last;
	rcb_generator_count<CntN> cnt;
	//only first two flags used (1 << 1) is "left" (1 << 0) is start
	char flags;
	inline static T shift_transform(T val, int i, bool& start_bit) {
        val ^= (T)start_bit << i;
		start_bit ^= get_bit(val, i);
		return val;
	}
	static T generate(T val, bool left, bool start_bit) {
		if(left)
			for(int i = 0; i < (int)(sizeof(T) * 8); ++i)
				val = shift_transform(val, i, start_bit);
		else
			for(int i = (sizeof(T) * 8) - 1; i > -1; --i)
				val = shift_transform(val, i, start_bit);
		return val;
	}
	T generate(T inval) {
		//set the flags left and start bit
		bool left = (get_bit(val, bit_pos_left) ^ get_bit(flags, 1) ^ true);
		bool start_bit = (get_bit(val, bit_pos_start) ^ get_bit(flags, 0) ^ true);
		flags = set_bit(flags, 1, left);
		flags = set_bit(flags, 0, start_bit);

		return last = generate(inval, left, start_bit) ^ inval ^ ~last;
	}
	T generate_outer(T tmp_cnt) {
		return val = (((val = generate(val)) << 1) * (generate(tmp_cnt) << 1)) ^ generate(val);
	}
	void seed(T rnd, T offset, bool reseed) {
		flags = 0;
		val = rnd + offset;
		last = ~(rnd - offset);
		flags = set_bit(flags, 2, reseed);
	}
public:
	rcb_generator(T rnd, bool reseed = false) {
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
	bool good() {
		return cnt.good();
	}
	bool reseeds() const {
		return get_bit(flags, 2);
	}
};

}
