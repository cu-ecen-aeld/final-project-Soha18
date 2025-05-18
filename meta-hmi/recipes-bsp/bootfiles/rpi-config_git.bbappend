FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://ts_config_additions.txt"

do_deploy:append() {
    echo "dtoverlay=ads7846-overlay" >> ${DEPLOYDIR}/config.txt
}

