﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:43
*
*Description: Class(csf_message)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MESSAGE_INCLUDED_)
#define CSF_MESSAGE_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_element.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace message
			{
				/**
				 * 表示csf模块使用的message消息队列，用于消息的处理。
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:43
				 */
				class csf_message
				{

				public:
					csf_message();
					virtual ~csf_message();

					/**
					 * 根据csf_message_type和callback创建一个csf_message
					 * 
					 * @param type    表示message的类型
					 * @param callback    表示message的回调函数
					 */
					csf_message(const csf_message_type type, const csf::core::system::message::csf_message_callback callback);
					/**
					 * 根据csf_message_type和callback创建一个csf_message
					 * 
					 * @param type    表示message的类型
					 * @param callback    表示message的回调函数
					 * @param element
					 */
					csf_message(const csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element);
					/**
					 * 表示消息回调函数
					 */
					inline csf::core::system::message::csf_message_callback get_callback() {

						return m_callback;
					}
					/**
					 * 表示消息回调函数
					 * 
					 * @param newVal
					 */
					inline void set_callback(const csf::core::system::message::csf_message_callback newVal) {

						m_callback = newVal;
					}
					/**
					 * 表示消息的类型
					 */
					inline csf::core::system::message::csf_message_type get_type() {

						return m_type;
					}
					/**
					 * 表示消息的类型
					 * 
					 * @param newVal
					 */
					inline void set_type(const csf::core::system::message::csf_message_type newVal) {

						m_type = newVal;
					}
					/**
					 * 表示message自带的信息内容
					 */
					inline csf_element& get_element() {

						return m_element;
					}
					/**
					 * 表示message自带的信息内容
					 * 
					 * @param newVal
					 */
					inline void set_element(const csf_element& newVal) {

						m_element = newVal;
					}

				private:
					/**
					 * 表示消息回调函数
					 */
					csf::core::system::message::csf_message_callback m_callback = csf_null;
					/**
					 * 表示消息的类型
					 */
					csf::core::system::message::csf_message_type m_type = csf_message_type_none;
					/**
					 * 表示message自带的信息内容
					 */
					csf::core::system::csf_element m_element;

				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_INCLUDED_)
