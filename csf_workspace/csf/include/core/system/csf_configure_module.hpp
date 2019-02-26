/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_configure_module.hpp
*
*Version: 1.0
*
*Date: 04-10��-2018 19:44:08
*
*Description: Class(csf_configure_module) ��Ҫ��ʾģ������ü������ඨ��
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONFIGURE_MODULE_H_INCLUDED_)
#define CSF_CONFIGURE_MODULE_H_INCLUDED_

#include "csf_module_manager.hpp"
#include "csf_element.hpp"
#include "csf_device_base.hpp"
#include "csf_app.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * ��Ҫ��ʾģ������ü������ඨ��
			 * @author f
			 * @version 1.0
			 * @created 04-10��-2018 19:44:08
			 */
			class csf_configure_module
			{

			public:
				csf_configure_module();
				virtual ~csf_configure_module();

				/**
				* ��Ҫ�����ǣ�ͨ��������Ϣ����һ������ģ�����
				* ���أ���null��ʾģ������ַ��null��ʾʧ�ܣ�
				*
				* @param app    ��ʾ���ָ��app����ģ�����
				* @param module_manager    ��ʾģ�������������Ϣ
				* @param element    ��ʾģ���������Ϣ��
				*
				* ģ��������Ϣ�ṹ���£�
				* <!--***�ò�������ģ��������Ϣ���Ǳ������õ���������***-->
				* <module>
				*        <!--***��ʾģ���Ӧ��ģ��������Ϣ***-->
				*        <name>csf_connection</name>
				*        <!--***��ʾ���豸ģ���Ψһ��ʶ�ַ��������ַ�������ӦС�ڵ���64�ֽ�***-->
				*        <mid>02000000-0000001</mid>
				*        <!--��ʾ��ģ���������Ϣ����Ҫ��ģ���configure�ӿڴ�����ģ���������������ģ��Ӧ��ģ��ȷ��-->
				*        <configure>
				*                <!--��ʾ�߳�����-->
				*                <thread_number>4</thread_number>
				*        </configure>
				* </module>
				*
				*
				*/
				static csf::core::module::csf_device_base* create_module(
					csf_app* app
					, csf::core::module::csf_module_manager& module_manager
					, const csf::core::system::csf_element& element);
				/**
				* ��Ҫ�����ǣ�
				*    ����boost.
				* log��־ģ��Ĵ������⣬��֧��dll��soģ�������������Ҫ������־���ܡ������е�device��device_io����ʱ������Ҫִ�иô�����������������־
				* ģ�飬����Ҫ�ú������ܡ�
				*
				* ���أ�
				*    true:��ʾ���óɹ���
				*    false:��ʾʧ�ܣ�
				*
				* @param configure_manager    ��ʾ�����ļ�����
				*/
				inline static csf_bool init_logger(const csf_configure_manager * configure_manager) {

					csf_void				*tmp_app = csf_nullptr;

					
					if (!configure_manager) {
						return csf_false;
					}

					//��ȡapp����
					tmp_app = ((csf_configure_manager *)configure_manager)->get_app_object();
					if (!tmp_app) {
						return csf_false;
					}

					//�ж��Ƿ�Ϊapp��������
					if (!csf_device_base::is_app(((csf_device_base*)tmp_app)->get_type())) {
						return csf_false;
					}

					//��ʼ����־����
					return init_logger((csf_app*)tmp_app);
				}
				/**
				* ��Ҫ�����ǣ�
				*    ����boost.
				* log��־ģ��Ĵ������⣬��֧��dll��soģ�������������Ҫ������־���ܡ������е�device��device_io����ʱ������Ҫִ�иô�����������������־
				* ģ�飬����Ҫ�ú������ܡ�
				*
				* ���أ�
				*    true:��ʾ���óɹ���
				*    false:��ʾʧ�ܣ�
				*
				* @param app    ��ʾ��Ӧ��app�����ַ��Ϣ
				*/
				inline static csf_bool init_logger(csf_app* app) {

					if (!app) {
						return csf_false;
					}
					
					return init_logger(app->get_logger());
				}

				/**
				* ��Ҫ�����ǣ�
				*    ����boost.
				* log��־ģ��Ĵ������⣬��֧��dll��soģ�������������Ҫ������־���ܡ������е�device��device_io����ʱ������Ҫִ�иô�����������������־
				* ģ�飬����Ҫ�ú������ܡ�
				*
				* ���أ�
				*    true:��ʾ���óɹ���
				*    false:��ʾʧ�ܣ�
				*
				* @param logger    ��ʾ��Ҫ������־����
				*/
				inline static csf_bool init_logger(csf_logger& logger) {

#if defined(WIN32)
					boost::log::core::get()->add_sink(logger.get_text_sink_ptr());
#endif
					boost::log::core::get()->add_sink(logger.get_file_sink_ptr());

					csf_logger::set_level(logger.get_level());

					return csf_true;
				}
			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_MODULE_H_INCLUDED_)
