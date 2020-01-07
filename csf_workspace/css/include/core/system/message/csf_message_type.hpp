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
*Date: 27-6��-2018 17:28:44
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
				 * ��ʾ��Ϣ������
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:44
				 */
				enum csf_message_type
				{
					/**
					 * ��ʾδ֪����Ϣ����
					 */
					m_csf_message_type_none = 0x00000000,
					/**
					 * ��ʾ�����Ϣ����
					 */
					m_csf_message_type_add = 0x00010000,
					/**
					 * ��ʾɾ����Ϣ����
					 */
					m_csf_message_type_delete = 0x00020000,
					/**
					 * ��ʾ������Ϣ����
					 */
					m_csf_message_type_update = 0x00040000,
					/**
					 * ��ʾ������Ϣ����
					 */
					m_csf_message_type_ctrl = 0x00080000,
					/**
					 * ��ʾ��ʼ����Ϣ����
					 */
					m_csf_message_type_init = 0x00100000,
					/**
					 * ��ʾ������Ϣ����
					 */
					m_csf_message_type_start = 0x00200000,
					/**
					 * ��ʾֹͣ��Ϣ����
					 */
					m_csf_message_type_stop = 0x00400000,
					/**
					 * ��ʾ������Ϣ����
					 */
					m_csf_message_type_create = 0x00800000,
					/**
					 * ��ʾ������Ϣ����
					 */
					m_csf_message_type_destroy = 0x01000000
				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_TYPE_INCLUDED_)
