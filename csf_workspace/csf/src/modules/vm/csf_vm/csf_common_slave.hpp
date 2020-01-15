/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_common_slave.hpp
*
*Version: 1.0
*
*Date: 15-1月-2020 18:46:53
*
*Description: Class(csf_common_slave) 表示保存app运行时的信息描述对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_COMMON_SLAVE_H_INCLUDED_)
#define CSF_COMMON_SLAVE_H_INCLUDED_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/process.hpp>
#include "csf_slave.hpp"

namespace csf
{
	namespace modules
	{
		namespace vm
		{
			/**
			 * 表示保存app运行时的信息描述对象
			 * @author f
			 * @version 1.0
			 * @created 15-1月-2020 18:46:53
			 */
			class csf_common_slave : public csf::core::module::csf_slave
			{

			public:
				csf_common_slave();
				virtual ~csf_common_slave();

				/**
				 * 功能：
				 *    将slave信息转换为字符串
				 * 返回：
				 *    slave信息字符串
				 */
				virtual csf_string to_string();
				/**
				 * 功能：
				 *    表示进程退出时调用的函数
				 * 返回：
				 *    无
				 * 
				 * @param ec    表示错误码
				 * @param rc    表示进程退出后的返回码
				 */
				void exit_handler(boost::system::error_code ec, int rc);

			};

		}

	}

}
#endif // !defined(CSF_COMMON_SLAVE_H_INCLUDED_)
