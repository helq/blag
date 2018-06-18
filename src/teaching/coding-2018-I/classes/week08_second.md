# date #

## Class's plan ##
- Ask if somebody wants to be corrected, if they want to see the answers to some of the
  questions from a single student
- Create groups on the fly, in front of all students, the groups for projects
- Try to explain recursion asking them to tell me what a program did (kinda exercise and
  explanation):
  * first what a for loop outputed in console
  * then what a for loop in reverse outputed in console
  * then what a recursive function (outputing the thing above) outputed
  * asked them to write down a recursive function to output what the original forward loop
    outputed
  * now a recursive function that returns something (a simple addition)
  * now a recursive function that returns the factorial of something
- Now that we have some examples, I should explain to them the two main kinds of recursive
  functions, the ones with `void` (which usually are impure) and the ones which return
  something (usually "pure")
- Exercises on converting a for loop into a recursion (two exercises, one per type of
  recursive function)
- remind them about "tutorías"
- Exercises on converting a recursive function into a for loop (two exercises)
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

### Executed actions ##
- Created groups on the fly, in front of all students, the groups for projects
- Left them select from the following list the game they wanted to code (the minus sign
  before some games is for games which can be found in the internet already implemented):
  * -tetris
  * -2048
  * -maze
  * -connect four
  * -battle ship
  * -pong
  * -breakout
  * -sokoban
  * memory puzzle
  * sliding puzzle
  * bloxorz
  * abalone
  * pipe dream
  * frogger
  * brick game car racing
  * tank brick game https://www.youtube.com/watch?v=NO-AocePNYQ
  * minesweeper
  * invaders
  advanced:
  * -pacman
  * scrabble
  * black jack
  * chess.
  (more options from:
  <https://inventwithpython.com/blog/2012/02/20/i-need-practice-programming-49-ideas-for-game-clones-to-code/>)
- Tried to explain recursion asking them to tell me what a program did (kinda exercise and
  explanation):
  * first what the of for loop execution will output in the end on console
  * then what a recursive version of the function above
  * another for loop but without modifying any variable, just printing in console inside
    the loop
  * void function equivalent to the for loop above
  * asked them to convert three different for loops into recursive functions:
    - a `for` which accumulates some result per iteration
    - a `for` which prints in console
    - a combination of the two types of loops, two loops one inside the other
  * asked them to convert a recursive function into its equivalent for loop

## Homework ##

## Notes ##
