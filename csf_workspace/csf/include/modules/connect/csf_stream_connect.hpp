/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_stream_connect.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:52
*
*Description: Class(csf_stream_connect) ��ʾͨ�ſ⣬��������Ϣ����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_STREAM_CONNECT_H_INCLUDED_)
#define CSF_STREAM_CONNECT_H_INCLUDED_

#include "csf_url.hpp"
#include "csf_ip_connnect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾͨ�ſ⣬��������Ϣ����
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-10��-2018 12:54:53
			 */
			class csf_stream_connect : public csf::modules::connect::csf_ip_connnect
			{

			public:
				csf_stream_connect();
				virtual ~csf_stream_connect();

				/**
				 * ��ʾͨ��factory����һ��connect
				 * 
				 * @param factory    ��ʾ��Ҫ����connect�Ĺ�����
				 */
				inline explicit csf_stream_connect(csf_connect_factory* factory) {

				}
				/**
				 * ģ���ʼ��
				 * 
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
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
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
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
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				 */
				virtual csf_int32 get_option();
				/**
				 * ��ʾ���ӵ�����
				 */
				inline csf_connect::csf_connect_type get_type() {

					return m_type;
				}
				/**
				 * ��ʾ���ö���ʱʱ��.
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				 * 
				 * @param timeout_ms
				 * @param callback    ��ʾ��ʱ�ص�������
				 */
				virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ���ӵ�����
				 * 
				 * @param new_value
				 */
				inline csf_int32 set_type(csf_connect::csf_connect_type new_value) {

					m_type = new_value;
				}
				csf_url& get_remote_url();
				/**
				 * ��ʾ����д��ʱʱ�䡣
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				 * 
				 * @param timeout_ms
				 * @param callback    ��ʾ��ʱ�ص�������
				 */
				virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 
				 * @param new_value
				 */
				csf_int32 set_remote_url(csf_url& new_value);
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
				 * ��ʾ���ص�������ַ
				 */
				csf_url& get_local_url();
				/**
				 * ��ʾд��csf_buffer���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 * 
				 * @param buffer    ��ʾ��Ҫд���csf_buffer����
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ���ص�������ַ
				 * 
				 * @param new_value
				 */
				csf_int32 set_local_url(csf_url& new_value);
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
				 * ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
				 */
				inline csf_bool get_sync() {

					return m_sync;
				}
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
				 * ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
				 * 
				 * @param new_value
				 */
				inline csf_void set_sync(csf_bool new_value) {

					m_sync = new_value;
				}
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
				 * ��ʾ�����״̬��Ϣ
				 */
				inline csf_uint32 get_status() {

					return m_status;
				}
				/**
				 * ��ʾ����csf_csfstring���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 * 
				 * @param chain    ��ʾcsf_chain������
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
				 * 
				 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ�����״̬��Ϣ
				 * 
				 * @param new_value
				 */
				inline csf_void set_status(csf_uint32 new_value) {

					m_status = new_value;
				}
				/**
				 * ��ʾ����connect�Ĺ������ַ
				 */
				csf_connect_factory* get_factory();
				/**
				 * ��ʾ��ȡ���ݲ�����ָ�����������С�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
				 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
				 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ����connect�Ĺ������ַ
				 * 
				 * @param new_value
				 */
				csf_void set_factory(csf_connect_factory* new_value);
				csf_uint32 get_read_timeout();
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_buffer& buffer, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
				 * 
				 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 
				 * @param new_value
				 */
				csf_void set_read_timeout(csf_uint32 new_value);
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 */
				csf_uint32 get_write_timeout();
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
				 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 * 
				 * @param new_value
				 */
				csf_void set_write_timeout(csf_uint32 new_value);
				/**
				 * ��ʾ��ȡ���ݲ�����ָ�����������С�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_null);

			private:
				/**
				 * ��ʾ���ӵ�����
				 */
				csf_connect::csf_connect_type m_type = csf_connect_type_none;
				/**
				 * ��ʾԶ�˵�������ַ
				 */
				csf::core::module::connect::csf_url m_remote_url;
				/**
				 * ��ʾ���ص�������ַ
				 */
				csf::core::module::connect::csf_url m_local_url;
				/**
				 * ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
				 */
				csf_bool m_sync = csf_false;
				/**
				 * ��ʾ�����״̬��Ϣ
				 */
				csf_uint32 m_status = 0;
				/**
				 * ��ʾ����connect�Ĺ������ַ
				 */
				csf_connect_factory* m_factory = csf_nullptr;
				/**
				 * ��ʾ����ʱʱ�䣬��λΪ���롣
				 */
				csf_uint32 m_read_timeout = 0;
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 */
				csf_uint32 m_write_timeout = 0;
				/**
				 * ��ʾ����ʱ��ʱ����
				 */
				csf_deadline_timer m_read_timer;
				/**
				 * ��ʾд��ʱ��ʱ����
				 */
				csf_deadline_timer m_write_timer;
				/**
				 * ��ʾ�����ļ�������
				 */
				csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;

			};

		}

	}

}
#endif // !defined(CSF_STREAM_CONNECT_H_INCLUDED_)
