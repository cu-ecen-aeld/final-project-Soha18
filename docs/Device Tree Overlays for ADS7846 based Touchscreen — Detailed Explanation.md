## Device Tree Overlays for ADS7846 Touchscreen — Detailed Explanation

---

### Overview

This document explains in deep detail the contents and structure of two Device Tree Source (DTS) overlay files used to integrate an ADS7846 touchscreen controller with a Raspberry Pi via SPI. It also covers how chip select (CS) lines are assigned, how to choose them, and how these relate to SPI bus configuration.

---

## Device Tree Basics

* **DTS** files describe hardware devices for the Linux kernel.
* **Device Tree Overlays** extend or modify the base device tree at runtime.
* SPI devices are connected on a bus with CS (chip select) lines used to address them.

---



## 📌 SPI Chip Select and CS Pin Selection

**SPI Concept:**

* Devices on an SPI bus are addressed via Chip Select (CS) lines.
* SPI0 on Raspberry Pi typically has CS0 (spidev0) and CS1 (spidev1).

**In Device Tree:**

* `reg = <0>` uses CS0.
* `reg = <1>` uses CS1.

**Device Tree Fragments:**

* Fragments disable spidevN nodes to free CS lines.
* Fragments\@4 adds touchscreen node on chosen CS.

**Choosing CS:**

* Based on physical wiring between touchscreen CS pin and Raspberry Pi CS line.
* If touchscreen wired to SPI0 CS0 → use `reg = <0>`.
* If wired to SPI0 CS1 → use `reg = <1>`.

---

**How to write custom overlay for MPI3508 Touchscreen:**

This Part serves as a detailed reference for configuring ADS7846 touchscreens on Raspberry Pi via Device Tree overlays.
📖 Full Annotated Deep-Dive into DTS #1
📌 Device Tree Overlay Header

/dts-v1/;
/plugin/;

✅ Meaning:

    /dts-v1/; → Declares that this file uses Device Tree Source version 1 syntax.

    /plugin/; → Marks this file as a Device Tree overlay plugin. Overlays are patches that get merged into the main Device Tree at runtime (or boot time, on Raspberry Pi for example via /boot/config.txt).

📌 Root Node

/ {
    compatible = "brcm,bcm2835";

✅ Meaning:

    / { } → The root node of the device tree.

    compatible = "brcm,bcm2835"; → This overlay is designed for Broadcom SoCs compatible with bcm2835 (used by Raspberry Pi). The kernel uses this string to match drivers and overlays to hardware.

📦 Fragment Nodes

Overlays are organized into fragments — each fragment modifies or adds something to the main Device Tree.
📌 Fragment 0 — Enable SPI0

fragment@0 {
    target = <&spi0>;
    __overlay__ {
        status = "okay";
    };
};

✅ Meaning:

    fragment@0 {} → The first overlay fragment.

    target = <&spi0>; → Refers to the existing spi0 node in the base Device Tree.

    __overlay__ { status = "okay"; } → This patch modifies the spi0 node to enable it (sets status from "disabled" to "okay").

📌 Fragment 1 & 2 — Disable spidev devices

fragment@1 {
    target = <&spidev0>;
    __overlay__ {
        status = "disabled";
    };
};

fragment@2 {
    target = <&spidev1>;
    __overlay__ {
        status = "disabled";
    };
};

✅ Meaning:

    spidev0 and spidev1 are default SPI character devices attached to spi0 chip selects CS0 and CS1.

    By disabling them, we make sure those chip selects are available for other devices (like our touchscreen controller).

    target = <&spidev0>; — Refers to existing node spidev0 in base DT.

    status = "disabled"; — Tells kernel not to instantiate this spidev device.

Why?
To prevent conflicts and free up CS lines for our own hardware.
📌 Fragment 3 — Define GPIO pins for Touchscreen IRQ

fragment@3 {
    target = <&gpio>;
    __overlay__ {
        ads7846_pins: ads7846_pins {
            brcm,pins = <255>;
            brcm,function = <0>; /* input */
            brcm,pull = <2>; /* pull-up */
        };
    };
};

✅ Meaning:

    target = <&gpio>; — Refers to GPIO controller node in base DT.

    ads7846_pins: → Creates a named pinctrl node for our touchscreen, defining how its interrupt line (PENIRQ) is configured.

    brcm,pins = <255>; → Illegal placeholder value. This gets replaced via __overrides__. (Why 255? Because it’s out of normal GPIO range and signals “to be filled.”)

    brcm,function = <0>; → Set this pin as input.

    brcm,pull = <2>; → Set this GPIO’s pull mode to pull-up resistor.

Why?
The touchscreen IRQ line is active-low. A pull-up keeps it high when idle.
📌 Fragment 4 — Add ads7846 Device Node

fragment@4 {
    target = <&spi0>;
    __overlay__ {
        #address-cells = <1>;
        #size-cells = <0>;

✅ Meaning:

    target = <&spi0>; → Adds a child device to spi0.

    #address-cells = <1>; and #size-cells = <0>;

        Tells Device Tree parser how to interpret child node addresses.

        1 cell for address (SPI chip select number), 0 for size (not needed for SPI devices).

📌 Define ads7846@1 SPI Device

        ads7846@1 {
            compatible = "ti,ads7846";
            reg = <1>;
            spi-max-frequency = <2000000>;

✅ Meaning:

    ads7846@1 → SPI device on chip select 1 (CS1).

    compatible = "ti,ads7846"; → Kernel uses this string to match the device driver.

    reg = <1>; → CS line number.

    spi-max-frequency = <2000000>; → Max SPI clock speed (2 MHz).

📌 Link Pin Control

            pinctrl-names = "default";
            pinctrl-0 = <&ads7846_pins>;

✅ Meaning:

    Specifies the pinctrl configuration to use.

    pinctrl-0 = <&ads7846_pins>; links to the earlier-defined GPIO config in fragment 3.

📌 Interrupt Definition

            interrupt-parent = <&gpio>;
            interrupts = <255 2>;

✅ Meaning:

    interrupt-parent = <&gpio>; → GPIO controller handles the interrupt.

    interrupts = <255 2>;

        255 = GPIO number (to be overridden via __overrides__).

        2 = Interrupt type (falling edge — when the line goes from high to low).

📌 Device Properties

            touchscreen-size-x = <4096>;
            touchscreen-size-y = <4096>;
            ti,x-min = /bits/ 16 <200>;
            ti,x-max = /bits/ 16 <3900>;
            ti,y-min = /bits/ 16 <200>;
            ti,y-max = /bits/ 16 <3900>;
            ti,pressure-min = /bits/ 16 <0>;
            ti,pressure-max = /bits/ 16 <255>;
            ti,x-plate-ohms = /bits/ 16 <60>;
        };

✅ Meaning:
Defines hardware parameters — from max X/Y ranges to touch pressure sensitivity to electrical resistance — which the ADS7846 driver uses to calibrate touch input.
📦 Overrides Section — Dynamic Parameters

__overrides__ {
    cs = <&ads7846@1>,"reg:0";
    speed = <&ads7846@1>,"spi-max-frequency:0";
    penirq = <&ads7846_pins>,"brcm,pins:0",
             <&ads7846@1>,"interrupts:0";
};

✅ Meaning:
Defines dynamic parameters you can pass from the command line or config.txt at boot time like:

dtoverlay=my_touchscreen-overlay.dtbo,cs=0,penirq=22

    cs → SPI chip select

    speed → Max SPI clock speed

    penirq → GPIO pin for IRQ (both in pinctrl and interrupts property)

This makes the overlay highly reusable without editing the DTS.
📑 Why All These Nodes?

Device Tree overlays describe hardware topology and tell the kernel:

    Which devices are attached

    Where they are connected (SPI, GPIO, I2C, etc.)

    What parameters and interrupts they have

    Which drivers to use

The kernel doesn’t “discover” hardware on its own — it reads the Device Tree Blob (DTB) at boot (or dynamic overlays) to instantiate and configure devices properly.
📌 How It Works

    Base DTB loads

    Overlay fragments patch specific nodes (target)

    New nodes (like ads7846@1) are created

    Kernel drivers match on compatible strings

    Driver reads properties (spi-max-frequency, interrupts, etc.)

    Hardware initialized according to parameters

    Dynamic __overrides__ allow config-time flexibility
    

## 📌 Summary

* Device Tree overlays modify hardware definitions at runtime.
* Fragments target specific existing nodes to enable/disable/configure devices.
* CS lines on SPI buses must be managed carefully to avoid conflicts.
* The `__overrides__` section allows flexible runtime changes via config files.
* Chip select assignment must match both physical connections and `reg` values.

---


