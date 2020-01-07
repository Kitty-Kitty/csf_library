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
*Date: 27-6��-2018 17:28:38
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
				 * ��ʾ���ӵ�����
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:38
				 */
				enum csf_connect_type
				{
					/**
					 * ��ʾδ֪����������
					 */
					m_csf_connect_type_none = 0,
					/**
					 * ��ʾTCP��������
					 */
					m_csf_connect_type_tcp,
					/**
					 * ��ʾUDP��������
					 */
					m_csf_connect_type_udp,
					/**
					 * ��ʾ�鲥��������
					 */
					m_csf_connect_type_multicast,
					/**
					 * ��ʾ�㲥��������
					 */
					m_csf_connect_type_broadcast
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_TYPE_INCLUDED_)
