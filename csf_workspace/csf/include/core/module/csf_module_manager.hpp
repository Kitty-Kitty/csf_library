/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_manager.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7月-2018 19:12:21
*
*Description: Class(csf_module_manager)表示模块管理器内容
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_MANAGER_INCLUDED_)
#define CSF_MODULE_MANAGER_INCLUDED_

#include <set>
#include "csf_module_manager_interface.hpp"
#include "csf_manager.hpp"
#include "csf_module_factory_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示模块管理器内容
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7月-2018 19:12:21
			 */
			class csf_module_manager : public csf::core::module::csf_manager, public csf::core::module::csf_module_manager_interface
			{

			public:
				inline explicit csf_module_manager()
					: m_module_factory_manager(csf_nullptr, this) {

				}

				inline virtual ~csf_module_manager() {
					clear();
				}

				/**
				* 根据配置信息创建对象。
				*
				* @param conf_mg    表示配置项信息
				*/
				inline explicit csf_module_manager(const csf_configure_manager * configure_manager)
					: csf_manager(configure_manager)
					, m_module_factory_manager(configure_manager, this) {

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
				inline virtual csf_module * create(const csf_string& name) {

					csf_module						*tmp_module = csf_nullptr;


					tmp_module = get_module_factory_manager().create(name);
					if (tmp_module) {
						add(tmp_module);
					}
					return tmp_module;
				}
				/**
				 * 销毁模块操作。
				 * 返回：0表示正确；<0表示错误码；
				 *
				 * @param module    表示需要销毁的模块地址
				 */
				inline virtual csf_int32 destroy(const csf_module * module) {

					csf_int32					tmp_int_ret = csf_failure;


					tmp_int_ret = get_module_factory_manager().destroy(module);
					if (csf_succeed == tmp_int_ret) {
						del(module);
					}
					return tmp_int_ret;
				}
				/**
				 * 创建模块操作。
				 * 返回：非空表示创建的模块地址；空表示错误；
				 *
				 * @param name    表示需要创建的模块名称
				 */
				inline virtual csf_module * create(const csf_char* name) {

					if (!name || csf_strlen(name)) {
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
				inline virtual csf_module * create(const csf_module::csf_module_type type) {
					csf_module						*tmp_module = csf_nullptr;


					tmp_module = get_module_factory_manager().create(type);
					if (tmp_module) {
						add(tmp_module);
					}
					return tmp_module;
				}
				/**
				* 功能：清空模块对象列表中的所有模块对象
				*/
				csf_void clear();
			protected:
				/**
				* 模块管理器中包含一个模块工厂管理器
				*/
				inline csf::core::module::csf_module_factory_manager& get_module_factory_manager() {

					return m_module_factory_manager;
				}
				/**
				* 表示用于保存所用通过模块管理器创建的模块对象
				*/
				inline csf_set<csf_module*>& get_modules() {

					return m_modules;
				}
				/**
				* 功能：添加一个已经创建的模块对象到模块对象列表
				* 返回：true表示成功；false表示失败；
				*
				* @param module    表示模块对象
				*/
				inline csf_bool add(const csf_module* module) {

					csf_unqiue_lock<decltype(m_mutex)>			tmp_lock(m_mutex);

					get_modules().insert((csf_module*)module);

					return csf_true;
				}
				/**
				* 功能：从模块对象列表中删除模块对象
				* 返回：true表示成功；false表示失败；
				*
				* @param module    表示模块对象
				*/
				inline csf_bool del(const csf_module* module) {

					csf_set<csf_module*>::iterator				tmp_iter;


					csf_unqiue_lock<decltype(m_mutex)>			tmp_lock(m_mutex);

					tmp_iter = get_modules().find((csf_module*)module);
					if (tmp_iter != get_modules().end()) {
						get_modules().erase(tmp_iter);
					}

					return csf_true;
				}

			private:
				/**
				* 模块管理器中包含一个模块工厂管理器
				*/
				csf::core::module::csf_module_factory_manager m_module_factory_manager;
				/**
				* 表示线程安全使用的互斥锁内容
				*/
				csf_shared_mutex m_mutex;
				/**
				* 表示用于保存所用通过模块管理器创建的模块对象
				*/
				csf_set<csf_module*> m_modules;
			};

		}

	}

}
#endif // !defined(CSF_MODULE_MANAGER_INCLUDED_)
