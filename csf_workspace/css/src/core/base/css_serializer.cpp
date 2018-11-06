/*******************************************************************************
*
*Copyright: Administrator
*
*Author: Administrator
*
*File name: css_serializer.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:31
*
*Description: Class(css_serializer)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_serializer.hpp"

using css::core::css_serializer;


css_serializer::css_serializer() {

}



css_serializer::~css_serializer() {

}





/**
 * 序列化，表示将本对象转换为gmdu。
 * 返回：非null表示成功；null表示失败。
 * 
 * @param dest    表示目标对象
 * @param src    需要转换的源对象
 * @param gmf    表示目标gmf对象指针
 */
csf_int32 css_serializer::serialize(const gmp_gmdu_t* & dest, const T & src, const gmp_gmf_t& gmf) {

	return 0;
}


/**
 * 反序列化，表示将gmf中描述的内容回去的转换为对象数值。
 * 返回：0表示成功；非0表示失败。
 * 
 * @param dest
 * @param gmf    表示源gmf对象信息
 * @param root    表示对象相对的根目录路径。
 * @param addtion    附加信息，没有任何意义
 */
csf_int32 css_serializer::deserialize(T& dest, const gmp_gmf_t& gmf, const csf_vector<csf_string>& root, csf_bool addtion) {

	return 0;
}


/**
 * 序列化，表示将src对象转换为dest指定的对象。
 * 返回：0表示成功；非0表示错误码。
 * 
 * @param dest    表示目标对象
 * @param src    表示源数据对象
 * @param addtion    表示序列化的附加信息
 */
gmp_gmdu_t* css_serializer::serialize(const T& dest, const T& src, const T& addtion) {

	return  csf_nullptr;
}