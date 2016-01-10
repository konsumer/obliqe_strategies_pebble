/* global Pebble */

function getWatchVersion() {
  // 1 = Pebble OG
  // 2 = Pebble Steel
  // 3 = Pebble Time
  // 3 = Pebble Basalt Emulator (currently Pebble Time)
  // 4 = Pebble Time Steel
  var watch_version = 1
  if (Pebble.getActiveWatchInfo) {
    var watch_name = Pebble.getActiveWatchInfo().model;
    if (watch_name.indexOf('pebble_time_steel') >= 0) {
      watch_version = 4
    } else if (watch_name.indexOf('pebble_time') >= 0) {
      watch_version = 3
    } else if (watch_name.indexOf('qemu_platform_basalt') >= 0) {
      watch_version = 3
    } else if (watch_name.indexOf('pebble_steel') >= 0) {
      watch_version = 2
    }
  }
  return watch_version
}

Pebble.addEventListener('showConfiguration', function () {
  var url = 'http://konsumer.github.io/obliqe_strategies_pebble/?version=' + getWatchVersion()
  Pebble.openURL(url)
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
