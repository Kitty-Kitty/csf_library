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
*Date: 14-7月-2018 10:30:55
*
*Description: Class(csf_container_convert) 表示容器的转换处理模块，主要实现容器化字符串等功能。
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONTAINER_CONVERT_INCLUDED_)
#define CSF_CONTAINER_CONVERT_INCLUDED_

#include "csf_null.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示容器的转换处理模块，主要实现容器化字符串等功能。
			 * @author f
			 * @version 1.0
			 * @created 14-7月-2018 10:30:55
			 */
			template<typename ContainerType>
			class csf_container_convert
			{

			public:
				/**
				* 表示根目标容器对象
				*
				* @param container    表示目标容器对象
				*/
				inline explicit csf_container_convert(const ContainerType& container)
					: m_container((ContainerType&)container) {

				}

				virtual ~csf_container_convert() {

				}

				/**
				 * 该函数主要实现将容器对象转换为字符串内容。
				 */
				csf_string to_string() {

					csf_int						i = 0;
					csf_int						tmp_size = get_container().size();
					csf_string					tmp_ret_string = csf_string_null;


					for (auto &tmp_item : get_container()) {

						//表示转换成字符的起始标记
						if (!i) {
							tmp_ret_string += "{ ";
						}

						//表示容器保存的数值
						tmp_ret_string += "\"";
						tmp_ret_string += tmp_item;
						tmp_ret_string += "\"";

						//表示转换成字符的结束标记
						if (i == (tmp_size - 1)) {
							tmp_ret_string += " }";
						}
						else {
							tmp_ret_string += ", ";
						}

						++i;
					}

					return tmp_ret_string;
				}
				/**
				 * 表示转换器需要处理的目标对象。
				 */
				inline ContainerType& get_container() {

					return m_container;
				}
				

			private:
				/**
				 * 表示转换器需要处理的目标对象。
				 */
				ContainerType& m_container;

				/**
				 * 表示转换器需要处理的目标对象。
				 * 
				 * @param newVal    表示目标容器对象
				 */
				inline void set_container(const ContainerType& newVal) {

					m_container = (ContainerType&)newVal;
				}

			};

		}

	}

}
#endif // !defined(CSF_CONTAINER_CONVERT_INCLUDED_)
