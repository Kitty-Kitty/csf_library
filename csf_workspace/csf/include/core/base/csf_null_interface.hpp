/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_null_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 30-6��-2018 10:06:13
*
*Description: Interface(csf_null_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_NULL_INTERFACE_INCLUDED_)
#define CSF_NULL_INTERFACE_INCLUDED_

#include "csf_typedef.h"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾcsf�����������͵�null�жϲ����ӿڡ�
			 * @author f
			 * @version 1.0
			 * @created 30-6��-2018 10:06:13
			 */
			class csf_null_interface
			{

			public:
				csf_null_interface() {

				}

				virtual ~csf_null_interface() {

				}

				/**
				 * ��ʾ�ж��Ƿ�Ϊ�ա�
				 * ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				 */
				virtual csf_bool is_null() =0;
				/**
				 * ��ʾ�ж��Ƿ�Ϊ�ա�
				 * ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				 */
				virtual csf_bool not_null() =0;

			};

		}

	}

}
#endif // !defined(CSF_NULL_INTERFACE_INCLUDED_)
