/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_app_option.hpp
*
*Version: 1.0
*
*Date: 06-12月-2019 13:11:25
*
*Description: Class(csf_app_option) 表示应用程序运行环境参数。主要实现可执行程序的参数解析相关内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_APP_OPTION_H_INCLUDED_)
#define CSF_APP_OPTION_H_INCLUDED_

#include <iostream>
#include <map>
#include <functional>
#include <boost/program_options.hpp>
#include "csf_app.hpp"

using namespace boost::program_options;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示应用程序运行环境参数。主要实现可执行程序的参数解析相关内容
			 * @author f
			 * @version 1.0
			 * @created 06-12月-2019 13:11:25
			 */
			class csf_app_option
			{

			public:

				/**
				* 功能：
				*    需要将csf_app_option作用的对象csf_app
				*
				* @param app
				*/
				inline explicit csf_app_option(csf_app& app)
					: m_app(app)
					, m_description("allowed options") {
					add_options();
				}

				virtual ~csf_app_option() {

				}
				/**
				* 功能：
				*    解析程序运行参数信息
				* 返回：
				*    true：表示设置成功；
				*    false：表示设置失败；
				*
				* @param argc    表示参数的个数
				* @param argv    表示参数内容
				*/
				virtual bool get_option(int argc, char** argv);
				/**
				* 功能：
				*    表示app是否已经配置完成
				* 返回：
				*    true：表示设置成功；
				*    false：表示未设置成功；
				*/
				bool isconfigured();
			protected:
				/**
				* 功能：
				*    表示添加程序参数信息
				* 返回：
				*    无
				*/
				virtual void add_options();
				/**
				 * 功能：
				 *    打印app使用参数提示信息
				 * 返回：
				 *    无
				 *
				 * @param vm    表示当前的参数列表
				 * @param key    表示当前参数的名称
				 */
				virtual void help(variables_map& vm, std::string key);
				/**
				 * 功能：
				 *    打印app版本号信息
				 * 返回：
				 *    无
				 *
				 * @param vm    表示当前的参数列表
				 * @param key    表示当前参数的名称
				 */
				virtual void version(variables_map& vm, std::string key);
				/**
				 * 功能：
				 *    设置当前app的名称
				 * 返回：
				 *    无
				 *
				 * @param vm    表示当前的参数列表
				 * @param key    表示当前参数的名称
				 */
				virtual void name(variables_map& vm, std::string key);
				/**
				 * 功能：
				 *    设置当前app所属的vm对象
				 * 返回：
				 *    无
				 *
				 * @param vm    表示当前的参数列表
				 * @param key    表示当前参数的名称
				 */
				virtual void vm_pid(variables_map& vm, std::string key);
				/**
				 * 功能：
				 *    设置当前app所属的vm对象地址指针
				 * 返回：
				 *    无
				 *
				 * @param vm    表示当前的参数列表
				 * @param key    表示当前参数的名称
				 */
				virtual void vm_instance(variables_map& vm, std::string key);
				/**
				* 表示app运行参数描述信息
				*/
				inline options_description& get_description() {

					return m_description;
				}
				/**
				* 表示当前关键字所对应的处理函数对应列表
				*/
				inline std::map<std::string, std::function<void(variables_map&, std::string)>>& get_function_map() {

					return m_function_map;
				}

			private:
				/**
				 *
				 * @param file    表示app需要的根配置文件
				 * @param fmt    表示配置文件的格式
				 */
				bool configure(std::string file, std::string fmt);
				/**
				* 表示当前的app对象
				*/
				inline csf_app& get_app() {

					return m_app;
				}

			private:
				/**
				 * 表示当前的app对象
				 */
				csf_app& m_app;
				/**
				 * 表示app运行参数描述信息
				 */
				options_description m_description;
				/**
				* 表示当前关键字所对应的处理函数对应列表
				*/
				std::map<std::string, std::function<void(variables_map&, std::string )>> m_function_map;
			};

		}

	}

}
#endif // !defined(CSF_APP_OPTION_H_INCLUDED_)
