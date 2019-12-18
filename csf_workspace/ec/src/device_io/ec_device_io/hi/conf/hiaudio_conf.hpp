/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hiaudio_conf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:47
*
*Description: Class(hiaudio_conf) 表示海思音频配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HIAUDIO_CONF_H_INCLUDED_)
#define HIAUDIO_CONF_H_INCLUDED_

#include <iostream>

#include "hiaudio_aiconf.hpp"
#include "hiaudio_aoconf.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示海思音频配置信息
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:31:47
		 */
		class hiaudio_conf
		{

		public:
			hiaudio_conf();
			virtual ~hiaudio_conf();
			ec::core::hiaudio_aiconf *m_hiaudio_aiconf;
			ec::core::hiaudio_aoconf *m_hiaudio_aoconf;

			/**
			 * 表示音频播放配置信息
			 */
			inline hiaudio_aoconf& get_ao_conf() {

				return m_ao_conf;
			}
			/**
			 * 表示音频播放配置信息
			 * 
			 * @param newVal
			 */
			inline void set_ao_conf(hiaudio_aoconf& newVal) {

				m_ao_conf = newVal;
			}
			/**
			 * 表示音频采集配置信息
			 */
			inline hiaudio_aiconf& get_ai_conf() {

				return m_ai_conf;
			}
			/**
			 * 表示音频采集配置信息
			 * 
			 * @param newVal
			 */
			inline void set_ai_conf(hiaudio_aiconf& newVal) {

				m_ai_conf = newVal;
			}

		private:
			/**
			 * 表示音频采集配置信息
			 */
			hiaudio_aiconf m_ai_conf;
			/**
			 * 表示音频播放配置信息
			 */
			hiaudio_aoconf m_ao_conf;

		};

	}

}
#endif // !defined(HIAUDIO_CONF_H_INCLUDED_)
