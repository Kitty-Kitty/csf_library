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
*Date: 28-7��-2018 14:23:33
*
*Description: Class(csf_connect) ��ʾͨ�ſ�����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_INCLUDED_)
#define CSF_CONNECT_INCLUDED_

#include "csf_url.hpp"
#include "csf_deadline_timer.hpp"
#include "csf_connect_interface.hpp"
#include "csf_configure_manager.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				//��ʾ���Ӵ���������
				class csf_connect_factory;

				/**
				 * ��ʾͨ�ſ�����
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 28-7��-2018 14:23:33
				 */
				class csf_connect : public csf::core::module::connect::csf_connect_interface
				{

				public:
					/**
					 * ��ʾ���ӵ�����
					 * @author f
					 * @version 1.0
					 * @created 28-7��-2018 14:23:33
					 */
					enum csf_connect_type
					{
						/**
						 * ��ʾδ֪����������
						 */
						csf_connect_type_none = 0,
						/**
						 * ��ʾTCP��������
						 */
						csf_connect_type_tcp,
						/**
						 * ��ʾUDP��������
						 */
						csf_connect_type_udp,
						/**
						 * ��ʾ�鲥��������
						 */
						csf_connect_type_multicast,
						/**
						 * ��ʾ�㲥��������
						 */
						csf_connect_type_broadcast
					};

					/**
					 * ��ʾ��ǰ������״̬
					 * @author f
					 * @version 1.0
					 * @created 28-7��-2018 14:23:33
					 */
					enum csf_connect_status
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
					};


					csf_connect();
					virtual ~csf_connect();

					/**
					 * ��ʾͨ��factory����һ��connect
					 * 
					 * @param factory    ��ʾ��Ҫ����connect�Ĺ�����
					 */
					inline explicit csf_connect(csf_connect_factory* factory) {

					}
					inline csf_configure_manager * get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * 
					 * @param newVal
					 */
					inline csf_void set_configure_manager(csf_configure_manager * newVal) {

						m_configure_manager = newVal;
					}
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
					inline csf_connect_type get_type() {

						return m_type;
					}
					/**
					 * ��ʾ���ӵ�����
					 * 
					 * @param newVal
					 */
					inline csf_int32 set_type(csf_connect_type newVal) {

						m_type = newVal;
					}
					csf_url& get_remote_url();
					/**
					 * 
					 * @param newVal
					 */
					csf_int32 set_remote_url(csf_url& newVal);
					/**
					 * ��ʾ���ص�������ַ
					 */
					csf_url& get_local_url();
					/**
					 * ��ʾ���ص�������ַ
					 * 
					 * @param newVal
					 */
					csf_int32 set_local_url(csf_url& newVal);
					/**
					 * ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
					 */
					inline csf_bool get_sync() {

						return m_sync;
					}
					/**
					 * ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
					 * 
					 * @param newVal
					 */
					inline csf_void set_sync(csf_bool newVal) {

						m_sync = newVal;
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
					 * ��ʾ����connect�Ĺ������ַ
					 * 
					 * @param newVal
					 */
					csf_void set_factory(csf_connect_factory* newVal);
					csf_uint32 get_read_timeout();
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
					 * ��ʾд��ʱʱ�䣬��λΪ���롣
					 * 
					 * @param newVal
					 */
					csf_void set_write_timeout(csf_uint32 newVal);
					/**
					 * ��ʾ��������Ϣ
					 * 
					 * @param url    ��ʾ���ӵ�ַ
					 */
					virtual csf_int32 open(const csf_url& url);
					/**
					 * ��ʾ�ر�����
					 */
					virtual csf_int32 close();
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������������
					 * 
					 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾд��ָ�����������
					 * 
					 * @param buf    ��ʾ���ݵĻ����ַ
					 * @param len    ��ʾ���ݻ���ĳ���
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
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
					 * ��ʾд��csf_buffer����
					 * 
					 * @param buffer    ��ʾ��Ҫд���csf_buffer����
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param csfstr    ��ʾcsf_csfstring������
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param chain    ��ʾcsf_chain������
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾд��csf_buffer����
					 * 
					 * @param buffer    ��ʾ��Ҫд���csf_buffer����
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾд��ָ�����������
					 * 
					 * @param buf    ��ʾ���ݵĻ����ַ
					 * @param len    ��ʾ���ݻ���ĳ���
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					 * 
					 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					 * 
					 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param csfstr    ��ʾcsf_csfstring������
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ���ö���ʱʱ��
					 * 
					 * @param timeout_ms
					 * @param callback    ��ʾ��ʱ�ص�������
					 */
					virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param chain    ��ʾcsf_chain������
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ����д��ʱʱ��
					 * 
					 * @param timeout_ms
					 * @param callback    ��ʾ��ʱ�ص�������
					 */
					virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������������
					 * 
					 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_nullptr);

				private:
					/**
					 * ��ʾ���ӵ�����
					 */
					csf_connect_type m_type = csf_connect_type_none;
					/**
					 * ��ʾԶ�˵�������ַ
					 */
					csf_url m_remote_url;
					/**
					 * ��ʾ���ص�������ַ
					 */
					csf_url m_local_url;
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

}
#endif // !defined(CSF_CONNECT_INCLUDED_)
