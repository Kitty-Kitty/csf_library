/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_configure_module.hpp
*
*Version: 1.0
*
*Date: 04-10��-2018 19:44:08
*
*Description: Class(csf_configure_module) ��Ҫ��ʾģ������ü������ඨ��
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONFIGURE_MODULE_H_INCLUDED_)
#define CSF_CONFIGURE_MODULE_H_INCLUDED_

#include "csf_module_manager.hpp"
#include "csf_element.hpp"
#include "csf_device_base.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * ��Ҫ��ʾģ������ü������ඨ��
			 * @author f
			 * @version 1.0
			 * @created 04-10��-2018 19:44:08
			 */
			class csf_configure_module
			{

			public:
				csf_configure_module();
				virtual ~csf_configure_module();

				/**
				* ��Ҫ�����ǣ�ͨ��������Ϣ����һ������ģ�����
				* ���أ���null��ʾģ������ַ��null��ʾʧ�ܣ�
				*
				* @param module_manager    ��ʾģ�������������Ϣ
				* @param element    ��ʾģ���������Ϣ��
				*
				* ģ��������Ϣ�ṹ���£�
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
				*
				*
				*/
				static csf::core::module::csf_device_base* create_module(csf::core::module::csf_module_manager& module_manager
					, csf::core::system::csf_element& element);

			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_MODULE_H_INCLUDED_)
