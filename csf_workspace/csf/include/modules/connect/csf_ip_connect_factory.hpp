/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:43
*
*Description: Class(csf_ip_connect_factory) ��ʾip����ͨ�����ӹ�����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_FACTORY_H_INCLUDED_)
#define CSF_IP_CONNNECT_FACTORY_H_INCLUDED_

#include "csf_csfmap.hpp"
#include "csf_configure_manager.hpp"
#include "csf_connect_factory.hpp"
#include "csf_boost_asio.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾip����ͨ�����ӹ�����
			 * @author f
			 * @version 1.0
			 * @created 01-10��-2018 12:54:43
			 */
			class csf_ip_connect_factory : public csf::core::module::connect::csf_connect_factory
			{

			public:
				csf_ip_connect_factory();
				virtual ~csf_ip_connect_factory();
				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				* @param type    ��ʾģ�������
				*/
				inline explicit csf_ip_connect_factory(const csf_configure_manager * configure_manager
					, const csf_device_type type)
					: csf_connect_factory(configure_manager, type) {

				}
				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				* @param type    ��ʾģ�������
				* @param cfm    ��ʾ���繤����������ָ��
				*/
				inline explicit csf_ip_connect_factory(const csf_configure_manager * configure_manager
					, const csf_device_type type
					, const csf_connect_factory_manager* cfm)
					: csf_connect_factory(configure_manager, type, cfm) {

				}
				/**
				 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
				 * 
				 * @param type    ��ʾ��������
				 */
				virtual csf_connect_ptr create(const csf_connect::csf_connect_type type);
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
				 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
				 * 
				 * @param type    ��ʾ��������
				 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
				 */
				virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url);
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
				 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
				 * 
				 * @param type    ��ʾ��������
				 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
				 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
				 */
				virtual csf_connect_ptr create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
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
				 * ��ʾ�����������ӣ����ٳɹ�����0��ʧ�ܷ���<0����ֵ��
				 * 
				 * @param connect_ptr    ��ʾ��Ҫ���ٵ�����
				 */
				inline virtual csf_int32 destroy(const csf_connect_ptr connect_ptr) {

					get_connect_collector().remove(connect_ptr.get());

					return 0;
				}
				/**
				* ��ʾboost��io_service����
				*/
				inline boost::asio::io_service& get_io_service() {

					return m_io_service;
				}
			protected:
				/**
				* ��Ҫ�����ǣ���ʾ���������ӹ������в����������Ӷ���
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				*
				* @param connect_ptr    ��ʾ��Ҫ��ӵ��������Ӷ���
				*/
				inline csf::core::base::csf_int32 insert(csf_connect_ptr connect_ptr) {

					if (!connect_ptr) {
						return csf_failure;
					}

					get_connect_collector().insert(connect_ptr.get(), connect_ptr);

					return csf_success;
				}
				/**
				* ��Ҫ�����ǣ���ʾ���������ӹ�������ɾ���������Ӷ���
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				*
				* @param connect_ptr    ��ʾ��Ҫ��ӵ��������Ӷ���
				*/
				inline csf::core::base::csf_int32 remove(csf_connect_ptr connect_ptr) {

					if (!connect_ptr) {
						return csf_failure;
					}

					get_connect_collector().erase(connect_ptr.get());

					return csf_success;
				}
				/**
				* ��Ҫ�����ǣ���ʾ����������ӹ����������е��������Ӷ���
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				*/
				inline csf::core::base::csf_int32 clear() {

					get_connect_collector().clear();

					return csf_success;
				}
			private:
				/**
				* ��ʾ�������ӹ�����
				*/
				inline csf_csfmap<csf_connect*, csf_connect_ptr>& get_connect_collector() {

					return m_connect_collector;
				}
				/**
				* ��ʾ�������ӹ�����
				*/
				csf_csfmap<csf_connect*, csf_connect_ptr> m_connect_collector;
				/**
				* ��ʾboost��io_service����
				*/
				boost::asio::io_service m_io_service;
			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_FACTORY_H_INCLUDED_)
