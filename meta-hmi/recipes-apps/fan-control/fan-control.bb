SUMMARY = "Fan Control Daemon for RPi using libgpiod"
DESCRIPTION = "A background daemon that controls a fan via GPIO based on temperature and GUI state."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835c8d1236dd3327762e34f91c03b53"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI = "file://fan-daemon.c \
           file://fancontrol.c \
           file://fancontrol.h \
           file://fancontrol.service"

DEPENDS += "libgpiod"
RDEPENDS:${PN} = "libgpiod"
S = "${WORKDIR}/sources-unpack"
TARGET_CC_ARCH += "${LDFLAGS}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} fan-daemon.c fancontrol.c -o fan-daemon -lgpiod
}

do_install() {
    # Install binary
    install -d ${D}${bindir}
    install -m 0755 fan-daemon ${D}${bindir}

# Install systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${S}/fancontrol.service ${D}${systemd_unitdir}/system/
}

FILES:${PN} += "${systemd_unitdir}/system"


# Package files
inherit systemd

SYSTEMD_SERVICE:${PN} = "fancontrol.service"
SYSTEMD_AUTO_ENABLE = "enable"

