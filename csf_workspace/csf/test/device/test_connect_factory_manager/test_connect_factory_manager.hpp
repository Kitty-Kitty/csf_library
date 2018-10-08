/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: test_connect_factory_manager.hpp
*
*Version: 1.0
*
*Date: 08-10月-2018 20:52:07
*
*Description: Class(test_connect_factory_manager) 主要功能用于测试connect factory manager 中的自动配置功能
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(TEST_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
#define TEST_CONNECT_FACTORY_MANAGER_H_INCLUDED_

#include "csf_device.hpp"

namespace csf
{
	namespace example
	{
		/**
		 * 主要功能用于测试connect factory manager 中的自动配置功能
		 * @author f
		 * @version 1.0
		 * @created 08-10月-2018 20:52:07
		 */
		class test_connect_factory_manager : public csf::core::module::csf_device
		{

		public:
			test_connect_factory_manager();
			virtual ~test_connect_factory_manager();

			/**
			* 表示根据配置文件和类型创建设备模块
			*
			* @param configure_manager    表示配置文件内容
			* @param type    表示模块的类型
			*/
			inline explicit test_connect_factory_manager(const csf_configure_manager * configure_manager)
				: csf_device(configure_manager, csf_device_type_test) {

			}

			/**
			 * 模块初始化
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
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

		};

	}

}
#endif // !defined(TEST_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
