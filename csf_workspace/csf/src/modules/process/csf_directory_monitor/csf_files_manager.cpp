/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_files_manager.hpp
*
*Version: 1.0
*
*Date: 13-12月-2019 17:29:45
*
*Description: Class(csf_files_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_files_manager.hpp"
#include "system_time.hpp"
#include "csf_attribute_space_size.hpp"

using csf::modules::process::csf_files_manager;
using csf::core::utils::time::system_time;
using csf::core::system::attribute::csf_attribute_space_size;


csf_files_manager::csf_files_manager()
	: m_directory("")
	, m_extension("")
	, m_rotation_size(0)
	, m_stored_max_size(0)
	, m_disk_min_free_size(0) {

}



csf_files_manager::~csf_files_manager() {

}





/**
 * 模块初始化
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_files_manager::init() {

	csf_bool		tmp_bool_ret = csf_false;


	//更新监控的目录下的所有文件
	tmp_bool_ret = refresh();
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "refresh() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "refresh() succeed!");
	}
	return 0;
}


/**
 * 模块启动
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_files_manager::start() {

	return 0;
}


/**
 * 模块停止
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_files_manager::stop() {

	return 0;
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
csf_bool csf_files_manager::set_content(std::string directory
	, std::string extension) {

	//判断输入是否为空
	if (directory.empty() || extension.empty()) {
		return csf_false;
	}

	//判断目录是否存在，不存在则返回失败
	if (!fs::is_directory(directory)) {
		return csf_false;
	}

	set_directory(directory);
	set_extension(extension);

	return csf_true;
}
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
csf_bool csf_files_manager::set_space(csf_uint64 rotation_size
	, csf_uint64 stored_max_size
	, csf_uint64 disk_min_free_size) {

	if (rotation_size >= stored_max_size) {
		return csf_false;
	}

	set_rotation_size(rotation_size);
	set_stored_max_size(stored_max_size);
	set_disk_min_free_size(disk_min_free_size);

	return csf_true;
}


/**
* 功能：
*    从操作系统文件中获取信息，刷新文件管理器中的文件列表
* 返回：
*    true  ： 表示刷新成功；
*    false ： 表示刷新失败；
*/
csf_bool csf_files_manager::refresh() {

	csf_vector<csf_file_struct>		tmp_file_list;
	csf_uint64						tmp_total_size = 0;
	fs::path						tmp_path(get_directory());


	//递归地遍历一个目录和子目录，也就是迭代整个目录结构下的所有文件
	//
	recursive_directory(tmp_file_list, tmp_path);

	{
		csf_unqiue_lock<decltype(m_modify_mutex)> tmp_modify_lock(m_modify_mutex);
		get_modify_map().clear();
	}

	{
		csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

		//清空多索引文件管理器中的所有文件对象
		get_file_container().clear();

		//更新多索引文件管理器
		for (auto &tmp_iter : tmp_file_list) {
			get_file_container().insert(tmp_iter);
			tmp_total_size += tmp_iter.m_size;
		}

		//更新当前目录的总大小
		set_stored_size(tmp_total_size);

		csf_log(notice
			, "[file number: %d | total size: %s | directory: %s ]"
			, get_file_container().size()
			, csf_attribute_space_size::format_string(tmp_total_size).c_str()
			, get_directory().c_str()
		);

	}

	return csf_true;
}


/**
* 功能：
*    添加新文件
* 返回：
*    true  ： 表示成功；
*    false ： 表示失败；
*
* @param file_absolute    表示文件的绝对路径
*/
csf_bool csf_files_manager::add(std::string file_absolute) {

	{
		csf_unqiue_lock<decltype(m_modify_mutex)> tmp_modify_lock(m_modify_mutex);
		refresh_modify_map();
	}

	{
		csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);
		return update_file(file_absolute);
	}

	return csf_true;
}


/**
* 功能：
*    删除文件
* 返回：
*    true  ： 表示成功；
*    false ： 表示失败；
*
* @param file_absolute    表示文件的绝对路径
*/
csf_bool csf_files_manager::remove(std::string file_absolute) {

	csf_log(notice, "remove a file[%s].", file_absolute.c_str());

	{
		csf_unqiue_lock<decltype(m_modify_mutex)> tmp_modify_lock(m_modify_mutex);
		get_modify_map().erase(file_absolute);
	}

	{
		csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);
		return update_file(file_absolute);
	}

	return csf_true;
}


/**
* 功能：
*    更新文件
* 返回：
*    true  ： 表示成功；
*    false ： 表示失败；
*
* @param file_absolute    表示文件的绝对路径
*/
csf_bool csf_files_manager::modify(std::string file_absolute) {

	csf_unordered_map<csf_string, csf_file_struct>::iterator  tmp_iter;


	{
		csf_unqiue_lock<decltype(m_modify_mutex)> tmp_modify_lock(m_modify_mutex);

		tmp_iter = get_modify_map().find(file_absolute);
		if (tmp_iter == get_modify_map().end()) {
			//如果修改列表中不存在指定文件，则更新指定文件修改信息
			csf_file_struct   tmp_file_struct;

			tmp_file_struct.m_absolute = file_absolute;
			tmp_file_struct.m_lase_write_time = system_time::get_time();
			tmp_file_struct.m_size = 0;

			get_modify_map().insert(std::make_pair(file_absolute, tmp_file_struct));

			return csf_true;
		}
		//如果时间超过修改更新时间，则需要重新计算空间大小
		if (system_time::get_time() - tmp_iter->second.m_lase_write_time
			<= get_modify_update_time()) {
			tmp_iter->second.m_size++;
			return csf_true;
		}
		else {
			tmp_iter->second.m_lase_write_time = system_time::get_time();
		}
	}

	{
		csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);
		return update_file(file_absolute);
	}


	return csf_true;
}


/**
* 功能：
*    重新命名文件
* 返回：
*    true  ： 表示成功；
*    false ： 表示失败；
*
* @param file_absolute    表示文件的绝对路径
*/
csf_bool csf_files_manager::rename(std::string file_absolute) {

	{
		csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);
		return update_file(file_absolute);
	}
}


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
csf_bool csf_files_manager::recursive_directory(csf_vector<csf_file_struct>& dest
	, fs::path& path) {

	csf_vector<std::string>			tmp_files;
	csf_file_struct					tmp_file_struct;


	//递归地遍历一个目录和子目录，也就是迭代整个目录结构下的所有文件
	recursive_directory(tmp_files, path);

	for (auto &tmp_iter : tmp_files) {

		if (get_file_struct(tmp_file_struct, tmp_iter)) {
			dest.push_back(tmp_file_struct);
		}
		else {
			csf_log(warning
				, "get file information failed! file[ %s ]."
				, tmp_iter.c_str()
			);
		}
	}

	return csf_true;
}


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
csf_bool csf_files_manager::recursive_directory(csf_vector<std::string>& dest
	, fs::path& path) {

	if (fs::exists(path) && fs::is_directory(path)) {

		// Create a Recursive Directory Iterator object and points to the starting of directory
		fs::recursive_directory_iterator iter(path);

		// Create a Recursive Directory Iterator object pointing to end.
		fs::recursive_directory_iterator end;

		// Iterate till end
		while (iter != end) {

			// Check if current entry is a directory and if exists in skip list
			if (fs::is_directory(iter->path()) &&
				(std::find(dest.begin(), dest.end(), iter->path().filename()) != dest.end())) {
				// Skip the iteration of current directory pointed by iterator
#ifdef BOOST_FILESYSTEM_FILESYSTEM_HPP
				// Boost Fileystsem  API to skip current directory iteration
				iter.no_push();
#else
				// c++17 Filesystem API to skip current directory iteration
				iter.disable_recursion_pending();
#endif
			}
			else
			{
				// Add the name in vector
				dest.push_back(iter->path().string());
			}

			error_code tmp_ec;
			// Increment the iterator to point to next entry in recursive iteration
			iter.increment(tmp_ec);
			if (tmp_ec) {
				csf_log(warning
					, "error while accessing. directory[%s] error_code[%d]: %s."
					, iter->path().string().c_str()
					, tmp_ec.value()
					, tmp_ec.message().c_str()
				);
				//std::cerr << "Error While Accessing: " << iter->path().string() << " :: " << tmp_ec.message() << '\n';
			}
		}
	}

	return csf_true;
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
csf::core::base::csf_uint64 csf_files_manager::free_space(csf_uint64 size
	, std::string extension) {

	csf_uint64			tmp_int_ret = 0;
	csf_uint64			tmp_total_size = 0;


	//循环删除指定扩展名的最旧文件
	while (tmp_total_size < size) {

		tmp_int_ret = delete_old_file(extension);
		if (tmp_int_ret <= 0) {
			//如果为0表示已经没有可以删除的文件了
			//则直接退出
			return tmp_total_size;
		}
		else {
			tmp_total_size += tmp_int_ret;
		}
	}

	return tmp_total_size;
}


/**
* 功能：
*    表示删除一个指定文件扩展名的创建时间最久的文件。
* 返回：
*    表示处理后，实际释放的空间大小。如果为0，表示没有可以被删除的指定文件。
*
* @param extension    表示允许被删除的指定文件扩展名
*/
csf::core::base::csf_uint64 csf_files_manager::delete_old_file(std::string extension) {

	auto				&tmp_file = get_file_container().get<file_lase_write_time>();
	csf_uint64			tmp_int_ret = 0;
	file_lase_write_time_index::iterator	tmp_iter;


	//从多索引列表中，获取第一个时间最小的对象（时间最小则表示越久）
	for (tmp_iter = tmp_file.begin(); tmp_iter != tmp_file.end(); tmp_iter++) {
		if (tmp_iter->m_extension == extension) {
			tmp_int_ret = delete_file(tmp_iter->m_absolute);
			tmp_file.erase(tmp_iter);
			return tmp_int_ret;
		}
	}

	return 0;
}


/**
* 功能：
*    表示删除一个指定文件。
* 返回：
*    表示处理后，实际释放的空间大小。如果为0，表示没有可以被删除的指定文件。
*
* @param path    表示允许被删除的指定文件
*/
csf::core::base::csf_uint64 csf_files_manager::delete_file(fs::path& path) {

	error_code					tmp_ec;
	csf::core::base::csf_uint64	tmp_size = get_file_size(path);


	if (boost::filesystem::remove(path, tmp_ec)) {
		csf_log(notice
			, "delete file succeed! [size: %s | file: %s]"
			, csf_attribute_space_size::format_string(tmp_size).c_str()
			, path.string().c_str()
		);
		return tmp_size;
	}
	else {
		csf_log(error
			, "delete file[ %s ] failed! error_code[ %d ]: %s"
			, path.string().c_str()
			, tmp_ec.value()
			, tmp_ec.message().c_str()
		);
	}
	return 0;
}


/**
* 功能：
*    表示更新一个指定文件。
* 返回：
*    true  ：  表示更新成功；
*    false ：  表示更新失败；
*
* @param path    表示允许被删除的指定文件
*/
csf_bool csf_files_manager::update_file(fs::path& path) {

	csf_file_struct		tmp_file_struct;
	csf_string			tmp_file_absolute = fs::absolute(path).string();
	auto				&tmp_file = get_file_container().get<file_absolute>();
	file_absolute_index::iterator	tmp_iter;


	//查找需要的文件
	tmp_iter = tmp_file.find(tmp_file_absolute);
	if (tmp_iter == tmp_file.end()) {
		//如果不在之前的统一列表之中，则准备进行新增处理
		if (!get_file_struct(tmp_file_struct, path)) {
			//如果不在列表中，也不存在文件，则不做处理
			return csf_true;
		}
		else {
			//如果不在列表，但文件存在，则添加文件
			get_file_container().insert(tmp_file_struct);
			set_stored_size(get_stored_size() + tmp_file_struct.m_size);

			csf_log(notice
				, "add a new file. [size: %s | file: %s]"
				, csf_attribute_space_size::format_string(tmp_file_struct.m_size).c_str()
				, tmp_file_absolute.c_str()
			);

			//根据当前的系统存储情况，刷新当前存储
			return refresh_stored_disk();
		}
	}
	else {
		//如已经在列表中，则准备进行更新处理
		if (!get_file_struct(tmp_file_struct, path)) {
			//如果信息获取失败，则删除对应的文件
			set_stored_size((csf_int64)get_stored_size() - tmp_iter->m_size);

			csf_log(warning
				, "free a file space. [size: %s | file: %s]"
				, csf_attribute_space_size::format_string(tmp_iter->m_size).c_str()
				, tmp_file_absolute.c_str()
			);

			tmp_file.erase(tmp_iter);

			return csf_false;
		}
		else {
			//如果信息获取成功，则更新系统保存信息
			csf_int64		tmp_update_size = (csf_int64)tmp_file_struct.m_size - tmp_iter->m_size;
			set_stored_size((csf_int64)get_stored_size() + tmp_update_size);
			const_cast<csf_file_struct&>(*tmp_iter).m_lase_write_time = tmp_file_struct.m_lase_write_time;
			const_cast<csf_file_struct&>(*tmp_iter).m_size = tmp_file_struct.m_size;

			csf_log(notice
				, "update a file size. [size: %s | file: %s]"
				, csf_attribute_space_size::format_string(tmp_update_size).c_str()
				, tmp_file_absolute.c_str()
			);

			//根据当前的系统存储情况，刷新当前存储
			return refresh_stored_disk();
		}
	}

	return csf_false;
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
csf_bool csf_files_manager::get_file_struct(csf_file_struct& dest, fs::path& path) {

	if (fs::exists(path) && fs::is_regular_file(path)) {

		dest.m_name = path.filename().string();
		dest.m_absolute = fs::absolute(path).string();
		dest.m_extension = path.extension().string();
		dest.m_lase_write_time = fs::last_write_time(path);
		dest.m_size = fs::file_size(path);

		return csf_true;
	}
	return csf_false;
}


/**
* 功能：
*    获取文件大小，单位：字节（bytes）。
* 返回：
*    表示处理后，实际释放的空间大小。获取异常都返回0。
*
* @param path    表示允许被删除的指定文件
*/
csf_uint64 csf_files_manager::get_file_size(fs::path& path) {

	if (fs::exists(path) && fs::is_regular_file(path)) {
		return fs::file_size(path);
	}
	return 0;
}


/**
* 功能：
*    根据当前的系统现有存储情况，刷新存储文件，保证系统存储空间在合理的范围内
* 返回：
*    true  ： 表示刷新成功；
*    false ： 表示刷新失败；
*/
csf_bool csf_files_manager::refresh_stored_disk() {

	csf_uint64			tmp_size = 0;

	while (csf_true) {

		//判断存储与目录空间的合法性
		if (is_stored_size_valid() && is_disk_size_valid()) {
			return csf_true;
		}

		//如果存储与目录非法，则删除最久的指令扩展名文件，从而释放空间。
		tmp_size = delete_old_file(get_extension());
		if (tmp_size <= 0) {
			csf_log(error
				, "free disk space failed! not other file by extension[%s]."
				, get_extension().c_str()
			);
			return csf_false;
		}
		else {
			//删除文件成功，则更新当前空间大小
			set_stored_size(get_stored_size() - tmp_size);
		}
	}

	return csf_true;
}


/**
* 功能：
*    刷新更新列表中的所有正在更新的文件信息
* 返回：
*    true  ： 表示刷新成功；
*    false ： 表示刷新失败；
*/
csf_bool csf_files_manager::refresh_modify_map() {

	csf_unordered_map<csf_string, csf_file_struct>::iterator	tmp_iter;


	for (tmp_iter = get_modify_map().begin(); tmp_iter != get_modify_map().end();) {

		//如果时间超过修改更新时间，则需要重新计算空间大小
		if (system_time::get_time() - tmp_iter->second.m_lase_write_time
			>= get_modify_update_time()) {

			if (tmp_iter->second.m_size > 0) {
				tmp_iter->second.m_size = 0;
				tmp_iter++;
			}
			else {
				{
					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);
					update_file(tmp_iter->first);
				}

				tmp_iter = get_modify_map().erase(tmp_iter);
			}
		}
		else {
			tmp_iter++;
		}
	}
	return csf_true;
}


/**
* 功能：
*    校验目录存储空间的合法性
* 返回：
*    true  ：  表示合法；
*    false ：  表示不合法；
*/
csf_bool csf_files_manager::is_stored_size_valid() {
	if (get_stored_size() > get_stored_max_size()) {
		csf_log(error
			, "disk stored size[%s] more than disk stored max size[%s]."
			, csf_attribute_space_size::format_string(get_stored_size()).c_str()
			, csf_attribute_space_size::format_string(get_stored_max_size()).c_str()
		);
		return csf_false;
	}
	return csf_true;
}


/**
* 功能：
*    校验磁盘存储空间的合法性
* 返回：
*    true  ：  表示合法；
*    false ：  表示不合法；
*/
csf_bool csf_files_manager::is_disk_size_valid() {

	fs::path		tmp_path(get_directory());
	error_code		tmp_ec;

	fs::space_info tmp_space_info = fs::space(tmp_path, tmp_ec);
	if (tmp_ec) {
		csf_log(error
			, "get disk space failed! directory[%s] error_code[%d]: %s."
			, get_directory().c_str()
			, tmp_ec.value()
			, tmp_ec.message().c_str()
		);
		return csf_true;
	}
	else {
		//
		// space 所确定的文件系统信息。
		//	成员拥有下列含义：
		//		capacity   ——文件系统的总大小，以字节计
		//		free       ——文件系统的空闲空间，以字节计
		//		available  ——无特权进程可用的空闲空间(可以小于或等于 free)
		//
		//如果存储空间不足，则返回非法
		if (get_disk_min_free_size() >= tmp_space_info.available) {
			csf_log(error
				, "disk space available[%s] less than disk_min_free_size[%s]."
				, csf_attribute_space_size::format_string(tmp_space_info.available).c_str()
				, csf_attribute_space_size::format_string(get_disk_min_free_size()).c_str()
			);
			return csf_false;
		}
	}

	return csf_true;
}