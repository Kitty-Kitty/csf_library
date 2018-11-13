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
			 * 表示类型转换类内容，主要负责几个重要数据类型的解析和转换
			 * @author Administrator
			 * @version 1.0
			 * @created 01-7月-2018 14:06:44
			 */
			class csf_configure_parser
			{

			public:
				/**
				 * 表示配置文件格式类型列表
				 * @author f
				 * @version 1.0
				 * @created 01-7月-2018 14:06:44
				 */
				typedef enum csf_configure_format_type_enum
				{
					/**
					 * 表示未定义的配置文件格式类型
					 */
					csf_configure_format_type_none = 0x00000000,
					/**
					 * 表示xml格式的配置文件格式类型
					 */
					csf_configure_format_type_xml = 0x00000001
				} csf_configure_format_type;

				/**
				* 表示定义的配置文件格式类型和类型编号的对应关系
				*/
				#define CSF_CONFIGURE_FORMAT_TYPE_NAME(CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP)		\
					CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP(none, "")								\
					CSF_CONFIGURE_FORMAT_TYPE_NAME_MAP(xml, "xml")								\

				csf_configure_parser();
				virtual ~csf_configure_parser();

				/**
				 * 表示将configure_file中的文件内容转换为csf_element内容。
				 * 返回：0表示成功；<0表示错误码。
				 * 
				 * @param element    表示存储最终结果的csf_element对象
				 * @param configure_file    表示源文件描述信息
				 */
				csf_int32 parse(csf_element& element, const csf_configure_file& configure_file);
				/**
				 * 将配置文件信息保存到文件中
				 * 
				 * @param configure_file    表示需要保存的文件信息
				 * @param element    表示需要保存的配置信息
				 */
				csf_int32 save(const csf_configure_file& configure_file, const csf_element& element);
				/**
				 * 表示获取配置文件的文件格式
				 * 
				 * @param format    表示需要获取的配置文件格式类型数据
				 */
				inline csf_configure_parser::csf_configure_format_type format(const csf_string& fmt) {

					return  format(fmt.c_str());
				}
				/**
				 * 表示获取配置文件的文件格式
				 * 
				 * @param format    表示需要获取的配置文件格式类型数据
				 */
				csf_configure_parser::csf_configure_format_type format(const csf_char* fmt);
				/**
				* 根据配置文件格式类型转换格式类型字符串
				*
				* @param fmt    表示需要获取的配置文件格式类型
				*/
				csf_string format(const csf_configure_parser::csf_configure_format_type fmt);

			protected:
				/**
				* 表示将configure_file中的XML文件内容转换为csf_element内容。
				* 返回：0表示成功；<0表示错误码。
				*
				* @param element    表示存储最终结果的csf_element对象
				* @param configure_file    表示源文件描述信息
				*/
				csf_int32 parse_xml(csf_element& element, const csf_configure_file& configure_file);
				/**
				* 表示将configure_file中的文件内容转换为csf_element内容。
				* 返回：0表示成功；<0表示错误码。
				*
				* @param element    表示存储最终结果的csf_element对象
				* @param markup    表示CMarkup解析的XML文件对象
				*/
				csf_int32 parse(csf_element& element, CMarkup& markup);
			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_PARSER_INCLUDED_)
