﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device_base.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:39
*
*Description: Class(csf_device_base)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEVICE_BASE_INCLUDED_)
#define CSF_DEVICE_BASE_INCLUDED_

#include "csf_device_operation_interface.hpp"
#include "csf_module.hpp"
#include "csf_attribute_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			//表示device id字符串缓存的默认长度
			#define csf_device_id_length							256

			//表示设备处理回调函数
			typedef csf_function<csf_int32 (csf_element&)>			csf_device_operation_callback;

			/**
			 * 表示基础设备类型
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:39
			 */
			class csf_device_base : public csf::core::module::csf_module, public csf::core::module::csf_device_operation_interface
			{

			public:
				inline explicit csf_device_base()
					: m_mid{ 0, }
					, m_parent(csf_nullptr) {

				}

				virtual ~csf_device_base() {

				}
				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				* @param type    表示模块的类型
				*/
				inline explicit csf_device_base(const csf_configure_manager * configure_manager
					, const csf_module::csf_module_type type) 
				
					: csf_module(configure_manager, type)
					, m_mid{ 0, }
					, m_parent(csf_nullptr) {

				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 del(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_success;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 ctrl(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_success;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 update(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_success;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 add(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_success;
				}
				/**
				* 模块初始化
				*
				* @param conf_mg    表示配置文件信息
				*/
				inline virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_success;
				}
				/**
				* 模块启动
				*
				* @param conf_mg    表示配置文件信息
				*/
				inline virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_success;
				}
				/**
				* 表示设备的唯一编码id
				*/
				inline csf_string get_mid() {

					return m_mid;
				}
				/**
				* 模块停止
				*
				* @param conf_mg    表示配置文件信息
				*/
				inline virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_success;
				}
				/**
				* 表示设备的唯一编码id，其中id最大长度256字节。
				* 返回：true表示设置成功；false表示设置失败。
				*
				* @param newVal
				*/
				inline csf_bool set_mid(const csf_string& newVal) {

					if (newVal.empty() || newVal.length() >= csf_device_id_length) {
						return csf_false;
					}

					return set_mid(newVal.c_str());
				}
				/**
				* 表示设备的唯一编码id，其中id最大长度256字节。
				* 返回：true表示设置成功；false表示设置失败。
				*
				* @param newVal
				*/
				inline csf_bool set_mid(const csf_char* newVal) {

					if (!newVal || csf_strlen(newVal) >= csf_device_id_length) {
						return csf_false;
					}

					csf_memset(m_mid, 0, csf_sizeof(m_mid));
					csf_strcpy(m_mid, newVal);
					
					return csf_true;
				}
				/**
				* 功能：根据模块的类型数据，判断是否为csf_device_base设备。校验的方法是判断是否为app、device、device_io的设备
				* 返回：true表示是device设备；false表示不是device设备。
				*
				* @param type    表示模块的类型数值
				*/
				inline static csf_bool is_device(const csf::core::module::csf_module::csf_module_type type) {

					if ((type && csf_module::csf_module_type::csf_module_type_app)
							|| (type && csf_module::csf_module_type::csf_module_type_device)
							|| (type && csf_module::csf_module_type::csf_module_type_device_io)) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				* 表示设备所属的父设备的节点名称
				*
				* @param newVal    表示父设备节点
				*/
				inline virtual csf_void set_parent(const csf_device_base* newVal) {

					m_parent = (csf_device_base*)newVal;
				}
				/**
				* 表示设备所属的父设备的节点名称
				*/
				inline virtual csf_device_base* get_parent() {

					return m_parent;
				}

			private:
				/**
				* 表示设备的唯一编码id
				*/
				csf_char m_mid[csf_device_id_length] = { 0, };
				/**
				* 表示设备所属的父设备的节点名称
				*/
				csf_device_base* m_parent = csf_nullptr;

			};

		}

	}

}
#endif // !defined(CSF_DEVICE_BASE_INCLUDED_)
