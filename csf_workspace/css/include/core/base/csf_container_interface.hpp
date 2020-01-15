/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_container_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 16:45:40
*
*Description: Interface(csf_container_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONTAINER_INTERFACE_INCLUDED_)
#define CSF_CONTAINER_INTERFACE_INCLUDED_

#include "csf_typedef.h"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示所有非collector类的父类对象的操作接口
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 16:45:40
			 */
			class csf_container_interface
			{

			public:
				csf_container_interface() {

				}

				virtual ~csf_container_interface() {

				}

				/**
				 * 表示容器是否为空，为空返回true,否则返回false。长度为0或null为空，返回true。
				 */
				virtual csf_bool empty() =0;
				/**
				 * 表示获取容器的实际内容长度，没有内容为0
				 */
				virtual csf_uint32 length() =0;
				/**
				 * 表示获取容器的空间长度。没有预分配内存的类，则size=length，例如csf_string中length=size。而预分配内存的类，size>=lengt
				 * h，例如csf_buffer中size>=length。
				 */
				virtual csf_uint32 size() =0;
				/**
				 * 表示清空容器，有些类需要释放空间（例如：csf_chain），有些空间可重用的类则重置数据(例如：csf_buffer)。
				 */
				virtual csf_void clear() =0;

			};

		}

	}

}
#endif // !defined(CSF_CONTAINER_INTERFACE_INCLUDED_)
