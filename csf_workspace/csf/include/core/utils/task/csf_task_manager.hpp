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
*Date: 19-7��-2018 20:11:51
*
*Description: Class(csf_task_manager) ��ʾ���������
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_MANAGER_INCLUDED_)
#define CSF_TASK_MANAGER_INCLUDED_

#include "csf_module.hpp"
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
				 * ��ʾ���������
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:51
				 */
				class csf_task_manager : public csf::core::module::csf_module
				{

				public:
					csf_task_manager();
					virtual ~csf_task_manager();

					/**
					 * ��ʾ������Ϣ
					 */
					inline csf_configure_manager* get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ������Ϣ
					 * 
					 * @param newVal
					 */
					inline csf::core::base::csf_void set_configure_manager(const csf_configure_manager* newVal) {

						m_configure_manager = (csf_configure_manager*)newVal;
					}
					/**
					 * ģ������
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ�����������״̬��Ϣ
					 */
					inline csf::core::utils::task::csf_task::csf_task_status get_status() {

						return m_status;
					}
					/**
					 * ��ʾ�����������״̬��Ϣ
					 * 
					 * @param newVal
					 */
					inline void set_status(const csf::core::utils::task::csf_task::csf_task_status newVal) {

						m_status = newVal;
					}

				private:
					/**
					 * ��ʾ������Ϣ
					 */
					csf_configure_manager* m_configure_manager = csf_null;
					/**
					 * ��ʾ�����������״̬��Ϣ
					 */
					csf::core::utils::task::csf_task::csf_task_status m_status = csf::core::utils::task::csf_task::csf_task_status::csf_task_status_none;

				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_MANAGER_INCLUDED_)
