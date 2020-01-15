/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hivideo_conf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:48
*
*Description: Class(hivideo_conf) 表示海思视频配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HIVIDEO_CONF_H_INCLUDED_)
#define HIVIDEO_CONF_H_INCLUDED_

#include <iostream>
#include <map>

#include "hivideo_channel_conf.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示海思视频配置信息
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:31:48
		 */
		class hivideo_conf
		{

		public:
			hivideo_conf();
			virtual ~hivideo_conf();
			/**
			* 功能：
			*    根据名称查找对应的视频配置信息
			* 返回：
			*    如果存在需要的视频配置，则返回对象
			*    如果不存在，则返回空
			*
			* @param name    表示当前视频配置名称
			*/
			inline hivideo_channel_conf* find(std::string name) {

				auto tmp_iter = get_configures().find(name);
				if (tmp_iter != get_configures().end()) {
					return tmp_iter->second;
				}

				return  csf_nullptr;
			}
			/**
			* 功能：
			*    添加对应的视频配置对象
			* 返回：
			*    无
			*
			* @param name    表示当前视频配置名称
			* @param conf    表示视频配置对象
			*/
			inline void add(std::string name, hivideo_channel_conf* conf) {
				get_configures().insert(std::make_pair(name, conf));
			}
			/**
			* 功能：
			*    删除名称查找对应的视频配置信息
			* 返回：
			*    无
			*
			* @param name    表示当前视频配置名称
			*/
			inline void del(std::string name) {
				get_configures().erase(name);
			}
			/**
			* 功能：
			*    表示清除所有的视频配置对象
			* 返回：
			*    无
			*/
			inline void clear() {
				for (auto tmp_iter:get_configures()) {
					if (tmp_iter.second) {
						delete tmp_iter.second;
					}
				}
				get_configures().clear();
			}
		private:
			/**
			* 表示视频通道相关的配置信息
			*/
			inline std::map<std::string, hivideo_channel_conf*>& get_configures() {

				return m_configures;
			}
		private:
			/**
			* 表示视频通道相关的配置信息
			*/
			std::map<std::string, hivideo_channel_conf*> m_configures;

		};

	}

}
#endif // !defined(HIVIDEO_CONF_H_INCLUDED_)
