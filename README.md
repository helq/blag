# My blog's source code

Welcome everyone! Here lies the source code for my personal site/blog. It uses
[Metalsmith][].

[Metalsmith]: http://www.metalsmith.io/ (Metalsmith's official site)

## Requirements

To compile the website, you need [npm]() and [nodejs]().

[npm]: https://www.npmjs.com/ (npm's official site)
[nodejs]: https://nodejs.org/ (nodejs's official site)

## How to compile

In a shell run:

```bash
git clone --recursive https://github.com/helq/blag
cd blag
npm install
node build
```

The website is built under `_site/`.

## Directory structure

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

For licensing details please read `LICENSE.md`
