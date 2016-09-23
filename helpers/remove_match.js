/**
 * Dependencies
 */
var debug = require('debug')('remove_match');
 
/**
 * Expose `plugin`.
 */

module.exports = plugin;

/**
 * @param {Regex} match
 * @return {Function}
 */
function plugin(match) {

  return function(files, metalsmith, done) {
    Object.keys(files).forEach(function(file){
      //debug('file %s '+match.test(file), file);
      if( match.test(file) ) {
        debug('deleting file: %s', file);
        delete files[file];
      }
    });

    done();
  };
};

