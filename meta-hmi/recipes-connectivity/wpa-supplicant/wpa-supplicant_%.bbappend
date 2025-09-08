
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://wpa_supplicant-nl80211-wlan0.conf"

S = "${WORKDIR}/wpa_supplicant-${PV}"

inherit systemd
SYSTEMD_SERVICE:${PN} = "wpa_supplicant-nl80211@wlan0.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"

do_install:append() {
    # Create directory for wpa_supplicant configs
    install -d ${D}${sysconfdir}/wpa_supplicant/

    # Install wlan0 config with the correct filename
    install -D -m 600 ${WORKDIR}/sources-unpack/wpa_supplicant-nl80211-wlan0.conf \
        ${D}${sysconfdir}/wpa_supplicant/wpa_supplicant-nl80211-wlan0.conf

    # Enable systemd unit for wlan0
    install -d ${D}${sysconfdir}/systemd/system/multi-user.target.wants/
    ln -s ${systemd_unitdir}/system/wpa_supplicant-nl80211@.service \
        ${D}${sysconfdir}/systemd/system/multi-user.target.wants/wpa_supplicant-nl80211@wlan0.service
}

#FILES:${PN} += " ${sysconfdir}/wpa_supplicant/wpa_supplicant-nl80211-wlan0.conf "
