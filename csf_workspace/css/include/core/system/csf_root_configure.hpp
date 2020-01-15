/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: fangzhenmu@aliyun.com
*
*Author: fz
*
*Version: 1.0
*
*Date: 14-7月-2018 11:29:48
*
*Description: Class(csf_root_configure) 表示系统的根配置文件处理模块，主要处理程序的根配置文件内容。
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ROOT_CONFIGURE_INCLUDED_)
#define CSF_ROOT_CONFIGURE_INCLUDED_

#include "csf_logger.hpp"
#include "csf_configure_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * 表示系统的根配置文件处理模块，主要处理程序的根配置文件内容。
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 14-7月-2018 11:29:48
			 */
			class csf_root_configure
			{

			public:
				/**
				 * 表示根配置文件属性名称定义
				 * @author f
				 * @version 1.0
				 * @created 14-7月-2018 11:29:48
				 */
				enum csf_root_configure_attribute_string
				{
					/**
					 * 表示属性中的name字符串
					 */
					csf_root_configure_attribute_string_name = 0x00,
					/**
					 * 表示属性中的file字符串
					 */
					csf_root_configure_attribute_string_file,
					/**
					 * 表示属性中的format字符串
					 */
					csf_root_configure_attribute_string_format
				};


				inline explicit csf_root_configure() {

				}

				virtual ~csf_root_configure() {

				}

				/**
				 * 根据根配置文件信息创建一个app
				 * 
				 * @param root_configure_file    表示当前app根配置文件信息
				 */
				inline explicit csf_root_configure(csf_configure_file& root_configure_file) {

				}
				/**
				 * 根据根配置文件信息创建一个app
				 * 
				 * @param path    表示当前app根配置文件的文件路径
				 * @param format    表示根配置文件的文件格式
				 */
				inline explicit csf_root_configure(csf_string& path, csf_string& format) {

				}
				/**
				 * 根据根配置文件信息创建一个app
				 * 
				 * @param format    表示根配置文件的文件格式
				 * @param path    表示当前app根配置文件的文件路径
				 */
				inline explicit csf_root_configure(const csf_char* format, const csf_char* path) {

				}
				/**
				 * 表示app的根配置文件信息，主要保存app的各种配置文件信息。
				 */
				inline csf_configure_file& get_root_configure_file() {

					return m_root_configure_file;
				}
				/**
				* 该函数主要用于初始化app的配置文件，获取配置文件中保存的属性信息。
				* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
				*
				* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
				* @param root_configure_file    表示当前app根配置文件信息
				*/
				csf_bool init_configure_manager(csf::core::system::csf_configure_manager& configure_manager, csf_configure_file& root_configure_file);

			protected:
				/**
				 * 表示app的根配置文件信息，主要保存app的各种配置文件信息。
				 * 
				 * @param newVal
				 */
				inline csf_void set_root_configure_file(csf_configure_file& newVal) {

					m_root_configure_file = newVal;
				}
				/**
				 * 表示主配置文件文件列表节点的路径信息。
				 */
				inline const csf_list<csf_string>& get_configure_files_items() {

					return m_configure_files_items;
				}

			private:
				/**
				 * 表示app的根配置文件信息，主要保存app的各种配置文件信息。
				 */
				csf_configure_file m_root_configure_file;
				/**
				 * 表示主配置文件文件列表节点的路径信息。
				 */
				static const csf_list<csf_string> m_configure_files_items;
				/**
				 * 表示配置文件的属性字符串定义.
				 */
				static const csf_string m_configure_file_attribute[];
			};

		}

	}

}
#endif // !defined(CSF_ROOT_CONFIGURE_INCLUDED_)
