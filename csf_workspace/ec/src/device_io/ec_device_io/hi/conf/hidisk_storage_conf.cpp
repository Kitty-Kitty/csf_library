/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: hidisk_storage_conf.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 15:11:47
*
*Description: Class(hidisk_storage_conf)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "hidisk_storage_conf.hpp"

using ec::core::hidisk_storage_conf;


hidisk_storage_conf::hidisk_storage_conf()
	: m_path("")
	, m_rotation_size(0)
	, m_stored_max_size(0)
	, m_disk_min_free_size(0) {

}



hidisk_storage_conf::~hidisk_storage_conf() {

}