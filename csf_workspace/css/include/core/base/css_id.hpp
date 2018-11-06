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
*Date: 07-10��-2018 16:50:28
*
*Description: Class(css_id) ��ʾcssϵͳ���豸id
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
		 * ��ʾcssϵͳ���豸id
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:28
		 */
		class css_id
		{

		public:
			css_id();
			virtual ~css_id();

			/**
			 * ��ʾid��ֵ
			 */
			inline csf_string get_value() {

				return m_value;
			}
			/**
			 * ��ʾid��ֵ
			 * 
			 * @param newVal
			 */
			inline csf_void set_value(const csf_string newVal) {

				m_value = newVal;
			}
			/**
			 * ��ʾid��Ψһ��ʶ��
			 */
			inline csf_string get_guid() {

				return m_guid;
			}
			/**
			 * ��ʾid��Ψһ��ʶ��
			 * 
			 * @param newVal
			 */
			inline csf_void set_guid(const csf_string newVal) {

				m_guid = newVal;
			}
			/**
			 * ����id��
			 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
			 * 
			 * @param id    ��ʾ��Ҫ��������id
			 */
			csf_bool parse(const csf_string& id);
			/**
			 * ����id��
			 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
			 * 
			 * @param id    ��ʾ��Ҫ��������id
			 */
			csf_bool parse(const csf_char* id);
			/**
			 * ��ʾ����css_id
			 * 
			 * @param parameters    ��ʾʵ�ʵ�id�����б�
			 * @param guid    ��ʾid��guid����
			 */
			csf_bool make(const csf_vertor<csf_int32>& parameters, csf_string& guid);
			/**
			 * ��ʾ����css_id
			 * 
			 * @param parameters    ��ʾʵ�ʵ�id�����б�
			 * @param guid    ��ʾid��guid����
			 */
			csf_bool make(const csf_vertor<csf_int32>& parameters, csf_char* guid);
			/**
			 * ��ʾ����css_id
			 * 
			 * @param parameters    ��ʾʵ�ʵ�id�����б�
			 */
			csf_bool make(const csf_vertor<csf_int32>& parameters);
			/**
			 * ��ʾid�б���Ĳ����б�
			 */
			inline csf_vertor<csf_string>& get_parameters() {

				return m_parameters;
			}
			/**
			 * ��ʾid�б���Ĳ����б�
			 * 
			 * @param newVal    ��ʾ�����ַ��б�
			 */
			inline void set_parameters(const csf_vertor<csf_string>& newVal) {

				m_parameters = newVal;
			}
			/**
			 * ��ʾ��ʾ��ȡָ�������Ĳ���
			 * 
			 * @param index    ��ʾ��������ֵ
			 */
			inline csf_string get_parameter(const csf_int32 index = 0) {

				return m_parameters;
			}
			/**
			 * ����id��
			 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
			 * 
			 * @param id    ��ʾ��Ҫ��������id
			 */
			css_id& operator =(const csf_char* id);
			/**
			 * ����id��
			 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
			 * 
			 * @param id    ��ʾ��Ҫ��������id
			 */
			css_id& operator =(const csf_string& id);

		private:
			/**
			 * ��ʾid��ֵ
			 */
			csf_string m_value = "";
			/**
			 * ��ʾid��Ψһ��ʶ��
			 */
			csf_string m_guid = "";
			/**
			 * ��ʾid�б���Ĳ����б�
			 */
			csf_vertor<csf_string> m_parameters;

		};

	}

}
#endif // !defined(CSS_ID_H_INCLUDED_)
