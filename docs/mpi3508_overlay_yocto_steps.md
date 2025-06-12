
# Custom Overlay Development for MPI3508 Touchscreen in Yocto  
**Using the `recipetool` method**

## 📌 Introduction  
This document outlines the step-by-step workflow for integrating a custom Device Tree Overlay (`*.dts`) for the MPI3508 touchscreen into a Yocto-based Embedded Linux system for Raspberry Pi. The method leverages Yocto’s `recipetool` for clean integration into a custom layer and activation of the overlay at boot.

## 📋 Steps

### 1️⃣ Prepare Yocto Build Environment  
Start by setting up the Yocto environment:
```bash
source poky/oe-init-build-env
```

### 2️⃣ Create a Custom Meta Layer  
Use the `bitbake-layers` command to create a new layer for the overlay source:
```bash
bitbake-layers create-layer meta-mydts
```

This creates the `meta-mydts` directory with the required layer structure.

### 3️⃣ Import the Custom Overlay DTS  
Use the `recipetool appendsrcfile` command to integrate your custom overlay DTS file into the kernel recipe.

**Command syntax:**
```bash
recipetool appendsrcfile -wm <machine-name> . virtual/kernel <source-path> 'arch/${ARCH}/boot/dts/overlays/<destination-file>'
```

**Example for Raspberry Pi 3-64:**
```bash
recipetool appendsrcfile -wm raspberrypi3-64 . virtual/kernel path/to/mpi3508-overlay.dts 'arch/${ARCH}/boot/dts/overlays/mpi3508-overlay.dts'
```

This command:
- Places the DTS file under your custom meta-layer
- Generates a `.bbappend` for the kernel
- Updates the kernel build path to include your overlay

### 4️⃣ Modify `KERNEL_DEVICETREE` Variable  
In meta-raspberrypi layer’s `conf/machine/raspberrypi3-64.conf`, append your overlay to the `KERNEL_DEVICETREE` variable:

**Example:**
```conf
KERNEL_DEVICETREE:append = " overlays/mpi3508.dtbo"
```

**Note:**  
Do **not** include the `-overlay` suffix in the `.dtbo` filename here. and it is important to use :append rather that += operator


### 6️⃣ Activate the Overlay at Boot  
To automatically load the overlay at boot, use the `RPI_EXTRA_CONFIG` variable in `conf/local.conf`:

**Example:**
```conf
RPI_EXTRA_CONFIG:append = "\ndtoverlay=mpi3508\n"
```

This ensures that the overlay gets applied by the Raspberry Pi firmware on startup.

## 📌 Summary  
| Task                     | Command/Config                                                   |
|:------------------------|:----------------------------------------------------------------|
| Initialize Yocto env     | `source poky/oe-init-build-env`                                 |
| Create new meta-layer     | `bitbake-layers create-layer meta-mydts`                        |
| Import overlay DTS file   | `recipetool appendsrcfile -wm <machine> . virtual/kernel ...`   |
| Append overlay to kernel  | `KERNEL_DEVICETREE:append = " overlays/mpi3508.dtbo"`           |
| Register layer in Yocto   | Add to `bblayers.conf`                                          |
| Auto-load overlay at boot | `RPI_EXTRA_CONFIG:append = "\ndtoverlay=mpi3508\n"`             |

## 📌 Notes
- Use `raspberrypi3-64`, `raspberrypi4-64`, etc. for your machine name depending on your target.
- Ensure your `.dts` file is properly tested with local `dtc` before integrating.
- Validate the `penirq` GPIO mapping and IRQ settings within the overlay.
- Use `dmesg`, `evtest`, and `cat /sys/kernel/debug/gpio` for runtime debugging.
- It took me quite some time to realize a critical detail when working with custom overlays on Yocto and Raspberry Pi. Always use a unique, custom name for your overlay source file.

For example, I originally named my overlay file ads7846-overlay.dts because my touchscreen uses an ADS7846-compatible controller. However, every time I built and deployed it, it behaved unexpectedly — always applying default configurations, and my intended properties were ignored.

After investigation, I discovered that this was happening because the system image already includes a default ads7846 overlay, and even though my custom DTS was being compiled, it wasn’t properly overriding the default. Yocto and the Raspberry Pi firmware tend to prioritize built-in or existing overlays if the names conflict.

As soon as I changed my custom DTS file name (for example, to myads7846-custom-overlay.dts), everything worked exactly as expected. The system loaded my intended configuration, and the touchscreen responded properly.
