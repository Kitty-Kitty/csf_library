/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_id.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:28
*
*Description: Class(css_id) 表示css系统的设备id
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_ID_H_INCLUDED_)
#define CSS_ID_H_INCLUDED_

namespace css
{
	namespace core
	{
		/**
		 * 表示css系统的设备id
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:28
		 */
		class css_id
		{

		public:
			css_id();
			virtual ~css_id();

			/**
			 * 表示id数值
			 */
			inline csf_string get_value() {

				return m_value;
			}
			/**
			 * 表示id数值
			 * 
			 * @param newVal
			 */
			inline csf_void set_value(const csf_string newVal) {

				m_value = newVal;
			}
			/**
			 * 表示id的唯一标识符
			 */
			inline csf_string get_guid() {

				return m_guid;
			}
			/**
			 * 表示id的唯一标识符
			 * 
			 * @param newVal
			 */
			inline csf_void set_guid(const csf_string newVal) {

				m_guid = newVal;
			}
			/**
			 * 解析id。
			 * 返回：true表示成功；false表示失败。
			 * 
			 * @param id    表示需要被解析的id
			 */
			csf_bool parse(const csf_string& id);
			/**
			 * 解析id。
			 * 返回：true表示成功；false表示失败。
			 * 
			 * @param id    表示需要被解析的id
			 */
			csf_bool parse(const csf_char* id);
			/**
			 * 表示创建css_id
			 * 
			 * @param parameters    表示实际的id参数列表
			 * @param guid    表示id的guid数据
			 */
			csf_bool make(const csf_vertor<csf_int32>& parameters, csf_string& guid);
			/**
			 * 表示创建css_id
			 * 
			 * @param parameters    表示实际的id参数列表
			 * @param guid    表示id的guid数据
			 */
			csf_bool make(const csf_vertor<csf_int32>& parameters, csf_char* guid);
			/**
			 * 表示创建css_id
			 * 
			 * @param parameters    表示实际的id参数列表
			 */
			csf_bool make(const csf_vertor<csf_int32>& parameters);
			/**
			 * 表示id中保存的参数列表
			 */
			inline csf_vertor<csf_string>& get_parameters() {

				return m_parameters;
			}
			/**
			 * 表示id中保存的参数列表
			 * 
			 * @param newVal    表示参数字符列表
			 */
			inline void set_parameters(const csf_vertor<csf_string>& newVal) {

				m_parameters = newVal;
			}
			/**
			 * 表示表示获取指定索引的参数
			 * 
			 * @param index    表示索引号数值
			 */
			inline csf_string get_parameter(const csf_int32 index = 0) {

				return m_parameters;
			}
			/**
			 * 解析id。
			 * 返回：true表示成功；false表示失败。
			 * 
			 * @param id    表示需要被解析的id
			 */
			css_id& operator =(const csf_char* id);
			/**
			 * 解析id。
			 * 返回：true表示成功；false表示失败。
			 * 
			 * @param id    表示需要被解析的id
			 */
			css_id& operator =(const csf_string& id);

		private:
			/**
			 * 表示id数值
			 */
			csf_string m_value = "";
			/**
			 * 表示id的唯一标识符
			 */
			csf_string m_guid = "";
			/**
			 * 表示id中保存的参数列表
			 */
			csf_vertor<csf_string> m_parameters;

		};

	}

}
#endif // !defined(CSS_ID_H_INCLUDED_)
