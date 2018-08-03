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
*Date: 30-6��-2018 11:58:29
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
 * �����������ԵĹ��캯��
 * 
 * @param name    ��ʾ�������������
 * @param file_path    ��ʾ�����ļ����ļ�·��
 * @param format    ��ʾ�����ļ����ļ���ʽ������ָ���ļ��Ľ���
 */
csf_configure_file::csf_configure_file(const csf_char* name, const csf_char* file_path, const csf_char* format) {

}


/**
 * �����������ԵĹ��캯��
 * 
 * @param name    ��ʾ�������������
 * @param file_path    ��ʾ�����ļ����ļ�·��
 * @param format    ��ʾ�����ļ����ļ���ʽ������ָ���ļ��Ľ���
 */
csf_configure_file::csf_configure_file(const csf_string& name, const csf_string& file_path, const csf_string& format) {

}