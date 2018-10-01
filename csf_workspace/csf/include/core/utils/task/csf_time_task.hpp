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
*Description: Class(csf_time_task) ��ʾʱ������
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TIME_TASK_INCLUDED_)
#define CSF_TIME_TASK_INCLUDED_

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
				 * ��ʾʱ������
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:52
				 */
				class csf_time_task : public csf::core::utils::task::csf_task
				{

				public:
					csf_time_task();
					virtual ~csf_time_task();

					/**
					 * ��ʾ����ӿڣ���ֻ��is_process����true�����process��
					 */
					virtual csf_int32 process();
					/**
					 * ��ʾ�Ƿ���д���,���is_process����true������ִ��process��
					 */
					virtual csf_bool is_process();
					/**
					 * �ж��Ƿ���Ҫɾ�������is_delete����true��ɾ��task��
					 */
					virtual csf_bool is_delete();
					/**
					 * ��ʾ��ʼʱ��
					 */
					inline csf_uint64 get_begin() {

						return m_begin;
					}
					/**
					 * ��ʾ��ʼʱ��
					 * 
					 * @param new_value
					 */
					inline void set_begin(csf_uint64 new_value) {

						m_begin = new_value;
					}
					/**
					 * ��ʾֹͣʱ��
					 */
					inline csf_uint64 get_end() {

						return m_end;
					}
					/**
					 * ��ʾֹͣʱ��
					 * 
					 * @param new_value
					 */
					inline void set_end(csf_uint64 new_value) {

						m_end = new_value;
					}

				private:
					/**
					 * ��ʾ��ʼʱ��
					 */
					csf_uint64 m_begin = 0;
					/**
					 * ��ʾֹͣʱ��
					 */
					csf_uint64 m_end = 0;

				};

			}

		}

	}

}
#endif // !defined(CSF_TIME_TASK_INCLUDED_)
