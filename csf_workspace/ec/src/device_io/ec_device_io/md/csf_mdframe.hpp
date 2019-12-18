/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdframe.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 12:20:35
*
*Description: Class(csf_mdframe) 表示媒体通道中的每一帧数据，每帧是都是一个媒体对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDFRAME_H_INCLUDED_)
#define CSF_MDFRAME_H_INCLUDED_

#include <memory>
#include "csf_mdobject.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体通道中的每一帧数据，每帧是都是一个媒体对象
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 12:20:35
		 */
		class csf_mdframe : public std::enable_shared_from_this<csf_mdframe>
		{

		public:
			csf_mdframe(csf_mdobject* mdobject)
				: m_mdobject(mdobject) {

			}
			virtual ~csf_mdframe() {

				if (get_mdobject()) {
					get_mdobject()->destroy();
					set_mdobject(NULL);
				}
			}

			/**
			 * 保存的媒体源数据对象
			 */
			inline csf_mdobject* get_mdobject() {

				return m_mdobject;
			}
			/**
			 * 保存的媒体源数据对象
			 * 
			 * @param newVal
			 */
			inline void set_mdobject(csf_mdobject* newVal) {

				m_mdobject = newVal;
			}

		private:
			/**
			 * 保存的媒体源数据对象
			 */
			csf_mdobject* m_mdobject = NULL;

		};
		//定义一个智能指针类型
		typedef	std::shared_ptr<csf_mdframe>	csf_mdframe_ptr;
	}

}
#endif // !defined(CSF_MDFRAME_H_INCLUDED_)
