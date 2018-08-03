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
*Date: 30-6月-2018 8:49:47
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
			 * 表示数据对象内容
			 * @author fz
			 * @version 1.0
			 * @created 30-6月-2018 8:49:47
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
				 * 表示数据对象节点名称
				 */
				inline csf_string& get_name() {

					return m_name;
				}
				/**
				 * 添加一个元素对象。
				 * 
				 * @param element    表示需要被添加的元素
				 */
				inline virtual csf_int32 add(const csf_element& element) {

					get_children().push_back(element);
					return csf_success;
				}
				/**
				 * 表示数据对象节点数据内容
				 */
				inline csf_string& get_content() {

					return m_content;
				}
				/**
				 * 表示添加一个父子结点,将child添加到parent中。
				 * 返回：0表示成功；非0表示失败。
				 * 
				 * @param parent    表示父结点
				 * @param child    表示子结点
				 */
				inline virtual csf_int32 add(csf_element& parent, const csf_element& child) {

					return parent.add(child);
				}
				/**
				 * 表示添加一个子结点，添加到指定parent中。
				 * 返回：0表示成功；非0表示失败。
				 * 
				 * @param parent    表示父结点
				 * @param child    表示子结点
				 */
				inline virtual csf_int32 add(const csf_string& parent, const csf_element& child) {

					csf_element						&tmp_element = (csf_element&)get_null();

					tmp_element = find_element(parent);
					if (tmp_element.not_null()) {
						return tmp_element.add(child);
					}

					return csf_failure;
				}
				/**
				 * 表示添加一个子结点，添加到指定parent中。
				 * 返回：0表示成功；非0表示失败。
				 * 
				 * @param parent    表示父结点
				 * @param child    表示子结点
				 */
				inline virtual csf_int32 add(const csf_char* parent, const csf_element& child) {

					if (!parent || csf_strlen(parent) <= 0) {
						return csf_failure;
					}

					return add(csf_string(parent), child);
				}
				/**
				 * 表示添加一个属性数据
				 * 
				 * @param name    表示需要添加的属性名称
				 * @param val    表示需要添加的属性数据
				 */
				inline virtual csf_int32 add(const csf_string& name, const csf_string& val) {

					if (name.empty()) {
						return csf_failure;
					}

					return add(name.c_str(), val.c_str());
				}
				/**
				 * 表示添加一个属性数据
				 * 
				 * @param name    表示需要添加的属性名称
				 * @param val    表示需要添加的属性数据
				 */
				inline virtual csf_int32 add(const csf_char* name, const csf_char* val) {

					if (!name || !val || csf_strlen(name) <= 0) {
						return csf_failure;
					}

					get_attributes().insert(csf_map<csf_string, csf_string>::value_type(name, val));
					//m_attributes[name] = val;
					return csf_success;
				}
				/**
				 * 表示清空内容
				 */
				inline virtual csf_void clear() {
					*this = get_null();
				}
				/**
				 * 表示查找一个属性数值
				 * 
				 * @param name    表示需要查找的属性名称
				 */
				inline virtual const csf_string& find(const csf_string& name) {

					if (name.empty()) {
						return  csf_string_null;
					}

					return  find(name.c_str());
				}
				/**
				 * 表示查找一个属性数值
				 * 
				 * @param name    表示需要查找的属性名称
				 */
				inline virtual const csf_string& find(const csf_char* name) {

					csf_map<csf_string, csf_string>::iterator			tmp_iter;

					if (!name || csf_strlen(name) <= 0) {
						return csf_string_null;
					}

					tmp_iter = get_attributes().find(name);
					if (tmp_iter != get_attributes().end()) {
						return tmp_iter->second;
					}

					return  csf_string_null;
				}
				/**
				 * 表示查找一个子element
				 * 返回：非null表示成功；null表示失败。
				 * 
				 * @param name    表示需要查找的element名称
				 */
				inline virtual const csf_element& find_child(const csf_string& name) {

					//名称为空则返回空
					if (name.empty()) {
						return get_null();
					}

					//判断当前模块是否就是需要查找的名称
					if (get_name() == name) {
						return *this;
					}

					//查找子模块列表
					for (csf_element &tmp_iter : m_children) {
						if (tmp_iter.get_name() == name) {
							return tmp_iter;
						}
					}
					return get_null();
				}
				/**
				 * 表示查找一个子element
				 * 返回：非null表示成功；null表示失败。
				 * 
				 * @param name    表示需要查找的element名称
				 */
				inline virtual const csf_element& find_child(const csf_char* name) {

					if (!name || csf_strlen(name) <= 0) {
						return get_null();
					}

					return find_child(csf_string(name));
				}
				/**
				* 表示查找一个element
				* 返回：非null表示成功；null表示失败。
				*
				* @param name    表示需要查找的element名称
				*/
				virtual const csf_element& find_element(const csf_string& name);
#if 0
				/**
				 * 表示查找一个element
				 * 返回：非null表示成功；null表示失败。
				 * 
				 * @param name    表示需要查找的element名称
				 */
				inline virtual const csf_element& find_element(const csf_string& name) {

					csf_element						&tmp_element = (csf_element&)m_null;

					//表示先查询子结点
					tmp_element = find_child(name);
					if (tmp_element.not_null()) {
						return tmp_element;
					}

					//从子模块中遍布查找子对象
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
				 * 表示查找一个element
				 * 返回：非null表示成功；null表示失败。
				 * 
				 * @param name    表示需要查找的element名称
				 */
				inline virtual const csf_element& find_element(const csf_char* name) {

					if (!name) {
						return get_null();
					}
					return  find_element(csf_string(name));
				}
				/**
				* 表示根据items属性路径查找一个element。
				* 返回：非null表示满足items所有路径的节点；null表示没有查找到满足路径的节点；
				*
				* @param items    items属性路径
				*/
				virtual const csf_element& find_element(const csf_list<csf_string>& items);
				/**
				 * 表示数据对象节点数据内容
				 * 
				 * @param newVal
				 */
				inline csf_void set_content(csf_string& newVal) {

					m_content = newVal;
				}
				/**
				 * 表示数据对象节点名称
				 * 
				 * @param newVal
				 */
				inline csf_void set_name(const csf_char* newVal) {

					m_name = newVal;
				}
				/**
				 * 表示数据对象节点名称
				 * 
				 * @param newVal
				 */
				inline csf_void set_name(const csf_string& newVal) {

					m_name = newVal;
				}
				/**
				 * 表示数据对象节点数据内容
				 * 
				 * @param newVal
				 */
				inline csf_void set_content(csf_char* newVal) {

					m_content = newVal;
				}
				/**
				* 表示子节点列表
				*/
				inline csf_list<csf_element>& get_children() {

					return m_children;
				}
				/**
				* 表示判断是否为空。
				* 返回：true表示为空；false表示不为空。
				*/
				inline csf_bool is_null() {

					if (get_name().empty()
						&& get_content().empty()
						&& get_children().empty()
						&& get_attributes().empty()) {
						return csf_true;
					}

					return csf_false;
				}
				/**
				* 表示判断是否不为空。
				* 返回：true表示不为空；false表示为空。
				*/
				inline csf_bool not_null() {

					return !is_null();
				}

			private:
				/**
				 * 表示数据对象节点名称
				 */
				csf_string m_name = "";
				/**
				 * 表示数据对象节点数据内容
				 */
				csf_string m_content = "";
				/**
				 * 表示子节点列表
				 */
				csf_list<csf_element> m_children;
				/**
				 * 表示属性信息内容
				 */
				csf_map<csf_string, csf_string> m_attributes;

				/**
				 * 表示属性信息内容
				 */
				inline csf_map<csf_string, csf_string>& get_attributes() {

					return m_attributes;
				}
				/**
				 * 表示属性信息内容
				 * 
				 * @param newVal
				 */
				inline csf_void set_attributes(csf_map<csf_string, csf_string>& newVal) {

					m_attributes = newVal;
				}
				/**
				 * 表示子节点列表
				 * 
				 * @param newVal
				 */
				inline csf_void set_children(const csf_list<csf_element>& newVal) {

					m_children = newVal;
				}
			};

		}

	}

}
#endif // !defined(CSF_ELEMENT_INCLUDED_)
