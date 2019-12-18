/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_linux_platform.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:42
*
*Description: Class(csf_linux_platform)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_LINUX_PLATFORM_INCLUDED_)
#define CSF_LINUX_PLATFORM_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_platform.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace platform
			{
				/**
				 * ��ʾlinuxϵͳ����
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:42
				 */
				class csf_linux_platform : public csf::core::system::platform::csf_platform
				{

				public:
					csf_linux_platform();
					virtual ~csf_linux_platform();

					inline csf::core::system::csf_configure_manager get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 
					 * @param new_value
					 */
					inline csf::core::base::csf_void set_configure_manager(csf::core::system::csf_configure_manager new_value) {

						m_configure_manager = newVal;
					}
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
#endif // !defined(CSF_LINUX_PLATFORM_INCLUDED_)