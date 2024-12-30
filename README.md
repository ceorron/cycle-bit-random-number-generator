# cycle bit scalable psuedo random number generator (rcb-generator)

rcb-generator is a new kind of psuedo random number generator. rcb-generator is a bit pattern generator made to be fast, scalable, high quality psuedo random number generator.

rcb-generator is provided as a C++ source file (single header file) or C source and header files.

MIT Licence - See Source/License file

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

```C
#include <stdio.h>
#include <time.h>

#include "rcb_generator.h"

int main() {
    /* seed the random number generator with the system clock */
    rcb_gen rnd;
    rcb_init(&rnd, time(NULL), 0);

    /* get a random number */
    unsigned random_number = rcb_rand(&rnd);

    /* print it */
    printf("random number generated : %u", random_number);
    return 0;
}
```

To change the bit size of the data stored in and returned from the C code for rcb_generator, edit `RCG_T_TYPE` in `rcb_generator.h` to the desired unsigned type.

# more on rcb-generator design

rcb-generator provides fast, scalable, random number generation with a very good period. 2<sup>8N</sup> minimum, when using C code or default C++. (see C++ differences, below, for details).

rcb-generator is fast; slower than many shift/modulo/xorshift generators but faster than more complex pseudo random number generators.

Because rcb-generator operates on a bit pattern, not on a value, this makes the generator highly scalable and reusable, unlike other shift/modulo generators/MT and random number generators in general.

# C++ differences

Note that there are differences between the C and C++ versions (as of Feb 2020).

The C++ version now has :
 - scalable internal count template variable (CntN)

If you are setting the scalable internal count template variable (CntN) the minimum period is 2<sup>8N</sup>. N being the number of bytes chosen. (NOTE the default uses N == sizeof(T), the same as the C code).

This means that the two version will produce different values if a non default internal count template variable (CntN) is used.

# reseed

In both the C and C++ version, at construction, you can opt to turn on automatic reseed.

If you set reseed == true on construction the maximum period is 2<sup>2bit-length(T) + 8N</sup>. Minumum period is still 2<sup>8N</sup>.

# rcb_fast_generator

As of August 2020 a new random number generator was added building off of the original ideas in the first generator, however this generator would specifically aim to be fast, as fast as the fastest xorshift generators but still giving excellent statistical correctness while incorporating ideas from the original rcb_generator.

This makes rcb_fast_generator, potentially, the best random number generator to date. Giving the speed of an xorshift generator with better statistical qualities and a long period of at minimum 2<sup8N</sup>.

# rcb_generator catches up

Optimisations to rcb_generator, in June 2023, mean that it now rivals rcb_fast_generator for speed. The output is still exactly the same, meaning the two are extremely fast while producing very high-quality random numbers.

MIT Licence - See Source/License file

```C++
#include <iostream>
#include <ctime>

#include "rcb_fast_generator.hpp"

using namespace std;

int main() {
    //seed the random number generator with the system clock
    rcbg::rcb_fast_generator<unsigned> rnd(time(NULL));

    //get a random number
    unsigned random_number = rnd.rand();

    //print it
    cout << "random number generated : " << random_number << endl;
    return 0;
}
```

```C
#include <stdio.h>
#include <time.h>

#include "rcb_fast_generator.h"

int main() {
    /* seed the random number generator with the system clock */
    rcb_fast_gen rnd;
    rcb_fast_init(&rnd, time(NULL), 0);

    /* get a random number */
    unsigned random_number = rcb_fast_rand(&rnd);

    /* print it */
    printf("random number generated : %u", random_number);
    return 0;
}
```

Please use and let me know what you think.

Thanks

ceorron

aka

Richard Cookman
