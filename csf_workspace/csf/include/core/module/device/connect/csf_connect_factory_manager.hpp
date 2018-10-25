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

#include "csf_connect.hpp"
#include "csf_connect_factory.hpp"
#include "csf_connect_factory_manager_interface.hpp"
#include "csf_manager.hpp"
#include "csf_app.hpp"

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
				class csf_connect_factory_manager : public csf::core::module::csf_manager
					, public csf::core::module::connect::csf_connect_factory_manager_interface
				{

				public:
					inline explicit csf_connect_factory_manager()
						: m_app(csf_nullptr) {

					}

					inline virtual ~csf_connect_factory_manager() {

					}
					/**
					* 根据配置管理器创建一个管理对象
					*
					* @param configure_manager    表示配置管理器地址信息
					*/
					inline explicit csf_connect_factory_manager(const csf_configure_manager* configure_manager)
						: csf_manager(configure_manager)
						, m_app(csf_nullptr) {

					}
					/**
					* 根据配置管理器创建一个管理对象
					*
					* @param configure_manager    表示配置管理器地址信息
					* @param app    表示该模块所属的app对象地址
					*/
					inline explicit csf_connect_factory_manager(const csf_configure_manager* configure_manager
						, const csf_app* app)
						: csf_manager(configure_manager)
						, m_app((csf_app*)app) {

					}
					/**
					* 主要功能是：初始化模块管理器
					* 返回：0表示成功；非0表示失败；
					*
					* @param conf_mg    表示配置文件信息
					* @param app    表示该模块所属的app对象地址
					*/
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg, const csf_app* app);
					/**
					* 主要功能是：启动模块管理器
					* 返回：0表示成功；非0表示失败；
					*
					* @param conf_mg    表示配置文件信息
					* @param app    表示该模块所属的app对象地址
					*/
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg, const csf_app* app);
					/**
					* 主要功能是：停止模块管理器
					* 返回：0表示成功；非0表示失败；
					*
					* @param conf_mg    表示配置文件信息
					*/
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					* 主要功能是：创建所有的连接工厂类对象
					* 返回：0表示成功；非0表示失败；
					*
					* @param app    表示所属的app信息
					* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
					*/
					csf_bool create_connect_factories(csf_app& app, csf_configure_manager& configure_manager);
					/**
					* 主要功能是：创建一个连接工厂类对象
					* 返回：0表示成功；非0表示失败；
					*
					* @param app    表示所属的app信息
					* @param element    表示当前的device节点内容
					*/
					csf_bool create_connect_factory(csf_app& app, csf_element& element);
					/**
					* 主要功能是：启动网络连接工厂对象
					* 返回：0表示成功；非0表示失败；
					*
					* @param connect_factory    表示网络连接工厂对象
					*/
					csf_bool start_connect_factory(csf_connect_factory* connect_factory);
					/**
					* 主要功能是：创建该连接工厂对象所包含的所有网络连接对象
					* 返回：0表示成功；非0表示失败；
					*
					* @param app    表示所属的app信息
					* @param factory    表示当前处理的连接工厂类对象
					* @param element    表示当前的device节点内容
					*/
					csf_bool create_listen_list(csf_app& app, csf_connect_factory& factory, csf_element& element);
					/**
					* 主要功能是：创建一个连接类对象
					* 返回：0表示成功；非0表示失败
					*
					* @param app    表示所属的app信息
					* @param factory    表示当前处理的连接工厂类对象
					* @param element    表示当前的device节点内容
					*/
					csf_bool create_listen(csf_app& app, csf_connect_factory& factory, csf_element& element);
					/**
					* 表示该模块所属的app对象地址
					*/
					inline csf_app* get_app() {

						return m_app;
					}
					/**
					* 表示该模块所属的app对象地址
					*
					* @param newVal
					*/
					inline void set_app(const csf_app* newVal) {

						m_app = (csf_app*)newVal;
					}
					/**
					* 表示连接工厂管理器保存的对象列表
					*/
					inline csf_unordered_map<csf_string, csf_connect_factory*>& get_factories() {

						return m_factories;
					}
					/**
					* 表示通过配置文件创建的连接对象保存的对象列表
					*/
					inline csf_unordered_map<csf_string, csf_connect_ptr>& get_connectes() {

						return m_connectes;
					}
					/**
					* 表示注册需要使用的处理句柄
					*/
					inline csf_unordered_map<csf_string, csf_connect_callback>& get_handles() {

						return m_handles;
					}
					/**
					* 主要功能是：向连接工厂列表中添加一个连接工厂类对象
					* 返回：true表示成功；false表示失败；
					*
					* @param name    表示连接工厂类对象名称
					* @param factory    表示连接工厂类对象指针
					*/
					inline csf_bool add_factory(csf_string name, csf_connect_factory* factory) {

						get_factories()[name] = factory;

						return csf_true;
					}
					/**
					* 主要功能是：根据名称从连接工厂列表中查找一个连接工厂类对象
					* 返回：非null表示成功；null表示失败；
					*
					* @param name    表示连接工厂类对象名称
					*/
					inline csf_connect_factory* find_factory(csf_string name) {

						csf_unordered_map<csf_string, csf_connect_factory*>::iterator tmp_iter;


						tmp_iter = get_factories().find(name);
						if (tmp_iter == get_factories().end()) {
							return csf_nullptr;
						}
						else {
							return tmp_iter->second;
						}
						return  csf_nullptr;
					}
					/**
					* 主要功能是：根据名称从连接工厂列表中删除一个连接工厂类对象
					* 返回：true表示成功；false表示失败；
					*
					* @param name    表示连接工厂类对象名称
					*/
					inline csf_bool remove_factory(csf_string name) {

						csf_connect_factory			*tmp_factory = csf_nullptr;
						csf_unordered_map<csf_string, csf_connect_factory*>::iterator tmp_iter;


						tmp_iter = get_factories().find(name);
						if (tmp_iter == get_factories().end()) {
							return csf_false;
						}
						else {
							tmp_factory = tmp_iter->second;
							get_factories().erase(tmp_iter);
							get_app()->get_module_manager().destory(tmp_factory);
						}
							
						return csf_true;
					}
					/**
					* 主要功能是：从连接工厂列表中删除所有连接工厂类对象
					* 返回：true表示成功；false表示失败；
					*/
					inline csf_bool clear_factory() {

						for (auto tmp_iter : get_factories()) {
							if (csf_nullptr != tmp_iter.second) {
								get_app()->get_module_manager().destory(tmp_iter.second);
							}
						}

						get_factories().clear();

						return csf_true;
					}
					/**
					* 主要功能是：创建一个连接类对象
					* 返回：非m_null_connect_ptr表示成功；m_null_connect_ptr表示失败
					*
					* @param factory    表示当前处理的连接工厂类对象
					* @param element    表示需要创建的连接对象配置信息
					*/
					csf_connect_ptr create_connect(csf_connect_factory& factory, csf_element& element);
					/**
					* 主要功能是：表示监听一个连接类对象
					* 返回：0表示成功；非0表示失败错误码
					*
					* @param connect    表示当前处理的连接工厂类对象
					* @param handle    表示连接对象的回调句柄
					* @param element    表示需要创建的连接对象配置信息
					*/
					csf::core::base::csf_int32 listen_connect(csf_connect_ptr& connect
						, csf_connect_callback handle
						, csf_element& element);
					/**
					* 主要功能是：向连接列表中添加一个连接类对象
					* 返回：true表示成功；false表示失败；
					*
					* @param name    表示连接类对象名称
					* @param connect_ptr    表示连接类对象指针
					*/
					inline csf_bool add_connect(csf_string name, csf_connect_ptr connect_ptr) {

						get_connectes()[name] = connect_ptr;

						return csf_true;
					}
					/**
					* 主要功能是：根据名称从连接列表中查找一个连接类对象
					* 返回：非null表示成功；null表示失败；
					*
					* @param name    表示连接类对象名称
					*/
					inline csf_connect_ptr find_connect(csf_string name) {

						csf_unordered_map<csf_string, csf_connect_ptr>::iterator tmp_iter;


						tmp_iter = get_connectes().find(name);
						if (tmp_iter == get_connectes().end()) {
							return m_null_connect_ptr;
						}
						else {
							return tmp_iter->second;
						}
						return m_null_connect_ptr;
					}
					/**
					* 主要功能是：根据名称从连接列表中删除一个连接类对象
					* 返回：true表示成功；false表示失败；
					*
					* @param name    表示连接类对象名称
					*/
					inline csf_bool remove_connect(csf_string name) {

						csf_unordered_map<csf_string, csf_connect_ptr>::iterator tmp_iter;


						tmp_iter = get_connectes().find(name);
						if (tmp_iter == get_connectes().end()) {
							return csf_false;
						}
						else {
							get_connectes().erase(tmp_iter);
						}

						return csf_true;
					}
					/**
					* 主要功能是：从连接列表中删除所有连接类对象
					* 返回：true表示成功；false表示失败；
					*/
					inline csf_bool clear_connect() {

						get_connectes().clear();

						return csf_true;
					}
					/**
					* 主要功能是：向句柄列表中添加一个句柄
					* 返回：true表示成功；false表示失败；
					*
					* @param name    表示句柄名称
					* @param handle    表示句柄指针
					*/
					inline csf_bool add_handle(csf_string name, csf_connect_callback handle) {

						get_handles()[name] = handle;

						return csf_true;
					}
					/**
					* 主要功能是：根据名称从句柄列表中查找一个句柄
					* 返回：非null表示成功；null表示失败；
					*
					* @param name    表示句柄名称
					*/
					inline csf_connect_callback find_handle(csf_string name) {


						csf_unordered_map<csf_string, csf_connect_callback>::iterator tmp_iter;


						tmp_iter = get_handles().find(name);
						if (tmp_iter == get_handles().end()) {
							return csf_nullptr;
						}
						else {
							return tmp_iter->second;
						}

						return  csf_nullptr;
					}
					/**
					* 主要功能是：根据名称从句柄列表中删除一个句柄
					* 返回：true表示成功；false表示失败；
					*
					* @param name    表示句柄名称
					*/
					inline csf_bool remove_handle(csf_string name) {

						csf_unordered_map<csf_string, csf_connect_callback>::iterator tmp_iter;


						tmp_iter = get_handles().find(name);
						if (tmp_iter == get_handles().end()) {
							return csf_false;
						}
						else {
							get_handles().erase(tmp_iter);
						}

						return csf_true;
					}
					/**
					* 主要功能是：从句柄列表中删除所有句柄
					* 返回：true表示成功；false表示失败；
					*/
					inline csf_bool clear_handle() {

						get_handles().clear();

						return csf_true;
					}
				private:
					/**
					* 表示该模块所属的app对象地址
					*/
					csf_app* m_app = csf_nullptr;
					/**
					* 表示连接工厂管理器保存的对象列表
					*/
					csf_unordered_map<csf_string, csf_connect_factory*> m_factories;
					/**
					* 表示通过配置文件创建的连接对象保存的对象列表
					*/
					csf_unordered_map<csf_string, csf_connect_ptr> m_connectes;
					/**
					* 表示注册需要使用的处理句柄
					*/
					csf_unordered_map<csf_string, csf_connect_callback> m_handles;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
