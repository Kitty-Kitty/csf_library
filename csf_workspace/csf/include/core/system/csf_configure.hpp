/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 13:21:34
*
*Description: Class(csf_configure)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONFIGURE_INCLUDED_)
#define CSF_CONFIGURE_INCLUDED_

#include "csf_configure_interface.hpp"
#include "csf_configure_parser.hpp"
#include "csf_csftype_template.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * 描述单个配置文件及解析信息
			 * @author fz
			 * @version 1.0
			 * @created 01-7月-2018 13:21:34
			 */
			class csf_configure : public csf::core::system::csf_configure_interface, public csf::core::base::csf_csftype_template<csf_configure>
			{

			public:
				inline explicit csf_configure() {

				}
				/**
				 * 根据configure_file内容创建一个csf_cofigure构造对象
				 * 
				 * @param configure_file    需要创建的configure为configure_file描述的文档内容
				 */
				inline explicit csf_configure(csf_configure_file& configure_file) {
					if (csf_failure == set_configure_file(configure_file)) {
						throw csf_nullptr;
					}
				}
				inline virtual ~csf_configure() {

				}
				/**
				 * 表示配置文件转换后的csf_element对象
				 */
				inline csf_element& get_element() {

					return m_element;
				}
				/**
				 * 指定的配置文件信息
				 */
				inline csf_configure_file& get_configure_file() {

					return m_configure_file;
				}
				/**
				 * 指定的配置文件信息，这里需要对设置的配置文件进行解析处理。 解析成功返回0，返回其他为错误。
				 * 
				 * @param new_value    new_value
				 */
				inline csf_int32 set_configure_file(csf_configure_file& new_value) {

					csf_configure_parser				tmp_config_parse;


					//解析configure_file的文件内容
					if (csf_failure == tmp_config_parse.parse(get_element(), new_value)) {
						return csf_failure;
					}

					m_configure_file = new_value;
					return csf_success;
				}
				/**
				* 表示根据items属性路径查找一个element。
				* 返回：非null表示满足items所有路径的节点；null表示没有查找到满足路径的节点；
				*
				* @param items    items属性路径
				*/
				inline virtual const csf_element& find_element(const csf_list<csf_string>& items) {

					return  get_element().find_element(items);
				}
				/**
				* 表示判断是否为空。
				* 返回：true表示为空；false表示不为空。
				*/
				inline virtual csf_bool is_null() {

					return get_element().is_null();
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
				 * 指定的配置文件信息
				 */
				csf::core::system::csf_configure_file m_configure_file;
				/**
				 * 表示配置文件转换后的csf_element对象
				 */
				csf::core::system::csf_element m_element;

				/**
				 * 表示配置文件转换后的csf_element对象
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_element(csf_element& new_value) {

					m_element = new_value;
				}

			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_INCLUDED_)
