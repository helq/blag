# 2018.02.26-27 #

## Class's plan ##
- what are valid names for variables
- Booleans in C++ (how are they represented)
- ask students to give me a list of things that could go wrong and make a program don't run
- more about phonetics (th's, vowels, and aspiration)
- show example of floating number from the wikipedia into c++, how we can set bit per bit
  and get some number <https://en.wikipedia.org/wiki/Single-precision_floating-point_format>
- show them binary operations
- explain what the `^` operation does
- show them how to cypher a bit, and a whole number, using _xor_
- show them trick about how to verify if three numbers as input are the angle of a
  triangle using an auxiliary variable:
    ~~~
    int a = 20;
    int b = 40;
    int c = 120;
    bool failed = false;
    if ( a<=0 ) {
      std::cout << "a is too small :(" << std::endl;
      failed = true;
    }
    if ( b<=0 ) {
      std::cout << "b is too small :(" << std::endl;
      failed = true;
    }
    if ( c<=0 ) {
      std::cout << "c is too small :(" << std::endl;
      failed = true;
    }
    if ( !failed && a+b+c==180 ) {
      std::cout << "It is indeed possible to construct a triangle with those angles" << std::endl;
    } else {
      std::cout << "too sad! it isn't possible to construct a triangle with those angles" << std::endl;
    }
    ~~~
- explain property of `&&` to never try to execute the second argument if the first is
  false
- tell them to read the whole book, I may assume you know all that it is in the book,
  there are many little details that I explain in the book that I may not do in class,
  because

### Executed actions ##
- what are valid names for variables (ok: `inta`, `int0`, `a_0`, `B_0`; not ok: `0ue`,
  `int`, `float`, `0_`)
- Booleans in C++ (how are they represented)
- show them binary operations
- explain what the `^` operation does
- show them how to cypher a bit, and a whole number, using _xor_
- Explained them how to exchange two variables values using only xor:
    ~~~
    * a ^= b     =>      a = a ^ b
    * b ^= a     =>      b = a ^ b
    * a ^= b     =>      a = a ^ b
    ~~~
  using another variable:
    ~~~
    * a_ = a ^ b
    * b_ = (a_ ^ b) = ((a ^ b) ^ b) = a
    * a__ = (a_ ^ b_) = ((a ^ b) ^ a) = b
    ~~~
- what is the difference between `&&` and others `&`
- explain property of `&&` to never try to execute the second argument if the first is
  false
- explained `+=` and other simplified operators
- more about phonetics (th's, and aspiration)
- show example of floating number from the wikipedia into c++, how we can set bit per bit
  and get some number <https://en.wikipedia.org/wiki/Single-precision_floating-point_format>
- put exercise on how to integrate a function between two values (group two)

## Homework ##

## Notes ##
