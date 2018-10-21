/*******************************************************************************
*
*Copyright: fangzhenmu@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_stream_connect.hpp
*
*Version: 1.0
*
*Date: 02-10��-2018 14:17:59
*
*Description: Class(csf_stream_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_stream_connect.hpp"

using csf::modules::connect::csf_stream_connect;



csf_stream_connect::~csf_stream_connect() {

}




/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_stream_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ��������Ϣ.
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 * 
 * @param url    ��ʾ���ӵ�ַ
 */
csf_int32 csf_stream_connect::open(const csf_url& url) {

	return 0;
}


/**
 * ��ʾ�ر�����.
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 */
csf_int32 csf_stream_connect::close() {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_stream_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�������ӵ�������Ŀ��Ϣ��
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
 */
csf_int32 csf_stream_connect::set_option() {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_stream_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
 */
csf_int32 csf_stream_connect::get_option() {

	return 0;
}


/**
 * ��ʾ���ö���ʱʱ��.
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 * 
 * @param timeout_ms
 * @param callback    ��ʾ��ʱ�ص�������
 */
csf_int32 csf_stream_connect::set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����д��ʱʱ�䡣
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 * 
 * @param timeout_ms
 * @param callback    ��ʾ��ʱ�ص�������
 */
csf_int32 csf_stream_connect::set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}
