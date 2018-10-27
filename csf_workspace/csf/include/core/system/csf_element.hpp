/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_element.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 30-6��-2018 8:49:47
*
*Description: Class(csf_element)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ELEMENT_INCLUDED_)
#define CSF_ELEMENT_INCLUDED_


#include <list>
#include <map>
#include "csf_typedef.h"
#include "csf_default.h"
#include "csf_stddef.h"
#include "csf_null.hpp"
#include "csf_csftype_template.hpp"


using namespace csf::core;
using namespace csf::core::base;


namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * ��ʾ���ݶ�������
			 * @author fz
			 * @version 1.0
			 * @created 30-6��-2018 8:49:47
			 */
			class csf_element : public csf::core::base::csf_csftype_template<csf_element>
			{

			public:
				csf_element() 
					: m_name("")
					, m_content("") {

				}
				virtual ~csf_element() {

				}

				/**
				 * ��ʾ���ݶ���ڵ�����
				 */
				inline const csf_string& get_name() const {

					return m_name;
				}
				/**
				 * ���һ��Ԫ�ض���
				 * 
				 * @param element    ��ʾ��Ҫ����ӵ�Ԫ��
				 */
				inline virtual csf_int32 add(const csf_element& element) {

					const_cast<csf_list<csf_element>&>(get_children()).push_back(element);
					return csf_success;
				}
				/**
				 * ��ʾ���ݶ���ڵ���������
				 */
				inline const csf_string& get_content() const {

					return m_content;
				}
				/**
				 * ��ʾ���һ�����ӽ��,��child��ӵ�parent�С�
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				 * 
				 * @param parent    ��ʾ�����
				 * @param child    ��ʾ�ӽ��
				 */
				inline virtual csf_int32 add(csf_element& parent, const csf_element& child) {

					return parent.add(child);
				}
				/**
				 * ��ʾ���һ���ӽ�㣬��ӵ�ָ��parent�С�
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				 * 
				 * @param parent    ��ʾ�����
				 * @param child    ��ʾ�ӽ��
				 */
				inline virtual csf_int32 add(const csf_string& parent, const csf_element& child) {

					csf_element						&tmp_element = const_cast<csf_element&>(get_null());

					tmp_element = find_element(parent);
					if (tmp_element.not_null()) {
						return tmp_element.add(child);
					}

					return csf_failure;
				}
				/**
				 * ��ʾ���һ���ӽ�㣬��ӵ�ָ��parent�С�
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				 * 
				 * @param parent    ��ʾ�����
				 * @param child    ��ʾ�ӽ��
				 */
				inline virtual csf_int32 add(const csf_char* parent, const csf_element& child) {

					if (!parent || csf_strlen(parent) <= 0) {
						return csf_failure;
					}

					return add(csf_string(parent), child);
				}
				/**
				 * ��ʾ���һ����������
				 * 
				 * @param name    ��ʾ��Ҫ��ӵ���������
				 * @param val    ��ʾ��Ҫ��ӵ���������
				 */
				inline virtual csf_int32 add(const csf_string& name, const csf_string& val) {

					if (name.empty()) {
						return csf_failure;
					}

					return add(name.c_str(), val.c_str());
				}
				/**
				 * ��ʾ���һ����������
				 * 
				 * @param name    ��ʾ��Ҫ��ӵ���������
				 * @param val    ��ʾ��Ҫ��ӵ���������
				 */
				inline virtual csf_int32 add(const csf_char* name, const csf_char* val) {

					if (!name || !val || csf_strlen(name) <= 0) {
						return csf_failure;
					}

					const_cast<csf_map<csf_string, csf_string>&>(get_attributes()).insert(csf_map<csf_string, csf_string>::value_type(name, val));
					//m_attributes[name] = val;
					return csf_success;
				}
				/**
				 * ��ʾ�������
				 */
				inline virtual csf_void clear() {

					*this = get_null();
				}
				/**
				 * ��ʾ����һ��������ֵ
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ���������
				 */
				inline virtual const csf_string& find(const csf_string& name) const {

					if (name.empty()) {
						return  csf_string_null;
					}

					return  find(name.c_str());
				}
				/**
				 * ��ʾ����һ��������ֵ
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ���������
				 */
				inline virtual const csf_string& find(const csf_char* name) const {

					csf_map<csf_string, csf_string>::iterator			tmp_iter;

					if (!name || csf_strlen(name) <= 0) {
						return csf_string_null;
					}

					tmp_iter = const_cast<csf_map<csf_string, csf_string>&>(get_attributes()).find(name);
					if (tmp_iter != const_cast<csf_map<csf_string, csf_string>&>(get_attributes()).end()) {
						return tmp_iter->second;
					}

					return  csf_string_null;
				}
				/**
				 * ��ʾ����һ����element
				 * ���أ���null��ʾ�ɹ���null��ʾʧ�ܡ�
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ�element����
				 */
				inline virtual const csf_element& find_child(const csf_string& name) const {

					//����Ϊ���򷵻ؿ�
					if (name.empty()) {
						return get_null();
					}

					//�жϵ�ǰģ���Ƿ������Ҫ���ҵ�����
					if (get_name() == name) {
						return *this;
					}

					//������ģ���б�
					for (csf_element &tmp_iter : const_cast<csf_list<csf_element>&>(get_children())) {
						if (tmp_iter.get_name() == name) {
							return tmp_iter;
						}
					}
					return get_null();
				}
				/**
				 * ��ʾ����һ����element
				 * ���أ���null��ʾ�ɹ���null��ʾʧ�ܡ�
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ�element����
				 */
				inline virtual const csf_element& find_child(const csf_char* name) const {

					if (!name || csf_strlen(name) <= 0) {
						return get_null();
					}

					return find_child(csf_string(name));
				}
				/**
				* ��ʾ����һ��element
				* ���أ���null��ʾ�ɹ���null��ʾʧ�ܡ�
				*
				* @param name    ��ʾ��Ҫ���ҵ�element����
				*/
				virtual const csf_element& find_element(const csf_string& name) const;
#if 0
				/**
				 * ��ʾ����һ��element
				 * ���أ���null��ʾ�ɹ���null��ʾʧ�ܡ�
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ�element����
				 */
				inline virtual const csf_element& find_element(const csf_string& name) {

					csf_element						&tmp_element = (csf_element&)m_null;

					//��ʾ�Ȳ�ѯ�ӽ��
					tmp_element = find_child(name);
					if (tmp_element.not_null()) {
						return tmp_element;
					}

					//����ģ���б鲼�����Ӷ���
					for (csf_element &tmp_iter : get_children()) {
						tmp_element = tmp_iter.find_element(name);
						if (tmp_element.not_null()) {
							return tmp_element;
						}
					}
					return get_null();
				}
#endif
				/**
				 * ��ʾ����һ��element
				 * ���أ���null��ʾ�ɹ���null��ʾʧ�ܡ�
				 * 
				 * @param name    ��ʾ��Ҫ���ҵ�element����
				 */
				inline virtual const csf_element& find_element(const csf_char* name) const {

					if (!name) {
						return get_null();
					}
					return  find_element(csf_string(name));
				}
				/**
				* ��ʾ����items����·������һ��element��
				* ���أ���null��ʾ����items����·���Ľڵ㣻null��ʾû�в��ҵ�����·���Ľڵ㣻
				*
				* @param items    items����·��
				*/
				virtual const csf_element& find_element(const csf_list<csf_string>& items) const;
				/**
				 * ��ʾ���ݶ���ڵ���������
				 * 
				 * @param new_value
				 */
				inline csf_void set_content(csf_string& new_value) {

					m_content = new_value;
				}
				/**
				 * ��ʾ���ݶ���ڵ�����
				 * 
				 * @param new_value
				 */
				inline csf_void set_name(const csf_char* new_value) {

					m_name = new_value;
				}
				/**
				 * ��ʾ���ݶ���ڵ�����
				 * 
				 * @param new_value
				 */
				inline csf_void set_name(const csf_string& new_value) {

					m_name = new_value;
				}
				/**
				 * ��ʾ���ݶ���ڵ���������
				 * 
				 * @param new_value
				 */
				inline csf_void set_content(csf_char* new_value) {

					m_content = new_value;
				}
				/**
				* ��ʾ�ӽڵ��б�
				*/
				inline const csf_list<csf_element>& get_children() const {

					return m_children;
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				*/
				inline csf_bool is_null() const {

					if (get_name().empty()
						&& get_content().empty()
						&& get_children().empty()
						&& get_attributes().empty()) {
						return csf_true;
					}

					return csf_false;
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				*/
				inline csf_bool not_null() const {

					return !is_null();
				}

			private:
				/**
				 * ��ʾ���ݶ���ڵ�����
				 */
				csf_string m_name = "";
				/**
				 * ��ʾ���ݶ���ڵ���������
				 */
				csf_string m_content = "";
				/**
				 * ��ʾ�ӽڵ��б�
				 */
				csf_list<csf_element> m_children;
				/**
				 * ��ʾ������Ϣ����
				 */
				csf_map<csf_string, csf_string> m_attributes;

				/**
				 * ��ʾ������Ϣ����
				 */
				inline const csf_map<csf_string, csf_string>& get_attributes() const {

					return m_attributes;
				}
				/**
				 * ��ʾ������Ϣ����
				 * 
				 * @param new_value
				 */
				inline csf_void set_attributes(csf_map<csf_string, csf_string>& new_value) {

					m_attributes = new_value;
				}
				/**
				 * ��ʾ�ӽڵ��б�
				 * 
				 * @param new_value
				 */
				inline csf_void set_children(const csf_list<csf_element>& new_value) {

					m_children = new_value;
				}
			};

		}

	}

}
#endif // !defined(CSF_ELEMENT_INCLUDED_)
