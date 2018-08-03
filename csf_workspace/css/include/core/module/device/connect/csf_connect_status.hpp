/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_status.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:38
*
*Description: Enumeration(csf_connect_status)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_STATUS_INCLUDED_)
#define CSF_CONNECT_STATUS_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示当前的连接状态
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:38
				 */
				enum csf_connect_status
				{
					/**
					 * 表示打开关闭标识位。标识位为1表示打开；标识位为0表示关闭；
					 */
					m_csf_connect_status_open = 0x00000001,
					/**
					 * 表示同步标识位。当标识位为1表示同步；标识位为0表示异步。默认为0异步方式。
					 */
					m_csf_connect_status_sync = 0x00000002,
					/**
					 * 表示使用读超时标识位，设置为1表示使用，0表示不使用。
					 */
					m_csf_connect_status_use_read_timeout = 0x00000004,
					/**
					 * 表示使用写超时标识位，设置为1表示使用，0表示不使用。
					 */
					m_csf_connect_status_use_write_timeout = 0x00000008,
					/**
					 * 表示读超时标识位，设置为1表示读超时，0表示正常。
					 */
					m_csf_connect_status_read_deadline = 0x00000010,
					/**
					 * 表示写超时标识位，设置为1表示写超时，0表示正常。
					 */
					m_csf_connect_status_write_deadline = 0x00000020
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_STATUS_INCLUDED_)
