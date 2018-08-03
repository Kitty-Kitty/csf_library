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
*Date: 27-6月-2018 17:28:41
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
			 * 表示csf_element类型数据操作接口
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:41
			 */
			class csf_element_interface
			{

			public:
				csf_element_interface() {

				}

				virtual ~csf_element_interface() {

				}

				/**
				 * 添加一个元素对象。
				 * 
				 * @param element    表示需要被添加的元素
				 */
				virtual csf_int32 add(const csf_element& element) =0;
				/**
				 * 表示添加一个父子结点
				 * 
				 * @param parent    表示父结点
				 * @param child    表示子结点
				 */
				virtual csf_int32 add(const csf_element& parent, const csf_element& child) =0;
				/**
				 * 表示添加一个父子结点
				 * 
				 * @param parent    表示父结点
				 * @param child    表示子结点
				 */
				virtual csf_int32 add(const csf_string& parent, const csf_element& child) =0;
				/**
				 * 表示添加一个父子结点
				 * 
				 * @param parent    表示父结点
				 * @param child    表示子结点
				 */
				virtual csf_int32 add(const csf_char* parent, const csf_element& child) =0;
				/**
				 * 表示添加一个属性数据
				 * 
				 * @param name    表示需要添加的属性名称
				 * @param val    表示需要添加的属性数据
				 */
				virtual csf_int32 add(const csf_string& name, const csf_string& val) =0;
				/**
				 * 表示添加一个属性数据
				 * 
				 * @param name    表示需要添加的属性名称
				 * @param val    表示需要添加的属性数据
				 */
				virtual csf_int32 add(const csf_char* name, const csf_char* val) =0;
				/**
				 * 表示清空内容
				 */
				virtual csf_void clear() =0;
				/**
				 * 表示查找一个属性数值
				 * 
				 * @param name    表示需要查找的属性名称
				 */
				virtual csf_string& find(const csf_string& name) =0;
				/**
				 * 表示查找一个属性数值
				 * 
				 * @param name    表示需要查找的属性名称
				 */
				virtual csf_string& find(const csf_char* name) =0;
				/**
				 * 表示查找一个子element。
				 * 
				 * @param name    表示需要查找的element名称
				 */
				virtual const csf_element& find_child(const csf_string& name) =0;
				/**
				 * 表示查找一个子element。
				 * 
				 * @param name    表示需要查找的element名称
				 */
				virtual const csf_element& find_child(const csf_char* name) =0;
				/**
				 * 表示查找一个element。
				 * 
				 * @param name    表示需要查找的element名称
				 */
				virtual const csf_element& find_element(const csf_string& name) =0;
				/**
				 * 表示查找一个element。
				 * 
				 * @param name    表示需要查找的element名称
				 */
				virtual const csf_element& find_element(const csf_char* name) =0;
				/**
				* 表示根据items属性路径查找一个element。
				* 返回：非null表示满足items所有路径的节点；null表示没有查找到满足路径的节点；
				*
				* @param items    items属性路径
				*/
				virtual const csf_element& find_element(const csf_list<csf_string>& items) = 0;
			};

		}

	}

}
#endif // !defined(CSF_ELEMENT_INTERFACE_INCLUDED_)
