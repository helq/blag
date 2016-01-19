/**
 * Expose `plugin`.
 */

module.exports = plugin;

/**
 * Metalsmith plugin to copy contents to a variable called orig_contentss
 *
 * @return {Function}
 */
function plugin() {
  return function(fs,ms,done) {
    Object.keys(fs).forEach(function(file){
        var data = fs[file];
        data["orig_contents"] = data["contents"];
    });

    done();
  }
};
