/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_connect_interface.hpp
*
*Version: 1.0
*
*Date: 21-10��-2018 12:26:50
*
*Description: Interface(csf_connect_interface) ��ʾ����ͨ�ſ�����ӿ�����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_INTERFACE_H_INCLUDED_)
#define CSF_CONNECT_INTERFACE_H_INCLUDED_

#include "csf_base_include.h"
#include "csf_connect_buffer.hpp"
#include "csf_connect_callback.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				* ��ʾ����ͨ�ſ�����ӿ�����
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @updated 21-10��-2018 12:28:32
				*/
				class csf_connect_interface
				{
				public:
					/**
					* ��ʾ��ȡchar�Ļص�����
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, const csf_uchar*
						, const csf_uint32
						, csf_connect_error&)> 	csf_char_read_callback;
					/**
					* ��ʾ��ȡcsf_buffer�Ļص�����
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_buffer& buffer
						, const csf_uint32
						, csf_connect_error&)> 	csf_buffer_read_callback;
					/**
					* ��ʾ��ȡcsf_csfstring�Ļص�����
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_csfstring& csfstr
						, const csf_uint32
						, csf_connect_error&)> 	csf_csfstr_read_callback;
					/**
					* ��ʾ��ȡcsf_chain�Ļص�����
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_chain& chain
						, const csf_uint32
						, csf_connect_error&)> 	csf_chain_read_callback;
					/**
					* ��ʾ��ȡchar�Ļص�����
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_connect_buffer<csf_uchar>&
						, csf_connect_error&)> 	csf_char_buffer_read_callback;
					/**
					* ��ʾ��ȡcsf_buffer�Ļص�����
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_connect_buffer<csf_buffer>&
						, csf_connect_error&)> 	csf_buffer_buffer_read_callback;
					/**
					* ��ʾ��ȡcsf_csfstring�Ļص�����
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_connect_buffer<csf_csfstring>& csfstr
						, csf_connect_error&)> 	csf_csfstr_buffer_read_callback;
					/**
					* ��ʾ��ȡcsf_chain�Ļص�����
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_connect_buffer<csf_chain>& chain
						, csf_connect_error&)> 	csf_chain_buffer_read_callback;
				public:
					csf_connect_interface() {

					}

					virtual ~csf_connect_interface() {

					}
					/**
					* ��ʾ�첽����ʱ�ص�����
					*/
					csf::core::module::connect::csf_connect_callback m_read_timeout_callback = csf_nullptr;
					/**
					* ��ʾ�첽д��ʱ�ص�����
					*/
					csf::core::module::connect::csf_connect_callback m_write_timeout_callback = csf_nullptr;

					/**
					* ��Ҫ�����ǣ���ʾ��������Ϣ������bind����
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param url    ��ʾ���ӵ�ַ
					*/
					virtual csf_int32 open(const csf_url& url) = 0;
					/**
					* ��Ҫ�����ǣ��ر�����.
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*/
					virtual csf_int32 close() = 0;
					/**
					* ��Ҫ�����ǣ��������ӵ�������Ŀ��Ϣ��
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
					*/
					virtual csf_int32 set_option() = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ӵ�������Ŀ��Ϣ��
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
					*/
					virtual csf_int32 get_option() = 0;
					/**
					* ��Ҫ�����ǣ����ö���ʱʱ��.
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param timeout_ms    ��ʾ��ʱ��ʱ����ֵ����λ�����루ms��
					* @param callback    ��ʾ��ʱ�ص�������
					*/
					virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����д��ʱʱ�䡣
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param timeout_ms    ��ʾ��ʱ��ʱ����ֵ����λ�����루ms��
					* @param callback    ��ʾ��ʱ�ص�������
					*/
					virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���һ��������ַ��
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param url    ��ʾ��Ҫ�����ĵ�ַ
					* @param callback    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					*/
					virtual csf_int32 listen(const csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���Ҫ����һ����ַ��
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param url    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 connect(const csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�д��ָ����������ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buf    ��ʾ���ݵĻ����ַ
					* @param len    ��ʾ���ݻ���ĳ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫд���csf_buffer����
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_buffer& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param csfstr    ��ʾcsf_csfstring������
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_csfstring& csfstr, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param chain    ��ʾcsf_chain������
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_chain& chain, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�д��ָ����������ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buf    ��ʾ���ݵĻ����ַ
					* @param len    ��ʾ���ݻ���ĳ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫд���csf_buffer����
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_buffer& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param csfstr    ��ʾcsf_csfstring������
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_csfstring& csfstr, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param chain    ��ʾcsf_chain������
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_chain& chain, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�д��ָ����������ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�д��ָ����������ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
					*
					* @param buffer    ��ʾ��Ҫ���͵����ݻ���
					* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					* @param callback    ��ʾ��Ҫ���صĻص�����
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					*
					* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_char_read_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_buffer& buffer, const csf_uint32 len, const csf_buffer_read_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_csfstring& csfstr, const csf_uint32 len, const csf_csfstr_read_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_chain& chain, const csf_uint32 len, const csf_chain_read_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ�ŵĻ������
					*
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_uchar>& buffer, const csf_char_buffer_read_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_buffer>& buffer, const csf_buffer_buffer_read_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_csfstring>& buffer, const csf_csfstr_buffer_read_callback& callback = csf_nullptr) = 0;
					/**
					* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
					* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
					*
					* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
					* @param callback    ��ʾ��ȡ�Ļص�����
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_chain>& buffer, const csf_chain_buffer_read_callback& callback = csf_nullptr) = 0;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_INTERFACE_H_INCLUDED_)
