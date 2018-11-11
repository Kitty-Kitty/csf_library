/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connect.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 15:10:39
*
*Description: Class(csf_ip_connect) ��ʾIP���͵�������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_H_INCLUDED_)
#define CSF_IP_CONNNECT_H_INCLUDED_

#include "csf_ip_url.hpp"
#include "csf_connect.hpp"
#include "csf_ip_connect_factory.hpp"
#include "csf_ip_connect_error.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾIP���͵�������
			 * @author f
			 * @version 1.0
			 * @updated 01-10��-2018 15:12:05
			 */
			class csf_ip_connect : public csf::core::module::connect::csf_connect
			{

			public:
				/**
				* ����csf_ip_connect_factory����һ�������׽���
				*
				* @param factory    ��ʾ���������׽��ֵĹ��������
				*/
				inline explicit csf_ip_connect(csf_ip_connect_factory& factory, csf_connect_type type)
					: csf_connect(factory, type) {

				}
				virtual ~csf_ip_connect();
				/**
				* ��ʾԶ�̵�������ַ
				*
				* @param newVal    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_remote_url(csf_string newVal) {

					m_remote_url = newVal;

					return csf_succeed;
				}
				/**
				* ��ʾԶ�������ַ
				*
				* @param newVal    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_remote_url(csf::core::module::connect::csf_url& newVal) {

					m_remote_url = (csf::modules::connect::csf_ip_url&)newVal;

					return csf_succeed;
				}
				/**
				* ��ʾ���ص�������ַ
				*
				* @param newVal    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_local_url(csf_string newVal) {

					m_local_url = newVal;

					return csf_succeed;
				}
				/**
				* ��ʾ���������ַ
				*
				* @param newVal    ��ʾurl�ַ�������
				*/
				inline virtual csf_int32 set_local_url(csf::core::module::connect::csf_url& newVal) {

					m_local_url = (csf::modules::connect::csf_ip_url&)newVal;

					return csf_succeed;
				}
				/**
				* ��ʾԶ�������ַ
				*/
				inline virtual const csf_url& get_remote_url() const {

					return m_remote_url;
				}
				/**
				* ��ʾ���������ַ
				*/
				inline virtual const csf_url& get_local_url() const {

					return m_local_url;
				}
			protected:
				/**
				* ��Ҫ�����ǣ���Դ�����쳣�Ĵ���
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param connect_ptr    ��ʾ������������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾ�쳣��Ϣ����
				*/
				inline csf_int32 async_callback(csf_connect_ptr& connect_ptr
					, const csf_connect_callback& callback
					, csf_ip_connect_error& error_code) {

					if (!connect_ptr 
						|| csf_nullptr == callback) {
						return csf_failure;
					}
					else {
						return callback(connect_ptr, error_code);
					}

					return csf_succeed;
				}
				/**
				* ��Ҫ�����ǣ���Դ�����쳣�Ĵ���
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param connect_ptr    ��ʾ������������Ӷ���
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾ�쳣��Ϣ����
				*/
				inline csf_int32 exception_callback(csf_connect_ptr& connect_ptr
					, const csf_connect_callback& callback
					, csf_ip_connect_error& error_code) {

					return async_callback(connect_ptr, callback, error_code);
				}

				/**
				* ��Ҫ�����ǣ������첽д����ص�����
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾboost�Ĵ�����Ϣ
				* @param len    ��ʾ���ݳ�����Ϣ
				*/
				inline csf_bool csf_ip_connect::async_write_callback(const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 len) {

					async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));

					return csf_true;
				}
				/**
				* ��Ҫ�����ǣ������첽������ص�����
				* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
				*
				* @param callback    ��ʾ�쳣��������Ϣ
				* @param error_code    ��ʾboost�Ĵ�����Ϣ
				* @param len    ��ʾ���ݳ�����Ϣ
				*/
				inline csf_bool csf_ip_connect::async_read_callback(const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 len) {

					async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));

					return csf_true;
				}
			private:
				/**
				* ��ʾԶ�������ַ
				*/
				csf::modules::connect::csf_ip_url m_remote_url;
				/**
				* ��ʾ���������ַ
				*/
				csf::modules::connect::csf_ip_url m_local_url;

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_H_INCLUDED_)
