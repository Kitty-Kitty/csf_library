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

#if !defined(TEST_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
#define TEST_CONNECT_FACTORY_MANAGER_H_INCLUDED_

#include "csf_device.hpp"

namespace csf
{
	namespace example
	{
		/**
		 * ��Ҫ�������ڲ���connect factory manager �е��Զ����ù���
		 * @author f
		 * @version 1.0
		 * @created 08-10��-2018 20:52:07
		 */
		class test_connect_factory_manager : public csf::core::module::csf_device
		{

		public:
			test_connect_factory_manager();
			virtual ~test_connect_factory_manager();

			/**
			* ��ʾ���������ļ������ʹ����豸ģ��
			*
			* @param configure_manager    ��ʾ�����ļ�����
			* @param type    ��ʾģ�������
			*/
			inline explicit test_connect_factory_manager(const csf_configure_manager * configure_manager)
				: csf_device(configure_manager, csf_device_type_test) {

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

		};

	}

}
#endif // !defined(TEST_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
