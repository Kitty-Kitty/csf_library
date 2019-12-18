#!/bin/sh


current_path=$(cd `dirname $0`; pwd);
pwd_path=$pwd


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/hi3536/other/cp_vdu/lib/arm-hisiv400
export QT_QPA_PLATFORM_PLUGIN_PATH="/mnt/hi3536/other/cp_vdu/lib/arm-hisiv400/plugins"
export QT_QPA_PLATFORM=linuxfb:tty=/dev/fb0
export QT_QPA_PLATFORM=eglfs
export QT_QPA_EGLFS_PHYSICAL_WIDTH=3840
export QT_QPA_EGLFS_PHYSICAL_HEIGHT=2160
export XDG_RUNTIME_DIR=/tmp/runtime-root
export LD_PRELOAD=/mnt/hi3536/other/cp_vdu/lib/arm-hisiv400/preloadable_libiconv.so


${current_path}/svg_opengl_demo

