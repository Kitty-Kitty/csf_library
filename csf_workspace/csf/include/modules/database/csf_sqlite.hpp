/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: fangzhenmu@aliyun.com
*
*Author: fz
*
*Version: 1.0
*
*Date: 28-7月-2018 14:23:47
*
*Description: Class(csf_sqlite) 表示sqlite数据库操作抽象内容
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
			 * @created 28-7月-2018 14:23:47
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
