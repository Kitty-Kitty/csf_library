/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_dgram_connect.hpp
*
*Version: 1.0
*
*Date: 02-10月-2018 14:17:45
*
*Description: Class(csf_dgram_connect) 表示通信库，网络报文连接信息内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DGRAM_CONNECT_H_INCLUDED_)
#define CSF_DGRAM_CONNECT_H_INCLUDED_

#include "csf_ip_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示通信库，网络报文连接信息内容
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 02-10月-2018 14:17:45
			 */
			class csf_dgram_connect : public csf::modules::connect::csf_ip_connect
			{

			public:
				csf_dgram_connect();
				virtual ~csf_dgram_connect();

				/**
				 * 表示通过factory创建一个connect
				 * 
				 * @param factory    表示需要创建connect的工厂类
				 */
				inline explicit csf_dgram_connect(csf_ip_connect_factory& factory, csf_connect_type type)
					: csf_ip_connect(factory, type) {

				}
				/**
				 * 模块初始化
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
				/**
				 * 表示打开连接信息.
				 * 返回：0表示成功；非0表示失败；
				 * 
				 * @param url    表示连接地址
				 */
				virtual csf_int32 open(const csf_url& url);
				/**
				 * 表示关闭连接.
				 * 返回：0表示成功；非0表示失败；
				 */
				virtual csf_int32 close();
				/**
				 * 模块启动
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
				/**
				 * 表示设置连接的属性项目信息。
				 * 返回：0表示成功；非0表示失败。
				 */
				virtual csf_int32 set_option();
				/**
				 * 模块停止
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
				/**
				 * 表示获取连接的属性项目信息。
				 * 返回：0表示成功；非0表示失败。
				 */
				virtual csf_int32 get_option();

			};

		}

	}

}
#endif // !defined(CSF_DGRAM_CONNECT_H_INCLUDED_)
