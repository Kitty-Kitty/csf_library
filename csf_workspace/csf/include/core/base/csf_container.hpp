/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_container.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:01:18
*
*Description: Class(csf_container)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONTAINER_INCLUDED_)
#define CSF_CONTAINER_INCLUDED_

#include "csf_container_interface.hpp"
#include "csf_csftype_template.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示所有非collector类的父类对象
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:01:18
			 */
			class csf_container : public csf::core::base::csf_container_interface
				, public csf::core::base::csf_csftype_template<csf_container>
			{

			public:
				csf_container() {

				}
				virtual ~csf_container() {

				}

				/**
				 * 表示容器是否为空，为空返回true,否则返回false。长度为0或null为空，返回true。
				 */
				inline virtual csf_bool empty() const {

					return csf_true;
				}
				/**
				 * 表示获取容器的实际内容长度，没有内容为0
				 */
				inline virtual csf_uint32 length() const {

					return 0;
				}
				/**
				 * 表示获取容器的空间长度。没有预分配内存的类，则size=length，例如csf_string中length=size。而预分配内存的类，size>=lengt
				 * h，例如csf_buffer中size>=length。
				 */
				inline virtual csf_uint32 size() const {

					return 0;
				}
				/**
				 * 表示清空容器，有些类需要释放空间（例如：csf_chain），有些空间可重用的类则重置数据(例如：csf_buffer)。
				 */
				inline virtual csf_void clear() {

				}
				/**
				* 表示判断是否为空。
				* 返回：true表示为空；false表示不为空。
				*/
				inline virtual csf_bool is_null() const {

					return csf_true;
				}
				/**
				* 表示判断是否不为空。
				* 返回：true表示不为空；false表示为空。
				*/
				inline virtual csf_bool not_null() const {

					return csf_true;
				}
			};

		}

	}

}
#endif // !defined(CSF_CONTAINER_INCLUDED_)
