/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_exception.hpp
*
*Version: 1.0
*
*Date: 28-2月-2019 17:17:26
*
*Description: Class(csf_exception) 表示csf平台的异常信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_EXCEPTION_H_INCLUDED_)
#define CSF_EXCEPTION_H_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf平台的异常信息
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 28-2月-2019 17:17:26
			 */
			class csf_exception
			{

			public:
				csf_exception();
				virtual ~csf_exception();

			};

		}

	}

}
#endif // !defined(CSF_EXCEPTION_H_INCLUDED_)
