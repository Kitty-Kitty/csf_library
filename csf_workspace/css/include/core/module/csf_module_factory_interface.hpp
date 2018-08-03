/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7月-2018 16:49:58
*
*Description: Interface(csf_module_factory_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_FACTORY_INTERFACE_INCLUDED_)
#define CSF_MODULE_FACTORY_INTERFACE_INCLUDED_

#include "csf_interface.hpp"
#include "csf_module.hpp"

using namespace csf::core::module;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示模块创建工厂的操作接口
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7月-2018 16:49:58
			 */
			class csf_module_factory_interface : public csf::core::module::csf_interface
			{

			public:
				csf_module_factory_interface() {

				}

				virtual ~csf_module_factory_interface() {

				}

				/**
				 * 销毁模块操作。
				 * 返回：0表示正确；<0表示错误码；
				 * 
				 * @param module    表示需要销毁的模块地址
				 */
				virtual csf_int32 destory(const csf_module * module) =0;
				/**
				 * 创建模块操作。
				 * 返回：非空表示创建的模块地址；空表示错误；
				 * 
				 * @param configure_manager    表示模块的配置项信息
				 */
				virtual csf_module * create(const csf_configure_manager * configure_manager) =0;

			};

		}

	}

}
#endif // !defined(CSF_MODULE_FACTORY_INTERFACE_INCLUDED_)
