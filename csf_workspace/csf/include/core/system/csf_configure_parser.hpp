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

#if !defined(CSF_CONFIGURE_PARSER_INCLUDED_)
#define CSF_CONFIGURE_PARSER_INCLUDED_


//#include "csf_configure.hpp"
#include "csf_markup_xml.hpp"
#include "csf_configure_file.hpp"
#include "csf_element.hpp"


using namespace csf::core::system;

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * ��ʾ����ת�������ݣ���Ҫ���𼸸���Ҫ�������͵Ľ�����ת��
			 * @author Administrator
			 * @version 1.0
			 * @created 01-7��-2018 14:06:44
			 */
			class csf_configure_parser
			{

			public:
				/**
				 * ��ʾ�����ļ���ʽ�����б�
				 * @author f
				 * @version 1.0
				 * @created 01-7��-2018 14:06:44
				 */
				typedef enum csf_configure_format_type_enum
				{
					/**
					 * ��ʾδ����������ļ���ʽ����
					 */
					csf_configure_format_type_none = 0x00000000,
					/**
					 * ��ʾxml��ʽ�������ļ���ʽ����
					 */
					csf_configure_format_type_xml = 0x00000001
				} csf_configure_format_type;

				/**
				* ��ʾ����������ļ���ʽ���ͺ����ͱ�ŵĶ�Ӧ��ϵ
				*/
				#define CSF_CONFIGURE_FORMAT_TYPE_NAME(CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP)		\
					CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP(none, "")								\
					CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP(xml, "xml")								\

				csf_configure_parser();
				virtual ~csf_configure_parser();

				/**
				 * ��ʾ��configure_file�е��ļ�����ת��Ϊcsf_element���ݡ�
				 * ���أ�0��ʾ�ɹ���<0��ʾ�����롣
				 * 
				 * @param element    ��ʾ�洢���ս����csf_element����
				 * @param configure_file    ��ʾԴ�ļ�������Ϣ
				 */
				csf_int32 parse(csf_element& element, const csf_configure_file& configure_file);
				/**
				 * �������ļ���Ϣ���浽�ļ���
				 * 
				 * @param configure_file    ��ʾ��Ҫ������ļ���Ϣ
				 * @param element    ��ʾ��Ҫ�����������Ϣ
				 */
				csf_int32 save(const csf_configure_file& configure_file, const csf_element& element);
				/**
				 * ��ʾ��ȡ�����ļ����ļ���ʽ
				 * 
				 * @param format    ��ʾ��Ҫ��ȡ�������ļ���ʽ��������
				 */
				inline csf_configure_parser::csf_configure_format_type format(const csf_string& fmt) {

					return  format(fmt.c_str());
				}
				/**
				 * ��ʾ��ȡ�����ļ����ļ���ʽ
				 * 
				 * @param format    ��ʾ��Ҫ��ȡ�������ļ���ʽ��������
				 */
				csf_configure_parser::csf_configure_format_type format(const csf_char* fmt);
				/**
				* ���������ļ���ʽ����ת����ʽ�����ַ���
				*
				* @param fmt    ��ʾ��Ҫ��ȡ�������ļ���ʽ����
				*/
				csf_string format(const csf_configure_parser::csf_configure_format_type fmt);

			protected:
				/**
				* ��ʾ��configure_file�е�XML�ļ�����ת��Ϊcsf_element���ݡ�
				* ���أ�0��ʾ�ɹ���<0��ʾ�����롣
				*
				* @param element    ��ʾ�洢���ս����csf_element����
				* @param configure_file    ��ʾԴ�ļ�������Ϣ
				*/
				csf_int32 parse_xml(csf_element& element, const csf_configure_file& configure_file);
				/**
				* ��ʾ��configure_file�е��ļ�����ת��Ϊcsf_element���ݡ�
				* ���أ�0��ʾ�ɹ���<0��ʾ�����롣
				*
				* @param element    ��ʾ�洢���ս����csf_element����
				* @param markup    ��ʾCMarkup������XML�ļ�����
				*/
				csf_int32 parse(csf_element& element, CMarkup& markup);
			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_PARSER_INCLUDED_)
