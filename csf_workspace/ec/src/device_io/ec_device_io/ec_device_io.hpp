/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: ec_device_io.hpp
*
*Version: 1.0
*
*Date: 26-11月-2019 21:35:52
*
*Description: Class(ec_device_io) 表示执法记录仪业务处理模块，处理音视频内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(EC_DEVICE_IO_H_INCLUDED_)
#define EC_DEVICE_IO_H_INCLUDED_

#include "csf_device_io.hpp"
#include "csf_hiprocessor.hpp"

using namespace ec::core;

namespace ec
{
	namespace device_io
	{
#define		csf_ec_version				1000000
#define		CSF_EC_VERSION				"V1.0.0"
#define		CSF_EC_VAR					"ec_device_io"
#define		CSF_EC_VER					CSF_EC_VAR "/" CSF_EC_VERSION

		/**
		 * 表示执法记录仪业务处理模块，处理音视频内容
		 * @author f
		 * @version 1.0
		 * @created 26-11月-2019 21:35:52
		 */
		class ec_device_io : public csf::core::module::csf_device_io
		{

		public:
			virtual ~ec_device_io();

			/**
			 * 表示根据配置文件创建设备模块
			 *
			 * @param configure_manager    表示配置文件内容
			 */
			inline explicit ec_device_io(const csf_configure_manager * configure_manager)
				: csf_device_io(configure_manager, (csf_module_type)csf_device_io_type_general_extend) {

				set_version(
					csf_ec_version
					, CSF_EC_VER
					, CSF_EC_VAR
					, "ec device io"
				);

			}
			/**
			 * * 主要功能是：主要实现模块的配置信息处理接口。
			 * * 返回：0表示成功；非0表示失败；
			 * *
			 * * @param element    表示模块的配置信息
			 * *
			 * * 常用的配置信息保存结构为：
			 * * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
			 * * <module>
			 * *        <!--***表示模块对应的模块名称信息***-->
			 * *        <name>csf_connection</name>
			 * *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
			 * *        <mid>02000000-0000001</mid>
			 * *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
			 * *        <configure>
			 * *                <!--表示线程数量-->
			 * *                <thread_number>4</thread_number>
			 * *        </configure>
			 * * </module>
			 *
			 */
			virtual csf_int32 configure(const csf_element& element);
			/**
			 * 模块初始化
			 *
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			 * 模块启动
			 *
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			 * 模块停止
			 *
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr);
		private:
			/**
			* 表示设备所拥有的海思处理模块
			*/
			inline csf_hiprocessor& get_hiprocessor() {

				return m_hiprocessor;
			}
			/**
			* 模块启动
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 start_hiprocessor(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			* 模块停止
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 stop_hiprocessor(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			* 表示配置文件管理对象
			*/
			inline csf_configure_manager* get_configure_manager() {

				return m_configure_manager;
			}
			/**
			* 表示配置文件管理对象
			*
			* @param newVal
			*/
			inline void set_configure_manager(csf_configure_manager* newVal) {

				m_configure_manager = newVal;
			}
			/**
			* * 主要功能是：主要海思设备相关的配置信息处理接口。
			* * 返回：0表示成功；非0表示失败；
			* *
			* * @param element    表示模块的配置信息
			* *
			* * 常用的配置信息保存结构为：
			* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
			* * <module>
			* *        <!--***表示模块对应的模块名称信息***-->
			* *        <name>csf_connection</name>
			* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
			* *        <mid>02000000-0000001</mid>
			* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
			* *        <configure>
			* *                <!--表示线程数量-->
			* *                <thread_number>4</thread_number>
			* *        </configure>
			* * </module>
			*/
			csf_int32 parse_hiprocessor_configure(const csf_element& element);
			/**
			* * 主要功能是：海思主要配置文件。
			* * 返回：0表示成功；非0表示失败；
			* *
			* * @param element    表示模块的配置信息
			* *
			* * 常用的配置信息保存结构为：
			* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
			* * <module>
			* *        <!--***表示模块对应的模块名称信息***-->
			* *        <name>csf_connection</name>
			* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
			* *        <mid>02000000-0000001</mid>
			* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
			* *        <configure>
			* *                <!--表示线程数量-->
			* *                <thread_number>4</thread_number>
			* *        </configure>
			* * </module>
			*
			* @param element    表示模块的配置信息
			*/
			csf_int32 parse_hiroot_configure(const csf_element& element);
			/**
			* * 主要功能是：海思视频配置文件。
			* * 返回：0表示成功；非0表示失败；
			* *
			* * @param element    表示模块的配置信息
			* *
			* * 常用的配置信息保存结构为：
			* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
			* * <module>
			* *        <!--***表示模块对应的模块名称信息***-->
			* *        <name>csf_connection</name>
			* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
			* *        <mid>02000000-0000001</mid>
			* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
			* *        <configure>
			* *                <!--表示线程数量-->
			* *                <thread_number>4</thread_number>
			* *        </configure>
			* * </module>
			*/
			csf_int32 parse_hisiv_video_configure(const csf_element& element);
			/**
			* * 主要功能是：海思音频配置文件。
			* * 返回：0表示成功；非0表示失败；
			* *
			* * @param element    表示模块的配置信息
			* *
			* * 常用的配置信息保存结构为：
			* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
			* * <module>
			* *        <!--***表示模块对应的模块名称信息***-->
			* *        <name>csf_connection</name>
			* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
			* *        <mid>02000000-0000001</mid>
			* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
			* *        <configure>
			* *                <!--表示线程数量-->
			* *                <thread_number>4</thread_number>
			* *        </configure>
			* * </module>
			*
			* @param element    表示模块的配置信息
			*/
			csf_int32 parse_hisiv_audio_configure(const csf_element& element);

		private:
			/**
			* 表示设备所拥有的海思处理模块
			*/
			csf_hiprocessor m_hiprocessor;
			/**
			* 表示配置文件管理对象
			*/
			csf_configure_manager* m_configure_manager = NULL;
		};

	}

}
#endif // !defined(EC_DEVICE_IO_H_INCLUDED_)
