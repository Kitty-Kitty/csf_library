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
*Date: 24-7��-2018 22:17:27
*
*Description: Class(device_io) ��ʾ�豸�����豸���ݡ�
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(DEVICE_IO_INCLUDED_)
#define DEVICE_IO_INCLUDED_

#include "csf_device_io.hpp"

namespace test
{
	/**
	 * ��ʾ�豸�����豸���ݡ�
	 * @author f
	 * @version 1.0
	 * @created 24-7��-2018 22:17:27
	 */
	class device_io : public csf::core::module::device_io::csf_device_io
	{

	public:
		device_io();
		virtual ~device_io();

		/**
		 * ��ʾ�豸����Ӳ���
		 * 
		 * @param element    ��ʾ�豸��Ӳ���
		 * @param callback    ��ʾ�豸�����Ļص�����
		 */
		virtual csf_int32 del(const csf_element& element, const csf_device_operation_callback callback);
		/**
		 * ģ���ʼ��
		 * 
		 * @param conf_mg    ��ʾ�����ļ���Ϣ
		 */
		virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
		/**
		 * ��ʾ�豸����Ӳ���
		 * 
		 * @param element    ��ʾ�豸��Ӳ���
		 * @param callback    ��ʾ�豸�����Ļص�����
		 */
		virtual csf_int32 ctrl(const csf_element& element, const csf_device_operation_callback callback);
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
		/**
		 * ��ʾ�豸����Ӳ���
		 * 
		 * @param element    ��ʾ�豸��Ӳ���
		 * @param callback    ��ʾ�豸�����Ļص�����
		 */
		virtual csf_int32 update(const csf_element& element, const csf_device_operation_callback callback);
		/**
		 * ��ʾ�豸����Ӳ���
		 * 
		 * @param element    ��ʾ�豸��Ӳ���
		 * @param callback    ��ʾ�豸�����Ļص�����
		 */
		virtual csf_int32 add(const csf_element& element, const csf_device_operation_callback callback);

	};

}
#endif // !defined(DEVICE_IO_INCLUDED_)
