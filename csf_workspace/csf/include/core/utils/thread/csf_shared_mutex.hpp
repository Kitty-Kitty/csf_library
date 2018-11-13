/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: fz
*
*Author: fz
*
*Version: 1.0
*
*Date: 19-7月-2018 20:11:49
*
*Description: Class(csf_shared_mutex) 表示共享互斥锁内容
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_SHARED_MUTEX_INCLUDED_)
#define CSF_SHARED_MUTEX_INCLUDED_

//#include <shared_mutex>		//c++17
#include "boost/thread/shared_mutex.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace thread
			{
				//typedef	std::shared_mutex				csf_shared_mutex;		//C++17
				typedef		boost::shared_mutex				csf_shared_mutex;
				/**
				 * 表示共享互斥锁内容
				 * @author fz
				 * @version 1.0
				 * @created 19-7月-2018 20:11:49
				 */
#if 0
				class csf_shared_mutex
				{

				public:
					csf_shared_mutex();
					virtual ~csf_shared_mutex();

				};
#endif

			}

		}

	}

}
#endif // !defined(CSF_SHARED_MUTEX_INCLUDED_)
