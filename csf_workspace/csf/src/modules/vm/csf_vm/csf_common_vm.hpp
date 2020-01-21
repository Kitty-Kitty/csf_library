/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: csf_common_vm.hpp
*
*Version: 1.0
*
*Date: 15-1月-2020 18:46:53
*
*Description: Class(csf_common_vm) 表示csf的虚拟主机。
这是新引入的模块类型，主要处理app上一层次内容，充当一种容器角色。其目的是释放app概念，让app、device、device_io能够的用于业务处理。
csf_vm的处理逻辑相对固定，主要初始化环境操作，为系统运行搭建最基础的环境。例如：初始日志系统、解析配置文件等。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_COMMON_VM_H_INCLUDED_)
#define CSF_COMMON_VM_H_INCLUDED_

#include <string.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
//#include <boost/process.hpp>
#include <boost/asio/signal_set.hpp>
#include "csf_csfdeque.hpp"
#include "csf_thread_pool.hpp"
#include "csf_app.hpp"
#include "csf_shared_memory.hpp"
#include "csf_vm.hpp"

namespace csf
{
	namespace modules
	{
		namespace vm
		{
			/**
			 * 表示csf的虚拟主机。
			 * 这是新引入的模块类型，主要处理app上一层次内容，充当一种容器角色。其目的是释放app概念，让app、device、device_io能够的用于业务处理。
			 * csf_vm的处理逻辑相对固定，主要初始化环境操作，为系统运行搭建最基础的环境。例如：初始日志系统、解析配置文件等。
			 * @author Administrator
			 * @version 1.0
			 * @created 15-1月-2020 18:46:53
			 */
			class csf_common_vm : public csf::core::module::csf_vm
			{

			public:
				csf_common_vm();
				virtual ~csf_common_vm();

				/**
				 * 功能：
				 *    模块初始化，进行模块启动前的准备工作。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 功能：
				 *    模块启动，进行模块启动工作。表示模块已经正常运行。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 功能：
				 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 表示当前进程io上下文
				 */
				inline boost::asio::io_context& get_ioctx() {

					return m_ioctx;
				}
				/**
				 * 表示需要处理的进程信号
				 */
				inline boost::asio::signal_set& get_signals() {

					return m_signals;
				}
				/**
				 * 功能：
				 *    将已经退出的slave对象添加到处理队列中
				 * 返回：
				 *    true  ：  表示成功；
				 *    false ：  表示失败；
				 *
				 * @param slave
				 */
				inline csf_bool add_exit_slave(csf_slave* slave) {

					return get_deque().push_back(slave);
				}
			protected:
				/**
				 * 表示当前vm对象使用的共享内存
				 */
				inline csf_shared_memory& get_sm() {

					return m_sm;
				}
				/**
				 * 功能：
				 *    初始化共享内存资源
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败；
				 */
				csf_bool init_shared_memory();
				/**
				 * 功能：
				 *    启动指定的私服程序
				 * 返回：
				 *    true  ：  表示成功；
				 *   false  ：  表示失败；
				 *
				 * @param element    表示当前需要启动的伺服信息
				 */
				csf_bool start_slave(csf_element& element);
				/**
				 * 功能：
				 *    启动所有私服进程
				 * 返回：
				 *    true  ：  表示成功；
				 *   false  ：  表示失败；
				 */
				csf_bool start_slaves();
				/**
				 * 功能：
				 *    处理已经退出的进程队列中伺服对象，实现伺服进程的守护。
				 * 返回：
				 *    true  ：  表示成功；
				 *   false  ：  表示失败；
				 */
				csf_bool deamon_slaves();
				/**
				 * 功能：
				 *    实现伺服进程的守护
				 * 返回：
				 *   true  ：  表示成功；
				 *   false ：  表示失败；
				 *
				 * @param slave    表示伺服信息对象
				 */
				csf_bool deamon_slave(csf_slave* slave);
				/**
				 * 功能：
				 *    根据名称停止指定的私服程序
				 * 返回：
				 *    true  ：  表示成功；
				 *   false  ：  表示失败；
				 *
				 * @param name    表示当前需要停止的伺服名称
				 */
				csf_bool stop_slave(csf_string& name);
				/**
				 * 功能：
				 *    停止所有私服进程
				 * 返回：
				 *    true  ：  表示成功；
				 *   false  ：  表示失败；
				 */
				csf_bool stop_slaves();
				/**
				 * 功能：
				 *    根据名称查找指定的私服信息
				 * 返回：
				 *    非null  ：  表示查找到的伺服对象；
				 *      null  ：  表示不存在指定的伺服对象；
				 *
				 * @param name    表示伺服名称
				 */
				csf_slave* find_slave(csf_string& name);
				/**
				 * 功能：
				 *    表示进程信号处理函数
				 * 返回：
				 *    无
				 *
				 * @param ec    表示错误码
				 * @param signal    表示进程当前接收到的信号数值
				 */
				void signal_handler(boost::system::error_code ec, int signal);
				/**
				 * 功能：
				 *    根据名称启动指定的私服程序
				 * 返回：
				 *   true  ：  表示成功；
				 *   false ：  表示失败；
				 *
				 * @param name    表示伺服名称
				 */
				csf_bool start_slave(csf_string& name);
				/**
				 * 功能：
				 *    启动指定的私服程序
				 * 返回：
				 *   true  ：  表示成功；
				 *   false ：  表示失败；
				 *
				 * @param slave    表示伺服信息对象
				 */
				csf_bool start_slave(csf_slave* slave);
				/**
				 * 功能：
				 *    停止指定的私服程序
				 * 返回：
				 *   true  ：  表示成功；
				 *   false ：  表示失败；
				 *
				 * @param slave    表示伺服信息对象
				 */
				csf_bool stop_slave(csf_slave* slave);
				/**
				 * 功能：
				 *    插入指定的私服信息
				 * 返回：
				 *   true  ：  表示成功；
				 *   false ：  表示失败；
				 *
				 * @param slave    表示伺服信息对象
				 */
				csf_bool insert_slave(csf_slave* slave);
				/**
				 * 功能：
				 *    该函数主要用于启动信号处理
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败。
				 */
				csf_bool start_signals_process();
				/**
				 * 功能：
				 *    该函数主要用于停止信号处理
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败。
				 */
				csf_bool stop_signals_process();
				/**
				 * 功能：
				 *    该函数主要用于处理子进程队列
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败。
				 */
				csf_void deamon_thread_process();
				/**
				 * 功能：
				 *    该函数主要用于启动守护处理线程池
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败。
				 */
				csf_bool start_deamon_thread_pool();
				/**
				 * 功能：
				 *    该函数主要用于停止守护处理线程池
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败。
				 */
				csf_bool stop_deamon_thread_pool();
				/**
				 * 表示处理进程守护使用的线程池对象
				 */
				inline csf::core::utils::thread::csf_thread_pool& get_deamon_thread_pool() {

					return m_deamon_thread_pool;
				}
				/**
				 * 表示处理子进程退出信号的线程池
				 */
				inline csf::core::utils::thread::csf_thread_pool& get_io_context_thread_pool() {

					return m_io_context_thread_pool;
				}
				/**
				 * 功能：
				 *    该函数主要用于启动处理子进程退出信号的线程池
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败。
				 */
				csf_bool start_io_context_thread_pool();
				/**
				 * 功能：
				 *    该函数主要用于停止处理子进程退出信号的线程池
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败。
				 */
				csf_bool stop_io_context_thread_pool();
				/**
				 * 功能：
				 *    该函数主要用于处理子进程退出信号队列
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败。
				 */
				csf_void io_context_thread_process();
				/**
				 * 功能：
				 *    该函数主要用于初始化vm的名称
				 * 返回：
				 *    true  :  表示初始化成功；
				 *    false :  表示初始化失败。
				 */
				csf_bool init_vm_name();
				/**
				 * 保存已经异常退出的slave对象列表,方便后续的守护处理
				 */
				inline csf_csfdeque<csf_slave*>& get_deque() {

					return m_deque;
				}

			private:
				/**
				 * 表示处理进程守护使用的线程池对象
				 */
				csf::core::utils::thread::csf_thread_pool m_deamon_thread_pool;
				/**
				 * 表示处理子进程退出信号的线程池
				 */
				csf::core::utils::thread::csf_thread_pool m_io_context_thread_pool;
				/**
				 * 表示当前进程io上下文
				 */
				boost::asio::io_context m_ioctx;
				/**
				 * 表示需要处理的进程信号
				 */
				boost::asio::signal_set m_signals;
				/**
				 * 表示当前vm对象使用的共享内存
				 */
				csf::modules::vm::csf_shared_memory m_sm;
				/**
				 * 保存已经异常退出的slave对象列表,方便后续的守护处理
				 */
				csf_csfdeque<csf_slave*> m_deque;

			};

		}

	}

}
#endif // !defined(CSF_COMMON_VM_H_INCLUDED_)
