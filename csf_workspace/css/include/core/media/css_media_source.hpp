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
*Date: 07-10月-2018 16:50:29
*
*Description: Class(css_media_source) 表示css媒体源
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
		 * 表示css媒体源
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:29
		 */
		class css_media_source
		{

		public:
			/**
			 * 表示媒体源的类型
			 * @author f
			 * @version 1.0
			 * @created 07-10月-2018 16:50:29
			 */
			enum css_media_source_type
			{
				/**
				 * 表示未知的媒体源类型
				 */
				m_css_media_source_type_none = 0x00000001,
				/**
				 * 表示视频的媒体源类型
				 */
				m_css_media_source_type_video = 0x00000002,
				/**
				 * 表示音频的媒体源类型
				 */
				m_css_media_source_type_audio = 0x00000004
			};

			/**
			 * 表示媒体源子类型
			 * @author f
			 * @version 1.0
			 * @created 07-10月-2018 16:50:29
			 */
			enum css_media_source_subtype
			{
				/**
				 * 表示媒体源子类型
				 */
				m_css_media_source_subtype_none = 0x00000001
			};


			css_media_source();
			virtual ~css_media_source();

			/**
			 * 表示媒体源类型
			 */
			inline css::core::css_media_source_type get_type() {

				return m_type;
			}
			/**
			 * 表示媒体源类型
			 * 
			 * @param newVal
			 */
			inline void set_type(const css::core::css_media_source_type newVal) {

				m_type = newVal;
			}
			/**
			 * 表示媒体源子类型
			 */
			inline css::core::css_media_source_subtype get_subtype() {

				return m_subtype;
			}
			/**
			 * 表示媒体源子类型
			 * 
			 * @param newVal
			 */
			inline void set_subtype(const css::core::css_media_source_subtype newVal) {

				m_subtype = newVal;
			}
			/**
			 * 表示媒体源id
			 */
			inline csf_string get_id() {

				return m_id;
			}
			/**
			 * 表示媒体源id
			 * 
			 * @param newVal
			 */
			inline void set_id(const csf_string newVal) {

				m_id = newVal;
			}
			/**
			 * 表示媒体源名称
			 */
			inline csf_string get_name() {

				return m_name;
			}
			/**
			 * 表示媒体源名称
			 * 
			 * @param newVal
			 */
			inline void set_name(const csf_string newVal) {

				m_name = newVal;
			}
			/**
			 * 表示媒体源网络地址
			 */
			inline csf_string get_url() {

				return m_url;
			}
			/**
			 * 表示媒体源网络地址
			 * 
			 * @param newVal
			 */
			inline void set_url(const csf_string newVal) {

				m_url = newVal;
			}
			/**
			 * 表示媒体源的描述信息
			 */
			inline csf_string get_description() {

				return m_description;
			}
			/**
			 * 表示媒体源的描述信息
			 * 
			 * @param newVal
			 */
			inline void set_description(const csf_string newVal) {

				m_description = newVal;
			}
			/**
			 * 表示媒体源的解码url地址
			 */
			inline csf_string get_decode_url() {

				return m_decode_url;
			}
			/**
			 * 表示媒体源的解码url地址
			 * 
			 * @param newVal
			 */
			inline void set_decode_url(const csf_string newVal) {

				m_decode_url = newVal;
			}
			/**
			 * 表示媒体源的父节点
			 */
			inline csf_string get_parent() {

				return m_parent;
			}
			/**
			 * 表示媒体源的父节点
			 * 
			 * @param newVal
			 */
			inline void set_parent(const csf_string newVal) {

				m_parent = newVal;
			}

		private:
			/**
			 * 表示媒体源类型
			 */
			css::core::css_media_source_type m_type = css_media_source_type_none;
			/**
			 * 表示媒体源子类型
			 */
			css::core::css_media_source_subtype m_subtype = css_media_source_subtype_none;
			/**
			 * 表示媒体源id
			 */
			csf_string m_id = "";
			/**
			 * 表示媒体源名称
			 */
			csf_string m_name = "";
			/**
			 * 表示媒体源网络地址
			 */
			csf_string m_url = "";
			/**
			 * 表示媒体源的描述信息
			 */
			csf_string m_description = "";
			/**
			 * 表示媒体源的解码url地址
			 */
			csf_string m_decode_url = "";
			/**
			 * 表示媒体源的父节点
			 */
			csf_string m_parent = "";

		};

	}

}
#endif // !defined(CSS_MEDIA_SOURCE_H_INCLUDED_)
