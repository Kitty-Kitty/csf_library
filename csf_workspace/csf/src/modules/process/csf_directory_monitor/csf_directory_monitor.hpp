/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_directory_monitor.hpp
*
*Version: 1.0
*
*Date: 12-12月-2019 22:03:18
*
*Description: Class(csf_directory_monitor) 主要实现指定目录的空间回滚功能。当目录中的文件空间大于指定大小时，将采取删除最久文件的，释放空间，以避免磁盘空间全部被占用。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DIRECTORY_MONITOR_H_INCLUDED_)
#define CSF_DIRECTORY_MONITOR_H_INCLUDED_

#include "csf_process.hpp"
#include "csf_thread_pool.hpp"

#undef BOOST_CONFIG_ABI_PREFIX_HPP

#include "dir_monitor/dir_monitor.hpp"
#include "csf_files_manager.hpp"

namespace csf
{
	namespace modules
	{
		namespace process
		{
#define		csf_process_version				1000000
#define		CSF_PROCESS_VERSION				"V1.0.0"
#define		CSF_PROCESS_VAR					"csf_directory_monitor"
#define		CSF_PROCESS_VER					CSF_CONNECT_VAR	"/" CSF_CONNECT_VERSION

			/**
			*定义目录监控事件监控函数
			*/
			typedef csf_function<void(boost::asio::dir_monitor& dm
				, const boost::system::error_code& ec
				, const boost::asio::dir_monitor_event& ev)>		csf_dm_function;
			/**
			 * 主要实现指定目录的空间回滚功能。当目录中的文件空间大于指定大小时，将采取删除最久文件的，释放空间，以避免磁盘空间全部被占用。
			 * @author f
			 * @version 1.0
			 * @created 12-12月-2019 22:03:18
			 */
			class csf_directory_monitor : public csf::core::module::device::csf_process
			{

			public:
				csf_directory_monitor()
					: m_dm(m_io_service) {

				}
				virtual ~csf_directory_monitor();

				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				*/
				inline explicit csf_directory_monitor(const csf_configure_manager * configure_manager)
					: csf_process(configure_manager
						, csf::core::module::csf_device::csf_device_type_general_extend)
					, m_dm(m_io_service) {

				}
				/**
				 * 模块初始化
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
				/**
				 * 模块启动
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
				/**
				 * 模块停止
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
				/**
				* * 主要功能是：主要实现模块的配置信息处理接口。
				* * 返回：0表示成功；非0表示失败；
				* *
				* * @param element    表示模块的配置信息
				* *
				* * 常用的配置信息保存结构为：
				* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
				* * <module>
				* *        <!--***表示模块对应的模块名称信息***-->
				* *        <name>csf_connection</name>
				* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
				* *        <mid>02000000-0000001</mid>
				* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
				* *        <configure>
				* *                <!--表示线程数量-->
				* *                <thread_number>4</thread_number>
				* *        </configure>
				* * </module>
				*
				*/
				virtual csf_int32 configure(const csf_element& element);

			protected:
				/**
				* 功能：
				*    创建需要监控的目录
				* 返回：
				*    true  ： 表示成功
				*    false ： 表示失败
				*/
				bool create_directory();
				/**
				* 功能：
				*    启动目录监控处理
				* 返回：
				*    无
				*/
				bool start_monitor();
				/**
				* 功能：
				*    启动线程组，进行监控处理
				* 返回：
				*    无
				*/
				bool start_thread_pool();
				/**
				* 功能：
				*    表示线程处理函数
				* 返回：
				*    无
				*/
				void thread_process();
				/**
				* 功能：
				*    停止线程组，停止监控处理
				* 返回：
				*    无
				*/
				bool stop_thread_pool();
				/**
				* 功能：
				*    停止目录监控处理
				* 返回：
				*    无
				*/
				bool stop_monitor();
				/**
				* 功能：
				*    初始化文件管理器对象
				* 返回：
				*    无
				*/
				bool init_files_manager();
				/**
				* 功能：
				*    启动文件管理器对象
				* 返回：
				*    无
				*/
				bool start_files_manager();
				/**
				* 功能：
				*    停止文件管理器对象
				* 返回：
				*    无
				*/
				bool stop_files_manager();
				/**
				* 功能：
				*    表示事件消息处理的主要函数
				* 返回：
				*    无
				*
				* @param dm    表示当前的监控对象
				* @param ec    表示当前的系统错误对象
				* @param ev    表示当前目录监控事件类型
				*/
				void event_process(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev);
				/**
				* 功能：
				*    处理文件添加消息
				* 返回：
				*    无
				*
				* @param dm    表示当前的监控对象
				* @param ec    表示当前的系统错误对象
				* @param ev    表示当前目录监控事件类型
				*/
				void event_added(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev);
				/**
				* 功能：
				*    处理未知消息
				* 返回：
				*    无
				*
				* @param dm    表示当前的监控对象
				* @param ec    表示当前的系统错误对象
				* @param ev    表示当前目录监控事件类型
				*/
				void event_null(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev);
				/**
				* 功能：
				*    处理文件删除消息
				* 返回：
				*    无
				*
				* @param dm    表示当前的监控对象
				* @param ec    表示当前的系统错误对象
				* @param ev    表示当前目录监控事件类型
				*/
				void event_removed(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev);
				/**
				* 功能：
				*    处理文件修改消息
				* 返回：
				*    无
				*
				* @param dm    表示当前的监控对象
				* @param ec    表示当前的系统错误对象
				* @param ev    表示当前目录监控事件类型
				*/
				void event_modified(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev);
				/**
				* 功能：
				*    处理修改文件名称消息
				* 返回：
				*    无
				*
				* @param dm    表示当前的监控对象
				* @param ec    表示当前的系统错误对象
				* @param ev    表示当前目录监控事件类型
				*/
				void event_renamed_old_name(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev);
				/**
				* 功能：
				*    处理修改文件名称消息
				* 返回：
				*    无
				*
				* @param dm    表示当前的监控对象
				* @param ec    表示当前的系统错误对象
				* @param ev    表示当前目录监控事件类型
				*/
				void event_renamed_new_name(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev);
				/**
				* 功能：
				*    处理文件扫描消息
				* 返回：
				*    无
				*
				* @param dm    表示当前的监控对象
				* @param ec    表示当前的系统错误对象
				* @param ev    表示当前目录监控事件类型
				*/
				void event_recursive_rescan(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev);
			private:
				/**
				* 功能：
				*    初始目录监控事件所对应的处理函数
				* 返回：
				*    无
				*/
				void init_function();
				/**
				* 表示当前同时进行目录监控的线程池
				*/
				inline csf_thread_pool& get_thread_pool() {
					return m_thread_pool;
				}
				/**
				* 表示监控处理的任务队列对象
				*/
				inline boost::asio::io_service& get_io_service() {

					return m_io_service;
				}
				/**
				* 表示当前的任务监控对象
				*/
				inline boost::asio::dir_monitor& get_dm() {

					return m_dm;
				}
				/**
				* 表示监控事件处理列表
				*/
				inline csf_map<boost::asio::dir_monitor_event::event_type, csf_dm_function>& get_function_map() {

					return m_function_map;
				}
				/**
				* 表示文件管理器对象，实现目录下文件的统计、更新、删除的监控
				*/
				inline csf_files_manager& get_files_manager() {

					return m_files_manager;
				}
			private:
				/**
				* 表示当前同时进行目录监控的线程池
				*/
				csf_thread_pool m_thread_pool;
				/**
				* 表示监控处理的任务队列对象
				*/
				boost::asio::io_service m_io_service;
				/**
				* 表示当前的任务监控对象
				*/
				boost::asio::dir_monitor m_dm;
				/**
				* 表示监控事件处理列表
				*/
				csf_map<boost::asio::dir_monitor_event::event_type, csf_dm_function> m_function_map;
				/**
				* 表示文件管理器对象，实现目录下文件的统计、更新、删除的监控
				*/
				csf_files_manager m_files_manager;
			};

		}

	}

}
#endif // !defined(CSF_DIRECTORY_MONITOR_H_INCLUDED_)
