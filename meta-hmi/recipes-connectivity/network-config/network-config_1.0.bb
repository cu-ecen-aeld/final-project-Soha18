SUMMARY = "Provision systemd-networkd + wpa_supplicant (eth0 static, wlan0 DHCP)"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835e0...<snip>"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += " \
  file://10-eth0-static.network \
  file://20-wlan0.network \
"
#inherit allarch 

S = "${WORKDIR}/sources-unpack"
RDEPENDS:${PN} += " systemd-networkd "

do_install() {
    # networkd configs
    install -d ${D}${sysconfdir}/systemd/network
    install -m 0644 ${S}/10-eth0-static.network \
        ${D}${sysconfdir}/systemd/network/
    install -m 0644 ${S}/20-wlan0.network \
        ${D}${sysconfdir}/systemd/network/

}

FILES:${PN} += " \
  ${sysconfdir}/systemd/network/10-eth0-static.network \
  ${sysconfdir}/systemd/network/20-wlan0.network \
  #${sysconfdir}/wpa_supplicant/wpa_supplicant-nl80211-wlan0.conf \
"
