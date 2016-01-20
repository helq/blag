Code of my personal blog
========================

Welcome everyone!. This is the source code to my personal site/blog, it uses [Metalsmith](http://www.metalsmith.io/).

How to compile
--------------

To compile the site/blog you need npm and nodejs installed:

``` .sh
git clone https://github.com/helq/blag
cd blag
npm install
node build
```

The site will be generated inside the folder `_site`.

This directory structure
------------------------

```
/blag
|-/_site
|-/assets
|-/layouts
|-/src
  |-/posts
    |-/hello-world.md
```

License
-------

The `layouts` and `assets` folders are based on the [hexo](https://hexo.io/) theme: [sipmlest](https://github.com/dnxbf321/hexo-theme-simplest) by Jason Tung, which is license under MIT, but sublicense for this project under BSD-3
