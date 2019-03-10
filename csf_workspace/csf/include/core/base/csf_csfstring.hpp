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
					: csf_memblock((const csf_uchar*)buf, (csf_uint32)csf_strlen(buf)) {

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
					: csf_memblock((csf_uint32)str.length()) {
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

					clear();
					reset(csfstr.get_size());
					cat(csfstr.get_buffer(), csfstr.length());

					return *this;
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

					if (get_buffer() && get_size() > 0) {
						get_buffer()[get_size() - 1] = '\0';
						return csf_string((csf_char*)get_buffer());
					}

					return "";
				}
				/**
				* 主要功能：
				*    格式化csfstring字符串内容
				* 返回：
				*    <0 ：表示失败；
				*    >=0：表示处理后的字符串长度
				*
				* @param fmt    表示格式化字符串
				* @param ...
				*/
				inline csf_int32 format(const csf_char* fmt, ...) {

					csf_int32				tmp_int = 0;
					va_list					tmp_marker;


					if (!fmt || csf_strlen(fmt) <= 0) {
						return 0;
					}

					va_start(tmp_marker, fmt);

					tmp_int = format(fmt, tmp_marker);

					va_end(tmp_marker);

					//如果返回正值，则表示当前的字符串
					return tmp_int;
				}
				/**
				* 主要功能：
				*    格式化csfstring字符串内容
				* 返回：
				*    <0 ：表示失败；
				*    >=0：表示处理后的字符串长度
				*
				* @param fmt    表示格式化字符串
				* @param args   表示参数列表
				*/
				inline csf_int32 format(const csf_char* fmt, va_list args) {

					csf_int32				tmp_int = 0;


					if (!fmt || csf_strlen(fmt) <= 0) {
						return 0;
					}

					tmp_int = csf_vsnprintf((csf_char*)get_buffer()
						, get_size()
						, fmt
						, args);
					if (tmp_int < 0) {
						//如果返回负值，则表示失败
						return tmp_int;
					}

					//如果返回正值，则表示当前的字符串
					return tmp_int;
				}
				
				/**
				* 表示容器是否为空，为空返回true,否则返回false。长度为0或null为空，返回true。
				*/
				inline virtual csf_bool empty() {

					//如果buffer为空，则返回正确
					if (csf_memblock::empty()) {
						return csf_true;
					}

					//如果buffer不为空，而内容为空，也返回正确
					if (get_buffer() && 0 == *get_buffer()) {
						return csf_true;
					}

					return csf_false;
				}

			};

		}

	}

}
#endif // !defined(CSF_CSFSTRING_INCLUDED_)
