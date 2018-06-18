---
geometry: # regular letter size is 215.9 wide by 279.44 long
  - "verbose"
  - "letterpaper"
  - "textwidth=190mm"
  - "textheight=235mm"
  #- "voffset=7mm"
  #- "lmargin=22mm"
#  - "paperwidth=275.9mm"
#  - "paperheight=279.4mm"

...

\pagenumbering{gobble}

<!--TODO: Normalise tenses in the story -->

<!--
# comment filter line to see what is hidden
 pandoc \
  -H 00-header.tex \
  --filter ./put_blanks_filter.sh \
     week04_second_material.md \
  -o week04_second_material.pdf
-->

# Languages, history and other stuff (2018.02.28-03.01) #

Lexemes are the minimum thing with a meaning, many lexemes make a lexicon.

Syntaxis (grammar is another thing, and it is a term often used in philology) is how to
organize stuff correctly. (The rules used to costruct things, like in `C++` a `;` is
always mandatory at the end). Kinda similar to grammar, but not quite, not in the context
of natural languages.

Semantic is how to interprete a some combination of stuff. Add meaning to ordered stuff.

Examples of lexicon, syntaxis and semantics in different "languages":


|           | Machine Code | Assembler          | C++ [`some-space`](~h) | Natural language   | Propositional calculus |
|:---------:|--------------|--------------------|------------------------|--------------------|------------------------|
| Lexicon   |     01       | `addx` (mnemonics) | [`int`,`{`,`&&`](~h)   | Go to philology ;) | $)$, $p$, $q$, $\vee$  |
| Syntaxis  |              |                    |                        |                    |                        |
| Semantic  |              |                    |                        |                    |                        |

Where does the compiler fits in the table ( it converts something from a high level
language to machine code )

# Other stuff #

- empty set: The empty set which has no elements, and we can usually get it by creating a
  set which definition impedes all elements to keep it in, e.g., $x = x + 1$. No number
  can meet that. We are using here set comprehension, show them how it can be used to
  define sets
- operators: `and` is onjunction, `or` is disjunction and `negation` is negation
- valid variables in C++: all that can be made with `[a-zA-Z_][a-zA-Z0-9_]`
- Reserved keywords: There are many of these things made of what you could consider a
  valid variable but not, some of them are the builtin types: `int`, `double`, but also
  `for`, `while`... \todo{find all}
- use of `%` only with integers
- explain what is an interpreter
- fbf (fórmulas bien formadas), adding as all the necessary parenthesis to make it look
  weird XD. The rules are in page 17
- (table with) precendence of all operators, all! `% ! && || << >> < > + * - / ...`
- precendence of all logical operators `^ v -> <->`
- give students a hard time using some of the examples for the exam:
  `a/b*d%c-d>4.0||a==3&&10!=int(d)` (many examples of this)
- how to get logically equivalent formulas from the truth table and by applying rules
  (explain rules of logic, how to do it)
- remember to tell them what is tautology, contradiction and contingency (!!)
- propositional calculus (lógica propositional en español) is composed of: propositional characters, logic connectives, and
  auxiliary symbols (parenthesis)
- logically equivalent formulas, how to use the laws of logic to arrive from one
proposition
  (preposición) to another
- explain precendence of logical proposition
- what is a well formed formula
- what is a proposition (proposición), and what makes a phrase a proposition and what doesn't, for example:
  * socrates is mortal (is a proposition)
  * a dog which eats (is NOT a proposition!)
  * x+y=15 (is not a proposition, it is implicitely quantified)
  proposition are those which talk explicitely about a person or object, and a determinate
  action. If it includes a "for all", or "exists", it isn't a proposition.
- show examples of valid proposition and invalid proposition (imperatives, questions, and
  doubtful ideas are not proposition)
- explained predicates with "for all" or "exists" (quantified prepositions)
- table explaining what a preposition has and what a predicate has
- examples of predicates like: P(x): x is negative, and (forall x: (P(x) or x==0 or P(-x)))
- explain how to use the laws of predicates to convert from one to another predicates,
  example: ¬(forall x: P(x)) <=> exists x: ¬P(x), and all the other things
  this are not equivalent: (forall x: exists y: Q(x,y)), and (exists y: forall x: Q(x,y)),
  the usual example is: for all students in some class there exists a girl for them, than
  there exists a girl for all students of a class
  others are: forall x: (P(x) and Q(x)) => forall x: P(x) and forall x: Q(x)
- talk about the domain of discourse
- talk about the meaning of P(x) in a domain of discourse (either, truth or false)
- talk about modus ponens, hypothetic silogisms, and modus tollens, and the other rules of inference
- talk about logical equivalences
- there are many ways to define a number in C++, one is doing it in decimal, or octal, or
  hexadecimal, or binary
- example of converting some phrases in spanish to propositions or predicates
- C++ functions to convert a float into an int, floor, ceil, (int), round, "frac"
- explain why sometimes they can find code without `std::cout` but just `cout`, I don't
  like it but it is important
- use the weird E symbol to define the truth value in a domain of discourse
- how is truth and false written in math equations, usually (T and `bottom`)

- size of a set: cardinal (for finite sets that is a natural number)
- sets are equipotent if they have the same cardinal
- what are disjunct sets
- parts function and its cardinal (2^n, where n is the cardinal of the original set), and
  many examples
- all possible operations with sets, that includes: disjunction, conjunction, symetrical
  disjunction, complement (over a universe), and difference
- what is AxB (ordered pairs), and what it's cardinal
- laws of sets (very similar to the laws of prepositions, both are examples of boolean
  algebras)
- examples of unitary sets, and emtpy set
- what is the cardinal of the union of two sets defined with the intersection of two sets
- how all possible operations can be defined defined with "for all", `and` and `or`

- explain how are relations defined
- explain frequent representation of functions as relations with a (or some) special
  restriction
- examples of definition of functions in this manner:
  - f: R x B x N -> B
    (a,b,c) |-> a*c > 20 or b
  - convert a centigrade into fahrenheit
  - area of a rectangle to use in the integral function
  - number of students in howards (using a single integer to represent three) and the many
    more precise ways to represent it using R and Ns:
    * (N x N x N) -> N
    * N -> N
    * ({1..31} x {1..12} x Z) -> N // for this class of restrictions we need to define an if to check
    * int num_students(int day, int month, int year)
    * int num_students(int daymonthyear) // and how to get the individual values from it
  - more examples of day to day stuff, like:
    to aprove my class you need not to do weird things, you need 3.0 or more on your final
    score, plus no funny business with copying to others in quizzes or exams
- the correspondence between integers/natural, bools, reals, ASCII, with the datatypes
int, bool, double, and char
- add examples to book of floating numbers with explicit exponents
- range (also image) and dom (where the preimages live) of functions (example, x^2, x^3,
  x^2 + y^2 = 0 (this is not a function, why?), sin(x), )
- the types of things we require when somebody gives us a problem, for example the types
  if you need to calculate the price of transportation in the city, depending on what
  medium you take
- explain explicity casting
- explain difference between defining the type of function and defining what it does, the
  body of the function
- the properties symetry, transitivity, antisymetry, reflexibility (for this, give them a
  taste on what each one of the types of relations do, and what is need it for each one of
  them)
- explain what means for a relation to be preorder, equivalence, order
- number of possible relations from two sets
- how to convert math functions into C++ functions
- talk about inyectivity, biyectivity,
- how to compose functions, and what is the power of it (this could be used just to
  explain the power of higher order functions)

- additionally explain what is std::cin, and why you don't want to show them how to use
  it, it is just an annoyance
- explain switch, and how it can make some things simpler to write (it allows us to group
  things), give example of using switch with the scores of grades
- return breaks the flow of a function execution if it put anywhere but not a the end,
  which is usually pretty annoying
- if you don't use brakets `{}` when using if, while, or others, you risk to ... it's
  just ugly, don't do it
- ask for the trace of several different program executions

- the value of how difficult is a question is, well, not well implemented. Many people
  write their opinions on how hard it is and many simple exercises are graded as hard, and
  viceversa
- there are questions that are badly classified
- this exam will be ugly, because the exam is all about theory behind programming, or
  better, the relation of theory and C++. But the other exams will be all about
  programming, and you know what? you are gonna be awesome at them, we will get deeper on
  the programming part of the class and the theory will be there, but just sporadically
  shown
- the first exam is, almost, basically a soft exam on fundamentals of math
- did you remember I was telling you to take the class Fundamentals of math, well I still
  think you should, but what I don't like is trying to convert a class into another
  because, well, that's what the people who made the class thought about it. This class
  pretends to be a mini fundamentals of math focused to programming, but if you truly want
  to code in C++14, performant and well written code, then this is no the class you should
  take. If you want to have some backaground on the relation of this class and math, then
  you're welcome
- the students may be very unlucky, because a student can see at most 15 questions, and
  they may be about anything, there are thousands of questions, and of the many kinds,
  therefore anything I will give them could appear there, they need to memorize a lot of,
  often, not so useful information

<!-- vim:set filetype=markdown.pandoc : -->
