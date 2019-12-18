/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_database_request.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:39
*
*Description: Class(csf_database_request)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DATABASE_REQUEST_INCLUDED_)
#define CSF_DATABASE_REQUEST_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示数据库请求信息
				 * @author fz
				 * @version 1.0
				 * @created 27-6月-2018 17:28:39
				 */
				class csf_database_request
				{

				public:
					csf_database_request();
					virtual ~csf_database_request();

				};

			}

		}

	}

}
#endif // !defined(CSF_DATABASE_REQUEST_INCLUDED_)
