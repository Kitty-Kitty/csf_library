/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_factory_manager_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:38
*
*Description: Interface(csf_connect_factory_manager_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_MANAGER_INTERFACE_INCLUDED_)
#define CSF_CONNECT_FACTORY_MANAGER_INTERFACE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:38
				 */
				class csf_connect_factory_manager_interface
				{

				public:
					csf_connect_factory_manager_interface() {

					}

					virtual ~csf_connect_factory_manager_interface() {

					}

					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null) =0;
					/**
					 * 模块启动
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null) =0;
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_MANAGER_INTERFACE_INCLUDED_)
