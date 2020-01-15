﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:37
*
*Description: Class(csf_connect_factory) 表示连接创建工厂类
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_H_INCLUDED_)
#define CSF_CONNECT_FACTORY_H_INCLUDED_

//#include "csf_connect_factory_manager.hpp"
#include "csf_csfmap.hpp"
#include "csf_connect_factory_interface.hpp"
#include "csf_connect_timeout_manager.hpp"
#include "csf_device.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * 表示连接创建工厂类
				 * @author f
				 * @version 1.0
				 * @created 01-10月-2018 12:54:37
				 */
				class csf_connect_factory : public csf::core::module::csf_device
					, public csf::core::module::connect::csf_connect_factory_interface
				{

				public:
					csf_connect_factory();
					virtual ~csf_connect_factory();

					/**
					 * 表示根据配置文件和类型创建设备模块
					 * 
					 * @param configure_manager    表示配置文件内容
					 * @param type    表示模块的类型
					 */
					inline explicit csf_connect_factory(const csf_configure_manager * configure_manager
						, const csf_device_type type)
						: csf_device(configure_manager, type)
						, m_connect_factory_manager(csf_nullptr) {

					}

					/**
					* 表示根据配置文件和类型创建设备模块
					*
					* @param configure_manager    表示配置文件内容
					* @param type    表示模块的类型
					* @param cfm    表示网络工厂管理器的指针
					*/
					inline explicit csf_connect_factory(const csf_configure_manager * configure_manager
						, const csf_device_type type
						, const csf::core::module::connect::csf_connect_factory_manager* cfm)
						: csf_device(configure_manager, type)
						, m_connect_factory_manager((csf::core::module::connect::csf_connect_factory_manager*)cfm) {

					}

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
					 * 表示根据连接类型创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 */
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type);
					/**
					 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 * @param local_url    表示连接打开的本地地址
					 */
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url);
					/**
					 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 * @param local_url    表示连接打开的本地地址
					 * @param remote_url    表示连接打开的远程地址
					 */
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
					/**
					 * 表示销毁网络连接，销毁成功返回0，失败返回<0的数值。
					 * 
					 * @param connect    表示需要销毁的连接
					 */
					virtual csf_int32 destroy(const csf_connect_ptr connect);
					/**
					* 表示网络连接工厂所属的工厂管理器
					*/
					inline csf::core::module::connect::csf_connect_factory_manager * get_connect_factory_manager() {

						return m_connect_factory_manager;
					}
					/**
					* 表示网络连接工厂所属的工厂管理器
					*
					* @param new_value
					*/
					inline csf_void set_connect_factory_manager(csf::core::module::connect::csf_connect_factory_manager * new_value) {

						m_connect_factory_manager = new_value;
					}
					/**
					* 表示连接超时管理器，主要处理各个连接对象的超时问题。
					*/
					inline csf::core::module::connect::csf_connect_timeout_manager& get_timeout_manager() {

						return m_timeout_manager;
					}
					/**
					* 表示保存所有创建的连接对象
					*/
					inline csf_csfmap<csf_connect*, csf_connect_ptr>& get_connect_collector() {

						return m_connect_collector;
					}
					/**
					* 主要功能是：添加一个连接对象
					* 返回：0表示成功；非0表示失败；
					*
					* @param connect_ptr    表示连接对象
					*/
					inline virtual csf::core::base::csf_int32 insert(csf_connect_ptr& connect_ptr) {

						get_connect_collector().insert(connect_ptr.get(), connect_ptr);

						return csf_succeed;
					}
					/**
					* 主要功能是：删除一个连接对象
					* 返回：0表示成功；非0表示失败；
					*
					* @param connect_ptr    表示连接对象
					*/
					inline csf::core::base::csf_int32 remove(csf_connect_ptr connect_ptr) {

						get_connect_collector().remove(connect_ptr.get());
						get_timeout_manager().remove(connect_ptr->get_read_timeout());
						get_timeout_manager().remove(connect_ptr->get_write_timeout());

						return csf_succeed;
					}
					/**
					* 主要功能是：
					*    查找该连接对象是否存在
					* 返回：
					*    csf_true：表示存在；
					*    csf_false：表示不存在；
					*
					* @param connect_ptr    表示连接对象
					*/
					inline csf_bool is_exist(csf_connect_ptr connect_ptr) {

						return get_connect_collector().have_key(connect_ptr.get());
					}
				private:
					/**
					 * 表示连接工厂管理器对象地址
					 */
					csf::core::module::connect::csf_connect_factory_manager *m_connect_factory_manager = csf_nullptr;
					/**
					* 表示连接超时管理器，主要用于连接的超时处理。
					*/
					csf::core::module::connect::csf_connect_timeout_manager m_timeout_manager;
					/**
					* 表示保存所有创建的连接对象
					*/
					csf_csfmap<csf_connect*, csf_connect_ptr> m_connect_collector;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_H_INCLUDED_)
