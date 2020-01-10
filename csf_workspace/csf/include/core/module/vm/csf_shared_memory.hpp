/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_shared_memory.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:42
*
*Description: Class(csf_shared_memory) 实现共享内存的管理操作。在csf框架中，共享内存除了共享数据外，还用于运行时判断。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_SHARED_MEMORY_H_INCLUDED_)
#define CSF_SHARED_MEMORY_H_INCLUDED_

#include <boost/interprocess/managed_shared_memory.hpp>
#include "csf_typedef.h"

using namespace csf::core::base;
using namespace boost::interprocess;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 实现共享内存的管理操作。在csf框架中，共享内存除了共享数据外，还用于运行时判断。
			 * @author f
			 * @version 1.0
			 * @created 10-1月-2020 14:50:42
			 */
			class csf_shared_memory
			{

			public:
				csf_shared_memory();
				virtual ~csf_shared_memory();

				/**
				 * 功能：
				 *    为对象创建一个指定名称和长度的共享内存
				 * 返回：
				 *    0  ：  表示成功；
				 *   非0 ：  表示失败；
				 * 
				 * @param name    表示共享内存的名称
				 * @param size    表示共享内存的空间大小
				 */
				csf_int32 create(csf_string name, csf_uint32 size);
				/**
				 * 功能：
				 *    销毁共享对象中已经创建好的共享内存
				 * 返回：
				 *    无
				 */
				void destroy();

			private:
				/**
				 * 表示共享内存对象指针
				 */
				managed_shared_memory* m_smm = csf_nullptr;

				/**
				 * 表示共享内存对象指针
				 */
				inline managed_shared_memory* get_smm() {

					return m_smm;
				}
				/**
				 * 表示共享内存对象指针
				 * 
				 * @param newVal
				 */
				inline void set_smm(managed_shared_memory* newVal) {

					m_smm = newVal;
				}

			};

		}

	}

}
#endif // !defined(CSF_SHARED_MEMORY_H_INCLUDED_)
