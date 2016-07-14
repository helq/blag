/**
 * Dependencies
 */
let debug = require('debug')('add-metadata');
 
/**
 * Expose `plugin`.
 */

module.exports = plugin;

/**
 * Metalsmith plugin to add metadata to files
 *
 * @param {Object} options
 * @return {Function}
 */
function plugin(metadata) {
  metadata = metadata || {};

  return function(files, metalsmith, done) {
    debug('adding metadata:', metadata);

    Object.keys(files).forEach(function(file){
      var data = files[file];

      for (key in metadata)
        data[key] = data[key] || metadata[key];
    });
    
    done();
  };
};

