/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_csfstring.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 21:34:05
*
*Description: Class(csf_csfstring)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CSFSTRING_INCLUDED_)
#define CSF_CSFSTRING_INCLUDED_

#include "csf_memblock.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf使用的string
			 * @author f
			 * @version 1.0
			 * @created 27-6月-2018 21:34:05
			 */
			class csf_csfstring : public csf::core::base::csf_memblock
			{

			public:
				inline explicit csf_csfstring() {

				}
				/**
				 * 根据char*字符串创建csf_csfstring
				 * 
				 * @param buf    buf
				 */
				inline explicit csf_csfstring(const csf_char* buf)
					: csf_memblock((const csf_uchar*)buf, csf_strlen(buf)) {

				}
				/**
				 * 根据缓存地址和长度创建一个csf_csfstring
				 * 
				 * @param buf    表示根据缓存地址和长度创建一个csf_csfstring
				 * @param len    len
				 */
				inline explicit csf_csfstring(const csf_uchar* buf, const csf_int32 len) 
					: csf_memblock(buf, len) {

				}
				/**
				 * 将string转换为csf_csfstring
				 * 
				 * @param str    表示需要被转换的string字符串
				 */
				inline explicit csf_csfstring(const csf_string& str) 
					: csf_memblock(str.length()) {
					csf_strcpy((csf_char*)get_buffer(), str.c_str());
				}
				/**
				 * 根据长度创建一个csf_csfstring
				 * 
				 * @param len    表示需要创建的csf_csfstring缓存的长度
				 */
				inline explicit csf_csfstring(const csf_int32 len) 
					: csf_memblock(len) {

				}
				virtual ~csf_csfstring() {

				}
				/**
				 * 表示将char*字符串添加到csf_csfstrin中。
				 * 返回：>=0表示实际添加的字符数量；<0表示错误码；
				 * 
				 * @param buf    表示char*字符串内容
				 */
				inline csf_int32 cat(const csf_char* buf) {

					return 0;
				}
				/**
				 * 将缓存地址的指定长度内容添加到csf_csfstring中。
				 * 返回：>=0表示实际添加的字符数量；<0表示错误码；
				 * 
				 * @param buf    表示添加内容的缓存地址
				 * @param len    表示添加内容的缓存长度
				 */
				inline csf_int32 cat(const csf_uchar* buf, const csf_uint32 len) {

					return 0;
				}
				/**
				 * 将string内容添加到csf_csfstring中。
				 * 返回：>=0表示实际添加的字符数量；<0表示错误码；
				 * 
				 * @param str    表示需要添加的string内容
				 */
				inline csf_int32 cat(const csf_string str) {

					return 0;
				}
				/**
				 * 赋值操作，处理方式是将对象的所有内容（本身结构 和内存数据）拷贝一份，
				 * 
				 * @param csfstr    需要被赋值的对象
				 */
				inline csf_csfstring& operator =(const csf_csfstring& csfstr) {

					return csf_csfstring();
				}
				/**
				 * 表示获取指定长度的缓存地址
				 * 
				 * @param len    表示指定长度
				 */
				inline csf_uchar* position(const csf_uint32 len) {

					return  NULL;
				}
				/**
				 * 将csf_csfstring内容转换为string
				 */
				inline csf_string to_string() {

					return "";
				}

			};

		}

	}

}
#endif // !defined(CSF_CSFSTRING_INCLUDED_)
