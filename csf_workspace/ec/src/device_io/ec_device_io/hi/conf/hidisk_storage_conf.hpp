/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hidisk_storage_conf.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 15:11:47
*
*Description: Class(hidisk_storage_conf) 表示磁盘存储配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HIDISK_STORAGE_CONF_H_INCLUDED_)
#define HIDISK_STORAGE_CONF_H_INCLUDED_

#include <iostream>
#include "csf_typedef.h"

using namespace csf::core::base;

namespace ec
{
	namespace core
	{
		/**
		 * 表示磁盘存储配置信息
		 * @author f
		 * @version 1.0
		 * @created 07-12月-2019 15:11:47
		 */
		class hidisk_storage_conf
		{

		public:
			hidisk_storage_conf();
			virtual ~hidisk_storage_conf();

			/**
			 * 表示存储文件的目录地址
			 */
			inline std::string get_path() {

				return m_path;
			}
			/**
			 * 表示存储文件的目录地址
			 * 
			 * @param newVal
			 */
			inline void set_path(std::string newVal) {

				m_path = newVal;
			}
			/**
			 * 表示单文件回滚最大大小，即每个文件的最大大小。
			 */
			inline csf_uint64 get_rotation_size() {

				return m_rotation_size;
			}
			/**
			 * 表示单文件回滚最大大小，即每个文件的最大大小。
			 * 
			 * @param newVal
			 */
			inline void set_rotation_size(csf_uint64 newVal) {

				m_rotation_size = newVal;
			}
			/**
			 * 表示日志占用磁盘最大大小，stored_max_size/rotation_size表示保存的日志文件数量。
			 */
			inline csf_uint64 get_stored_max_size() {

				return m_stored_max_size;
			}
			/**
			 * 表示日志占用磁盘最大大小，stored_max_size/rotation_size表示保存的日志文件数量。
			 * 
			 * @param newVal
			 */
			inline void set_stored_max_size(csf_uint64 newVal) {

				m_stored_max_size = newVal;
			}
			/**
			 * 表示磁盘空间最小多大的时候才能写日志。
			 */
			inline csf_uint64 get_disk_min_free_size() {

				return m_disk_min_free_size;
			}
			/**
			 * 表示磁盘空间最小多大的时候才能写日志。
			 * 
			 * @param newVal
			 */
			inline void set_disk_min_free_size(csf_uint64 newVal) {

				m_disk_min_free_size = newVal;
			}

		private:
			/**
			 * 表示存储文件的目录地址
			 */
			std::string m_path = "";
			/**
			 * 表示单文件回滚最大大小，即每个文件的最大大小。
			 */
			csf_uint64 m_rotation_size = 0;
			/**
			 * 表示日志占用磁盘最大大小，stored_max_size/rotation_size表示保存的日志文件数量。
			 */
			csf_uint64 m_stored_max_size = 0;
			/**
			 * 表示磁盘空间最小多大的时候才能写日志。
			 */
			csf_uint64 m_disk_min_free_size = 0;

		};

	}

}
#endif // !defined(HIDISK_STORAGE_CONF_H_INCLUDED_)
