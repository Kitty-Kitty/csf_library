/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_divider_manager.hpp
*
*Version: 1.0
*
*Date: 28-3月-2019 14:56:49
*
*Description: Class(csf_divider_manager) 服务请求分配管理器，用于管理各种特定的分配器。满足各种不同业务的处理。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DIVIDER_MANAGER_H_INCLUDED_)
#define CSF_DIVIDER_MANAGER_H_INCLUDED_

#include "csf_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace service
		{
			/**
			 * 服务请求分配管理器，用于管理各种特定的分配器。满足各种不同业务的处理。
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 28-3月-2019 14:56:49
			 */
			class csf_divider_manager : public csf::core::module::csf_manager
			{

			public:
				csf_divider_manager();
				virtual ~csf_divider_manager();

				/**
				 * 根据配置管理器创建一个管理对象
				 * 
				 * @param configure_manager    表示配置管理器地址信息
				 */
				inline explicit csf_divider_manager(const csf_configure_manager* configure_manager) {

				}
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
#endif // !defined(CSF_DIVIDER_MANAGER_H_INCLUDED_)
