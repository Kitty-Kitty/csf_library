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
*Date: 30-6月-2018 8:49:48
*
*Description: Class(csf_element)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_element.hpp"

using csf::core::system::csf_element;


/**
* 表示查找一个element
* 返回：非null表示成功；null表示失败。
*
* @param name    表示需要查找的element名称
*/
const csf_element& csf_element::find_element(const csf_string& name) {

	csf_element						*tmp_element = csf_nullptr;


	//表示先查询子结点
	tmp_element = (csf_element*)&find_child(name);
	if (tmp_element->not_null()) {

		return *tmp_element;
	}

	//从子模块中遍布查找子对象
	for (csf_element &tmp_iter : get_children()) {

		tmp_element = (csf_element*)&tmp_iter.find_element(name);
		if (tmp_element->not_null()) {
			return *tmp_element;
		}
	}
	return get_null();
}


/**
* 表示根据items属性路径查找一个element。
* 返回：非null表示满足items所有路径的节点；null表示没有查找到满足路径的节点；
*
* @param items    items属性路径
*/
const csf_element& csf_element::find_element(const csf_list<csf_string>& items) {

	csf_element						*tmp_element = this;


	//如果请求的属性路径为空，则直接返回空
	if (items.empty()) {
		return get_null();
	}

	//遍历属性路径，查找满足路径的节点对象
	for (csf_string &tmp_item : (csf_list<csf_string>&)items) {
		tmp_element = (csf_element*)&(tmp_element->find_element(tmp_item));
		if (tmp_element->is_null()) {
			return get_null();
		}
	}

	if (tmp_element->not_null()) {
		return *tmp_element;
	}

	return get_null();
}