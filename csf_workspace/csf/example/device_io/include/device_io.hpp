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
*Date: 24-7月-2018 22:17:27
*
*Description: Class(device_io) 表示设备的子设备内容。
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
	 * 表示设备的子设备内容。
	 * @author f
	 * @version 1.0
	 * @created 24-7月-2018 22:17:27
	 */
	class device_io : public csf::core::module::device_io::csf_device_io
	{

	public:
		device_io();
		virtual ~device_io();

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

}
#endif // !defined(DEVICE_IO_INCLUDED_)
