/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_media_source.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:29
*
*Description: Class(css_media_source) ��ʾcssý��Դ
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_MEDIA_SOURCE_H_INCLUDED_)
#define CSS_MEDIA_SOURCE_H_INCLUDED_

namespace css
{
	namespace core
	{
		/**
		 * ��ʾcssý��Դ
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:29
		 */
		class css_media_source
		{

		public:
			/**
			 * ��ʾý��Դ������
			 * @author f
			 * @version 1.0
			 * @created 07-10��-2018 16:50:29
			 */
			enum css_media_source_type
			{
				/**
				 * ��ʾδ֪��ý��Դ����
				 */
				m_css_media_source_type_none = 0x00000001,
				/**
				 * ��ʾ��Ƶ��ý��Դ����
				 */
				m_css_media_source_type_video = 0x00000002,
				/**
				 * ��ʾ��Ƶ��ý��Դ����
				 */
				m_css_media_source_type_audio = 0x00000004
			};

			/**
			 * ��ʾý��Դ������
			 * @author f
			 * @version 1.0
			 * @created 07-10��-2018 16:50:29
			 */
			enum css_media_source_subtype
			{
				/**
				 * ��ʾý��Դ������
				 */
				m_css_media_source_subtype_none = 0x00000001
			};


			css_media_source();
			virtual ~css_media_source();

			/**
			 * ��ʾý��Դ����
			 */
			inline css::core::css_media_source_type get_type() {

				return m_type;
			}
			/**
			 * ��ʾý��Դ����
			 * 
			 * @param newVal
			 */
			inline void set_type(const css::core::css_media_source_type newVal) {

				m_type = newVal;
			}
			/**
			 * ��ʾý��Դ������
			 */
			inline css::core::css_media_source_subtype get_subtype() {

				return m_subtype;
			}
			/**
			 * ��ʾý��Դ������
			 * 
			 * @param newVal
			 */
			inline void set_subtype(const css::core::css_media_source_subtype newVal) {

				m_subtype = newVal;
			}
			/**
			 * ��ʾý��Դid
			 */
			inline csf_string get_id() {

				return m_id;
			}
			/**
			 * ��ʾý��Դid
			 * 
			 * @param newVal
			 */
			inline void set_id(const csf_string newVal) {

				m_id = newVal;
			}
			/**
			 * ��ʾý��Դ����
			 */
			inline csf_string get_name() {

				return m_name;
			}
			/**
			 * ��ʾý��Դ����
			 * 
			 * @param newVal
			 */
			inline void set_name(const csf_string newVal) {

				m_name = newVal;
			}
			/**
			 * ��ʾý��Դ�����ַ
			 */
			inline csf_string get_url() {

				return m_url;
			}
			/**
			 * ��ʾý��Դ�����ַ
			 * 
			 * @param newVal
			 */
			inline void set_url(const csf_string newVal) {

				m_url = newVal;
			}
			/**
			 * ��ʾý��Դ��������Ϣ
			 */
			inline csf_string get_description() {

				return m_description;
			}
			/**
			 * ��ʾý��Դ��������Ϣ
			 * 
			 * @param newVal
			 */
			inline void set_description(const csf_string newVal) {

				m_description = newVal;
			}
			/**
			 * ��ʾý��Դ�Ľ���url��ַ
			 */
			inline csf_string get_decode_url() {

				return m_decode_url;
			}
			/**
			 * ��ʾý��Դ�Ľ���url��ַ
			 * 
			 * @param newVal
			 */
			inline void set_decode_url(const csf_string newVal) {

				m_decode_url = newVal;
			}
			/**
			 * ��ʾý��Դ�ĸ��ڵ�
			 */
			inline csf_string get_parent() {

				return m_parent;
			}
			/**
			 * ��ʾý��Դ�ĸ��ڵ�
			 * 
			 * @param newVal
			 */
			inline void set_parent(const csf_string newVal) {

				m_parent = newVal;
			}

		private:
			/**
			 * ��ʾý��Դ����
			 */
			css::core::css_media_source_type m_type = css_media_source_type_none;
			/**
			 * ��ʾý��Դ������
			 */
			css::core::css_media_source_subtype m_subtype = css_media_source_subtype_none;
			/**
			 * ��ʾý��Դid
			 */
			csf_string m_id = "";
			/**
			 * ��ʾý��Դ����
			 */
			csf_string m_name = "";
			/**
			 * ��ʾý��Դ�����ַ
			 */
			csf_string m_url = "";
			/**
			 * ��ʾý��Դ��������Ϣ
			 */
			csf_string m_description = "";
			/**
			 * ��ʾý��Դ�Ľ���url��ַ
			 */
			csf_string m_decode_url = "";
			/**
			 * ��ʾý��Դ�ĸ��ڵ�
			 */
			csf_string m_parent = "";

		};

	}

}
#endif // !defined(CSS_MEDIA_SOURCE_H_INCLUDED_)
