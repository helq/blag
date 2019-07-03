---
title: "Understanding Higher Rank Polymorphism: A small guide using Typed Lambda Calculus"
started_writing: 2017-06-26 11:41 (COT)
date: 2017-06-28 13:08 (COT)
updated: 2019-07-03 13:00 (COT)
tags: development, haskell, lambda calculus, learning
---

**Disclaimer:** I'm not an expert on type systems. I was just trying to figure out what
"higher rank polymorphism" means and found useful to use some ad-hoc Typed Lambda
Calculus.  For what I've been reading for the last hour, all "code" below is in something
close to "System F" ([wikipedia][wSf], and [an in-depth explanation of System F with an
interpreter and actual runnable code][blynnSf]).

[wSf]: https://en.wikipedia.org/wiki/System_F
[blynnSf]: https://crypto.stanford.edu/~blynn/lambda/systemf.html

As I understand, Typed Lambda Calculus is the basis of Haskell, so it makes sense to try
to understand what something means in Haskell by studying it first in Typed Lambda
Calculus. That is why, I have written this little guide to understand "Higher Rank
Polymorphism" using Typed Lambda Calculus.

For those of you who don't know what Lambda Calculus is, I've written a micro-introduction
below. If you know what Lambda Calculus is, jump ahead to the Typed Lambda Calculus
Explanation section.

## Lambda Calculus ##

In the 1920's, at the same time that Turing was formulating his "Turing Machine", another
guy called [Alonzo Church][church] (a friend of Turing) was also working in the problem of
computability. Alonzo formulated what we know now as lambda calculus. Church and Turing
proved that both formulations were equivalent, meaning that anything you can do with a
Turing Machine can be done with Lambda Calculus. Basically, Haskell and C have the same
power to compute anything[^C-not-turing-complete].

[church]: https://en.wikipedia.org/wiki/Alonzo_Church

[^C-not-turing-complete]: This is not actually truth because C is not Turing Complete, but
  for the sake of simplicity we will assume that C and Haskell are both Turing Complete.
  The main problem arises from C's way to access to memory. C is limited by the size of
  pointers, which in theory limits it from being truly Turing Complete, but in practice is
  just as powerful as Haskell. For further discussion take a look at this fantastic thread
  in stack exchange: https://cs.stackexchange.com/questions/60965/is-c-actually-turing-complete

In Lambda Calculus we have terms. Terms are:

- **Variables**. They are denoted by single characters, e.g., `x`, `a`, `w`, ...
- **Abstractions**. They are like function definitions, we build an abstraction using a
    variable and a term. Abstractions are denoted by `(λx.M)` (where `x` is a variable
    and `M` a term).
- **Applications**. Abstractions let us build bigger terms, and applications let us apply terms to
    abstractions.

    For example, `(λx.x+1) 2` is an application of `(λx.x+1)` with the term `2`. When we
    [reduce][][^reduce] this application we get[^betareduction] the term `2+1`[^further].
    Applications are denoted by two terms and a space! How weird is that! I mean, this `E M`,
    this `(λx.x+1) 2`, and this `y (λx.x**2)` are all valid applications (terms)
    in lambda calculus[^haskelllambda].

[reduce]: https://ro-che.info/ccc/18 "A link to a cartoon explaining the difference between equality and reduction"

[^reduce]: Lambda Calculus is like maths written on paper. You need an interpreter,
  which is often your head, that transforms a term into another term by applying a set of
  rules. In lambda calculus, there are two main rules to transform between different
  terms: **alpha-conversion** (renaming of variables inside an abstraction, e.g.,
  `(λy.y+1)` can be alpha-converted into `(λm.m+1)` or `(λz.z+1)`, ...), and
  **beta-reduction** (takes the right side of an application and replaces all appeareances
  of the variable on the abstraction on the left side of the application, e.g., `(λx.x+1)
  2` gets beta-reduced into `2+1`[^further])
[^betareduction]: Using beta-reduction.
[^further]: `2+1` can be further reduced to `3` by using the intuitive rule of adding, or
  if you want to be less pragmatic write `2`, `1`, `+`, and `2+1` as pure lambda calculus
  terms. Some guidence on that can be found in the wikipedia
  [here](https://en.wikipedia.org/wiki/Lambda_calculus). You nerds.
[^haskelllambda]: Wait! That looks just like Haskell code! Well, it shouldn't surprise us
  much, after all we can do this `sum list` (with `list = [1..10]`, for example), this
  `(\x->x+1) 2`, and this `y (\x->x**2)` (with `y f = f 3` or `y = ($3)`, for example) in
  Haskell.

With Lambda Calculus we can do many interesting things, but it's a little cumbersome and
verbose. For example, to calculate the factorial using only Lambda Calculus, we must
defined all the following terms:

``` plain
true = \x y . x
false = \x y . y
0 = \f x . x
1 = \f x . f x
succ = \n f x . f(n f x)
pred = \n f x . n(\g h . h (g f)) (\u . x) (\u .u)
mul = \m n f . m(n f)
is0 = \n . n (\x . false) true
Y = \f . (\x . x x)(\x . f(x x))
fact = Y(\f n . (is0 n) 1 (mul n (f (pred n))))
4 = (succ (succ (succ 1)))
```

With these definitions in place, we can compute the factorial of 4 by reducing the
expression `fact 4`.

I've taken the code above from [Ben Lynn's notes on Lambda Calculus][blynn]. You can even
try to run the same example right on Lynn's page (click on the button that says
_Factorial_).

[blynn]: https://crypto.stanford.edu/~blynn/lambda/

That's a pain on the guts to read and understand (unless you're into that kind of stuff
;)). That's why I'm taking some liberties here forward to extend this Lambda Calculus with
numbers, strings and booleans and their respective operations. Plus recursion and
`if-else` statements. With these extensions, it's easy to write factorial:

``` plain
fact = \x. if (x=0) 1 (x * fact (x-1))
```

To continue with the factorial example, let's reduce the application `fact 4`:

``` plain
fact 4
// replacing fact for definition
       = (λx.if (x=0) 1 (x*fact (x-1))) 4
// β-reduction
       = if (4=0) 1 (4*fact (4-1))
// if rule applied, 4 != 0
       = 4 * fact (4-1)
// replacing fact for definition
       = 4 * (λx.if (x=0) 1 (x*fact (x-1))) (4-1)
// β-reduction
       = 4 * if (4-1=0) 1 ((4-1)*fact (4-1-1))
// if rule applied, 4-1 != 0
       = 4 * (4-1) * fact (4-1-1)
// ...
       = 4 * (4-1) * (λx.if (x=0) 1 (x*fact (x-1))) (4-1-1)
       = 4 * (4-1) * if (4-1-1=0) 1 ((4-1-1)*fact (4-1-1-1))
       = 4 * (4-1) * (4-1-1) * fact (4-1-1-1)
       = 4 * (4-1) * (4-1-1) * (λx.if (x=0) 1 (x*fact (x-1))) (4-1-1-1)
       = 4 * (4-1) * (4-1-1) * if (4-1-1-1=0) 1 ((4-1-1-1)*fact (4-1-1-1-1))
       = 4 * (4-1) * (4-1-1) * (4-1-1-1) * fact (4-1-1-1-1)
       = 4 * (4-1) * (4-1-1) * (4-1-1-1) * (λx.if (x=0) 1 (x*fact (x-1))) (4-1-1-1-1)
       = 4 * (4-1) * (4-1-1) * (4-1-1-1) * if (4-1-1-1-1=0) 1 ((4-1-1-1-1)*fact (4-1-1-1-1-1))
       = 4 * (4-1) * (4-1-1) * (4-1-1-1) * 1
       = 4 * (4-1) * (4-1-1) * 1 * 1
       = 4 * (4-1) * 2 * 1 * 1
       = 4 * 3 * 2 * 1 * 1
       = 24
```

Well, that's nice, and "simple" too. Because that is a bit annoying to do by hand, I wrote
a Python script reduce the expression for me. You can find the code in
[here](https://github.com/helq/ILLA)[^sorry].

[^sorry]: Sorry if you see too many spelling mistakes on the Python script.  I wrote the
  code some years ago for a class on "compilers"[^shameless]. My English sucked at the
  time. Not that it doesn't now, but it was way worse back then.
[^shameless]: ikr, shameless self-promotion.


## Typed Lambda Calculus ##

Lambda Calculus is nice but it lacks types, and as we know from Haskell, types are
awesome! When we have types, we can ask the compiler/interpreter to dectect if what we're
saying is coherent or not. Fortunately adding types to lambda calculus is quite simple and
intuitive. As any good professor I'll give it to you as an exercise for home, or better
it's trivial and left to the reader to finish (take that calculus[^calc] books :P).

[^calc]: or should it be _calculi_? _calculuses_? _calculus's_? _calculises'_???

Do you remember that we use `λ` to create an abstraction using a variable and a term? Well,
in Typed Lambda Calculus[^systemf] we use the character `Λ` to create an "abstraction"
where the left side holds not a variable but a **type** variable. For example:

[^systemf]: In [System F](https://en.wikipedia.org/wiki/System_F) to be more precise

```
ΛT.λx:T.x
```

it's the equivalent lambda expression to `λx.x` in untyped lambda calculus.

Applications are now of two kinds: applications for terms and applications for types.
These two types of applications look the same and have the same semantic rules from
before. For example, the application `(ΛT.λx:T.x) Int 5`[^abusing] reduces to:

[^abusing]: Note that I'm abusing ("extending") again the notation of Lambda Calculus to
  add some simple and intuitive types like `String`, `Int` and `Bool`. Also, I need to
  aknowledge [this awesome post][elmanantial] which got me thinking on type Lambda
  Calculus and Higher Order Polymorphism.

[elmanantial]: https://elmanantialdebits.blogspot.com.co/2010/04/polimorfismo-de-rango-superior.html

```
(ΛT.λx:T.x) Int 5
= (λx:Int.x) 5 // beta-reduction
= 5:Int // beta-reduction
```

Note that the type of the whole expression `ΛT.λx:T.x` is `∀X.(X->X)`. This means that when
we apply any type `X` to whole the term, we get a new term with type `X->X`. Thus, in
Typed Lambda Calculus we have that any term, with and without type variables, has a type.
Let's look at some other Typed Lambda Calculus terms:

```
λx:Int.x+1            // with type: Int -> Int
λx:String.x<>" text"  // String -> String
λx:String.x+1         // String -> String, this definition is inconsistent with + which is defined for numbers only (at least for this explanation)
ΛT.λx:Int.x           // ∀T.(Int->Int)
ΛX. ΛY. λx:X. λy:Y. x // ∀X.∀Y.X->Y->X
```

Take a close look at that last example and make sure you understand it. _Tip_: I've gain some
insight by working backwards, reading the type definition `∀X.∀Y.X->Y->X` and trying to
create the term definition.

Let's apply some types and terms to the lambda expressions above:

```
(λx:Int.x+1) 5                // Int
(λx:String.x<>" text") "some" // String
(λx:String.x+1) "more text"   // failure!!! type mismatch of x:String and operator (+):Int->Int->Int
(ΛT.λx:Int.x) String 4        // Int

(ΛX. ΛY. λx:X. λy:Y. x) Int          // ∀Y.Int->Y->Int
(ΛX. ΛY. λx:X. λy:Y. x) Int String   // Int->String->Int
(ΛX. ΛY. λx:X. λy:Y. x) Int String 5 // Int
```

## Higher Rank Polymorphism ##

Before we explore Higher Rank Polymorphism, I would like to ask you to give me the type
definition of some haskell functions in Typed Lambda Calculus. For that, we will need to
translate Haskell code into Typed Lambda Calculus, and get the type definition from
there. For example, the process to get the type of `map` on Typed Lambda Calculus would
be:

### Translate `map` into Typed Lambda Calculus ###

Given the definition of `map`:

``` haskell
map _ []     = []
map f (x:xs) = f x : map f xs
```

we can rewrite it as the Untyped Lambda expression[^cons]:

```
map = λf.λxs.if (xs=nil) nil (cons ((f (car xs)) (map f (cdr xs))))
```

[^cons]: `cons`, `car` and `cdr` are simple functions to operate with tuples in
  languages like lisp. `cons` creates a new tuple from two values, `car` and `cdr` take a
  tuple and return its first element and second element, respectively[^haskconst]. Lisp
  was designed directly from Untyped Lambda Calculus, thus it's easier to write an
  expression first in Lisp and then translate it into a Lambda expresion of Untyped Lambda
  Calculus.
[^haskconst]: We may think that the "equivalents" of `cons`, `car` and `cdr` in haskell
  would be `(,)`, `fst` and `snd`, but they aren't! They behave different to the original
  Lisp definitions. It is not possible to create a list in Haskell using only `(,)`'s
  (unless you wrapped `(,)` in a newtype definition and did some trickery), i.e.,
  this fails in Haskell: `range n m = if n>m then () else (n, range (n+1) m)`, but this
  works just fine in lisp: `(defun range (n m) (cons n (range (+ n 1) m)))`.

Notice, how the lack of pattern matching on lambda expressions forces us to check if the
list is empty. In case the list is empty, we return an empty list, otherwise we return a
new list with the application of the function to the first element and a recursive call to
`map` for the rest of the list. If we were to write the expression back into Haskell, we'd
get:

``` haskell
map f xs = if null xs
            then []
            else f (head xs) : map f (last xs)
```

Anyway, if we add the necessary types we would get[^drill]:

```
map = ΛX.ΛY.λf:X->Y.λxs:[X].if (xs=nil) nil (cons ((f (car xs)) (map f (cdr xs))))
```

[^drill]: You know the drill already. I'm extending the typed lambda calculus with lists.
  Their type is represented by the type `[] a` or `[a]` (which has kind: unary type
  constructor[^kind]).
[^kind]: Kinds are another extension to Lambda Calculus which give us the power to
  parametrize types. It's another whole topic (and to be honest, I don't get it
  completely), you can find more info in the [wikipedia](https://en.wikipedia.org/wiki/Kind_(type_theory)).

with type:

```
∀X.∀Y.(X->Y)->[X]->[Y]
```

Here is where I want you to notice how this type looks very similar to the haskell type
for `map`:

``` haskell
Prelude> :t map
map :: (a -> b) -> [a] -> [b]
```

but there is no `∀X.∀Y.` in that haskell type, or is there? Yeah, it is there, but it is
implicit. You can define you're own `map` function and specify the type you want for it
using `forall` in the type definition (available in the extension `RankNTypes`):

```
$ ghci -XRankNTypes
Prelude> let rmap f xs = if null xs then [] else f (head xs) : rmap f (tail xs); rmap :: forall a. forall b. (a->b) -> [a] -> [b]
```

Notice the type definition `rmap :: forall a. forall b. (a->b) -> [a] -> [b]`, it's very
similar to the type of our Typed Lambda expression. Unfortunatelly, Haskell ignores all
`forall`'s (when they're rank 1), so we get in console the type:

```
Prelude> :t rmap
rmap :: (a -> b) -> [a] -> [b]
```

By the way, functions with `forall` in their type definition are called **polymorphic**.

### More Typed Lambda expressions ###

Now, a little exercise for you. Find the type definitions for the following Haskell
functions. Don't forget to use `forall` in the definitions.

```haskell
foldl _ z []     = z
foldl f z (x:xs) = foldl f (f z x) xs

const a _ = a

length []     = 0
length (_:xs) = 1 + length xs

fst (a, b) = a
```

The answers are:

```haskell
foldl :: forall a b. (a -> b -> a) -> a -> [b] -> a
const :: forall a b. a -> b -> a
length :: forall a. [a] -> Int
fst :: forall a b. (a, b) -> a
```

Well, it wasn't that hard, was it?

### Higher Rank Polymorphism (finally) ###

What should be the type of `weird` (defined below) if we want to call it with parameters
`id 5 "ho"`?

```haskell
weird g a s = (g a, g s)
```

Our first guess could be:

```haskell
weird :: forall x y. (x->x) -> y -> String -> (y, String)
```

but Haskell objects:

```plain
<interactive>:18:27: error:
    • Couldn't match expected type ‘x’ with actual type ‘String’
      ‘x’ is a rigid type variable bound by
        the type signature for:
          weird :: forall x y. (x -> x) -> y -> String -> (y, String)
        at <interactive>:18:46
    • In the first argument of ‘g’, namely ‘s’
      In the expression: g s
      In the expression: (g a, g s)
    • Relevant bindings include
        g :: x -> x (bound at <interactive>:18:11)
        weird :: (x -> x) -> y -> String -> (y, String)
          (bound at <interactive>:18:5)
```

What does that mean? Basically, that `x` was expected to be of the type `String`. But the
whole deal with `forall`s was to tell the type inference that `x` could be anything, not
just `String`.  `weird` should receive a polymorphic function `x->x`.

What the heck is happening?!

Well, to understand why that type doesn't really work, we will rewrite our function as a
Typed Lambda expression:

```
weird = ΛY. ΛX. λg:(X->X). λa:Y.  λs:String. (g a, g s)
```

with type (we hope):

```
∀Y.∀X.(X->X)->Y->String->(Y, String)
```

and try to reduce the application `weird Int String (λb.b) 5 "ho"`:

``` plain
weird Int String (λb.b) 5 "ho"
  = (ΛY. ΛX. λg:(X->X). λa:Y. λs:String. (g a, g s)) Int String (λb.b) 5 "ho"
  = (ΛX. λg:(X->X). λa:Int. λs:String. (g a, g s)) String (λb.b) 5 "ho"
  = (λg:(String->String). λa:Int. λs:String. (g a, g s)) (λb.b) 5 "ho"        // g:(λX.X) stops being polymorphic!!!
  = (λa:Int. λs:String. ((λb:String.b) a, (λb:String.b) s)) 5 "ho"
  = (λs:String. ((λb:String.b) (5:Int), (λb:String.b) s)) "ho"
  = ((λb:String.b) (5:Int), (λb:String.b) ("ho":String))
  FAIL!! 5 has type `Int` but (λb:String.b) requires 5 to be `String`
```

Now you know why it fails! Going from line 3 to 4 the type of `g` gets converted from what
we expected to be polymorphic `∀X.X->X` to `String->String`. What does this means is that we're
forcing to pick the type of `X->X` when we give the type of the first element `a`. At the
end, the real type of the whole lambda expression is:

```
∀Y.∀X.(String->String)->String->String->(String, String)
```

to prove it, let's reduce the expression `weird String String (λb.b) "hi" "ho"`:

``` plain
weird String String (λb.b) "hi" "ho"
  == (ΛY. ΛX. λg:(X->X). λa:Y. λs:String. (g a, g s)) String String (λb.b) "hi" "ho"
  == (ΛX. λg:(X->X). λa:String. λs:String. (g a, g s)) String (λb.b) "hi" "ho"
  == (λg:(String->String). λa:String. λs:String. (g a, g s)) (λb.b) "hi" "ho"
  == (λa:String. λs:String. ((λb:String.b) a, (λb:String.b) s)) "hi" "ho"
  == (λs:String. ((λb:String.b) "Hi":String, (λb:String.b) s:String)) "ho"
  == ((λb:String.b) ("Hi":String), (λb:String.b) ("ho":String))
  == (("Hi":String), (λb:String.b) ("ho":String))
  == ("Hi":String, "ho":String)
```

You may think, there is no way to make our function behave like we wanted to, but there
is something we haven't explored yet. We can define the type of `g` using `∀`!  Mmmm...,
let's see what happens if we rewrite our typed lambda expression to make `g`'s definition
polymorphic:

```
weird = ΛY. λg:(∀X.(X->X)). λa:Y. λs:String. (g Y a, g String s)
```

and now, the type of `weird` would be:

```
∀Y.(∀X.X->X)->Y->String->(Y, String)
```

Notice how `g` receives two parameters now! The first is the type and the second is a term.
Reducing the application `weird Int (ΛX.λb:X.b) 5 "hi"` we get:


``` plain
weird Int (ΛX.λb:X.b) 5 "hi"
  == (ΛY. λg:(∀X.(X->X)). λa:Y. λs:String. (g Y a, g String s)) Int (ΛX.λb:X.b) 5 "hi"
  == (λg:(∀X.(X->X)). λa:Int. λs:String. (g Int a, g String s)) (ΛX.λb:X.b) 5 "hi"
  == (λa:Int. λs:String. ((ΛX.λb:X.b) Int a, (ΛX.λb:X.b) String s)) 5 "hi"
  == (λs:String. ((ΛX.λb:X.b) Int 5, (ΛX.λb:X.b) String s)) "hi"
  == ((ΛX.λb:X.b) Int 5, (ΛX.λb:X.b) String "hi")
  == ((λb:Int.b) 5, (ΛX.λb:X.b) String "hi")
  == (5:Int, (ΛX.λb:X.b) String "hi")
  == (5:Int, (λb:String.b) "hi")
  == (5:Int, "hi":String)
```

Awesome. It worked! If we translate it back to Haskell, we get:

```
Prelude> let weird g a s = (g a, g s); weird :: forall y. (forall x. x->x) -> y -> String -> (y, String)
Prelude>
```

and

```
Prelude> weird id 5 "ho"
(5,"ho")
Prelude> :t weird id (5::Int) "ho"
weird id (5::Int) "ho" :: (Int, String)
Prelude>
```

`weird` is what is called a **rank-2 polymorphic function** ;). It's rank-2 because
it has a `forall` nested inside. By default Haskell doesn't understand rank-2 functions,
so to define them we need to use the GHC extension `RankNTypes` which we were using in the
examples above.

Further readings:

- [Polymorphism (Haskell Wikibook)](https://en.wikibooks.org/wiki/Haskell/Polymorphism)
- [24 Days of GHC Extensions: Rank N Types](https://ocharles.org.uk/blog/guest-posts/2014-12-18-rank-n-types.html)
- [Higher-Rank Polymorphism in Scala](https://apocalisp.wordpress.com/2010/07/02/higher-rank-polymorphism-in-scala/)
- [Polimorfismo de Rango Superior (spanish for Higher Rank Polymorphism)][elmanantial]
- [Lambda Calculus by Ben Lynn][blynn]
