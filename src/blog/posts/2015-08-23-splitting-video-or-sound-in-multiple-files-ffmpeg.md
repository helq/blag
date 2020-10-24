---
title: Splitting video or sound in multiple files - ffmpeg [bash script]
date: 2015-08-23 15:12 (COT)
tags: ffmpeg, bash, programming, scripting
license: "CC BY-SA 4.0"
license-code: CC0
---

## **Edit: 2016-08-02** ##

I found a [simpler, built-in in ffmpeg aproach][stackoverflow] to split a sound/video file
in multiple parts with the same time length.

[stackoverflow]: http://unix.stackexchange.com/a/283547

~~~ bash
ffmpeg -i 'input_file.mp3' \
       -acodec copy -vcodec copy \
       -f segment -segment_time 600 \
       '%03d_out_name.mp3'
~~~

In this example we have an input file called `input_file.mp3` and we break it in multiple
files of 10 minutes each (600 seconds). Each output file has a unique name of the form:
`XXX_out_name.mp3` where `XXX` represents a 3 digit number.

## _As a reference, the old article:_ ##

The present article describes how to split a video/sound into multiple files of same
duration using ffmpeg. [Click to download automated bash script.](/blog/data/splitVideo.sh)

With ffmpeg, to copy just a fraction of a sound (`.mp3`, `.wma`, `.aac`, ...) or video
file (`.mp4`, `.wma`, ...) use:

~~~ bash
ffmpeg -i "$name" -acodec copy -vcodec copy -t $splitLen -ss $start "$new_name"
~~~

where `$name` is the name of the file to split, `$splitLen` is the length in seconds of
the split, `$start` the second in which the splitting start and the `$new_name` for the
file.

The idea is to copy fractions of the song (or video) in pieces of the same size, so that
adding all the pieces we get the original song (video). Here a bash function that does the
job:

~~~ bash
splitVideo() {
    # name file to split
    name="$1"
    # splitting time in seconds
    splitLen=$2

    # total of the song
    totalTime="$(ffprobe -i "$name" -show_format 2> /dev/null | sed -n 's/duration=//p')"
    # number of splits required
    numOfSplits="$(printf '%.0f\n' $[ totalTime / splitLen ])"

    for i in {0..$numOfSplits}; do
        start=$[ splitLen * i ]

        num=$(printf '%02d' $[i+1])
        new_name="${name%.*}_${num}.${name//*.}"

        ffmpeg -i "$name" -acodec copy -vcodec copy \
               -t $splitLen -ss $start \
               -metadata "track=$[i+1]" \
               "$new_name"
    done
}
~~~

Mode of use: `splitVideo "$name_of_the_file" $time_in_seconds`, where `$time_in_seconds`
is the size of the split in seconds, for example, if you put 600 it means 10 minutes.

[Here's the bash script][script]. It is the same code as in the bash function, just in a
bash file ;)

[script]: /blog/data/splitVideo.sh

[//]: # ( vim:set ts=2 sw=2 tw=90 et : cc=92: )
