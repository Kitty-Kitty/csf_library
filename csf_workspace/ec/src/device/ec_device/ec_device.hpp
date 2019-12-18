/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: ec_device.hpp
*
*Version: 1.0
*
*Date: 08-10月-2018 20:52:07
*
*Description: Class(ec_device) 主要功能用于测试connect factory manager 中的自动配置功能
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(EC_DEVICE_H_INCLUDED_)
#define EC_DEVICE_H_INCLUDED_

#include "csf_device.hpp"

namespace csf
{
	namespace device
	{
		#define		csf_ec_version				1000000
		#define		CSF_EC_VERSION				"V1.0.0"
		#define		CSF_EC_VAR					"ec_device"
		#define		CSF_EC_VER					CSF_EC_VAR "/" CSF_EC_VERSION

		/**
		 * 主要功能用于测试connect factory manager 中的自动配置功能
		 * @author f
		 * @version 1.0
		 * @created 08-10月-2018 20:52:07
		 */
		class ec_device : public csf::core::module::csf_device
		{

		public:
			/**
			* 表示根据配置文件和类型创建设备模块
			*
			* @param configure_manager    表示配置文件内容
			* @param type    表示模块的类型
			*/
			inline explicit ec_device(const csf_configure_manager * configure_manager)
				: csf_device(configure_manager, csf_device_type_general_extend) {

				set_version(
					csf_ec_version
					, CSF_EC_VER
					, CSF_EC_VAR
					, "ec device"
				);

			}

			virtual ~ec_device();

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
			/**
			* 主要功能是：主要实现模块的配置信息处理接口。
			* 返回：0表示成功；非0表示失败；
			*
			* @param element    表示模块的配置信息
			*
			* 常用的配置信息保存结构为：
			* <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
			* <module>
			*        <!--***表示模块对应的模块名称信息***-->
			*        <name>csf_connection</name>
			*        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
			*        <mid>02000000-0000001</mid>
			*        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
			*        <configure>
			*                <!--表示线程数量-->
			*                <thread_number>4</thread_number>
			*        </configure>
			* </module>
			*/
			virtual csf_int32 configure(const csf_element& element);
		};

	}

}
#endif // !defined(EC_DEVICE_H_INCLUDED_)
