/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_manager_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7��-2018 16:58:58
*
*Description: Interface(csf_module_manager_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_MANAGER_INTERFACE_INCLUDED_)
#define CSF_MODULE_MANAGER_INTERFACE_INCLUDED_

#include "csf_module.hpp"

using csf::core::module::csf_module;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾģ��������ӿ�
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7��-2018 16:58:58
			 */
			class csf_module_manager_interface
			{

			public:
				csf_module_manager_interface() {

				}

				virtual ~csf_module_manager_interface() {

				}

				/**
				 * ����ģ�������
				 * ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
				 * 
				 * @param name    ��ʾ��Ҫ������ģ������
				 */
				virtual csf_module * create(const csf_string& name) =0;
				/**
				 * ����ģ�������
				 * ���أ�0��ʾ��ȷ��<0��ʾ�����룻
				 * 
				 * @param module    ��ʾ��Ҫ���ٵ�ģ���ַ
				 */
				virtual csf_int32 destory(const csf_module * module) =0;
				/**
				 * ����ģ�������
				 * ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
				 * 
				 * @param name    ��ʾ��Ҫ������ģ������
				 */
				virtual csf_module * create(const csf_char* name) =0;
				/**
				 * ����ģ�������
				 * ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
				 * 
				 * @param type    ��ʾ��Ҫ������ģ������
				 */
				virtual csf_module * create(const csf_module::csf_module_type type) =0;

			};

		}

	}

}
#endif // !defined(CSF_MODULE_MANAGER_INTERFACE_INCLUDED_)
