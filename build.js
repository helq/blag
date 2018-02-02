"use strict";

const Metalsmith   = require('metalsmith'),
      markdown     = require('metalsmith-markdown-remarkable'),
      layouts      = require('metalsmith-layouts'),
      permalinks   = require('metalsmith-permalinks'),
      branch       = require('metalsmith-branch'),
      collections  = require('metalsmith-collections'),
      i18n         = require('metalsmith-i18n'),
      assets       = require('metalsmith-assets'),
      pagination   = require('metalsmith-pagination'),
      excerptor    = require('metalsmith-excerptor'),
      tags         = require('metalsmith-tags'),
      feed         = require('metalsmith-feed'),
      blc          = require('metalsmith-broken-link-checker');
      //highlight    = require('metalsmith-code-highlight'),
      //beautify     = require('metalsmith-beautify'),
      //compressgzip = require('metalsmith-gzip');

const debug  = require('debug')('build'),
      moment = require("moment"),
      dev    = require('metalsmith-dev');

/**
 * Helpers
 */
const basename         = require('./helpers/basename');
const parse_dates      = require('./helpers/parse_dates');
const metadataadder    = require('./helpers/add-metadata');
const copying_contents = require('./helpers/copying_contents');
const drafts           = require('./helpers/drafts');
const remove_match     = require('./helpers/remove_match');

/**
 * Global variables
 */
let remove_drafts = true;
let serve = false;

if (process.argv.length > 2) {
    process.argv.slice(2).forEach((val) => {
        switch(val) {
            case '-d':
            case '--drafts':
                remove_drafts = false;
                debug("Setted: drafts are now being build");
                break;

//            case '-s':
//            case '--serve':
//                serve = true;
//                debug("Setted: serving and watching");
//                break;

            case '-h':
            case '--help':
            default:
                //console.log("mode of use: node build [-h|--help] [-d|--drafts] [-s|--serve]");
                console.log("mode of use: node build [-h|--help] [-d|--drafts]");
                process.exit(1);
        }
    });
}

/**
 * Simple logging plugin, helpful for debugging ;)
 */
const log = function() {
  // TODO: replace `console.log` for `debug`
  return function(files, metalsmith, done) {
    //console.log("hey ;)");
    console.log(Object.keys(files));
    //console.log(files);
    //console.log(metalsmith);
    //console.log(metalsmith.metadata());
    done();
  };
};

// from: https://stackoverflow.com/a/29939805
const name = function(str, sep) {
    return str.substr(str.lastIndexOf(sep) + 1);
}
const strip_extension = function(str) {
    return str.substr(0,str.lastIndexOf('.'));
}

/**
 * blog data
 */
const blog = {
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
     home: "/",
     about: "/blog/about/",
     archive: "/blog/archive/",
     webcomics: "/blog/personal/webcomics"
   },
   sourcecode_url: 'https://github.com/helq/blag/blob/master/src/',
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
let site = Metalsmith(__dirname)
  /**
   * common metadata for all files in this site/blog
   * metadata should be only use by the `layouts' plugin
   */
  .metadata({
      blog: blog,
      layout_name: function(n) { return strip_extension(name(n, '/')); }, // 'name.nunjucks' -> 'name'
      year: moment(Date.now()).format('YYYY'), // getting the current year
      url_for: function(path) {
          let not_index = /^(.*\/)index\.html?$/.exec(path); // removing index.html from the path
          return blog.root + (not_index ? not_index[1] : path);
      },
      permalink: function(path) { return blog.url + path; },
      tag_path: function(tag) { return blog.root + "blog/tags/" + tag.replace(/ /g, '-') + "/"; },
      moment: moment, // dates formatting accesible to the layouts
      Object: Object,
  })
  /*
   * - preserving original file name in `orig_filename`
   */
  .use(
      function(files, metalsmith, done) {
        Object.keys(files).forEach(function(file){
          files[file]['orig_filename'] = file;
        });
        done();
      }
  )


  /**
   * basic preprocessing
   */
  .source('./src')
  .destination('./_site')
  .clean(false) // TODO: clean all the files except for the .git folder which lies in `./_site'

  /**
   * Removing drafts and everything inside blog/notes and blog/.git
   */
  .use( drafts(remove_drafts) )
  //.use( remove_match( RegExp('^blog/\\.git') ) )
  //.use( remove_match( RegExp('^blog/notes/') ) )

  /**
   * markdown processing: converting all '.md' files in '.html' files
   */
  .use( markdown('full', {
      html: true,
      breaks: false,
      typographer: true
  }))

  //.use( log() )

  /**
   * Copying `contents' to the variable `orig_contents'
   * `orig_contents' is used by layouts and feed plugins
   */
  .use( copying_contents() )

  /**
   * Specific configuration for '/blog/*.htm?' and "blog/personal/*.htm?"
   * - adding layout metadata
   * - renaming from '/blog/about.html' to '/blog/about/index.html'
   */
  .use( branch()
          .pattern( ["blog/*.htm?", "blog/personal/*.htm?"] )
          .use( metadataadder({
              layout: "blog/page.nunjucks"
          }))
          .use( permalinks({
              pattern: undefined,
              relative: false
          }))
  )

  /**
   * Specific configuration for '*.htm?' and "teaching/*.htm?"
   * - adding layout metadata
   * - renaming from 'research.html' to 'research/index.html'
   */
  .use( branch()
      .pattern( ["*.htm?", "teaching/*.htm?"] )
          .use( metadataadder({
              layout: "root/walkie.nunjucks"
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
              layout: "blog/post.nunjucks"
          }))
          .use( excerptor({
              maxLength: 800,
              ellipsis: '…'
          }))
          .use( tags({
              handle: 'tags',
              path: 'blog/tags/:tag/index.html',
              layout: 'blog/tag.nunjucks',
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
      layout: 'blog/archive.nunjucks',
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
      layout: 'blog/index.nunjucks',
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
      directory: 'layouts/blog/locales',
      updateFiles: false
  }) )

//  .use( log() )

  /**
   * applying layouts
   */
  .use( layouts({
      engine: 'nunjucks',
      directory: './layouts'
      //pattern: 'blog/**'
  }))

//  .use( log() )

//  .use( highlight() )

//  .use( beautify({
//      indent_size: 2,
//      indent_char: ' ',
//      js: false,
//      preserve_newlines: true
//  }))

  /**
   * copying assets from the './assets' folder
   */
  .use( assets({
      source: "./assets/blog",
      destination: "blog/assets"
  }))
  .use( assets({
      source: "./assets/root",
      destination: "assets"
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
  }));

  // compressing using gzip
  //.use( compressgzip() )

//if (serve) {
//    /** serving site */
//    dev.watch(site, ['./src', './layouts']);
//    dev.serve(site, 8000);
//} else {
    /**
     * building site
     **/
    site.use( blc({
        //allowRegex: /\/blog\/data\/.*/,
        allowRedirects: true,
        checkImages: true,
        checkLinks: true,
        warn: true
    }))
    .build( function(err) {
      if (err)
        throw err;
      else {
        console.log('Site build complete!');
      }
    });
//}

// vim:set tabstop=4 :
