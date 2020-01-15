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
*Date: 18-7月-2018 22:31:08
*
*Description: Class(csf_manager) 表示基础管理器
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MANAGER_INCLUDED_)
#define CSF_MANAGER_INCLUDED_

#include "csf_manager_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示基础管理器
			 * @author f
			 * @version 1.0
			 * @created 18-7月-2018 22:31:08
			 */
			class csf_manager : public csf::core::module::csf_manager_interface
			{

			public:
				inline explicit csf_manager()
					: m_configure_manager(csf_nullptr) {

				}
				inline virtual ~csf_manager() {

				}

				/**
				 * 根据配置管理器创建一个管理对象
				 * 
				 * @param configure_manager    表示配置管理器地址信息
				 */
				inline explicit csf_manager(const csf_configure_manager* configure_manager)
					: m_configure_manager((csf_configure_manager*)configure_manager) {

				}
				/**
				 * 表示基础管理器
				 */
				inline csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * 表示基础管理器
				 * 
				 * @param new_value
				 */
				inline void set_configure_manager(const csf_configure_manager* new_value) {

					m_configure_manager = (csf_configure_manager*)new_value;
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

			private:
				/**
				 * 表示基础管理器
				 */
				csf_configure_manager* m_configure_manager = csf_nullptr;

			};

		}

	}

}
#endif // !defined(CSF_MANAGER_INCLUDED_)
