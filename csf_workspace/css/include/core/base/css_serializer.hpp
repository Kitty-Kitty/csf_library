/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: css_serializer.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:31
*
*Description: Class(css_serializer) 表示转换处理，采用模板特化方式实现。这样处理主要为了实现其他数据交换格式的快速兼容处理。如：json、xml、gmf等等。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_SERIALIZER_H_INCLUDED_)
#define CSS_SERIALIZER_H_INCLUDED_

#include "css_serializer_interface.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示转换处理，采用模板特化方式实现。这样处理主要为了实现其他数据交换格式的快速兼容处理。如：json、xml、gmf等等。
		 * @author Administrator
		 * @version 1.0
		 * @created 07-10月-2018 16:50:31
		 */
		class css_serializer : public css::core::css_serializer_interface
		{

		public:
			css_serializer();
			virtual ~css_serializer();

			/**
			 * 序列化，表示将本对象转换为gmdu。
			 * 返回：非null表示成功；null表示失败。
			 * 
			 * @param dest    表示目标对象
			 * @param src    需要转换的源对象
			 * @param gmf    表示目标gmf对象指针
			 */
			virtual csf_int32 serialize(const gmp_gmdu_t* & dest, const T & src, const gmp_gmf_t& gmf);
			/**
			 * 反序列化，表示将gmf中描述的内容回去的转换为对象数值。
			 * 返回：0表示成功；非0表示失败。
			 * 
			 * @param dest
			 * @param gmf    表示源gmf对象信息
			 * @param root    表示对象相对的根目录路径。
			 * @param addtion    附加信息，没有任何意义
			 */
			virtual csf_int32 deserialize(T& dest, const gmp_gmf_t& gmf, const csf_vector<csf_string>& root, csf_bool addtion = csf_true);
			/**
			 * 序列化，表示将src对象转换为dest指定的对象。
			 * 返回：0表示成功；非0表示错误码。
			 * 
			 * @param dest    表示目标对象
			 * @param src    表示源数据对象
			 * @param addtion    表示序列化的附加信息
			 */
			virtual gmp_gmdu_t* serialize(const T& dest, const T& src, const T& addtion);

		};

	}

}
#endif // !defined(CSS_SERIALIZER_H_INCLUDED_)
