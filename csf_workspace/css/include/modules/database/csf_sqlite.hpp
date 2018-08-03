/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_sqlite.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:49
*
*Description: Class(csf_sqlite)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_SQLITE_INCLUDED_)
#define CSF_SQLITE_INCLUDED_

#include "csf_database.hpp"

namespace csf
{
	namespace modules
	{
		namespace database
		{
			/**
			 * 表示sqlite数据库操作抽象内容
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 27-6月-2018 17:28:49
			 */
			class csf_sqlite : public csf::core::module::device::csf_database
			{

			public:
				csf_sqlite();
				virtual ~csf_sqlite();

				cf_int32 init();
				cf_int32 start();
				cf_int32 stop();

			};

		}

	}

}
#endif // !defined(CSF_SQLITE_INCLUDED_)
