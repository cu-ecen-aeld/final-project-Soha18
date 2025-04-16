#!/bin/bash
# Script to build image for Raspberry Pi 3
# Author: Soha (adapted from Siddhant Jajoo)

set -e

# Initialize and sync submodules (if used)
git submodule init
git submodule sync
git submodule update

# Source the environment and create build directory
source poky/oe-init-build-env

# Set target MACHINE
MACHINE_LINE='MACHINE = "raspberrypi3-64"'

# Append MACHINE setting if not already present
if ! grep -q "${MACHINE_LINE}" conf/local.conf; then
    echo "Appending ${MACHINE_LINE} to conf/local.conf"
    echo "${MACHINE_LINE}" >> conf/local.conf
else
    echo "${MACHINE_LINE} already exists in conf/local.conf"
fi

# Add meta-raspberrypi layer
if ! bitbake-layers show-layers | grep -q "meta-raspberrypi"; then
    echo "Adding meta-raspberrypi layer"
    bitbake-layers add-layer ../meta-raspberrypi
else
    echo "meta-raspberrypi layer already added"
fi

# Add meta-openembedded sublayers (individually)
OPENEMBEDDED_LAYERS=("meta-oe" "meta-python" "meta-networking")

for layer in "${OPENEMBEDDED_LAYERS[@]}"; do
    if ! bitbake-layers show-layers | grep -q "$layer"; then
        echo "Adding $layer layer from meta-openembedded"
        bitbake-layers add-layer ../meta-openembedded/$layer
    else
        echo "$layer layer already added"
    fi
done

# Build the image (replace with your custom image if needed)
bitbake core-image-minimal

