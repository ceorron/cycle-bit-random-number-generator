# cycle bit scalable psuedo random number generator (rcb_generator)

rcb-generator is a new kind of psuedo random number generator. rcb-generator is a bit pattern generator made to be fast, scalable, high quality psuedo random number generator.

rcb-generator is provided as a C++ source file (single header file).

MIT Licence - See Source/License file

# How to use

```C++
#include <iostream>
#include <ctime>

#include "rcb_generator.hpp"

using namespace std;

int main() {
	//seed the random number generator with the system clock
	rcbg::rcb_generator<unsigned> rnd(time(NULL));
	
	//get a random number
	unsigned random_number = rnd.rand();
	
	//print it
	cout << "random number generated : " << random_number << endl;
	return 0;
}
```

# more on rcb_generator design

rcb-generator provides a fast, scalable, random number generation with a very good period (2^bit-length guaranteed).

rcb-generator is very fast, slower than many shift/modulo generators but about twice as fast (or more) than Mersenne Twister in my tests.

Because rcb-generator operates on a bit pattern not on a value this makes the generator highly scalable (unlike other shift/modulo generators/MT and random number generators in general)

Please use and let me know what you think.

Thanks

ceorron

aka

Richard Cookman