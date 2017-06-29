---
title: "Higher Rank Polymorphism, a beginners explanation using typed lambda calculus"
started_writing: 2017-06-26 11:41 (COT)
date: 2017-06-28 13:08 (COT)
tags: development, haskell, lambda calculus, learning
---

**Disclaimer:** I'm not an expert on type systems, I was just trying to figure out what
"higher rank polymorphism" was and found useful to use some ad-hoc typed lambda calculus.
For what I've been reading for the last hour, all "code" below is in something close to
"System F" ([wikipedia][wSf], [an in-depth explanation of System F with an interpreter
and actual runnable code][blynnSf]).

[wSf]: https://en.wikipedia.org/wiki/System_F
[blynnSf]: https://crypto.stanford.edu/~blynn/lambda/systemf.html

As I understand, Typed Lambda Calculus is the basis of Haskell, so it makes sense to try
to understand what something means in Haskell by studying it first in Typed Lambda
Calculus. For those of you who doesn't know what lambda calculus is, well, here is a
micro-introduction (if you know what lambda calculus is, jump ahead to the typed lambda
calculus explanation).

## Lambda Calculus ##

In the 20's at the same time Turing was formulating his "Turing Machine", another guy
called [Alonzo Church][church] (a friend of Turing) was working, just like Turing, in the
problem of computability, he then formulated what we know now as lambda calculus. They
(Church and Turing) proved that both formulations were equivalent, meaning that anything
you can do with a Turing Machine can be done with Lambda Calculus. Basically, Haskell and
C have the same power to compute anything.

[church]: https://en.wikipedia.org/wiki/Alonzo_Church

Let's explain how does lambda calculus works. In Lambda Calculus we have terms, and we can
build them using three rules:

- Variables: denoted by single characters, e.g., `x`, `a`, `w`, ...
- Abstraction: with these we can build bigger things out of variables and terms, they're
  like function definitions. Abstractions are denoted by `(λx.M)` (where `x` is a variable
  and `M` a term).
- Application: abstractions let us build bigger terms, applications let us apply terms to
  abstractions (yeah, kinda abstract, let's see an example).  E.g., `(λx.x+1) 2` is an
  application of `(λx.x+1)` with the term `2`, when we [reduce][][^reduce] this
  application we get[^betareduction] the term `2+1`[^further].  Applications are denoted
  by two terms and a space! How weird is that!, I mean, this `E M`, and this `(λx.x+1) 2`,
  and this `y (λx.x**2)` are all valid applications (terms) in lambda
  calculus[^haskelllambda].

[reduce]: https://ro-che.info/ccc/18 "A link to a cartoon explaining the difference between equality and reduction"

[^reduce]: Lambda Calculus is like maths written on paper, you need an interpreter
  (in the case of a piece of paper, the intrepreter will be your head), an iterpreter that
  transforms an term into another term by applying a set of rules. In lambda calculus,
  there are two main rules to transform between different terms: **alpha-conversion**
  (renaming of variables inside an abstraction, e.g., `(λy.y+1)` gets alpha-converted into
  `(λm.m+1)` or `(λz.z+1)`, ...), and **beta-reduction** (gets the right side of an
  application and replaces all appeareances of the variable on the abstraction on the left
  side of the application, e.g., `(λx.x+1) 2` gets beta-reduced into `2+1`[^further])
[^betareduction]: Using beta-reduction.
[^further]: `2+1` can be further reduced to `3` by using the intuitive rule of adding, or
  if you want to be less pragmatic write `2`, `1`, `+`, and `2+1` as pure lambda calculus
  terms. Some guidence on that can be found in the wikipedia
  [here](https://en.wikipedia.org/wiki/Lambda_calculus), you nerds.
[^haskelllambda]: wait, that's looks just like Haskell code!. Well, we can do after all
  this `sum list` (with `list = [1..10]`, for example), this `(\x->x+1) 2`, and this
  `y (\x->x**2)` (with `y f = f 3` or `y = ($3)`, for example) in Haskell.

With lambda calculus we can do many interesting things, but it's a little cumbersome and
verbose, for example, to calculate the factorial we define the following terms:

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

The factorial of 4 can be computed by `fact 4`. I've taken the code above from [Ben
Lynn's notes on Lambda Calculus][blynn], you can even try to run the same example right on
Lynn's page (click on the button that says _Factorial_).

[blynn]: https://crypto.stanford.edu/~blynn/lambda/

But well, that's a pain on the guts to read and understand (unless your into that kind of
stuff ;) ). So, I'm taking some liberties onward to extend this lambda calculus with
numbers, strings and booleans with their respective operations, and allowing recursion.
With this extensions it's easy to write factorial:

``` plain
fact = \x. if (x=0) 1 (x * fact (x-1))
```

Reducing `fact 4` would give us:

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

Well, that's nice, and "simple" too. In fact I didn't write that by hand, I let a python
script reduce the expression for me, you can find the python code
[here](https://github.com/helq/ILLA)[^sorry].

[^sorry]: Sorry if you see too many spelling mistakes on the python script, it's some code
  I wrote some years ago for a class on "compilers"[^shameless], I didn't know any better
  at that time.
[^shameless]: ikr, shameless self-promotion.


## Typed Lambda Calculus ##

Lambda Calculus is nice but it lacks types, and as we know from Haskell, types are
awesome! When we have types, we can ask the compiler/interpreter to dectect if what we're
saying is coherent or not. Fortunately adding types to lambda calculus is quite simple and
intuitive, and as any good professor I'll give it to you as an exercise for home by saying
that it's trivial and left to the reader to finish (take that calculus[^calc] books :P).

[^calc]: or should it be _calculi_? _calculuses_? _calculus's_? _calculises'_???

Do you remember that we use `λ` to create an abstraction using a variable and a term? Well,
in Typed Lambda Calculus[^systemf] we use the character `Λ` to create an "abstraction"
where the left side holds not a variable but a **type** variable. For example:

[^systemf]: In [System F](https://en.wikipedia.org/wiki/System_F) to be more precise

```
ΛT.λx:T.x
```

it's the equivalent lambda expression to `λx.x` in untyped lambda calculus. If we apply to
the term, for example, `Int 5`[^abusing], we'll get:

[^abusing]: Note that I'm abusing ("extending") again the notation of lambda calculus to
  add some simple and intuitive types like `String`, `Int` and `Bool`. Also, I need to
  aknowledge [this awesome post][elmanantial] which got me thinking on type lambda
  calculus and Higher Order Polymorphism.

[elmanantial]: https://elmanantialdebits.blogspot.com.co/2010/04/polimorfismo-de-rango-superior.html

```
(ΛT.λx:T.x) Int 5
= (λx:Int.x) 5 // beta-reduction
= 5:Int // beta-reduction
```

Note that the type of the whole expression `ΛT.λx:T.x` is `∀X.(X->X)`, meaning that when
we apply any type `X` to whole the term we get a new term with type `X->X`, aka. an
abstraction that "returns" a term with of the same type it gets in. Thus, in typed lambda
calculus we have that any term, with and without type variables, has a type. Let's look
at some more typed lambda calculus terms (lambda expressions is shorter ;) ):

```
λx:Int.x+1            // with type: Int -> Int
λx:String.x<>" text"  // String -> String
λx:String.x+1         // String -> String, this definition is inconsistent with + which is defined for numbers only (at least for this explanation)
ΛT.λx:Int.x           // ∀T.(Int->Int)
ΛX. ΛY. λx:X. λy:Y. x // ∀X.∀Y.X->Y->X
```

Take a close look at that last example, and make sure you understand it. I've gain some
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

Before we explore higher rank polymorphism, I would like to ask you to give me the type
definition of some haskell functions in typed lambda calculus. For that we will need to
translate the haskell code into typed lambda calculus, and get the type definition from
there. For example, the process to get the type of `map` on typed lambda calculus would
be:

### `map`'s into typed lambda calculus ###

Given `map`'s definition:

``` haskell
map _ []     = []
map f (x:xs) = f x : map f xs
```

we can rewrite it as the untyped lambda expression[^cons]:

```
map = λf.λxs.if (xs=nil) nil (cons ((f (car xs)) (map f (cdr xs))))
```

[^cons]: `cons`, `car` and `cdr` are some simple functions to operate with tuples in
  languages like lisp (`cons` creates a new tuple from two values, `car` and `cdr` take a
  tuple and return its first element and second element, respectively)[^haskconst]. Lisp
  was designed directly from untyped lambda calculus, thus it's easier to write an
  expression first in lisp and then translate it into a lambda expresion of untyped lambda
  calculus.
[^haskconst]: We may think that the "equivalents" of `cons`, `car` and `cdr` in haskell
  would be `(,)`, `fst` and `snd`, but they aren't! they behave different to the original
  lisp's definitions, it is not possible to create a list using only `(,)`'s (unless you
  wrapped `(,)` in a newtype definition and did some more trickery), i.e., this fails in
  haskell: `range n m = if n>m then () else (n, range (n+1) m)`, but this works just fine
  in lisp: `(defun range (n m) (cons n (range (+ n 1) m)))`[^brackets]
[^brackets]: yeah, those are a lot of brackets! It's after all called LISP (Lots of
  Irritating Superfluous Parentheses)

Notice, how the lack of pattern matching on lambda expressions forces us to check if the
list is empty, in case the list is empty we return an empty list, otherwise we return a
new list applying the function at the first element of the list and applying map
recursively to the rest of the list. Rewritten back into Haskell, we'd get:

``` haskell
map f xs = if null xs
            then []
            else f (head xs) : map f (last xs)
```

Finally writing it into typed lambda calculus, we'd get[^drill]:

```
map = ΛX.ΛY.λf:X->Y.λxs:[X].if (xs=nil) nil (cons ((f (car xs)) (map f (cdr xs))))
```

[^drill]: you know the drill, I'm extending the typed lambda calculus with lists, and
  their type is represented by the type `[] a` or `[a]` (which has kind: unary type constructor[^kind]).
[^kind]: kinds are another extension to Lambda Calculus which give us the power to
  parametrize types, it's another whole topic (and to be honest, I don't get it
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

but there is no `∀X.∀Y.` in that haskell type, or there is? (yeah, it is there, but it is
implicit). You can define you're own `map` function and specify the type you want for it
using `forall` in the type definition (available in the extension `RankNTypes`):

```
$ ghci -XRankNTypes
Prelude> let rmap f xs = if null xs then [] else f (head xs) : rmap f (tail xs); rmap :: forall a. forall b. (a->b) -> [a] -> [b]
```

Notice the type definition `rmap :: forall a. forall b. (a->b) -> [a] -> [b]`, it's very
similar to the type of our typed lambda expression. Unfortunatelly, haskell ignores all
`forall`'s (when they're rank 1), so we get in console the type:

```
Prelude> :t rmap
rmap :: (a -> b) -> [a] -> [b]
```

By the way, functions with `forall` in their type definition are called **polymorphic**.

### More typed lambda expressions ###

Now, a little exercise for you, get the type definitions of the following Haskell
functions using `forall`.

```haskell
foldl _ z []     = z
foldl f z (x:xs) = foldl f (f z x) xs

const a _ = a

length []     = 0
length (_:xs) = 1 + length xs

fst (a, b) = a
```

And the answers are:

```haskell
foldl :: forall a b. (a -> b -> a) -> a -> [b] -> a
const :: forall a b. a -> b -> a
length :: forall a. [a] -> Int
fst :: forall a b. (a, b) -> a
```

Well, it wasn't that hard, was it?

### Higher Rank Polymorphism (finally) ###

What should be the type of `weird` (defined below), if we want to call it with parameters
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

But, what does that mean? Basically, that `x` was expected to be of the type `String`, and
that's weird, because we wrote `forall x` to tell the type inference system that it should
expect to receive a polymorphic function `x->x`.

What the heck is happening?!

Well, to understand why that type doesn't really work, we can rewrite our function as a
typed lambda expression:

```
weird = ΛY. ΛX. λg:(X->X). λa:Y.  λs:String. (g a, g s)
```

with type (we hope):

```
∀Y.∀X.(X->X)->Y->String->(Y, String)
```

and try on our own to reduce the application `weird Int String (λb.b) 5 "ho"`.

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

Now you know why it fails? Yeah, going from line 3 to 4 the type of `g` gets converted from what
we expected to be polymorphic `∀X.X->X` to `String->String`. What does this mean, is that we're
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

You may think, there is no way to do make our function behave like we wanted to, but there
is something we haven't explored (and I haven't tell you on purpose), we can define the
type of `g` using `∀`!  Mmmm..., let's see what happens if we rewrite our typed lambda
expression to make `g`'s definition polymorphic:

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

Awesome, it worked! If we translate it back to Haskell, we get:

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

`weird` is then what is called a **rank-2 polymorphic function** ;), it's rank-2 because
it has a `forall` nested inside. By default Haskell doesn't understand rank-2 functions,
so to define them we need to use the GHC extension `RankNTypes` which we were using in the
examples above.

Further readings:

- [Polymorphism (Haskell Wikibook)](https://en.wikibooks.org/wiki/Haskell/Polymorphism)
- [24 Days of GHC Extensions: Rank N Types](https://ocharles.org.uk/blog/guest-posts/2014-12-18-rank-n-types.html)
- [Higher-Rank Polymorphism in Scala](https://apocalisp.wordpress.com/2010/07/02/higher-rank-polymorphism-in-scala/)
- [Polimorfismo de Rango Superior (spanish for Higher Rank Polymorphism)][elmanantial]
- [Lambda Calculus by Ben Lynn][blynn]
