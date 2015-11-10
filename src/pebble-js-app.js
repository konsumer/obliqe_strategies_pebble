/* global Pebble */

Pebble.addEventListener('showConfiguration', function () {
  Pebble.openURL('http://konsumer.github.io/obliqe_strategies_pebble')
})

Pebble.addEventListener('webviewclosed', function (e) {
  var config = JSON.parse(decodeURIComponent(e.response))
  Pebble.sendAppMessage({
    'colorBackground': parseInt(config.colorBackground, 16),
    'colorForeground': parseInt(config.colorForeground, 16)
  }, function () {
    // success
  }, function () {
    // fail
  })
})
