"use strict";

let Metalsmith   = require('metalsmith'),
    markdown     = require('metalsmith-markdown'),
    layouts      = require('metalsmith-layouts'),
    permalinks   = require('metalsmith-permalinks'),
    branch       = require('metalsmith-branch'),
    collections  = require('metalsmith-collections'),
    serve        = require('metalsmith-serve'),
    i18n         = require('metalsmith-i18n'),
    moment       = require("moment"),
    assets       = require('metalsmith-assets'),
    pagination   = require('metalsmith-pagination'),
    excerptor    = require('metalsmith-excerptor'),
    tags         = require('metalsmith-tags'),
    beautify     = require('metalsmith-beautify'),
    feed         = require('metalsmith-feed'),
    watch        = require('metalsmith-watch'),
    blc          = require('metalsmith-broken-link-checker'),
    compressgzip = require('metalsmith-gzip');

let debug = require('debug')('builder');

/**
 * Helpers
 */
let basename = require('./helpers/basename');
let parse_dates = require('./helpers/parse_dates');
let metadataadder = require('./helpers/add-metadata');
let copying_contents = require('./helpers/copying_contents');
let drafts = require('./helpers/drafts');

/**
 * Global variables
 */
let remove_drafts = true;

if (process.argv.length > 2) {
    process.argv.slice(2).forEach((val) => {
        switch(val) {
            case '-d':
            case '--drafts':
                remove_drafts = false;
                debug("Setting: drafts are now displayed");
                break;

            case '-h':
            case '--help':
            default:
                console.log("mode of use: node build [-h|--help] [-d|--drafts]");
                process.exit(1);
        }
    });
}

/**
 * Simple logging plugin, helpful for debugging ;)
 */
let log = function() {
  return function(files, metalsmith, done) {
    console.log(Object.keys(files));
    //console.log(files);
    //console.log(metalsmith);
    //console.log(metalsmith.metadata());
    done();
  };
};

/**
 * blog data
 */
let blog = {
   title: "omnomnomelq",
   subtitle: "i'm a subtitle!",
   subtitle_alt: "helq's blog",
   description: "",
   author: "helq",
   url: 'https://helq.github.io/',
   root: "/",
   date_format: "YYYY-MM-DD",
   excerpt_more: 'read more',
   locale: 'en',
   menu: {
       home: "/blog/",
       about: "/blog/about/",
       archive: "/blog/archive/"
   },
   google_analytics: {
       active: false
   },
   comments: {
       enable: false,
       disqus_shortname: undefined
   },
   rss: {
      destination: "blog/rss.xml"
   }
};



/**
 * Metalsmith core function
 */
Metalsmith(__dirname)
  /**
   * common metadata for all files in this site/blog
   * metadata should be only use by the `layouts' plugin
   */
  .metadata({
      blog: blog,
      layout_name: function(n) { return /^(.*)\.[^.]+$/.exec(n)[1]; }, // 'name.nunjucks' -> 'name'
      date_now: moment(Date.now()).format('YYYY'), //getting the current year
      url_for: function(path) {
          let not_index = /^(.*\/)index\.html?$/.exec(path); // removing index.html from the path
          return blog.root + (not_index ? not_index[1] : path);
      },
      permalink: function(path) { return blog.url + path; },
      tag_path: function(tag) { return blog.root + "blog/tags/" + tag.replace(/ /g, '-') + "/"; },
      moment: moment, // dates formatting accesible to the layouts
      Object: Object,
  })

  /**
   * basic preprocessing
   */
  .source('./src')
  .destination('./_site')
  .clean(false) // TODO: clean all the files except for the .git folder which lies in `./_site'

  /**
   * markdown processing: converting all '.md' files in '.html' files
   */
  .use( markdown({
      smartypants: true
  }))

  //.use( log() )

  /**
   * Removing drafts files (if true)
   */
  .use( drafts(remove_drafts) )

  /**
   * Copying `contents' to the variable `orig_contents'
   * `orig_contents' is used by layouts and feed plugins
   */
  .use( copying_contents() )

  /**
   * Specific '/blog/*.htm?' configuration
   * - adding layout metadata
   * - renaming from '/blog/about.html' to '/blog/about/index.html'
   */
  .use( branch("blog/*.htm?")
          .use( metadataadder({
              layout: "page.nunjucks"
          }))
          .use( permalinks({
              pattern: undefined,
              relative: false
          }))
  )

  /**
   * Specific posts configurations:
   * - adding locale and layout metadata
   * - creating excerpts
   * - creating tag files
   * - and parsing dates (plain text -> Date Object)
   * - creating a posts collection
   * - renaming posts from 'blog/posts/2999-99-99-post-name.html'
   *                 to -> 'blog/posts/2999/99/en/post-name/index.html'
   */
  .use( branch("blog/posts/*")
          .use( metadataadder({
              locale: blog.locale,
              layout: "post.nunjucks"
          }))
          .use( excerptor({
              maxLength: 800,
              ellipsis: '…'
          }))
          .use( tags({
              handle: 'tags',
              path: 'blog/tags/:tag/index.html',
              layout: 'tag.nunjucks',
              sortBy: 'date',
              reverse: false,
              skipMetadata: false
          }))
          .use( parse_dates() )

          /**
           * creating 'posts' collection
           */
          .use( collections({
              posts: {
                  pattern: 'blog/posts/*.html',
                  sortBy: 'date',
                  reverse: true
              }
          }))

          /**
           * extracting the basename from the posts
           * '2999-99-99-post-name.html' -> 'post-name.html'
           */
          .use( basename(11) )

          .use( permalinks({
              pattern: "blog/posts/:date/:locale/:basename",
              date: "YYYY/MM",
              relative: false
          }))
          //.use( log() )
  )

  /**
   * making the archive ('blog/archive/**') using the collection 'posts'
   */
  .use(pagination({
    'posts': {
      perPage: 30,
      layout: 'archive.nunjucks',
      first: 'blog/archive/index.html',
      path: 'blog/archive/page/:num/index.html',
      //filter: function (page) {
      //  return !page.private
      //},
      pageMetadata: {
        title: 'Archive',
        page: {
            archive: true,
            year: undefined,
            month: undefined,
            category: undefined,
            tag: undefined
        }
      }
    }
  }))

  /**
   * making the `blog/index.html' using the collection 'posts'
   */
  .use(pagination({
    'posts': {
      perPage: 6,
      layout: 'index.nunjucks',
      first: 'blog/index.html',
      path: 'blog/page/:num/index.html',
      //filter: function (page) {
      //  return !page.private
      //},
      pageMetadata: {
        title: 'Home',
        page: {
            archive: false
        }
      }
    }
  }))

  /**
   * Multilanguage Support
   * the default `locale' will be set any remaining file which doesn't
   * have `locale' already
   */
  .use( metadataadder({
      locale: blog.locale // default language is blog.locale ('en')
  }))
  .use( i18n({
      default: 'en',
      locales: ['en', 'es'],
      directory: 'layouts/locales',
      updateFiles: false
  }) )
  //.use( log() )

  /**
   * applying layouts
   */
  .use( layouts({
      engine: 'nunjucks',
      directory: './layouts'
      //pattern: 'blog/**'
  }))

  .use( beautify({
      indent_size: 2,
      indent_char: ' '
  }))

  /**
   * copying assets from the './assets' folder
   */
  .use( assets({
      source: "./assets",
      destination: "blog/assets"
  }))

  /**
   * creating feed
   */
  .use( feed({
      title: blog.title + ' - ' + blog.subtitle_alt,
      description: blog.subtitle,
      collection: "posts",
      limit: 20,
      destination: blog.rss.destination,
      postDescription: function(file) { return file.orig_contents; },
      site_url: blog.url
  }))

  .use( blc({
      //allowRegex: /\/blog\/data\/.*/,
      allowRedirects: true,
      checkImages: true,
      checkLinks: true,
      warn: true
  }))

  // compressing using gzip
  .use( compressgzip() )

  /**
   * serving the site
   */
  //.use(serve({
  //    port: 8080,
  //    verbose: true
  //}))

  // breaks with pagination :/
  //.use(watch({
  //    "**/*": true
  //}))

  /**
   * Executing everything
   */
  .build( function(err) {
    if (err)
      throw err;
    else {
      console.log('Site build complete!');
    }
  });
