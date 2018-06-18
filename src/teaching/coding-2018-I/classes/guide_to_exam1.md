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
     guide_to_exam1.md \
  -o guide_to_exam1.pdf
-->

# "La ciencia de programar" abridged #

1. Una [interpretación](~h) es una asignación de valores de verdad a cada una de las
   letras proposicionales en una fórmula proposicional. Por ejemplo, dada la fórmula
   proposicional $\theta = p \vee q \wedge r \rightarrow r$, una [interpretación](~h) de
   $\theta$ es:

   $$\{\xi(p) = \bot, \xi(q) = \bot, \xi(r) = \top\}$$
   Con los valores de verdad que nos da una [interpretación](~h) podemos hallar el valor
   de verdad de nuestra fórmula proposicional, en nuestro ejemplo:
   $$\bot \vee \bot \wedge \top \rightarrow \top \quad\Rightarrow\quad \bot \wedge \top \rightarrow \top
   \quad\Rightarrow\quad \bot \rightarrow \top \quad\Rightarrow\quad \top$$

   (Nota: recuerda que $\top$ es verdadero y $\bot$ falso)

   ¿Cuál de las siguientes interpretaciones hace falsa a la fórmula proposicional
   $(p \wedge r) \vee q \leftrightarrow p \wedge (r \vee q)$?:

   $$
   \begin{aligned}
     & \{ \xi(p) = \top, \xi(q) = \bot, \xi(r) = \bot \} \\
     & \{ \xi(p) = \bot, \xi(q) = \top, \xi(r) = \top \} \\
     & \{ \xi(p) = \bot, \xi(q) = \bot, \xi(r) = \bot \} \\
     & \{ \xi(p) = \top, \xi(q) = \top, \xi(r) = \bot \}
   \end{aligned}
   $$

2. Una fórmula bien formada (*fbf*) es una formula proposicional que se puede construir a
   partir de las siguientes reglas:

   a. si $p$ es una variable proposicional, entonces $p$ es una fbf
   b. si $\spadesuit$ y $\clubsuit$ son fbf, y $\oslash$ es un [conectivo lógico](~h),
      entonces $(\spadesuit \oslash \clubsuit)$ es un fbf
   c. si $\maltese$ es una fbf, entonces $\neg (\maltese)$ es una fbf

    \inlinetodo{add exercise to form well a non-well formed formula}

3. La [precedencia](~h) de los operadores nos dice en que orden debemos realizar las
   operaciones. A continuación las [precedencias](~h) de algunos de los operadores más
   comunes en C++ (de mayor a menor precedencia):

   1. `(`, `)` (No son en realidad operadores en C++, pero nos indican que sentencia^[no
      pude encontrar una mejor traducción para "sentence" :S] evaluar primero)
   2. `!`, `(int)` (ó `(double)`, ó cualquier otro _casting_)
   3. `*`, `/`, `%`
   4. `+`, `-`
   4. `<`, `>`, `<=`, `>=`
   4. `==`, `!=`
   4. `&&`
   4. `||`

3. La [precedencia](~h) de los conectivos lógicos nos dice en que orden debemos realizar las
   operaciones en una fórmula proposicional para obtener su valor de verdad. La
   [precedencia](~h) de los operadores lógicos es, en orden, de mayor a menor:

   1. $($, $)$ (No realmente un conectivo lógico, pero nos indican la expresión que debe
      ser evaluada antes del resto)
   2. $\neg$
   3. $\wedge$, $\vee$
   4. $\rightarrow$, $\leftrightarrow$

   Fijate en cómo $\wedge$ y $\vee$ tienen la misma precendencia cómo connectivos
   lógicos, pero esto no sucede en C++ dónde `&&` tiene mayor precedencia que `||`

5. ¿Cuál de las siguientes sentencias en C++ es la mejor traducción de la fórmula lógica
   $p \vee q \wedge r \wedge r$ a C++?

   a. `p && q || r || r`{.cpp}
   a. `((p || q) && r) && r`{.cpp}
   a. `p || (q && (r && r))`{.cpp}
   a. `(p || q) && (r && r)`{.cpp}

5. Dos fórmulas proposicionales son equivalentes si tienen las mismas tablas de verdad, es
   decir, si $\theta_1$ y $\theta_2$ son fórmulas proposicionales, ambas son equivalentes
   si y sólo si sus tablas de verdad son las mismas.

   Determine cuál de las siguientes fórmulas proposicionales es equivalente a
   $p \rightarrow q \wedge p$, para esto escriba las tablas de verdad de cada una de las
   proposiciones:

   | $p$ | $q$ | $p \rightarrow q \wedge p$ | $p \leftrightarrow q \wedge p$ | $\neg p \wedge q \vee p$ | $(\neg p \vee q) \wedge p$ | $\neg p \vee (q \wedge p)$ |
   |-----+-----+----+----+----+----+----|
   | $\top$ | $\top$ |  |  |  |  |  |
   | $\top$ | $\bot$ |  |  |  |  |  |
   | $\bot$ | $\top$ |  |  |  |  |  |
   | $\bot$ | $\bot$ |  |  |  |  |  |

   Otra forma de determinar si dos fórmulas lógicas son equivalentes es mostrando una
   serie de equivalencias conocidas entre ellas, por ejemplo, la fórmula lógica
   $p \vee \neg (p \vee r)$ es equivalente a $p \vee \neg r$ porque:
   $$\begin{aligned}
    p \vee \neg (p \vee r) & \equiv p \vee (\neg p \wedge \neg r)  &\text{\quad Por ley de De Morgan } \neg (\bigtriangleup \vee \square) \equiv \neg \bigtriangleup \wedge \: \neg \square \\
                  & \equiv (p \vee \neg p) \wedge (p \vee \neg r)  &\text{\quad Propiedad distributiva de } \vee \text{ en } \wedge \\
                  & \equiv \top \wedge (p \vee \neg r)  &\text{\quad } \bigtriangleup \vee \: \neg \bigtriangleup \equiv \top \\
                  & \equiv p \vee \neg r  &\text{\quad Dominancia en } \wedge \qquad \top \wedge \bigtriangleup \equiv \bigtriangleup
   \end{aligned}$$

   Donde cada una de las equivalencias mencionadas a la izquierda son bien conocidas y
   poseen nombre propio (aunque no es necesario aprenderse el nombre, es siempre buena
   idea saberse algunas equivalencias de memoria).

6. Algunas equivalencias son:

   --------------------------------------------------------------------------------------------------------------------------------------------
                                          **Equivalencia**                                         **Nombre**
   ---------------------------------------------------------------------------------------------- ---------------------------------------------
    $\bigtriangleup \rightarrow \square \equiv \neg \bigtriangleup \vee \: \square$

    $\bigtriangleup \vee \bot \equiv \bigtriangleup \qquad                                         Dominancia
     \bigtriangleup \wedge \: \top \equiv \bigtriangleup$

    $\neg (\bigtriangleup \vee \square) \equiv \neg \bigtriangleup \wedge \: \neg \square \qquad   Leyes de De Morgan
     \neg (\bigtriangleup \wedge \square) \equiv \neg \bigtriangleup \vee \: \neg \square$

    $\bigtriangleup \vee (\square \wedge \Diamond) \equiv                                          Propiedad distributiva de $\vee$ en $\wedge$
     (\bigtriangleup \vee \square) \wedge (\bigtriangleup \vee \Diamond)$

    $\bigtriangleup \wedge (\square \vee \Diamond) \equiv                                          Propiedad distributiva de $\wedge$ en $\vee$
     (\bigtriangleup \wedge \square) \vee (\bigtriangleup \wedge \Diamond)$

    $\bigtriangleup \wedge \: \neg \bigtriangleup \equiv \bot$                                     Contradicción

    $\bigtriangleup \vee \: \neg \bigtriangleup \equiv \top$                                       Tercio excluído

    $\neg \neg \bigtriangleup \equiv \bigtriangleup$                                               Doble negación

    $\bigtriangleup \vee \square \equiv \square \vee \bigtriangleup \qquad                         Conmutatividad(es)
     \bigtriangleup \wedge \: \square \equiv \square \wedge \bigtriangleup \qquad
     \bigtriangleup \leftrightarrow \square \equiv \square \leftrightarrow \bigtriangleup$

    $\square \leftrightarrow \bigtriangleup \equiv                                                 Material
     (\square \rightarrow \bigtriangleup) \wedge (\bigtriangleup \rightarrow \square)$
   --------------------------------------------------------------------------------------------------------------------------------------------

   ¿Qué equivalencia se puede utilizar para transformar la fórmula lógica $p \rightarrow q \wedge p$
   (punto anterior) para hallar otra fórmula lógica equivalente a esta?

6. Los [conjuntos](~h) que uno usualmente usa para modelar un problema son $\mathbb{N}$,
   $\mathbb{R}$ y $\mathbb{B}$. Estos [conjuntos](~h) no se encuentran disponibles en C++,
   pero nos aproximamos a estos con los tipos de datos: `int`, `double` y `bool`,
   respectivamente.

   Podemos definir un conjunto más, el conjunto $\mathbb{ASCII}$, el cual corresponde al
   tipo de datos `char` disponible en C++.

   En la siguiente tabla se encuentran todos los tipos de datos de C++ que nos interesan,
   por el momento, y sus simíles con conjuntos matemáticos:

   |   Conjunto   | Tipo de datos |
   |--------------+---------------|
   | $\mathbb{N} = \{0, 1, 2, 3, 4, ...\}$ | [`int`](~h) |
   | $\mathbb{R}$ | `double` |
   | $\mathbb{B} = \{\top, \bot\}$ | [`bool`](~h) |
   | [$\mathbb{ASCII}$](~h) $= \{$`'A'`$,$`'a'`$,$`'B'`$,$`'b'`$, \dots,$`'!'`$,$`'#'`$,$`'/'`$,$`'\n'`$,\dots\}$ | `char` |

6. Para convertir una función matemática en su equivalente en C++, lo primero que uno
   requiere es saber el tipo del dominio de la función así como también el tipo del rango
   de la función, por ejemplo, dada la función $par : \mathbb{N} \rightarrow \mathbb{B}$,
   uno sabe que su declaración en C++ será: `bool par(int n)`{.cpp}.

   Dada la función $descuento : \mathbb{N} \times \mathbb{B} \times \mathbb{R} \rightarrow \mathbb{B}$,
    escribir su declaración en C++.
    \inlinetodo{extend this section, it's very important and will appear for sure in the
    exam}

7. ¿Qué conectivo lógico es necesario para que la siguiente expresión sea una tautología?:
   $$((p \vee q) \wedge (p \rightarrow r) \wedge (q \rightarrow r)) \:\ \_ \:\ r$$
   <!--respuesta: `then`-->

8. La **traza** de un programa es cómo cada variable cambia a medida que se ejecuta cada
   sentencia de un programa. Por ejemplo, dada la siguiente porción de programa
   (y suponiendo que todas las variables ya están declaradas, con `r = 4`):

    ~~~cpp
    l = r + 3;
    m = 23*r;
    n = m + r;
    o = n*l;
    l = n+o%m;
    ~~~

   La traza de la porción de código será:

   | _t_ | `r` | `l` | `m` | `n` | `o` |
   |-----|-----|-----|-----|-----|-----|
   |  0  |  4  | --- | --- | --- | --- |
   |  1  |  4  |  7  | --- | --- | --- |
   |  2  |  4  |  7  |  92 | --- | --- |
   |  3  |  4  |  7  |  92 | 96 | --- |
   |  4  |  4  |  7  |  92 | 96 | 672 |
   |  5  |  4  | 124 |  92 | 96 | 672 |

   ¿Cuál es la traza del siguiente programa? (suponiendo `mm = -2`):

    ~~~cpp
    rri = 32;
    var = -mm * rri;
    ll = var % 4;
    var = (ll % 3)*11;
    mm = var - ll + rri;
    ~~~

11. Nos piden escribir un programa que sea capaz de llevar la contabilidad de una
    organización, para esto nos dan una lista de requerimientos. Uno de los requerimientos
    es: "El día jueves hay promoción de alimentos lácteos sólo para nuestros clientes
    frecuentes y para aquellos que lleven más de 200.000 pesos en comida".

    En el sistema decidimos declarar una variable que determine el día de la semana
    ($dia$ como un natural, dónde cero es lunes), otra que determine si un cliente es
    frecuente ($frecuente$ como un booleano), y una última que determine el total de lo que
    el cliente a de comprar ($total\_compra$ como un real). Una vez determinados las
    variables, podemos escribir una expresión que determine si se le va a hacer descuento
    por los lácteos o no:

    $día = 3 \wedge (frecuente \vee total\_compra > 200000)$

    Esta expresión la podemos convertir fácilmente a C++, la cual sería:

    [`complete me! ............................................................`](~h)

12. Cuáles de los siguientes son nombres válidos para una variable o función, y cúales no
    (¿por qué?):

    `inta`, \quad
    `variable`, \quad
    `veryfreakinglongnameof0avariable`, \quad
    `double`, \quad
    `3nums`, \quad
    `num__`, \quad
    `num_03`, \quad
    `23_a`, \quad
    `3.4e-2`, \quad
    `aeo.02e`, \quad
    `werid_etr09_2`

<!--
   -7. Las expresiones con "para todo" y "existe" se les llama predicados, y los "para
   -   todo"/"existe" cuantifican una variable, digamos x en "for x: x>0"
   -->

**PD:** Esta guía esta construida para ser un resumen del libro, sin embargo no contiene
todo lo que este mismo dice, un par de temas más que __hay__ que conocer son: Operaciones
entre conjuntos y predicados (una extensión del cálculo proposicional).

<!-- vim:set filetype=markdown.pandoc : -->
