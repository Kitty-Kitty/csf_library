/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_device_configure_interface.hpp
*
*Version: 1.0
*
*Date: 04-10��-2018 21:15:02
*
*Description: Interface(csf_device_configure_interface) ��ʾ�豸�����ò����ӿ�
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DEVICE_CONFIGURE_INTERFACE_H_INCLUDED_)
#define CSF_DEVICE_CONFIGURE_INTERFACE_H_INCLUDED_

#include "csf_base_include.h"
#include "csf_element.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾ�豸�����ò����ӿ�
			 * @author f
			 * @version 1.0
			 * @created 04-10��-2018 21:15:02
			 */
			class csf_device_configure_interface
			{

			public:
				csf_device_configure_interface() {

				}

				virtual ~csf_device_configure_interface() {

				}

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
				virtual csf_int32 configure(const csf::core::system::csf_element& element) = 0;

			};

		}

	}

}
#endif // !defined(CSF_DEVICE_CONFIGURE_INTERFACE_H_INCLUDED_)
