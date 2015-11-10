/* global Pebble */

Pebble.addEventListener('showConfiguration', function () {
  Pebble.openURL('http://konsumer.github.io/obliqe_strategies_pebble')
})

Pebble.addEventListener('webviewclosed', function (e) {
  var config = JSON.parse(decodeURIComponent(e.response))
  var msg = {
    'color': parseInt(config.color, 16),
    'invert': config.invert === 'true' ? 1 : 0
  }
  console.log(JSON.stringify(msg))
  Pebble.sendAppMessage(msg, function () {
    // success
  }, function () {
    // fail
  })
})
