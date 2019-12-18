/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: Administrator
*
*Author: fz
*
*Version: 1.0
*
*Date: 19-7��-2018 20:11:46
*
*Description: Class(csf_mutex) ��ʾ������
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MUTEX_INCLUDED_)
#define CSF_MUTEX_INCLUDED_

#include <mutex>
#include "csf_lock.hpp"


using namespace csf::core::utils::thread;


namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace thread
			{
				/**
				 * ��ʾ������
				 * @author Administrator
				 * @version 1.0
				 * @created 19-7��-2018 20:11:46
				 */
				class csf_mutex
				{

				public:
					csf_mutex();
					virtual ~csf_mutex();

				};

			}

		}

	}

}
#endif // !defined(CSF_MUTEX_INCLUDED_)