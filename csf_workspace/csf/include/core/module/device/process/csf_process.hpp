/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_process.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:47
*
*Description: Class(csf_process)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_PROCESS_INCLUDED_)
#define CSF_PROCESS_INCLUDED_

#include "csf_process_interface.hpp"
#include "csf_device.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * ��ʾ������̳���
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6��-2018 17:28:47
				 */
				class csf_process : public csf::core::module::csf_device, public csf::core::module::device::csf_process_interface
				{

				public:
					csf_process();
					virtual ~csf_process();
					/**
					* ��ʾ���������ļ������ʹ����豸ģ��
					*
					* @param configure_manager    ��ʾ�����ļ�����
					* @param type    ��ʾģ�������
					*/
					inline explicit csf_process(const csf_configure_manager * configure_manager
						, const csf::core::module::csf_device::csf_device_type type)
						: csf_device(configure_manager, type) {

					}
					/**
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 del(csf_element& element, csf_device_operation_callback callback);
					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 ctrl(csf_element& element, csf_device_operation_callback callback);
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
					/**
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 update(csf_element& element, csf_device_operation_callback callback);
					/**
					 * ��ʾ�豸����Ӳ���
					 * 
					 * @param element    ��ʾ�豸��Ӳ���
					 * @param callback    ��ʾ�豸�����Ļص�����
					 */
					virtual csf_int32 add(csf_element& element, csf_device_operation_callback callback);

				};

			}

		}

	}

}
#endif // !defined(CSF_PROCESS_INCLUDED_)
