/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure_file.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 30-6月-2018 11:58:29
*
*Description: Class(csf_configure_file) 表示配置文件，一个文件一个configure_file对象
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONFIGURE_FILE_INCLUDED_)
#define CSF_CONFIGURE_FILE_INCLUDED_

#include "csf_typedef.h"
#include "csf_csftype_template.hpp"
#include "csf_configure_interface.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * 表示配置文件，一个文件一个configure_file对象
			 * @author fz
			 * @version 1.0
			 * @created 30-6月-2018 11:58:29
			 */
			class csf_configure_file : public csf::core::system::csf_configure_interface, public csf::core::base::csf_csftype_template<csf_configure_file>
			{

			public:
				inline explicit csf_configure_file()
					: m_file_path("")
					, m_format("")
					, m_name("") {

				}
				virtual ~csf_configure_file() {

				}

				/**
				 * 包含三个属性的构造函数
				 * 
				 * @param name    表示该配置项的名称
				 * @param file_path    表示配置文件的文件路径
				 * @param format    表示配置文件的文件格式，用于指导文件的解析
				 */
				inline explicit csf_configure_file(const csf_char* name, const csf_char* file_path, const csf_char* format)
					: m_name(name)
					, m_file_path(file_path)
					, m_format(format) {

				}
				/**
				 * 包含三个属性的构造函数
				 * 
				 * @param name    表示该配置项的名称
				 * @param file_path    表示配置文件的文件路径
				 * @param format    表示配置文件的文件格式，用于指导文件的解析
				 */
				inline explicit csf_configure_file(const csf_string& name, const csf_string& file_path, const csf_string& format)
					: csf_configure_file(name.c_str(), file_path.c_str(), format.c_str()){

				}
				/**
				 * 表示配置文件的目录地址
				 */
				inline csf_string& get_file_path() {

					return m_file_path;
				}
				/**
				 * 表示配置文件的目录地址
				 * 
				 * @param new_value
				 */
				inline csf_void set_file_path(csf_string& new_value) {

					m_file_path = new_value;
				}
				/**
				 * 表示配置文件的格式
				 */
				inline csf_string& get_format() {

					return m_format;
				}
				/**
				 * 表示配置文件的格式
				 * 
				 * @param new_value
				 */
				inline csf_void set_format(csf_string& new_value) {

					m_format = new_value;
				}
				/**
				 * 表示配置文件的命名，用于丰富配置文件的处理
				 */
				inline csf_string& get_name() {

					return m_name;
				}
				/**
				 * 表示配置文件的命名，用于丰富配置文件的处理
				 * 
				 * @param new_value
				 */
				inline csf_void set_name(csf_string& new_value) {

					m_name = new_value;
				}
				/**
				 * 表示配置文件的命名，用于丰富配置文件的处理
				 * 
				 * @param new_value
				 */
				inline csf_void set_name(csf_char* new_value) {

					m_name = new_value;
				}
				/**
				 * 表示配置文件的格式
				 * 
				 * @param new_value
				 */
				inline csf_void set_format(csf_char* new_value) {

					m_format = new_value;
				}
				/**
				 * 表示配置文件的目录地址
				 * 
				 * @param new_value
				 */
				inline csf_void set_file_path(csf_char* new_value) {

					m_file_path = new_value;
				}
				/**
				* 表示判断是否为空。
				* 返回：true表示为空；false表示不为空。
				*/
				inline virtual csf_bool is_null() {

					if (get_name().empty() 
						&& get_file_path().empty()
						&& get_format().empty()) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				* 表示判断是否不为空。
				* 返回：true表示不为空；false表示为空。
				*/
				inline virtual csf_bool not_null() {

					return !is_null();
				}
			private:
				/**
				 * 表示配置文件的目录地址
				 */
				csf_string m_file_path = "";
				/**
				 * 表示配置文件的格式
				 */
				csf_string m_format = "";
				/**
				 * 表示配置文件的命名，用于丰富配置文件的处理
				 */
				csf_string m_name = "";

			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_FILE_INCLUDED_)
