# Code of my personal blog #

Welcome everyone!. This is the source code to my personal site/blog, it uses
[Metalsmith][].

[Metalsmith]: http://www.metalsmith.io/ (Metalsmith's official site)

## Requirements ##
To compile the site/blog you will require [npm]() and [nodejs]().

[npm]: https://www.npmjs.com/ (npm's official site)
[nodejs]: https://nodejs.org/ (nodejs's official site)

## How to compile ##
In a shell run:

``` .sh
git clone https://github.com/helq/blag
cd blag
npm install
node build
```

You will see after a folder called `_site`, that folder contains the site/blog.

## Directory structure ##

```
/blag
  /_site
  /assets
  /layouts
  /src
    /posts
      /hello-world.md
```

## License ##

The `layouts` and `assets` folders are based on the [hexo][] theme:
[simplest][] by Jason Tung, which is licensed under MIT, but sublicensed here
under the BSD-3.

[hexo]: https://hexo.io/ (Hexo's official website)
[simplest]: https://github.com/dnxbf321/hexo-theme-simplest (github link to hexo theme)
