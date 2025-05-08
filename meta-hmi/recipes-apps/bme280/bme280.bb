# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# Unable to find any files that looked like license statements. Check the accompanying
# documentation and source headers and set LICENSE and LIC_FILES_CHKSUM accordingly.
#
# NOTE: LICENSE is being set to "CLOSED" to allow you to at least start building - if
# this is not accurate with respect to the licensing of the software being built (it
# will not be in most cases) you must specify the correct value before using this
# recipe for anything other than initial testing/development!
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# No information for SRC_URI yet (only an external source tree was specified)
SRC_URI = "file://bme280.c \
           file://bme280.h \
           file://compensation.c \
           file://compensation.h \
           file://Makefile \
           file://pme280"

S = "${WORKDIR}/sources-unpack"
DEPENDS += "i2c-tools"
# NOTE: this is a Makefile-only piece of software, so we cannot generate much of the
# recipe automatically - you will need to examine the Makefile yourself and ensure
# that the appropriate arguments are passed in.

inherit update-rc.d
INITSCRIPT_NAME = "pme280"
INITSCRIPT_PACKAGES = "${PN}"

FILES:${PN} += "${sysconfdir}/*"
EXTRA_OEMAKE = "CFLAGS='${CFLAGS}' LDFLAGS='${LDFLAGS}'"
#TARGET_LDFLAGS += "-Wl, --hash-style=gnu"

do_configure () {
	# Specify any needed configure commands here
	:
}

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/bme280 ${D}${bindir}

    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${S}/pme280 ${D}${sysconfdir}/init.d/
}

