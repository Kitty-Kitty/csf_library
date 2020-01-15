/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_vm_option.hpp
*
*Version: 1.0
*
*Date: 12-1月-2020 11:18:35
*
*Description: Class(csf_vm_option) 表示当前vm支持的操作指令
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_VM_OPTION_H_INCLUDED_)
#define CSF_VM_OPTION_H_INCLUDED_

#include "csf_vm.hpp"
#include "csf_app_option.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示当前vm支持的操作指令
			 * @author f
			 * @version 1.0
			 * @created 12-1月-2020 11:18:35
			 */
			class csf_vm_option : public csf::core::module::csf_app_option
			{

			public:
				/**
				 *
				 * @param vm    表示当前option对应的vm对象
				 */
				csf_vm_option(csf_vm& vm);
				virtual ~csf_vm_option();
				
				csf_vm& get_vm();

			private:
				/**
				 * 表示当前option作用的vm对象
				 */
				csf_vm& m_vm;

			};

		}

	}

}
#endif // !defined(CSF_VM_OPTION_H_INCLUDED_)
