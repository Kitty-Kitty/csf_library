/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hiaudio_aiconf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:46
*
*Description: Class(hiaudio_aiconf) 表示音频采集所需要的配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HIAUDIO_AICONF_H_INCLUDED_)
#define HIAUDIO_AICONF_H_INCLUDED_

#include <iostream>

#include "hiaudio_common_conf.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示音频采集所需要的配置信息
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:31:46
		 */
		class hiaudio_aiconf : public ec::core::hiaudio_common_conf
		{

		public:
			hiaudio_aiconf();
			virtual ~hiaudio_aiconf();

		};

	}

}
#endif // !defined(HIAUDIO_AICONF_H_INCLUDED_)
