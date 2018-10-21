/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connect_timeout.hpp
*
*Version: 1.0
*
*Date: 21-10��-2018 14:31:55
*
*Description: Class(csf_ip_connect_timeout) ��ʾip_connect�ĳ�ʱ����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNECT_TIMEOUT_H_INCLUDED_)
#define CSF_IP_CONNECT_TIMEOUT_H_INCLUDED_

#include "csf_boost_asio.hpp"
#include "csf_connect_timeout.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾip_connect�ĳ�ʱ����
			 * @author f
			 * @version 1.0
			 * @created 21-10��-2018 14:31:55
			 */
			class csf_ip_connect_timeout : public csf::core::module::connect::csf_connect_timeout
			{
			public:
				/**
				* ��ʾ���߶�ʱ��
				* @author f
				* @version 1.0
				* @updated 01-10��-2018 15:12:05
				*/
				typedef boost::asio::deadline_timer			csf_deadline_timer;
			public:
				virtual ~csf_ip_connect_timeout() {

				}
				/**
				* ��Ҫ�����ǣ�����io_service����һ��timeout����
				* ���أ���
				*
				* @param io_service    ��ʾboost��io_service����
				*/
				inline explicit csf_ip_connect_timeout(boost::asio::io_service& io_service)
					: m_deadline_timer(io_service) {

				}
				/**
				* ��Ҫ�����ǣ�����io_service�ͻ�����Ϣ����һ��timeout����
				* ���أ���
				*
				* @param io_service    ��ʾboost��io_service����
				* @param time    ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
				*
				* @param handle    ��ʾ��ʱ��Ļص�����
				*/
				inline explicit csf_ip_connect_timeout(boost::asio::io_service& io_service
					, const csf_uint32 time
					, const csf::core::module::connect::csf_connect_callback handle)
					: csf_connect_timeout(time, handle)
					, m_deadline_timer(io_service) {

				}
				/**
				* ��ʾ��ʱ��ʱ������
				*/
				inline csf_deadline_timer& get_deadline_timer() {

					return m_deadline_timer;
				}

			private:
				/**
				 * ��ʾ��ʱ��ʱ������
				 */
				csf_deadline_timer m_deadline_timer;

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNECT_TIMEOUT_H_INCLUDED_)
