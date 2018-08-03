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
*Date: 29-7��-2018 15:13:08
*
*Description: Class(csf_dgram_connect) ��ʾͨ�ſ⣬���籨��������Ϣ����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DGRAM_CONNECT_INCLUDED_)
#define CSF_DGRAM_CONNECT_INCLUDED_

#include "csf_url.hpp"
#include "csf_connect_interface.hpp"
#include "csf_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾͨ�ſ⣬���籨��������Ϣ����
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 29-7��-2018 15:13:08
			 */
			class csf_dgram_connect : public csf::core::module::connect::csf_connect
			{

			public:
				csf_dgram_connect();
				virtual ~csf_dgram_connect();

				/**
				 * ��ʾͨ��factory����һ��connect
				 * 
				 * @param factory    ��ʾ��Ҫ����connect�Ĺ�����
				 */
				inline explicit csf_dgram_connect(csf_connect_factory* factory) {

				}
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
				 * ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				 */
				virtual csf_int32 get_option();
				/**
				 * ��ʾ���ӵ�����
				 */
				inline csf::core::module::connect::csf_connect::csf_connect_type get_type() {

					return m_type;
				}
				/**
				 * ��ʾ���ö���ʱʱ��.
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				 * 
				 * @param timeout_ms
				 * @param callback    ��ʾ��ʱ�ص�������
				 */
				virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback);
				/**
				 * ��ʾ���ӵ�����
				 * 
				 * @param newVal
				 */
				inline csf_int32 set_type(csf::core::module::connect::csf_connect::csf_connect_type newVal) {

					m_type = newVal;
				}
				csf_url& get_remote_url();
				/**
				 * ��ʾ����д��ʱʱ�䡣
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				 * 
				 * @param timeout_ms
				 * @param callback    ��ʾ��ʱ�ص�������
				 */
				virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback);
				/**
				 * 
				 * @param newVal
				 */
				csf_int32 set_remote_url(csf_url& newVal);
				/**
				 * ��ʾд��ָ����������ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 * 
				 * @param buf    ��ʾ���ݵĻ����ַ
				 * @param len    ��ʾ���ݻ���ĳ���
				 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null);
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
				virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾ���ص�������ַ
				 * 
				 * @param newVal
				 */
				csf_int32 set_local_url(csf_url& newVal);
				/**
				 * ��ʾ����csf_csfstring���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 * 
				 * @param csfstr    ��ʾcsf_csfstring������
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾ����csf_csfstring���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 * 
				 * @param chain    ��ʾcsf_chain������
				 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾд��csf_buffer���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 * 
				 * @param buffer    ��ʾ��Ҫд���csf_buffer����
				 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null);
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
				virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
				 * 
				 * @param newVal
				 */
				inline csf_void set_sync(csf_bool newVal) {

					m_sync = newVal;
				}
				/**
				 * ��ʾ����csf_csfstring���ݡ�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
				 * 
				 * @param csfstr    ��ʾcsf_csfstring������
				 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
				 * @param callback    ��ʾ��Ҫ���صĻص�����
				 */
				virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null);
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
				virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_null);
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
				virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾ�����״̬��Ϣ
				 * 
				 * @param newVal
				 */
				inline csf_void set_status(csf_uint32 newVal) {

					m_status = newVal;
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
				virtual csf_int32 read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
				 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾ����connect�Ĺ������ַ
				 * 
				 * @param newVal
				 */
				csf_void set_factory(csf_connect_factory* newVal);
				csf_uint32 get_read_timeout();
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_buffer& buffer, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
				 * 
				 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null);
				/**
				 * 
				 * @param newVal
				 */
				csf_void set_read_timeout(csf_uint32 newVal);
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
				virtual csf_int32 read(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
				 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null);
				/**
				 * ��ʾд��ʱʱ�䣬��λΪ���롣
				 * 
				 * @param newVal
				 */
				csf_void set_write_timeout(csf_uint32 newVal);
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
				csf::core::module::connect::csf_connect::csf_connect_type m_type = csf_connect_type_none;
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
#endif // !defined(CSF_DGRAM_CONNECT_INCLUDED_)
