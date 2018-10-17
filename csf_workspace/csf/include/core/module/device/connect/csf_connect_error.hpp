/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_error.hpp
*
*Version: 1.0
*
*Date: 02-10��-2018 18:25:40
*
*Description: Class(csf_connect_error) ������������ͨ�Ŵ���
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_ERROR_H_INCLUDED_)
#define CSF_CONNECT_ERROR_H_INCLUDED_

#include "csf_error.hpp"
#include "csf_logger.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * ������������ͨ�Ŵ���
				 * @author f
				 * @version 1.0
				 * @created 02-10��-2018 18:25:40
				 */
				class csf_connect_error : public csf::core::module::csf_error
				{

				public:
					inline explicit csf_connect_error() {

					}
					virtual ~csf_connect_error() {

					}
					/**
					* ��ʾ���ݴ����루code���ʹ���������description������һ��csf_error��
					*
					* @param code    ��ʾ���������
					* @param description    ��ʾ����������Ϣ
					*/
					inline explicit csf_connect_error(const csf_int32 code, const csf_string& description)
						: csf_error(code, description) {

					}
					/**
					* ��ʾ���ݴ����루code���ʹ���������description������һ��csf_error��
					*
					* @param code    ��ʾ���������
					* @param description    ��ʾ����������Ϣ
					*/
					inline explicit csf_connect_error(const csf_int32 code, const csf_char* description)
						: csf_error(code, description) {

					}
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_ERROR_H_INCLUDED_)
