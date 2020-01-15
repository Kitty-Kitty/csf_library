/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_factory.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:37
*
*Description: Class(csf_connect_factory)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_INCLUDED_)
#define CSF_CONNECT_FACTORY_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_connect_factory_manager.hpp"
#include "csf_connect_factory_interface.hpp"
#include "csf_device.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:37
				 */
				class csf_connect_factory : public csf::core::module::device::csf_device, public csf::core::module::device::csf_connect_factory_interface
				{

				public:
					csf_connect_factory();
					virtual ~csf_connect_factory();

					/**
					 * 表示设备的添加操作
					 * 
					 * @param element    表示设备添加操作
					 * @param callback    表示设备操作的回调函数
					 */
					virtual csf_int32 del(csf_element& element, csf_device_operation_callback callback);
					inline csf::core::system::csf_configure_manager get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示设备的添加操作
					 * 
					 * @param element    表示设备添加操作
					 * @param callback    表示设备操作的回调函数
					 */
					virtual csf_int32 ctrl(csf_element& element, csf_device_operation_callback callback);
					/**
					 * 
					 * @param new_value
					 */
					inline void set_configure_manager(csf::core::system::csf_configure_manager new_value) {

						m_configure_manager = newVal;
					}
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
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示根据连接类型创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 */
					virtual csf_connect* create(const csf::core::module::device::csf_connect_type type);
					/**
					 * 模块启动
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 * @param local_url    表示连接打开的本地地址
					 */
					virtual csf_connect* create(const csf_connect_type type, const csf_url& local_url);
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 * @param local_url    表示连接打开的本地地址
					 * @param remote_url    表示连接打开的远程地址
					 */
					virtual csf_connect* create(const csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
					/**
					 * 表示销毁网络连接，销毁成功返回0，失败返回<0的数值。
					 * 
					 * @param connect    表示需要销毁的连接
					 */
					virtual csf_int32 destroy(const csf_connect* connect);

				private:
					/**
					 * 表示连接工厂管理器对象地址
					 */
					csf::core::module::device::csf_connect_factory_manager *m_connect_factory_manager;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_INCLUDED_)
