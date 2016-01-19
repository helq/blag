/**
 * Dependencies
 */
//var debug = require('debug')('basename');
 
/**
 * Expose `plugin`.
 */

module.exports = plugin;

/**
 * Metalsmith plugin to parse the date field in each file
 *
 * @return {Function}
 */
function plugin() {
  return function(files, metalsmith, done) {
    Object.keys(files).forEach(function(file){
      var data = files[file];

      if ( typeof(data["date"]) === 'string' ) {
        var date = new Date( data["date"] );
        if (!isNaN(date))
            data["date"] = date;
      }

    });

    done();
  };
};

