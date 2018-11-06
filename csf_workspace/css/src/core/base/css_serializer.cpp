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
*Date: 07-10��-2018 16:50:31
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
 * ���л�����ʾ��������ת��Ϊgmdu��
 * ���أ���null��ʾ�ɹ���null��ʾʧ�ܡ�
 * 
 * @param dest    ��ʾĿ�����
 * @param src    ��Ҫת����Դ����
 * @param gmf    ��ʾĿ��gmf����ָ��
 */
csf_int32 css_serializer::serialize(const gmp_gmdu_t* & dest, const T & src, const gmp_gmf_t& gmf) {

	return 0;
}


/**
 * �����л�����ʾ��gmf�����������ݻ�ȥ��ת��Ϊ������ֵ��
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
 * 
 * @param dest
 * @param gmf    ��ʾԴgmf������Ϣ
 * @param root    ��ʾ������Եĸ�Ŀ¼·����
 * @param addtion    ������Ϣ��û���κ�����
 */
csf_int32 css_serializer::deserialize(T& dest, const gmp_gmf_t& gmf, const csf_vector<csf_string>& root, csf_bool addtion) {

	return 0;
}


/**
 * ���л�����ʾ��src����ת��Ϊdestָ���Ķ���
 * ���أ�0��ʾ�ɹ�����0��ʾ�����롣
 * 
 * @param dest    ��ʾĿ�����
 * @param src    ��ʾԴ���ݶ���
 * @param addtion    ��ʾ���л��ĸ�����Ϣ
 */
gmp_gmdu_t* css_serializer::serialize(const T& dest, const T& src, const T& addtion) {

	return  csf_nullptr;
}