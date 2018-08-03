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
*Date: 24-7��-2018 22:17:26
*
*Description: Class(device) ��ʾ�����õ�device�豸�ĳ���
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(DEVICE_INCLUDED_)
#define DEVICE_INCLUDED_

#include "csf_device.hpp"

/**
 * ��ʾ�����õ�device�豸�ĳ���
 * @author f
 * @version 1.0
 * @created 24-7��-2018 22:17:26
 */
class device : public csf::core::module::device::csf_device
{

public:
	device();
	virtual ~device();

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

#endif // !defined(DEVICE_INCLUDED_)
