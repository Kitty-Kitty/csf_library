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
					return m_command;
				}
				/**
				 * 表示当前进程所执行指令的参数信息。
				 *
				 * @param newVal
				 */
				inline void set_arguments(csf_string& newVal) {
					csf_strncpy(m_arguments, newVal.c_str(), csf_sizeof(m_arguments) - 1);
				}

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
