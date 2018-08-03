/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_task_type.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:51
*
*Description: Enumeration(csf_task_type)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_TYPE_INCLUDED_)
#define CSF_TASK_TYPE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * ��ʾ���������
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:51
				 */
				enum csf_task_type
				{
					/**
					 * ��ʾδ֪������״ֵ̬
					 */
					m_csf_task_type_none = 0x00000000,
					/**
					 * ��ʾִֻ��һ�ε�����״ֵ̬
					 */
					m_csf_task_type_once = 0x00010000,
					/**
					 * ��ʾѭ��ִ�е����񣬸���������ѭ����ȥ
					 */
					m_csf_task_type_loop = 0x00020000,
					/**
					 * ��ʾһ������ѭ��������������ڷ��ش���ʱ���ͻᱻɾ��
					 */
					m_csf_task_type_loop_broken = csf_task_type_loop | 0x00000100,
					/**
					 * ��ʾָ���������������ڼ�¼����
					 */
					m_csf_task_type_times = 0x00040000,
					/**
					 * ��ʾ����ʱ�������
					 */
					m_csf_task_type_time = 0x00080000
				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_TYPE_INCLUDED_)
