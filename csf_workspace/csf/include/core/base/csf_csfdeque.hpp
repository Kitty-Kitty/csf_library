/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: csf_csfdeque.hpp
*
*Version: 1.0
*
*Date: 28-2月-2019 17:04:00
*
*Description: Class(csf_csfdeque) 表示csf封装的线程安全的双向队列
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CSFDEQUE_H_INCLUDED_)
#define CSF_CSFDEQUE_H_INCLUDED_

#include "csf_stdcollector.hpp"
#include "csf_collector.hpp"
#include "csf_mutex.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf封装的线程安全的双向队列
			 * @author Administrator
			 * @version 1.0
			 * @created 28-2月-2019 17:04:00
			 */
			template<typename TypeName>
			class csf_csfdeque : public csf::core::base::csf_collector
			{

			public:
				csf_csfdeque() {

				}

				virtual ~csf_csfdeque() {

				}

				/**
				 * 功能：
				 *    在队列后面插入元素。
				 * 返回：
				 *    true：表示成功；
				 *    false：表示失败；
				 *
				 * @param value    表示需要被插入的对象
				 */
				inline csf_bool push_back(const TypeName& value) {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					try {
						get_deque().push_back(value);
					}
//					catch (...) {
					catch (std::exception &e) {
						throw e;
// 						csf_log_ex(debug
// 							, csf_log_code_debug
// 							, "exception[%s]"
// 							, e.what());
						return csf_false;
					}
					return csf_true;
				}
				/**
				 * 主要功能：
				 *    查询收集器的元素总个数。
				 * 返回：
				 *    >=0表示元素的总个数。
				 */
				virtual csf_int32 size() {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					return (csf_int32)get_deque().size();
				}
				/**
				 * 主要功能：
				 *    清空收集器中的所有元素
				 * 返回：
				 *    ture：表示清除成功
				 *    false：表示清除失败
				 */
				virtual csf_bool clear() {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					get_deque().clear();

					return csf_true;
				}
				/**
				 * 功能：
				 *    在队列前面插入元素。
				 * 返回：
				 *    true：表示成功；
				 *    false：表示失败；
				 *
				 * @param value    表示需要被插入的对象
				 */
				inline csf_bool push_front(const TypeName& value) {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					try {
						get_deque().push_front(value);
					}
//					catch (...) {
					catch (std::exception &e) {
						throw e;
						//写入异常处理代码
// 						csf_log_ex(debug
// 							, csf_log_code_debug
// 							, "exception[%s]"
// 							, e.what());
						return csf_false;
					}
					return csf_true;
				}
				/**
				 * 主要功能：
				 *    判断容器是否为空
				 * 返回：
				 *    ture：表示为空
				 *    false：表示不为空
				 */
				virtual csf_bool empty() {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					return get_deque().empty();
				}
				/**
				 * 功能：
				 *    在队列前面删除一个元素。
				 * 返回：
				 *    true：表示成功；
				 *    false：表示失败；
				 *
				 * @param value    表示需要被插入的对象
				 */
				inline csf_bool pop_front(TypeName& value) {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					if (get_deque().empty()) {
						return csf_false;
					}
					value = get_deque().front();
					get_deque().pop_front();

					return csf_true;
				}
				/**
				 * 功能：
				 *    在队列后面删除一个元素。
				 * 返回：
				 *    true：表示成功；
				 *    false：表示失败；
				 *
				 * @param value    表示需要被插入的对象
				 */
				inline csf_bool pop_back(TypeName& value) {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					if (get_deque().empty()) {
						return csf_false;
					}
					value = get_deque().back();
					get_deque().pop_back();

					return csf_true;
				}
			private:
				/**
				* 表示封闭在内部的stl标准双向队列
				*/
				inline csf_deque<TypeName>& get_deque() {

					return m_deque;
				}
			private:
				/**
				* 表示封闭在内部的stl标准双向队列
				*/
				csf_deque<TypeName> m_deque;
				/**
				* 表示线程安全使用的互斥锁内容
				*/
				csf_shared_mutex m_mutex;
			};

		}

	}

}
#endif // !defined(CSF_CSFDEQUE_H_INCLUDED_)
