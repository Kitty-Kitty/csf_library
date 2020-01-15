/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_windows_network.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:54
*
*Description: Class(csf_windows_network)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_WINDOWS_NETWORK_INCLUDED_)
#define CSF_WINDOWS_NETWORK_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_network.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace platform
			{
				/**
				 * 表示windows网络信息
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:54
				 */
				class csf_windows_network : public csf::core::system::platform::csf_network
				{

				public:
					csf_windows_network();
					virtual ~csf_windows_network();

					inline csf::core::system::csf_configure_manager get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 
					 * @param new_value
					 */
					inline csf::core::base::csf_void set_configure_manager(csf::core::system::csf_configure_manager new_value) {

						m_configure_manager = newVal;
					}
					/**
					 * 模块启动
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);

				};

			}

		}

	}

}
#endif // !defined(CSF_WINDOWS_NETWORK_INCLUDED_)
