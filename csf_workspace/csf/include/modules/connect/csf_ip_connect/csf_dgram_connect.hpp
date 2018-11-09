/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_dgram_connect.hpp
*
*Version: 1.0
*
*Date: 02-10��-2018 14:17:45
*
*Description: Class(csf_dgram_connect) ��ʾͨ�ſ⣬���籨��������Ϣ����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DGRAM_CONNECT_H_INCLUDED_)
#define CSF_DGRAM_CONNECT_H_INCLUDED_

#include "csf_ip_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾͨ�ſ⣬���籨��������Ϣ����
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 02-10��-2018 14:17:45
			 */
			class csf_dgram_connect : public csf::modules::connect::csf_ip_connect
			{

			public:
				csf_dgram_connect();
				virtual ~csf_dgram_connect();

				/**
				 * ��ʾͨ��factory����һ��connect
				 * 
				 * @param factory    ��ʾ��Ҫ����connect�Ĺ�����
				 */
				inline explicit csf_dgram_connect(csf_ip_connect_factory& factory, csf_connect_type type)
					: csf_ip_connect(factory, type) {

				}
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

			};

		}

	}

}
#endif // !defined(CSF_DGRAM_CONNECT_H_INCLUDED_)
