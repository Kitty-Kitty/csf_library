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
*Date: 07-10��-2018 16:50:32
*
*Description: Interface(css_serializer_interface) ��ʾgmfת�������ӿ�
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
		 * ��ʾgmfת�������ӿ�
		 * @author Administrator
		 * @version 1.0
		 * @created 07-10��-2018 16:50:32
		 */
		class css_serializer_interface
		{

		public:
			css_serializer_interface() {

			}

			virtual ~css_serializer_interface() {

			}

			/**
			 * �����л�����ʾ��src���������������ݻ�ȥ��ת��Ϊ������ֵ��
			 * ���أ�0��ʾ�ɹ�����0��ʾ�����롣
			 * 
			 * @param dest
			 * @param src    ��ʾԴ������Ϣ
			 * @param root    ��ʾĿ���������
			 * @param addtion    ��ʾ���л��ĸ�����Ϣ
			 */
			virtual csf_int32 deserialize(const T & dest, const T & src, const csf_vector<csf_string>& root, T & addtion) =0;
			/**
			 * ���л�����ʾ��src����ת��Ϊdestָ���Ķ���
			 * ���أ�0��ʾ�ɹ�����0��ʾ�����롣
			 * 
			 * @param dest    ��ʾĿ�����
			 * @param src    ��ʾԴ���ݶ���
			 * @param addtion    ��ʾ���л��ĸ�����Ϣ
			 */
			virtual gmp_gmdu_t* serialize(const T& dest, const T& src, const T& addtion) =0;

		};

	}

}
#endif // !defined(CSS_SERIALIZER_INTERFACE_H_INCLUDED_)
