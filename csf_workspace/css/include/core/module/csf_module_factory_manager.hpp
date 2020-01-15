/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 16:49:58
*
*Description: Class(csf_module_factory_manager)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_FACTORY_MANAGER_INCLUDED_)
#define CSF_MODULE_FACTORY_MANAGER_INCLUDED_


#include "csf_manager.hpp"
#include "csf_module_factory_manager_interface.hpp"
#include "csf_module_factory.hpp"


class csf_module_manager;


namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示模块创建工厂管理器
			 * @author fz
			 * @version 1.0
			 * @created 01-7月-2018 16:49:58
			 */
			class csf_module_factory_manager : public csf::core::module::csf_manager, public csf::core::module::csf_module_factory_manager_interface
			{

			public:
				inline explicit csf_module_factory_manager()
					: m_module_manager(csf_nullptr) {

				}
				inline virtual ~csf_module_factory_manager() {
					clear();
				}

				/**
				* 根据配置信息创建工厂管理器
				*
				* @param configure_manager    表示配置信息
				* @param module_manager    表示模块总管理器地址
				*/
				inline explicit csf_module_factory_manager(const csf_configure_manager * configure_manager
					, const csf_void* module_manager)

					: csf_manager(configure_manager)
					, m_module_manager((csf_module_manager*)module_manager) {

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
				/**
				* 创建模块操作。
				* 返回：非空表示创建的模块地址；空表示错误；
				*
				* @param name    表示需要创建的模块名称
				*/
				virtual csf_module * create(const csf_string& name);
				/**
				* 创建模块操作。
				* 返回：非空表示创建的模块地址；空表示错误；
				*
				* @param name    表示需要创建的模块名称
				*/
				inline virtual csf_module * create(const csf_char* name) {

					if (!name || csf_strlen(name) <= 0) {
						return csf_nullptr;
					}

					return create(csf_string(name));
				}
				/**
				 * 创建模块操作。
				 * 返回：非空表示创建的模块地址；空表示错误；
				 *
				 * @param type    表示需要创建的模块类型
				 */
				virtual csf_module * create(const csf_module::csf_module_type type);
				/**
				* 销毁模块操作。
				* 返回：0表示正确；<0表示错误码；
				*
				* @param module    表示需要销毁的模块地址
				*/
				virtual csf_int32 destory(const csf_module * module);
				/**
				* 表示模块工厂的存储列表
				*/
				inline csf_unordered_map<csf_string, csf_module_factory*>& get_module_factories() {

					return m_module_factories;
				}
				/**
				* 功能：根据模块名称查找模块工厂
				*
				* @param name    模块名称
				*/
				csf_module_factory* find(const csf_string& name);
				/**
				* 功能：根据模块名称查找模块工厂
				*
				* @param name    模块名称
				*/
				inline csf_module_factory* find(const csf_char* name) {

					if (!name || csf_strlen(name) <= 0) {
						return csf_nullptr;
					}
					return find(csf_string(name));
				}
				/**
				* 功能：根据模块类型查找模块工厂
				*
				* @param type    模块类型
				*/
				csf_module_factory* find(const csf_module::csf_module_type type);
				/**
				* 功能：销毁工厂管理器中的所有资源，主要是已经创建的模块工厂列表。
				*/
				csf_void clear();
			protected:
				/**
				* 功能：根据模块的名称创建一个模块工厂对象
				* 返回：非空表示成功；空表示失败；
				*
				* @param name    表示模块的名称
				*/
				csf_module_factory* create_module_factory(const csf_string& name);
				/**
				* 功能：根据模块的名称创建一个模块工厂对象
				* 返回：非空表示成功；空表示失败；
				*
				* @param name    表示模块的名称
				*/
				inline csf_module_factory* create_module_factory(const csf_char* name) {

					if (!name || csf_strlen(name) <= 0) {
						return csf_nullptr;
					}

					return create_module_factory(csf_string(name));
				}
				/**
				* 功能：根据模块的配置信息创建一个模块工厂对象
				* 返回：非空表示成功；空表示失败；
				*
				* @param module_configure    表示模块的配置信息
				*/
				inline csf_module_factory* create_module_factory(const csf_module_configure& module_configure) {

					return  create_module_factory(((csf_module_configure&)module_configure).get_name());
				}
			private:
				/**
				 * 表示模块工厂管理器所属的模块管理器
				 */
				csf_module_manager *m_module_manager = csf_nullptr;
				/**
				* 表示模块工厂的存储列表
				*/
				csf_unordered_map<csf_string, csf_module_factory*> m_module_factories;
				/**
				* 表示线程安全使用的互斥锁内容
				*/
				csf_shared_mutex m_mutex;
				/**
				* 表示模块工厂的存储列表
				*
				* @param newVal
				*/
				inline csf_void set_module_factories(csf_unordered_map<csf_string, csf_module_factory*>& newVal) {

					m_module_factories = newVal;
				}
			};

		}

	}

}
#endif // !defined(CSF_MODULE_FACTORY_MANAGER_INCLUDED_)
