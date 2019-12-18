/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hiaudio_aoconf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:46
*
*Description: Class(hiaudio_aoconf) 表示音频播放配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HIAUDIO_AOCONF_H_INCLUDED_)
#define HIAUDIO_AOCONF_H_INCLUDED_

#include <iostream>

#include "hiaudio_common_conf.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示音频播放配置信息
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:31:46
		 */
		class hiaudio_aoconf : public ec::core::hiaudio_common_conf
		{

		public:
			hiaudio_aoconf();
			virtual ~hiaudio_aoconf();

		};

	}

}
#endif // !defined(HIAUDIO_AOCONF_H_INCLUDED_)
