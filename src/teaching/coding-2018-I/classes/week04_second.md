# 2018.02.28-03.01 #

## Class's plan ##
- solve all problems in quiz
- hand them out the guide for the week
- what did we see last week
- ask students to give me a list of things that could go wrong and make a program don't run
- explain the guide: what is semantics, syntaxis, and lexicon
- explain phonetic of vowels (chart for the phonetics)
- put exercise to integrate a simple function
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
- tell them to read the whole book, I may assume you know all that it is in the book,
  there are many little details that I explain in the book that I may not do in class,
  because
- put more exercises

### Executed actions ##
- solved all problems in quiz
- handed them out the guide for the week
- explain the guide: what is semantics, syntaxis, and lexicon
- explained to group one the trick on swaping two variables
- put exercise on how to integrate a function ($x^2$) between two values (group one)
- put exercise (for group 2) on printing a rectangle made of `a`s in console:
    ~~~
    ########
    #      #
    #      #
    #      #
    ########
    ~~~
- explained phonetic of -ing (and the spanish word "mango")
- told them when is the exam (week before "semana santa")

## Homework ##

## Notes ##
