DESCRIPTION = "Minimal image with bme280 sensor application and WiFi support"
LICENSE = "MIT"

inherit core-image
#inherit linux-raspberrypi-base

# Install core apps and services
IMAGE_INSTALL += " \
    bme280 \
    linux-firmware-bcm43430 \
    bluez5 \
    i2c-tools \
    bridge-utils \
    hostapd \
    iptables \
    wpa-supplicant \
    iw \
    openssh \
    network-config \
    fan-control \
    qt-gui \
"

DISTRO_FEATURES:append = " wifi  "

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
    qtdeclarative-mkspecs \
    qtgraphicaleffects \
    qtgraphicaleffects-dev \
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
"


