/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 16:49:53
*
*Description: Interface(csf_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_INTERFACE_INCLUDED_)
#define CSF_INTERFACE_INCLUDED_

#include "csf_typedef.h"
#include "csf_configure_manager.hpp"

using namespace csf::core::base;
using namespace csf::core::system;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示cf的专用操作接口
			 * @author fz
			 * @version 1.0
			 * @created 01-7月-2018 16:49:53
			 */
			class csf_interface
			{

			public:
				csf_interface() {

				}

				virtual ~csf_interface() {

				}

				/**
				 * 模块初始化
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr) =0;
				/**
				 * 模块启动
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr) =0;
				/**
				 * 模块停止
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr) =0;

			};

		}

	}

}
#endif // !defined(CSF_INTERFACE_INCLUDED_)
