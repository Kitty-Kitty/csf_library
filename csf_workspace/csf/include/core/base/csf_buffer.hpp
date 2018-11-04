/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_buffer.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 22:12:32
*
*Description: Class(csf_buffer)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_BUFFER_INCLUDED_)
#define CSF_BUFFER_INCLUDED_

#include "csf_memblock.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾ��ʶ����
			 * @author f
			 * @version 1.0
			 * @created 27-6��-2018 22:12:32
			 */
			class csf_buffer : public csf::core::base::csf_memblock
			{

			public:
				inline explicit csf_buffer()
				    : m_start(csf_nullptr)
					, m_end(csf_nullptr)
					, m_pos(csf_nullptr)
					, m_last(csf_nullptr) {

				}
				/**
				 * ����һ��ָ�����ȵ�buffer
				 * 
				 * @param len    ��ʾbuffer����ĳ���
				 */
				inline explicit csf_buffer(const csf_uint32 len) 
					: csf_memblock(len)
					, m_start(csf_nullptr)
					, m_end(csf_nullptr)
					, m_pos(csf_nullptr)
					, m_last(csf_nullptr) {

					reset();
				}
				/**
				 * 
				 * @param buf    ��ʾ���ݻ���ռ�������buffer
				 * @param len    ��ʾ����ĳ���
				 */
				inline explicit csf_buffer(const csf_uchar* buf, const csf_uint32 len) 
					: csf_memblock(buf, len)
					, m_start(csf_nullptr)
					, m_end(csf_nullptr)
					, m_pos(csf_nullptr)
					, m_last(csf_nullptr) {

					reset();
				}
				/**
				 * 
				 * @param buf    ��ʾ�����ַ�������buffer
				 */
				inline explicit csf_buffer(const csf_char* buf) 
					: csf_buffer((const csf_uchar*) buf, csf_strlen(buf)) {

				}
				/**
				 * 
				 * @param str    ��ʾ����csf_string���ݴ���һ��buffer
				 */
				inline explicit csf_buffer(const csf_string& str) 
					: csf_buffer(str.c_str()) {

				}
				virtual ~csf_buffer() {

				}
				/**
				 * ��ʾbuffer����ʼ��ַ
				 */
				inline csf_uchar* get_start() const {

					return m_start;
				}
				/**
				 * ��ʾbuffer�����ڵ�ַ
				 */
				inline csf_uchar* get_end() const {

					return m_end;
				}
				/**
				 * ��ʾbuffer��ʹ�����ڵ�ַ
				 */
				inline csf_uchar* get_last() const {

					return m_last;
				}
				/**
				* ��ʾbuffer��ʹ�����ڵ�ַ��
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
				*
				* @param new_value    new_value
				*/
				inline csf_bool set_last(const csf_uchar* new_value) {

					if (new_value < get_pos() || new_value > get_end()) {
						return csf_false;
					}

					m_last = (csf_uchar*)new_value;
					return csf_true;
				}
				/**
				* ��ʾ�������ݵĻ����ַ
				*/
				inline csf_uchar* get_buffer() const {

					return get_pos();
				}
				/**
				 * ��ʾ��ȡbuffer�ܻ��泤��
				 */
				inline csf_uint32 size() const {

					return csf_memblock::size();
				}
				/**
				 * ��ʾ��ǰʵ���Ѿ�ʹ�õĻ���ĳ���
				 */
				inline csf_uint32 length() const {

					return (csf_uint32)(get_last() - get_pos());
				}
				/**
				 * ��ʾ���buffer���ݣ�����buffer���ݣ����ͷ��ڴ档
				 */
				inline csf_void clear() {
					csf_memblock::clear();

					reset();
				}
				/**
				 * ��ʾ����ڴ�ռ䣬������buffer����
				 */
				inline csf_void memzero() {

					reset();
				}
				/**
				 * ��ʾͨ�����õ��ڴ��ʼ��buffer
				 * 
				 * @param buf    ��ʾ�����ڴ��ַ
				 * @param len    ��ʾ����ĳ���
				 */
				inline csf_void assemble(const csf_uchar* buf, const csf_uint32 len) {

					csf_memblock::set_buffer(buf, len);
					reset();
				}
				/**
				 * ��ȡbufferָ��λ�õ��ڴ��ַ
				 * 
				 * @param len    ��ʾ��ȡ��������ƫ��length����ڴ��ַ
				 */
				inline csf_uchar* position(const csf_uint32 len) const {

					if (length() < len) {
						return csf_nullptr;
					}

					return get_pos() + len;
				}
				/**
				 * ��bufferת��Ϊstring
				 */
				inline csf_string to_string() const {

					return "";
				}
				/**
				 * ��ʾ�ͷ�buffer�е�startָ�����ڴ棬����buffer���Ϊnull
				 */
				inline csf_void destroy() {
					clear();
				}
				/**
				 * ��ʾbuffer�Ƿ�Ϊ�գ�Ϊ�շ���true,���򷵻�false������Ϊ0��null��Ϊ�գ�����true��
				 */
				inline csf_bool empty() const {

					if (csf_memblock::empty()) {
						return csf_true;
					}

					if (length() <= 0) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				* ��ʾ��csf_buffer���뵽csf_buffer�С� ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
				*
				* @param buffer    ��ʾ��Ҫ��ӵ�buffer����
				*/
				inline csf_int32 cat(csf_buffer& buffer) {

					return cat(buffer.get_buffer(), buffer.length());
				}
				/**
				 * ��ʾ��csf_string���뵽csf_buffer�С� ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
				 * 
				 * @param str    ��ʾ��׼�ַ�����
				 */
				inline csf_int32 cat(const csf_string& str) {

					return cat((csf_uchar*)str.c_str(), str.length());
				}
				/**
				 * ��ʾ��һ��char*�ַ������뵽buffer�С� ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
				 * 
				 * @param buf    ��ʾ����char*����
				 */
				inline csf_int32 cat(const csf_char* buf) {

					return cat((csf_uchar*)buf, csf_strlen(buf));
				}
				/**
				* ���ڴ�������ӵ�buffer�С� ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
				*
				* @param buf    ��ʾ�����ڴ����ʼ��ַ
				* @param len    ��ʾ�ڴ����ݵĳ���
				*/
				inline csf_int32 cat(const csf_uchar* buf, const csf_uint32 len) {
					if (!buf || len <= 0 || len > avail()) {
						return 0;
					}

					//�������ݵ��ڴ���
					csf_memcpy(get_last(), buf, len);

					//����last��־��ַ
					set_last(get_last() + len);

					return len;
				}
				/**
				 * ��ֵ����������ʽ�ǽ�csf_buffer������������ݣ�����ṹ ���ڴ����ݣ�����һ�ݣ�
				 * 
				 * @param buffer    buffer
				 */
				inline csf_buffer& operator =(csf_buffer& buffer) {

					//���С�ڵ�0����ʾbufferΪ�գ�����ձ������ݼ���
					if (buffer.length() <= 0) {
						clear();
					}
					else {
						//��������ݣ���������
						csf_memblock::reset(buffer.length());
						reset();
						cat(buffer);
					}

					return *this;
				}
				/**
				 * �ԱȲ��������ж�csf_buffer���ĸ��ڲ���ַ��ͬʱ������ʾcsf_buffer������ͬ��
				 * 
				 * @param buffer    ��ʾ��Ҫ���Ƚϵ�csf_buffer����
				 */
				inline bool operator ==(const csf_buffer& buffer) const {

					return false;
				}
				/**
				* �ۼӲ���������ʽ�ǽ�csf_buffer������������ݣ�����ṹ ���ڴ����ݣ�����һ�ݣ�
				*
				* @param buffer    buffer
				*/
				inline csf_buffer& operator +=(csf_buffer& buffer) {

					csf_uchar			*tmp_buf = csf_nullptr;

					//���û�����ݣ���ֱ�ӷ���
					if (buffer.length() <= 0) {
						return *this;
					}

					//���buffer�������ڿ��пռ䣬��ֱ�����
					if (buffer.length() <= avail()) {
						cat(buffer);
						return *this;
					}

					//������ݴ��ڿ��пռ䣬����Ҫ���´����ڴ汣��
					tmp_buf = new csf_uchar(length() + buffer.length());
					csf_memcpy(tmp_buf, get_buffer(), length());
					csf_memcpy(tmp_buf + length(), buffer.get_buffer(), buffer.length());
					clear();
					set_buffer(tmp_buf, length() + buffer.length(), csf_true);

					return  *this;
				}
				/**
				 * ��ʾbuffer�ĵ�ǰ��ַ
				 */
				inline csf_uchar* get_pos() const {

					return m_pos;
				}
				/**
				 * ��ʾ���buffer���ݣ�����buffer����
				 */
				inline csf_void reset() {

					set_start(get_buffer());
					set_pos(get_start());
					set_last(get_pos());
					set_end(get_start() + csf_memblock::size());
				}
				/**
				* ��ʾbuffer�ĵ�ǰ��ַ��
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
				*
				* @param new_value
				*/
				inline csf_bool set_pos(const csf_uchar* new_value) {

					if (new_value < get_start() || new_value > get_last()) {
						return csf_false;
					}

					m_pos = (csf_uchar*)new_value;
					return csf_true;
				}
				/**
				* ��ʾ��ȡbufferδʹ�õĿռ䳤��
				*/
				inline csf_uint32 avail() const {

					return (csf_uint32)(get_end() - get_last());
				}

			private:
				/**
				 * ��ʾbuffer����ʼ��ַ
				 */
				csf_uchar* m_start = csf_nullptr;
				/**
				 * ��ʾbuffer�����ڵ�ַ
				 */
				csf_uchar* m_end = csf_nullptr;
				/**
				 * ��ʾbuffer�ĵ�ǰ��ַ
				 */
				csf_uchar* m_pos = csf_nullptr;
				/**
				 * ��ʾbuffer��ʹ�����ڵ�ַ
				 */
				csf_uchar* m_last = csf_nullptr;

				/**
				 * ��ʾbuffer����ʼ��ַ
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_start(const csf_uchar* new_value) {

					m_start = (csf_uchar*)new_value;
				}
				/**
				 * ��ʾbuffer�����ڵ�ַ
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_end(const csf_uchar* new_value) {

					m_end = (csf_uchar*)new_value;
				}

			};

		}

	}

}
#endif // !defined(CSF_BUFFER_INCLUDED_)
