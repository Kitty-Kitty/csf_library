/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message_type.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:44
*
*Description: Enumeration(csf_message_type)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MESSAGE_TYPE_INCLUDED_)
#define CSF_MESSAGE_TYPE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace message
			{
				/**
				 * 表示消息的类型
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:44
				 */
				enum csf_message_type
				{
					/**
					 * 表示未知的消息类型
					 */
					m_csf_message_type_none = 0x00000000,
					/**
					 * 表示添加消息类型
					 */
					m_csf_message_type_add = 0x00010000,
					/**
					 * 表示删除消息类型
					 */
					m_csf_message_type_delete = 0x00020000,
					/**
					 * 表示更新消息类型
					 */
					m_csf_message_type_update = 0x00040000,
					/**
					 * 表示控制消息类型
					 */
					m_csf_message_type_ctrl = 0x00080000,
					/**
					 * 表示初始化消息类型
					 */
					m_csf_message_type_init = 0x00100000,
					/**
					 * 表示启动消息类型
					 */
					m_csf_message_type_start = 0x00200000,
					/**
					 * 表示停止消息类型
					 */
					m_csf_message_type_stop = 0x00400000,
					/**
					 * 表示创建消息类型
					 */
					m_csf_message_type_create = 0x00800000,
					/**
					 * 表示销毁消息类型
					 */
					m_csf_message_type_destroy = 0x01000000
				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_TYPE_INCLUDED_)
