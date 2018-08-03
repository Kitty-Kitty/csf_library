/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 18:45:44
*
*Description: Class(csf_module_factory)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_FACTORY_INCLUDED_)
#define CSF_MODULE_FACTORY_INCLUDED_

#include "csf_mutex.hpp"
#include "csf_module_factory_printf.h"
#include "csf_module_factory_interface.hpp"
#include "csf_atomic.h"

class csf_module_factory_manager;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			* 定义两个句柄的名称
			*/
			#define csf_module_factory_create_handle_name					"create"
			#define csf_module_factory_destroy_handle_name					"destroy"

			#ifdef WIN32
			//表示错误信息缓存空间大小
			#define CSF_MODULE_FACTORY_MAX_ERROR_STRING						1024
			#endif

			typedef	csf_module* (*csf_module_create_handle)(const csf_configure_manager* conf_mg);
			typedef csf_int32 (*csf_module_destroy_handle)(const csf_module *module);


			/**
			 * 表示模块创建工厂
			 * @author fz
			 * @version 1.0
			 * @created 01-7月-2018 18:45:44
			 */
			class csf_module_factory : public csf::core::module::csf_module_factory_interface
			{

			public:
				inline explicit csf_module_factory()
					: m_count(0)
					, m_name("")
					, m_symbol_path("")
					, m_create_handle(csf_nullptr)
					, m_destroy_handle(csf_nullptr)
					, m_symbol_handle(csf_nullptr)
					, m_module_factory_manager(csf_nullptr)
					, m_configure_manager(csf_nullptr)
					, m_type(csf_module::csf_module_type::csf_module_type_none) {

				}
				/**
				 * 根据module_configure创建一个对象
				 *
				 * @param module_configure    表示模块的配置信息
				 */
				inline explicit csf_module_factory(const csf_void* mfm
					, const csf_configure_manager* cm
					, const csf_module_configure& module_configure)

					: csf_module_factory(
						mfm,
						cm,
						((csf_module_configure&)module_configure).get_name(),
						((csf_module_configure&)module_configure).get_file()) {
				}
				/**
				 * 根据模块名称和模块文件路径创建一个对象
				 *
				 * @param name    表示模块的名称
				 * @param path    表示模块动态库文件路径
				 */
				inline explicit csf_module_factory(const csf_void* mfm
					, const csf_configure_manager* cm
					, const csf_char* name, const csf_char* path)

					: m_count(0)
					, m_name(name)
					, m_symbol_path(path)
					, m_create_handle(csf_nullptr)
					, m_destroy_handle(csf_nullptr)
					, m_symbol_handle(csf_nullptr)
					, m_module_factory_manager((csf_module_factory_manager*)mfm)
					, m_configure_manager((csf_configure_manager*)cm)
					, m_type(csf_module::csf_module_type::csf_module_type_none) {


				}
				/**
				 * 根据模块名称和模块文件路径创建一个对象
				 *
				 * @param name    表示模块的名称
				 * @param path    表示模块动态库文件路径
				 */
				inline explicit csf_module_factory(const csf_void* mfm
					, const csf_configure_manager* cm
					, const csf_string& name
					, const csf_string& path)

					: csf_module_factory(mfm, cm, name.c_str(), path.c_str()) {
				}

				inline virtual ~csf_module_factory() {
					clear();
				}
				/**
				 * 表示配置管理器
				 */
				inline csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * 模块初始化
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_null);
				/**
				 * 销毁模块操作。 返回：0表示正确；<0表示错误码；
				 *
				 * @param module    表示需要销毁的模块地址
				 */
				inline virtual csf_int32 destory(const csf_module* module) {

					csf_int32					tmp_ret = 0;

					//判断是否已经加载，如果未加载则错误
					if (!is_load()) {
						csf_module_factory_log(error, csf_log_code_error,
							"symbol unload error.");
						return csf_failure;
					}

					//释放模块资源
					tmp_ret = get_destroy_handle()(module);
					if (tmp_ret) {
						csf_module_factory_log(warning, csf_log_code_warning,
							"destroy module[%p] return[%d] warning.",
							module,
							tmp_ret);
					}
					//释放完则计数减少1
					down_count();

					return tmp_ret;
				}
				/**
				 * 表示配置管理器
				 *
				 * @param newVal    newVal
				 */
				inline csf::core::base::csf_void set_configure_manager(const csf_configure_manager* newVal) {

					m_configure_manager = (csf_configure_manager*)newVal;
				}
				/**
				 * 模块启动
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_null);
				/**
				 * 创建模块操作。 返回：非空表示创建的模块地址；空表示错误；
				 *
				 * @param conf_mg    表示模块的配置项信息
				 */
				virtual csf_module * create(const csf_configure_manager* conf_mg);

				inline csf::core::base::csf_int32 get_count() {

					return m_count;
				}
				/**
				 * 模块停止
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_null);
				inline const csf_string& get_name() {

					return m_name;
				}
				/**
				 * 表示模块创建句柄
				 */
				inline csf::core::module::csf_module_create_handle get_create_handle() {

					return m_create_handle;
				}
				/**
				 * 表示模块销毁句柄
				 */
				inline csf::core::module::csf_module_destroy_handle get_destroy_handle() {

					return m_destroy_handle;
				}
				/**
				 * 打开动态链接库后返回的指针
				 */
				inline csf_void* get_symbol_handle() {

					return m_symbol_handle;
				}
				/**
				* 模块类型
				*/
				inline const csf::core::module::csf_module::csf_module_type& get_type() {

					return m_type;
				}
				/**
				* 表示模块工厂所属的工厂管理器
				*/
				inline csf_module_factory_manager* get_module_factory_manager() {

					return m_module_factory_manager;
				}
				/**
				* 功能：清空释放所有资源
				*/
				csf_void clear();
			protected:
				/**
				* 表示模块的文件目录
				*/
				inline const csf_string& get_symbol_path() {

					return m_symbol_path;
				}
				/**
				*
				* @param newVal    newVal
				*/
				inline csf_void set_count(const csf_int32 newVal) {

					m_count = newVal;
				}
				/**
				*
				* @param newVal    newVal
				*/
				inline csf_void set_name(const csf_string& newVal) {

					m_name = newVal;
				}
				/**
				* 表示模块的文件目录
				*
				* @param newVal    newVal
				*/
				inline csf_void set_symbol_path(const csf_string& newVal) {

					m_symbol_path = newVal;
				}
				/**
				* 设备模块的名称
				*
				* @param newVal    表示模块的名称
				*/
				inline csf_void set_name(const csf_char* newVal) {

					m_name = newVal;
				}
				/**
				* 表示模块的文件目录
				*
				* @param newVal    表示设置的模块动态库的文件路径
				*/
				inline csf_void set_symbol_path(const csf_char* newVal) {

					m_symbol_path = newVal;
				}
				/**
				* 表示模块创建句柄
				*
				* @param newVal    newVal
				*/
				inline csf::core::base::csf_void set_create_handle(const csf::core::module::csf_module_create_handle newVal) {
					m_create_handle = newVal;
				}
				/**
				* 表示模块销毁句柄
				*
				* @param newVal    newVal
				*/
				inline csf::core::base::csf_void set_destroy_handle(const csf::core::module::csf_module_destroy_handle newVal) {
					m_destroy_handle = newVal;
				}
				/**
				* 打开动态链接库后返回的指针
				*
				* @param newVal    newVal
				*/
				inline csf::core::base::csf_void set_symbol_handle(const csf_void* newVal) {

					m_symbol_handle = (csf_void*)newVal;
				}
				/**
				* 表示加载动态库模块。 返回：非空（csf_null）表示成功；空(csf_null)表示错误；
				*
				* @param path    表示加载模块的文件路径
				*/
				inline csf_void* load(const csf_string& path) {

					if (path.empty()) {
						return csf_nullptr;
					}

					return  load(path.c_str());
				}
				/**
				* 表示加载动态库模块。 返回：非空（csf_null）表示成功；空(csf_null)表示错误；
				*
				* @param path    表示加载模块的文件路径
				*/
				csf_void* load(const csf_char* path);
				/**
				* 卸载模块句柄
				*
				* @param symbol_handle    表示需要卸载的动态库句柄
				*/
				csf::core::base::csf_void unload(const csf_void* symbol_handle);
				/**
				* 表示模块是否已经被加载。 返回：csf_true表示已经加载；csf_false表示还没有加载。
				*/
				inline csf_bool is_load() {

					if (get_symbol_handle() && get_create_handle() && get_destroy_handle()) {
						return csf_true;
					}

					return csf_false;
				}
				/**
				* 查找动态库中的符号句柄
				*
				* @param handle    表示动态库文件句柄
				* @param name    表示需要获取的符号名称
				*/
				csf_void* find_symbol(const csf_void* handle, const csf_char* name);
				/**
				* 查找动态库中的符号句柄
				*
				* @param handle    表示动态库文件句柄
				* @param name    表示需要获取的符号名称
				*/
				inline csf_void* find_symbol(const csf_void* handle, const csf_string& name) {

					if (!handle || name.empty()) {
						return csf_nullptr;
					}

					return  find_symbol(handle, name.c_str());
				}
				/**
				* 表示初始化模块的创建和销毁句柄。 返回：true表示成功；false表示错误；
				*
				* @param path    表示加载模块的文件路径
				*/
				inline csf_bool init_handles(const csf_string& path) {

					if (path.empty()) {
						return csf_false;
					}

					return init_handles(path.c_str());
				}
				/**
				* 表示初始化模块的创建和销毁句柄。 返回：true表示成功；false表示错误；
				*
				* @param path    表示加载模块的文件路径
				*/
				csf_bool init_handles(const csf_char* path);
				/**
				* 表示增加一个计数，每次成功创建模块，则添加1。
				*/
				inline csf_void up_count() {
					++m_count;
				}
				/**
				* 表示减少一个计数，每次销毁一个模块，则减少1。
				*/
				inline csf_void down_count() {
					--m_count;
				}
				/**
				* 模块类型
				*
				* @param newVal    模块类型
				*/
				inline csf_void set_type(const csf::core::module::csf_module::csf_module_type newVal) {

					m_type = newVal;
				}
				/**
				* 表示模块工厂所属的工厂管理器
				*
				* @param newVal
				*/
				inline void set_module_factory_manager(csf_module_factory_manager* newVal) {

					m_module_factory_manager = newVal;
				}
			private:
				/**
				 * 表示模块创建的数量
				 */
				csf::core::base::csf_atomic_uint32 m_count = 0;
				/**
				 * 表示模块工厂对应的模块名称
				 */
				csf_string m_name = "";
				/**
				* 模块类型
				*/
				csf::core::module::csf_module::csf_module_type m_type = csf_module::csf_module_type::csf_module_type_none;
				/**
				 * 表示模块的文件目录
				 */
				csf_string m_symbol_path = "";
				/**
				* 表示线程安全使用的互斥锁内容
				*/
				csf_shared_mutex m_mutex;
				/**
				 * 表示模块创建句柄
				 */
				csf::core::module::csf_module_create_handle m_create_handle = csf_nullptr;
				/**
				 * 表示模块销毁句柄
				 */
				csf::core::module::csf_module_destroy_handle m_destroy_handle = csf_nullptr;
				/**
				 * 打开动态链接库后返回的指针
				 */
				csf_void* m_symbol_handle = csf_nullptr;
				/**
				 * 表示模块工厂所属的工厂管理器
				 */
				csf_module_factory_manager* m_module_factory_manager = csf_nullptr;
				/**
				 * 表示配置文件管理器
				 */
				csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
			};

		}

	}

}
#endif // !defined(CSF_MODULE_FACTORY_INCLUDED_)
