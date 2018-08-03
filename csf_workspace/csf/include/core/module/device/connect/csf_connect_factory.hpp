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
*Date: 28-7��-2018 14:23:34
*
*Description: Class(csf_connect_factory) ��ʾ���Ӵ���������
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
			namespace connect
			{
				/**
				 * ��ʾ���Ӵ���������
				 * @author f
				 * @version 1.0
				 * @created 28-7��-2018 14:23:34
				 */
				class csf_connect_factory : public csf::core::module::csf_device, public csf::core::module::connect::csf_connect_factory_interface
				{

				public:
					inline explicit csf_connect_factory() {

					}

					/**
					* ��ʾ���������ļ������ʹ����豸ģ��
					*
					* @param configure_manager    ��ʾ�����ļ�����
					* @param type    ��ʾģ�������
					*/
					inline explicit csf_connect_factory(const csf_configure_manager * configure_manager)

						: csf_device(configure_manager, csf_device_type_connect) {

					}

					/**
					* ��ʾ���������ļ������ʹ����豸ģ��
					*
					* @param configure_manager    ��ʾ�����ļ�����
					* @param type    ��ʾģ�������
					*/
					inline explicit csf_connect_factory(const csf_configure_manager * configure_manager
						, const csf::core::module::csf_device::csf_device_type type) 
					
						: csf_device(configure_manager, type) {

					}

					inline virtual ~csf_connect_factory() {

					}

					/**
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 del(csf_element& element, csf_device_operation_callback callback);
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
					 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 */
					virtual csf_connect* create(const csf_connect::csf_connect_type type);
					/**
					 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
					 */
					virtual csf_connect* create(const csf_connect::csf_connect_type type, const csf_url& local_url);
					/**
					 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
					 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
					 */
					virtual csf_connect* create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
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
					csf::core::module::connect::csf_connect_factory_manager *m_connect_factory_manager;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_INCLUDED_)
