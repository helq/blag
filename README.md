# Code of my personal blog #

Welcome everyone!. This is the source code to my personal site/blog, it uses
[Metalsmith][].

[Metalsmith]: http://www.metalsmith.io/ (Metalsmith's official site)

## How to compile ##

To compile the site/blog you need npm and nodejs installed:

``` .sh
git clone https://github.com/helq/blag
cd blag
npm install
node build
```

The site will be generated inside the folder `_site`.

## This directory structure ##

```
/blag
|-/_site
|-/assets
|-/layouts
|-/src
  |-/posts
    |-/hello-world.md
```

## License ##

The `layouts` and `assets` folders are based on the [hexo][] theme:
[simplest][] by Jason Tung, which is licensed under MIT, but sublicensed under
BSD-3 for this project.

[hexo]: https://hexo.io/ (Hexo's official website)
[simplest]: https://github.com/dnxbf321/hexo-theme-simplest (github link to hexo theme)
