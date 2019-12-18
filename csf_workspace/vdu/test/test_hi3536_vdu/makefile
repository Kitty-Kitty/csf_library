#test vdu for hi3536


PROJECT_NAME = test_hi3536_vdu


DIR_INC = .
DIR_SRC = .
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_LIB = ./lib


CROSS_COMPILE ?= arm-hisiv400-linux-
CC := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)ld
AR := $(CROSS_COMPILE)ar
STRIP := $(CROSS_COMPILE)strip


CFLAGS = -g -Wall -std=c++11 -I /opt/Project/hi3536/cp_player/third-party/lib/arm-hisiv400/qt-5.9.6/include -I /home/f/Project/hi3536/Hi3536_SDK_V2.0.6.0/mpp_single/component/gpu/release/include
#CFLAGS =-Wall -std=c++11 -I /opt/Project/hi3536/cp_player/third-party/lib/arm-hisiv400/qt-5.9.6/include -I /home/f/Project/hi3536/Hi3536_SDK_V2.0.6.0/mpp_single/component/gpu/release/include
LDFLAGS = -L /opt/hisi-linux/x86-arm/arm-hisiv400-linux/target/opt/Project/qt_project/qt-everywhere-opensource-src-5.9.6/qt-5.9.6/lib -L /home/f/Project/hi3536/Hi3536_SDK_V2.0.6.0/mpp_single/component/gpu/release/lib -lQt5Charts -lQt5Svg -lQt5Widgets -lQt5OpenGL -lQt5Core -lQt5Gui -lEGL -lGLESv1_CM -lGLESv2 -lmali


#SRC = $(wildcard ${DIR_SRC}/*.cpp)
SRC = test_hi3536_vdu.cpp
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))


all:
	echo $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROJECT_NAME) $(SRC)
	#$(STRIP) $(PROJECT_NAME)


.PHONY:clean
clean:
	rm -f *.o
	rm -f $(PROJECT_NAME)

