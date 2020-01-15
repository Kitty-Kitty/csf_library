/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hivideo_storage_conf.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 15:11:48
*
*Description: Class(hivideo_storage_conf) 表示视频存储配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HIVIDEO_STORAGE_CONF_H_INCLUDED_)
#define HIVIDEO_STORAGE_CONF_H_INCLUDED_

#include <iostream>
#include "csf_typedef.h"

using namespace csf::core::base;

namespace ec
{
	namespace core
	{
		/**
		 * 表示视频存储配置信息
		 * @author f
		 * @version 1.0
		 * @created 07-12月-2019 15:11:48
		 */
		class hivideo_storage_conf
		{

		public:
			hivideo_storage_conf();
			virtual ~hivideo_storage_conf();

			/**
			 * 表示视频文件的播放时间长度
			 */
			inline csf_uint64 get_duration() {

				return m_duration;
			}
			/**
			 * 表示视频文件的播放时间长度
			 * 
			 * @param newVal
			 */
			inline void set_duration(csf_uint64 newVal) {

				m_duration = newVal;
			}

		private:
			/**
			 * 表示视频文件的播放时间长度
			 */
			csf_uint64 m_duration = 0;

		};

	}

}
#endif // !defined(HIVIDEO_STORAGE_CONF_H_INCLUDED_)
