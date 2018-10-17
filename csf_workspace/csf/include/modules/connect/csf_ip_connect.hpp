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
			/**
			* ��ʾ���߶�ʱ��
			* @author f
			* @version 1.0
			* @updated 01-10��-2018 15:12:05
			*/
			typedef boost::asio::deadline_timer			csf_deadline_timer;
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
				inline explicit csf_ip_connect(csf_ip_connect_factory& factory)
					: m_read_timer(factory.get_io_service())
					, m_write_timer(factory.get_io_service())
					, m_read_timeout(0)
					, m_write_timeout(0) {

				}
				virtual ~csf_ip_connect();

				/**
				 * ��ʾ����ʱʱ�䣬��λΪ���롣
				 */
				inline csf_uint32 get_read_timeout() {

					return m_read_timeout;
				}
				/**
				 * ��ʾ����ʱʱ�䣬��λΪ���롣
				 *
				 * @param newVal
				 */
				inline csf_void set_read_timeout(csf_uint32 newVal) {

					m_read_timeout = newVal;
				}
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 */
				inline csf_uint32 get_write_timeout() {

					return m_write_timeout;
				}
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 *
				 * @param newVal
				 */
				inline csf_void set_write_timeout(csf_uint32 newVal) {

					m_write_timeout = newVal;
				}
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 *
				 * @param timeout_ms    ��ʾ��ʱ��ֵ����λ������(ms)
				 * @param callback    ��ʾ��ʱ�ص�����
				 */
				inline csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr) {

					m_write_timeout = timeout_ms;

					return 0;
				}
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 *
				 * @param timeout_ms    ��ʾ��ʱ��ֵ����λ������(ms)
				 * @param callback    ��ʾ��ʱ�ص�����
				 */
				inline csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr) {

					m_read_timeout = timeout_ms;

					return 0;
				}
				virtual csf_url& get_remote_url();
				/**
				*
				* @param new_value
				*/
				virtual csf_int32 set_remote_url(csf_url& new_value);
				/**
				* ��ʾԶ�̵�������ַ
				*
				* @param newVal    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_remote_url(csf_string newVal) {

					m_remote_url = newVal;

					return csf_success;
				}
				/**
				* ��ʾ���ص�������ַ
				*/
				virtual csf_url& get_local_url();
				/**
				* ��ʾ���ص�������ַ
				*
				* @param new_value
				*/
				virtual csf_int32 set_local_url(csf_url& new_value);
				/**
				* ��ʾ���ص�������ַ
				*
				* @param newVal    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_local_url(csf_string newVal) {

					m_local_url = newVal;

					return csf_success;
				}
				/**
				 * ��ʾд��ָ����������ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 *
				 * @param buf    ��ʾ���ݵĻ����ַ
				 * @param len    ��ʾ���ݻ���ĳ���
				 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾд��csf_buffer���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 *
				 * @param buffer    ��ʾ��Ҫд���csf_buffer����
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ����csf_csfstring���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 *
				 * @param csfstr    ��ʾcsf_csfstring������
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ����csf_csfstring���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 *
				 * @param chain    ��ʾcsf_chain������
				 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾд��csf_buffer���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 *
				 * @param buffer    ��ʾ��Ҫд���csf_buffer����
				 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾд��ָ����������ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 *
				 * @param buf    ��ʾ���ݵĻ����ַ
				 * @param len    ��ʾ���ݻ���ĳ���
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ����csf_csfstring���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 *
				 * @param csfstr    ��ʾcsf_csfstring������
				 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ����csf_csfstring���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 *
				 * @param chain    ��ʾcsf_chain������
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_nullptr);
				/**
				* ��ʾ����ʱ��ʱ����
				*/
				inline csf_deadline_timer& get_read_timer() {

					return m_read_timer;
				}
				/**
				* ��ʾд��ʱ��ʱ����
				*/
				inline csf_deadline_timer& get_write_timer() {

					return m_write_timer;
				}
			protected:
				/**
				* ��Ҫ�����ǣ���Դ�����쳣�Ĵ���
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param connect_ptr    ��ʾ������������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾ�쳣��Ϣ����
				*/
				inline csf_int32 async_callback(csf_connect *connect
					, const csf_connect_callback& callback
					, const csf_ip_connect_error& error_code) {

					if (csf_nullptr == connect || csf_nullptr == callback) {
						return csf_failure;
					}
					else {
						return callback(connect, error_code);
					}
					return 0;
				}
				/**
				* ��Ҫ�����ǣ���Դ�����쳣�Ĵ���
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param connect_ptr    ��ʾ������������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾ�쳣��Ϣ����
				*/
				inline csf_int32 exception_callback(csf_connect *connect
					, const csf_connect_callback& callback
					, csf_ip_connect_error& error_code) {

					return async_callback(connect, callback, error_code);
				}

				/**
				*
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾboost�Ĵ�����Ϣ
				* @param len    ��ʾ���ݳ�����Ϣ
				*/
				csf_bool csf_ip_connect::async_write_callback(const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 len);
				/**
				*
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾboost�Ĵ�����Ϣ
				* @param len    ��ʾ���ݳ�����Ϣ
				*/
				csf_bool csf_ip_connect::async_read_callback(const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 len);
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
				 * ��ʾ����ʱ��ʱ����
				 */
				csf_deadline_timer m_read_timer;
				/**
				 * ��ʾд��ʱ��ʱ����
				 */
				csf_deadline_timer m_write_timer;
				/**
				 * ��ʾ����ʱʱ�䣬��λΪ���롣
				 */
				csf_uint32 m_read_timeout = 0;
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 */
				csf_uint32 m_write_timeout = 0;

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_H_INCLUDED_)
