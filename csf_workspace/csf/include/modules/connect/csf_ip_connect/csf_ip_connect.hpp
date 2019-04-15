/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connect.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 15:10:39
*
*Description: Class(csf_ip_connect) ��ʾIP���͵�������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_H_INCLUDED_)
#define CSF_IP_CONNNECT_H_INCLUDED_

#include "csf_ip_url.hpp"
#include "csf_connect.hpp"
#include "csf_ip_connect_factory.hpp"
#include "csf_ip_connect_error.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/************************************************************************/
			/* ��ʾip_connect��������Ϣ�Ļ����С����ֵĬ��Ϊ��128						*/
			/************************************************************************/
			#define csf_ip_connect_format_buffer_size							128
			/**
			 * ��ʾIP���͵�������
			 * @author f
			 * @version 1.0
			 * @updated 01-10��-2018 15:12:05
			 */
			class csf_ip_connect : public csf::core::module::connect::csf_connect
			{

			public:
				/**
				* ����csf_ip_connect_factory����һ�������׽���
				*
				* @param factory    ��ʾ���������׽��ֵĹ��������
				*/
				inline explicit csf_ip_connect(csf_ip_connect_factory& factory, csf_connect_type type)
					: csf_connect(factory, type)
					, m_format(csf_ip_connect_format_buffer_size) {

				}
				virtual ~csf_ip_connect();
				/**
				* ��ʾԶ�̵�������ַ
				*
				* @param new_value    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_remote_url(csf_string new_value) {

					return m_remote_url.parse(new_value);
					//m_remote_url = new_value;
					//return csf_succeed;
				}
				/**
				* ��ʾԶ�������ַ
				*
				* @param new_value    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_remote_url(csf::core::module::connect::csf_url& new_value) {

					if (csf_false == csf_ip_url::is_valid_type(new_value)) {
						return csf_failure;
					}
					m_remote_url = (csf::modules::connect::csf_ip_url&)new_value;

					return csf_succeed;
				}
				/**
				* ��ʾ���ص�������ַ
				*
				* @param new_value    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_local_url(csf_string new_value) {

					return m_local_url.parse(new_value);
					//m_local_url = new_value;
					//return csf_succeed;
				}
				/**
				* ��ʾ���������ַ
				*
				* @param new_value    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_local_url(csf::core::module::connect::csf_url& new_value) {

					if (csf_false == csf_ip_url::is_valid_type(new_value)) {
						return csf_failure;
					}
					m_local_url = (csf::modules::connect::csf_ip_url&)new_value;

					return csf_succeed;
				}
				/**
				* ��ʾԶ�������ַ
				*/
				inline virtual const csf_url& get_remote_url() const {

					return m_remote_url;
				}
				/**
				* ��ʾ���������ַ
				*/
				inline virtual const csf_url& get_local_url() const {

					return m_local_url;
				}
				/**
				* ��Ҫ�����ǣ�
				*    �����첽���ӻص�����
				* ���أ�
				*    0   ����ʾ�ɹ���
				*    ��0 ����ʾʧ��
				*
				* @param connect    ��ʾ������������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾboost�Ĵ�����Ϣ
				*/
				inline csf_int32 async_connect_callback(csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, const boost::system::error_code& error_code) {

					//����һ�±��صĵ�ַ��Ϣ
					connect_ptr->get_local_url();

					//������������ô�����Ϣ
					//��ȷ��񶼴�ӡ��Ϣ
					if (error_code) {
						set_error(csf_connect_error(error_code.value()
							, boost::system::system_error(error_code).what()));

						csf_log_ex(error, csf_log_code_error
							, "connect[url:%s] failed! %s."
							, connect_ptr->get_remote_url().get_url().c_str()
							, get_error().to_string().c_str());
					}
					else {
						csf_log_ex(notice, csf_log_code_notice
							, "connect %s succeed!"
							, connect_ptr->to_string().c_str());
					}

					return async_callback(connect_ptr
						, callback
						, csf_ip_connect_error(error_code));
				}
				/**
				* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ��Ҫ���͵����ݻ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				virtual csf_int32 read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
			protected:
				/**
				* ��Ҫ�����ǣ���Դ�����쳣�Ĵ���
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param connect_ptr    ��ʾ������������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾ�쳣��Ϣ����
				*/
				inline csf_int32 async_callback(csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, csf_ip_connect_error error_code) {

					if (!connect_ptr
						|| csf_nullptr == callback) {

						if (error_code.get_code() > 0) {
							csf_log_ex(warning
								, csf_log_code_warning
								, "%s %s"
								, connect_ptr->to_string().c_str()
								, error_code.to_string().c_str());
						}
						return csf_failure;
					}
					else {
						return callback(connect_ptr, error_code);
					}

					return csf_succeed;
				}
				/**
				* ��Ҫ�����ǣ���Դ�����쳣�Ĵ���
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param connect_ptr    ��ʾ������������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾ�쳣��Ϣ����
				*/
				inline csf_int32 exception_callback(csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, csf_ip_connect_error error_code) {

					return async_callback(connect_ptr, callback, error_code);
				}
				/**
				* ��Ҫ�����ǣ������첽д����ص�����
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param buffer		 ��ʾ���ݵĻ���
				* @param connect_ptr ��ʾ��ǰ���������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code  ��ʾboost�Ĵ�����Ϣ
				* @param length		��ʾ��ǰʵ��д�Ļ��泤��
				*/
				csf_bool async_write_callback(csf_connect_buffer<csf_buffer>& buffer
					, csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 length);
				/**
				* ��Ҫ�����ǣ������첽������ص�����
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param buffer		 ��ʾ���ݵĻ���
				* @param connect_ptr ��ʾ��ǰ���������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code  ��ʾboost�Ĵ�����Ϣ
				* @param length   ��ʾ��ǰʵ��д�Ļ��泤��
				*/
				csf_bool async_read_callback(csf_connect_buffer<csf_buffer>& buffer
					, csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 length);
				/**
				* ��ʾд��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				/**
				* ��ʾд��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 async_write(csf_connect_buffer<csf_buffer>& buffer
					, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* ��Ҫ�����ǣ��첽��ȡ���ݣ�������ָ�����档
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 async_read(csf_connect_buffer<csf_buffer>& buffer
					, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* ��ʾд��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 sync_write(csf_connect_buffer<csf_buffer>& buffer
					, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* ��Ҫ�����ǣ�ͬ����ȡ���ݣ�������ָ�����档
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 sync_read(csf_connect_buffer<csf_buffer>& buffer
					, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* ��ʾ������Ϣ�ĸ�ʽ���ַ���
				*/
				inline csf::core::base::csf_csfstring& get_format() {

					return m_format;
				}
				/**
				* ��ʾ������Ϣ�ĸ�ʽ���ַ���
				*
				* @param new_value
				*/
				inline void set_format(const csf_char* fmt, ...) {

					va_list					tmp_marker;


					if (!fmt || csf_strlen(fmt) <= 0) {
						return ;
					}

					va_start(tmp_marker, fmt);

					get_format().format(fmt, tmp_marker);

					va_end(tmp_marker);

					return;
				}
			private:
				/**
				* ��ʾԶ�������ַ
				*/
				csf::modules::connect::csf_ip_url m_remote_url;
				/**
				* ��ʾ���������ַ
				*/
				csf::modules::connect::csf_ip_url m_local_url;
				/**
				* ��ʾ������Ϣ�ĸ�ʽ���ַ���
				*/
				csf::core::base::csf_csfstring m_format;

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_H_INCLUDED_)
