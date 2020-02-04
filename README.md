# cycle bit scalable psuedo random number generator (rcb-generator)

rcb-generator is a new kind of psuedo random number generator. rcb-generator is a bit pattern generator made to be fast, scalable, high quality psuedo random number generator.

rcb-generator is provided as a C++ source file (single header file) or C source and header files.

MIT Licence - See Source/License file
v

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
    rcb_init(&rnd, time(NULL));

    /* get a random number */
    unsigned random_number = rcb_rand(&rnd);

    /* print it */
    printf("random number generated : %u", random_number);
    return 0;
}
```

To change the bit size of the data stored in and returned from the C code for rcb_generator, edit `RCG_T_TYPE` in `rcb_generator.h` to the desired unsigned type.

# more on rcb-generator design

rcb-generator provides fast, scalable, random number generation with a very good period (2<sup>bit-length</sup> minimum).

rcb-generator is very fast; slower than many shift/modulo generators but about twice as fast (or more) than Mersenne Twister in my tests.

Because rcb-generator operates on a bit pattern, not on a value, this makes the generator highly scalable and reusable, unlike other shift/modulo generators/MT and random number generators in general.

# C++ Differences

Note that there are differences between the C and C++ versions (as of Feb 2020).

The C++ version now has :
 - optional automatic reseed (off by default)
 - scalable internal count variable

This means that the two version will produce different values after the reseed point (if reseed enabled), and/or if a non default internal count variable size is used.

Please use and let me know what you think.

Thanks

ceorron

aka

Richard Cookman

# sample output
first 500 numbers with T == uint32_t, seed == 0

```C	[ 4294963667 ]
	[ 2133890565 ]
	[ 425129385 ]
	[ 1362748505 ]
	[ 1963842932 ]
	[ 2321861801 ]
	[ 3345617667 ]
	[ 3232206751 ]
	[ 978834774 ]
	[ 385829056 ]
	[ 753487869 ]
	[ 1172506996 ]
	[ 2309357337 ]
	[ 16849875 ]
	[ 1280618151 ]
	[ 234803628 ]
	[ 2934035053 ]
	[ 609955222 ]
	[ 3961027388 ]
	[ 115493263 ]
	[ 955133128 ]
	[ 1946173069 ]
	[ 1521749013 ]
	[ 981029052 ]
	[ 1771670761 ]
	[ 3596481950 ]
	[ 2713120402 ]
	[ 1090342078 ]
	[ 3082687689 ]
	[ 1801604503 ]
	[ 799688533 ]
	[ 1559129420 ]
	[ 383453389 ]
	[ 2462901945 ]
	[ 1913966345 ]
	[ 1089543343 ]
	[ 1862363290 ]
	[ 2277571556 ]
	[ 368195418 ]
	[ 3014074211 ]
	[ 2078957246 ]
	[ 1651152968 ]
	[ 1852806398 ]
	[ 14013969 ]
	[ 22660536 ]
	[ 4154141762 ]
	[ 1520192085 ]
	[ 3038742136 ]
	[ 2142115342 ]
	[ 2035931194 ]
	[ 3840512739 ]
	[ 818408724 ]
	[ 1656499477 ]
	[ 3290580307 ]
	[ 1013817100 ]
	[ 816700397 ]
	[ 3287543096 ]
	[ 2806563434 ]
	[ 3444459285 ]
	[ 3078102654 ]
	[ 2548987699 ]
	[ 3561927049 ]
	[ 1612948092 ]
	[ 3535536471 ]
	[ 3165355748 ]
	[ 2378911724 ]
	[ 2887314387 ]
	[ 1527566855 ]
	[ 3763544570 ]
	[ 493611171 ]
	[ 1488285536 ]
	[ 3565438414 ]
	[ 3223398801 ]
	[ 1854057569 ]
	[ 504493461 ]
	[ 1433663744 ]
	[ 1638738358 ]
	[ 918799123 ]
	[ 3885457698 ]
	[ 118236287 ]
	[ 4210175784 ]
	[ 4185748142 ]
	[ 2968200412 ]
	[ 3668761629 ]
	[ 1521849194 ]
	[ 370852635 ]
	[ 3432508141 ]
	[ 1345970978 ]
	[ 1994319309 ]
	[ 4093722509 ]
	[ 1254890139 ]
	[ 1471977989 ]
	[ 2736612542 ]
	[ 3636699014 ]
	[ 744053561 ]
	[ 866646539 ]
	[ 858852797 ]
	[ 1747950103 ]
	[ 3579223503 ]
	[ 3130719188 ]
	[ 2441929231 ]
	[ 533714369 ]
	[ 2852806015 ]
	[ 2632025064 ]
	[ 1029065569 ]
	[ 3281703975 ]
	[ 989269197 ]
	[ 2865854525 ]
	[ 2702132820 ]
	[ 3927015728 ]
	[ 1666536306 ]
	[ 4025847390 ]
	[ 2474018819 ]
	[ 2387442563 ]
	[ 140584080 ]
	[ 2607546226 ]
	[ 2841934064 ]
	[ 3221341240 ]
	[ 1923930496 ]
	[ 55809341 ]
	[ 335818278 ]
	[ 2729988330 ]
	[ 2798924850 ]
	[ 2157544940 ]
	[ 2753779869 ]
	[ 2163343039 ]
	[ 3136012461 ]
	[ 3780923310 ]
	[ 1548968277 ]
	[ 2298873769 ]
	[ 2231173108 ]
	[ 4196675425 ]
	[ 63485263 ]
	[ 3995284953 ]
	[ 3780126548 ]
	[ 2312002351 ]
	[ 3515575650 ]
	[ 812054655 ]
	[ 2618519101 ]
	[ 3734016060 ]
	[ 257091497 ]
	[ 3926213696 ]
	[ 3650801091 ]
	[ 518044165 ]
	[ 1336472648 ]
	[ 394162338 ]
	[ 4124746524 ]
	[ 913718 ]
	[ 3015742361 ]
	[ 3954393791 ]
	[ 4154518459 ]
	[ 2038464679 ]
	[ 2987480844 ]
	[ 1698576470 ]
	[ 3515468055 ]
	[ 1681955483 ]
	[ 4137488944 ]
	[ 3950231218 ]
	[ 1554764406 ]
	[ 3191495315 ]
	[ 850921033 ]
	[ 3216317149 ]
	[ 4063945575 ]
	[ 2125270121 ]
	[ 3756356987 ]
	[ 999598155 ]
	[ 1814453657 ]
	[ 1511859939 ]
	[ 138043541 ]
	[ 2363925315 ]
	[ 779569087 ]
	[ 4230773797 ]
	[ 1803604146 ]
	[ 1260748986 ]
	[ 2922390448 ]
	[ 670733274 ]
	[ 1493249497 ]
	[ 1829370297 ]
	[ 2876009576 ]
	[ 1767768201 ]
	[ 2918414309 ]
	[ 2713086203 ]
	[ 930314281 ]
	[ 290905485 ]
	[ 4271479306 ]
	[ 4082802332 ]
	[ 1293219016 ]
	[ 3181054535 ]
	[ 1324081666 ]
	[ 1479625390 ]
	[ 1520816409 ]
	[ 585028511 ]
	[ 3394628879 ]
	[ 4008543941 ]
	[ 459025144 ]
	[ 3212515764 ]
	[ 3937066695 ]
	[ 2825442105 ]
	[ 1972487759 ]
	[ 1369946088 ]
	[ 1813508339 ]
	[ 326053250 ]
	[ 1956244782 ]
	[ 345932299 ]
	[ 2850946963 ]
	[ 578901100 ]
	[ 3902977761 ]
	[ 3005661867 ]
	[ 3793262436 ]
	[ 1842290050 ]
	[ 3936358432 ]
	[ 1197158464 ]
	[ 1093231454 ]
	[ 1657349402 ]
	[ 1881501146 ]
	[ 918098263 ]
	[ 1024215668 ]
	[ 2292195780 ]
	[ 1416164046 ]
	[ 3291182859 ]
	[ 1431968584 ]
	[ 3167302410 ]
	[ 376612609 ]
	[ 174677348 ]
	[ 2368164453 ]
	[ 1347882529 ]
	[ 140858695 ]
	[ 3625322837 ]
	[ 1105685350 ]
	[ 4046852520 ]
	[ 810248811 ]
	[ 559678663 ]
	[ 4178550183 ]
	[ 3123666938 ]
	[ 3417227516 ]
	[ 1253750533 ]
	[ 891935348 ]
	[ 1375938585 ]
	[ 2411359557 ]
	[ 1105890676 ]
	[ 721031229 ]
	[ 811602431 ]
	[ 1006122581 ]
	[ 981196866 ]
	[ 2300091265 ]
	[ 1582587577 ]
	[ 2436805257 ]
	[ 226715913 ]
	[ 3495311675 ]
	[ 226377141 ]
	[ 1069915193 ]
	[ 417869070 ]
	[ 885964783 ]
	[ 3612326179 ]
	[ 435193238 ]
	[ 198545537 ]
	[ 3435083090 ]
	[ 304960950 ]
	[ 2358893230 ]
	[ 2337483383 ]
	[ 1196699673 ]
	[ 3577967491 ]
	[ 361665821 ]
	[ 1638389750 ]
	[ 2099204132 ]
	[ 3572538747 ]
	[ 987062082 ]
	[ 2139557880 ]
	[ 3238268502 ]
	[ 4016419948 ]
	[ 2009082356 ]
	[ 3355221522 ]
	[ 298334695 ]
	[ 2486526251 ]
	[ 1928909387 ]
	[ 4255002441 ]
	[ 3085849757 ]
	[ 2316722653 ]
	[ 2853651899 ]
	[ 1974489268 ]
	[ 2869175909 ]
	[ 3476409323 ]
	[ 652118463 ]
	[ 2599480996 ]
	[ 2478298047 ]
	[ 2525160359 ]
	[ 586852176 ]
	[ 3809610701 ]
	[ 2201243852 ]
	[ 1034324112 ]
	[ 27913888 ]
	[ 1110766916 ]
	[ 2378372437 ]
	[ 452430051 ]
	[ 984343455 ]
	[ 3919304322 ]
	[ 1870166170 ]
	[ 1823890532 ]
	[ 1914549158 ]
	[ 2518700201 ]
	[ 914785570 ]
	[ 4220961237 ]
	[ 750908062 ]
	[ 3379367257 ]
	[ 2158669755 ]
	[ 591616908 ]
	[ 3882163640 ]
	[ 3296434470 ]
	[ 1732405481 ]
	[ 1751699 ]
	[ 855482005 ]
	[ 3669275112 ]
	[ 477322735 ]
	[ 3044654140 ]
	[ 2237736024 ]
	[ 2471314128 ]
	[ 1074611561 ]
	[ 176885552 ]
	[ 2840620031 ]
	[ 2536356214 ]
	[ 440942667 ]
	[ 2108009951 ]
	[ 2678173614 ]
	[ 110364367 ]
	[ 1596016890 ]
	[ 1939565068 ]
	[ 2258849060 ]
	[ 2098854998 ]
	[ 1143786541 ]
	[ 2407502935 ]
	[ 4018591277 ]
	[ 1901969512 ]
	[ 3993649013 ]
	[ 3634718756 ]
	[ 3867587224 ]
	[ 2736159926 ]
	[ 4133373920 ]
	[ 4187172303 ]
	[ 594706291 ]
	[ 3238701388 ]
	[ 3882927941 ]
	[ 4024460541 ]
	[ 1896897825 ]
	[ 3205750233 ]
	[ 2796400426 ]
	[ 3342180458 ]
	[ 2625319831 ]
	[ 1786396782 ]
	[ 4224004706 ]
	[ 1415038181 ]
	[ 3836739427 ]
	[ 3641486758 ]
	[ 2590124942 ]
	[ 2511344729 ]
	[ 3969869299 ]
	[ 2069423311 ]
	[ 218032826 ]
	[ 3210222570 ]
	[ 1404540274 ]
	[ 2955109802 ]
	[ 2582724261 ]
	[ 2835768715 ]
	[ 271366613 ]
	[ 771167905 ]
	[ 2133220265 ]
	[ 1571414124 ]
	[ 1491587436 ]
	[ 230415915 ]
	[ 615356990 ]
	[ 1290992900 ]
	[ 637109952 ]
	[ 2797905194 ]
	[ 4087084339 ]
	[ 1281535552 ]
	[ 2276389061 ]
	[ 3622243347 ]
	[ 1252468660 ]
	[ 2107695016 ]
	[ 1968439595 ]
	[ 280795789 ]
	[ 1316855858 ]
	[ 935752921 ]
	[ 2316284291 ]
	[ 2987094187 ]
	[ 843870006 ]
	[ 4071667915 ]
	[ 130270895 ]
	[ 3846934106 ]
	[ 3100299558 ]
	[ 3816084062 ]
	[ 2989105978 ]
	[ 2809272942 ]
	[ 1197614463 ]
	[ 2435546677 ]
	[ 64134741 ]
	[ 1535743096 ]
	[ 4021356887 ]
	[ 1676325683 ]
	[ 2807436599 ]
	[ 2726327328 ]
	[ 2717784722 ]
	[ 2229412375 ]
	[ 1353881315 ]
	[ 1980044337 ]
	[ 882164654 ]
	[ 952594745 ]
	[ 954854857 ]
	[ 2478071391 ]
	[ 3398789036 ]
	[ 2650950978 ]
	[ 4087020853 ]
	[ 1689631808 ]
	[ 3411104630 ]
	[ 657933276 ]
	[ 4185232310 ]
	[ 2220125601 ]
	[ 1077557860 ]
	[ 2834962104 ]
	[ 7262889 ]
	[ 3996909370 ]
	[ 1357080803 ]
	[ 1008899584 ]
	[ 3640202395 ]
	[ 235205014 ]
	[ 3960317003 ]
	[ 2772479371 ]
	[ 4226134824 ]
	[ 3814152600 ]
	[ 3523390724 ]
	[ 2270262738 ]
	[ 1770390235 ]
	[ 1424254557 ]
	[ 3073265187 ]
	[ 2216285640 ]
	[ 1707182559 ]
	[ 1183954840 ]
	[ 429514017 ]
	[ 1462625287 ]
	[ 1576666313 ]
	[ 3268179231 ]
	[ 2452150589 ]
	[ 33922625 ]
	[ 3980301132 ]
	[ 2541187928 ]
	[ 3633680794 ]
	[ 4060089877 ]
	[ 1685450879 ]
	[ 1872334560 ]
	[ 689881007 ]
	[ 1942383918 ]
	[ 408325851 ]
	[ 2831428196 ]
	[ 634239117 ]
	[ 2076931571 ]
	[ 2164134285 ]
	[ 2587346226 ]
	[ 4168691245 ]
	[ 2133818243 ]
	[ 4094851711 ]
	[ 4279621464 ]
	[ 1196619584 ]
	[ 293589610 ]
	[ 3629754728 ]
	[ 3853152890 ]
	[ 4146247426 ]
	[ 3973523531 ]
	[ 3585310351 ]
	[ 2093322126 ]
	[ 3413265547 ]
	[ 2306984532 ]
	[ 337449013 ]
	[ 3315100758 ]
	[ 2204474467 ]
	[ 3089343027 ]
	[ 757468286 ]
	[ 495471067 ]
	[ 2207467614 ]
	[ 4124669482 ]
	[ 1955493245 ]
	[ 3505300226 ]
	[ 1649929193 ]
	[ 2131043523 ]
	[ 2393797223 ]
	[ 3524845840 ]
	[ 3476980798 ]
	[ 1957592145 ]
	[ 1145366007 ]
	[ 1381900382 ]
	[ 2038988117 ]
	[ 2037097659 ]
	[ 17813692 ]
	[ 1275290884 ]
	[ 1230152152 ]
	[ 1805851610 ]
	[ 2569620840 ]
	[ 3220149199 ]
	[ 420967160 ]
	[ 3347193648 ]
	[ 3675638073 ]
	[ 3046230717 ]
```
