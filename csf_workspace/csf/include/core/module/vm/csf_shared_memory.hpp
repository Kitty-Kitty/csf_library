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
#include "csf_default.h"

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
				/**
				 * 功能：
				 *    在共享内存中创建一个指定类型对象
				 * 返回：
				 *    对象指针
				 *
				 * @param name    表示共享内存对象的名称
				 */
				template <typename TypeName>
				TypeName* create_object(csf_string name) {
					return create_object(name, 1);
				}
				/**
				 * 功能：
				 *    在共享内存中创建指定类型对象
				 * 返回：
				 *    对象指针
				 *
				 * @param name    表示共享内存对象的名称
				 * @param number    表示共享内存对象的个数
				 */
				template <typename TypeName>
				TypeName* create_object(csf_string name, csf_uint32 number) {

					TypeName	*tmp_objects = csf_nullptr;

					if (get_smm()) {
						tmp_objects = get_smm()->construct<TypeName>
							(name.c_str())		//name of the object
							[number]			//number of elements
							();					//same arguments for all objects
					}

					return tmp_objects;
				}
				/**
				 * 功能：
				 *    销毁共享内存中对象
				 * 返回：
				 *    无
				 *
				 * @param name
				 */
				template <typename TypeName>
				csf_void destroy_object(csf_string name) {
					if (get_smm()) {
						get_smm()->destroy<TypeName>(name);
					}
				}
				/**
				 * 表示当前共享内存的名称
				 */
				inline csf_string get_name() {

					return m_name;
				}
			protected:
				/**
				 * 表示当前共享内存的名称
				 *
				 * @param newVal
				 */
				inline void set_name(csf_string newVal) {

					m_name = newVal;
				}
			private:
				/**
				 * 表示共享内存对象指针
				 */
				managed_shared_memory* m_smm = csf_nullptr;
				/**
				 * 表示当前共享内存的名称
				 */
				csf_string m_name = "";
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
