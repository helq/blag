/**
 * Dependencies
 */
var debug = require('debug')('drafts');
 
/**
 * Expose `plugin`.
 */

module.exports = plugin;

/**
 * Metalsmith plugin to add file basename to its metadata.
 * Optionally slice the basename
 *
 * @param {Boolean} remove
 * @return {Function}
 */
function plugin(remove) {
  remove = remove && true;

  return function(files, metalsmith, done) {
    if (remove) {
      Object.keys(files).forEach(function(file){
        var data = files[file];
        if(data.draft) {
          debug('deleting draft file: %s', file)
          delete files[file];
        }
      });
    }

    done();
  };
};

