FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://interfaces"
S = "${WORKDIR}/sources-unpack"
#inherit update-rc.d
do_install:append() {
    install -m 0644 ${S}/interfaces ${D}${sysconfdir}/network/interfaces
}

