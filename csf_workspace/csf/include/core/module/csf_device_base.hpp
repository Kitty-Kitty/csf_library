/*******************************************************************************
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

#include "csf_device_configure_interface.hpp"
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

			//表示应用程序的的抽象模型app对象，一个app表示一个应用程序
			class csf_app;

			//表示设备抽象
			class csf_device;

			//表示设备io的抽象
			class csf_device_io;

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

				inline virtual ~csf_device_base() {

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

					return csf_succeed;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 ctrl(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_succeed;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 update(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_succeed;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 add(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_succeed;
				}
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
				inline virtual csf_int32 configure(const csf::core::system::csf_element& element) {

					return 0;
				}
				/**
				* 主要功能是：根据配置文件内容，实现模块的配置信息处理接口；
				*      注意：
				*            1、该接口根据items获取根配置项后，调用configure(const
				* csf_element&)实现具体的配置，所以该接口需要模块需要实现配置接口；
				*            2、如果已经调用configure(const csf_element&)接口实现配置，则该函数无效；
				* 返回：0表示成功；非0表示失败；
				*
				* @param conf_mg    表示配置文件信息
				* @param items    表示items根属性路径
				*/
				csf_int32 configure(const csf_configure_manager * conf_mg, const csf_list<csf_string>& items) {

					if (csf_nullptr != conf_mg
						&& csf_false == get_attribute_manager().is_configured()) {

						return configure(((csf_configure_manager *)conf_mg)->find_element(items));
					}

					return csf_succeed;
				}
				/**
				/**
				* 模块初始化
				*
				* @param conf_mg    表示配置文件信息
				*/
				inline virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_succeed;
				}
				/**
				* 模块启动
				*
				* @param conf_mg    表示配置文件信息
				*/
				inline virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_succeed;
				}
				/**
				* 表示设备的唯一编码id
				*/
				inline csf_string get_mid() {

					return csf_string(m_mid);
				}
				/**
				* 模块停止
				*
				* @param conf_mg    表示配置文件信息
				*/
				inline virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_succeed;
				}
				/**
				* 表示设备的唯一编码id，其中id最大长度256字节。
				* 返回：true表示设置成功；false表示设置失败。
				*
				* @param new_value
				*/
				inline csf_bool set_mid(const csf_string& new_value) {

					if (new_value.empty() || new_value.length() >= csf_device_id_length) {
						return csf_false;
					}

					return set_mid(new_value.c_str());
				}
				/**
				* 表示设备的唯一编码id，其中id最大长度256字节。
				* 返回：true表示设置成功；false表示设置失败。
				*
				* @param new_value
				*/
				inline csf_bool set_mid(const csf_char* new_value) {

					if (!new_value || csf_strlen(new_value) >= csf_device_id_length) {
						return csf_false;
					}

					csf_memset(m_mid, 0, csf_sizeof(m_mid));
					csf_strcpy(m_mid, new_value);
					
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
				* @param new_value    表示父设备节点
				*/
				inline virtual csf_void set_parent(const csf_device_base* new_value) {

					m_parent = (csf_device_base*)new_value;
				}
				/**
				* 表示设备所属的父设备的节点名称
				*/
				inline virtual csf_device_base* get_parent() {

					return m_parent;
				}
				/**
				* 主要功能是：将模块信息格式化成字符串输出
				* 返回：模块信息字符串
				*/
				inline virtual csf_string to_string() {

					csf_char				tmp_buf[512] = { 0, };


					csf_snprintf(tmp_buf
						, csf_sizeof(tmp_buf)
						, "device_base[mid:%s parent:%p] %s"
						, m_mid
						, m_parent
						, csf_module::to_string().c_str());

					return csf_string(tmp_buf);
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
