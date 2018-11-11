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

#include <memory>
#include "csf_url.hpp"
#include "csf_connect_timeout.hpp"
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
				 * ��ʾͨ�ſ⣬����������Ϣ����
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 01-10��-2018 12:54:36
				 */
				class csf_connect : public csf::core::module::connect::csf_connect_interface
					, public std::enable_shared_from_this<csf_connect>
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
						* ��ʾδ֪״̬������ʼ״̬
						*/
						csf_connect_status_none = 0x00000000,
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
					/**
					* ����csf_ip_connect_factory����һ�������׽���
					*
					* @param factory    ��ʾ���������׽��ֵĹ��������
					*/
					/**
					* ����csf_ip_connect_factory����һ�������׽���
					*
					* @param factory    ��ʾ���������׽��ֵĹ��������
					*/
					inline explicit csf_connect::csf_connect(csf_connect_factory& factory
						, csf_connect_type type)
						: csf_connect(&factory, type) {

					}
					/**
					 * ��ʾͨ��factory����һ��connect
					 *
					 * @param factory    ��ʾ��Ҫ����connect�Ĺ�����
					 */
					explicit csf_connect(csf_connect_factory* factory, csf_connect_type type);
					virtual ~csf_connect();
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
					inline virtual const csf_url& get_remote_url() const {
						return m_remote_url;
					}
					/**
					 *
					 * @param new_value
					 */
					inline virtual csf_int32 set_remote_url(csf_url& new_value) {

						m_remote_url = new_value;

						return csf_succeed;
					}
					/**
					* ��ʾԶ�̵�������ַ
					*
					* @param newVal    ��ʾurl�ַ�������
					*/
					inline virtual csf_int32 set_remote_url(csf_string newVal) {

						//m_remote_url = newVal;

						return csf_succeed;
					}
					/**
					 * ��ʾ���ص�������ַ
					 */
					inline virtual const csf_url& get_local_url() const {

						return m_local_url;
					}
					/**
					 * ��ʾ���ص�������ַ
					 *
					 * @param new_value
					 */
					inline virtual csf_int32 set_local_url(csf_url& new_value) {

						m_local_url = new_value;

						return csf_succeed;
					}
					/**
					* ��ʾ���ص�������ַ
					*
					* @param newVal    ��ʾurl�ַ�������
					*/
					inline virtual csf_int32 set_local_url(csf_string newVal) {

						//m_local_url = newVal;

						return csf_succeed;
					}
					/**
					* ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
					*/
					inline csf_bool get_is_sync() {

						return m_is_sync;
					}
					/**
					* ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
					*
					* @param newVal
					*/
					inline void set_is_sync(csf_bool newVal) {

						m_is_sync = newVal;
					}
					/**
					 * ��ʾ�����״̬��Ϣ
					 */
					inline csf_connect_status get_status() {

						return m_status;
					}
					/**
					 * ��ʾ�����״̬��Ϣ
					 *
					 * @param new_value
					 */
					inline csf_void set_status(csf_connect_status new_value) {

						m_status = new_value;
					}
					/**
					 * ��ʾ����connect�Ĺ������ַ
					 */
					inline csf_connect_factory* get_factory() {

						return m_factory;
					}
					/**
					 * ��ʾ����connect�Ĺ������ַ
					 *
					 * @param new_value
					 */
					csf_void set_factory(csf_connect_factory* new_value) {

						m_factory = new_value;
					}
					/**
					* ��ʾ����������������ӳ���
					*/
					inline static const csf_unordered_map<csf_connect::csf_connect_type, csf_string>& get_connect_type_name() {

						return m_connect_type_name;
					}
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
					* ��Ҫ�����ǣ����ö���ʱʱ��.
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param timeout_ms    ��ʾ��ʱ��ʱ����ֵ����λ�����루ms��
					* @param callback    ��ʾ��ʱ�ص�������
					*/
					virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����д��ʱʱ�䡣
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param timeout_ms    ��ʾ��ʱ��ʱ����ֵ����λ�����루ms��
					* @param callback    ��ʾ��ʱ�ص�������
					*/
					virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback& callback = csf_nullptr);
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
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫд���csf_buffer����
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_buffer& buffer, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param csfstr    ��ʾcsf_csfstring������
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_csfstring& csfstr, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param chain    ��ʾcsf_chain������
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_chain& chain, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�д��ָ����������ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buf    ��ʾ���ݵĻ����ַ
					* @param len    ��ʾ���ݻ���ĳ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫд���csf_buffer����
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_buffer& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param csfstr    ��ʾcsf_csfstring������
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_csfstring& csfstr, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param chain    ��ʾcsf_chain������
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_chain& chain, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�д��ָ����������ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�д��ָ����������ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					*
					* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_char_read_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_buffer& buffer, const csf_uint32 len, const csf_buffer_read_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_csfstring& csfstr, const csf_uint32 len, const csf_csfstr_read_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_chain& chain, const csf_uint32 len, const csf_chain_read_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ�ŵĻ������
					*
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_uchar>& buffer, const csf_char_buffer_read_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_buffer>& buffer, const csf_buffer_buffer_read_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_csfstring>& buffer, const csf_csfstr_buffer_read_callback& callback = csf_nullptr);
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_chain>& buffer, const csf_chain_buffer_read_callback& callback = csf_nullptr);
					/**
					* ��ʾ�첽����ʱ����
					*/
					inline virtual csf::core::module::connect::csf_connect_timeout& get_read_timeout() {

						return m_read_timeout;
					}
					/**
					* ��ʾ�첽д��ʱ����
					*/
					inline virtual csf::core::module::connect::csf_connect_timeout& get_write_timeout() {

						return m_write_timeout;
					}
				protected:
					/**
					* ��ʾ�첽д��ʱ����
					*
					* @param newVal
					*/
					inline virtual void set_write_timeout(csf::core::module::connect::csf_connect_timeout& newVal) {

						m_write_timeout = newVal;
					}
					/**
					* ��ʾ�첽����ʱ����
					*
					* @param newVal
					*/
					inline virtual void set_read_timeout(csf::core::module::connect::csf_connect_timeout& newVal) {

						m_read_timeout = newVal;
					}
					/**
					* ��Ҫ�����ǣ������첽д��ʱ����
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*/
					inline virtual void flush_write_timeout();
					/**
					* ��Ҫ�����ǣ������첽����ʱ����
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*/
					inline virtual void flush_read_timeout();
					/**
					* ��Ҫ�����ǣ����ӳ�ʱ���������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param connect_ptr    ��ʾ���Ӷ���
					* @param connect_error    ��ʾ���Ӵ�����Ϣ
					*/
					csf::core::base::csf_int32 timeout_handle(csf_connect_ptr connect_ptr, csf_connect_error connect_error);
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
					* ��ʾ�첽����ʱ����
					*/
					csf::core::module::connect::csf_connect_timeout m_read_timeout;
					/**
					* ��ʾ�첽д��ʱ����
					*/
					csf::core::module::connect::csf_connect_timeout m_write_timeout;
					/**
					* ��ʾͬ����־λ���豸�ñ�ʶλ��ǿ��ͨ�Ų���ͬ�����͡���sync=true��ʾ����ͬ����ʽ���͡�
					*/
					csf_bool m_is_sync = csf_false;
					/**
					 * ��ʾ�����״̬��Ϣ
					 */
					csf_connect_status m_status = csf_connect_status_none;
					/**
					 * ��ʾ����connect�Ĺ������ַ
					 */
					csf_connect_factory* m_factory = csf_nullptr;
					/**
					 * ��ʾ�����ļ�������
					 */
					csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
					/**
					* ��ʾ����������������ӳ���
					*/
					static const csf_unordered_map<csf_connect::csf_connect_type, csf_string> m_connect_type_name;

				};

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
