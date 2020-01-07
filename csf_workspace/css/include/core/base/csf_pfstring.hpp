/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_pfstring.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:50:22
*
*Description: Class(csf_pfstring)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_PFSTRING_INCLUDED_)
#define CSF_PFSTRING_INCLUDED_

#include "csf_memblock.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾָ���ʶ�ַ����ͣ������Ͳ�����ʵ�����ݡ�����һ�������ַ�����ʼ��ָ����ַ����ĳ�������������ɡ�
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:50:22
			 */
			class csf_pfstring : public csf::core::base::csf_memblock
			{

			public:
				csf_pfstring() {

				}
				virtual ~csf_pfstring() {

				}

				/**
				 * ���ݻ����ַ�ͳ��ȴ�������
				 * 
				 * @param buf    ��ʾ���ݻ����ַ�ͳ��ȴ���һ��csf_csfstring
				 * @param len    len
				 */
				inline explicit csf_pfstring(const csf_uchar* buf, const csf_int32 len)
					: csf_memblock(buf, len) {

				}

			};

		}

	}

}
#endif // !defined(CSF_PFSTRING_INCLUDED_)
