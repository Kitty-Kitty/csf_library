/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_configure_module.hpp
*
*Version: 1.0
*
*Date: 04-10月-2018 19:44:08
*
*Description: Class(csf_configure_module) 主要表示模块的配置及处理类定义
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONFIGURE_MODULE_H_INCLUDED_)
#define CSF_CONFIGURE_MODULE_H_INCLUDED_

#include "csf_module_manager.hpp"
#include "csf_element.hpp"
#include "csf_device_base.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * 主要表示模块的配置及处理类定义
			 * @author f
			 * @version 1.0
			 * @created 04-10月-2018 19:44:08
			 */
			class csf_configure_module
			{

			public:
				csf_configure_module();
				virtual ~csf_configure_module();

				/**
				* 主要功能是：通过配置信息创建一个基础模块对象
				* 返回：非null表示模块对象地址；null表示失败；
				*
				* @param module_manager    表示模块管理器对象信息
				* @param element    表示模块的配置信息。
				*
				* 模块配置信息结构如下：
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
				*
				*
				*/
				static csf::core::module::csf_device_base* create_module(csf::core::module::csf_module_manager& module_manager
					, csf::core::system::csf_element& element);

			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_MODULE_H_INCLUDED_)
