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
*Date: 27-6��-2018 17:28:38
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
				 * ��ʾ��ǰ������״̬
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:38
				 */
				enum csf_connect_status
				{
					/**
					 * ��ʾ�򿪹رձ�ʶλ����ʶλΪ1��ʾ�򿪣���ʶλΪ0��ʾ�رգ�
					 */
					m_csf_connect_status_open = 0x00000001,
					/**
					 * ��ʾͬ����ʶλ������ʶλΪ1��ʾͬ������ʶλΪ0��ʾ�첽��Ĭ��Ϊ0�첽��ʽ��
					 */
					m_csf_connect_status_sync = 0x00000002,
					/**
					 * ��ʾʹ�ö���ʱ��ʶλ������Ϊ1��ʾʹ�ã�0��ʾ��ʹ�á�
					 */
					m_csf_connect_status_use_read_timeout = 0x00000004,
					/**
					 * ��ʾʹ��д��ʱ��ʶλ������Ϊ1��ʾʹ�ã�0��ʾ��ʹ�á�
					 */
					m_csf_connect_status_use_write_timeout = 0x00000008,
					/**
					 * ��ʾ����ʱ��ʶλ������Ϊ1��ʾ����ʱ��0��ʾ������
					 */
					m_csf_connect_status_read_deadline = 0x00000010,
					/**
					 * ��ʾд��ʱ��ʶλ������Ϊ1��ʾд��ʱ��0��ʾ������
					 */
					m_csf_connect_status_write_deadline = 0x00000020
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_STATUS_INCLUDED_)
