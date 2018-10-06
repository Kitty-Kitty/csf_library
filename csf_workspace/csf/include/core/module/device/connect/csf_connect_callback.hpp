/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_callback.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:37
*
*Description: Class(csf_connect_callback) 表示连接的返回函数
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_CALLBACK_H_INCLUDED_)
#define CSF_CONNECT_CALLBACK_H_INCLUDED_

#include "csf_base_include.h"
#include "csf_stdbind.hpp"
#include "csf_connect_error.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				* 表示定义一个网络连接类
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10月-2018 12:54:36
				*/
				class csf_connect;
				/**
				* 表示定义一个网络连接工厂类
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10月-2018 12:54:36
				*/
				class csf_connect_factory;
				/**
				* 表示定义一个网络连接工厂类管理器
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10月-2018 12:54:36
				*/
				class csf_connect_factory_manager;
				/**
				* 表示定义一个网络连接智能指针
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10月-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_connect>				csf_connect_ptr;
				/**
				* 表示定义一个网络连接工厂类智能指针
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10月-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_connect_factory>		csf_connect_factory_ptr;
				/**
				 * 表示连接的返回函数
				 * @author f
				 * @version 1.0
				 * @created 01-10月-2018 12:54:37
				 */
				typedef csf_function<csf_int32(const csf_connect*, const csf_connect_error&)> 	csf_connect_callback;

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_CALLBACK_H_INCLUDED_)
