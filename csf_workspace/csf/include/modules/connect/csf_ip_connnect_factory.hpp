/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 29-7月-2018 15:13:09
*
*Description: Class(csf_ip_connnect_factory) 表示ip网络通信连接工厂类
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_FACTORY_INCLUDED_)
#define CSF_IP_CONNNECT_FACTORY_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_connect_factory.hpp"

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
			 * @created 29-7月-2018 15:13:09
			 */
			class csf_ip_connnect_factory : public csf::core::module::connect::csf_connect_factory
			{

			public:
				explicit csf_ip_connnect_factory() {

				}

				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				*/
				explicit csf_ip_connnect_factory(const csf_configure_manager * configure_manager)

					: csf_connect_factory(configure_manager) {

				}

				virtual ~csf_ip_connnect_factory() {

				}

				/**
				 * 表示根据连接类型创建一个连接。成功返回非0，失败返回0。
				 *
				 * @param type    表示连接类型
				 */
				virtual csf_connect* create(const csf::core::module::connect::csf_connect::csf_connect_type type);
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
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
				/**
				 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
				 *
				 * @param type    表示连接类型
				 * @param local_url    表示连接打开的本地地址
				 */
				virtual csf_connect* create(const csf::core::module::connect::csf_connect::csf_connect_type type, const csf_url& local_url);
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
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
				/**
				 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
				 *
				 * @param type    表示连接类型
				 * @param local_url    表示连接打开的本地地址
				 * @param remote_url    表示连接打开的远程地址
				 */
				virtual csf_connect* create(const csf::core::module::connect::csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
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
				 * 表示销毁网络连接，销毁成功返回0，失败返回<0的数值。
				 *
				 * @param connect    表示需要销毁的连接
				 */
				virtual csf_int32 destroy(const csf_connect* connect);

			};

		}

	}

}


/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* 表示模块的create 和 destroy 句柄定义。                                              */
/* 每个需要通过模块工厂创建的模块都需要添加该宏定义。                                    */
/* 其中module_type表示该模块的类名称，该类实现了构造方法为：                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(csf::modules::connect::csf_ip_connnect_factory)


#endif // !defined(CSF_IP_CONNNECT_FACTORY_INCLUDED_)
