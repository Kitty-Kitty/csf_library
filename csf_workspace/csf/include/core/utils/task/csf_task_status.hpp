/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_task_status.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:51
*
*Description: Enumeration(csf_task_status)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_STATUS_INCLUDED_)
#define CSF_TASK_STATUS_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * ��ʾ��ʱ����״ֵ̬
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:51
				 */
				enum csf_task_status
				{
					/**
					 * ��ʾδ֪������״ֵ̬
					 */
					m_csf_task_status_none = 0x00000000,
					/**
					 * ��ʾ��ʼ������״ֵ̬
					 */
					m_csf_task_status_init = 0x00010000,
					/**
					 * ��ʾ��ʼ������״ֵ̬
					 */
					m_csf_task_status_start = 0x00020000,
					/**
					 * ��ʾֹͣ������״ֵ̬
					 */
					m_csf_task_status_stop = 0x00040000
				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_STATUS_INCLUDED_)
