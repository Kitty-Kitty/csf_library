/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_factory.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:37
*
*Description: Class(csf_connect_factory)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_INCLUDED_)
#define CSF_CONNECT_FACTORY_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_connect_factory_manager.hpp"
#include "csf_connect_factory_interface.hpp"
#include "csf_device.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:37
				 */
				class csf_connect_factory : public csf::core::module::device::csf_device, public csf::core::module::device::csf_connect_factory_interface
				{

				public:
					csf_connect_factory();
					virtual ~csf_connect_factory();

					/**
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 del(csf_element& element, csf_device_operation_callback callback);
					inline csf::core::system::csf_configure_manager get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 ctrl(csf_element& element, csf_device_operation_callback callback);
					/**
					 * 
					 * @param new_value
					 */
					inline void set_configure_manager(csf::core::system::csf_configure_manager new_value) {

						m_configure_manager = newVal;
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
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 update(csf_element& element, csf_device_operation_callback callback);
					/**
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 add(csf_element& element, csf_device_operation_callback callback);
					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 */
					virtual csf_connect* create(const csf::core::module::device::csf_connect_type type);
					/**
					 * ģ������
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
					 */
					virtual csf_connect* create(const csf_connect_type type, const csf_url& local_url);
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
					 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
					 */
					virtual csf_connect* create(const csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
					/**
					 * ��ʾ�����������ӣ����ٳɹ�����0��ʧ�ܷ���<0����ֵ��
					 * 
					 * @param connect    ��ʾ��Ҫ���ٵ�����
					 */
					virtual csf_int32 destroy(const csf_connect* connect);

				private:
					/**
					 * ��ʾ���ӹ��������������ַ
					 */
					csf::core::module::device::csf_connect_factory_manager *m_connect_factory_manager;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_INCLUDED_)
