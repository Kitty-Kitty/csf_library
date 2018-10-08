/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_factory_manager_interface.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:38
*
*Description: Interface(csf_connect_factory_manager_interface) 
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_MANAGER_INTERFACE_H_INCLUDED_)
#define CSF_CONNECT_FACTORY_MANAGER_INTERFACE_H_INCLUDED_

#include "csf_configure_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:38
				 */
				class csf_connect_factory_manager_interface
				{

				public:
					csf_connect_factory_manager_interface() {

					}

					virtual ~csf_connect_factory_manager_interface() {

					}
					/**
					* ��Ҫ�����ǣ���ʼ��ģ�������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param conf_mg    ��ʾ�����ļ���Ϣ
					* @param app    ��ʾ��ģ��������app�����ַ
					*/
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg, const csf_app* app) = 0;
					/**
					* ��Ҫ�����ǣ�����ģ�������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param conf_mg    ��ʾ�����ļ���Ϣ
					* @param app    ��ʾ��ģ��������app�����ַ
					*/
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg, const csf_app* app) = 0;
					/**
					* ��Ҫ�����ǣ�ֹͣģ�������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param conf_mg    ��ʾ�����ļ���Ϣ
					*/
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr) = 0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_MANAGER_INTERFACE_H_INCLUDED_)
