# 2018.04.09 #

## Class's plan ##
- Check exercises I left for home about how to convert a recursive function into a for
  loop (two exercises)
- Explain to them why is the distinction between `void` and non-`void` functions
  important. In the game we will like to have the state of the game be modified by a set
  of functions (even if they're not recursive), and another functions will be in charge of
  printing the game on screen.
- Now that I think about it, there is another way to represent a loop computation as a
  recursion, using the techinique of tail call recursion, though this can only be done in
  certain circumstances (this is basically a foldl, a foldr may be harder to write in the
  tail call way). The best thing to show them, it's how to write recursive functions that
  have an additional parameter (accum) which is used to accumulate the computation and
  pass it to the next stage in the "loop"
- Show them a simple program using the "ncurses" library, code in front of them `hangman`
  to show them how to use the library, and what many of the functions do.

### Executed actions ##
- Asked who had done the exercises
- Very little actually did the exercises
- Explained to them references

## Homework ##

## Notes ##
