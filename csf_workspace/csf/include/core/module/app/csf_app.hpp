/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_app.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7月-2018 17:33:42
*
*Description: Class(csf_app)表示应用程序的的抽象模型app对象，一个app表示一个应用程序
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_APP_INCLUDED_)
#define CSF_APP_INCLUDED_

#include "csf_time.hpp"
#include "csf_module_manager.hpp"
#include "csf_vm.hpp"
#include "csf_app_interface.hpp"
#include "csf_logger.hpp"
#include "csf_device_base.hpp"
#include "csf_root_configure.hpp"
#include "csf_mutex.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			* 表示当前app的根配置文件的别名
			*/
			#define CSF_APP_ROOT_CONFIGURE_FILE_NAME_STRING				"_root_configure_file_"

			/**
			 * 表示应用程序的的抽象模型app对象，一个app表示一个应用程序
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7月-2018 17:33:42
			 */
			class csf_app : public csf::core::module::csf_device_base, public csf::core::module::csf_app_interface
			{

			public:
				/**
				* 表示app模块的类型
				* @author f
				* @version 1.0
				* @created 12-7月-2018 16:38:04
				*/
				enum csf_app_type
				{
					/**
					* 表示未知的app类型
					*/
					csf_app_type_none = csf_module_type_app | 0x00000000,
					/**
					* 表示通用app的扩展，运用于第三方扩展。
					*/
					csf_app_type_general_extend = csf_app_type_none | 0x00010000
				};

				inline explicit csf_app()
					: csf_device_base(&m_config_mg, csf_module_type_app)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg) {

				}

				inline virtual ~csf_app() {

				}

				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				*/
				inline explicit csf_app(const csf_configure_manager * configure_manager)
					: csf_device_base(&m_config_mg, csf_module_type_app)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg) {

				}
				/**
				* 表示根据配置文件和类型创建设备模块
				*
				* @param configure_manager    表示配置文件内容
				* @param type    表示模块的类型
				*/
				inline explicit csf_app(const csf_configure_manager * configure_manager, const csf_module::csf_module_type type)
					: csf_device_base(&m_config_mg, type)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg) {

				}
				/**
				* 根据根配置文件信息创建一个app
				*
				* @param root_configure_file    表示当前app根配置文件信息
				*/
				inline explicit csf_app(csf_configure_file& root_configure_file)
					: csf_device_base(&m_config_mg, csf_module_type_app)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg)
					, m_root_configure_file(root_configure_file) {

				}
				/**
				* 根据根配置文件信息创建一个app
				*
				* @param path    表示当前app根配置文件的文件路径
				* @param format    表示根配置文件的文件格式
				*/
				inline explicit csf_app(const csf_char* path, const csf_char* format)
					: csf_device_base(&m_config_mg, csf_module_type_app)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg)
					, m_root_configure_file(CSF_APP_ROOT_CONFIGURE_FILE_NAME_STRING, path, format) {

				}
				/**
				* 根据根配置文件信息创建一个app
				*
				* @param path    表示当前app根配置文件的文件路径
				* @param format    表示根配置文件的文件格式
				*/
				inline explicit csf_app(csf_string& path, csf_string& format)
					: csf_app(path.c_str(), format.c_str()) {

				}

				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 del(const csf_element& element, const csf_device_operation_callback callback) {

					return 0;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 ctrl(const csf_element& element, const csf_device_operation_callback callback) {

					return 0;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 update(const csf_element& element, const csf_device_operation_callback callback) {

					return 0;
				}
				/**
				* 表示设备的添加操作
				*
				* @param element    表示设备添加操作
				* @param callback    表示设备操作的回调函数
				*/
				inline virtual csf_int32 add(const csf_element& element, const csf_device_operation_callback callback) {

					return 0;
				}
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
				/**
				* 表示日志系统
				*/
				inline csf_logger& get_logger() {

					return m_logger;
				}
				/**
				* 表示app自身维持的时间
				*/
				inline csf::core::base::csf_time get_app_time() {

					return m_app_time;
				}
				/**
				* 表示定时获取的系统时间
				*/
				inline csf::core::base::csf_time get_system_time() {

					return m_system_time;
				}
				/**
				* 表示app的启动时间
				*/
				inline csf::core::base::csf_time get_start_time() {

					return m_start_time;
				}
				/**
				* 表示当前的工作目录地址
				*/
				inline csf_string& get_work_directory() {

					return m_work_directory;
				}
				/**
				* 表示系统app所拥有的device列表，个个device都属于app，都共享app的资源。
				*/
				inline csf_unordered_map<csf_string, csf_device*>& get_devices() {

					return m_devices;
				}
				/**
				* 表示系统总的配置管理器，一个系统存在至少一个该配置管理器
				*/
				inline csf::core::system::csf_configure_manager& get_config_mg() {

					return m_config_mg;
				}
				/**
				* 表示app的根配置文件信息，主要保存app的各种配置文件信息。
				*/
				inline csf_configure_file& get_root_configure_file() {

					return m_root_configure_file;
				}
				/**
				* 表示模块工厂管理器
				*/
				inline csf::core::module::csf_module_manager& get_module_manager() {

					return m_module_manager;
				}
				/**
				* 功能：根据设备名称查询指定设备地址
				* 返回：非空表示成功；空表示失败；
				*
				* @param mid    表示设备名称
				*/
				csf_device* find_device(const csf_string& mid);
				/**
				* 功能：根据设备名称查询指定设备地址
				* 返回：非空表示成功；空表示失败；
				*
				* @param mid    表示设备名称
				*/
				inline csf_device* find_device(const char* mid) {

					if (!mid || csf_strlen(mid) <= 0) {
						return csf_nullptr;
					}

					return  find_device(csf_string(mid));
				}
				/**
				* 功能：根据设备名称添加指定设备地址到设备列表中
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备名称
				* @param device
				*/
				csf_bool add_device(const csf_string& mid, const csf_device* device);
				/**
				* 功能：根据设备名称添加指定设备地址到设备列表中
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备名称
				* @param device
				*/
				inline csf_bool add_device(const csf_char* mid, const csf_device* device) {

					if (!device || !mid || csf_strlen(mid) <= 0) {
						return csf_nullptr;
					}

					return  add_device(csf_string(mid), device);
				}
				/**
				* 功能：根据设备名称删除指定设备地址
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备名称
				*/
				csf_bool del_device(const csf_string& mid);
				/**
				* 功能：根据设备名称删除指定设备地址
				* 返回：true表示成功；false表示失败；
				*
				* @param mid    表示设备名称
				*/
				inline csf_bool del_device(const csf_char* mid) {

					if (!mid || csf_strlen(mid) <= 0) {
						return csf_nullptr;
					}

					return del_device(csf_string(mid));
				}
				/**
				* 主要功能是：将模块信息格式化成字符串输出
				* 返回：模块信息字符串
				*/
				inline virtual csf_string to_string() {

					return "";
				}
			protected:
				/**
				* 表示app自身维持的时间
				*
				* @param new_value
				*/
				inline void set_app_time(csf::core::base::csf_time new_value) {

					m_app_time = new_value;
				}
				/**
				* 表示定时获取的系统时间
				*
				* @param new_value
				*/
				inline void set_system_time(csf::core::base::csf_time new_value) {

					m_system_time = new_value;
				}
				/**
				* 表示app的启动时间
				*
				* @param new_value
				*/
				inline void set_start_time(csf::core::base::csf_time new_value) {

					m_start_time = new_value;
				}
				/**
				* 表示当前的工作目录地址
				*
				* @param new_value
				*/
				inline void set_work_directory(csf_string& new_value) {

					m_work_directory = new_value;
				}
				/**
				* 表示系统app所拥有的device列表，个个device都属于app，都共享app的资源。
				*
				* @param new_value
				*/
				inline void set_devices(csf_unordered_map<csf_string, csf_device*>& new_value) {

					m_devices = new_value;
				}
				/**
				* 表示系统总的配置管理器，一个系统存在至少一个该配置管理器
				*
				* @param new_value
				*/
				inline void set_config_mg(const csf::core::system::csf_configure_manager& new_value) {

					m_config_mg = new_value;
				}
				/**
				* 该函数主要用于初始化app的配置文件，获取配置文件中保存的属性信息。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				* @param root_configure_file    表示当前app根配置文件信息
				*/
				inline csf_bool init_configure_manager(csf::core::system::csf_configure_manager& configure_manager,
					csf_configure_file& root_configure_file) {

					if (!csf_root_configure().init_configure_manager(configure_manager, root_configure_file)) {
						csf_log_ex(critical, csf_log_code_critical, "init configure manager failed!");
						return csf_false;
					}
					else {
						csf_log_ex(notice, csf_log_code_notice, "init configure manager succeed!");
						return csf_true;
					}

					return csf_false;
				}
				/**
				* 表示app的根配置文件信息，主要保存app的各种配置文件信息。
				*
				* @param new_value
				*/
				inline csf_void set_root_configure_file(csf_configure_file& new_value) {

					m_root_configure_file = new_value;
				}
				/**
				* 该函数主要用于初始化app的日志系统。
				* 返回：true表示初始化日志系统成功；false表示初始化日志系统失败。
				*
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				* @param work_directory    表示程序默认的工作根目录地址
				*/
				csf_bool init_logger(csf::core::system::csf_configure_manager& configure_manager, csf_string work_directory = "");
				/**
				* 该函数主要用于初始化app的模块管理器
				* 返回：true表示初始化成功；false表示初始化失败。
				*
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool init_module_manager(csf::core::system::csf_configure_manager& configure_manager);
				/**
				* 功能：该函数主要用于初始化app的引导器，启动模块
				* 返回：true表示初始化成功；false表示初始化失败。
				*
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool init_bootloader(csf::core::system::csf_configure_manager& configure_manager);
				/**
				* 功能：该函数主要用于初始化app的当前工作目录
				* 返回：true表示初始化成功；false表示初始化失败。
				*
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool init_work_directory(csf::core::system::csf_configure_manager& configure_manager);

			private:
				/**
				 * 表示app的启动时间
				 */
				csf::core::base::csf_time m_start_time;
				/**
				 * 表示app自身维持的时间
				 */
				csf::core::base::csf_time m_app_time;
				/**
				 * 表示定时获取的系统时间
				 */
				csf::core::base::csf_time m_system_time;
				/**
				 * 表示当前的工作目录地址
				 */
				csf_string m_work_directory = "";
				/**
				 * 表示系统app所拥有的device列表，个个device都属于app，都共享app的资源。
				 */
				csf_unordered_map<csf_string, csf_device*> m_devices;
				/**
				* 表示系统总的配置管理器，一个系统存在至少一个该配置管理器
				*/
				csf::core::system::csf_configure_manager m_config_mg;
				/**
				 * 表示系统的模块管理器，一个系统至少有一个模块管理器
				 */
				csf::core::module::csf_module_manager m_module_manager;
				/**
				 * 表示系统运行虚拟机
				 */
				csf::core::module::csf_vm *m_vm = csf_nullptr;
				/**
				 * 系统日志系统
				 */
				csf::core::system::csf_logger m_logger;
				/**
				* 表示app的根配置文件信息，主要保存app的各种配置文件信息。
				*/
				csf_configure_file m_root_configure_file;
				/**
				* 表示线程安全使用的互斥锁内容
				*/
				csf_shared_mutex m_devices_mutex;
			};

		}

	}

}
#endif // !defined(CSF_APP_INCLUDED_)
