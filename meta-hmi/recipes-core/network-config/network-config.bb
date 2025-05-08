SUMMARY = "Root filesystem overlay with network config files"
DESCRIPTION = "Adds static IP and Wi-Fi configuration files to the root filesystem"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
S = "${WORKDIR}/sources-unpack"
SRC_URI = "file://wpa_supplicant.conf \
           file://wpa_supplicant-init"
           
inherit update-rc.d

INITSCRIPT_NAME = "wpa_supplicant-init"
INITSCRIPT_PARAMS = "start 99 S ."

do_install() {
    # Install wpa_supplicant.conf
    install -d ${D}${sysconfdir}/wpa_supplicant
    install -m 0644 ${S}/wpa_supplicant.conf ${D}${sysconfdir}/wpa_supplicant/


    # Create init.d directory first 👈
    install -d ${D}${sysconfdir}/init.d

    # Install init script for wpa_supplicant
    install -m 0755 ${S}/wpa_supplicant-init ${D}${sysconfdir}/init.d/wpa_supplicant-init
}


do_install:append() {
    # Link dropbear to rcS.d if not already handled by dropbear recipe
    if [ -f ${D}${sysconfdir}/init.d/dropbear ]; then
        install -d ${D}${sysconfdir}/rcS.d
        ln -sf ../init.d/dropbear ${D}${sysconfdir}/rcS.d/S50dropbear
    fi
}

FILES_${PN} += "${sysconfdir}/wpa_supplicant \
                ${sysconfdir}/init.d/wpa_supplicant"
