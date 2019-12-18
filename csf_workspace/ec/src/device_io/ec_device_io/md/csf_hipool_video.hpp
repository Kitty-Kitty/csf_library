/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hipool_video.hpp
*
*Version: 1.0
*
*Date: 08-12月-2019 20:54:21
*
*Description: Class(csf_hipool_video) 表示用于视频数据帧保存的存储池
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HIPOOL_VIDEO_H_INCLUDED_)
#define CSF_HIPOOL_VIDEO_H_INCLUDED_

#include "csf_hipool.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示用于视频数据帧保存的存储池
		 * @author f
		 * @version 1.0
		 * @created 08-12月-2019 20:54:21
		 */
		class csf_hipool_video : public ec::core::csf_hipool
		{

		public:
			/**
			* 指定参数创建对象池
			*
			* @param size    表示内存池保留的最多内存数量。
			* @param buffer_size    表示当前默认的内存大小
			* 当内存块数量超过这个数量时，free的内存块将立即被释放；
			* 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			*/
			inline explicit csf_hipool_video(unsigned int size, unsigned int buffer_size)
				: csf_hipool(size, buffer_size) {

			}
			virtual ~csf_hipool_video() {

			}

		protected:
			/**
			 * 功能：创建一个资源对象
			 * 返回：成功则一个资源对象指针；失败则返回空
			 * 
			 * @param size    表示当前帧数据长度
			 */
			virtual csf_mdobject* create_object(unsigned int size);

		};

	}

}
#endif // !defined(CSF_HIPOOL_VIDEO_H_INCLUDED_)
