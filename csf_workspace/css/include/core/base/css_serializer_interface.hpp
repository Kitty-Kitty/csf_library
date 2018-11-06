/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: css_serializer_interface.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:32
*
*Description: Interface(css_serializer_interface) 表示gmf转换操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_SERIALIZER_INTERFACE_H_INCLUDED_)
#define CSS_SERIALIZER_INTERFACE_H_INCLUDED_

namespace css
{
	namespace core
	{
		/**
		 * 表示gmf转换操作接口
		 * @author Administrator
		 * @version 1.0
		 * @created 07-10月-2018 16:50:32
		 */
		class css_serializer_interface
		{

		public:
			css_serializer_interface() {

			}

			virtual ~css_serializer_interface() {

			}

			/**
			 * 反序列化，表示将src对象中描述的内容回去的转换为对象数值。
			 * 返回：0表示成功；非0表示错误码。
			 * 
			 * @param dest
			 * @param src    表示源对象信息
			 * @param root    表示目标对象类型
			 * @param addtion    表示序列化的附加信息
			 */
			virtual csf_int32 deserialize(const T & dest, const T & src, const csf_vector<csf_string>& root, T & addtion) =0;
			/**
			 * 序列化，表示将src对象转换为dest指定的对象。
			 * 返回：0表示成功；非0表示错误码。
			 * 
			 * @param dest    表示目标对象
			 * @param src    表示源数据对象
			 * @param addtion    表示序列化的附加信息
			 */
			virtual gmp_gmdu_t* serialize(const T& dest, const T& src, const T& addtion) =0;

		};

	}

}
#endif // !defined(CSS_SERIALIZER_INTERFACE_H_INCLUDED_)
