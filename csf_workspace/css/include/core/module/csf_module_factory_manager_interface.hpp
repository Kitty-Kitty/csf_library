/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory_manager_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:46
*
*Description: Interface(csf_module_factory_manager_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_FACTORY_MANAGER_INTERFACE_INCLUDED_)
#define CSF_MODULE_FACTORY_MANAGER_INTERFACE_INCLUDED_

#include "csf_module_manager_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示模块工厂管理器操作接口内容
			 * @author fz
			 * @version 1.0
			 * @created 27-6月-2018 17:28:46
			 */
			class csf_module_factory_manager_interface : public csf::core::module::csf_module_manager_interface
			{

			public:
				csf_module_factory_manager_interface() {

				}

				virtual ~csf_module_factory_manager_interface() {

				}

			};

		}

	}

}
#endif // !defined(CSF_MODULE_FACTORY_MANAGER_INTERFACE_INCLUDED_)
