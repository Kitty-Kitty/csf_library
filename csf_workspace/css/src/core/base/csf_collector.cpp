/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_collector.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:35
*
*Description: Class(csf_collector)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_collector.hpp"

using csf::core::base::csf_collector;


csf_collector::csf_collector() {

}



csf_collector::~csf_collector() {

}





/**
 * ��ѯ�ռ�����Ԫ���ܸ�����
 * ���أ�>=0��ʾԪ�ص��ܸ�����
 */
csf_int32 csf_collector::size() {

	return 0;
}


/**
 * ��ʾ����ռ����е�����Ԫ��
 */
csf_bool csf_collector::clear() {

	return csf_true;
}