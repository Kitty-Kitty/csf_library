/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_database_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:39
*
*Description: Interface(csf_database_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DATABASE_INTERFACE_INCLUDED_)
#define CSF_DATABASE_INTERFACE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示数据库操作接口内容
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6月-2018 17:28:39
				 */
				class csf_database_interface
				{

				public:
					csf_database_interface() {

					}

					virtual ~csf_database_interface() {

					}

				};

			}

		}

	}

}
#endif // !defined(CSF_DATABASE_INTERFACE_INCLUDED_)
