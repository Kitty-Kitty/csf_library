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
*Date: 27-6月-2018 17:28:47
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
				 * 表示处理进程抽象
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6月-2018 17:28:47
				 */
				class csf_process : public csf::core::module::csf_device, public csf::core::module::device::csf_process_interface
				{

				public:
					csf_process();
					virtual ~csf_process();
					/**
					* 表示根据配置文件和类型创建设备模块
					*
					* @param configure_manager    表示配置文件内容
					* @param type    表示模块的类型
					*/
					inline explicit csf_process(const csf_configure_manager * configure_manager
						, const csf::core::module::csf_device::csf_device_type type)
						: csf_device(configure_manager, type) {

					}
					/**
					 * 表示设备的添加操作
					 * 
					 * @param element    表示设备添加操作
					 * @param callback    表示设备操作的回调函数
					 */
					virtual csf_int32 del(csf_element& element, csf_device_operation_callback callback);
					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示设备的添加操作
					 * 
					 * @param element    表示设备添加操作
					 * @param callback    表示设备操作的回调函数
					 */
					virtual csf_int32 ctrl(csf_element& element, csf_device_operation_callback callback);
					/**
					 * 模块启动
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示设备的添加操作
					 * 
					 * @param element    表示设备添加操作
					 * @param callback    表示设备操作的回调函数
					 */
					virtual csf_int32 update(csf_element& element, csf_device_operation_callback callback);
					/**
					 * 表示设备的添加操作
					 * 
					 * @param element    表示设备添加操作
					 * @param callback    表示设备操作的回调函数
					 */
					virtual csf_int32 add(csf_element& element, csf_device_operation_callback callback);

				};

			}

		}

	}

}
#endif // !defined(CSF_PROCESS_INCLUDED_)
