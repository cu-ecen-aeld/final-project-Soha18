Integrating Qt5 Plugins and Backends in Yocto HMI Project
Background

In this HMI project, Qt5 is used for the graphical user interface running on an embedded Linux system built using the Yocto Project. Qt's backends (like linuxfb, eglfs, etc.) are essential for rendering graphics directly to the framebuffer without a windowing system like X11 or Wayland, which were removed via:

DISTRO_FEATURES:remove = "X11 wayland"

Initial Approach

The initial implementation attempted to include Qt-related libraries and plugins directly through the IMAGE_INSTALL variable in the image recipe:

IMAGE_INSTALL += "qtbase-plugins qt-gui qtbase qtcharts ..."

Additionally, the GUI application recipe (guiapp.bb) correctly added:

DEPENDS += "qtbase"

Problem Encountered

After building the image:

    Qt runtime libraries were present.

    No usable QPA backends (like linuxfb or eglfs) were available in the final image.

    The application failed at runtime with errors like:

    Could not load the Qt platform plugin "linuxfb" in "" even though it was found.

    Installed qtbase-plugins package contained only minimal plugins.

Investigation

Yocto’s build system separates:

    How packages are built (decided at recipe build time by PACKAGECONFIG variables)

    Which packages are installed in the image (decided at image creation time by IMAGE_INSTALL)

At image creation, it was simply installing whatever build artifacts existed for qtbase-plugins — which, due to missing PACKAGECONFIG flags, did not include critical backends.
Root Cause

The required QPA backends (linuxfb, eglfs, etc.) were not enabled at build time in the qtbase recipe.
Solution

Create a qtbase_%.bbappend in the project’s custom layer (meta-hmi) to configure PACKAGECONFIG correctly.

File: meta-hmi/recipes-qt/qt5/qtbase_%.bbappend

PACKAGECONFIG:append = " linuxfb eglfs gbm gles2 kms sql-sqlite"
PACKAGECONFIG:remove = "gl tests examples"

Correct Build Process

    Add the bbappend file as shown above

    Clean the old build to force rebuild with new configuration

bitbake -c cleansstate qtbase

Rebuild qtbase

bitbake qtbase

Build the final image

bitbake hmi-image

Verify the built plugins

    find tmp/deploy/images/ -name "*plugin*" | grep linuxfb

    Confirm application runs correctly with specified QPA backend

Recommended Best Practice

To avoid scattered configurations for Qt recipes:

    Create a shared configuration include:
    File: meta-hmi/recipes-qt/qt5/qt5-config.inc

QT_COMMON_PACKAGECONFIG = "linuxfb eglfs gbm gles2 kms sql-sqlite"
QT_REMOVE_PACKAGECONFIG = "gl tests examples"

Reference this .inc file in multiple bbappend files:

    require qt5-config.inc

    PACKAGECONFIG:append = " ${QT_COMMON_PACKAGECONFIG} "
    PACKAGECONFIG:remove = " ${QT_REMOVE_PACKAGECONFIG} "

Lessons Learned
Mistake	Cause	Solution
Relying solely on IMAGE_INSTALL to control runtime capabilities	Yocto separates build-time features from image packaging	Use PACKAGECONFIG in a bbappend or distro config to control build features
Not verifying built plugin contents before image build	Assumed installed packages had desired runtime plugins	Always inspect build artifacts or use tools like oe-pkgdata-util list-pkg-files
Changing DISTRO_FEATURES or IMAGE_INSTALL without cleaning affected recipes	Yocto won’t rebuild packages unless inputs change	Clean affected packages (bitbake -c cleansstate) when changing build config
Conclusion

The issue stemmed from misunderstanding the Yocto package build/install separation. Properly managing Qt backend options via PACKAGECONFIG in a bbappend resolved the issue, ensuring the image included the necessary QPA plugins for framebuffer rendering.
