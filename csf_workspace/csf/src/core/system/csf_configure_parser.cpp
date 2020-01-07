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
*Date: 01-7��-2018 14:06:44
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
 * ��ʾ��configure_file�е��ļ�����ת��Ϊcsf_element���ݡ�
 * ���أ�0��ʾ�ɹ���<0��ʾ�����롣
 *
 * @param element    ��ʾ�洢���ս����csf_element����
 * @param configure_file    ��ʾԴ�ļ�������Ϣ
 */
csf_int32 csf_configure_parser::parse(csf_element& element, const csf_configure_file& configure_file) {

	csf_configure_format_type			tmp_fmt_type = csf_configure_format_type_none;


	//У����������ĺϷ���
	if (((csf_configure_file&)configure_file).is_null()) {
		return csf_failure;
	}

	//��ȡ�����ļ���ʽ��������
	tmp_fmt_type = format(((csf_configure_file&)configure_file).get_format());
	if (csf_configure_format_type_none == tmp_fmt_type) {
		return csf_failure;
	}

	//���������ļ���ʽ���ͣ����������ļ�����
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
 * �������ļ���Ϣ���浽�ļ���
 *
 * @param configure_file    ��ʾ��Ҫ������ļ���Ϣ
 * @param element    ��ʾ��Ҫ�����������Ϣ
 */
csf_int32 csf_configure_parser::save(const csf_configure_file& configure_file, const csf_element& element) {

	return 0;
}


/**
 * ��ʾ��ȡ�����ļ����ļ���ʽ
 * ���أ������ļ���ʽ��ֵ
 *
 * @param format    ��ʾ��Ҫ��ȡ�������ļ���ʽ��������
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
* ���������ļ���ʽ����ת����ʽ�����ַ���
* ���أ������ļ���ʽ�ַ�������
*
* @param fmt    ��ʾ��Ҫ��ȡ�������ļ���ʽ����
*/
#ifdef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN
#undef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN
#endif
#define CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN(type, name)	case csf_configure_format_type_ ## type: return name;
csf_string csf_configure_parser::format(const csf_configure_parser::csf_configure_format_type fmt) {

	switch (fmt) {
		CSF_CONFIGURE_FORMAT_TYPE_NAME(CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN)
	}

	//���û�в��ҵ����򷵻ؿ�����
	return format(csf_configure_format_type_none);
}
#undef CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP_GEN


/**
* ��ʾ��configure_file�е�XML�ļ�����ת��Ϊcsf_element���ݡ�
* ���أ�0��ʾ�ɹ���<0��ʾ�����롣
*
* @param element    ��ʾ�洢���ս����csf_element����
* @param configure_file    ��ʾԴ�ļ�������Ϣ
*/
csf_int32 csf_configure_parser::parse_xml(csf_element& element, const csf_configure_file& configure_file) {

	CMarkup				tmp_markup_xml;


	//��XML�����ļ�����
	if (!tmp_markup_xml.Load(((csf_configure_file&)configure_file).get_file_path())) {
		csf_log(warning, "parse xml file failed! reason: %s. file[%s]",
			tmp_markup_xml.GetError().c_str(),
			((csf_configure_file&)configure_file).get_file_path().c_str());
		
		return csf_failure;
	}

	return parse(((csf_element&)element), tmp_markup_xml);;
}

/**
* ��ʾ��configure_file�е��ļ�����ת��Ϊcsf_element���ݡ�
* ���أ�0��ʾ�ɹ���<0��ʾ�����롣
*
* @param element    ��ʾ�洢���ս����csf_element����
* @param markup    ��ʾCMarkup������XML�ļ�����
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