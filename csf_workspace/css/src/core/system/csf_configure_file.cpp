/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure_file.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 30-6月-2018 11:58:29
*
*Description: Class(csf_configure_file)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_configure_file.hpp"

using csf::core::system::csf_configure_file;


csf_configure_file::csf_configure_file()
	: m_file_path("")
	, m_format("")
	, m_name("") {

}



csf_configure_file::~csf_configure_file() {

}





/**
 * 包含三个属性的构造函数
 * 
 * @param name    表示该配置项的名称
 * @param file_path    表示配置文件的文件路径
 * @param format    表示配置文件的文件格式，用于指导文件的解析
 */
csf_configure_file::csf_configure_file(const csf_char* name, const csf_char* file_path, const csf_char* format) {

}


/**
 * 包含三个属性的构造函数
 * 
 * @param name    表示该配置项的名称
 * @param file_path    表示配置文件的文件路径
 * @param format    表示配置文件的文件格式，用于指导文件的解析
 */
csf_configure_file::csf_configure_file(const csf_string& name, const csf_string& file_path, const csf_string& format) {

}