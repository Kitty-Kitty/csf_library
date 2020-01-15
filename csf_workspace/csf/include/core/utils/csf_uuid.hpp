/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_uuid.hpp
*
*Version: 1.0
*
*Date: 30-11月-2019 17:33:24
*
*Description: Class(csf_uuid) 这是一个简单的创建uuid字符串实现
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_UUID_H_INCLUDED_)
#define CSF_UUID_H_INCLUDED_

#include <stdio.h>

namespace csf
{
	namespace core
	{
		namespace utils
		{
			/**
			 * 这是一个简单的创建uuid字符串实现
			 * @author f
			 * @version 1.0
			 * @created 30-11月-2019 17:33:24
			 */
			class csf_uuid
			{

			public:
				csf_uuid();
				virtual ~csf_uuid();

				/**
				 * 功能：创建32位的uuid字符串保存到目标内存位置
				 * 返回：true表示创建成功；false表示创建失败；
				 * 
				 * @param dest    表示创建后的32位uuid保存的位置。该存储空间不能少于32字节。
				 * @param len    表示dest内存长度
				 */
				static bool make32(char* dest, int len);

			};

		}

	}

}
#endif // !defined(CSF_UUID_H_INCLUDED_)
