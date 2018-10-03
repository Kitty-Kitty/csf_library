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
*Date: 02-10��-2018 14:17:58
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

#include "csf_ip_connect.hpp"

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
			 * @created 02-10��-2018 14:17:58
			 */
			class csf_stream_connect : public csf::modules::connect::csf_ip_connect
			{

			public:
				csf_stream_connect();
				virtual ~csf_stream_connect();

				/**
				 * ��ʾͨ��factory����һ��connect
				 * 
				 * @param factory    ��ʾ��Ҫ����connect�Ĺ�����
				 */
				inline explicit csf_stream_connect(csf_ip_connect_factory& factory)
					: csf_ip_connect(factory) {

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
				 * ��ʾ���ö���ʱʱ��.
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				 * 
				 * @param timeout_ms
				 * @param callback    ��ʾ��ʱ�ص�������
				 */
				virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr);
				/**
				 * ��ʾ����д��ʱʱ�䡣
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
				 * 
				 * @param timeout_ms
				 * @param callback    ��ʾ��ʱ�ص�������
				 */
				virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr);
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
				 * ��ʾ��ȡ���ݲ�����ָ�����������С�
				 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
				 * 
				 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
				 * @param callback    ��ʾ��ȡ�Ļص�����
				 */
				virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_null);

			};

		}

	}

}
#endif // !defined(CSF_STREAM_CONNECT_H_INCLUDED_)
