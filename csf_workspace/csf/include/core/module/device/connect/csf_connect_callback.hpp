/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_callback.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:37
*
*Description: Class(csf_connect_callback) ��ʾ���ӵķ��غ���
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_CALLBACK_H_INCLUDED_)
#define CSF_CONNECT_CALLBACK_H_INCLUDED_

#include "csf_base_include.h"
#include "csf_stdbind.hpp"
#include "csf_connect_error.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				* ��ʾ����һ������������
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				class csf_connect;
				/**
				* ��ʾ����һ���������ӹ�����
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				class csf_connect_factory;
				/**
				* ��ʾ����һ���������ӹ����������
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				class csf_connect_factory_manager;
				/**
				* ��ʾ����һ��������������ָ��
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_connect>				csf_connect_ptr;
				/**
				* ��ʾ����һ���������ӹ���������ָ��
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10��-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_connect_factory>		csf_connect_factory_ptr;
				/**
				 * ��ʾ���ӵķ��غ���
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:37
				 */
				typedef csf_function<csf_int32(const csf_connect*, const csf_connect_error&)> 	csf_connect_callback;

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_CALLBACK_H_INCLUDED_)
