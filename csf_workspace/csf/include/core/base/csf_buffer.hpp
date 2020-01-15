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
*Date: 27-6月-2018 22:12:32
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
			 * 表示标识缓存
			 * @author f
			 * @version 1.0
			 * @created 27-6月-2018 22:12:32
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
				 * 构造一个指定长度的buffer
				 *
				 * @param len    表示buffer缓存的长度
				 */
				inline explicit csf_buffer(const csf_uint32 len)
					: csf_memblock(len)
					, m_start(csf_memblock::get_buffer())
					, m_end(m_start + csf_memblock::get_size())
					, m_pos(m_start)
					, m_last(m_start) {

					//reset();
				}
				/**
				 *
				 * @param buf    表示根据缓存空间来创建buffer
				 * @param len    表示缓存的长度
				 */
				inline explicit csf_buffer(const csf_uchar* buf, const csf_uint32 len)
					: csf_memblock(buf, len)
					, m_start(csf_memblock::get_buffer())
					, m_end(m_start + csf_memblock::get_size())
					, m_pos(m_start)
					, m_last(m_end) {

					//reset();
				}
				/**
				 *
				 * @param buf    表示根据字符串创建buffer
				 */
				inline explicit csf_buffer(const csf_char* buf)
					: csf_buffer((const csf_uchar*)buf, (csf_uint32)csf_strlen(buf)) {

				}
				/**
				 *
				 * @param str    表示根据csf_string内容创建一个buffer
				 */
				inline explicit csf_buffer(const csf_string& str)
					: csf_buffer(str.c_str()) {

				}
				/**
				* 复制构造函数
				* @param str    表示根据csf_buffer内容创建一个buffer
				*/
				inline csf_buffer(const csf_buffer& buf)
				{
					*this = buf;
				}

				virtual ~csf_buffer() {

				}
				/**
				 * 表示buffer的起始地址
				 */
				inline csf_uchar* get_start() const {

					return m_start;
				}
				/**
				 * 表示buffer的终于地址
				 */
				inline csf_uchar* get_end() const {

					return m_end;
				}
				/**
				 * 表示buffer的使用终于地址
				 */
				inline csf_uchar* get_last() const {

					return m_last;
				}
				/**
				* 表示buffer的使用终于地址。
				* 返回：true表示成功；false表示失败。
				*
				* @param new_value    new_value
				*/
				inline csf_bool set_last(const csf_uchar* new_value) {

					if (new_value < get_start() || new_value > get_end()) {
						return csf_false;
					}

					m_last = (csf_uchar*)new_value;
					return csf_true;
				}
				/**
				* 表示保存内容的缓存地址
				*/
				inline csf_uchar* get_buffer() const {

					return get_pos();
				}
				/**
				 * 表示获取buffer总缓存长度
				 */
				inline csf_uint32 size() const {

					return csf_memblock::size();
				}
				/**
				 * 表示当前实际已经使用的缓存的长度
				 */
				inline csf_uint32 length() const {

					return (csf_uint32)(get_last() - get_pos());
				}
				/**
				 * 表示清空buffer内容，重置buffer内容，并释放内存。
				 */
				inline csf_void clear() {
					csf_memblock::clear();

					reset();
				}
				/**
				 * 表示清空内存空间，并重置buffer内容
				 */
				inline csf_void memzero() {
					csf_memblock::memzero();
					reset();
				}
				/**
				 * 表示通过外置的内存初始化buffer
				 *
				 * @param buf    表示缓存内存地址
				 * @param len    表示缓存的长度
				 */
				inline csf_void assemble(const csf_uchar* buf, const csf_uint32 len) {

					csf_memblock::set_buffer(buf, len);
					reset();
				}
				/**
				 * 获取buffer指定位置的内存地址
				 *
				 * @param len    表示获取缓存数据偏移length后的内存地址
				 */
				inline csf_uchar* position(const csf_uint32 len) const {

					if (length() < len) {
						return csf_nullptr;
					}

					return get_pos() + len;
				}
				/**
				 * 将buffer转换为string
				 */
				inline csf_string to_string() const {

					return "";
				}
				/**
				 * 表示buffer是否为空，为空返回true,否则返回false。长度为0或null都为空，返回true。
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
				* 表示将csf_buffer插入到csf_buffer中。 返回：>=0表示实际添加的字符数量；<0表示错误码；
				*
				* @param buffer    表示需要添加的buffer内容
				*/
				inline csf_int32 cat(const csf_buffer& buffer) {

					return cat(buffer.get_buffer(), buffer.length());
				}
				/**
				 * 表示将csf_string插入到csf_buffer中。 返回：>=0表示实际添加的字符数量；<0表示错误码；
				 *
				 * @param str    表示标准字符内容
				 */
				inline csf_int32 cat(const csf_string& str) {

					return cat((csf_uchar*)str.c_str(), (csf_uint32)str.length());
				}
				/**
				 * 表示将一个char*字符串插入到buffer中。 返回：>=0表示实际添加的字符数量；<0表示错误码；
				 *
				 * @param buf    表示插入char*内容
				 */
				inline csf_int32 cat(const csf_char* buf) {

					return cat((csf_uchar*)buf, (csf_uint32)csf_strlen(buf));
				}
				/**
				* 将内存数据添加到buffer中。 返回：>=0表示实际添加的字符数量；<0表示错误码；
				*
				* @param buf    表示数据内存的起始地址
				* @param len    表示内存数据的长度
				*/
				inline csf_int32 cat(const csf_uchar* buf, const csf_uint32 len) {
					if (!buf || len <= 0 || len > avail()) {
						return 0;
					}

					//复制数据到内存中
					csf_memcpy(get_last(), buf, len);

					//设置last标志地址
					set_last(get_last() + len);

					return len;
				}
				/**
				 * 赋值操作，处理方式是将csf_buffer对象的所有内容（本身结构 和内存数据）拷贝一份，
				 *
				 * @param buffer    buffer
				 */
				inline csf_buffer& operator =(const csf_buffer& buffer) {

					/*如果是自复制，返回自身即可*/
					if (buffer == *this)
					{
						return *this;
					}

					//如果小于等0，表示buffer为空，则清空本地数据即可
					if (buffer.length() <= 0) {
						clear();
					}
					else {
						//如果有数据，则复制数据
						csf_memblock::reset(buffer.length());
						reset();
						cat(buffer);
					}

					return *this;
				}
				/**
				 * 对比操作，当判断csf_buffer的四个内部地址相同时，即表示csf_buffer对象相同。
				 *
				 * @param buffer    表示需要被比较的csf_buffer对象
				 */
				inline bool operator ==(const csf_buffer& buffer) const {

					if ((get_start() == buffer.get_start())
						&& (get_end() == buffer.get_end())
						&& (get_pos() == buffer.get_pos())
						&& (get_last() == buffer.get_last())
						)
					{
						return true;
					}

					return false;
				}
				/**
				* 累加操作，处理方式是将csf_buffer对象的所有内容（本身结构 和内存数据）拷贝一份，
				*
				* @param buffer    buffer
				*/
				inline csf_buffer& operator +=(csf_buffer& buffer) {

					csf_uchar			*tmp_buf = csf_nullptr;
					csf_uint32			tmp_length = 0;

					//如果没有内容，则直接返回
					if (buffer.length() <= 0) {
						return *this;
					}

					//如果buffer数据少于空闲空间，则直接添加
					if (buffer.length() <= avail()) {
						cat(buffer);
						return *this;
					}

					/*
					//如果数据大于空闲空间，则需要重新创建内存保存
					tmp_length = length() + buffer.length();
					tmp_buf = new csf_uchar[tmp_length];

					csf_memcpy(tmp_buf, get_buffer(), length());
					csf_memcpy(tmp_buf + length(), buffer.get_buffer(), buffer.length());
					clear();
					set_buffer(tmp_buf, tmp_length, csf_true);
					reset();

					//设置游标值
					reset();
					set_last(get_end());
					*/

					/*修改：采用临时变量存储内容，避免在buffer中申请内存，在memblock中去释放*/
					csf_buffer tmp_buffer(length() + buffer.length());

					tmp_buffer.cat(*this);
					tmp_buffer.cat(buffer);

					*this = tmp_buffer;

					return  *this;
				}
				/**
				 * 表示buffer的当前地址
				 */
				inline csf_uchar* get_pos() const {

					return m_pos;
				}
				/**
				 * 表示清空buffer内容，重置buffer内容
				 */
				inline csf_void reset() {

					set_start(csf_memblock::get_buffer());
					set_end(get_start() + csf_memblock::size());

					set_last(get_start());
					set_pos(get_start());

				}
				/**
				* 表示buffer的当前地址。
				* 返回：true表示成功；false表示失败。
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
				* 表示获取buffer未使用的空间长度
				*/
				inline csf_uint32 avail() const {

					return (csf_uint32)(get_end() - get_last());
				}
				/**
				* 取buffer中间部分的内容。
				*
				* @param pos 从pos位置取数据
				* @param cnt 需要取得数据的个数
				*/
				csf_buffer mid(csf_uint32 pos, csf_uint32 cnt)const
				{
					/*参数不合法*/
					if (pos + cnt > get_size())
					{
						return csf_buffer();
					}

					csf_buffer tmp_buf(cnt);
					tmp_buf.cat(get_buffer() + pos, cnt);

					return tmp_buf;
				}
				/**
				* 取buffer左侧部分的内容。
				* 返回：成功返回数据内容，失败返回空
				*
				* @param cnt 需要取得数据的个数
				*/
				csf_buffer left(csf_uint32 cnt)const
				{
					return mid(0, cnt);
				}
				/**
				* 取buffer右侧部分的内容。
				* 返回：成功返回数据内容，失败返回空
				*
				* @param cnt 需要取得数据的个数
				*/
				csf_buffer right(csf_uint32 cnt)const
				{
					return mid(get_size() - cnt, cnt);
				}
			protected:
				/**
				* 表示销毁容器，除了clear清空数据外，更增加了销毁内存的功能。
				* 执行clear后，对象还是完整的，可以继续使用。而相对执行destroy函数后，部分资源将会被释放，可能导致对象不完整，不能继续正常使用。
				*/
				inline virtual csf_void destroy() {
					csf_memblock::destroy();
				}
			private:
				/**
				 * 表示buffer的起始地址
				 */
				csf_uchar* m_start = csf_nullptr;
				/**
				 * 表示buffer的终于地址
				 */
				csf_uchar* m_end = csf_nullptr;
				/**
				 * 表示buffer的当前地址
				 */
				csf_uchar* m_pos = csf_nullptr;
				/**
				 * 表示buffer的使用终于地址
				 */
				csf_uchar* m_last = csf_nullptr;

				/**
				 * 表示buffer的起始地址
				 *
				 * @param new_value    new_value
				 */
				inline csf_void set_start(const csf_uchar* new_value) {

					m_start = (csf_uchar*)new_value;
				}
				/**
				 * 表示buffer的终于地址
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
