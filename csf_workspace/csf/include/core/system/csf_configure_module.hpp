/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_configure_module.hpp
*
*Version: 1.0
*
*Date: 04-10月-2018 19:44:08
*
*Description: Class(csf_configure_module) 主要表示模块的配置及处理类定义
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONFIGURE_MODULE_H_INCLUDED_)
#define CSF_CONFIGURE_MODULE_H_INCLUDED_

#include "csf_module_manager.hpp"
#include "csf_element.hpp"
#include "csf_device_base.hpp"
#include "csf_app.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * 主要表示模块的配置及处理类定义
			 * @author f
			 * @version 1.0
			 * @created 04-10月-2018 19:44:08
			 */
			class csf_configure_module
			{

			public:
				csf_configure_module();
				virtual ~csf_configure_module();

				/**
				* 主要功能是：通过配置信息创建一个基础模块对象
				* 返回：非null表示模块对象地址；null表示失败；
				*
				* @param app    表示针对指定app创建模块对象
				* @param module_manager    表示模块管理器对象信息
				* @param element    表示模块的配置信息。
				*
				* 模块配置信息结构如下：
				* <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
				* <module>
				*        <!--***表示模块对应的模块名称信息***-->
				*        <name>csf_connection</name>
				*        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
				*        <mid>02000000-0000001</mid>
				*        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
				*        <configure>
				*                <!--表示线程数量-->
				*                <thread_number>4</thread_number>
				*        </configure>
				* </module>
				*
				*
				*/
				static csf::core::module::csf_device_base* create_module(
					csf_app* app
					, csf::core::module::csf_module_manager& module_manager
					, const csf::core::system::csf_element& element);
				/**
				* 主要功能是：
				*    由于boost.
				* log日志模块的处理问题，不支持dll和so模块输出，所以需要配置日志功能。在所有的device和device_io构造时，都需要执行该处理。如果后面更换了日志
				* 模块，则不需要该函数功能。
				*
				* 返回：
				*    true:表示配置成功；
				*    false:表示失败；
				*
				* @param configure_manager    表示配置文件内容
				*/
				inline static csf_bool init_logger(const csf_configure_manager * configure_manager) {

					csf_void				*tmp_app = csf_nullptr;

					
					if (!configure_manager) {
						return csf_false;
					}

					//获取app对象
					tmp_app = ((csf_configure_manager *)configure_manager)->get_app_object();
					if (!tmp_app) {
						return csf_false;
					}

					//判断是否为app对象类型
					if (!csf_device_base::is_app(((csf_device_base*)tmp_app)->get_type())) {
						return csf_false;
					}

					//初始化日志功能
					return init_logger((csf_app*)tmp_app);
				}
				/**
				* 主要功能是：
				*    由于boost.
				* log日志模块的处理问题，不支持dll和so模块输出，所以需要配置日志功能。在所有的device和device_io构造时，都需要执行该处理。如果后面更换了日志
				* 模块，则不需要该函数功能。
				*
				* 返回：
				*    true:表示配置成功；
				*    false:表示失败；
				*
				* @param app    表示对应的app对象地址信息
				*/
				inline static csf_bool init_logger(csf_app* app) {

					if (!app) {
						return csf_false;
					}
					
					return init_logger(app->get_logger());
				}

				/**
				* 主要功能是：
				*    由于boost.
				* log日志模块的处理问题，不支持dll和so模块输出，所以需要配置日志功能。在所有的device和device_io构造时，都需要执行该处理。如果后面更换了日志
				* 模块，则不需要该函数功能。
				*
				* 返回：
				*    true:表示配置成功；
				*    false:表示失败；
				*
				* @param logger    表示需要处理日志对象
				*/
				inline static csf_bool init_logger(csf_logger& logger) {

#if defined(WIN32)
					boost::log::core::get()->add_sink(logger.get_text_sink_ptr());
#endif
					boost::log::core::get()->add_sink(logger.get_file_sink_ptr());

					csf_logger::set_level(logger.get_level());

					return csf_true;
				}
			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_MODULE_H_INCLUDED_)
