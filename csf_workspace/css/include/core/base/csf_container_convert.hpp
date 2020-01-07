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
*Date: 14-7��-2018 10:30:55
*
*Description: Class(csf_container_convert) ��ʾ������ת������ģ�飬��Ҫʵ���������ַ����ȹ��ܡ�
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
			 * ��ʾ������ת������ģ�飬��Ҫʵ���������ַ����ȹ��ܡ�
			 * @author f
			 * @version 1.0
			 * @created 14-7��-2018 10:30:55
			 */
			template<typename ContainerType>
			class csf_container_convert
			{

			public:
				/**
				* ��ʾ��Ŀ����������
				*
				* @param container    ��ʾĿ����������
				*/
				inline explicit csf_container_convert(const ContainerType& container)
					: m_container((ContainerType&)container) {

				}

				virtual ~csf_container_convert() {

				}

				/**
				 * �ú�����Ҫʵ�ֽ���������ת��Ϊ�ַ������ݡ�
				 */
				csf_string to_string() {

					csf_int						i = 0;
					csf_int						tmp_size = get_container().size();
					csf_string					tmp_ret_string = csf_string_null;


					for (auto &tmp_item : get_container()) {

						//��ʾת�����ַ�����ʼ���
						if (!i) {
							tmp_ret_string += "{ ";
						}

						//��ʾ�����������ֵ
						tmp_ret_string += "\"";
						tmp_ret_string += tmp_item;
						tmp_ret_string += "\"";

						//��ʾת�����ַ��Ľ������
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
				 * ��ʾת������Ҫ�����Ŀ�����
				 */
				inline ContainerType& get_container() {

					return m_container;
				}
				

			private:
				/**
				 * ��ʾת������Ҫ�����Ŀ�����
				 */
				ContainerType& m_container;

				/**
				 * ��ʾת������Ҫ�����Ŀ�����
				 * 
				 * @param newVal    ��ʾĿ����������
				 */
				inline void set_container(const ContainerType& newVal) {

					m_container = (ContainerType&)newVal;
				}

			};

		}

	}

}
#endif // !defined(CSF_CONTAINER_CONVERT_INCLUDED_)
