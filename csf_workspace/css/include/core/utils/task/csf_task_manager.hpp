/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 19-7月-2018 20:11:51
*
*Description: Class(csf_task_manager) 表示任务管理器
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_MANAGER_INCLUDED_)
#define CSF_TASK_MANAGER_INCLUDED_

#include "csf_module.hpp"
#include "csf_task.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * 表示任务管理器
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:51
				 */
				class csf_task_manager : public csf::core::module::csf_module
				{

				public:
					csf_task_manager();
					virtual ~csf_task_manager();

					/**
					 * 表示配置信息
					 */
					inline csf_configure_manager* get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示配置信息
					 * 
					 * @param newVal
					 */
					inline csf::core::base::csf_void set_configure_manager(const csf_configure_manager* newVal) {

						m_configure_manager = (csf_configure_manager*)newVal;
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
					/**
					 * 表示任务管理器的状态信息
					 */
					inline csf::core::utils::task::csf_task::csf_task_status get_status() {

						return m_status;
					}
					/**
					 * 表示任务管理器的状态信息
					 * 
					 * @param newVal
					 */
					inline void set_status(const csf::core::utils::task::csf_task::csf_task_status newVal) {

						m_status = newVal;
					}

				private:
					/**
					 * 表示配置信息
					 */
					csf_configure_manager* m_configure_manager = csf_null;
					/**
					 * 表示任务管理器的状态信息
					 */
					csf::core::utils::task::csf_task::csf_task_status m_status = csf::core::utils::task::csf_task::csf_task_status::csf_task_status_none;

				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_MANAGER_INCLUDED_)
