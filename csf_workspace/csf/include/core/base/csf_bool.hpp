/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_bool.hpp
*
*Author: Administrator
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:35
*
*Description: Enumeration(csf_bool)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_BOOL_INCLUDED_)
#define CSF_BOOL_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾ������������
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:28:35
			 */
			enum csf_bool
			{
				/**
				 * ��ʾ��
				 */
				m_csf_false = 0x00,
				/**
				 * ��ʾ��
				 */
				m_csf_true = 0x01
			};

		}

	}

}
#endif // !defined(CSF_BOOL_INCLUDED_)
