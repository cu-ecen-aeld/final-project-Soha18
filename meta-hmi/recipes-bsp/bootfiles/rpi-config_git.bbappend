FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://ts_config_additions.txt"

do_deploy:append() {
    echo "hdmi_cvt 800 480 60 6 0 0 0" >> ${DEPLOYDIR}/bootfiles/config.txt 
    echo "hdmi_mode=87" >> ${DEPLOYDIR}/bootfiles/config.txt
    echo "hdmi_group=2" >> ${DEPLOYDIR}/bootfiles/config.txt
    echo "display_rotate=2" >> ${DEPLOYDIR}/bootfiles/config.txt
}

