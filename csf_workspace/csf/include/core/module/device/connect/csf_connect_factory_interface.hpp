/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 28-7��-2018 14:23:34
*
*Description: Interface(csf_connect_factory_interface) <ul>
	<li></li>
</ul>
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_INTERFACE_INCLUDED_)
#define CSF_CONNECT_FACTORY_INTERFACE_INCLUDED_

#include "csf_interface.hpp"
#include "csf_connect.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * <ul>
				 * 	<li></li>
				 * </ul>
				 * @author f
				 * @version 1.0
				 * @created 28-7��-2018 14:23:34
				 */
				class csf_connect_factory_interface : public csf::core::module::csf_interface
				{

				public:
					csf_connect_factory_interface() {

					}

					virtual ~csf_connect_factory_interface() {

					}

					/**
					 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 */
					virtual csf_connect* create(const csf_connect::csf_connect_type type) =0;
					/**
					 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
					 */
					virtual csf_connect* create(const csf_connect::csf_connect_type type, const csf_url& local_url) =0;
					/**
					 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
					 * 
					 * @param type    ��ʾ��������
					 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
					 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
					 */
					virtual csf_connect* create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) =0;
					/**
					 * ��ʾ�����������ӣ����ٳɹ�����0��ʧ�ܷ���<0����ֵ��
					 * 
					 * @param connect    ��ʾ��Ҫ���ٵ�����
					 */
					virtual csf_int32 destroy(const csf_connect* connect) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_INTERFACE_INCLUDED_)
