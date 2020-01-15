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
			#define CSF_CONFIGURE_STRING(str)				#str
			/**
			* 表示模块附加对象中保存的vm对象
			*/
			#define CSF_VM_OBJECT							CSF_CONFIGURE_STRING(csf_vm)
			/**
			* 表示模块附加对象中保存的app对象
			*/
			#define CSF_APP_OBJECT							CSF_CONFIGURE_STRING(csf_app)
			/**
			* 申明一个类型，解决编译错误
			*/
			class csf_configure_supply;
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
					return csf_succeed;
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
					return csf_succeed;
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
				/**
				* 表示配置管理器在运行时附加的对象，以满足部分特殊模块的配置需求。
				*/
				inline csf_unordered_map<csf_string, csf_void*>& get_addition_objects() {

					return m_addition_objects;
				}
				/**
				* 表示配置管理器在运行时附加的配置信息，以满足部分特殊模块的配置需求。
				*/
				inline csf_unordered_map<csf_string, csf_element>& get_addition_element() {

					return m_addition_element;
				}
				/**
				* 表示模块的补充配置信息。该类主要解决csf_configure_manager的信息不易扩展的问题。
				* csf_configure_manager主要保存配置文件信息，没有保存程序运行时的配置信息，当需要传输运行时的参数时，可能有三种处理方式：
				* 1、扩展csf_configure_manager类，生成独立配置对象
				* 2、保持csf_configure_manager一致，可以使用csf_configure_supply扩展对象的方式进行。
				* 3、将需要的运行时对象附加到csf_configure_manager的附加对象列表中，使用时查找。
				*/
				inline csf_configure_supply* get_supply() {

					return m_supply;
				}
				/**
				* 表示模块的补充配置信息。该类主要解决csf_configure_manager的信息不易扩展的问题。
				* csf_configure_manager主要保存配置文件信息，没有保存程序运行时的配置信息，当需要传输运行时的参数时，可能有三种处理方式：
				* 1、扩展csf_configure_manager类，生成独立配置对象
				* 2、保持csf_configure_manager一致，可以使用csf_configure_supply扩展对象的方式进行。
				* 3、将需要的运行时对象附加到csf_configure_manager的附加对象列表中，使用时查找。
				*
				* @param new_value
				*/
				inline void set_supply(csf_configure_supply* new_value) {

					m_supply = new_value;
				}
				/**
				* 表示附加对象列表中保存的vm对象指针。即，addition_objects中促成的key为csf_vm的对象。
				*/
				inline csf_void* get_vm_object() {

					csf_unordered_map<csf_string, csf_void*>::iterator		tmp_iter;


					tmp_iter = get_addition_objects().find(CSF_VM_OBJECT);
					if (tmp_iter != get_addition_objects().end()) {
						return tmp_iter->second;
					}

					return csf_nullptr;
				}
				/**
				* 表示附加对象列表中保存的vm对象指针。即，addition_objects中促成的key为csf_vm的对象。
				*
				* @param new_value
				*/
				inline void set_vm_object(csf_void* new_value) {

					get_addition_objects()[CSF_VM_OBJECT] = new_value;
				}
				/**
				* 表示附加对象列表中保存的app对象指针。即，addition_objects中促成的kdy为csf_app的对象。
				*/
				inline csf_void* get_app_object() {

					csf_unordered_map<csf_string, csf_void*>::iterator		tmp_iter;


					tmp_iter = get_addition_objects().find(CSF_APP_OBJECT);
					if (tmp_iter != get_addition_objects().end()) {
						return tmp_iter->second;
					}

					return csf_nullptr;
				}
				/**
				* 表示附加对象列表中保存的app对象指针。即，addition_objects中促成的kdy为csf_app的对象。
				*
				* @param new_value
				*/
				inline void set_app_object(csf_void* new_value) {

					get_addition_objects()[CSF_APP_OBJECT] = new_value;
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
				* 表示配置管理器在运行时附加的对象，以满足部分特殊模块的配置需求。
				*/
				csf_unordered_map<csf_string, csf_void*> m_addition_objects;
				/**
				* 表示配置管理器在运行时附加的配置信息，以满足部分特殊模块的配置需求。
				*/
				csf_unordered_map<csf_string, csf_element> m_addition_element;
				/**
				 * 表示性能限制配置信息
				 */
				csf::core::system::csf_measure_configure m_measure_configure;
				/**
				* 表示模块的补充配置信息。该类主要解决csf_configure_manager的信息不易扩展的问题。
				* csf_configure_manager主要保存配置文件信息，没有保存程序运行时的配置信息，当需要传输运行时的参数时，可能有三种处理方式：
				* 1、扩展csf_configure_manager类，生成独立配置对象
				* 2、保持csf_configure_manager一致，可以使用csf_configure_supply扩展对象的方式进行。
				* 3、将需要的运行时对象附加到csf_configure_manager的附加对象列表中，使用时查找。
				*
				*/
				csf::core::system::csf_configure_supply *m_supply = csf_nullptr;

			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_MANAGER_INCLUDED_)
