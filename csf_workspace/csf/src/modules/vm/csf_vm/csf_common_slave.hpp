/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_common_slave.hpp
*
*Version: 1.0
*
*Date: 15-1月-2020 18:46:53
*
*Description: Class(csf_common_slave) 表示保存app运行时的信息描述对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_COMMON_SLAVE_H_INCLUDED_)
#define CSF_COMMON_SLAVE_H_INCLUDED_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/process.hpp>
#include "csf_slave.hpp"
#include "csf_common_vm.hpp"

namespace csf
{
	namespace modules
	{
		namespace vm
		{
			/**
			 * 表示保存app运行时的信息描述对象
			 * @author f
			 * @version 1.0
			 * @created 15-1月-2020 18:46:53
			 */
			class csf_common_slave : public csf::core::module::csf_slave
			{

			public:
				csf_common_slave();
				virtual ~csf_common_slave();
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
				 * 表示当前伺服进程所属的虚拟主机对象
				 */
				inline csf_common_vm* get_common_vm() {

					return m_common_vm;
				}
				/**
				 * 表示当前伺服进程所属的虚拟主机对象
				 *
				 * @param newVal
				 */
				inline void set_common_vm(csf_common_vm* newVal) {

					m_common_vm = newVal;
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
				/**
				 * 功能：
				 *    表示进程退出时调用的函数
				 * 返回：
				 *    无
				 *
				 * @param signal    表示进程退出时接收到信号类型
				 * @param ec    表示错误码
				 */
				void exit_handler(int signal, const std::error_code& ec);
				/**
				 * 表示当前伺服进程接收到的信号类型
				 */
				inline int get_signal() {

					return m_signal;
				}
				/**
				 * 表示销毁已经创建的child对象
				 */
				csf_void destroy_child();
			protected:
				/**
				 * 表示当前伺服进程接收到的信号类型
				 *
				 * @param newVal
				 */
				inline void set_signal(int newVal) {

					m_signal = newVal;
				}
				/**
				 * 表示子进程对象
				 */
				inline boost::process::child* get_child() {

					return m_child;
				}
				/**
				 * 表示子进程对象
				 *
				 * @param newVal
				 */
				inline void set_child(boost::process::child* newVal) {

					m_child = newVal;
				}
			private:
				/**
				 * 表示当前伺服进程接收到的信号类型
				 */
				int m_signal = 0;
				/**
				 * 表示当前伺服进程所属的虚拟主机对象
				 */
				csf_common_vm* m_common_vm = csf_nullptr;
				/**
				 * 表示子进程对象
				 */
				boost::process::child* m_child = csf_nullptr;
			};

		}

	}

}
#endif // !defined(CSF_COMMON_SLAVE_H_INCLUDED_)
