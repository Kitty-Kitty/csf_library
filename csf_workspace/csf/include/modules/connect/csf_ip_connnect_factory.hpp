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
*Date: 29-7��-2018 15:13:09
*
*Description: Class(csf_ip_connnect_factory) ��ʾip����ͨ�����ӹ�����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_FACTORY_INCLUDED_)
#define CSF_IP_CONNNECT_FACTORY_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_connect_factory.hpp"

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
			 * @created 29-7��-2018 15:13:09
			 */
			class csf_ip_connnect_factory : public csf::core::module::connect::csf_connect_factory
			{

			public:
				explicit csf_ip_connnect_factory() {

				}

				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				*/
				explicit csf_ip_connnect_factory(const csf_configure_manager * configure_manager)

					: csf_connect_factory(configure_manager) {

				}

				virtual ~csf_ip_connnect_factory() {

				}

				/**
				 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
				 *
				 * @param type    ��ʾ��������
				 */
				virtual csf_connect* create(const csf::core::module::connect::csf_connect::csf_connect_type type);
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
				 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
				 *
				 * @param type    ��ʾ��������
				 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
				 */
				virtual csf_connect* create(const csf::core::module::connect::csf_connect::csf_connect_type type, const csf_url& local_url);
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
				 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
				 *
				 * @param type    ��ʾ��������
				 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
				 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
				 */
				virtual csf_connect* create(const csf::core::module::connect::csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url);
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
				 * ��ʾ�����������ӣ����ٳɹ�����0��ʧ�ܷ���<0����ֵ��
				 *
				 * @param connect    ��ʾ��Ҫ���ٵ�����
				 */
				virtual csf_int32 destroy(const csf_connect* connect);

			};

		}

	}

}


/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* ��ʾģ���create �� destroy ������塣                                              */
/* ÿ����Ҫͨ��ģ�鹤��������ģ�鶼��Ҫ��Ӹú궨�塣                                    */
/* ����module_type��ʾ��ģ��������ƣ�����ʵ���˹��췽��Ϊ��                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(csf::modules::connect::csf_ip_connnect_factory)


#endif // !defined(CSF_IP_CONNNECT_FACTORY_INCLUDED_)
