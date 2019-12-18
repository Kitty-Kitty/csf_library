/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hivideo_channel_conf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:48
*
*Description: Class(hivideo_channel_conf) 表示媒体通道配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HIVIDEO_CHANNEL_CONF_H_INCLUDED_)
#define HIVIDEO_CHANNEL_CONF_H_INCLUDED_

#include <iostream>

#include "hichannel_conf.hpp"
#include "hidisk_storage_conf.hpp"
#include "hivideo_storage_conf.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体通道配置信息
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:31:48
		 */
		class hivideo_channel_conf : public ec::core::hichannel_conf
		{

		public:
			hivideo_channel_conf();
			virtual ~hivideo_channel_conf();
		public:
			/**
			* 表示存储空间大小配置
			*/
			inline hidisk_storage_conf& get_disk_storage() {

				return m_disk_storage;
			}
			/**
			* 表示存储空间大小配置
			*
			* @param newVal
			*/
			inline void set_disk_storage(hidisk_storage_conf& newVal) {

				m_disk_storage = newVal;
			}
			/**
			* 表示视频存储空间大小配置
			*/
			inline hivideo_storage_conf& get_video_storage() {

				return m_video_storage;
			}
			/**
			* 表示视频存储空间大小配置
			*
			* @param newVal
			*/
			inline void set_video_storage(hivideo_storage_conf& newVal) {

				m_video_storage = newVal;
			}

		private:
			/**
			* 表示磁盘存储空间大小配置
			*/
			hidisk_storage_conf m_disk_storage;
			/**
			* 表示视频存储空间大小配置
			*/
			hivideo_storage_conf m_video_storage;
		};

	}

}
#endif // !defined(HIVIDEO_CHANNEL_CONF_H_INCLUDED_)
