DESCRIPTION = "Minimal image with bme280 sensor application and WiFi support"
LICENSE = "MIT"

inherit core-image
#inherit linux-raspberrypi-base

# Install core apps and services
IMAGE_INSTALL:append= " \
    bme280 \
    linux-firmware-bcm43430 \
    linux-firmware-rpidistro-bcm43455 \
    bluez5 \
    i2c-tools \
    bridge-utils \
    hostapd \
    iptables \
    systemd-networkd \
    wpa-supplicant \
    iw \
    openssh \
    fan-control \
    qt-gui \
    network-config \
"

DISTRO_FEATURES:append = " wifi"
DISTRO_FEATURES:remove = "connman"

MY_TOOLS = " \
    qtbase \
    qtbase-plugins \
    qtbase-dev \
    qtbase-mkspecs \
    qtbase-tools \
"
MY_PKGS = " \
    qtcharts \
    qtcharts-dev \
    qtconnectivity-dev \
    qtquickcontrols2 \
    qtquickcontrols2-dev \
    qtquickcontrols2-mkspecs \
    qtdeclarative \
    qtdeclarative-dev \
  "
    
MY_FEATURES = " \
    python-smbus \
"
IMAGE_INSTALL:append = " \
    ${MY_TOOLS} \
    ${MY_PKGS} \
    liberation-fonts \
    fontconfig \
    tslib \
    tslib-tests \
    tslib-calibrate \
    evtest \
    libgpiod \
    libgpiod-dev \
    libgpiod-tools \
    mosquitto \
    mosquitto-clients \
    dhcpcd \
"
IMAGE_INSTALL:remove = "initscripts"
#IMAGE_INSTALL:append = " systemd-resolved"
