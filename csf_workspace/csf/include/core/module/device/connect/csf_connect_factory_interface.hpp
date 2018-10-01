/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_factory_interface.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:37
*
*Description: Interface(csf_connect_factory_interface) <ul>
	<li></li>
</ul>
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_INTERFACE_H_INCLUDED_)
#define CSF_CONNECT_FACTORY_INTERFACE_H_INCLUDED_

#include "csf_stdcplusplus.hpp"
#include "csf_interface.hpp"
#include "csf_connect.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				
				/**
				 * <ul>
				 * 	<li></li>
				 * </ul>
				 * @author f
				 * @version 1.0
				 * @created 01-10月-2018 12:54:37
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
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type) =0;
					/**
					 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 * @param local_url    表示连接打开的本地地址
					 */
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url) =0;
					/**
					 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
					 * 
					 * @param type    表示连接类型
					 * @param local_url    表示连接打开的本地地址
					 * @param remote_url    表示连接打开的远程地址
					 */
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) =0;
					/**
					 * 表示销毁网络连接，销毁成功返回0，失败返回<0的数值。
					 * 
					 * @param connect    表示需要销毁的连接
					 */
					virtual csf_int32 destroy(const csf_connect_ptr connect) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_INTERFACE_H_INCLUDED_)
