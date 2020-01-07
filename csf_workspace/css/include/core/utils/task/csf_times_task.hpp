/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 19-7��-2018 20:11:52
*
*Description: Class(csf_times_task) ��ʾָ���������������ڼ�¼����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TIMES_TASK_INCLUDED_)
#define CSF_TIMES_TASK_INCLUDED_

#include "csf_task.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * ��ʾָ���������������ڼ�¼����
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:52
				 */
				class csf_times_task : public csf::core::utils::task::csf_task
				{

				public:
					csf_times_task();
					virtual ~csf_times_task();

					inline csf_uint32 get_times() {

						return m_times;
					}
					/**
					 * ��ʾ����ӿڣ���ֻ��is_process����true�����process��
					 */
					virtual csf_int32 process();
					/**
					 * ��ʾ�Ƿ���д���,���is_process����true������ִ��process��
					 */
					virtual csf_bool is_process();
					/**
					 * 
					 * @param newVal
					 */
					inline void set_times(csf_uint32 newVal) {

						m_times = newVal;
					}
					/**
					 * ��ʾ��ǰ�Ѿ����еĴ�������
					 */
					inline csf_uint32 get_sequence() {

						return m_sequence;
					}
					/**
					 * �ж��Ƿ���Ҫɾ�������is_delete����true��ɾ��task��
					 */
					virtual csf_bool is_delete();
					/**
					 * ��ʾ��ǰ�Ѿ����еĴ�������
					 * 
					 * @param newVal
					 */
					inline void set_sequence(csf_uint32 newVal) {

						m_sequence = newVal;
					}

				private:
					/**
					 * ��ʾ��ǰ�Ѿ����еĴ�������
					 */
					csf_uint32 m_sequence = 0;
					/**
					 * ��ʾ�������д���
					 */
					csf_uint32 m_times = 0;

				};

			}

		}

	}

}
#endif // !defined(CSF_TIMES_TASK_INCLUDED_)
