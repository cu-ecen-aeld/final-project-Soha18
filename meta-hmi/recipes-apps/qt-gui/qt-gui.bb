SUMMARY = "Simple Qt5 Quick application"
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
# I want to make sure these get installed too.

DEPENDS += "qtbase"

SRC_URI = "file://CMakeLists.txt \
	   file://main.cpp \
           file://mainwindow.h \
           file://mainwindow.cpp\
           file://guiapp.pro \
           file://guiapp.service \
           file://ui_mainwindow.h \
           file://mainwindow.ui \
           file://fancontrol.h \
           "
FILESEXTRAPATHS:prepend := "${THISDIR}/files:${THISDIR}/../fan-control/files:"

S = "${WORKDIR}/sources-unpack"

inherit qmake5 systemd

SYSTEMD_SERVICE:${PN} = "guiapp.service"
SYSTEMD_AUTO_ENABLE = "enable"

do_compile() {
    qmake ${S}/guiapp.pro
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/guiapp ${D}${bindir}/guiapp

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${S}/guiapp.service ${D}${systemd_unitdir}/system/
}


