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
*Date: 18-7��-2018 22:31:08
*
*Description: Class(csf_manager) ��ʾ����������
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MANAGER_INCLUDED_)
#define CSF_MANAGER_INCLUDED_

#include "csf_manager_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾ����������
			 * @author f
			 * @version 1.0
			 * @created 18-7��-2018 22:31:08
			 */
			class csf_manager : public csf::core::module::csf_manager_interface
			{

			public:
				inline explicit csf_manager()
					: m_configure_manager(csf_nullptr) {

				}
				inline virtual ~csf_manager() {

				}

				/**
				 * �������ù���������һ���������
				 * 
				 * @param configure_manager    ��ʾ���ù�������ַ��Ϣ
				 */
				inline explicit csf_manager(const csf_configure_manager* configure_manager)
					: m_configure_manager((csf_configure_manager*)configure_manager) {

				}
				/**
				 * ��ʾ����������
				 */
				inline csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * ��ʾ����������
				 * 
				 * @param new_value
				 */
				inline void set_configure_manager(const csf_configure_manager* new_value) {

					m_configure_manager = (csf_configure_manager*)new_value;
				}
				/**
				 * ģ���ʼ��
				 * 
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * ģ������
				 * 
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * ģ��ֹͣ
				 * 
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);

			private:
				/**
				 * ��ʾ����������
				 */
				csf_configure_manager* m_configure_manager = csf_nullptr;

			};

		}

	}

}
#endif // !defined(CSF_MANAGER_INCLUDED_)
