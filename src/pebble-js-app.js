/* global Pebble */

Pebble.addEventListener('showConfiguration', function () {
  Pebble.openURL('http://konsumer.github.io/obliqe_strategies_pebble')
})

Pebble.addEventListener('webviewclosed', function (e) {
  var config = JSON.parse(decodeURIComponent(e.response))
  console.log(config)
  Pebble.sendAppMessage({
    'color': parseInt(config.color, 16),
    'invert': config.invert
  }, function () {
    // success
  }, function () {
    // fail
  })
})
