/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 19-7月-2018 20:11:41
*
*Description: Class(csf_lock) 描述互斥锁信息
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_LOCK_INCLUDED_)
#define CSF_LOCK_INCLUDED_

#include <mutex>
#include "csf_shared_mutex.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace thread
			{
				#define	csf_shared_lock									std::shared_lock
				#define csf_lock_guard									std::lock_guard
				#define csf_unqiue_lock									std::unique_lock
				typedef	csf_shared_lock<csf_shared_mutex>				csf_read_lock;
				typedef	csf_unqiue_lock<csf_shared_mutex>				csf_write_lock;
				/**	
				 * 描述互斥锁信息
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:41
				 */
				class csf_lock
				{

				public:
					csf_lock();
					virtual ~csf_lock();

				};

			}

		}

	}

}
#endif // !defined(CSF_LOCK_INCLUDED_)
