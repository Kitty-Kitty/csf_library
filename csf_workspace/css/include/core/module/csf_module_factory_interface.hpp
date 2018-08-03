/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7��-2018 16:49:58
*
*Description: Interface(csf_module_factory_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_FACTORY_INTERFACE_INCLUDED_)
#define CSF_MODULE_FACTORY_INTERFACE_INCLUDED_

#include "csf_interface.hpp"
#include "csf_module.hpp"

using namespace csf::core::module;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾģ�鴴�������Ĳ����ӿ�
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7��-2018 16:49:58
			 */
			class csf_module_factory_interface : public csf::core::module::csf_interface
			{

			public:
				csf_module_factory_interface() {

				}

				virtual ~csf_module_factory_interface() {

				}

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
				 * @param configure_manager    ��ʾģ�����������Ϣ
				 */
				virtual csf_module * create(const csf_configure_manager * configure_manager) =0;

			};

		}

	}

}
#endif // !defined(CSF_MODULE_FACTORY_INTERFACE_INCLUDED_)
