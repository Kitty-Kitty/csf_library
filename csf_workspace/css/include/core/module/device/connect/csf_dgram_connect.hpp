/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_dgram_connect.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:40
*
*Description: Class(csf_dgram_connect)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DGRAM_CONNECT_INCLUDED_)
#define CSF_DGRAM_CONNECT_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_url.hpp"
#include "csf_dgram_connect_interface.hpp"
#include "csf_connect.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * ��ʾ�������ݱ�����
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:40
				 */
				class csf_dgram_connect : public csf::core::module::device::csf_connect, public csf::core::module::device::csf_dgram_connect_interface
				{

				public:
					csf_dgram_connect();
					virtual ~csf_dgram_connect();

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
					 * ��ʾ��������Ϣ
					 * 
					 * @param url    ��ʾ���ӵ�ַ
					 */
					virtual void open(csf::core::module::device::csf_url url);
					/**
					 * ��ʾ�ر�����
					 */
					virtual csf::core::base::csf_uint32 close();
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
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(csf_csfstring& csfstr, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ���ӵ�����
					 */
					csf::core::module::device::csf_connect_type get_type();
					/**
					 * ��ʾд��ָ�����������
					 * 
					 * @param buffer    ��ʾ���ݵĻ����ַ
					 * @param length    ��ʾ���ݻ���ĳ���
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(csf_uchar* buffer, csf_uint32 length, csf_url& url, csf_connect_callback callback = csf_null);
					virtual void get_address();
					/**
					 * ��ʾ���ӵ�����
					 * 
					 * @param newVal
					 */
					csf_int32 set_type(csf::core::module::device::csf_connect_type newVal);
					csf_url& get_remote_url();
					virtual void set_address();
					virtual void set_option();
					/**
					 * 
					 * @param newVal
					 */
					csf_int32 set_remote_url(csf_url& newVal);
					/**
					 * ��ʾ���ص�������ַ
					 */
					csf_url& get_local_url();
					virtual void get_option();
					/**
					 * ��ʾ���ص�������ַ
					 * 
					 * @param newVal
					 */
					csf_int32 set_local_url(csf_url& newVal);
					/**
					 * ��ʾд��csf_buffer����
					 * 
					 * @param buffer    ��ʾ��Ҫд���csf_buffer����
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(csf_buffer& buffer, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param csfstr    ��ʾcsf_csfstring������
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(csf_csfstring& csfstr, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ����csf_csfstring����
					 * 
					 * @param csfstr    ��ʾcsf_csfstring������
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(csf_csfstring& csfstr, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾд��csf_buffer����
					 * 
					 * @param buffer    ��ʾ��Ҫд���csf_buffer����
					 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(csf_buffer& buffer, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾд��ָ�����������
					 * 
					 * @param buffer    ��ʾ���ݵĻ����ַ
					 * @param length    ��ʾ���ݻ���ĳ���
					 * @param callback    ��ʾ��Ҫ���صĻص�����
					 */
					virtual csf_int32 write(csf_uchar* buffer, csf_uint32 length, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					 * 
					 * @param length    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(csf_uchar* buffer, csf_int32 length, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(csf_buffer& buffer, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(csf_buffer& buffer, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
					 * 
					 * @param length    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(csf_uchar* buffer, csf_int32 length, csf_connect_callback callback = csf_null);
					/**
					 * ��ʾ��ȡ���ݲ�����ָ������λ��
					 * 
					 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
					 * @param callback    ��ʾ��ȡ�Ļص�����
					 */
					virtual csf_int32 read(csf_csfstring& csfstr, csf_connect_callback callback = csf_null);

				};

			}

		}

	}

}
#endif // !defined(CSF_DGRAM_CONNECT_INCLUDED_)
