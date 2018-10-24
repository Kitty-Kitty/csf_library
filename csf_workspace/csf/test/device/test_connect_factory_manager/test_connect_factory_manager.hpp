/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: test_connect_factory_manager.hpp
*
*Version: 1.0
*
*Date: 08-10��-2018 20:52:07
*
*Description: Class(test_connect_factory_manager) ��Ҫ�������ڲ���connect factory manager �е��Զ����ù���
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(TEST_TEST_FACTORY_MANAGER_H_INCLUDED_)
#define TEST_TEST_FACTORY_MANAGER_H_INCLUDED_

#include "csf_device.hpp"
#include "csf_connect.hpp"

namespace csf
{
	namespace example
	{
#define		csf_test_version				1000000
#define		CSF_TEST_VERSION				"v1.0.0"
#define		CSF_TEST_VAR					"csf_ip_connect_factory"
#define		CSF_TEST_VER					CSF_TEST_VAR "/" CSF_TEST_VERSION

		/**
		 * ��Ҫ�������ڲ���connect factory manager �е��Զ����ù���
		 * @author f
		 * @version 1.0
		 * @created 08-10��-2018 20:52:07
		 */
		class test_connect_factory_manager : public csf::core::module::csf_device
		{

		public:
			/**
			* ��ʾ���������ļ������ʹ����豸ģ��
			*
			* @param configure_manager    ��ʾ�����ļ�����
			* @param type    ��ʾģ�������
			*/
			inline explicit test_connect_factory_manager(const csf_configure_manager * configure_manager)
				: csf_device(configure_manager, csf_device_type_test) {

				set_version(
					csf_test_version
					, CSF_TEST_VER
					, CSF_TEST_VAR
					, "test connect factory manager"
				);

			}

			virtual ~test_connect_factory_manager();

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
			/**
			* ��Ҫ�����ǣ�tcp���������ؽӿ�
			* ���أ�0��ʾ��������0��ʾ����
			*
			* @param connect    ��ʾ��ǰ���ڴ�������Ӷ���
			* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
			*/
			csf::core::base::csf_int32 tcp_handle(csf_connect* connect, csf_connect_error& connect_error);
			/**
			* ��Ҫ�����ǣ�udp���������ؽӿ�
			* ���أ�0��ʾ��������0��ʾ����
			*
			* @param connect    ��ʾ��ǰ���ڴ�������Ӷ���
			* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
			*/
			csf::core::base::csf_int32 udp_handle(csf_connect* connect, csf_connect_error& connect_error);
		};

	}

}
#endif // !defined(TEST_TEST_FACTORY_MANAGER_H_INCLUDED_)
