/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_thread_pool.hpp
*
*Version: 1.0
*
*Date: 21-10ÔÂ-2018 16:52:05
*
*Description: Class(csf_thread_pool)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_thread_pool.hpp"

using csf::core::utils::thread::csf_thread_pool;


csf_thread_pool::csf_thread_pool()
	: m_thread_number(csf_thread_pool_default_thread_number)
	, m_max_failure_times(csf_thread_pool_max_failure_times) {

}



csf_thread_pool::~csf_thread_pool() {
	stop();
}