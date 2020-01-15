﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7月-2018 17:33:44
*
*Description: Class(csf_device)表示设备抽象
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEVICE_INCLUDED_)
#define CSF_DEVICE_INCLUDED_

#include "csf_device_interface.hpp"
#include "csf_device_base.hpp"
#include "csf_logger.hpp"
#include "csf_mutex.hpp"
#include "csf_configure_module.hpp"


namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示设备抽象
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7月-2018 17:33:44
			 */
			class csf_device : public csf::core::module::csf_device_base, public csf::core::module::csf_device_interface
			{

			public:
				/**
				* 表示设备的类型
				* @author f
				* @version 1.0
				* @created 12-7月-2018 16:39:10
				*/
				enum csf_device_type
				{
					/**
					* 表示未知的设备类型
					*/
					csf_device_type_none = csf_module_type_device | 0x00000000,
					/**
					* 表示网络连接设备
					*/
					csf_device_type_connect = csf_module_type_device | 0x00010000,
					/**
					* 表示数据库设备
					*/
					csf_device_type_database = csf_module_type_device | 0x00020000,
					/**
					* 表示测试设备类型
					*/
					csf_device_type_test = csf_module_type_device | 0x00030000,
					/**
					* 表示满足业务而进行的扩展
					*/
					csf_device_type_general_extend = csf_module_type_device | 0x00040000,
					/**
					* 表示网络连接设备扩展，用于第三方运用
					*/
					csf_device_type_connect_extend = csf_device_type_connect | 0x00000001,
					/**
					* 表示数据库设备扩展，用于第三方运用
					*/
					csf_device_type_database_extend = csf_device_type_database | 0x00000001,
				};

				inline explicit csf_device()
					: m_app(csf_nullptr) {

				}

				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				*/
				inline explicit csf_device(const csf_configure_manager * configure_manager)

					: csf_device_base(configure_manager, csf_module_type_device)
					, m_app(csf_nullptr) {

					csf_configure_module::init_logger(configure_manager);
				}

				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				* @param type    表示模块的类型
				*/
				inline explicit csf_device(const csf_configure_manager * configure_manager
					, const csf::core::module::csf_device::csf_device_type type)

					: csf_device_base(configure_manager, (csf::core::module::csf_module::csf_module_type)type)
					, m_app(csf_nullptr) {

					csf_configure_module::init_logger(configure_manager);
				}

				inline virtual ~csf_device() {

				}

				/**
				 * 表示device所属的app设备地址
				 */
				inline csf_app* get_app() {

					return m_app;
				}
				/**
				* 表示device所属的app设备地址
				*
				* @param new_value
				*/
				inline csf_void set_app(const csf_app* new_value) {

					m_app = (csf_app*)new_value;
				}
				/**
				* 表示设备所拥有的device_io对象地址
				*/
				inline csf_unordered_map<csf_string, csf_device_io*>& get_device_ioes() {

					return m_device_ioes;
				}
				/**
				* 功能：根据模块的mid查找一个设备对象
				* 返回：非空表示成功；空表示失败；
				*
				* @param mid    表示设备的模块编号
				*/
				csf_device_io* find_device_io(const csf_string& mid);
				/**
				* 功能：根据模块的mid查找一个设备对象
				* 返回：非空表示成功；空表示失败；
				*
				* @param mid    表示设备的模块编号
				*/
				inline csf_device_io* find_device_io(const csf_char* mid) {

					if (!mid || csf_strlen(mid) <= 0) {
						return csf_nullptr;
					}

					return  find_device_io(csf_string(mid));
				}
				/**
				* 功能：根据模块的mid向device中插入一个设备对象
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备的模块编号
				* @param device_io    表示device_io模块对象地址
				*/
				csf_bool add_device_io(const csf_string& mid, const csf_device_io* device_io);
				/**
				* 功能：根据模块的mid向device中插入一个设备对象
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备的模块编号
				* @param device_io    表示device_io模块对象地址
				*/
				inline csf_bool add_device_io(const csf_char* mid, const csf_device_io* device_io) {

					if (!mid || !device_io || csf_strlen(mid) <= 0) {
						return csf_false;
					}

					return add_device_io(csf_string(mid), device_io);
				}
				/**
				* 功能：根据模块的mid从设备列表中删除一个设备对象
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备的模块编号
				*/
				csf_bool del_device_io(const csf_string& mid);
				/**
				* 功能：根据模块的mid从设备列表中删除一个设备对象
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备的模块编号
				*/
				inline csf_bool del_device_io(const csf_char* mid) {

					if (!mid || csf_strlen(mid)) {
						return csf_false;
					}

					return del_device_io(csf_string(mid));
				}
				/**
				* 主要功能是：将模块信息格式化成字符串输出
				* 返回：模块信息字符串
				*/
				inline virtual csf_string to_string() {

					csf_char				tmp_buf[512] = { 0, };


					csf_snprintf(tmp_buf
						, csf_sizeof(tmp_buf)
						, "device[app:%p] %s"
						, get_app()
						, csf_device_base::to_string().c_str());

					return csf_string(tmp_buf);
				}
			protected:
				/**
				* 功能：初始化device_io对象
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备的模块编号
				* @param device_io    表示device_io模块对象地址
				*/
				csf_bool init_device_io(const csf_string& mid, csf_device_io* device_io);
				/**
				* 功能：启动device_io对象
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备的模块编号
				* @param device_io    表示device_io模块对象地址
				*/
				csf_bool start_device_io(const csf_string& mid, csf_device_io* device_io);
				/**
				* 功能：启动device_io对象
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备的模块编号
				* @param device_io    表示device_io模块对象地址
				*/
				csf_bool stop_device_io(const csf_string& mid, csf_device_io* device_io);
				/**
				* 功能：
				*    初始化所有device io 设备
				* 返回：
				*    true：表示成功；
				*    false：表示失败；
				*/
				csf_bool init_device_ioes();
				/**
				* 功能：
				*    启动所有device io 设备
				* 返回：
				*    true：表示成功；
				*    false：表示失败；
				*/
				csf_bool start_device_ioes();
				/**
				* 功能：
				*    停止所有device io 设备
				* 返回：
				*    true：表示成功；
				*    false：表示失败；
				*/
				csf_bool stop_device_ioes();
			private:
				/**
				 * 表示device所属的app设备地址
				 */
				csf_app* m_app = csf_nullptr;
				/**
				* 表示设备所拥有的device_io对象地址
				*/
				csf_unordered_map<csf_string, csf_device_io*> m_device_ioes;
				/**
				* 表示线程安全使用的互斥锁内容
				*/
				csf_shared_mutex m_device_ioes_mutex;
			};

		}

	}

}
#endif // !defined(CSF_DEVICE_INCLUDED_)
