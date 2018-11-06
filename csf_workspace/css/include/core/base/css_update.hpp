/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: css_update.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:32
*
*Description: Class(css_update) 表示css系统的更新信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_UPDATE_H_INCLUDED_)
#define CSS_UPDATE_H_INCLUDED_

#include "csf_pfstring.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示css系统的更新信息
		 * @author Administrator
		 * @version 1.0
		 * @created 07-10月-2018 16:50:32
		 */
		class css_update
		{

		public:
			css_update();
			virtual ~css_update();

			/**
			 * 表示升级运用的设备类型
			 */
			inline css::core::css_device_type get_type() {

				return m_type;
			}
			/**
			 * 表示升级运用的设备类型
			 * 
			 * @param newVal
			 */
			inline csf_void set_type(const css::core::css_device_type newVal) {

				m_type = newVal;
			}
			/**
			 * 表示升级包的打包方式
			 */
			inline css_packet_type get_packet_type() {

				return m_packet_type;
			}
			/**
			 * 表示升级包的打包方式
			 * 
			 * @param newVal
			 */
			inline csf_void set_packet_type(const css_packet_type newVal) {

				m_packet_type = newVal;
			}
			/**
			 * 表示升级运用的设备类型
			 */
			inline css::core::css_device_type get_device_type() {

				return m_device_type;
			}
			/**
			 * 表示升级运用的设备类型
			 * 
			 * @param newVal
			 */
			inline csf_void set_device_type(const css::core::css_device_type newVal) {

				m_device_type = newVal;
			}
			/**
			 * <font color="#008000">更新包数据内容</font>
			 */
			inline csf::core::base::csf_pfstring& get_program_file() {

				return m_program_file;
			}
			/**
			 * <font color="#008000">更新包数据内容</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_program_file(const csf::core::base::csf_pfstring& newVal) {

				m_program_file = newVal;
			}
			/**
			 * <font color="#008000">更新包中程序数据内容</font>
			 */
			inline csf::core::base::csf_pfstring& get_file_data() {

				return m_file_data;
			}
			/**
			 * <font color="#008000">更新包中程序数据内容</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_file_data(const csf::core::base::csf_pfstring& newVal) {

				m_file_data = newVal;
			}
			/**
			 * <font color="#008000">表示使用标识</font>
			 */
			inline css_update_operation get_operation_flag() {

				return m_operation_flag;
			}
			/**
			 * <font color="#008000">表示使用标识</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_operation_flag(const css_update_operation newVal) {

				m_operation_flag = newVal;
			}
			/**
			 * <font color="#008000">表示版本附加信息</font>
			 */
			inline csf_uint32 get_version() {

				return m_version_addtion;
			}
			/**
			 * <font color="#008000">表示版本附加信息</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_version(const csf_uint32 newVal) {

				m_version_addtion = newVal;
			}
			/**
			 * <font color="#008000">表示是否更新conf/conf.
			 * xml文件，TRUE表示需要更新（这个时候IP可能会被修改）；FLASE表示不需要更新</font>
			 */
			inline csf_bool get_is_update_conf_file() {

				return m_is_update_conf_file;
			}
			/**
			 * <font color="#008000">表示是否更新conf/conf.
			 * xml文件，TRUE表示需要更新（这个时候IP可能会被修改）；FLASE表示不需要更新</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_is_update_conf_file(const csf_bool newVal) {

				m_is_update_conf_file = newVal;
			}
			/**
			 * <font
			 * color="#008000">表示是否更新data中的数据文件，TRUE表示需要更新（这个时候数据可能被删除）；FLASE表示不需要更新</font>
			 */
			inline csf_bool get_is_update_data_file() {

				return m_is_update_data_file;
			}
			/**
			 * <font
			 * color="#008000">表示是否更新data中的数据文件，TRUE表示需要更新（这个时候数据可能被删除）；FLASE表示不需要更新</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_is_update_data_file(const csf_bool newVal) {

				m_is_update_data_file = newVal;
			}
			/**
			 * <font color="#008000">表示软件的发布时间信息</font>
			 */
			inline csf_uint64 get_time() {

				return m_time;
			}
			/**
			 * <font color="#008000">表示软件的发布时间信息</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_time(const csf_uint64 newVal) {

				m_time = newVal;
			}
			/**
			 * <font color="#008000">表示设备的编码ID</font>
			 */
			inline csf_string& get_device_id() {

				return m_device_id;
			}
			/**
			 * <font color="#008000">表示设备的编码ID</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_device_id(const csf_string& newVal) {

				m_device_id = newVal;
			}
			/**
			 * <font color="#008000">表示软件包名称</font>
			 */
			inline csf_string& get_packet_name() {

				return m_packet_name;
			}
			/**
			 * <font color="#008000">表示软件包名称</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_packet_name(const csf_string& newVal) {

				m_packet_name = newVal;
			}
			/**
			 * <font color="#008000">表示软件的更新信息</font>
			 */
			inline csf_string& get_change_log() {

				return m_change_log;
			}
			/**
			 * <font color="#008000">表示软件的更新信息</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_change_log(const csf_string& newVal) {

				m_change_log = newVal;
			}
			/**
			 * <font color="#008000">表示平台硬件信息</font>
			 */
			inline csf_string& get_platform_hardware() {

				return m_platform_hardware;
			}
			/**
			 * <font color="#008000">表示平台硬件信息</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_platform_hardware(const csf_string& newVal) {

				m_platform_hardware = newVal;
			}
			/**
			 * <font color="#008000">表示平台软件信息</font>
			 */
			inline csf_string& get_platform_software() {

				return m_platform_software;
			}
			/**
			 * <font color="#008000">表示平台软件信息</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_platform_software(const csf_string& newVal) {

				m_platform_software = newVal;
			}
			/**
			 * <font color="#008000">表示设备主型号</font>
			 */
			inline csf_string& get_serial_master() {

				return m_serial_master;
			}
			/**
			 * <font color="#008000">表示设备主型号</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_serial_master(const csf_string& newVal) {

				m_serial_master = newVal;
			}
			/**
			 * <font color="#008000">表示设备副型号</font>
			 */
			inline csf_string& get_serial_slave() {

				return m_serial_slave;
			}
			/**
			 * <font color="#008000">表示设备副型号</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_serial_slave(const csf_string& newVal) {

				m_serial_slave = newVal;
			}

		private:
			/**
			 * 表示升级运用的设备类型
			 */
			css::core::css_device_type m_device_type = css_device_type_none;
			/**
			 * 表示升级包的打包方式
			 */
			css_packet_type m_packet_type = css_packet_type_none;
			/**
			 * <font color="#008000">更新包数据内容</font>
			 */
			csf::core::base::csf_pfstring m_program_file;
			/**
			 * <font color="#008000">更新包中程序数据内容</font>
			 */
			csf::core::base::csf_pfstring m_file_data = csf_null;
			/**
			 * <font color="#008000">表示使用标识</font>
			 */
			css_update_operation m_operation_flag;
			/**
			 * <font color="#008000">表示是否更新conf/conf.
			 * xml文件，TRUE表示需要更新（这个时候IP可能会被修改）；FLASE表示不需要更新</font>
			 */
			csf_bool m_is_update_conf_file = csf_false;
			/**
			 * <font
			 * color="#008000">表示是否更新data中的数据文件，TRUE表示需要更新（这个时候数据可能被删除）；FLASE表示不需要更新</font>
			 */
			csf_bool m_is_update_data_file = csf_false;
			/**
			 * <font color="#008000">表示版本号信息</font>
			 */
			csf_uint32 m_version = 0;
			/**
			 * <font color="#008000">表示版本附加信息</font>
			 */
			csf_uint32 m_version_addtion = 0;
			/**
			 * <font color="#008000">表示软件的发布时间信息</font>
			 */
			csf_uint64 m_time = 0;
			/**
			 * <font color="#008000">表示设备的编码ID</font>
			 */
			csf_string m_device_id = "";
			/**
			 * <font color="#008000">表示软件包名称</font>
			 */
			csf_string m_packet_name = "";
			/**
			 * <font color="#008000">表示设备主型号</font>
			 */
			csf_string m_serial_master = "";
			/**
			 * <font color="#008000">表示设备副型号</font>
			 */
			csf_string m_serial_slave = "";
			/**
			 * <font color="#008000">表示平台硬件信息</font>
			 */
			csf_string m_platform_hardware = "";
			/**
			 * <font color="#008000">表示平台软件信息</font>
			 */
			csf_string m_platform_software = "";
			/**
			 * <font color="#008000">表示软件的更新信息</font>
			 */
			csf_string m_change_log = "";

		};

	}

}
#endif // !defined(CSS_UPDATE_H_INCLUDED_)
