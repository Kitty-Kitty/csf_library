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
*Date: 27-6��-2018 21:34:05
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
			 * ��ʾcsfʹ�õ�string
			 * @author f
			 * @version 1.0
			 * @created 27-6��-2018 21:34:05
			 */
			class csf_csfstring : public csf::core::base::csf_memblock
			{

			public:
				inline explicit csf_csfstring() {

				}
				/**
				 * ����char*�ַ�������csf_csfstring
				 *
				 * @param buf    buf
				 */
				inline explicit csf_csfstring(const csf_char* buf)
					: csf_memblock((const csf_uchar*)buf, (csf_uint32)csf_strlen(buf)) {

				}
				/**
				 * ���ݻ����ַ�ͳ��ȴ���һ��csf_csfstring
				 *
				 * @param buf    ��ʾ���ݻ����ַ�ͳ��ȴ���һ��csf_csfstring
				 * @param len    len
				 */
				inline explicit csf_csfstring(const csf_uchar* buf, const csf_int32 len)
					: csf_memblock(buf, len) {

				}
				/**
				 * ��stringת��Ϊcsf_csfstring
				 *
				 * @param str    ��ʾ��Ҫ��ת����string�ַ���
				 */
				inline explicit csf_csfstring(const csf_string& str)
					: csf_memblock((csf_uint32)str.length()) {
					csf_strcpy((csf_char*)get_buffer(), str.c_str());
				}
				/**
				 * ���ݳ��ȴ���һ��csf_csfstring
				 *
				 * @param len    ��ʾ��Ҫ������csf_csfstring����ĳ���
				 */
				inline explicit csf_csfstring(const csf_int32 len)
					: csf_memblock(len) {

				}
				virtual ~csf_csfstring() {

				}
				/**
				 * ��ʾ��char*�ַ�����ӵ�csf_csfstrin�С�
				 * ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
				 *
				 * @param buf    ��ʾchar*�ַ�������
				 */
				inline csf_int32 cat(const csf_char* buf) {

					return 0;
				}
				/**
				 * �������ַ��ָ������������ӵ�csf_csfstring�С�
				 * ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
				 *
				 * @param buf    ��ʾ������ݵĻ����ַ
				 * @param len    ��ʾ������ݵĻ��泤��
				 */
				inline csf_int32 cat(const csf_uchar* buf, const csf_uint32 len) {

					return 0;
				}
				/**
				 * ��string������ӵ�csf_csfstring�С�
				 * ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
				 *
				 * @param str    ��ʾ��Ҫ��ӵ�string����
				 */
				inline csf_int32 cat(const csf_string str) {

					return 0;
				}
				/**
				 * ��ֵ����������ʽ�ǽ�������������ݣ�����ṹ ���ڴ����ݣ�����һ�ݣ�
				 *
				 * @param csfstr    ��Ҫ����ֵ�Ķ���
				 */
				inline csf_csfstring& operator =(const csf_csfstring& csfstr) {

					clear();
					reset(csfstr.get_size());
					cat(csfstr.get_buffer(), csfstr.length());

					return *this;
				}
				/**
				 * ��ʾ��ȡָ�����ȵĻ����ַ
				 *
				 * @param len    ��ʾָ������
				 */
				inline csf_uchar* position(const csf_uint32 len) {

					return  NULL;
				}
				/**
				 * ��csf_csfstring����ת��Ϊstring
				 */
				inline csf_string to_string() {

					if (get_buffer() && get_size() > 0) {
						get_buffer()[get_size() - 1] = '\0';
						return csf_string((csf_char*)get_buffer());
					}

					return "";
				}
				/**
				* ��Ҫ���ܣ�
				*    ��ʽ��csfstring�ַ�������
				* ���أ�
				*    <0 ����ʾʧ�ܣ�
				*    >=0����ʾ�������ַ�������
				*
				* @param fmt    ��ʾ��ʽ���ַ���
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

					//���������ֵ�����ʾ��ǰ���ַ���
					return tmp_int;
				}
				/**
				* ��Ҫ���ܣ�
				*    ��ʽ��csfstring�ַ�������
				* ���أ�
				*    <0 ����ʾʧ�ܣ�
				*    >=0����ʾ�������ַ�������
				*
				* @param fmt    ��ʾ��ʽ���ַ���
				* @param args   ��ʾ�����б�
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
						//������ظ�ֵ�����ʾʧ��
						return tmp_int;
					}

					//���������ֵ�����ʾ��ǰ���ַ���
					return tmp_int;
				}
				
				/**
				* ��ʾ�����Ƿ�Ϊ�գ�Ϊ�շ���true,���򷵻�false������Ϊ0��nullΪ�գ�����true��
				*/
				inline virtual csf_bool empty() {

					//���bufferΪ�գ��򷵻���ȷ
					if (csf_memblock::empty()) {
						return csf_true;
					}

					//���buffer��Ϊ�գ�������Ϊ�գ�Ҳ������ȷ
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
