/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_tcp_connect.hpp
*
*Version: 1.0
*
*Date: 02-10��-2018 14:18:00
*
*Description: Class(csf_tcp_connect) ��ʾtcp����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_TCP_CONNECT_H_INCLUDED_)
#define CSF_TCP_CONNECT_H_INCLUDED_

#include "csf_ip_url.hpp"
#include "csf_stream_connect.hpp"
#include "csf_ip_connect_factory.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{

			/**
			 * ��ʾtcp����
			 * @author f
			 * @version 1.0
			 * @created 02-10��-2018 14:18:00
			 */
			class csf_tcp_connect : public csf::modules::connect::csf_stream_connect
			{
			public:
				/**
				* ��ʾ����һ��tcp������������ָ��
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_tcp_connect>				csf_tcp_connect_ptr;

			public:
				/**
				* ����csf_ip_connect_factory����һ�������׽���
				*
				* @param factory    ��ʾ���������׽��ֵĹ��������
				*/
				inline explicit csf_tcp_connect(csf_ip_connect_factory& factory)
					: csf_stream_connect(factory, csf_connect::csf_connect_type_tcp)
					, m_socket(factory.get_io_service()) {

				}
				/**
				* ����csf_ip_connect_factory����һ�������׽���
				*
				* @param factory    ��ʾ���������׽��ֵĹ��������
				*/
				inline explicit csf_tcp_connect(csf_ip_connect_factory* factory)
					: csf_stream_connect(*factory, csf_connect::csf_connect_type_tcp)
					, m_socket(factory->get_io_service()) {

				}
				/**
				* ����csf_tco_connect����һ�������׽���
				*
				* @param connect    ��ʾ�������е������׽��ֶ���
				*/
				inline explicit csf_tcp_connect(csf_tcp_connect* connect)
					: csf_stream_connect(*((csf_ip_connect_factory*)(connect->get_factory())), csf_connect::csf_connect_type_tcp)
					, m_socket(((csf_ip_connect_factory*)(connect->get_factory()))->get_io_service()) {
				}
				virtual ~csf_tcp_connect();
				/**
				* ģ���ʼ��
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
				/**
				* ��ʾ��������Ϣ.
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				*
				* @param url    ��ʾ���ӵ�ַ
				*/
				virtual csf_int32 open(const csf_url& url);
				/**
				* ��ʾ�ر�����.
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				*/
				virtual csf_int32 close();
				/**
				* ģ������
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
				/**
				* ��ʾ�������ӵ�������Ŀ��Ϣ��
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				*/
				virtual csf_int32 set_option();
				/**
				* ģ��ֹͣ
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
				/**
				* ��Ҫ�����ǣ���һ��������ַ��
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				*
				* @param url    ��ʾ��Ҫ�����ĵ�ַ
				* @param callback    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				*/
				virtual csf_int32 listen(const csf_url& url, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���Ҫ����һ����ַ��
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				*
				* @param url    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 connect(const csf_url& url, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�д��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buf    ��ʾ���ݵĻ����ַ
				* @param len    ��ʾ���ݻ���ĳ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ��Ҫд���csf_buffer����
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 write(csf_buffer& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param csfstr    ��ʾcsf_csfstring������
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 write(csf_csfstring& csfstr, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param chain    ��ʾcsf_chain������
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 write(csf_chain& chain, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�д��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ��Ҫ���͵����ݻ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ��Ҫ���͵����ݻ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ��Ҫ���͵����ݻ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ��Ҫ���͵����ݻ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
				*
				* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				//virtual csf_int32 read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
				* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				//virtual csf_int32 read(csf_buffer& buffer, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
				* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				//virtual csf_int32 read(csf_csfstring& csfstr, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
				* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				//virtual csf_int32 read(csf_chain& chain, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param buffer    ��ʾ��ȡ���ݴ�ŵĻ������
				*
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				//virtual csf_int32 read(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				//virtual csf_int32 read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				//virtual csf_int32 read(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				*
				* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
				* @param callback    ��ʾ��ȡ�Ļص�����
				*/
				//virtual csf_int32 read(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ���������Ϣ��ʽ�����ַ������
				* ���أ�������Ϣ�ַ���
				*/
				inline virtual csf_string to_string() {

					if (get_format().empty()) {
						set_format(
							"%s url[ local:%s -- remote:%s ]"
							, csf::core::module::connect::csf_connect::to_string().c_str()
							, get_local_url().get_url().c_str()
							, get_remote_url().get_url().c_str());
					}

					return get_format().to_string();
				}
				/**
				* ��Ҫ�����ǣ���ո�ʽ���ַ�������ռ�
				* ���أ���
				*/
				inline virtual void flush_string() {

					get_format().memzero();
				}
			protected:
				/**
				* ��ʾд��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buf    ��ʾ���ݵĻ����ַ
				* @param len    ��ʾ���ݻ���ĳ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 sync_write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��ʾд��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buf    ��ʾ���ݵĻ����ַ
				* @param len    ��ʾ���ݻ���ĳ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 async_write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�ͬ����ȡ���ݣ�������ָ�����档
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
				*
				* @param buf    ��ʾ���ݵĻ����ַ
				* @param len    ��ʾ���ݻ���ĳ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 sync_read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ��첽��ȡ���ݣ�������ָ�����档
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
				*
				* @param buf    ��ʾ���ݵĻ����ַ
				* @param len    ��ʾ���ݻ���ĳ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				//virtual csf_int32 async_read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��ʾд��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 sync_write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��ʾд��ָ����������ݡ�
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 async_write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ�ͬ����ȡ���ݣ�������ָ�����档
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 sync_read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��Ҫ�����ǣ��첽��ȡ���ݣ�������ָ�����档
				* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
				*
				* @param buffer    ��ʾ���ݵĻ����ַ
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				virtual csf_int32 async_read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* ��ʾԶ�̵�������ַ
				*/
				virtual const csf_url& get_remote_url() const;
				/**
				* ��ʾ���ص�������ַ
				*/
				virtual const csf_url& get_local_url() const;
				/**
				* ��ʾ���������׽���
				*/
				inline boost::asio::ip::tcp::socket& get_socket() const {

					return const_cast<boost::asio::ip::tcp::socket&>(m_socket);
				}
				/**
				* ��ʾ��ǰ��tcp����ȷ�϶���
				*/
				inline boost::asio::ip::tcp::acceptor* get_acceptor() const {

					return m_acceptor;
				}
				/**
				* ��ʾ��ǰ��tcp����ȷ�϶���
				*
				* @param newVal
				*/
				inline csf_void set_acceptor(boost::asio::ip::tcp::acceptor* newVal) {

					m_acceptor = newVal;
				}
				/**
				* ��Ҫ�����ǣ��첽tcp������accept��������
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				*
				* @param callback    ��ʾ��Ҫ���صĻص�����
				*/
				csf::core::base::csf_int32 async_accept(const csf_connect_callback callback);
				/**
				* ��Ҫ�����ǣ��첽tcp������accept�ص���������
				* ���أ���
				*
				* @param connect_ptr    ��ʾ��ǰ����ͨ�����Ӷ���
				* @param callback    ��ʾ��Ҫ���صĻص�����
				* @param ec    ��ʾ��ǰ�Ĵ�����Ϣ
				*/
				csf_void accept_handle(csf_tcp_connect_ptr connect_ptr
					, const csf_connect_callback callback
					, boost::system::error_code ec);
				/**
				* ��Ҫ���ܣ�
				*    ��ʾsocket���Ӷ���
				* ���أ�
				*    0����ʾ�ɹ���
				*    ��0����ʾʧ�ܣ�
				*/
				virtual csf_int32 close_socket();
			private:
				/**
				* ��Ҫ�����ǣ������첽д����ص�����
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param buf		 ��ʾ���ݵĻ����ַ
				* @param src_len	 ��ʾ��Ҫ�������Դ���ݻ���ĳ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code  ��ʾboost�Ĵ�����Ϣ
				* @param write_len   ��ʾ��ǰʵ��д�Ļ��泤��
				*/
				// 				csf_bool async_write_callback(const csf_uchar* buf
				// 					, const csf_uint32 src_len
				// 					, const csf_connect_callback& callback
				// 					, const boost::system::error_code& error_code
				// 					, csf_uint32 write_len);
				/**
				* ��Ҫ�����ǣ������첽������ص�����
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param buf		 ��ʾ���ݵĻ����ַ
				* @param buf_len	 ��ʾ��Ҫ�������Դ���ݻ���ĳ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code  ��ʾboost�Ĵ�����Ϣ
				* @param read_len   ��ʾ��ǰʵ��д�Ļ��泤��
				*/
				// 				csf_bool async_read_callback(csf_uchar* buf
				// 					, const csf_uint32 buf_len
				// 					, const csf_connect_callback& callback
				// 					, const boost::system::error_code& error_code
				// 					, csf_uint32 read_len);
				
			private:
				/**
				* ��ʾ���������׽���
				*/
				boost::asio::ip::tcp::socket m_socket;
				/**
				* ��ʾ��ǰ��tcp����ȷ�϶���
				*/
				boost::asio::ip::tcp::acceptor* m_acceptor;
				
			};
		}

	}

}
#endif // !defined(CSF_TCP_CONNECT_H_INCLUDED_)
