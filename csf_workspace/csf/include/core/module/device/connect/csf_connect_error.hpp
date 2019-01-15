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

					/**
					* ��ʾ���ӵĴ������
					* @author f
					* @version 1.0
					* @updated 04-11��-2018 20:11:47
					*/
					typedef enum csf_connect_code_enum
					{
						/**
						* ��ʾδ֪�Ĵ������
						*/
						csf_connect_code_none = 0x00000000,
						/**
						* ��ʾ��ʱ�������
						*/
						csf_connect_code_timeout = 0x00000010,
						/**
						* ��ʾ�򿪼�����ַ�������
						*/
						csf_connect_code_listen = 0x00000020,
						/**
						* ��ʾ����Ƿ�����������Ϊ�մ���
						*/
						csf_connect_code_invalid_parametes = 0x00000040,
						/**
						* ��ʾ������ݵĿռ䲻��
						*/
						csf_connect_code_not_enough_space = 0x00000080,
						/**
						* ��ʾ���еĴ������
						*/
						csf_connect_code_operation_error = 0x00000100
					} csf_connect_code;

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
