---
title: Splitting video or sound in multiple files - ffmpeg [bash script]
date: 2015-08-23 15:12 (COT)
tags: ffmpeg, bash, programming, scripting
---

The present article describes how to split a video/sound in multiple files of same duration using ffmpeg. [Click to download automated bash script.](/blog/data/splitVideo.sh)

With ffmpeg, to copy just a fraction of a sound (`.mp3`, `.wma`, `.aac`, ...) or video file (`.mp4`, `.wma`, ...) use:

~~~ bash
ffmpeg -i "$name" -acodec copy -vcodec copy -t $splitLen -ss $start "$new_name"
~~~

where `$name` is the name of the file to split, `$splitLen` is the length in seconds of the split, `$start` the second in which the splitting start and the `$new_name` for the file.

The idea is to copy fractions of the song (or video) in pieces of the same size, so that adding all the pieces we get the original song (video). Here a bash function that does the job:

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

Mode of use: `splitVideo "$name_of_the_file" $time_in_seconds`, where `$time_in_seconds` is the size of the split in seconds, for example, if you put 600 it means 10 minutes.

[Here's the bash script.](/blog/data/splitVideo.sh) It is the same code as in the bash function, just in a bash file ;)
