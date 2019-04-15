/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 06-7��-2018 19:29:31
*
*Description: Class(csf_attribute_manager) ��ʾģ������Թ���������Ҫ�ṩģ����������ͳһ������������ɾ���顢�ĵȡ�
* ��ʾģ������Թ���������Ҫ�ṩģ����������ͳһ������������ɾ���顢�ĵȡ�
* ��ģ����ҪΪ����������Ĺ�����������������Ϣ�������������ù�����(m_configure_manager*)�������Զ���(m_root_element*)����
* ·����Ϣ(m_root_items)��
* ��������Ϊ��
*   1����������·�������m_root_items��ָ����·��;
*   2��root_element���ȼ�����configure_manager;�������m_root_element*���root_element*�в�������ֵ;
*   3�����������root_element*���configure_manager*�в�������ֵ;
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_MANAGER_INCLUDED_)
#define CSF_ATTRIBUTE_MANAGER_INCLUDED_

#include "csf_attribute_manager_interface.hpp"
#include "csf_manager.hpp"
#include "csf_attribute_bool.hpp"
#include "csf_attribute_string.hpp"
#include "csf_attribute_int.hpp"
#include "csf_attribute_space_size.hpp"
#include "csf_attribute_time.hpp"
#include "csf_logger.hpp"


namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				* ��ʾģ������Թ���������Ҫ�ṩģ����������ͳһ������������ɾ���顢�ĵȡ�
				* ��ģ����ҪΪ����������Ĺ�����������������Ϣ�������������ù�����(m_configure_manager*)�������Զ���(m_root_element*)����
				* ·����Ϣ(m_root_items)��
				* ��������Ϊ��
				*   1����������·�������m_root_items��ָ����·��;
				*   2��root_element���ȼ�����configure_manager;�������m_root_element*���root_element*�в�������ֵ;
				*   3�����������root_element*���configure_manager*�в�������ֵ;
				* @author fz
				* @version 1.0
				* @updated 03-10��-2018 15:04:13
				*/
				class csf_attribute_manager : public csf::core::module::csf_manager
					, public csf::core::system::attribute::csf_attribute_manager_interface
				{

				public:
					inline explicit csf_attribute_manager()
						: m_root_element(csf_nullptr) {

					}

					virtual ~csf_attribute_manager() {
						clear();
					}
					/**
					 * ������ʱ��ֵ���ù�����
					 *
					 * @param configure_manager    ��ʾ���ù�������ַ
					 */
					inline explicit csf_attribute_manager(const csf::core::system::csf_configure_manager* configure_manager)
						: csf_manager((csf::core::system::csf_configure_manager*)configure_manager)
						, m_root_element(csf_nullptr) {

					}
					/**
					* ������ʱ��ֵ���ù�����
					*
					* @param configure_manager    ��ʾ���ù�������ַ
					* @param root_items    ��ʾ���Թ������и�·����Ϣ
					*/
					inline explicit csf_attribute_manager(const csf::core::system::csf_configure_manager* configure_manager
						, const std::list<csf_string> root_items)
						: csf_manager((csf::core::system::csf_configure_manager*)configure_manager)
						, m_root_element(csf_nullptr)
						, m_root_items(root_items) {

					}
					/**
					* ������ʱ��ֵ���ù�����
					*
					* @param root_element    ��ʾ������ĸ��ڵ���󡣸�������Ϣ������"csf_configure_manager*
					* m_configure_manager"������Ϣ����������˸ö��������Ȳ��ø���Ϣ��������������ö����л�ȡ��
					*
					* @param root_items    ��ʾ���Թ������и�·����Ϣ
					*/
					inline explicit csf_attribute_manager(const csf_element* root_element
						, const std::list<csf_string> root_items = std::list<csf_string>())
						: m_root_element((csf_element*)root_element)
						, m_root_items(root_items) {

					}
					/**
					 * ��������Ϊ����attribute_manager�����һ�����ԡ�
					 * ע�⣺��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ����������ʧ�ܡ�
					 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					 *
					 * @param name    ��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					 * @param attribute    ��ʾ��ӵ����Զ���
					 */
 					template <class AttributeType>
 					inline csf_bool add(const csf_string& name, AttributeType attribute) {
 
 						if (name.empty()) {
 							return csf_false;
 						}
 
 						return add<AttributeType>(name.c_str(), attribute);
 					}
					/**
					 * ��������Ϊ����attribute_manager�����һ�����ԡ�
					 * ע�⣺��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ����������ʧ�ܡ�
					 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					 *
					 * @param name    ��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					 * @param attribute    ��ʾ��ӵ����Զ���
					 */
					template <class AttributeType>
					csf_bool add(const csf_char* name, AttributeType attribute) {

						//�����������ݵĺϷ���
						if (!name || csf_strlen(name) <= 0 || attribute.is_null()) {
							csf_log_ex(warning, csf_log_code_warning
								, "add attribute failed. reason: attribute/name is null!");
							return csf_false;
						}

						//��ѯ�����������Ƿ��Ѿ����ڣ�����Ѿ������򷵻�ʧ��
						if (((csf_attribute&)find(name)).not_null()) {
							csf_log_ex(warning, csf_log_code_warning
								, "add name[ \"%s\" ] %s failed. reason: attribute existed!"
								, name
								, attribute.to_string().c_str());

							return exception_attribute(name, attribute);
						}

						//�����ֵΪ�գ�����Ҫ���»�ȡ������ֵ
						if (attribute.get_content().empty()) {
							if (!get_configure_manager()) {
								csf_log_ex(warning, csf_log_code_warning
									, "add name[ \"%s\" ] %s failed. reason: configure manager is null!"
									, name
									, attribute.to_string().c_str());
								
								return exception_attribute(name, attribute);
							}

							if (!attribute.process(*get_configure_manager(), name)) {
								csf_log_ex(warning, csf_log_code_warning
									, "add name[ \"%s\" ] %s failed. reason: attribute process failed!"
									, name
									, attribute.to_string().c_str());

								return exception_attribute(name, attribute);
							}
						}

						//����һ�����ܶ��󣬲���������Ϣ���µ������б���
						return insert_attribute(name, attribute);
					}
					/**
					* ��������Ϊ����attribute_manager�����һ�����ԡ�
					* ע�⣺��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ����������ʧ�ܡ�
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param name    ��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					* @param attribute    ��ʾ��ӵ����Զ���
					*/
 					virtual csf_bool add(const csf_string& name, csf_attribute& attribute) {
 						return add(name.c_str(), attribute);
 					}
					/**
					* ��������Ϊ����attribute_manager�����һ�����ԡ�
					* ע�⣺��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ����������ʧ�ܡ�
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param name    ��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					* @param attribute    ��ʾ��ӵ����Զ���
					*/
 					virtual csf_bool add(const csf_char* name, csf_attribute& attribute) {
 						return add<csf_attribute>(name, attribute);
 					}
					/**
					 * ��������Ϊ���������ƴ�attribute_manager��ɾ��һ�����ԡ�
					 * ���أ�true��ʾɾ���ɹ��������ڸ���������Ĭ�Ϸ��سɹ�����false��ʾʧ�ܡ�
					 *
					 * @param name    ��ʾ��Ҫɾ������������
					 */
					inline virtual csf_bool del(const csf_string& name) {

						if (name.empty()) {
							return csf_false;
						}

						return del(name.c_str());
					}
					/**
					 * ��������Ϊ���������ƴ�attribute_manager��ɾ��һ�����ԡ�
					 * ���أ�true��ʾɾ���ɹ��������ڸ���������Ĭ�Ϸ��سɹ�����false��ʾʧ�ܡ�
					 *
					 * @param name    ��ʾ��Ҫɾ������������
					 */
					virtual csf_bool del(const csf_char* name);
					/**
					 * ��������Ϊ���������ƴ�attribute_manager�в�ѯһ�����ԡ�
					 * ���أ�һ�����Զ���
					 *
					 * @param name    ��ʾ��������
					 */
					inline virtual const csf_attribute& find(const csf_string& name) {

						if (name.empty()) {
							return csf_attribute::get_null();
						}

						return find(name.c_str());
					}
					/**
					 * ��������Ϊ���������ƴ�attribute_manager�в�ѯһ�����ԡ�
					 * ���أ�һ�����Զ���
					 *
					 * @param name    ��ʾ��Ҫ����������
					 */
					const csf_attribute& find(const csf_char* name);
					/**
					 * ��������Ϊ������attribute_manager��һ��������Ϣ��
					 * ���أ�true��ʾ�����Ҹ��³ɹ���false��ʾ�����ڻ�ʧ�ܡ�
					 *
					 * @param name    ��ʾ�������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					 * @param attribute    ��ʾ���Զ���
					 */
					template <class AttributeType>
					inline csf_bool update(const csf_string& name, AttributeType& attribute) {

						if (name.empty()) {
							return csf_false;
						}

						return update(name.c_str(), attribute);
					}
					/**
					 * ��������Ϊ������attribute_manager��һ��������Ϣ��
					 * ���أ�true��ʾ�����Ҹ��³ɹ���false��ʾ�����ڻ�ʧ�ܡ�
					 *
					 * @param name    ��ʾ�������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					 * @param attribute    ��ʾ���Զ���
					 */
					template <class AttributeType>
					csf_bool update(const csf_char* name, AttributeType& attribute) {

						csf_unordered_map<csf_string, csf_attribute*>::iterator		tmp_iter;


						//�����������ݵĺϷ���
						if (!name || csf_strlen(name) <= 0) {
							csf_log_ex(warning, csf_log_code_warning
								, "add attribute failed. attribute/name is null!");
							return csf_false;
						}

						//��ѯ�����������Ƿ��Ѿ����ڣ�����Ѿ������򷵻�ʧ��
						tmp_iter = get_attributes().find(name);
						if (tmp_iter == get_attributes().end()) {
							csf_log_ex(warning, csf_log_code_warning
								, "update name[ \"%s\" ] %s failed. not found attribute."
								, name
								, attribute.to_string().c_str());
							return csf_false;
						}

						if (tmp_iter->second) {
							delete tmp_iter->second;
							tmp_iter->second = csf_nullptr;
							get_attributes().erase(tmp_iter);
						}

						if (!add(name, attribute)) {
							csf_log_ex(warning, csf_log_code_warning
								, "update name[ \"%s\" ] %s failed. add attribute failed."
								, name
								, attribute.to_string().c_str());
							return csf_false;
						}

						csf_log_ex(notice, csf_log_code_notice
							, "update name[ \"%s\" ] %s succeed."
							, name
							, attribute.to_string().c_str());
						return csf_true;
					}
					/**
					* ��������Ϊ������attribute_manager��һ��������Ϣ��
					* ���أ�true��ʾ�����Ҹ��³ɹ���false��ʾ�����ڻ�ʧ�ܡ�
					*
					* @param name    ��ʾ�������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					* @param attribute    ��ʾ���Զ���
					*/
					virtual csf_bool update(const csf_string& name, csf_attribute& attribute) {
						return update(name.c_str(), attribute);
					}
					/**
					* ��������Ϊ������attribute_manager��һ��������Ϣ��
					* ���أ�true��ʾ�����Ҹ��³ɹ���false��ʾ�����ڻ�ʧ�ܡ�
					*
					* @param name    ��ʾ�������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					* @param attribute    ��ʾ���Զ���
					*/
					virtual csf_bool update(const csf_char* name, csf_attribute& attribute) {
						return update<csf_attribute>(name, attribute);
					}
					/**
					* ��������Ϊ���������ƴ�attribute_manager��ȡһ��������ֵ��
					* �ú���ֱ�ӷ���һ��ָ��������ֵ��������Բ������򷵻�Ĭ�Ͽ�ֵ����ֵ�б�bool[false]��string[""]��int[0]��time[0]��space_
					* size[0]��
					*
					* ���أ�����ָ�����Ե���ֵ
					*
					* @param name    ��ʾ��������
					*/
					template <class AttributeType>
					inline auto get_value(const csf_string& name) -> decltype(std::declval<AttributeType>().get_value()) {
						return get_value<AttributeType
							, decltype(std::declval<AttributeType>().get_value())>(name.c_str());
					}
					/**
					* ��������Ϊ���������ƴ�attribute_manager��ȡһ��������ֵ��
					* �ú���ֱ�ӷ���һ��ָ��������ֵ��������Բ������򷵻�Ĭ�Ͽ�ֵ����ֵ�б�bool[false]��string[""]��int[0]��time[0]��space_
					* size[0]��
					*
					* ���أ�����ָ�����Ե���ֵ
					*
					* @param name    ��ʾ��������
					*/
					template <class AttributeType>
					inline auto get_value(const csf_char* name) -> decltype(std::declval<AttributeType>().get_value()) {

						csf_attribute			&attr = (csf_attribute &)find(name);


						if (attr.is_null()) {

							//����һ��ָ�����͵Ŀն��󷵻�Ĭ������
							static AttributeType			tmp_ret(name);
							return tmp_ret.get_value();
						}
						else {
							return get_value<AttributeType>(attr);
						}
					}
					/**
					* ��������Ϊ������attribute��ȡһ��������ֵ��
					* �ú���ֱ�ӷ���һ��ָ��������ֵ��������Բ������򷵻�Ĭ�Ͽ�ֵ����ֵ�б�bool[false]��string[""]��int[0]��time[0]��space_
					* size[0]��
					*
					* ���أ�����ָ�����Ե���ֵ
					*
					* @param attribute    ��ʾ���Զ���
					*/
					template <class AttributeType>
					inline auto get_value(csf_attribute& attribute) -> decltype(std::declval<AttributeType>().get_value()) {
						//return ((AttributeType&)attribute).get_value();
						return dynamic_cast<AttributeType&>(attribute).get_value();
					}
					/**
					* ��������Ϊ���������ƴ�attribute_manager�в�ѯһ�����Բ������������ݡ�
					* ���أ��ַ������ݡ�
					*
					* @param name    ��ʾ��Ҫ����������
					*/
					virtual csf_string get_content(const csf_char* name);
					/**
					* ��������Ϊ���������ƴ�attribute_manager�в�ѯһ�����Բ������������ݡ�
					* ���أ��ַ������ݡ�
					*
					* @param name    ��ʾ��Ҫ����������
					*/
					inline virtual csf_string get_content(const csf_string& name) {

						return get_content(name.c_str());
					}
					/**
					* ��ʾ������ù������е��������ݡ�
					* ���أ�true��ʾ����ɹ���false��ʾ����ʧ��
					*/
					inline csf_bool clear() {

						for (auto &tmp_attribute : get_attributes()) {
							if (tmp_attribute.second) {
								delete tmp_attribute.second;
								tmp_attribute.second = csf_nullptr;
							}
						}

						get_attributes().clear();

						return csf_true;
					}
					/**
					* ��ʾ������ĸ��ڵ����
					*/
					inline csf_element* get_root_element() {

						return m_root_element;
					}
					/**
					* ��ʾ������ĸ��ڵ����
					*
					* @param new_value
					*/
					inline void set_root_element(const csf_element* new_value) {

						m_root_element = (csf_element*)new_value;
					}
					/**
					* ��ʾģ��ָ����items����Եĸ�·����Ϣ�����ָ������Ϣ�����ģ���������Ϣ������Ը�·����Ϣ��
					*/
					inline std::list<csf_string>& get_root_items() {

						return m_root_items;
					}
					/**
					* ��ʾģ��ָ����items����Եĸ�·����Ϣ�����ָ������Ϣ�����ģ���������Ϣ������Ը�·����Ϣ��
					*
					* @param new_value
					*/
					inline void set_root_items(const std::list<csf_string>& new_value) {

						m_root_items = new_value;
					}
					/**
					*
					* @param cm    ��ʾ�������ù�����Ϣ����
					* @param root_items    ��ʾ���Թ������и�·����Ϣ
					*/
					inline void set_configure_manager(const csf::core::system::csf_configure_manager* cm
						, const std::list<csf_string> root_items) {

						csf::core::module::csf_manager::set_configure_manager(cm);
						set_root_items(root_items);
					}
					/**
					*
					* @param root_element    ��ʾ������ĸ��ڵ���󡣸�������Ϣ������"csf_configure_manager*
					* m_configure_manager"������Ϣ����������˸ö��������Ȳ��ø���Ϣ��������������ö����л�ȡ��
					*
					* @param root_items    ��ʾ���Թ������и�·����Ϣ
					*/
					inline void set_root_element(const csf_element* root_element
						, const std::list<csf_string> root_items) {

						set_root_element(root_element);
						set_root_items(root_items);
					}
					/**
					* ��Ҫ�����ǣ����������б��е������жϸ�ģ���Ƿ��Ѿ����ù�
					* ���أ�true��ʾ�����б������ݣ��Ѿ����ù���false��ʾ�����б�û�в�����û�����ù�
					*/
					inline csf_bool is_configured() {

						if (get_attributes().empty()) {
							return csf_false;
						}

						return csf_true;
					}
				protected:
					/**
					 * ��ʾ���õ������б�������Ҹ�����������
					 */
					inline csf_unordered_map<csf_string, csf_attribute*>& get_attributes() {

						return m_attributes;
					}

				private:
					/**
					* ��ʾ������ĸ��ڵ���󡣸�������Ϣ������"csf_configure_manager*
					* m_configure_manager"������Ϣ����������˸ö��������Ȳ��ø���Ϣ��������������ö����л�ȡ��
					*/
					csf_element* m_root_element = csf_nullptr;
					/**
					 * ��ʾ���õ������б�������Ҹ�����������
					 */
					csf_unordered_map<csf_string, csf_attribute*> m_attributes;
					/**
					* ��ʾģ��ָ����items����Եĸ�·����Ϣ�����ָ������Ϣ�����ģ���������Ϣ������Ը�·����Ϣ��
					*/
					std::list<csf_string> m_root_items;
					/**
					 * ��ʾ���õ������б�������Ҹ�����������
					 *
					 * @param new_value
					 */
					inline void set_attributes(csf_unordered_map<csf_string, csf_attribute*>& new_value) {

						m_attributes = new_value;
					}
					/**
					* ��������Ϊ����attribute_manager�����һ�����ԡ�
					* ע�⣺��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ����������ʧ�ܡ�
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param name    ��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					* @param attribute    ��ʾ��ӵ����Զ���
					*/
					template <class AttributeType>
					inline csf_bool exception_attribute(const csf_char* name, AttributeType& attribute) {

						if (attribute.exception_run()) {
							return insert_attribute(name, attribute);
						}

						return csf_false;
					}


					/**
					* ��������Ϊ����attribute_manager�����һ�����ԡ�
					* ע�⣺��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ����������ʧ�ܡ�
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param name    ��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					* @param attribute    ��ʾ��ӵ����Զ���
					*/
					template <class AttributeType>
					csf_bool insert_attribute(const csf_char* name, AttributeType& attribute) {

						AttributeType			*tmp_new = csf_nullptr;


						//����һ�����ܶ��󣬲���������Ϣ���µ������б���
						tmp_new = new AttributeType(attribute);
						if (!tmp_new) {
							csf_log_ex(warning, csf_log_code_warning
								, "add name[ \"%s\" ] %s failed. reason: new a instance failed!"
								, name
								, attribute.to_string().c_str());
							return csf_false;
						}
						else {
							get_attributes().insert(csf_unordered_map<csf_string, csf_attribute*>::value_type(name, tmp_new));

							csf_log_ex(notice, csf_log_code_notice
								, "add name[ \"%s\" ] %s succeed."
								, name
								, attribute.to_string().c_str());
						}
						return csf_true;
					}
				};
			}
		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_MANAGER_INCLUDED_)
