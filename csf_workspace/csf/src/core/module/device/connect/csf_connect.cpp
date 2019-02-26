/*******************************************************************************
*
*Copyright: fangzhenmu@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_connect.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:37
*
*Description: Class(csf_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_connect.hpp"
#include "csf_connect_factory.hpp"
#include "system_time.hpp"

using namespace csf::core::module::connect;
using csf::core::module::connect::csf_connect;

/**
* ��ʾ������������ӳ���
*/
const csf_map<csf_connect::csf_connect_type, csf_string> csf_connect::m_connect_type_name = {
	{ csf_connect::csf_connect_type::csf_connect_type_none, "none"},
	{ csf_connect::csf_connect_type::csf_connect_type_tcp, "tcp" },
	{ csf_connect::csf_connect_type::csf_connect_type_udp, "udp" },
	{ csf_connect::csf_connect_type::csf_connect_type_multicast, "multicast" },
	{ csf_connect::csf_connect_type::csf_connect_type_broadcast, "broadcast" }
};


csf_connect::csf_connect()
	: m_type(csf_connect_type_none)
	, m_is_sync(csf_false)
	, m_is_filled(csf_false)
	, m_status(csf_connect_status_none)
	, m_factory(csf_nullptr)
	, m_configure_manager(csf_nullptr)
	, m_format{ 0, }  {

}


/**
* ��ʾͨ��factory����һ��connect
*
* @param factory    ��ʾ��Ҫ����connect�Ĺ�����
*/
csf_connect::csf_connect(csf_connect_factory* factory, csf_connect_type type)
	: m_type(type)
	, m_is_sync(csf_false)
	, m_is_filled(csf_false)
	, m_status(csf_connect_status_none)
	, m_factory(factory)
	, m_configure_manager(factory->get_configure_manager())
	, m_format{ 0, } {

}


csf_connect::~csf_connect() {

	//��������ʱ����Ҫ��ջ�������
	get_read_buffer().clear();
	get_write_buffer().clear();
}


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ��������Ϣ.
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 * 
 * @param url    ��ʾ���ӵ�ַ
 */
csf_int32 csf_connect::open(const csf_url& url) {

	return 0;
}


/**
 * ��ʾ�ر�����.
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 */
csf_int32 csf_connect::close() {

	//���ö�д��ʱ
	get_read_timeout().set_expired();
	get_write_timeout().set_expired();

	return csf_succeed;
}


/**
 * ��ʾ�������ӵ�������Ŀ��Ϣ��
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
 */
csf_int32 csf_connect::set_option() {

	return 0;
}


/**
 * ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
 */
csf_int32 csf_connect::get_option() {

	return 0;
}


/**
* ��Ҫ�����ǣ����ö���ʱʱ��.
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param timeout_ms		��ʾ��ʱ��ʱ����ֵ����λ�����루ms��
* @param callback    ��ʾ��ʱ�ص�������
*/
csf_int32 csf_connect::set_read_timeout(const csf_uint64 timeout_ms, const csf_connect_callback& callback) {

	get_read_timeout().set_time(csf::core::utils::time::system_time::get_time());
	get_read_timeout().set_timeout(timeout_ms);
	if (csf_nullptr == callback) {
		get_read_timeout().set_handle(
			csf_bind(&csf_connect::timeout_handle
				, this
				, std::placeholders::_1
				, std::placeholders::_2));
	}
	else {
		get_read_timeout().set_handle(callback);
	}
	
	get_factory()->get_timeout_manager().insert(get_read_timeout(), shared_from_this());

	return csf_succeed;
}


/**
* ��Ҫ�����ǣ�����д��ʱʱ�䡣
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param timeout_ms		��ʾ��ʱ��ʱ����ֵ����λ�����루ms��
* @param callback    ��ʾ��ʱ�ص�������
*/
csf_int32 csf_connect::set_write_timeout(const csf_uint64 timeout_ms, const csf_connect_callback& callback) {

	get_write_timeout().set_time(csf::core::utils::time::system_time::get_time());
	get_write_timeout().set_timeout(timeout_ms);
	if (csf_nullptr == callback) {
		get_write_timeout().set_handle(
			csf_bind(&csf_connect::timeout_handle
				, this
				, std::placeholders::_1
				, std::placeholders::_2));
	}
	else {
		get_write_timeout().set_handle(callback);
	}
	get_factory()->get_timeout_manager().insert(get_write_timeout(), shared_from_this());

	return 0;
}


/**
* ��Ҫ�����ǣ������첽д��ʱ����
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*/
inline void csf_connect::flush_write_timeout() {
	get_write_timeout().set_time(csf::core::utils::time::system_time::get_time());
}


/**
* ��Ҫ�����ǣ������첽����ʱ����
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*/
inline void csf_connect::flush_read_timeout() {
	get_read_timeout().set_time(csf::core::utils::time::system_time::get_time());
}


/**
* ��Ҫ�����ǣ���һ��������ַ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param url    ��ʾ��Ҫ�����ĵ�ַ
* @param callback    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
*/
csf_int32 csf_connect::listen(const csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���Ҫ����һ����ַ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param url    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_connect::connect(const csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_buffer& buffer, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_csfstring& csfstr, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_chain& chain, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(const csf_uchar* buf, const csf_uint32 len, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_buffer& buffer, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_csfstring& csfstr, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_chain& chain, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_uchar>& buffer, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_connect::write(csf_connect_buffer<csf_buffer>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_csfstring>& buffer, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_chain>& buffer, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
*
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_connect::read(csf_buffer& buffer, const csf_uint32 len, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_connect::read(csf_csfstring& csfstr, const csf_uint32 len, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_connect::read(csf_chain& chain, const csf_uint32 len, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ�ŵĻ������
*
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_connect::read(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {
	return 0;
}



/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_connect::read(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_connect::read(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* ��Ҫ�����ǣ����ӳ�ʱ���������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param connect_ptr    ��ʾ���Ӷ���
* @param connect_error    ��ʾ���Ӵ�����Ϣ
*/
csf::core::base::csf_int32 csf_connect::timeout_handle(csf_connect_ptr connect_ptr, csf_connect_error connect_error) {

	connect_ptr->close();
	get_factory()->remove(connect_ptr);

	csf_log_ex(info
		, csf_log_code_info
		, "connect[%p] timeout."
		, connect_ptr.get());

	return 0;
}
