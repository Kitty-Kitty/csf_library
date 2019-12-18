/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_file_multi_index_container.hpp
*
*Version: 1.0
*
*Date: 13-12月-2019 17:28:23
*
*Description: Class(csf_file_multi_index_container) 表示当前文件的描述信息以及多索引对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_FILE_MULTI_INDEX_CONTAINER_H_INCLUDED_)
#define CSF_FILE_MULTI_INDEX_CONTAINER_H_INCLUDED_

#include <iostream>
#include <ctime>
#include "boost/cstdint.hpp"
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/member.hpp"
#include "boost/multi_index/ordered_index.hpp"


using boost::multi_index_container;
using namespace boost::multi_index;


/**
 * 表示当前文件的描述信息以及多索引对象
 * @author f
 * @version 1.0
 * @created 13-12月-2019 17:28:24
 */
struct csf_file_struct
{
	/**
	 * 表示文件名称，包括扩展名
	 */
	std::string m_name = "";
	/**
	 * 表示文件的绝对路径
	 */
	std::string m_absolute = "";
	/**
	 * 表示文件的扩展名
	 */
	std::string m_extension = "";
	/**
	 * 表示文件最后一次修改的时间，用这个数据判断文件的新旧情况
	 */
	std::time_t m_lase_write_time = 0;
	/**
	 * 表示文件的大小，按bytes计算
	 */
	boost::uintmax_t m_size = 0;

	//对象构造函数
	csf_file_struct()
		: m_name("")
		, m_absolute("")
		, m_extension("")
		, m_lase_write_time(0)
		, m_size(0) {
	}

	//对象构造函数
	csf_file_struct(std::string name_
		, std::string absolute_
		, std::string extension_
		, std::time_t lase_write_time_
		, boost::uintmax_t size_) 
		: m_name(name_)
		, m_absolute(absolute_)
		, m_extension(extension_)
		, m_lase_write_time(lase_write_time_)
		, m_size(size_) {
	}
};

// struct file_name {};
// struct file_absolute {};
// struct file_extension {};
// struct file_lase_write_time {};
// struct file_size {};

/**
* 表示文件对象使用的多索引对象
* @author f
* @version 1.0
* @created 13-12月-2019 17:28:24
*/
typedef boost::multi_index_container<
csf_file_struct,
indexed_by<
 	// 索引-文件名称，包括扩展名
 	ordered_non_unique<member<csf_file_struct, std::string, &csf_file_struct::m_name>>,
 	// 索引-文件的绝对路径
 	ordered_unique<member<csf_file_struct, std::string, &csf_file_struct::m_absolute>>,
 	// 索引-文件的扩展名
 	ordered_non_unique<member<csf_file_struct, std::string, &csf_file_struct::m_extension>>,
 	// 索引-文件最后一次修改的时间，用这个数据判断文件的新旧情况
 	ordered_non_unique<member<csf_file_struct, std::time_t, &csf_file_struct::m_lase_write_time>>,
 	// 索引-文件的大小，按bytes计算
 	ordered_non_unique<member<csf_file_struct, boost::uintmax_t, &csf_file_struct::m_size>>
	>
> csf_file_multi_index_container;


typedef csf_file_multi_index_container::nth_index<0>::type file_name_index;					// 索引-文件名称，包括扩展名
typedef csf_file_multi_index_container::nth_index<1>::type file_absolute_index;				// 索引-文件的绝对路径
typedef csf_file_multi_index_container::nth_index<2>::type file_extension_index;			// 索引-文件的扩展名
typedef csf_file_multi_index_container::nth_index<3>::type file_lase_write_time_index;		// 索引-文件最后一次修改的时间，用这个数据判断文件的新旧情况
typedef csf_file_multi_index_container::nth_index<4>::type file_size_index;					// 索引-文件的大小，按bytes计算
enum file_container_index {
	file_name = 0,
	file_absolute,
	file_extension,
	file_lase_write_time,
	file_size,
};

#endif // !defined(CSF_FILE_MULTI_INDEX_CONTAINER_H_INCLUDED_)
