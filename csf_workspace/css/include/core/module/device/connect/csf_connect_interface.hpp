/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:38
*
*Description: Interface(csf_connect_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_INTERFACE_INCLUDED_)
#define CSF_CONNECT_INTERFACE_INCLUDED_

#include "csf_connect_callback.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * ��ʾ����ͨ�ſ�����ӿ�����
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6��-2018 17:28:38
				 */
				class csf_connect_interface
				{

				public:
					csf_connect_interface() {

					}

					virtual ~csf_connect_interface() {

					}
					/**
					 * ��ʾ�첽���ص�����
					 */
					csf::core::module::device::csf_connect_callback m_read_callback = csf_null;
					/**
					 * ��ʾ�첽д�ص�����
					 */
					csf::core::module::device::csf_connect_callback m_write_callback = csf_null;
					/**
					 * ��ʾ�첽����ʱ�ص�����
					 */
					csf::core::module::device::csf_connect_callback m_read_timeout_callback = csf_null;
					/**
					 * ��ʾ�첽д��ʱ�ص�����
					 */
					csf::core::module::device::csf_connect_callback m_write_timeout_callback = csf_null;

					/**
					 * ��ʾ��������Ϣ
					 * 
					 * @param url    ��ʾ���ӵ�ַ
					 */
					virtual void open(const csf_url& url) =0;
					/**
					 * ��ʾ�ر�����
					 */
					virtual csf::core::base::csf_uint32 close() =0;
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������������
					 * 
					 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾд��ָ�����������
					 * 
					 * @param buf    ��ʾ���ݵĻ����ַ
					 * @param len    ��ʾ���ݻ���ĳ���
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					virtual void set_option() =0;
					virtual void get_option() =0;
					/**
					 * ��ʾд��csf_buffer����
					 * 
					 * @param buffer    ��ʾ��Ҫд���csf_buffer����
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param csfstr    ��ʾcsf_csfstring������
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param chain    ��ʾcsf_chain������
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾд��csf_buffer����
					 * 
					 * @param buffer    ��ʾ��Ҫд���csf_buffer����
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾд��ָ�����������
					 * 
					 * @param buf    ��ʾ���ݵĻ����ַ
					 * @param len    ��ʾ���ݻ���ĳ���
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					 * 
					 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					 * 
					 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ���ö���ʱʱ��
					 * 
					 * @param timeout_ms
					 * @param callback    ��ʾ��ʱ�ص�������
					 */
					virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) =0;
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param csfstr    ��ʾcsf_csfstring������
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ����д��ʱʱ��
					 * 
					 * @param timeout_ms
					 * @param callback    ��ʾ��ʱ�ص�������
					 */
					virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) =0;
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param chain    ��ʾcsf_chain������
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������������
					 * 
					 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_null) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_INTERFACE_INCLUDED_)
