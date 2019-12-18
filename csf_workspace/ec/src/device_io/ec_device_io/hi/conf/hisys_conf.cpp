/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: hisys_conf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:48
*
*Description: Class(hisys_conf)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "hisys_conf.hpp"

using ec::core::hisys_conf;


/**
* 表示音频编码类型
*/
const std::map<std::string, hisys_conf::hiprofile_type> hisys_conf::m_profile_map  = {
	{ "1080P_30", hiprofile_type_1080p_30 },
	{ "3M_30", hiprofile_type_3m_30 },
	{ "1080P_60", hiprofile_type_1080p_60 },
	{ "5M_30", hiprofile_type_5m_30 }
};



hisys_conf::hisys_conf()
	: m_align_width(16)
	, m_max_pool_count(128) {

}



hisys_conf::~hisys_conf() {

}