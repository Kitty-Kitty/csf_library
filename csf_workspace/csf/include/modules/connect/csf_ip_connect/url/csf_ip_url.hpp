/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_url.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:43
*
*Description: Class(csf_ip_url) ��ʾ�����ַ���󡣵�ַ��ʽΪ��ip:port������:192.168.1.10:80
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_URL_H_INCLUDED_)
#define CSF_IP_URL_H_INCLUDED_

#include "csf_url.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/************************************************************************/
			/* ��Ҫ��ȡ�Ĳ�������														*/
			/************************************************************************/
			#define csf_ip_url_parametes_size						2		//��ʾ��Ҫ��ȡ�Ĳ�������
			/************************************************************************/
			/* ��ʾip url ����Ĭ�ϵĻ����С											*/
			/************************************************************************/
			#define csf_ip_url_buffer_size							32		//��ʾip url ����Ĭ�ϵĻ����С
			/**
			 * @author f
			 * @version 1.0
			 * @created 01-10��-2018 12:54:43
			 */
			class csf_ip_url : public csf::core::module::connect::csf_url
			{

			public:
				csf_ip_url();
				virtual ~csf_ip_url();
				/**
				* ��Ҫ�����ǣ�ͨ��url�ַ�����������url����
				* ���أ����쳣��ʾ�ɹ����׳��쳣��ʾ����
				*
				* @param url    ��ʾurl�ַ������ݣ���ַ��ʽΪ��xxx.xxx.xxx.xxx������:192.168.1.10
				*/
				inline csf_url& operator =(const csf_char* url) {

// 					if (set_url(url)) {
// 						throw url;
// 					}
					set_url(url);

					return *this;
				}
				/**
				* ��Ҫ�����ǣ�ͨ��url�ַ�����������url����
				* ���أ����쳣��ʾ�ɹ����׳��쳣��ʾ����
				*
				* @param url    ��ʾurl�ַ������ݣ���ַ��ʽΪ��xxx.xxx.xxx.xxx������:192.168.1.10
				*/
				inline csf_url& operator =(const csf_string& url) {

// 					if (set_url(url)) {
// 						throw url;
// 					}
					set_url(url);

					return *this;
				}
				/**
				 * ��ʾIP��ַ�ַ���
				 */
				inline const csf_string & get_ip() {

					return m_ip;
				}
				/**
				 * ��ʾIP��ַ�ַ���
				 * 
				 * @param new_value
				 */
				inline csf_bool set_ip(const csf_string& new_value) {

					if (check_ip(new_value)) {
						m_ip = new_value;
						return csf_true;
					}
					return csf_false;
				}
				/**
				 * ��ȡ�˿�����
				 */
				inline csf::core::base::csf_ushort get_port() {

					return m_port;
				}
				/**
				 * ���ö˿�����
				 * 
				 * @param new_value
				 */
				inline void set_port(const csf::core::base::csf_ushort new_value) {

					m_port = new_value;
				}
				/**
				 * ��ʾ������ַ����
				 * 
				 * @param url    ��ʾurl��ַ�ַ�������
				 */
				virtual csf_int32 parse(const csf_string& url);
				/**
				 * ��ʾIP��ַ�ַ���
				 * 
				 * @param new_value
				 */
				inline csf_bool set_ip(const csf_char* new_value) {

					return set_ip(csf_string(new_value));
				}
				/**
				* ��Ҫ�����ǣ���ʾurl�������ַ�������
				* ���أ�0��ʾ�ɹ�����0��ʾ����
				*
				* @param newVal    ��ʾurl�ַ������ݣ���ַ��ʽΪ��xxx.xxx.xxx.xxx������:192.168.1.10
				*/
				inline csf_int32 set_url(const csf_char* newVal) {

					if (csf_succeed == parse(newVal)) {
						csf_url::set_url(newVal);
						return csf_succeed;
					}
					
					return csf_failure;
				}
				/**
				* ��Ҫ�����ǣ���ʾurl�������ַ�������
				* ���أ�0��ʾ�ɹ�����0��ʾ����
				*
				* @param newVal    ��ʾurl�ַ������ݣ���ַ��ʽΪ��xxx.xxx.xxx.xxx������:192.168.1.10
				*/
				inline csf_int32 set_url(const csf_string& newVal) {

					return set_url((csf_char*)(newVal.c_str()));
				}
				/**
				* ��Ҫ�����ǣ�����ip�Ͷ˿ں�����url��Ϣ
				* ���أ�0��ʾ�ɹ�����0��ʾ����
				*
				* @param ip    ��ʾip�ַ������ݣ���ַ��ʽΪ��xxx.xxx.xxx.xxxxt������:192.168.1.10
				* @param port    ��ʾ�˿�����
				*/
				csf_int32 set_url(const csf_string& ip, const csf_ushort port);
				/**
				* ��ʾ������ַ����
				*
				* @param url    ��ʾurl�ַ������ݣ���ַ��ʽΪ��xxx.xxx.xxx.xxx������:192.168.1.10����ַ��ʽΪ��ip:port������:192.168.1.10:80
				*/
				inline virtual csf_int32 csf_ip_url::parse(const csf_char* url) {

					return parse(csf_string(url));
				}
				/**
				* ��Ҫ�����ǣ�У��url�����Ƿ��ǺϷ�
				* ���أ�true��ʾ�ǺϷ���false��ʾ���Ϸ�
				*
				* @param url    ��ʾ��ҪУ���url����
				*/
				inline static csf_bool is_valid_type(const csf_url& url) {

					if (csf_url::csf_url_type::csf_url_type_ip == ((csf_url&)url).get_type()) {
						return csf_true;
					}
					return csf_false;
				}
			protected:
				/**
				* ��Ҫ�����ǣ���ip��ַ�ĸ�ʽ�Ϸ���У��
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param ip    ��ʾ�����ַ��ʽ
				*/
				csf_bool check_ip(const csf_string& ip);
				/**
				* ��Ҫ�����ǣ���port��ֵ�Ϸ���У��
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param port    ��ʾ����˿�
				*/
				csf_bool check_port(const csf_string& port);
				/**
				* ��Ҫ�����ǣ���port��ֵ�Ϸ���У��
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param port    ��ʾ��Ҫ��У�����ֵ
				*/
				inline csf_bool check_port(const csf_ushort port) {
					if (port >= 0 && port <= csf_max_ushort ) {
						return csf_true;
					}
					return csf_false;
				}
			private:
				/**
				 * ��ʾIP��ַ�ַ���
				 */
				csf::core::base::csf_string m_ip = "";
				/**
				 * ��ʾ�����ַ�Ķ˿�����
				 */
				csf::core::base::csf_ushort m_port = 0;

			};

		}

	}

}
#endif // !defined(CSF_IP_URL_H_INCLUDED_)
