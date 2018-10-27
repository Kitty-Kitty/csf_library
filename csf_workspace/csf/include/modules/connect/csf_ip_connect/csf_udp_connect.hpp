/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_udp_connect.hpp
*
*Version: 1.0
*
*Date: 02-10��-2018 14:18:02
*
*Description: Class(csf_udp_connect) ��ʾudp����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_UDP_CONNECT_H_INCLUDED_)
#define CSF_UDP_CONNECT_H_INCLUDED_

#include "csf_dgram_connect.hpp"
#include "csf_ip_connect_factory.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾudp����
			 * @author f
			 * @version 1.0
			 * @created 02-10��-2018 14:18:02
			 */
			class csf_udp_connect : public csf::modules::connect::csf_dgram_connect
			{
			public:
				/**
				* ��ʾ����һ��tcp������������ָ��
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_udp_connect>				csf_udp_connect_ptr;

			public:
				/**
				* ����csf_ip_connect_factory����һ�������׽���
				*
				* @param factory    ��ʾ���������׽��ֵĹ��������
				*/
				inline explicit csf_udp_connect(csf_ip_connect_factory& factory)
					: csf_dgram_connect(factory)
					, m_socket(factory.get_io_service()) {

				}
				virtual ~csf_udp_connect();

				/**
				* ģ���ʼ��
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
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
				* ģ������
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
				/**
				* ��ʾ�������ӵ�������Ŀ��Ϣ��
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				*/
				virtual csf_int32 set_option();
				/**
				* ģ��ֹͣ
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
				/**
				* ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
				* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				*/
				virtual csf_int32 get_option();
				/**
				* ��ʾԶ�̵�������ַ
				*/
				inline virtual const csf_url& get_remote_url() const {

					return csf_ip_connect::get_remote_url();
				}
				/**
				* ��ʾ���ص�������ַ
				*/
				inline virtual const csf_url& get_local_url() const {

					return csf_ip_connect::get_local_url();
				}
			protected:
				/**
				* ��ʾ���������׽���
				*/
				inline const boost::asio::ip::udp::socket& get_socket() const {

					return m_socket;
				}
			private:
				/**
				* ��ʾ���������׽���
				*/
				boost::asio::ip::udp::socket m_socket;
			};
		}

	}

}
#endif // !defined(CSF_UDP_CONNECT_H_INCLUDED_)
