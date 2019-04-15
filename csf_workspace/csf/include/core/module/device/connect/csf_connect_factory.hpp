/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:37
*
*Description: Class(csf_connect_factory) ��ʾ���Ӵ���������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_H_INCLUDED_)
#define CSF_CONNECT_FACTORY_H_INCLUDED_

//#include "csf_connect_factory_manager.hpp"
#include "csf_csfmap.hpp"
#include "csf_connect_factory_interface.hpp"
#include "csf_connect_timeout_manager.hpp"
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
				 * @created 01-10��-2018 12:54:37
				 */
				class csf_connect_factory : public csf::core::module::csf_device
					, public csf::core::module::connect::csf_connect_factory_interface
				{

				public:
					csf_connect_factory();
					virtual ~csf_connect_factory();

					/**
					 * ��ʾ���������ļ������ʹ����豸ģ��
					 * 
					 * @param configure_manager    ��ʾ�����ļ�����
					 * @param type    ��ʾģ�������
					 */
					inline explicit csf_connect_factory(const csf_configure_manager * configure_manager
						, const csf_device_type type)
						: csf_device(configure_manager, type)
						, m_connect_factory_manager(csf_nullptr) {

					}

					/**
					* ��ʾ���������ļ������ʹ����豸ģ��
					*
					* @param configure_manager    ��ʾ�����ļ�����
					* @param type    ��ʾģ�������
					* @param cfm    ��ʾ���繤����������ָ��
					*/
					inline explicit csf_connect_factory(const csf_configure_manager * configure_manager
						, const csf_device_type type
						, const csf::core::module::connect::csf_connect_factory_manager* cfm)
						: csf_device(configure_manager, type)
						, m_connect_factory_manager((csf::core::module::connect::csf_connect_factory_manager*)cfm) {

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
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
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
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
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
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type);
					/**
					 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
					 */
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url);
					/**
					 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
					 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
					 */
					virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
					/**
					 * ��ʾ�����������ӣ����ٳɹ�����0��ʧ�ܷ���<0����ֵ��
					 * 
					 * @param connect    ��ʾ��Ҫ���ٵ�����
					 */
					virtual csf_int32 destroy(const csf_connect_ptr connect);
					/**
					* ��ʾ�������ӹ��������Ĺ���������
					*/
					inline csf::core::module::connect::csf_connect_factory_manager * get_connect_factory_manager() {

						return m_connect_factory_manager;
					}
					/**
					* ��ʾ�������ӹ��������Ĺ���������
					*
					* @param new_value
					*/
					inline csf_void set_connect_factory_manager(csf::core::module::connect::csf_connect_factory_manager * new_value) {

						m_connect_factory_manager = new_value;
					}
					/**
					* ��ʾ���ӳ�ʱ����������Ҫ����������Ӷ���ĳ�ʱ���⡣
					*/
					inline csf::core::module::connect::csf_connect_timeout_manager& get_timeout_manager() {

						return m_timeout_manager;
					}
					/**
					* ��ʾ�������д��������Ӷ���
					*/
					inline csf_csfmap<csf_connect*, csf_connect_ptr>& get_connect_collector() {

						return m_connect_collector;
					}
					/**
					* ��Ҫ�����ǣ����һ�����Ӷ���
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param connect_ptr    ��ʾ���Ӷ���
					*/
					inline virtual csf::core::base::csf_int32 insert(csf_connect_ptr& connect_ptr) {

						get_connect_collector().insert(connect_ptr.get(), connect_ptr);

						return csf_succeed;
					}
					/**
					* ��Ҫ�����ǣ�ɾ��һ�����Ӷ���
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param connect_ptr    ��ʾ���Ӷ���
					*/
					inline csf::core::base::csf_int32 remove(csf_connect_ptr& connect_ptr) {

						get_connect_collector().remove(connect_ptr.get());
						get_timeout_manager().remove(connect_ptr->get_read_timeout());
						get_timeout_manager().remove(connect_ptr->get_write_timeout());

						return csf_succeed;
					}
					/**
					* ��Ҫ�����ǣ�
					*    ���Ҹ����Ӷ����Ƿ����
					* ���أ�
					*    csf_true����ʾ���ڣ�
					*    csf_false����ʾ�����ڣ�
					*
					* @param connect_ptr    ��ʾ���Ӷ���
					*/
					inline csf_bool is_exist(csf_connect_ptr& connect_ptr) {

						return get_connect_collector().have_key(connect_ptr.get());
					}
				private:
					/**
					 * ��ʾ���ӹ��������������ַ
					 */
					csf::core::module::connect::csf_connect_factory_manager *m_connect_factory_manager = csf_nullptr;
					/**
					* ��ʾ���ӳ�ʱ����������Ҫ�������ӵĳ�ʱ����
					*/
					csf::core::module::connect::csf_connect_timeout_manager m_timeout_manager;
					/**
					* ��ʾ�������д��������Ӷ���
					*/
					csf_csfmap<csf_connect*, csf_connect_ptr> m_connect_collector;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_H_INCLUDED_)
