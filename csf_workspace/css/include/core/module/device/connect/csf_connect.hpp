/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:36
*
*Description: Class(csf_connect)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_INCLUDED_)
#define CSF_CONNECT_INCLUDED_

#include "csf_url.hpp"
#include "csf_configure_manager.hpp"
#include "csf_connect_interface.hpp"
#include "csf_connect_factory.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * ��ʾͨ�ſ�����
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6��-2018 17:28:36
				 */
				class csf_connect : public csf::core::module::device::csf_connect_interface
				{

				public:
					csf_connect();
					virtual ~csf_connect();

					/**
					 * ��ʾͨ��factory����һ��connect
					 * 
					 * @param factory    ��ʾ��Ҫ����connect�Ĺ�����
					 */
					csf_void csf_connect(csf_connect_factory* factory);
					inline csf::core::system::csf_configure_manager get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 
					 * @param newVal
					 */
					inline csf_void set_configure_manager(csf::core::system::csf_configure_manager newVal) {

						m_configure_manager = newVal;
					}
					/**
					 * ģ������
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ���ӵ�����
					 */
					inline csf::core::module::device::csf_connect_type get_type() {

						return m_type;
					}
					/**
					 * ��ʾ���ӵ�����
					 * 
					 * @param newVal
					 */
					inline csf_int32 set_type(csf::core::module::device::csf_connect_type newVal) {

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
					inline void set_sync(csf_bool newVal) {

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
					inline void set_status(csf_uint32 newVal) {

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
					void set_factory(csf_connect_factory* newVal);
					csf_uint32 get_read_timeout();
					/**
					 * 
					 * @param newVal
					 */
					void set_read_timeout(csf_uint32 newVal);
					/**
					 * ��ʾд��ʱʱ�䣬��λΪ���롣
					 */
					csf_uint32 get_write_timeout();
					/**
					 * ��ʾд��ʱʱ�䣬��λΪ���롣
					 * 
					 * @param newVal
					 */
					void set_write_timeout(csf_uint32 newVal);
					/**
					 * ��ʾ��������Ϣ
					 * 
					 * @param url    ��ʾ���ӵ�ַ
					 */
					virtual void open(const csf_url& url);
					/**
					 * ��ʾ�ر�����
					 */
					virtual csf::core::base::csf_uint32 close();
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������������
					 * 
					 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾд��ָ�����������
					 * 
					 * @param buf    ��ʾ���ݵĻ����ַ
					 * @param len    ��ʾ���ݻ���ĳ���
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null);
					virtual void set_option();
					virtual void get_option();
					/**
					 * ��ʾд��csf_buffer����
					 * 
					 * @param buffer    ��ʾ��Ҫд���csf_buffer����
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param csfstr    ��ʾcsf_csfstring������
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param chain    ��ʾcsf_chain������
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾд��csf_buffer����
					 * 
					 * @param buffer    ��ʾ��Ҫд���csf_buffer����
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾд��ָ�����������
					 * 
					 * @param buf    ��ʾ���ݵĻ����ַ
					 * @param len    ��ʾ���ݻ���ĳ���
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					 * 
					 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					 * 
					 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param csfstr    ��ʾcsf_csfstring������
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null);
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
					virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_null);
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
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������������
					 * 
					 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_null);

				private:
					/**
					 * ��ʾ���ӵ�����
					 */
					csf::core::module::device::csf_connect_type m_type = csf_connect_type_none;
					/**
					 * ��ʾԶ�˵�������ַ
					 */
					csf::core::module::device::csf_url m_remote_url;
					/**
					 * ��ʾ���ص�������ַ
					 */
					csf::core::module::device::csf_url m_local_url;
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
					csf_connect_factory* m_factory = csf_null;
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
					 * ��ʾ���ӵĹ�������
					 */
					csf::core::module::device::csf_connect_factory *m_connect_factory;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_INCLUDED_)
