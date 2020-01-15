/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hiconfigure.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:47
*
*Description: Class(hiconfigure) 表示海思平台需要的配置信息,也包含模块等信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HICONFIGURE_H_INCLUDED_)
#define HICONFIGURE_H_INCLUDED_

#include <iostream>

#include "hivideo_conf.hpp"
#include "hisys_conf.hpp"
#include "hiaudio_conf.hpp"

namespace ec
{
	namespace core
	{
		class csf_module;
		/**
		 * 表示海思平台需要的配置信息,也包含模块等信息
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:31:47
		 */
		class hiconfigure
		{

		public:
			hiconfigure();
			virtual ~hiconfigure();

			/**
			 * 模块设备对象地址
			 */
			inline csf_module* get_module() {

				return m_module;
			}
			/**
			 * 模块设备对象地址
			 * 
			 * @param newVal
			 */
			inline void set_module(csf_module* newVal) {

				m_module = newVal;
			}
			/**
			 * 表示海思的系统配置信息
			 */
			inline hisys_conf& get_sys_conf() {

				return m_sys_conf;
			}
			/**
			 * 表示海思的系统配置信息
			 * 
			 * @param newVal
			 */
			inline void set_sys_conf(hisys_conf& newVal) {

				m_sys_conf = newVal;
			}
			/**
			 * 表示海思音频配置信息
			 */
			inline hiaudio_conf& get_audio_conf() {

				return m_audio_conf;
			}
			/**
			 * 表示海思音频配置信息
			 * 
			 * @param newVal
			 */
			inline void set_audio_conf(hiaudio_conf& newVal) {

				m_audio_conf = newVal;
			}
			/**
			 * 表示海思视频配置信息
			 */
			inline hivideo_conf& get_video_conf() {

				return m_video_conf;
			}
			/**
			 * 表示海思视频配置信息
			 * 
			 * @param newVal
			 */
			inline void set_video_conf(hivideo_conf& newVal) {

				m_video_conf = newVal;
			}

		private:
			/**
			 * 模块设备对象地址
			 */
			csf_module* m_module = NULL;
			/**
			 * 表示海思的系统配置信息
			 */
			hisys_conf m_sys_conf;
			/**
			 * 表示海思音频配置信息
			 */
			hiaudio_conf m_audio_conf;
			/**
			 * 表示海思视频配置信息
			 */
			hivideo_conf m_video_conf;

		};

	}

}
#endif // !defined(HICONFIGURE_H_INCLUDED_)
