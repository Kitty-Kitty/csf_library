/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fz
*
*File name: hi_include.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:50:14
*
*Description: 海思处理需要的头文件内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HI_INCLUDE_H_INCLUDED_)
#define HI_INCLUDE_H_INCLUDED_

#include <iostream>
#include "csf_logger.hpp"
#include "csf_stdbind.hpp"


#define HIAI_CHANNEL_NAME		"-hiai_audio_encoder_channel_"
#define HIVI_CHANNEL_NAME		"-hiai_video_encoder_channel_"


#ifdef __linux__
#define HI_BUILD_PLATFORM
#endif

//#define		HI_TEST_LOADER
#ifdef		HI_BUILD_PLATFORM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined(__linux__)
#include <pthread.h>
#include <sys/ioctl.h>
#endif

#include "hi_common.h"
#include "hi_comm_sys.h"
#include "hi_comm_vb.h"
#include "hi_comm_adec.h"
#include "hi_comm_aenc.h"
#include "hi_comm_ai.h"
#include "hi_comm_ao.h"
#include "hi_comm_aio.h"
#include "hi_defines.h"

#include "mpi_sys.h"
#include "mpi_vb.h"
#include "mpi_sys.h"
#include "mpi_vb.h"
#include "mpi_adec.h"
#include "mpi_aenc.h"
#include "mpi_ai.h"
#include "mpi_ao.h"

#include "sample_comm.h"

#endif




#endif // !defined(HI_INCLUDE_H_INCLUDED_)
