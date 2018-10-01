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
*Date: 14-7��-2018 11:29:48
*
*Description: Class(csf_root_configure) ��ʾϵͳ�ĸ������ļ�����ģ�飬��Ҫ�������ĸ������ļ����ݡ�
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
			 * ��ʾϵͳ�ĸ������ļ�����ģ�飬��Ҫ�������ĸ������ļ����ݡ�
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 14-7��-2018 11:29:48
			 */
			class csf_root_configure
			{

			public:
				/**
				 * ��ʾ�������ļ��������ƶ���
				 * @author f
				 * @version 1.0
				 * @created 14-7��-2018 11:29:48
				 */
				enum csf_root_configure_attribute_string
				{
					/**
					 * ��ʾ�����е�name�ַ���
					 */
					csf_root_configure_attribute_string_name = 0x00,
					/**
					 * ��ʾ�����е�file�ַ���
					 */
					csf_root_configure_attribute_string_file,
					/**
					 * ��ʾ�����е�format�ַ���
					 */
					csf_root_configure_attribute_string_format
				};


				inline explicit csf_root_configure() {

				}

				virtual ~csf_root_configure() {

				}

				/**
				 * ���ݸ������ļ���Ϣ����һ��app
				 * 
				 * @param root_configure_file    ��ʾ��ǰapp�������ļ���Ϣ
				 */
				inline explicit csf_root_configure(csf_configure_file& root_configure_file) {

				}
				/**
				 * ���ݸ������ļ���Ϣ����һ��app
				 * 
				 * @param path    ��ʾ��ǰapp�������ļ����ļ�·��
				 * @param format    ��ʾ�������ļ����ļ���ʽ
				 */
				inline explicit csf_root_configure(csf_string& path, csf_string& format) {

				}
				/**
				 * ���ݸ������ļ���Ϣ����һ��app
				 * 
				 * @param format    ��ʾ�������ļ����ļ���ʽ
				 * @param path    ��ʾ��ǰapp�������ļ����ļ�·��
				 */
				inline explicit csf_root_configure(const csf_char* format, const csf_char* path) {

				}
				/**
				 * ��ʾapp�ĸ������ļ���Ϣ����Ҫ����app�ĸ��������ļ���Ϣ��
				 */
				inline csf_configure_file& get_root_configure_file() {

					return m_root_configure_file;
				}
				/**
				* �ú�����Ҫ���ڳ�ʼ��app�������ļ�����ȡ�����ļ��б����������Ϣ��
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				* @param root_configure_file    ��ʾ��ǰapp�������ļ���Ϣ
				*/
				csf_bool init_configure_manager(csf::core::system::csf_configure_manager& configure_manager, csf_configure_file& root_configure_file);

			protected:
				/**
				 * ��ʾapp�ĸ������ļ���Ϣ����Ҫ����app�ĸ��������ļ���Ϣ��
				 * 
				 * @param new_value
				 */
				inline csf_void set_root_configure_file(csf_configure_file& new_value) {

					m_root_configure_file = new_value;
				}
				/**
				 * ��ʾ�������ļ��ļ��б�ڵ��·����Ϣ��
				 */
				inline const csf_list<csf_string>& get_configure_files_items() {

					return m_configure_files_items;
				}

			private:
				/**
				 * ��ʾapp�ĸ������ļ���Ϣ����Ҫ����app�ĸ��������ļ���Ϣ��
				 */
				csf_configure_file m_root_configure_file;
				/**
				 * ��ʾ�������ļ��ļ��б�ڵ��·����Ϣ��
				 */
				static const csf_list<csf_string> m_configure_files_items;
				/**
				 * ��ʾ�����ļ��������ַ�������.
				 */
				static const csf_string m_configure_file_attribute[];
			};

		}

	}

}
#endif // !defined(CSF_ROOT_CONFIGURE_INCLUDED_)
