---
title: 'Chinese Log - Step 2: Learning Pronunciation'
date: 2016-01-18 19:45 (COT)
tags: languages, Chinese, learning, Chinese Log, Mandarin
---

_Updated: 2019.05.29_

_This article was supposed to be one in a series of posts documenting my Mandarin learning
journey. I've stopped to learn the language but I still think that the Anki deck
presented in this post is valuable for anyone who whishes to trully learn the phonetics of
the language. You can find the deck in [ankiweb][decklink] and the source code in
[github][githublink]._

_The previous post can be found [in here][originalpost]._

[decklink]: https://ankiweb.net/shared/info/854183352
[originalpost]: https://github.com/helq/blag/blob/0188da8b861a0a8d3d8b4895181ef0f4d5485bd2/src/blog/posts/2016-01-18-chinese-log-step-2.md
[githublink]: https://github.com/helq/pinyin-beginners-anki-deck

---

The goal of this post is to explain the stuff I considered into the creation of an Anki
deck to learn Chinese phonetics.

First, some terminology. Mandarin syllables can be divided into two parts: an (optional)
initial part and a final part.

Mandarin initials and finals are quite different to many sounds (phonemes) found in
English (or Spanish, in my case). So, learning initials and finals in isolation will be
our first task.

Notice that even though we can study initials and finals in isolation, not all
combinations of initials and finals are valid sounds in Mandarin, similar to how not all
combinations of consonants and vowels in English make sense or are easy to pronunce (try with
`Szczęście`, happiness in Polish).

Once we master the individual sounds, we need to be able to recognise (and pronunce) the
sounds together, which means: we need to learn the syllables. And as if that wasn't
enough, Mandarin has this little thing that no other European Language has: Tones.

Tones are hard, unless you are familiar with them or have a trained ear. I think musicians
may have some advantage here, as they are trained to understand, tell apart, and detect
changes in pitch. I, a humble programmer, am not, and pitch presents for me the hardest of
challenges.

Anyway, in the rest of this post I want to give an overview of what you should know before
you go deep into your ear (and pronunciation) training.

I hope that by breaking the problem into little steps, I will be able to learn a new
characteristic of the language at the time and not be overwelmed by the immense difference
between the phonetic systems of my mother language and Mandarin.  This is of course an
oversimplification, but it is an useful simplification.

So, let's start. First, you need to know IPA!

## IPA and Pinyin ##

I use IPA as a guide to tell apart different sounds in a language that otherwise would
look like the same in paper from how they are written. What I mean is that if you are
learning to pronunce Mandarin using only Pinyin as your guide, you may be misguided into
thinking that, for example, `-ei` sounds like `-e` with some other sound added at the end,
but that is completely wrong. In fact, `-ei` is usually pronunced as `[eɪ̯]` while `-e` is
pronunced as `[ɯ̯ʌ]`.

An in depth introduction of IPA can be found at [IPA explanation | Pronunciation/Ear training](https://fluent-forever.com/chapter3/)
by Fluent Forever. The people behind [Fluent Forever](https://fluent-forever.com) have
been putting quality resources on Language Learning for years, be sure to check them out.

Also, the wikipedia is a great resource: [IPA for Mandarin](https://en.wikipedia.org/wiki/Help:IPA_for_Mandarin).
Don't forget to read the [Pinyin Article in the Wikipedia](https://en.wikipedia.org/wiki/Pinyin).

## The deck ##

Now, [the deck][decklink] and the [source code][githublink].

The deck is composed of four different decks. Each card in the deck has its own audio,
pinyin and IPA. The subdecks are:

- Initials,
- Finals,
- (some) Minimal Pairs (tailored to the sounds _I_ find the hardest),
- and, Tones.

_Beware:_ there are two kinds of 3rd tones in the recordings. The first kind is the
"traditional 3rd tone", i.e. the 3rd tone that is taught everywhere. The second kind is
the "Spoken/Real 4th Tone", which is is the tone spoken by people in real conversations.
For a detailed explanation on what I mean by traditional vs spoken see
[Toward Better Tones in Natural Speech](http://www.sinosplice.com/life/archives/2008/12/10/toward-better-tones-in-natural-speech).

I made the deck so that every time you check a card, the card picks a random audio from a
set of audios. For this to work properly in Anki Desktop, you need to install the
[Replay Button Addon](https://ankiweb.net/shared/info/498789867). No addon is needed for
AnkiDroid. I've only checked the deck in Anki Desktop and AnkiDroid.

## Sources and Acknoledgements ##

Special thanks to [anki-persistence][] which allows me to easily retrieve information
shown at the front of the card.

[anki-persistence]: https://github.com/SimonLammer/anki-persistence

I don't own any of the recordings. All credit for the recordings goes to:

1. <http://resources.allsetlearning.com/chinese/pronunciation/Pinyin_chart>
2. <https://chinese.yabla.com/chinese-pinyin-chart.php>
3. <http://www.yoyochinese.com/chinese-learning-tools/Mandarin-Chinese-pronunciation-lesson/pinyin-chart-table>
4. <http://www.archchinese.com/chinese_pinyin.html>
5. <http://pinpinchinese.com/pinyin-chart/>
6. <http://public.gettysburg.edu/~jli/PinYinChart/ChinesePinYinChartM.html>
7. <http://lost-theory.org/chinese/phonetics/>
8. <http://www.china-on-site.com/language/phonetic/phonetic.htm>

[//]: # ( vim:set ts=2 sw=2 tw=90 et : cc=92: )
