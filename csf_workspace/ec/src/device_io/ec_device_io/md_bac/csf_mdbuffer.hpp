/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdbuffer.hpp
*
*Version: 1.0
*
*Date: 28-11月-2019 21:23:03
*
*Description: Class(csf_mdbuffer) 表示内存池pool manager分配的buffer对象，满足线程安全需求
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDBUFFER_H_INCLUDED_)
#define CSF_MDBUFFER_H_INCLUDED_

#include "csf_buffer.hpp"

namespace ec
{
	namespace core
	{
		class csf_mdpool;
		/**
		 * 表示内存池pool manager分配的buffer对象，满足线程安全需求
		 * @author f
		 * @version 1.0
		 * @created 28-11月-2019 21:23:03
		 */
		class csf_mdbuffer : public csf::core::base::csf_buffer
		{

		public:
			inline explicit csf_mdbuffer()
				: m_mdpool(NULL) {

			}
			/**
			* 根据分配好的内存创建一个对象
			*
			* @param buf    表示内存地址
			* @param size    表示内存的大小
			*/
			inline explicit csf_mdbuffer(unsigned char* buf, int len)
				: csf_buffer(buf, len)
				, m_mdpool(NULL) {

			}

			virtual ~csf_mdbuffer() {

			}
			/**
			* 表示csf_mdbuffer所属的内存池对象
			*/
			inline ec::core::csf_mdpool* get_mdpool() {

				return m_mdpool;
			}
			/**
			* 表示csf_mdbuffer所属的内存池对象
			*
			* @param newVal
			*/
			inline void set_mdpool(ec::core::csf_mdpool* newVal) {
				m_mdpool = newVal;
			}
			/**
			* 功能：判断csf_mdbuffer是否为空
			* 返回：true表示是一个空对象，没有内存空间满足csf_buffer存储；fals表示不是一个空对象，有内存空间用于存储e
			*/
			inline bool is_null() {

				if (NULL == get_mdpool()
					|| csf_buffer::is_null()) {
					return true;
				}
				return false;
			}

			/**
			 * 表示销毁容器，除了clear清空数据外，更增加了销毁内存的功能。
			 * 执行clear后，对象还是完整的，可以继续使用。而相对执行destroy函数后，部分资源将会被释放，可能导致对象不完整，不能继续正常使用。
			 */
			virtual void destroy();

		private:
			/**
			 * 表示csf_mdbuffer所属的内存池对象
			 */
			ec::core::csf_mdpool *m_mdpool = NULL;

		};

	}

}
#endif // !defined(CSF_MDBUFFER_H_INCLUDED_)
