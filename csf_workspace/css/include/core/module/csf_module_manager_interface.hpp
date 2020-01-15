/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_manager_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7月-2018 16:58:58
*
*Description: Interface(csf_module_manager_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_MANAGER_INTERFACE_INCLUDED_)
#define CSF_MODULE_MANAGER_INTERFACE_INCLUDED_

#include "csf_module.hpp"

using csf::core::module::csf_module;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示模块管理器接口
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7月-2018 16:58:58
			 */
			class csf_module_manager_interface
			{

			public:
				csf_module_manager_interface() {

				}

				virtual ~csf_module_manager_interface() {

				}

				/**
				 * 创建模块操作。
				 * 返回：非空表示创建的模块地址；空表示错误；
				 * 
				 * @param name    表示需要创建的模块名称
				 */
				virtual csf_module * create(const csf_string& name) =0;
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
				 * @param name    表示需要创建的模块名称
				 */
				virtual csf_module * create(const csf_char* name) =0;
				/**
				 * 创建模块操作。
				 * 返回：非空表示创建的模块地址；空表示错误；
				 * 
				 * @param type    表示需要创建的模块类型
				 */
				virtual csf_module * create(const csf_module::csf_module_type type) =0;

			};

		}

	}

}
#endif // !defined(CSF_MODULE_MANAGER_INTERFACE_INCLUDED_)
