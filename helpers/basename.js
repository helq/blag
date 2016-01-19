/**
 * Dependencies
 */
//var debug = require('debug')('basename');
var path = require('path');
 
/**
 * Expose `plugin`.
 */

module.exports = plugin;

var settings = ["start", "end"]

/**
 * Metalsmith plugin to add file basename to its metadata.
 * Optionally slice the basename
 *
 * @param {Object} opts
 *   @property {Int} start (optional)
 *   @property {Int} end (optional)
 * @return {Function}
 */
function plugin(opts) {
  opts = opts || {};

  // by default if a value is passed, it's the start of the slice
  if (typeof opts === 'number') {
    opts = {start: opts};
  }

  var start = opts.start;
  var end   = opts.end;

  return function(files, metalsmith, done) {
    Object.keys(files).forEach(function(file){
      var data = files[file];
      var ext = path.extname(file);
      var basename = path.basename(file, ext);

      data['basename'] = basename.slice(start, end);
    });

    done();
  };
};

