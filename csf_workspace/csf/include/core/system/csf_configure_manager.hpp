/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 17:41:45
*
*Description: Class(csf_configure_manager)表示系统所有配置的管理器
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONFIGURE_MANAGER_INCLUDED_)
#define CSF_CONFIGURE_MANAGER_INCLUDED_

#include "csf_measure_configure.hpp"
#include "csf_module_configure.hpp"
#include "csf_configure.hpp"

using namespace csf::core::module;

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			* 表示模块配置文件字符串定义
			*/
			#define CSF_CONFIGURE_STRING(str)									#str
			/**
			 * 表示系统所有配置的管理器
			 * @author fz
			 * @version 1.0
			 * @created 01-7月-2018 17:41:45
			 */
			class csf_configure_manager
			{

			public:
				csf_configure_manager();
				virtual ~csf_configure_manager();
				/**
				* 功能：初始化配置管理器中的其他配置信息，主要指模块配置信息，负载配置信息部分内容
				* 返回：true表示初始化成功；false表示初始化失败
				*/
				csf_bool init();
				/**
				 * 添加一个csf_configure到configure_manager中。由于configure_manager在添加的时候需要根据name来判断该配置文件是否
				 * 已经在configure_manager中。
				 * 其中返回0表示成功；其他表示失败。
				 *
				 * @param configure    表示需要被添加的csf_configure对象
				 */
				inline csf_int32 add(const csf_configure& configure) {

					if (((csf_configure&)configure).get_configure_file().get_name().empty()) {
						return csf_failure;
					}

					//将csf_configure添加到列表中
					m_configures[((csf_configure&)configure).get_configure_file().get_name()] = configure;
					return csf_success;
				}
				/**
				 * 添加一个csf_configure_file到configure_manager中。由于configure_manager不保存configure_file未解
				 * 析的文件，所以这个csf_configure_file需要先创建一个csf_configure后才能添加到configure_manager中。
				 * 其中返回0表示成功；其他表示失败。
				 *
				 * @param configure_file    表示需要被添加的csf_configure_file对象。
				 */
				inline csf_int32 add(const csf_configure_file& configure_file) {

					if (((csf_configure_file&)configure_file).get_name().empty()) {
						return csf_failure;
					}

					return add(csf_configure((csf_configure_file&)configure_file));
				}
				/**
				 * 表示从configure_manager中删除一个csf_configure。这里的删除主要是根据配置文件的名称name属性删除。
				 * 其中返回0表示成功；其他表示失败。
				 *
				 * @param configure    表示需要被删除的csf_configure对象
				 */
				inline csf_int32 del(const csf_configure& configure) {

					return del(((csf_configure&)configure).get_configure_file());
				}
				/**
				 * 从configure_manager中删除csf_configure_file指定的配置文件。这里的删除主要是根据配置文件的名称name属性删除。
				 *
				 * 其中返回0表示成功；其他表示失败。
				 *
				 * @param configure_file    表示需要被删除一个csf_configure_file对象指定的配置文件。
				 */
				inline csf_int32 del(const csf_configure_file& configure_file) {

					if (((csf_configure_file&)configure_file).get_name().empty()) {
						return csf_failure;
					}

					//表示根据configure名称删除配置文件信息
					get_configures().erase(((csf_configure_file&)configure_file).get_name());
					return csf_success;
				}
				/**
				* 表示根据items属性路径查找一个element。
				* 返回：非null表示满足items所有路径的节点；null表示没有查找到满足路径的节点；
				*
				* @param items    items属性路径
				*/
				virtual const csf_element& find_element(const csf_list<csf_string>& items);
				/**
				* 表示系统限制配置项目内容
				*/
				inline csf::core::system::csf_measure_configure& get_measure_configure() {

					return m_measure_configure;
				}
				/**
				* 表示系统限制配置项目内容
				*
				* @param new_value
				*/
				inline void set_measure_configure(csf::core::system::csf_measure_configure& new_value) {

					m_measure_configure = new_value;
				}
				/**
				* 功能：根据模块名称查询模块配置信息
				* 返回：非空对象表示成功；非对象表示失败；
				*
				* @param name    表示模块的名称
				*/
				const csf_module_configure& find_module_configure(const csf_string& name);
				/**
				* 功能：根据模块名称查询模块配置信息
				* 返回：非空对象表示成功；非对象表示失败；
				*
				* @param name    表示模块的名称
				*/
				inline const csf_module_configure& find_module_configure(const csf_char* name) {

					if (!name || csf_strlen(name)) {
						return csf_module_configure::get_null();
					}
					return find_module_configure(csf_string(name));
				}

			protected:
				/**
				* 功能：初始化模块配置管理器
				* 返回：true表示初始化成功；false表示初始化失败
				*
				* @param module_configures    表示处理后保存输出的模块配置信息
				* @param configures    表示当前已经解析的配置文件信息
				*/
				csf_bool init_module_configures(csf_map<csf_string, csf_module_configure>& module_configures
					, csf_map<csf_string, csf_configure>& configures);
				/**
				* 功能：初始化负载配置管理器
				* 返回：true表示初始化成功；false表示初始化失败
				*
				* @param measure_configure    表示处理后保存输出的模块配置信息
				* @param configures    表示当前已经解析的配置文件信息
				*/
				csf_bool init_measure_configure(csf_measure_configure& measure_configure
					, csf_map<csf_string, csf_configure>& configures);
				/**
				* 功能：向模块配置管理器中添加一个模块配置信息，同时遍历信息下的所有子模块信息
				* 返回：true表示初始化成功；false表示初始化失败
				*
				* @param module_configures    表示处理后保存输出的模块配置信息
				* @param module_element    表示当前获取到的模块信息
				*/
				csf_bool add_module_configures(csf_map<csf_string, csf_module_configure>& module_configures, const csf_element& module_element);
				/**
				* 功能：向模块配置管理器中添加一个模块配置信息
				* 返回：true表示初始化成功；false表示初始化失败
				*
				* @param module_configures    表示处理后保存输出的模块配置信息
				* @param module_element    表示当前获取到的模块信息
				*/
				csf_bool add_module_configure(csf_map<csf_string, csf_module_configure>& module_configures, const csf_element& module_element);
				/**
				* 功能：向模块配置管理器中添加一个模块配置信息，同时遍历信息下的所有子模块信息
				* 返回：true表示初始化成功；false表示初始化失败
				*
				* @param module_configures    表示处理后保存输出的模块配置信息
				* @param items    表示当前模块信息路径
				*/
				csf_bool add_module_configures(csf_map<csf_string, csf_module_configure>& module_configures, const csf_list<csf_string>& items);
				/**
				* 表示配置文件信息列表
				*/
				inline csf_map<csf_string, csf_configure>& get_configures() {

					return m_configures;
				}
				/**
				* 表示配置文件信息列表
				*
				* @param new_value
				*/
				inline csf_void set_configures(csf_map<csf_string, csf_configure>& new_value) {

					m_configures = new_value;
				}
				/**
				* 表示模块配置管理器
				*/
				inline csf_map<csf_string, csf_module_configure>& get_module_configures() {

					return m_module_configures;
				}
				/**
				* 表示模块配置管理器
				*
				* @param new_value
				*/
				inline csf_void set_module_configures(csf_map<csf_string, csf_module_configure>& new_value) {

					m_module_configures = new_value;
				}
			private:
				/**
				 * 表示配置文件信息列表
				 */
				csf_map<csf_string, csf_configure> m_configures;
				/**
				 * 表示模块配置管理器
				 */
				csf_map<csf_string, csf_module_configure> m_module_configures;
				/**
				 * 表示性能限制配置信息
				 */
				csf::core::system::csf_measure_configure m_measure_configure;
			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_MANAGER_INCLUDED_)
