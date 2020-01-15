/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure_parser.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 14:06:44
*
*Description: Class(csf_configure_parser)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_configure_parser.hpp"

using csf::core::system::csf_configure_parser;


csf_configure_parser::csf_configure_parser() {

}



csf_configure_parser::~csf_configure_parser() {

}





/**
 * 表示将configure_file中的文件内容转换为csf_element内容。
 * 返回：0表示成功；<0表示错误码。
 *
 * @param element    表示存储最终结果的csf_element对象
 * @param configure_file    表示源文件描述信息
 */
csf_int32 csf_configure_parser::parse(csf_element& element, const csf_configure_file& configure_file) {

	csf_configure_format_type			tmp_fmt_type = csf_configure_format_type_none;


	//校验输入参数的合法性
	if (((csf_configure_file&)configure_file).is_null()) {
		return csf_failure;
	}

	//获取配置文件格式类型数据
	tmp_fmt_type = format(((csf_configure_file&)configure_file).get_format());
	if (csf_configure_format_type_none == tmp_fmt_type) {
		return csf_failure;
	}

	//根据配置文件格式类型，解析配置文件内容
	switch (tmp_fmt_type) {

	case csf_configure_format_type_xml:
	{
		return parse_xml(element, configure_file);
	}
	break;
	default:
	{
		return csf_failure;
	}
	break;
	}

	return csf_succeed;
}


/**
 * 将配置文件信息保存到文件中
 *
 * @param configure_file    表示需要保存的文件信息
 * @param element    表示需要保存的配置信息
 */
csf_int32 csf_configure_parser::save(const csf_configure_file& configure_file, const csf_element& element) {

	return 0;
}


/**
 * 表示获取配置文件的文件格式
 * 返回：配置文件格式数值
 *
 * @param format    表示需要获取的配置文件格式类型数据
 */
#ifdef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN
#undef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN
#endif
#define CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN(type, name)	if (!csf_strcmp(fmt, name)) {return csf_configure_format_type_ ## type;}
csf_configure_parser::csf_configure_format_type csf_configure_parser::format(const csf_char* fmt) {

	if (!fmt || csf_strlen(fmt) <= 0) {
		return  csf_configure_format_type_none;
	}

	CSF_CONFIGURE_FORMAT_TYPE_NAME(CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN)

	return  csf_configure_format_type_none;
}
#undef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN



/**
* 根据配置文件格式类型转换格式类型字符串
* 返回：配置文件格式字符串描述
*
* @param fmt    表示需要获取的配置文件格式类型
*/
#ifdef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN
#undef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN
#endif
#define CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN(type, name)	case csf_configure_format_type_ ## type: return name;
csf_string csf_configure_parser::format(const csf_configure_parser::csf_configure_format_type fmt) {

	switch (fmt) {
		CSF_CONFIGURE_FORMAT_TYPE_NAME(CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN)
	}

	//如果没有查找到，则返回空类型
	return format(csf_configure_format_type_none);
}
#undef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN


/**
* 表示将configure_file中的XML文件内容转换为csf_element内容。
* 返回：0表示成功；<0表示错误码。
*
* @param element    表示存储最终结果的csf_element对象
* @param configure_file    表示源文件描述信息
*/
csf_int32 csf_configure_parser::parse_xml(csf_element& element, const csf_configure_file& configure_file) {

	CMarkup				tmp_markup_xml;


	//打开XML配置文件内容
	if (!tmp_markup_xml.Load(((csf_configure_file&)configure_file).get_file_path())) {
		csf_log(warning, "parse xml file failed! reason: %s. file[%s]",
			tmp_markup_xml.GetError().c_str(),
			((csf_configure_file&)configure_file).get_file_path().c_str());
		
		return csf_failure;
	}

	return parse(((csf_element&)element), tmp_markup_xml);;
}

/**
* 表示将configure_file中的文件内容转换为csf_element内容。
* 返回：0表示成功；<0表示错误码。
*
* @param element    表示存储最终结果的csf_element对象
* @param markup    表示CMarkup解析的XML文件对象
*/
csf_int32 csf_configure_parser::parse(csf_element& element, CMarkup& markup) {

	csf_string								tmp_name = "";
	csf_string								tmp_value = "";


	markup.ResetMainPos();
	while (markup.FindElem()) {

		csf_element			tmp_child_element;

		tmp_child_element.set_name(clear_head_tail_space(markup.GetTagName()));
		for (csf_int32 i = 0; ; i++) {

			tmp_name = clear_head_tail_space(markup.GetAttribName(i));
			if (tmp_name.empty()) {
				break;
			}

			tmp_value = clear_head_tail_space(markup.GetAttrib(tmp_name));
			tmp_child_element.add(tmp_name, tmp_value);
		}

		while (markup.FindChildElem()) {
			markup.IntoElem();
			parse(tmp_child_element, markup);
			markup.OutOfElem();
		}

		if (tmp_child_element.not_null()) {
			tmp_child_element.set_content(clear_head_tail_space(markup.GetElemContent()));
			
			if (element.is_null()) {
				element = tmp_child_element;
			}
			else {
				element.add(tmp_child_element);
			}
		}
	}

	return csf_succeed;
}