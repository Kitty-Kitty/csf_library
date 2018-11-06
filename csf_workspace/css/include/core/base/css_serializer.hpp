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
*Date: 07-10��-2018 16:50:31
*
*Description: Class(css_serializer) ��ʾת����������ģ���ػ���ʽʵ�֡�����������ҪΪ��ʵ���������ݽ�����ʽ�Ŀ��ټ��ݴ����磺json��xml��gmf�ȵȡ�
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
		 * ��ʾת����������ģ���ػ���ʽʵ�֡�����������ҪΪ��ʵ���������ݽ�����ʽ�Ŀ��ټ��ݴ����磺json��xml��gmf�ȵȡ�
		 * @author Administrator
		 * @version 1.0
		 * @created 07-10��-2018 16:50:31
		 */
		class css_serializer : public css::core::css_serializer_interface
		{

		public:
			css_serializer();
			virtual ~css_serializer();

			/**
			 * ���л�����ʾ��������ת��Ϊgmdu��
			 * ���أ���null��ʾ�ɹ���null��ʾʧ�ܡ�
			 * 
			 * @param dest    ��ʾĿ�����
			 * @param src    ��Ҫת����Դ����
			 * @param gmf    ��ʾĿ��gmf����ָ��
			 */
			virtual csf_int32 serialize(const gmp_gmdu_t* & dest, const T & src, const gmp_gmf_t& gmf);
			/**
			 * �����л�����ʾ��gmf�����������ݻ�ȥ��ת��Ϊ������ֵ��
			 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
			 * 
			 * @param dest
			 * @param gmf    ��ʾԴgmf������Ϣ
			 * @param root    ��ʾ������Եĸ�Ŀ¼·����
			 * @param addtion    ������Ϣ��û���κ�����
			 */
			virtual csf_int32 deserialize(T& dest, const gmp_gmf_t& gmf, const csf_vector<csf_string>& root, csf_bool addtion = csf_true);
			/**
			 * ���л�����ʾ��src����ת��Ϊdestָ���Ķ���
			 * ���أ�0��ʾ�ɹ�����0��ʾ�����롣
			 * 
			 * @param dest    ��ʾĿ�����
			 * @param src    ��ʾԴ���ݶ���
			 * @param addtion    ��ʾ���л��ĸ�����Ϣ
			 */
			virtual gmp_gmdu_t* serialize(const T& dest, const T& src, const T& addtion);

		};

	}

}
#endif // !defined(CSS_SERIALIZER_H_INCLUDED_)
