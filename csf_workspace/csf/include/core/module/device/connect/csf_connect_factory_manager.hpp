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
*Description: Class(csf_connect_factory_manager) ��ʾ���ӹ���������
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_MANAGER_INCLUDED_)
#define CSF_CONNECT_FACTORY_MANAGER_INCLUDED_

#include "csf_connect_factory_manager_interface.hpp"
#include "csf_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * ��ʾ���ӹ���������
				 * @author f
				 * @version 1.0
				 * @created 28-7��-2018 14:23:34
				 */
				class csf_connect_factory_manager : public csf::core::module::csf_manager, public csf::core::module::connect::csf_connect_factory_manager_interface
				{

				public:
					csf_connect_factory_manager();
					virtual ~csf_connect_factory_manager();

					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ģ������
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_MANAGER_INCLUDED_)
