/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connnect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:43
*
*Description: Class(csf_ip_connnect_factory) 表示ip网络通信连接工厂类
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_FACTORY_H_INCLUDED_)
#define CSF_IP_CONNNECT_FACTORY_H_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_connect_factory.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示ip网络通信连接工厂类
			 * @author f
			 * @version 1.0
			 * @created 01-10月-2018 12:54:43
			 */
			class csf_ip_connnect_factory : public csf::core::module::connect::csf_connect_factory
			{

			public:
				csf_ip_connnect_factory();
				virtual ~csf_ip_connnect_factory();

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
				 * @param connect    表示需要销毁的连接
				 */
				virtual csf_int32 destroy(const csf_connect_ptr connect);
			protected:
				/**
				* 主要功能是：表示往网络连接管理器中插入网络连接对象
				* 返回：0表示成功；非0表示失败；
				*
				* @param connect_ptr    表示需要添加的网络连接对象
				*/
				inline csf::core::base::csf_int32 insert(csf_connect_ptr connect_ptr) {
					if (!connect_ptr) {
						return csf_failure;
					}

					csf_unqiue_lock<decltype(m_connect_mutex)> tmp_lock(m_connect_mutex);

					get_connect_collector().insert(csf_map<csf_connect*, csf_connect_ptr>::value_type(
						connect_ptr.get()
						, connect_ptr));

					return csf_success;
				}
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

					csf_unqiue_lock<decltype(m_connect_mutex)> tmp_lock(m_connect_mutex);

					csf_map<csf_connect*, csf_connect_ptr>::iterator		tmp_iter;

					tmp_iter = get_connect_collector().find(connect_ptr.get());
					if (tmp_iter != get_connect_collector().end()) {
						get_connect_collector().erase(tmp_iter);
						return csf_success;
					}

					return csf_failure;
				}
				/**
				* 主要功能是：表示清除网络连接管理器中所有的网络连接对象
				* 返回：0表示成功；非0表示失败；
				*/
				inline csf::core::base::csf_int32 clear() {

					csf_unqiue_lock<decltype(m_connect_mutex)> tmp_lock(m_connect_mutex);

					get_connect_collector().clear();

					return csf_success;
				}
			private:
				/**
				* 表示网络连接管理器
				*/
				inline csf_map<csf_connect*, csf_connect_ptr>& get_connect_collector() {

					return m_connect_collector;
				}
				/**
				* 表示网络连接管理器
				*/
				csf_map<csf_connect*, csf_connect_ptr> m_connect_collector;
				/**
				* 表示线程安全使用的互斥锁内容
				*/
				csf_shared_mutex m_connect_mutex;
			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_FACTORY_H_INCLUDED_)
