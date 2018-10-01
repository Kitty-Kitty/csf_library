/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_factory_manager.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:37
*
*Description: Class(csf_connect_factory_manager) 表示连接工厂管理器
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
#define CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_

#include "csf_connect_factory_manager_interface.hpp"
#include "csf_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * 表示连接工厂管理器
				 * @author f
				 * @version 1.0
				 * @created 01-10月-2018 12:54:37
				 */
				class csf_connect_factory_manager : public csf::core::module::csf_manager, public csf::core::module::connect::csf_connect_factory_manager_interface
				{

				public:
					csf_connect_factory_manager();
					virtual ~csf_connect_factory_manager();

					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * 模块启动
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
