/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message_callback.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:44
*
*Description: Class(csf_message_callback)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MESSAGE_CALLBACK_INCLUDED_)
#define CSF_MESSAGE_CALLBACK_INCLUDED_

#include "csf_base_include.h"
#include "csf_stdcplusplus.hpp"
#include "csf_stdbind.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace message
			{
				/**
				* ��ʾ����һ������������
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				class csf_message;
				/**
				* ��ʾ����һ��������������ָ��
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_message>				csf_message_ptr;
				/**
				* ��ʾ���ӵķ��غ���
				* @author f
				* @version 1.0
				* @created 01-10��-2018 12:54:37
				*/
				typedef csf_function<csf_int32(csf_message_ptr
					, csf_connect_error&)> 	csf_connect_callback;

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_CALLBACK_INCLUDED_)
