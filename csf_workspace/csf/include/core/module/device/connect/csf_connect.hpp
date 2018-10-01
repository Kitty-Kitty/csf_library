/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_connect.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:36
*
*Description: Class(csf_connect) ��ʾͨ�ſ⣬����������Ϣ����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_H_INCLUDED_)
#define CSF_CONNECT_H_INCLUDED_

#include "csf_stdcplusplus.hpp"
#include "csf_url.hpp"
#include "csf_connect_interface.hpp"
#include "csf_configure_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				* ��ʾ����һ���������ӹ�����
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				class csf_connect_factory;

				/**
				 * ��ʾͨ�ſ⣬����������Ϣ����
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 01-10��-2018 12:54:36
				 */
				class csf_connect : public csf::core::module::connect::csf_connect_interface
				{

				public:
					/**
					 * ��ʾ���ӵ�����
					 * @author f
					 * @version 1.0
					 * @created 01-10��-2018 12:54:36
					 */
					typedef enum csf_connect_type_enum
					{
						/**
						* ��ʾδ֪����������
						*/
						csf_connect_type_none = 0x00000000,
						/**
						* ��ʾTCP��������
						*/
						csf_connect_type_tcp = 0x00000200,
						/**
						* ��ʾUDP��������
						*/
						csf_connect_type_udp = 0x00000400,
						/**
						* ��ʾ�鲥��������
						*/
						csf_connect_type_multicast = 0x00000402,
						/**
						* ��ʾ�㲥��������
						*/
						csf_connect_type_broadcast = 0x00000404
					} csf_connect_type;

					/**
					 * ��ʾ��ǰ������״̬
					 * @author f
					 * @version 1.0
					 * @created 01-10��-2018 12:54:36
					 */
					typedef enum csf_connect_status_enum
					{
						/**
						 * ��ʾ�򿪹رձ�ʶλ����ʶλΪ1��ʾ�򿪣���ʶλΪ0��ʾ�رգ�
						 */
						csf_connect_status_open = 0x00000001,
						/**
						 * ��ʾͬ����ʶλ������ʶλΪ1��ʾͬ������ʶλΪ0��ʾ�첽��Ĭ��Ϊ0�첽��ʽ��
						 */
						csf_connect_status_sync = 0x00000002,
						/**
						 * ��ʾʹ�ö���ʱ��ʶλ������Ϊ1��ʾʹ�ã�0��ʾ��ʹ�á�
						 */
						csf_connect_status_use_read_timeout = 0x00000004,
						/**
						 * ��ʾʹ��д��ʱ��ʶλ������Ϊ1��ʾʹ�ã�0��ʾ��ʹ�á�
						 */
						csf_connect_status_use_write_timeout = 0x00000008,
						/**
						 * ��ʾ����ʱ��ʶλ������Ϊ1��ʾ����ʱ��0��ʾ������
						 */
						csf_connect_status_read_deadline = 0x00000010,
						/**
						 * ��ʾд��ʱ��ʶλ������Ϊ1��ʾд��ʱ��0��ʾ������
						 */
						csf_connect_status_write_deadline = 0x00000020
					} csf_connect_status;


					csf_connect();
					virtual ~csf_connect();

					/**
					 * ��ʾͨ��factory����һ��connect
					 * 
					 * @param factory    ��ʾ��Ҫ����connect�Ĺ�����
					 */
					inline explicit csf_connect(csf_connect_factory* factory) {

					}
					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * ģ������
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * ��ʾ���ӵ�����
					 */
					inline csf_connect::csf_connect_type get_type() {

						return m_type;
					}
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
					 * 
					 * @param new_value
					 */
					csf_int32 set_remote_url(csf_url& new_value);
					/**
					 * ��ʾ���ص�������ַ
					 */
					csf_url& get_local_url();
					/**
					 * ��ʾ���ص�������ַ
					 * 
					 * @param new_value
					 */
					csf_int32 set_local_url(csf_url& new_value);
					/**
					 * ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
					 */
					inline csf_bool get_sync() {

						return m_sync;
					}
					/**
					 * ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
					 * 
					 * @param new_value
					 */
					inline csf_void set_sync(csf_bool new_value) {

						m_sync = new_value;
					}
					/**
					 * ��ʾ�����״̬��Ϣ
					 */
					inline csf_uint32 get_status() {

						return m_status;
					}
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
					 * ��ʾ����connect�Ĺ������ַ
					 * 
					 * @param new_value
					 */
					csf_void set_factory(csf_connect_factory* new_value);
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
					 * ��ʾ�������ӵ�������Ŀ��Ϣ��
					 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
					 */
					virtual csf_int32 set_option();
					/**
					 * ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
					 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
					 */
					virtual csf_int32 get_option();
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
					virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_nullptr);

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
					 * ��ʾ�����ļ�������
					 */
					csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
					/**
					 * ��ʾ���ӵĹ�������
					 */
					csf::core::module::connect::csf_connect_factory *m_connect_factory = csf_nullptr;

				};

				/**
				* ��ʾ����һ��������������ָ��
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_connect>				csf_connect_ptr;

				/**
				* ��ʾһ���յ�������������ָ��
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				static	csf_connect_ptr							m_null_connect_ptr;
			}

		}

	}

}
#endif // !defined(CSF_CONNECT_H_INCLUDED_)
