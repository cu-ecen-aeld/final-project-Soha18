SUMMARY = "Fan Control Daemon for RPi using libgpiod"
DESCRIPTION = "A background daemon that controls a fan via GPIO based on temperature and GUI state."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835c8d1236dd3327762e34f91c03b53"

SRC_URI = "file://fan-daemon.c \
           file://fancontrol.c \
           file://fancontrol.h \
           file://fan-init"

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

    # Install init script for sysvinit 
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${S}/fan-init ${D}${sysconfdir}/init.d/fan-daemon
    
    # Create symlink for service management (optional but recommended)
    install -d ${D}${sysconfdir}/rc5.d
    ln -sf ../init.d/fan-daemon ${D}${sysconfdir}/rc5.d/S99fan-daemon
}

# Package files
FILES:${PN} = "${bindir}/fan-daemon \
               ${sysconfdir}/init.d/fan-daemon \
               ${sysconfdir}/rc5.d/S99fan-daemon"

# Inherit update-rc.d to properly handle sysvinit integration
inherit update-rc.d

# Configure the init script
INITSCRIPT_NAME = "fan-daemon"
INITSCRIPT_PARAMS = "defaults 99"
