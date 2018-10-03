/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_logger.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 01-7��-2018 20:38:59
*
*Description: Class(csf_logger)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_attribute_include.h"
#include "csf_attribute_exception_critical.hpp"

using csf::core::system::csf_logger;
using csf::core::system::attribute::csf_attribute_manager;


csf_logger::csf_logger()
	: m_configure_manager(csf_nullptr)
	, m_path("")
	, m_rotation_size(0)
	, m_stored_max_size(0)
	, m_drive_min_free_size(0)
	, m_file_name_format("")
	, m_attribute_manager(new csf_attribute_manager()) {

}


/**
* ��ʾ���������ļ�������־ģ��
*
* @param configure_manager    ��ʾ�����ļ�
* @param path    ��ʾ��־�ļ��������Ŀ¼·��
*/
csf_logger::csf_logger(const csf_configure_manager* configure_manager, const csf_string path)
	: m_configure_manager((csf_configure_manager*)configure_manager)
	, m_path(path)
	, m_rotation_size(0)
	, m_stored_max_size(0)
	, m_drive_min_free_size(0)
	, m_file_name_format("")
	, m_attribute_manager(new csf_attribute_manager(configure_manager)) {

}


csf_logger::~csf_logger() {

}


/**
* ��ʾ��ǰϵͳ����־����Ĭ��notice����
*/
csf_logger_level csf_logger::m_level = csf_logger_level::csf_logger_level_notice;

/**
* ��ʾ��־�����Ӧ�������б����ݡ�
*/
const csf_unordered_map<csf_string, csf_logger_level> csf_logger::m_level_name = {
	{ "debug", csf_logger_level_debug },
	{ "normal", csf_logger_level_normal },
	{ "info", csf_logger_level_info },
	{ "notice", csf_logger_level_notice },
	{ "warning", csf_logger_level_warning },
	{ "error", csf_logger_level_error },
	{ "critical", csf_logger_level_critical },
};

/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_logger::init(const csf_configure_manager * conf_mg) {

	csf_bool						tmp_bool_ret = csf_false;
	csf_string						tmp_string_ret = "";
	csf_string						tmp_string_level = "";
	csf_logger_level				tmp_level = csf_logger_level::csf_logger_level_notice;


	//У�����������Ϣ�ĺϷ���
	if (!get_configure_manager() || !get_attribute_manager()) {

		csf_log_ex(critical, csf_log_code_critical
			, "configure_manager[%p] / attribute_manager[%p] is null."
			, get_configure_manager()
			, get_attribute_manager());

		return csf_failure;
	}

	/************************************************************************/
	/* ������־ϵͳ��Ҫ�ļ�������������Ϣ                                     */
	/************************************************************************/
	//��ʾ��־�����Ŀ¼λ��,�����ֵΪ�������Ĭ�ϵ�ϵͳ·��
	((csf_attribute_manager*)get_attribute_manager())->add(CSF_LOGGER_ATTRIBUTE_NAME(path)
		, csf_attribute_string(std::list<csf_string>{ "log_configure", "path" }));

	//��ʾ��־�ļ������Ƹ�ʽ
	((csf_attribute_manager*)get_attribute_manager())->add(CSF_LOGGER_ATTRIBUTE_NAME(format)
		, csf_attribute_string(std::list<csf_string>{ "log_configure", "format" }
			, csf_attribute_exception_critical()));

	//��־����debug/normal/info/notice/warning/error/critical
	((csf_attribute_manager*)get_attribute_manager())->add(CSF_LOGGER_ATTRIBUTE_NAME(level)
		, csf_attribute_string(std::list<csf_string>{ "log_configure", "level" }
			, csf_attribute_exception_critical()));

	//��ʾ���ļ��ع�����С����ÿ���ļ�������С��ע�⣺����ֵҪС��stored_max_size,���Ϊ:1GB
	((csf_attribute_manager*)get_attribute_manager())->add(CSF_LOGGER_ATTRIBUTE_NAME(rotation_size)
			, csf_attribute_space_size(std::list<csf_string>{ "log_size", "rotation_size" }
				, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
				, csf_attribute_boundary("(1000, n)")
				, csf_attribute_exception_critical()));

	//��ʾ��־ռ�ô�������С��stored_max_size/rotation_size��ʾ�������־�ļ�������ע�⣺��ֵҪ����rotation_size�����Ϊ:1GB
	((csf_attribute_manager*)get_attribute_manager())->add(CSF_LOGGER_ATTRIBUTE_NAME(stored_max_size)
		, csf_attribute_space_size(std::list<csf_string>{ "log_size", "stored_max_size" }
			, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
			, csf_attribute_boundary("(1000, n)")
			, csf_attribute_exception_critical()));

	//��ʾ���̿ռ���С����ʱ�����д��־��ע�⣺��ֵҪ����stored_max_size�����Ϊ:1GB
	((csf_attribute_manager*)get_attribute_manager())->add(CSF_LOGGER_ATTRIBUTE_NAME(drive_min_free_size)
		, csf_attribute_space_size(std::list<csf_string>{ "log_size", "drive_min_free_size" }
			, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
			, csf_attribute_boundary("(1000, n)")
			, csf_attribute_exception_critical()));

	/************************************************************************/

	//���������ļ����������ݣ�������־����
	tmp_string_level = ((csf_attribute_manager*)get_attribute_manager())->get_value<csf_attribute_string>(CSF_LOGGER_ATTRIBUTE_NAME(level));
	tmp_bool_ret = convert(tmp_level, tmp_string_level);
	if (!tmp_bool_ret) {
		csf_log_ex(critical, csf_log_code_critical
			, "logger unknow level_name[%s] error."
			, tmp_string_level.c_str());
		return csf_failure;
	}
	else {
		set_level(tmp_level);
	}

	//���������ļ����ݣ�������־�ļ�����ʽ
	tmp_string_ret = ((csf_attribute_manager*)get_attribute_manager())->get_value<csf_attribute_string>(CSF_LOGGER_ATTRIBUTE_NAME(format));
	if (tmp_string_ret.empty()) {
		csf_log_ex(critical, csf_log_code_critical
			, "logger format is null error.");
		return csf_failure;
	}
	else {
		set_file_name_format(tmp_string_ret);
	}

	//���������ļ����ݣ�������־�ļ�����·��
	//����ʹ����־�����ļ��е���־�����ַ�������·��Ϊ�գ���ʹ���Ѿ����ó���ָ��Ŀ¼
	//�����־û�������κ�·����Ϣ������־ϵͳ�޷���������
	tmp_string_ret = ((csf_attribute_manager*)get_attribute_manager())->get_value<csf_attribute_string>(CSF_LOGGER_ATTRIBUTE_NAME(path));
	if (!tmp_string_ret.empty()) {
		set_path(tmp_string_ret);
	}
	else {
		if (get_path().empty()) {
			csf_log_ex(critical, csf_log_code_critical
				, "logger path is null error.");
			return csf_failure;
		}
	}

	//���ø��ֿռ������Ϣ
	set_rotation_size(((csf_attribute_manager*)get_attribute_manager())->get_value<csf_attribute_space_size>(CSF_LOGGER_ATTRIBUTE_NAME(rotation_size)));
	set_stored_max_size(((csf_attribute_manager*)get_attribute_manager())->get_value<csf_attribute_space_size>(CSF_LOGGER_ATTRIBUTE_NAME(stored_max_size)));
	set_drive_min_free_size(((csf_attribute_manager*)get_attribute_manager())->get_value<csf_attribute_space_size>(CSF_LOGGER_ATTRIBUTE_NAME(drive_min_free_size)));

	csf_log_ex(notice, csf_log_code_notice
		, "init logger[rotation_size: %s  stored_max_size: %s  drive_min_free_size: %s ]."
		, ((csf_attribute_manager*)get_attribute_manager())->get_content(CSF_LOGGER_ATTRIBUTE_NAME(rotation_size)).c_str()
		, ((csf_attribute_manager*)get_attribute_manager())->get_content(CSF_LOGGER_ATTRIBUTE_NAME(stored_max_size)).c_str()
		, ((csf_attribute_manager*)get_attribute_manager())->get_content(CSF_LOGGER_ATTRIBUTE_NAME(drive_min_free_size)).c_str());

	csf_log_ex(notice, csf_log_code_notice
		, "init logger[level: \"%s\"  format: \"%s\"  path: \"%s\"]."
		, tmp_string_level.c_str()
		, get_file_name_format().c_str()
		, get_path().c_str());


	return csf_success;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_logger::start(const csf_configure_manager * conf_mg) {

	std::string				tmp_log_file_name = "";
	std::string				tmp_log_path = "";


	tmp_log_path = get_path() + CSF_LOGGER_DIRECTORY_NAME;
	tmp_log_file_name = tmp_log_path + get_file_name_format();

	try	{
		//text_ostream_backend 
		boost::shared_ptr<text_sink> tmp_text_sink_ptr(new text_sink);
		{
			text_sink::locked_backend_ptr tmp_backend = tmp_text_sink_ptr->locked_backend();

			boost::shared_ptr< std::ostream > tmp_stream(&std::clog, csf_null_deleter());

			tmp_backend->add_stream(tmp_stream);
			tmp_backend->auto_flush();
		}
		boost::log::core::get()->add_sink(tmp_text_sink_ptr);

		boost::log::formatter tmp_fmtter =
			boost::log::expressions::stream
			<< "[" << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y%m%dT%H%M%S")
			<< "]<" << log_severity
			<< ":"
			<< boost::log::expressions::if_(boost::log::expressions::has_attr("Code"))
			[
				boost::log::expressions::stream << boost::log::expressions::attr< int >("Code")
			]
			<< ">"
			<< "(" << boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type >("ThreadID") << ") "
			<< boost::log::expressions::smessage;

		// Create a text file sink
		boost::shared_ptr<file_sink> tmp_file_sink_ptr(new file_sink(
			boost::log::keywords::file_name = tmp_log_file_name,									// file name pattern
			boost::log::keywords::rotation_size = get_rotation_size(),						// rotation size, in characters
			boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0)
		));

		// Set up where the rotated files will be stored
		tmp_file_sink_ptr->locked_backend()->set_file_collector(boost::log::sinks::file::make_collector(
			boost::log::keywords::target = tmp_log_path,						 // where to store rotated files
			boost::log::keywords::max_size = get_stored_max_size(),              // maximum total size of the stored files, in bytes
			boost::log::keywords::min_free_space = get_drive_min_free_size()     // minimum free space on the drive, in bytes
		));
		// Upon restart, scan the target directory for files matching the file_name pattern
		tmp_file_sink_ptr->locked_backend()->scan_for_files();
		tmp_file_sink_ptr->locked_backend()->auto_flush();
		boost::log::core::get()->add_sink(tmp_file_sink_ptr);

		//boost::log::add_common_attributes();

		// Add some attributes too
		boost::log::core::get()->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
		//boost::log::core::get()->add_global_attribute("Severity", boost::log::attributes::constant<pc_severity_level>());
		//boost::log::core::get()->add_global_attribute("Code", boost::log::attributes::constant<int>());
		boost::log::core::get()->add_global_attribute("ThreadID", boost::log::attributes::current_thread_id());

		tmp_text_sink_ptr->set_formatter(tmp_fmtter);
		tmp_file_sink_ptr->set_formatter(tmp_fmtter);

		//set filter
		tmp_text_sink_ptr->set_filter(log_severity >= csf_logger::get_level()); // ...or specifically tagged
		tmp_file_sink_ptr->set_filter(log_severity >= csf_logger::get_level()); // ...or specifically tagged

		set_text_sink_ptr(tmp_text_sink_ptr);
		set_file_sink_ptr(tmp_file_sink_ptr);

		return csf_success;
	}
	catch (std::exception& e) {
		std::cout << "csf_logger start failure! reason:" << e.what() << std::endl;
		return csf_failure;
	}

	return csf_success;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_logger::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ��ʾ�����ļ���ַ
*
* @param new_value
*/
csf_void csf_logger::set_configure_manager(const csf_configure_manager* new_value) {

	m_configure_manager = (csf_configure_manager*)new_value;

	if (get_attribute_manager()) {
		((csf_attribute_manager*)get_attribute_manager())->set_configure_manager(new_value, std::list<csf_string>());
	}
}