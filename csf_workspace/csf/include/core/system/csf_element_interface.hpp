/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_element_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:41
*
*Description: Interface(csf_element_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ELEMENT_INTERFACE_INCLUDED_)
#define CSF_ELEMENT_INTERFACE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * ��ʾcsf_element�������ݲ����ӿ�
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:28:41
			 */
			class csf_element_interface
			{

			public:
				csf_element_interface() {

				}

				virtual ~csf_element_interface() {

				}

				/**
				 * ���һ��Ԫ�ض���
				 * 
				 * @param element    ��ʾ��Ҫ����ӵ�Ԫ��
				 */
				virtual csf_int32 add(const csf_element& element) =0;
				/**
				 * ��ʾ���һ�����ӽ��
				 * 
				 * @param parent    ��ʾ�����
				 * @param child    ��ʾ�ӽ��
				 */
				virtual csf_int32 add(const csf_element& parent, const csf_element& child) =0;
				/**
				 * ��ʾ���һ�����ӽ��
				 * 
				 * @param parent    ��ʾ�����
				 * @param child    ��ʾ�ӽ��
				 */
				virtual csf_int32 add(const csf_string& parent, const csf_element& child) =0;
				/**
				 * ��ʾ���һ�����ӽ��
				 * 
				 * @param parent    ��ʾ�����
				 * @param child    ��ʾ�ӽ��
				 */
				virtual csf_int32 add(const csf_char* parent, const csf_element& child) =0;
				/**
				 * ��ʾ���һ����������
				 * 
				 * @param name    ��ʾ��Ҫ��ӵ���������
				 * @param val    ��ʾ��Ҫ��ӵ���������
				 */
				virtual csf_int32 add(const csf_string& name, const csf_string& val) =0;
				/**
				 * ��ʾ���һ����������
				 * 
				 * @param name    ��ʾ��Ҫ��ӵ���������
				 * @param val    ��ʾ��Ҫ��ӵ���������
				 */
				virtual csf_int32 add(const csf_char* name, const csf_char* val) =0;
				/**
				 * ��ʾ�������
				 */
				virtual csf_void clear() =0;
				/**
				 * ��ʾ����һ��������ֵ
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ���������
				 */
				virtual csf_string& find(const csf_string& name) =0;
				/**
				 * ��ʾ����һ��������ֵ
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ���������
				 */
				virtual csf_string& find(const csf_char* name) =0;
				/**
				 * ��ʾ����һ����element��
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ�element����
				 */
				virtual const csf_element& find_child(const csf_string& name) =0;
				/**
				 * ��ʾ����һ����element��
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ�element����
				 */
				virtual const csf_element& find_child(const csf_char* name) =0;
				/**
				 * ��ʾ����һ��element��
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ�element����
				 */
				virtual const csf_element& find_element(const csf_string& name) =0;
				/**
				 * ��ʾ����һ��element��
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ�element����
				 */
				virtual const csf_element& find_element(const csf_char* name) =0;
				/**
				* ��ʾ����items����·������һ��element��
				* ���أ���null��ʾ����items����·���Ľڵ㣻null��ʾû�в��ҵ�����·���Ľڵ㣻
				*
				* @param items    items����·��
				*/
				virtual const csf_element& find_element(const csf_list<csf_string>& items) = 0;
			};

		}

	}

}
#endif // !defined(CSF_ELEMENT_INTERFACE_INCLUDED_)
