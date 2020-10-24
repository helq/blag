/**
 * Dependencies
 */
let debug = require('debug')('licensing');
 
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
    debug('adding licenses to files');
    
    Object.keys(files).forEach(function(file){
      var data = files[file];

      if (data['license']) {
        let filelic = data['license'];
        debug('file:', file, 'is licensed under', filelic);
        data['license'] = {};
        data['license'][filelic] = true;
      }

      if (data['license-code']) {
        let filelic = data['license-code'];
        debug('file:', file, 'has code licensed under', filelic);
        data['license'] = data['license'] || {};
        data['license']['code'] = {};
        data['license']['code'][filelic] = true;
        delete data['license-code'];
      }   
    });
    
    done();
  };
};
