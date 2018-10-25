/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_device_configure_interface.hpp
*
*Version: 1.0
*
*Date: 04-10月-2018 21:15:02
*
*Description: Interface(csf_device_configure_interface) 表示设备的配置操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DEVICE_CONFIGURE_INTERFACE_H_INCLUDED_)
#define CSF_DEVICE_CONFIGURE_INTERFACE_H_INCLUDED_

#include "csf_base_include.h"
#include "csf_element.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示设备的配置操作接口
			 * @author f
			 * @version 1.0
			 * @created 04-10月-2018 21:15:02
			 */
			class csf_device_configure_interface
			{

			public:
				csf_device_configure_interface() {

				}

				virtual ~csf_device_configure_interface() {

				}

				/**
				* 主要功能是：主要实现模块的配置信息处理接口。
				* 返回：0表示成功；非0表示失败；
				*
				* @param element    表示模块的配置信息
				*
				* 常用的配置信息保存结构为：
				* <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
				* <module>
				*        <!--***表示模块对应的模块名称信息***-->
				*        <name>csf_connection</name>
				*        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
				*        <mid>02000000-0000001</mid>
				*        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
				*        <configure>
				*                <!--表示线程数量-->
				*                <thread_number>4</thread_number>
				*        </configure>
				* </module>
				*/
				virtual csf_int32 configure(const csf::core::system::csf_element& element) = 0;

			};

		}

	}

}
#endif // !defined(CSF_DEVICE_CONFIGURE_INTERFACE_H_INCLUDED_)
