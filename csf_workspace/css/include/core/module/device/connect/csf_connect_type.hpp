/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_type.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:38
*
*Description: Enumeration(csf_connect_type)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_TYPE_INCLUDED_)
#define CSF_CONNECT_TYPE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示连接的类型
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:38
				 */
				enum csf_connect_type
				{
					/**
					 * 表示未知的连接类型
					 */
					m_csf_connect_type_none = 0,
					/**
					 * 表示TCP连接类型
					 */
					m_csf_connect_type_tcp,
					/**
					 * 表示UDP连接类型
					 */
					m_csf_connect_type_udp,
					/**
					 * 表示组播连接类型
					 */
					m_csf_connect_type_multicast,
					/**
					 * 表示广播连接类型
					 */
					m_csf_connect_type_broadcast
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_TYPE_INCLUDED_)
