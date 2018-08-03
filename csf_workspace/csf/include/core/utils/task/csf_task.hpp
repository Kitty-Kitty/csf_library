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
*Date: 19-7��-2018 20:11:50
*
*Description: Class(csf_task) ��ʾ��ʱ����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_INCLUDED_)
#define CSF_TASK_INCLUDED_

#include "csf_task_callback.hpp"
#include "csf_task_delete_callback.hpp"
#include "csf_task_interface.hpp"
#include "csf_task_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * ��ʾ��ʱ����
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:50
				 */
				class csf_task : public csf::core::utils::task::csf_task_interface
				{

				public:
					/**
					 * ��ʾ��ʱ����״ֵ̬
					 * @author f
					 * @version 1.0
					 * @created 19-7��-2018 20:11:50
					 */
					enum csf_task_status
					{
						/**
						 * ��ʾδ֪������״ֵ̬
						 */
						csf_task_status_none = 0x00000000,
						/**
						 * ��ʾ��ʼ������״ֵ̬
						 */
						csf_task_status_init = 0x00010000,
						/**
						 * ��ʾ��ʼ������״ֵ̬
						 */
						csf_task_status_start = 0x00020000,
						/**
						 * ��ʾֹͣ������״ֵ̬
						 */
						csf_task_status_stop = 0x00040000
					};

					/**
					 * ��ʾ���������
					 * @author f
					 * @version 1.0
					 * @created 19-7��-2018 20:11:50
					 */
					enum csf_task_type
					{
						/**
						 * ��ʾδ֪������״ֵ̬
						 */
						csf_task_type_none = 0x00000000,
						/**
						 * ��ʾִֻ��һ�ε�����״ֵ̬
						 */
						csf_task_type_once = 0x00010000,
						/**
						 * ��ʾѭ��ִ�е����񣬸���������ѭ����ȥ
						 */
						csf_task_type_loop = 0x00020000,
						/**
						 * ��ʾһ������ѭ��������������ڷ��ش���ʱ���ͻᱻɾ��
						 */
						csf_task_type_loop_broken = csf_task_type_loop | 0x00000100,
						/**
						 * ��ʾָ���������������ڼ�¼����
						 */
						csf_task_type_times = 0x00040000,
						/**
						 * ��ʾ����ʱ�������
						 */
						csf_task_type_time = 0x00080000
					};


					csf_task();
					virtual ~csf_task();

					/**
					 * ����task�����ͺ����ʹ���һ������
					 * 
					 * @param manager    ��ʾ����������ĵ�ַ
					 * @param type    ��ʾ������ֵ
					 * @param offset    ��ʾ������ʱ��
					 * @param interval    ����ִ�еļ��ʱ��
					 * @param callback    �����ִ�лص�����
					 * @param delete_callback    ����ɾ����ִ�лص�����
					 */
					csf_task(const csf_task_manager* manager, const csf_task_type type, const csf_time offset, const csf_time interval, const csf_task_callback callback, const csf_task_delete_callback delete_callback = csf_null);
					/**
					 * ��ʾ�����������ֵ
					 */
					inline csf_task_type get_type() {

						return m_type;
					}
					/**
					 * ��ʾ�����������ֵ
					 * 
					 * @param newVal
					 */
					inline void set_type(const csf_task_type newVal) {

						m_type = newVal;
					}
					/**
					 * ��ʾ�����״̬��ֵ
					 */
					inline csf::core::utils::task::csf_task::csf_task_status get_status() {

						return m_status;
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
					 * ��ʾ�����״̬��ֵ
					 * 
					 * @param newVal
					 */
					inline void set_status(const csf::core::utils::task::csf_task::csf_task_status newVal) {

						m_status = newVal;
					}
					/**
					 * ��ʾ����Ļص�����
					 */
					inline csf::core::utils::task::csf_task_callback get_callback() {

						return m_callback;
					}
					/**
					 * �ж��Ƿ���Ҫɾ�������is_delete����true��ɾ��task��
					 */
					virtual csf_bool is_delete();
					/**
					 * ��ʾ����Ļص�����
					 * 
					 * @param newVal
					 */
					inline void set_callback(const csf::core::utils::task::csf_task_callback newVal) {

						m_callback = newVal;
					}
					/**
					 * ��ʾ����ɾ����Ļص�����
					 */
					inline csf::core::utils::task::csf_task_delete_callback get_delete_callback() {

						return m_delete_callback;
					}
					/**
					 * ��ʾ����ɾ����Ļص�����
					 * 
					 * @param newVal
					 */
					inline void set_delete_callback(const csf::core::utils::task::csf_task_delete_callback newVal) {

						m_delete_callback = newVal;
					}
					/**
					 * ��ʾ��ǰ��ʱ��ؼ���ֵ������ǰʱ��
					 */
					inline csf_uint64 get_time() {

						return m_time;
					}
					/**
					 * ��ʾ��ǰ��ʱ��ؼ���ֵ������ǰʱ��
					 * 
					 * @param newVal
					 */
					inline void set_time(const csf_uint64 newVal) {

						m_time = newVal;
					}
					/**
					 * ��ʾ��һ��ִ�е�ƫ��ʱ��
					 */
					inline csf_uint64 get_offset() {

						return m_offset;
					}
					/**
					 * ��ʾ��һ��ִ�е�ƫ��ʱ��
					 * 
					 * @param newVal
					 */
					inline void set_offset(const csf_uint64 newVal) {

						m_offset = newVal;
					}
					/**
					 * ָ��һ���������
					 * 
					 * @param newVal
					 */
					inline void set_task(const csf_task* newVal) {

						m_task = newVal;
					}
					/**
					 * ָ��һ��װ���߶���
					 */
					inline csf_task* get_decorator() {

						return m_decorator;
					}
					/**
					 * ��ʾ�����ִ�м��ʱ��
					 */
					inline csf_uint64 get_interval() {

						return m_interval;
					}
					/**
					 * ָ��һ��װ���߶���
					 * 
					 * @param newVal
					 */
					inline void set_decorator(const csf_task* newVal) {

						m_decorator = newVal;
					}
					/**
					 * ��ʾ�����ִ�м��ʱ��
					 * 
					 * @param newVal
					 */
					inline void set_interval(const csf_uint64 newVal) {

						m_interval = newVal;
					}
					/**
					 * ��ʾ�������������������
					 */
					csf_task_manager* get_task_manager();
					/**
					 * ��ʾ�������������������
					 * 
					 * @param newVal
					 */
					void set_task_manager(const csf_task_manager* newVal);
					/**
					 * ��ʾ����ӿڣ���ֻ��is_delete����true�����process_delete��
					 */
					virtual csf_int32 process_delete();

				private:
					/**
					 * ��ʾ�����������ֵ
					 */
					csf_task_type m_type = csf_task_type_none;
					/**
					 * ��ʾ�����״̬��ֵ
					 */
					csf::core::utils::task::csf_task::csf_task_status m_status = csf_task_status_none;
					/**
					 * ��ʾ����Ļص�����
					 */
					csf::core::utils::task::csf_task_callback m_callback = csf_null;
					/**
					 * ��ʾ����ɾ����Ļص�����
					 */
					csf::core::utils::task::csf_task_delete_callback m_delete_callback = csf_null;
					/**
					 * ��ʾ��ǰ��ʱ��ؼ���ֵ������ǰʱ�䣬��λ����
					 */
					csf_uint64 m_time = 0;
					/**
					 * ��ʾ��һ��ִ�е�ƫ��ʱ�䣬��λ����
					 */
					csf_uint64 m_offset = 0;
					/**
					 * ָ��һ��װ���߶���
					 */
					csf_task* m_decorator = csf_null;
					/**
					 * ��ʾ�����ִ�м��ʱ�䣬��λ����
					 */
					csf_uint64 m_interval = 0;
					/**
					 * ��ʾ�������������������
					 */
					csf_task_manager* m_task_manager = csf_null;
					/**
					 * ��ʾ���������������
					 */
					csf::core::utils::task::csf_task_manager *m_task_manager;

				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_INCLUDED_)
