#!/bin/sh


current_path=$(cd `dirname $0`; pwd);
pwd_path=$pwd


export set LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/hi3536/other/cp_vdu/lib/arm-hisiv400
export set QT_QPA_PLATFORM_PLUGIN_PATH="/mnt/hi3536/other/cp_vdu/lib/arm-hisiv400/plugins"
#export set QT_QPA_PLATFORM=linuxfb:tty=/dev/fb0
export set QT_QPA_PLATFORM=eglfs
export set QT_QPA_FONTDIR=/mnt/hi3536/csf_library/csf_workspace/vdu/test/test_hi3536_vdu/fonts
export set QT_QPA_EGLFS_PHYSICAL_WIDTH=3840
export set QT_QPA_EGLFS_PHYSICAL_HEIGHT=2160
export set XDG_RUNTIME_DIR=/tmp/runtime-root
export set LD_PRELOAD=/mnt/hi3536/other/cp_vdu/lib/arm-hisiv400/preloadable_libiconv.so


#/mnt/hi3536/gdb-7.10.1/gdbserver-7.10.1/bin/arm-hisiv400-linux-gdbserver 192.168.1.103:8080 ${current_path}/test_hi3536_vdu -f ./tiger.svg
#${current_path}/test_hi3536_vdu -f ./tiger.svg
${current_path}/test_hi3536_vdu -f ./chart.svg

