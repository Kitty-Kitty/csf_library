/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hisystem.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 20:29:46
*
*Description: Class(csf_hisystem)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "hi_include.hpp"
#include "csf_hisystem.hpp"
#include "csf_hiprocessor.hpp"
#include "hiaudio_conf.hpp"

using ec::core::csf_hisystem;


csf_hisystem::csf_hisystem() {

}



csf_hisystem::~csf_hisystem() {

}





/**
 * 功能：
 *    初始化通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hisystem::init(csf_hiprocessor* hiproc, const hisys_conf* hiconf) {

	//打印系统信息
	print_system(hiproc, hiconf);

	return csf_succeed;
}


/**
 * 功能：
 *    启动通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hisystem::start(csf_hiprocessor* hiproc, const hisys_conf* hiconf) {

	csf_int32		tmp_ret = 0;


	//启动海思系统
	tmp_ret = init_system(hiproc, hiconf);
	if (tmp_ret) {
		csf_log(error, "init system[hisiv] failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "init system[hisiv] succeed!");
	}

	return csf_succeed;
}


/**
 * 功能：
 *    停止通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hisystem::stop(csf_hiprocessor* hiproc, const hisys_conf* hiconf) {

	csf_int32		tmp_ret = 0;


	//退出海思系统
	tmp_ret = exit_system(hiproc, hiconf);
	if (tmp_ret) {
		csf_log(error, "exit system[hisiv] failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "exit system[hisiv] succeed!");
	}

	return csf_succeed;
}


/**
 * 功能：
 *    初始化系统
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hisystem::init_system(csf_hiprocessor* hiproc, const hisys_conf* hiconf) {

	hisys_conf		*tmp_sysconf = const_cast<hisys_conf*>(hiconf);

#ifdef HI_BUILD_PLATFORM
	HI_S32			tmp_int_ret = csf_failure;
	HI_U32			tmp_block_size = 0;
	VB_CONF_S		tmp_vb_conf = { 0, };
	MPP_SYS_CONF_S	tmp_sys_conf = { 0, };
	PIC_SIZE_E		tmp_pic_size = PIC_HD1080;


	SAMPLE_COMM_VI_GetSizeBySensor(&tmp_pic_size);

	tmp_block_size = SAMPLE_COMM_SYS_CalcPicVbBlkSize(VIDEO_ENCODING_MODE_NTSC
		, tmp_pic_size
		, SAMPLE_PIXEL_FORMAT
		, SAMPLE_SYS_ALIGN_WIDTH);

	csf_log(notice, "SENSOR_TYPE:%d PIC_SIZE:%d BLOCK_SIZE:%d"
		, SENSOR_TYPE
		, tmp_pic_size
		, tmp_block_size);

	//tmp_sys_conf.u32AlignWidth = tmp_sysconf->get_align_width();
	tmp_sys_conf.u32AlignWidth = SAMPLE_SYS_ALIGN_WIDTH;

	tmp_vb_conf.u32MaxPoolCnt = tmp_sysconf->get_max_pool_count();
	tmp_vb_conf.astCommPool[0].u32BlkSize = tmp_block_size;
	tmp_vb_conf.astCommPool[0].u32BlkCnt = 10;
 	tmp_vb_conf.astCommPool[1].u32BlkSize = tmp_block_size;
 	tmp_vb_conf.astCommPool[1].u32BlkCnt = 10;
 	tmp_vb_conf.astCommPool[2].u32BlkSize = tmp_block_size;
 	tmp_vb_conf.astCommPool[2].u32BlkCnt = 10;

	//先退出系统，后再初始化系统
	exit_system(hiproc, hiconf);

	tmp_int_ret = HI_MPI_VB_SetConf(&tmp_vb_conf);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_VB_SetConf() failed! error_code[0x%x]."
			, tmp_int_ret);

		return csf_failure;
	}
	else {
		csf_log(notice, "HI_MPI_VB_SetConf() succeed!");
	}

	tmp_int_ret = HI_MPI_VB_Init();
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_VB_Init() failed! error_code[0x%x]."
			, tmp_int_ret);

		return csf_failure;
	}
	else {
		csf_log(notice, "HI_MPI_VB_Init() succeed!");
	}

	tmp_int_ret = HI_MPI_SYS_SetConf(&tmp_sys_conf);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_SetConf() failed! error_code[0x%x]."
			, tmp_int_ret);

		return csf_failure;
	}
	else {
		csf_log(notice, "HI_MPI_SYS_SetConf() succeed!");
	}

	tmp_int_ret = HI_MPI_SYS_Init();
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_Init() failed! error_code[0x%x]."
			, tmp_int_ret);

		return csf_failure;
	}
	else {
		csf_log(notice, "HI_MPI_SYS_Init() succeed!");
	}

#endif

	return csf_succeed;
}


/**
 * 功能：
 *    退出系统
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hisystem::exit_system(csf_hiprocessor* hiproc, const hisys_conf* hiconf) {

#ifdef HI_BUILD_PLATFORM
	HI_MPI_SYS_Exit();
	HI_MPI_VB_Exit();
#endif

	return 0;
}


/**
* 功能：
*    打印系统信息
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param hiproc    表示海思处理模块对象
* @param hiconf    表示海思系统配置信息
*/
void csf_hisystem::print_system(csf_hiprocessor* hiproc, const hisys_conf* hiconf) {

#ifdef HI_BUILD_PLATFORM
	HI_S32			tmp_int_ret = csf_failure;
	HI_U32			tmp_chip_id = 0;
	MPP_VERSION_S	tmp_version = { 0, };


	//获取 MPP 的版本号
	tmp_int_ret = HI_MPI_SYS_GetVersion(&tmp_version);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "mpi information: get mpp version failed! error_code[0x%x]."
			, tmp_int_ret
		);
	}
	else {
		csf_log(notice, "mpi information: mpi version is [ %s ]"
			, tmp_version.aVersion);
	}

	//获取当前芯片的 ID
	tmp_int_ret = HI_MPI_SYS_GetChipId(&tmp_chip_id);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "mpi information: get chip id failed! error_code[0x%x]."
			, tmp_int_ret
		);
	}
	else {
		csf_log(notice, "mpi information: chip id is [ %#x ]"
			, tmp_chip_id);
	}

#endif
}


/**
* 功能：
*    判断系统是否已经在线
* 返回：
*    true ：表示在线
*    false：表示离线
*/
bool csf_hisystem::is_system_online() {

#ifdef HI_BUILD_PLATFORM

	HI_S32			tmp_int_ret = HI_SUCCESS;
	HI_U32			tmp_online_mode = 0;


	tmp_int_ret = HI_MPI_SYS_GetViVpssMode(&tmp_online_mode);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "HI_MPI_SYS_GetViVpssMode() failed! error_code[0x%x]."
			, tmp_int_ret);
		return false;
	}

	if (tmp_online_mode) {
		csf_log(notice
			, "HI_MPI_SYS_GetViVpssMode() succeed! vi_vpss mode[ online ].");
		return true;
	}
	else {
		csf_log(notice
			, "HI_MPI_SYS_GetViVpssMode() succeed! vi_vpss mode[ offline ].");
		return false;
	}

#endif

	return false;
}


/**
* 功能：
*    初始化 MPP 的时间戳基准
*/
void csf_hisystem::init_pts_base() {
#ifdef HI_BUILD_PLATFORM
	HI_S32			tmp_int_ret = csf_failure;
	HI_U64			tmp_pts_base = 0;


	//初始化 MPP 的时间戳基准
	tmp_int_ret = HI_MPI_SYS_InitPtsBase(tmp_pts_base);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_InitPtsBase() pts[%lld] failed! error_code[0x%x]."
			, tmp_pts_base
			, tmp_int_ret
		);
	}
	else {
		csf_log(error
			, "HI_MPI_SYS_InitPtsBase() pts[%lld] succeed!"
			, tmp_pts_base
		);
	}

#endif

}


/**
* 功能：
*    设置系统的配置类型
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param hiproc    表示海思处理模块对象
* @param hiconf    表示海思系统配置信息
*/
int csf_hisystem::set_profile(csf_hiprocessor* hiproc, const hisys_conf* hiconf) {

	hisys_conf		*tmp_sysconf = const_cast<hisys_conf*>(hiconf);

#if defined(HI_BUILD_PLATFORM)
	HI_S32			tmp_int_ret = csf_failure;
	PROFILE_TYPE_E	tmp_profile_type = PROFILE_BUTT;

	switch (tmp_sysconf->get_profile_index())
	{
	case hisys_conf::hiprofile_type_1080p_30:		//表示1080p@30的功耗场景类型
	{
		tmp_profile_type = PROFILE_1080P_30;
	}
	break;
	case hisys_conf::hiprofile_type_1080p_60:		//表示1080p@60的功耗场景类型
	{
		tmp_profile_type = PROFILE_1080P_60;
	}
	break;
	case hisys_conf::hiprofile_type_3m_30:		//表示3m@30的功耗场景类型
	{
		tmp_profile_type = PROFILE_3M_30;
	}
	break;
	case hisys_conf::hiprofile_type_5m_30:		//表示5m@30的功耗场景类型
	{
		tmp_profile_type = PROFILE_5M_30;
	}
	break;
	default:
	{
		csf_log(error
			, "unknow profile type[%s]."
			, tmp_sysconf->get_profile().c_str());

		return csf_failure;
	}
	break;
	}

	//设置profile类型
	tmp_int_ret = HI_MPI_SYS_SetProfile(tmp_profile_type);
	if (tmp_int_ret) {
		csf_log(error
			,"HI_MPI_SYS_SetProfile() profile type[%s] failed. error_code[0x%x]"
			, tmp_sysconf->get_profile().c_str()
			,tmp_int_ret);

		return csf_failure;
	}
	else {
		csf_log(notice
			, "HI_MPI_SYS_SetProfile() profile type[%s] succeed!"
			, tmp_sysconf->get_profile().c_str());
	}

#endif

	return csf_succeed;
}