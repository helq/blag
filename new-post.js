"use strict";

let fs     = require('fs'),
    moment = require("moment");

if (process.argv.length != 3) {
    console.log("mode of use: node new-post 'A title'");
    process.exit(1);
}

function string2urlSafe(value) { // http://stackoverflow.com/a/2497040
    return value === undefined ? '' : value.replace(/[^a-z0-9_]+/gi, '-').replace(/^-|-$/g, '').toLowerCase();
}

let date  = moment( Date.now() );
let title = process.argv[2];

let file_name = "src/blog/posts/"
              + date.format('YYYY-MM-DD-')
              + string2urlSafe(process.argv[2])
              + '.draft'
              + '.md';

let content = 
"---\n\
title: 'TITLE'\n\
date: DATE\n\
tags: \n\
---\n\n".replace('TITLE', title).replace('DATE', date.format('YYYY-MM-DD HH:mm [(COT)]'));

/**
 * Creating new post
 */
fs.writeFile(file_name, content,
    function(err) {
        if(err) {
            return console.log(err);
        }
    
        console.log("New post: '%s' created", title);
    }
); 

