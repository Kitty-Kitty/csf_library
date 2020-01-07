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
		#define		CSF_TEST_VERSION				"V1.0.0"
		#define		CSF_TEST_VAR					"test_connect_factory_manager"
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
			* @param connect_ptr    ��ʾ��ǰ���ڴ�������Ӷ���
			* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
			*/
			csf::core::base::csf_int32 tcp_handle(csf_connect_ptr connect_ptr, csf_connect_error& connect_error);
			/**
			* ��Ҫ�����ǣ�udp���������ؽӿ�
			* ���أ�0��ʾ��������0��ʾ����
			*
			* @param connect_ptr    ��ʾ��ǰ���ڴ�������Ӷ���
			* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
			*/
			csf::core::base::csf_int32 udp_handle(csf_connect_ptr connect_ptr, csf_connect_error& connect_error);
			/**
			* ��Ҫ�����ǣ�tcp�����ݷ��غ���
			* ���أ����ڵ���0��ʾ�ɹ���С��0��ʾ����
			*
			* @param connect_ptr    ��ʾ��ǰ���ڴ�������Ӷ���
			* @param connect_buffer
			* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
			*/
			csf::core::base::csf_int32 read_handle(
				csf_connect_ptr connect_ptr
				, csf_connect_error& connect_error
				, csf_connect_buffer<csf_buffer>& connect_buffer
				);
			/**
			* ��Ҫ�����ǣ�tcp�����ݷ��غ���
			* ���أ����ڵ���0��ʾ�ɹ���С��0��ʾ����
			*
			* @param connect_ptr    ��ʾ��ǰ���ڴ�������Ӷ���
			* @param connect_buffer
			* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
			*/
			csf::core::base::csf_int32 tcp_read_handle(csf_connect_ptr connect_ptr
				, csf_connect_error& connect_error
				, csf_int32 len);
			/**
			* ��Ҫ�����ǣ���Ҫʵ��ģ���������Ϣ����ӿڡ�
			* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
			*
			* @param element    ��ʾģ���������Ϣ
			*
			* ���õ�������Ϣ����ṹΪ��
			* <!--***�ò�������ģ��������Ϣ���Ǳ������õ���������***-->
			* <module>
			*        <!--***��ʾģ���Ӧ��ģ��������Ϣ***-->
			*        <name>csf_connection</name>
			*        <!--***��ʾ���豸ģ���Ψһ��ʶ�ַ��������ַ�������ӦС�ڵ���64�ֽ�***-->
			*        <mid>02000000-0000001</mid>
			*        <!--��ʾ��ģ���������Ϣ����Ҫ��ģ���configure�ӿڴ�����ģ���������������ģ��Ӧ��ģ��ȷ��-->
			*        <configure>
			*                <!--��ʾ�߳�����-->
			*                <thread_number>4</thread_number>
			*        </configure>
			* </module>
			*/
			virtual csf_int32 configure(const csf_element& element);
		private:
			/**
			* ��ʾ��ȡ������ʹ�õĻص���������
			*/
			csf_connect_callback m_read_function = csf_nullptr;
			/**
			* ��ʾд������ʹ�õĻص���������
			*/
			csf_connect_callback m_write_function = csf_nullptr;
			/**
			* ��ʾģ��ʹ�õ����ӹ���������
			*/
			csf_connect_factory* m_connect_factory = csf_nullptr;
			/**
			* ��ʾ��ȡ������ʹ�õĻص���������
			*/
			inline csf_connect_callback& get_read_function() {

				return m_read_function;
			}
			/**
			* ��ʾ��ȡ������ʹ�õĻص���������
			*
			* @param new_value
			*/
			inline void set_read_function(csf_connect_callback new_value) {

				m_read_function = new_value;
			}
			/**
			* ��ʾд������ʹ�õĻص���������
			*/
			inline csf_connect_callback& get_write_function() {

				return m_write_function;
			}
			/**
			* ��ʾд������ʹ�õĻص���������
			*
			* @param new_value
			*/
			inline void set_write_function(csf_connect_callback new_value) {

				m_write_function = new_value;
			}
			/**
			* ��ʾģ��ʹ�õ����ӹ���������
			*/
			inline csf_connect_factory* get_connect_factory() {

				return m_connect_factory;
			}
			/**
			* ��ʾģ��ʹ�õ����ӹ���������
			*
			* @param new_value
			*/
			inline void set_connect_factory(csf_connect_factory* new_value) {

				m_connect_factory = new_value;
			}
		};

	}

}
#endif // !defined(TEST_TEST_FACTORY_MANAGER_H_INCLUDED_)
