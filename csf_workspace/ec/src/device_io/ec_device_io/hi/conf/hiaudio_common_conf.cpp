/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: hiaudio_common_conf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:47
*
*Description: Class(hiaudio_common_conf)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "hiaudio_common_conf.hpp"

using ec::core::hiaudio_common_conf;


/**
* 表示音频编码类型
*/
const std::map<std::string, hiaudio_common_conf::hiaudio_encode_tpe> hiaudio_common_conf::m_encode_type_map = {
	{ "none", hiaudio_encode_type_none },
	{ "aac", hiaudio_encode_type_aac }
};


/**
* 表示音频声道模式
*/
const std::map<std::string, hiaudio_common_conf::hiaudio_sound_mode> hiaudio_common_conf::m_sound_mode_map = {
	{ "none", hiaudio_sound_mode_none },
	{ "mono", hiaudio_sound_mode_mono },
	{ "stereo", hiaudio_sound_mode_stereo }
};


hiaudio_common_conf::hiaudio_common_conf()
	: m_dev_id(0)
	, m_dev_channel(0)
	, m_coder_channel(0)
	, m_encode_type("")
	, m_sample_rate(44100)
	, m_sound_mode("") {

}



hiaudio_common_conf::~hiaudio_common_conf() {

}