/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_filter_manager.hpp
*
*Version: 1.0
*
*Date: 28-3月-2019 14:56:49
*
*Description: Class(csf_filter_manager) 主要管理多种不同类型的数据过滤器。可以解决同一个业务请求中的不同应用协议或数据内容。
这是在生成csf_request前的数据合法性校验处理。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_FILTER_MANAGER_H_INCLUDED_)
#define CSF_FILTER_MANAGER_H_INCLUDED_

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
				 * 主要管理多种不同类型的数据过滤器。可以解决同一个业务请求中的不同应用协议或数据内容。
				 * 这是在生成csf_request前的数据合法性校验处理。
				 * @author fangzhenmu
				 * @version 1.0
				 * @created 28-3月-2019 14:56:49
				 */
				class csf_filter_manager : public csf::core::module::csf_manager
				{

				public:
					csf_filter_manager();
					virtual ~csf_filter_manager();

					/**
					 * 根据配置管理器创建一个管理对象
					 *
					 * @param configure_manager    表示配置管理器地址信息
					 */
					inline explicit csf_filter_manager(const csf_configure_manager* configure_manager) {

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

}
#endif // !defined(CSF_FILTER_MANAGER_H_INCLUDED_)
