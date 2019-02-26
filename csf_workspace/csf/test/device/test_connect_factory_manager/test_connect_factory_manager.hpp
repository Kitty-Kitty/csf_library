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

#if !defined(TEST_TEST_FACTORY_MANAGER_H_INCLUDED_)
#define TEST_TEST_FACTORY_MANAGER_H_INCLUDED_

#include "csf_device.hpp"
#include "csf_connect.hpp"

namespace csf
{
	namespace example
	{
#define		csf_test_version				1000000
#define		CSF_TEST_VERSION				"v1.0.0"
#define		CSF_TEST_VAR					"test_connect_factory"
#define		CSF_TEST_VER					CSF_TEST_VAR "/" CSF_TEST_VERSION

		/**
		 * 主要功能用于测试connect factory manager 中的自动配置功能
		 * @author f
		 * @version 1.0
		 * @created 08-10月-2018 20:52:07
		 */
		class test_connect_factory_manager : public csf::core::module::csf_device
		{

		public:
			/**
			* 表示根据配置文件和类型创建设备模块
			*
			* @param configure_manager    表示配置文件内容
			* @param type    表示模块的类型
			*/
			inline explicit test_connect_factory_manager(const csf_configure_manager * configure_manager)
				: csf_device(configure_manager, csf_device_type_test) {

				set_version(
					csf_test_version
					, CSF_TEST_VER
					, CSF_TEST_VAR
					, "test connect factory manager"
				);

			}

			virtual ~test_connect_factory_manager();

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
			* 主要功能是：tcp监听处理返回接口
			* 返回：0表示正常；非0表示错误
			*
			* @param connect_ptr    表示当前正在处理的连接对象
			* @param connect_error    表示当前处理的异常信息
			*/
			csf::core::base::csf_int32 tcp_handle(csf_connect_ptr connect_ptr, csf_connect_error& connect_error);
			/**
			* 主要功能是：udp监听处理返回接口
			* 返回：0表示正常；非0表示错误
			*
			* @param connect_ptr    表示当前正在处理的连接对象
			* @param connect_error    表示当前处理的异常信息
			*/
			csf::core::base::csf_int32 udp_handle(csf_connect_ptr connect_ptr, csf_connect_error& connect_error);
			/**
			* 主要功能是：tcp读数据返回函数
			* 返回：大于等于0表示成功；小于0表示错误
			*
			* @param connect_ptr    表示当前正在处理的连接对象
			* @param connect_buffer
			* @param connect_error    表示当前处理的异常信息
			*/
			csf::core::base::csf_int32 read_handle(
				csf_connect_ptr connect_ptr
				, csf_connect_error& connect_error
				, csf_connect_buffer<csf_buffer>& connect_buffer
				);
			/**
			* 主要功能是：tcp读数据返回函数
			* 返回：大于等于0表示成功；小于0表示错误
			*
			* @param connect_ptr    表示当前正在处理的连接对象
			* @param connect_buffer
			* @param connect_error    表示当前处理的异常信息
			*/
			csf::core::base::csf_int32 tcp_read_handle(csf_connect_ptr connect_ptr
				, csf_connect_error& connect_error
				, csf_int32 len);

		private:
			/**
			* 表示读取数据所使用的回调函数对象
			*/
			csf_connect_callback m_read_function = csf_nullptr;
			/**
			* 表示写数据所使用的回调函数对象
			*/
			csf_connect_callback m_write_function = csf_nullptr;
			/**
			* 表示读取数据所使用的回调函数对象
			*/
			inline csf_connect_callback& get_read_function() {

				return m_read_function;
			}
			/**
			* 表示读取数据所使用的回调函数对象
			*
			* @param newVal
			*/
			inline void set_read_function(csf_connect_callback newVal) {

				m_read_function = newVal;
			}
			/**
			* 表示写数据所使用的回调函数对象
			*/
			inline csf_connect_callback& get_write_function() {

				return m_write_function;
			}
			/**
			* 表示写数据所使用的回调函数对象
			*
			* @param newVal
			*/
			inline void set_write_function(csf_connect_callback newVal) {

				m_write_function = newVal;
			}
		};

	}

}
#endif // !defined(TEST_TEST_FACTORY_MANAGER_H_INCLUDED_)
