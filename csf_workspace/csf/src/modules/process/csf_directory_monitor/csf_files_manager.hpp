/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_files_manager.hpp
*
*Version: 1.0
*
*Date: 13-12月-2019 17:29:45
*
*Description: Class(csf_files_manager) 主要实现指定目录的空间回滚功能。当目录中的文件空间大于指定大小时，将采取删除最久文件的，释放空间，以避免磁盘空间全部被占用。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_FILES_MANAGER_H_INCLUDED_)
#define CSF_FILES_MANAGER_H_INCLUDED_

#include "boost/filesystem.hpp"
#include "csf_typedef.h"
#include "csf_atomic.h"
#include "csf_mutex.hpp"
#include "csf_file_multi_index_container.hpp"
#include "csf_stdcollector.hpp"

using namespace csf::core::base;
namespace		fs = boost::filesystem;
typedef boost::system::error_code  error_code;

namespace csf
{
	namespace modules
	{
		namespace process
		{
			/**
			 * 主要实现指定目录的空间回滚功能。当目录中的文件空间大于指定大小时，将采取删除最久文件的，释放空间，以避免磁盘空间全部被占用。
			 * @author f
			 * @version 1.0
			 * @created 13-12月-2019 17:29:45
			 */
			class csf_files_manager
			{

			public:
				csf_files_manager();
				virtual ~csf_files_manager();

				/**
				 * 模块初始化
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init();
				/**
				 * 模块启动
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start();
				/**
				 * 模块停止
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop();
				/**
				 * 需要被监视的目录地址
				 */
				inline std::string get_directory() {

					return m_directory;
				}
				/**
				 * 需要被监视的目录地址
				 *
				 * @param newVal
				 */
				inline void set_directory(std::string newVal) {

					m_directory = newVal;
				}
				/**
				 * 被监控的文件扩展名（取值如:mp4、txt、log等）（当空间不足时，最久创建的该种文件将被删除释放空间）
				 */
				inline std::string get_extension() {

					return m_extension;
				}
				/**
				 * 被监控的文件扩展名（取值如:mp4、txt、log等）（当空间不足时，最久创建的该种文件将被删除释放空间）
				 *
				 * @param newVal
				 */
				inline void set_extension(std::string newVal) {

					m_extension = newVal;
				}
				/**
				 * 表示单文件回滚大小，每次释放空间时需要释放的空间大小。这也可以理解为最小空间大小。注意：该数值要小于stored_max_size
				 */
				inline csf_uint64 get_rotation_size() {

					return m_rotation_size;
				}
				/**
				 * 表示单文件回滚大小，每次释放空间时需要释放的空间大小。这也可以理解为最小空间大小。注意：该数值要小于stored_max_size
				 *
				 * @param newVal
				 */
				inline void set_rotation_size(csf_uint64 newVal) {

					m_rotation_size = newVal;
				}
				/**
				 * 表示目录中所有文件占用磁盘最大大小。注意：该值要大于rotation_size
				 */
				inline csf_uint64 get_stored_max_size() {

					return m_stored_max_size;
				}
				/**
				 * 表示目录中所有文件占用磁盘最大大小。注意：该值要大于rotation_size
				 *
				 * @param newVal
				 */
				inline void set_stored_max_size(csf_uint64 newVal) {

					m_stored_max_size = newVal;
				}
				/**
				 * 表示磁盘空间最小多大的时候才能往目录中保存文件。注意：该值要大于stored_max_size
				 */
				inline csf_uint64 get_disk_min_free_size() {

					return m_disk_min_free_size;
				}
				/**
				 * 表示磁盘空间最小多大的时候才能往目录中保存文件。注意：该值要大于stored_max_size
				 *
				 * @param newVal
				 */
				inline void set_disk_min_free_size(csf_uint64 newVal) {

					m_disk_min_free_size = newVal;
				}
				/**
				* 表示文件修改到真正更新数据的间隔时间，为了减少频繁的获取系统数据而增加负载。单位为：毫秒
				*/
				inline csf_uint64 get_modify_update_time() {

					return m_modify_update_time;
				}
				/**
				* 表示文件修改到真正更新数据的间隔时间，为了减少频繁的获取系统数据而增加负载。单位为：毫秒
				*
				* @param newVal
				*/
				inline void set_modify_update_time(csf_uint64 newVal) {

					m_modify_update_time = newVal;
				}
				/**
				* 功能：
				*    设置文件管理器的内容，主要包含文件目录和文件扩展名
				* 返回：
				*    无
				*
				* @param directory    需要被监视的目录地址
				* @param extension    被监控的文件扩展名（取值如:mp4、txt、log等）
				*/
				csf_bool set_content(std::string directory, std::string extension);
				/**
				* 功能：
				*    设置文件管理器的空间信息
				* 返回：
				*    无
				*
				* @param rotation_size    表示单文件回滚大小，每次释放空间时需要释放的空间大小。这也可以理解为最小空间大小。
				* @param stored_max_size    表示目录中所有文件占用磁盘最大大小。注意：该值要大于rotation_size
				* @param disk_min_free_size    表示磁盘空间最小多大的时候才能往目录中保存文件。注意：该值要大于stored_max_size
				*/
				csf_bool set_space(csf_uint64 rotation_size
					, csf_uint64 stored_max_size
					, csf_uint64 disk_min_free_size);

				/**
				* 功能：
				*    从操作系统文件中获取信息，刷新文件管理器中的文件列表
				* 返回：
				*    true  ： 表示刷新成功；
				*    false ： 表示刷新失败；
				*/
				csf_bool refresh();
				/**
				* 功能：
				*    添加新文件
				* 返回：
				*    true  ： 表示成功；
				*    false ： 表示失败；
				*
				* @param file_absolute    表示文件的绝对路径
				*/
				csf_bool add(std::string file_absolute);
				/**
				* 功能：
				*    删除文件
				* 返回：
				*    true  ： 表示成功；
				*    false ： 表示失败；
				*
				* @param file_absolute    表示文件的绝对路径
				*/
				csf_bool remove(std::string file_absolute);
				/**
				* 功能：
				*    更新文件
				* 返回：
				*    true  ： 表示成功；
				*    false ： 表示失败；
				*
				* @param file_absolute    表示文件的绝对路径
				*/
				csf_bool modify(std::string file_absolute);
				/**
				* 功能：
				*    重新命名文件
				* 返回：
				*    true  ： 表示成功；
				*    false ： 表示失败；
				*
				* @param file_absolute    表示文件的绝对路径
				*/
				csf_bool rename(std::string file_absolute);
			protected:
				/**
				* 功能：
				*    根据当前的系统现有存储情况，刷新存储文件，保证系统存储空间在合理的范围内
				* 返回：
				*    true  ： 表示刷新成功；
				*    false ： 表示刷新失败；
				*/
				csf_bool refresh_stored_disk();
				/**
				* 功能：
				*    刷新更新列表中的所有正在更新的文件信息
				* 返回：
				*    true  ： 表示刷新成功；
				*    false ： 表示刷新失败；
				*/
				csf_bool refresh_modify_map();
			private:
				/**
				* 功能：
				*    递归目录下的所有文件信息，并将文件信息保存在目标集合中。
				* 返回：
				*    true  ：  表示成功；
				*    false ：  表示失败；
				*
				* @param dest    表示获取的文件信息所保存的目标集合
				* @param path    表示需要遍历的目录
				*/
				csf_bool recursive_directory(csf_vector<csf_file_struct>& dest, boost::filesystem::path& path);
				/**
				* 功能：
				*    递归目录下的所有文件路径，并存放到目标集合中。
				* 返回：
				*    true  ：  表示成功；
				*    false ：  表示失败；
				*
				* @param dest    表示获取的文件信息所保存的目标集合
				* @param path    表示需要遍历的目录
				*/
				csf_bool recursive_directory(csf_vector<std::string>& dest, boost::filesystem::path& path);
				/**
				* 表示满足文件需要的多索引容器对象
				*/
				inline csf_file_multi_index_container& get_file_container() {

					return m_file_container;
				}
				/**
				* 表示多线程处理安全锁对象
				*/
				inline csf_shared_mutex& get_mutex() {

					return m_mutex;
				}
				/**
				* 表示文件修改多线程处理安全锁对象
				*/
				inline csf_shared_mutex& get_modify_mutex() {

					return m_modify_mutex;
				}
				/**
				* 表示当前目录中所有文件的总大小，单位：字节
				*/
				inline csf_uint64 get_stored_size() {

					return m_stored_size;
				}
				/**
				* 表示当前目录中所有文件的总大小，单位：字节
				*
				* @param newVal
				*/
				inline void set_stored_size(csf_uint64 newVal) {

					m_stored_size = newVal;
				}
				/**
				* 功能：
				*    表示释放至少指定大小的存储空间大小。实现过程为：删除指定文件扩展名的文件，直到释放得到指定的大小空间。
				* 返回：
				*    表示处理后，实际释放的空间大小。如果为0，表示没有可以被删除的指定文件。
				*
				* @param size    表示需要释放的磁盘空间大小，单位：字节(bytes)
				* @param extension    表示允许被删除的指定文件扩展名
				*/
				csf::core::base::csf_uint64 free_space(csf_uint64 size, std::string extension);
				/**
				* 功能：
				*    表示删除一个指定文件扩展名的创建时间最久的文件。
				* 返回：
				*    表示处理后，实际释放的空间大小。如果为0，表示没有可以被删除的指定文件。
				*
				* @param extension    表示允许被删除的指定文件扩展名
				*/
				csf::core::base::csf_uint64 delete_old_file(std::string extension);
				/**
				* 功能：
				*    表示删除一个指定文件。
				* 返回：
				*    表示处理后，实际释放的空间大小。如果为0，表示没有可以被删除的指定文件。
				*
				* @param file    表示允许被删除的指定文件
				*/
				inline csf::core::base::csf_uint64 delete_file(std::string file) {
					fs::path		tmp_path(file);
					return delete_file(tmp_path);
				}
				/**
				* 功能：
				*    表示删除一个指定文件。
				* 返回：
				*    表示处理后，实际释放的空间大小。如果为0，表示没有可以被删除的指定文件。
				*
				* @param path    表示允许被删除的指定文件
				*/
				csf::core::base::csf_uint64 delete_file(fs::path& path);
				/**
				* 功能：
				*    表示更新一个指定文件。
				* 返回：
				*    true  ：  表示更新成功；
				*    false ：  表示更新失败；
				*
				* @param path    表示允许被删除的指定文件
				*/
				csf_bool update_file(fs::path& path);
				/**
				* 功能：
				*    表示更新一个指定文件。
				* 返回：
				*    true  ：  表示更新成功；
				*    false ：  表示更新失败；
				*
				* @param file    表示允许被删除的指定文件
				*/
				inline csf_bool update_file(std::string file) {
					fs::path		tmp_path(file);
					return update_file(tmp_path);
				}
				/**
				* 功能：
				*    获取指定文件的文件详细信息。
				* 返回：
				*    true  ：  表示成功；
				*    false ：  表示失败
				*
				* @param dest    获取到的文件信息保存在对应信息结构体
				* @param file    表示指定文件
				*/
				inline csf_bool get_file_struct(csf_file_struct& dest, std::string file) {
					fs::path		tmp_path(file);
					return get_file_struct(dest, tmp_path);
				}
				/**
				* 功能：
				*    获取指定文件的文件详细信息。
				* 返回：
				*    true  ：  表示成功；
				*    false ：  表示失败
				*
				* @param dest    获取到的文件信息保存在对应信息结构体
				* @param path    表示指定文件
				*/
				csf_bool get_file_struct(csf_file_struct& dest, fs::path& path);
				/**
				* 功能：
				*    获取文件大小，单位：字节（bytes）。
				* 返回：
				*    表示处理后，实际释放的空间大小。获取异常都返回0。
				*
				* @param path    表示允许被删除的指定文件
				*/
				csf_uint64 get_file_size(fs::path& path);
				/**
				* 用于保存当前存在修改的文件信息
				*/
				inline csf_unordered_map<csf_string, csf_file_struct>& get_modify_map() {

					return m_modify_map;
				}
				/**
				* 功能：
				*    校验目录存储空间的合法性
				* 返回：
				*    true  ：  表示合法；
				*    false ：  表示不合法；
				*/
				inline csf_bool is_stored_size_valid();
				/**
				* 功能：
				*    校验磁盘存储空间的合法性
				* 返回：
				*    true  ：  表示合法；
				*    false ：  表示不合法；
				*/
				inline csf_bool is_disk_size_valid();
			private:
				/**
				 * 需要被监视的目录地址
				 */
				std::string m_directory = "";
				/**
				 * 被监控的文件扩展名（取值如:mp4、txt、log等）（当空间不足时，最久创建的该种文件将被删除释放空间）
				 */
				std::string m_extension = "";
				/**
				 * 表示单文件回滚大小，每次释放空间时需要释放的空间大小。这也可以理解为最小空间大小。注意：该数值要小于stored_max_size
				 */
				csf_uint64 m_rotation_size = 0;
				/**
				* 表示当前目录中所有文件的总大小，单位：字节
				*/
				csf_atomic_uint64 m_stored_size{ 0 };
				/**
				 * 表示目录中所有文件占用磁盘最大大小。注意：该值要大于rotation_size
				 */
				csf_uint64 m_stored_max_size = 0;
				/**
				 * 表示磁盘空间最小多大的时候才能往目录中保存文件。注意：该值要大于stored_max_size
				 */
				csf_uint64 m_disk_min_free_size = 0;
				/**
				* 表示满足文件需要的多索引容器对象
				*/
				csf_file_multi_index_container m_file_container;
				/**
				* 用于保存当前存在修改的文件信息
				*/
				csf_unordered_map<csf_string, csf_file_struct> m_modify_map;
				/**
				* 表示多线程处理安全锁对象
				*/
				csf_shared_mutex m_mutex;
				/**
				* 表示文件修改多线程处理安全锁对象
				*/
				csf_shared_mutex m_modify_mutex;
				/**
				* 表示文件修改到真正更新数据的间隔时间，为了减少频繁的获取系统数据而增加负载。单位为：毫秒
				*/
				csf_uint64 m_modify_update_time = 2000;
			};

		}

	}

}
#endif // !defined(CSF_FILES_MANAGER_H_INCLUDED_)
