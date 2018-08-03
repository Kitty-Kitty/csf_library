/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_manager_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 16:49:55
*
*Description: Interface(csf_manager_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MANAGER_INTERFACE_INCLUDED_)
#define CSF_MANAGER_INTERFACE_INCLUDED_

#include "csf_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示管理器的操作接口
			 * @author Administrator
			 * @version 1.0
			 * @created 01-7月-2018 16:49:55
			 */
			class csf_manager_interface : public csf::core::module::csf_interface
			{

			public:
				csf_manager_interface() {

				}

				virtual ~csf_manager_interface() {

				}

			};

		}

	}

}
#endif // !defined(CSF_MANAGER_INTERFACE_INCLUDED_)
