FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
DEPENDS += "dtc-native"

PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI:append:raspberrypi3-64 = " file://ads7846-overlay.dts;subdir=git/arch/arm64/boot/dts/overlays \
"

#do_install:append() {
#    install -d ${D}/boot/overlays
#    install -m 0644 ${B}/arch/arm64/boot/dts/overlays/ads7846.dtbo ${D}/boot/overlays/
#}

KERNEL_DEVICETREE:append = " overlays/ads7846.dtbo"

