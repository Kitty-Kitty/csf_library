/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_slave.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:42
*
*Description: Class(csf_slave) 表示保存app运行时的信息描述对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_SLAVE_H_INCLUDED_)
#define CSF_SLAVE_H_INCLUDED_

#include "csf_typedef.h"
#include "csf_stddef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace module
		{
			class csf_app;
			/**
			 * 表示保存app运行时的信息描述对象
			 * @author f
			 * @version 1.0
			 * @created 10-1月-2020 14:50:42
			 */
			class csf_slave
			{

			public:
				csf_slave();
				virtual ~csf_slave();
				/**
				 * 功能：
				 *    伺服进程初始化，进行启动前的准备工作。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 */
				virtual csf::core::base::csf_int32 init();
				/**
				 * 功能：
				 *    伺服启动，进行伺服启动工作。表示伺服已经正常运行。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 */
				virtual csf::core::base::csf_int32 start();
				/**
				 * 功能：
				 *    伺服停止，进行伺服停止工作。释放伺服初始化、运行时创建的资源。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 */
				virtual csf::core::base::csf_int32 stop();
				/**
				 * 表示app启动的进程的pid
				 */
				inline csf_uint32 get_pid() {

					return m_pid;
				}
				/**
				 * 表示app启动的进程的pid
				 *
				 * @param newVal
				 */
				inline void set_pid(csf_uint32 newVal) {

					m_pid = newVal;
				}
				/**
				 * 表示客服进程使用的app对象
				 */
				inline csf_app* get_app() {

					return m_app;
				}
				/**
				 * 表示客服进程使用的app对象
				 *
				 * @param newVal
				 */
				inline void set_app(csf_app* newVal) {

					m_app = newVal;
				}
				/**
				 * 表示当前客户机的名称，用于唯一描述一个客户进程。
				 */
				inline csf_string get_name() {

					return m_name;
				}
				/**
				 * 表示当前客户机的名称，用于唯一描述一个客户进程。
				 *
				 * @param newVal
				 */
				inline void set_name(csf_string& newVal) {
					csf_strncpy(m_name, newVal.c_str(), csf_sizeof(m_name) - 1);
				}
				/**
				 * 表示当前进程所执行的指令。
				 */
				inline csf_string get_command() {
					return m_command;
				}
				/**
				 * 表示当前进程所执行的指令。
				 *
				 * @param newVal
				 */
				inline void set_command(csf_string& newVal) {
					csf_strncpy(m_command, newVal.c_str(), csf_sizeof(m_command) - 1);
				}
				/**
				 * 表示当前进程所执行指令的参数信息。
				 */
				inline csf_string get_arguments() {
					return m_arguments;
				}
				/**
				 * 表示当前进程所执行指令的参数信息。
				 *
				 * @param newVal
				 */
				inline void set_arguments(csf_string& newVal) {
					csf_strncpy(m_arguments, newVal.c_str(), csf_sizeof(m_arguments) - 1);
				}
				
				/**
				 * 功能：
				 *    将slave信息转换为字符串
				 * 返回：
				 *    slave信息字符串
				 */
				virtual csf_string to_string();
				/**
				 * 功能：
				 *    查询当前伺服进程是否正在运行。
				 * 返回：
				 *    true  ： 表示正在运行；
				 *    false ： 表示不在运行
				 */
				virtual csf_bool is_running();
				/**
				 * 功能：
				 *    表示当前是否需要父进程守护处理（如果返回true，则父进程会重新启动该进程）
				 * 返回：
				 *    true  ：  表示需要父进程进行守护处理（重新启动）
				 *    false ：  表示不需要守护处理
				 */
				virtual csf_bool is_deamon();

			private:
				/**
				 * 表示当前客户机的名称，用于唯一描述一个客户进程。
				 */
				csf_char m_name[128] = { 0, };
				/**
				 * 表示app启动的进程的pid
				 */
				csf_uint32 m_pid = 0;
				/**
				 * 表示客服进程使用的app对象
				 */
				csf_app* m_app = csf_nullptr;
				/**
				 * 表示当前进程所执行的指令。
				 */
				csf_char m_command[1024] = { 0, };
				/**
				 * 表示当前进程所执行指令的参数信息。
				 */
				csf_char m_arguments[1024] = { 0, };
				
			};

		}

	}

}
#endif // !defined(CSF_SLAVE_H_INCLUDED_)
