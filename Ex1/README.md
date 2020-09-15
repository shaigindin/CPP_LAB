in this ex we had to understand the concept of finite fields and build finite field class and number inside
finite fields. therefore, it only make sense that a number instance will hold its own field instance.
because in finite fields we have order and arithmetic operators it is only make sense to implement the operators
as expected.
in this exercise we practice mostly building simple classes and basic function overloading.
because the design was made by the staff everything was straight forward.
there was not much design decision however i decided to implement the GFNumber class with long* array that will
holds the prime factors of the number. because the only "heavy" demand is for finding n primes, i decided that this
process will run only once. therefore, in the first call for printPrimes() or getPrimes() all the primes will be
saved in the array. Now, each time the user will call printPrimes() it will be printed directly and will save runtime
cost. if user will call getPrimes(), i allocated memory and made a "deep copy" of the long array.
the user will get GFNumber* pointer to allocated memory and it his *duty* to release this memory.
i think it is a bad decision of the designer but i couldn't change it. therefore i give the user a deep copy so
that at least i can delete my own allocated memory without concerns that the user freed me memory.

we have been asked to use Pollard algorithm and it was really hard for me to understand the logic behind the algorithm
so in the beginning, i just translated the pseudo code from the ex pdf. however, there WAS A MISTAKE in the code.
in addition, it was uncleared if we should use long numbers or GFNUmber.
after i spent many hours because of infinite loops i study the algorithm logic and understand the mistakes.
all and all, it is very sufficient algorithm which saves a lot of run time.

there were no runtime demands