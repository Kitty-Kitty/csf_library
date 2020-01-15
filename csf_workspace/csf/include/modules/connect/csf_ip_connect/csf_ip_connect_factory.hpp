﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:43
*
*Description: Class(csf_ip_connect_factory) 表示ip网络通信连接工厂类
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_FACTORY_H_INCLUDED_)
#define CSF_IP_CONNNECT_FACTORY_H_INCLUDED_

#include "csf_boost_asio.hpp"
#include "csf_configure_manager.hpp"
#include "csf_connect_factory.hpp"
#include "csf_thread_pool.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			#define		csf_connect_version				1000000
			#define		CSF_CONNECT_VERSION				"V1.0.0"
			#define		CSF_CONNECT_VAR					"csf_ip_connect_factory"
			#define		CSF_CONNECT_VER					CSF_CONNECT_VAR	"/" CSF_CONNECT_VERSION
			/************************************************************************/
			/* 表示连接工厂所需要创建的线程数量，数值默认为：2						*/
			/************************************************************************/
			#define csf_ip_connect_factory_thread_number							2		//表示连接工厂所需要创建的线程数量
			/************************************************************************/
			/* 表示连接工厂所能接收的最大连接数，数值默认为：1024						*/
			/************************************************************************/
			#define csf_ip_connect_factory_connect_limit							1024	//表示连接工厂所能接收的最大连接数
			/************************************************************************/
			/* 表示默认的定时器间隔时间，单位：毫秒（ms）								*/
			/************************************************************************/
			#define csf_ip_connect_factory_timer_interval_ms						500		//表示默认的定时器间隔时间，单位：毫秒（ms）
			/**
			 * 表示ip网络通信连接工厂类
			 * @author f
			 * @version 1.0
			 * @created 01-10月-2018 12:54:43
			 */
			class csf_ip_connect_factory : public csf::core::module::connect::csf_connect_factory
			{

			public:
				csf_ip_connect_factory();
				virtual ~csf_ip_connect_factory();
				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				* @param type    表示模块的类型
				*/
				inline explicit csf_ip_connect_factory(const csf_configure_manager * configure_manager)
					: csf_connect_factory(configure_manager, csf_device_type_connect_extend)
					, m_idle_interval(csf_ip_connect_factory_timer_interval_ms)
					, m_connect_limit(csf_ip_connect_factory_connect_limit)
					, m_connect_timeout(csf_connect_timeout_default_ms) {

					set_version(
						csf_connect_version
						, CSF_CONNECT_VER
						, CSF_CONNECT_VAR
						, "general ip connect factory"
					);
				}
				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				* @param type    表示模块的类型
				* @param cfm    表示网络工厂管理器的指针
				*/
				inline explicit csf_ip_connect_factory(const csf_configure_manager * configure_manager
					, const csf_connect_factory_manager* cfm)
					: csf_connect_factory(configure_manager, csf_device_type_connect_extend, cfm)
					, m_idle_interval(csf_ip_connect_factory_timer_interval_ms)
					, m_connect_limit(csf_ip_connect_factory_connect_limit)
					, m_connect_timeout(csf_connect_timeout_default_ms) {

					set_version(
						csf_connect_version
						, CSF_CONNECT_VER
						, CSF_CONNECT_VAR
						, "general ip connect factory"
					);
				}
				/**
				* 主要功能是：主要实现模块的配置信息处理接口。
				* 返回：0表示成功；非0表示失败；
				*
				* @param element    表示模块的配置信息
				*
				* 常用的配置信息保存结构为：
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
				*/
				virtual csf_int32 configure(const csf_element& element);
				/**
				 * 表示根据连接类型创建一个连接。成功返回非0，失败返回0。
				 *
				 * @param type    表示连接类型
				 */
				virtual csf_connect_ptr create(const csf_connect::csf_connect_type type);
				/**
				 * 表示设备的添加操作
				 *
				 * @param element    表示设备添加操作
				 * @param callback    表示设备操作的回调函数
				 */
				virtual csf_int32 del(csf_element& element, csf_device_operation_callback callback);
				/**
				 * 模块初始化
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
				 *
				 * @param type    表示连接类型
				 * @param local_url    表示连接打开的本地地址
				 */
				virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url);
				/**
				 * 表示设备的添加操作
				 *
				 * @param element    表示设备添加操作
				 * @param callback    表示设备操作的回调函数
				 */
				virtual csf_int32 ctrl(csf_element& element, csf_device_operation_callback callback);
				/**
				 * 模块启动
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
				 *
				 * @param type    表示连接类型
				 * @param local_url    表示连接打开的本地地址
				 * @param remote_url    表示连接打开的远程地址
				 */
				virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
				/**
				 * 模块停止
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 表示设备的添加操作
				 *
				 * @param element    表示设备添加操作
				 * @param callback    表示设备操作的回调函数
				 */
				virtual csf_int32 update(csf_element& element, csf_device_operation_callback callback);
				/**
				 * 表示设备的添加操作
				 *
				 * @param element    表示设备添加操作
				 * @param callback    表示设备操作的回调函数
				 */
				virtual csf_int32 add(csf_element& element, csf_device_operation_callback callback);
				/**
				 * 表示销毁网络连接，销毁成功返回0，失败返回<0的数值。
				 *
				 * @param connect_ptr    表示需要销毁的连接
				 */
				inline virtual csf_int32 destroy(const csf_connect_ptr connect_ptr) {

					get_connect_collector().remove(connect_ptr.get());

					return 0;
				}
				/**
				* 主要功能是：添加一个连接对象
				* 返回：0表示成功；非0表示失败；
				*
				* @param connect_ptr    表示连接对象
				*/
				inline virtual csf::core::base::csf_int32 insert(csf_connect_ptr connect_ptr) {

					if (!connect_ptr) {
						return csf_failure;
					}

					//如果已经配置了连接最大值，则需要进行最大连接数处理
					if (get_connect_limit() > 0) {
						//判断是否超过最大值，则返回失败
						if (get_connect_collector().size() >= (csf_int32)get_connect_limit()) {
							return csf_failure;
						}
					}

					return csf_connect_factory::insert(connect_ptr);
				}
				/**
				* 表示boost的io_service对象
				*/
				inline boost::asio::io_service& get_io_service() {

					return m_io_service;
				}
				/**
				* 表示系统的连接的超时时间，单位：毫秒（ms）
				*/
				inline csf_uint64 get_connect_timeout() {

					return m_connect_timeout;
				}
				/**
				* 表示连接工厂所能接收的最大连接
				*/
				inline csf_uint32 get_connect_limit() {

					return m_connect_limit;
				}
			protected:
				/**
				* 主要功能是：表示往网络连接管理器中删除网络连接对象
				* 返回：0表示成功；非0表示失败；
				*
				* @param connect_ptr    表示需要添加的网络连接对象
				*/
				inline csf::core::base::csf_int32 remove(csf_connect_ptr connect_ptr) {

					if (!connect_ptr) {
						return csf_failure;
					}

					get_connect_collector().erase(connect_ptr.get());

					return csf_succeed;
				}
				/**
				* 主要功能是：表示清除网络连接管理器中所有的网络连接对象
				* 返回：0表示成功；非0表示失败；
				*/
				inline csf::core::base::csf_int32 clear() {

					get_connect_collector().clear();

					return csf_succeed;
				}
				/**
				* 表示线程池
				*/
				inline csf::core::utils::thread::csf_thread_pool& get_thread_pool() {

					return m_thread_pool;
				}
				/**
				* 主要功能是：启动线程池
				* 返回：无
				*/
				csf_int32 start_thread_pool();
				/**
				* 主要功能是：线程池启动的io_service任务
				* 返回：无
				*/
				csf_void run_io_service();
				/**
				* 表示连接工厂所能接收的最大连接
				*
				* @param new_value
				*/
				inline void set_connect_limit(csf_uint32 new_value) {

					m_connect_limit = new_value;
				}
			private:
				/**
				* 表示系统的空休眠等待间隔时间，单位：毫秒（ms）
				*/
				inline csf_uint64 get_idle_interval() const {

					return m_idle_interval;
				}
				/**
				* 表示系统的空休眠等待间隔时间，单位：毫秒（ms）
				*
				* @param new_value
				*/
				inline void set_idle_interval(csf_uint64 new_value) {

					m_idle_interval = new_value;
				}
				/**
				* 表示系统的连接的超时时间，单位：毫秒（ms）
				*
				* @param new_value
				*/
				inline void set_connect_timeout(csf_uint64 new_value) {

					m_connect_timeout = new_value;
				}
				/**
				* 表示boost的io_service对象
				*/
				boost::asio::io_service m_io_service;
				/**
				* 表示线程池
				*/
				csf::core::utils::thread::csf_thread_pool m_thread_pool;
				/**
				* 表示系统的空休眠等待间隔时间，单位：毫秒（ms）
				*/
				csf_uint64 m_idle_interval = csf_ip_connect_factory_timer_interval_ms;
				/**
				* 表示连接工厂所能接收的最大连接
				*/
				csf_uint32 m_connect_limit = csf_ip_connect_factory_connect_limit;
				/**
				* 表示系统的连接的超时时间，单位：毫秒（ms）
				*/
				csf_uint64 m_connect_timeout = csf_connect_timeout_default_ms;
			};
		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_FACTORY_H_INCLUDED_)
