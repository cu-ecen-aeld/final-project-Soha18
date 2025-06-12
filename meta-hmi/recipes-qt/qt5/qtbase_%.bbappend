PACKAGECONFIG:append = " \
    linuxfb \
    eglfs \
    gbm \
    gles2 \
    tslib \
    sql-sqlite \
    xcb \
"
PACKAGECONFIG:append = " accessibility fontconfig "
PACKAGECONFIG:remove = " \
    gl \
    tests \
    examples \
"
