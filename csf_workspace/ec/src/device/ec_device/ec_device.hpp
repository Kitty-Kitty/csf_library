/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: ec_device.hpp
*
*Version: 1.0
*
*Date: 08-10��-2018 20:52:07
*
*Description: Class(ec_device) ��Ҫ�������ڲ���connect factory manager �е��Զ����ù���
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(EC_DEVICE_H_INCLUDED_)
#define EC_DEVICE_H_INCLUDED_

#include "csf_device.hpp"

namespace csf
{
	namespace device
	{
		#define		csf_ec_version				1000000
		#define		CSF_EC_VERSION				"V1.0.0"
		#define		CSF_EC_VAR					"ec_device"
		#define		CSF_EC_VER					CSF_EC_VAR "/" CSF_EC_VERSION

		/**
		 * ��Ҫ�������ڲ���connect factory manager �е��Զ����ù���
		 * @author f
		 * @version 1.0
		 * @created 08-10��-2018 20:52:07
		 */
		class ec_device : public csf::core::module::csf_device
		{

		public:
			/**
			* ��ʾ���������ļ������ʹ����豸ģ��
			*
			* @param configure_manager    ��ʾ�����ļ�����
			* @param type    ��ʾģ�������
			*/
			inline explicit ec_device(const csf_configure_manager * configure_manager)
				: csf_device(configure_manager, csf_device_type_general_extend) {

				set_version(
					csf_ec_version
					, CSF_EC_VER
					, CSF_EC_VAR
					, "ec device"
				);

			}

			virtual ~ec_device();

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
		};

	}

}
#endif // !defined(EC_DEVICE_H_INCLUDED_)
