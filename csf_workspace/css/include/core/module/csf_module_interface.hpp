/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:46
*
*Description: Interface(csf_module_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_INTERFACE_INCLUDED_)
#define CSF_MODULE_INTERFACE_INCLUDED_

#include "csf_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示模块的接口
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 27-6月-2018 17:28:46
			 */
			class csf_module_interface : public csf::core::module::csf_interface
			{

			public:
				csf_module_interface() {

				}

				virtual ~csf_module_interface() {

				}

			};

		}

	}

}
#endif // !defined(CSF_MODULE_INTERFACE_INCLUDED_)
