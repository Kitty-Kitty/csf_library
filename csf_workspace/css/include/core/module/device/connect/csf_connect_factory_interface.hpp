/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_factory_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:37
*
*Description: Interface(csf_connect_factory_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_INTERFACE_INCLUDED_)
#define CSF_CONNECT_FACTORY_INTERFACE_INCLUDED_

#include "csf_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * <ul>
				 * 	<li></li>
				 * </ul>
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:37
				 */
				class csf_connect_factory_interface : public csf::core::module::csf_interface
				{

				public:
					csf_connect_factory_interface() {

					}

					virtual ~csf_connect_factory_interface() {

					}

					/**
					 * 表示根据连接类型创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 */
					virtual csf_connect* create(const csf::core::module::device::csf_connect_type type) =0;
					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null) =0;
					/**
					 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 * @param local_url    表示连接打开的本地地址
					 */
					virtual csf_connect* create(const csf_connect_type type, const csf_url& local_url) =0;
					/**
					 * 模块启动
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null) =0;
					/**
					 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 * @param local_url    表示连接打开的本地地址
					 * @param remote_url    表示连接打开的远程地址
					 */
					virtual csf_connect* create(const csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) =0;
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null) =0;
					/**
					 * 表示销毁网络连接，销毁成功返回0，失败返回<0的数值。
					 * 
					 * @param connect    表示需要销毁的连接
					 */
					virtual csf_int32 destroy(const csf_connect* connect) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_INTERFACE_INCLUDED_)
