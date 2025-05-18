#!/bin/sh
### BEGIN INIT INFO
# Provides:          guiapp
# Required-Start:    $all
# Required-Stop:
# Default-Start:     5
# Default-Stop:
# Short-Description: Start GUI app at boot
### END INIT INFO

case "$1" in
  start)
    echo "Starting guiapp"
    export QT_QPA_PLATFORM_PLUGIN_PATH=/usr/lib/qt5/plugins
    export QT_QPA_PLATFORM=linuxfb
    export QT_QPA_GENERIC_PLUGINS=tslib
    /usr/bin/guiapp &
    ;;
  stop)
    echo "Stopping guiapp"
    killall guiapp
    ;;
  restart)
    $0 stop
    $0 start
    ;;
  *)
    echo "Usage: $0 {start|stop|restart}"
    exit 1
esac

exit 0

