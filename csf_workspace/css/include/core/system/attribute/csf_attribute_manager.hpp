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
				 * ��ʾģ������Թ�����
				 * @author Administrator
				 * @version 1.0
				 * @created 06-7��-2018 19:29:31
				 */
				class csf_attribute_manager : public csf::core::module::csf_manager, public csf::core::system::attribute::csf_attribute_manager_interface
				{

				public:
					inline explicit csf_attribute_manager()
						: m_configure_manager(csf_nullptr) {

					}

					virtual ~csf_attribute_manager() {
						clear();
					}

					/**
					 * ������ʱ��ֵ���ù�����
					 *
					 * @param configure_manager    ��ʾ���ù�������ַ
					 */
					inline explicit csf_attribute_manager(const csf_configure_manager* configure_manager)
						: m_configure_manager((csf_configure_manager*)configure_manager) {

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
					inline csf_bool add(const csf_string& name, AttributeType& attribute) {

						if (name.empty()) {
							return csf_false;
						}

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
					template <class AttributeType>
					csf_bool add(const csf_char* name, AttributeType& attribute) {

						AttributeType			*tmp_new = csf_nullptr;


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
							return csf_false;
						}

						//�����ֵΪ�գ�����Ҫ���»�ȡ������ֵ
						if (attribute.get_content().empty()) {
							if (!get_configure_manager()) {
								csf_log_ex(warning, csf_log_code_warning
									, "add name[ \"%s\" ] %s failed. reason: configure manager is null!"
									, name
									, attribute.to_string().c_str());
								return csf_false;
							}

							if (!attribute.process(*get_configure_manager(), name)) {
								csf_log_ex(warning, csf_log_code_warning
									, "add name[ \"%s\" ] %s failed. reason: attribute process failed!"
									, name
									, attribute.to_string().c_str());
								return csf_false;
							}
						}

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
					 * ��ʾ�����Թ�����ʹ�õ����ù����������ַ��
					 */
					inline csf_configure_manager* get_configure_manager() {

						return m_configure_manager;
					}
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
					 * ��ʾ�����Թ�����ʹ�õ����ù����������ַ��
					 *
					 * @param newVal    ��ʾ���ù�������ַ
					 */
					inline void set_configure_manager(const csf_configure_manager* newVal) {

						m_configure_manager = (csf_configure_manager*)newVal;
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
					inline auto get_value(const csf_string& name) {
						return get_value<AttributeType, ValueType>(name.c_str());
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
					inline auto get_value(const csf_char* name) {

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
					inline auto get_value(csf_attribute& attribute) {
						return ((AttributeType&)attribute).get_value();
					}
					/**
					* ��������Ϊ���������ƴ�attribute_manager��ȡһ��������ֵ������val�����С�
					*
					* ���أ�true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ�ܣ����в����ڸ���ֵҲ����ʧ�ܡ�
					*
					* @param val    ��ʾ��ȡ����������ֵ������val������
					* @param name    ��ʾ��������
					*/
					template <class AttributeType, typename ValueType>
					inline csf_bool get_value(ValueType& val, const csf_string& name) {

						return get_value<AttributeType, ValueType>(val, name.c_str());
					}
					/**
					* ��������Ϊ���������ƴ�attribute_manager��ȡһ��������ֵ������val�����С�
					*
					* ���أ�true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ�ܣ����в����ڸ���ֵҲ����ʧ�ܡ�
					*
					* @param val    ��ʾ��ȡ����������ֵ������val������
					* @param name    ��ʾ��������
					*/
					template <class AttributeType, typename ValueType>
					inline csf_bool get_value(ValueType& val, const csf_char* name) {

						csf_attribute			&attr = find(name);


						if (attr.is_null()) {
							return csf_false;
						}
						else {
							val = ((AttributeType&)attr).get_value();
						}
						return csf_true;
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
				protected:
					/**
					 * ��ʾ���õ������б�������Ҹ�����������
					 */
					inline csf_unordered_map<csf_string, csf_attribute*>& get_attributes() {

						return m_attributes;
					}

				private:
					/**
					 * ��ʾ���õ������б�������Ҹ�����������
					 */
					csf_unordered_map<csf_string, csf_attribute*> m_attributes;
					/**
					 * ��ʾ�����Թ�����ʹ�õ����ù����������ַ��
					 */
					csf_configure_manager* m_configure_manager = csf_nullptr;

					/**
					 * ��ʾ���õ������б�������Ҹ�����������
					 *
					 * @param newVal
					 */
					inline void set_attributes(csf_unordered_map<csf_string, csf_attribute*>& newVal) {

						m_attributes = newVal;
					}
				};
			}
		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_MANAGER_INCLUDED_)
