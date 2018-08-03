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
*Date: 27-6月-2018 17:28:35
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
 * 查询收集器的元素总个数。
 * 返回：>=0表示元素的总个数。
 */
csf_int32 csf_collector::size() {

	return 0;
}


/**
 * 表示清空收集器中的所有元素
 */
csf_bool csf_collector::clear() {

	return csf_true;
}