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
*Date: 28-7��-2018 14:23:34
*
*Description: Interface(csf_connect_factory_manager_interface) 
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_MANAGER_INTERFACE_INCLUDED_)
#define CSF_CONNECT_FACTORY_MANAGER_INTERFACE_INCLUDED_

#include "csf_typedef.h"
#include "csf_configure_manager.hpp"

using namespace csf::core::base;

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
				 * @created 28-7��-2018 14:23:34
				 */
				class csf_connect_factory_manager_interface
				{

				public:
					csf_connect_factory_manager_interface() {

					}

					virtual ~csf_connect_factory_manager_interface() {

					}

					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null) =0;
					/**
					 * ģ������
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null) =0;
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_MANAGER_INTERFACE_INCLUDED_)
