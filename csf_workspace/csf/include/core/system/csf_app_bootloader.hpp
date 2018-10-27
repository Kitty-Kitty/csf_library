/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: fangzhenmu@aliyun.com
*
*Author: fz
*
*Version: 1.0
*
*Date: 20-7月-2018 17:41:40
*
*Description: Class(csf_app_bootloader) 表示系统启动运行的app程序配置文件处理。类似启动引导文件，用于描述app需要默认运行的device及各个模块需要加载的device_io内容。
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_APP_BOOTLOADER_INCLUDED_)
#define CSF_APP_BOOTLOADER_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_app.hpp"
#include "csf_device.hpp"
#include "csf_device_io.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * 表示系统启动运行的app程序配置文件处理。类似启动引导文件，用于描述app需要默认运行的device及各个模块需要加载的device_io内容。
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 20-7月-2018 17:41:40
			 */
			class csf_app_bootloader
			{

			public:
				inline explicit csf_app_bootloader()
					: m_configure_manager(csf_nullptr)
					, m_app(csf_nullptr) {

				}

				inline virtual ~csf_app_bootloader() {

				}

				/**
				 * 根据根配置文件信息创建一个app
				 * 
				 * @param app    表示目标app对象
				 * @param configure_manager    配置文件管理器地址信息
				 * 
				 */
				inline explicit csf_app_bootloader(csf::core::module::csf_app* app
					, const csf_configure_manager* configure_manager)

					: m_configure_manager((csf_configure_manager*) configure_manager)
					, m_app(app) {

				}
				/**
				 * 表示配置文件管理器地址信息
				 */
				inline csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * 表示配置文件管理器地址信息
				 * 
				 * @param new_value    配置文件管理器地址信息
				 */
				inline void set_configure_manager(const csf_configure_manager* new_value) {

					m_configure_manager = (csf_configure_manager*)new_value;
				}
				/**
				 * 表示当前的app_configure文件作用的app对象
				 */
				inline csf::core::module::csf_app* get_app() {

					return m_app;
				}
				/**
				* 该函数主要用于初始化app。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param app    表示目标app对象
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool init(csf::core::module::csf_app& app
					, csf::core::system::csf_configure_manager& configure_manager);
				/**
				 * 该函数主要用于初始化app。
				 * 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				 * 
				 * @param app    表示目标app对象
				 * @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				 */
				csf_bool start(csf::core::module::csf_app& app
					, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* 该函数主要用于初始化app。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param app    表示目标app对象
				*/
				csf_bool stop(csf::core::module::csf_app& app);
				/**
				* 功能：该函数主要根据引导文件内容创建app的所属所有设备模块。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param app    表示目标app对象    表示所属的app信息
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool create_devices(csf::core::module::csf_app& app
					, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* 功能：该函数主要根据引导文件内容创建一个设备模块。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param app    表示目标app对象
				* @param element    表示当前的device节点内容
				*/
				csf_bool create_device(csf::core::module::csf_app& app
					, const csf_element& element);
				/**
				* 功能：该函数主要根据引导文件内容创建app的所属所有子设备模块。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param device    表示所属的device设备信息
				* @param element    表示当前的device节点内容
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool create_device_ioes(csf::core::module::csf_device& device
					, const csf_element& element
					, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* 功能：该函数主要根据引导文件内容创建一个子设备模块。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param device    表示所属的device设备信息
				* @param element    表示当前的device节点内容
				*/
				csf_bool create_device_io(csf::core::module::csf_device& device
					, const csf_element& element);
				/**
				 * 表示当前的app_configure文件作用的app对象
				 * 
				 * @param new_value    表示当前的app_configure文件作用的app对象
				 * 
				 */
				inline void set_app(const csf::core::module::csf_app* new_value) {

					m_app = (csf::core::module::csf_app*)new_value;
				}
			protected:
				/**
				 * 表示主配置文件文件列表节点的路径信息。
				 */
				inline const csf_list<csf_string>& get_configure_files_items() {

					return m_configure_files_items;
				}
				/**
				* 该函数主要用于添加一个设备到app中。
				* 返回：true表示添加成功；false表示添加失败。
				*
				* @param app    表示目标app对象
				* @param element    表示模块配置信息
				*/
				csf_bool add_device(csf::core::module::csf_app& app, const csf_element& element);
				/**
				* 该函数主要用于添加一个设备到app中。
				* 返回：true表示添加成功；false表示添加失败。
				*
				* @param app    表示目标app对象
				* @param device    表示需添加的设备地址
				*/
				csf_bool add_device(csf::core::module::csf_app& app
					, const csf::core::module::csf_device* device);
				/**
				* 功能：该函数主要用于创建一个设备对象。
				* 返回：非空表示成功；空表示失败。
				*
				* @param app    表示目标aap对象
				* @param name    表示模块名称
				*/
				csf::core::module::csf_module* create_module(csf::core::module::csf_app& app
					, const csf_string& name);
				/**
				* 功能：该函数主要用于创建一个设备对象。
				* 返回：非空表示成功；空表示失败。
				*
				* @param app    表示目标app对象
				* @param name    表示模块名称
				*/
				inline csf::core::module::csf_device* create_device(csf::core::module::csf_app& app
					, const csf_string& name) {

					csf::core::module::csf_device			*tmp_device = csf_nullptr;


					tmp_device = dynamic_cast<csf::core::module::csf_device*>(create_module(app, name));
					if (tmp_device) {
						tmp_device->set_app(&app);
					}
					return tmp_device;
				}
				/**
				* 功能：该函数主要用于创建一个设备对象。
				* 返回：非空表示成功；空表示失败。
				*
				* @param device    表示目标device对象
				* @param name    表示模块名称
				*/
				inline csf::core::module::csf_device_io* create_device_io(csf::core::module::csf_device& device
					, const csf_string& name) {

					csf::core::module::csf_device_io			*tmp_device_io = csf_nullptr;


					tmp_device_io = dynamic_cast<csf::core::module::csf_device_io*>(create_module(*get_app(), name));
					if (tmp_device_io) {
						tmp_device_io->set_app(device.get_app());
						tmp_device_io->set_device(&device);
					}
					return tmp_device_io;
				}
				/**
				* 该函数主要用于添加一个设备到device中。
				* 返回：true表示添加成功；false表示添加失败。
				*
				* @param device    表示目标device对象
				* @param element    表示模块配置信息
				*/
				csf_bool add_device_io(csf::core::module::csf_device& device
					, const csf_element& element);
				/**
				* 该函数主要用于添加一个设备到device中。
				* 返回：true表示添加成功；false表示添加失败。
				*
				* @param device    表示目标aap对象
				* @param mid    表示模块创建的对象唯一ID
				* @param device_io    表示需添加的设备地址
				*/
				csf_bool add_device_io(csf::core::module::csf_device& device
					, const csf::core::module::csf_device_io* device_io);
				/**
				* 功能：该函数初始化app中的所有设备。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param app    表示所属的app信息
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool init_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* 功能：该函数启动app中的所有设备。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param app    表示所属的app信息
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool start_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* 功能：该函数停止app中的所有设备。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param app    表示所属的app信息
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				*/
				csf_bool stop_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager);
			private:
				/**
				 * 表示配置文件管理器地址信息
				 */
				csf_configure_manager* m_configure_manager = csf_nullptr;
				/**
				 * 表示当前的app_configure文件作用的app对象
				 */
				csf::core::module::csf_app* m_app = csf_nullptr;
				/**
				 * 表示主配置文件文件列表节点的路径信息。
				 */
				static const csf_list<csf_string> m_configure_files_items;

			};

		}

	}

}
#endif // !defined(CSF_APP_BOOTLOADER_INCLUDED_)
