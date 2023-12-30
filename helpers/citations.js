"use strict";

/**
 * Simple citations plugin based on citation-js
 */
var debug = require('debug')('citations');
var Cite = require('citation-js');

// Adding PDF links using the publication id as a guide to find the PDF
const create_append = function(files, metadata, docs_dir) {
    return function(entry) {
        // TODO: A more complex check could be done in case that doc_dir has an extra
        // slash (/)
        debugger;
        let filename = `${docs_dir}/${entry.id}.pdf`;
        if (filename in files) {
            let href = `${metadata.blog.root}${filename}`;
            return ` [<a href="${href}"><b>PDF</b></a>]`;
        } else {
            return '';
        }
    }
}
 
// Processing bibliography and creating variables in `metadata` for nunjucks template to
// instert later on
const citations = function(options) {
    var collections = Object.keys(options.collections);

    return function(files, metalsmith, done) {

        var meta = metalsmith.metadata();
        meta.citations = {};

        collections.forEach(function(col) {
            let filename = options.collections[col];
            debug("Found bib file: %s", filename);

            let collection = Cite(files[filename].contents.toString());

            // If I ever want to modify the HTML bibliography output in more detail than what
            // a couple of parameters citation-js allows me to, then I'll check this
            // https://github.com/citation-js/citation-js/blob/main/packages/plugin-csl/src/bibliography.js
            var htmlcite = collection.format('bibliography', {
                format: 'html',
                template: options.format.template,
                lang: options.format.lang,
                nosort: true,
                // prepend (entry) { return `${entry.id}: ` },
                // append: ' [foobar]'
                append: create_append(files, meta, options.docs_dir),
            });

            // Simple postprocessing, bolden some text
            if (options.bolden) {
                htmlcite = htmlcite.replaceAll(options.bolden, "<b>$&</b>")
            }

            meta.citations[col] = htmlcite;
            //delete files[filename];
            //console.log(htmlcite);
        });

        done();
    };
};

/**
 * Expose `plugin`.
 */
module.exports = citations;
