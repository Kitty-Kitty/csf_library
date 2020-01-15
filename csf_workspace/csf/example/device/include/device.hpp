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
*Date: 24-7月-2018 22:17:26
*
*Description: Class(device) 表示测试用的device设备的抽象。
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(DEVICE_INCLUDED_)
#define DEVICE_INCLUDED_

#include "csf_device.hpp"

/**
 * 表示测试用的device设备的抽象。
 * @author f
 * @version 1.0
 * @created 24-7月-2018 22:17:26
 */
class device : public csf::core::module::device::csf_device
{

public:
	device();
	virtual ~device();

	/**
	 * 表示设备的添加操作
	 *
	 * @param element    表示设备添加操作
	 * @param callback    表示设备操作的回调函数
	 */
	virtual csf_int32 del(const csf_element& element, const csf_device_operation_callback callback);
	/**
	 * 模块初始化
	 *
	 * @param conf_mg    表示配置文件信息
	 */
	virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
	/**
	 * 表示设备的添加操作
	 *
	 * @param element    表示设备添加操作
	 * @param callback    表示设备操作的回调函数
	 */
	virtual csf_int32 ctrl(const csf_element& element, const csf_device_operation_callback callback);
	/**
	 * 模块启动
	 *
	 * @param conf_mg    表示配置文件信息
	 */
	virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
	/**
	 * 模块停止
	 *
	 * @param conf_mg    表示配置文件信息
	 */
	virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
	/**
	 * 表示设备的添加操作
	 *
	 * @param element    表示设备添加操作
	 * @param callback    表示设备操作的回调函数
	 */
	virtual csf_int32 update(const csf_element& element, const csf_device_operation_callback callback);
	/**
	 * 表示设备的添加操作
	 *
	 * @param element    表示设备添加操作
	 * @param callback    表示设备操作的回调函数
	 */
	virtual csf_int32 add(const csf_element& element, const csf_device_operation_callback callback);

};

#endif // !defined(DEVICE_INCLUDED_)
