/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hiobject_video.hpp
*
*Version: 1.0
*
*Date: 08-12月-2019 20:54:33
*
*Description: Class(csf_hiobject_video) 表示海思视频流使用的对象类型
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HIOBJECT_VIDEO_H_INCLUDED_)
#define CSF_HIOBJECT_VIDEO_H_INCLUDED_

#include "csf_hiobject.hpp"
#include "csf_h264_nalu.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示海思视频流使用的对象类型
		 * @author f
		 * @version 1.0
		 * @created 08-12月-2019 20:54:33
		 */
		class csf_hiobject_video : public ec::core::csf_hiobject
		{

		public:
			/**
			* 构造一个指定长度的buffer
			*
			* @param pool    表示当前对象所属的对象池
			* @param len    表示buffer缓存的长度
			*/
			inline explicit csf_hiobject_video(csf_mdpool* pool, const unsigned int len)
				: csf_hiobject(pool, len)
				, m_nalu_type(csf_h264_nalu::h264_nalu_nal) {
			}

			/**
			* 构造一个指定长度的buffer
			*
			* @param len    表示buffer缓存的长度
			*/
			inline explicit csf_hiobject_video(const unsigned int len)
				: csf_hiobject(len)
				, m_nalu_type(csf_h264_nalu::h264_nalu_nal) {

			}
			virtual ~csf_hiobject_video() {

			}

			/**
			 * 表示当前帧类型
			 */
			inline csf_h264_nalu::h264_nalu_type get_nalu_type() {

				return m_nalu_type;
			}
			/**
			 * 表示当前帧类型
			 *
			 * @param newVal
			 */
			inline void set_nalu_type(csf_h264_nalu::h264_nalu_type newVal) {

				m_nalu_type = newVal;
			}

		private:
			/**
			 * 表示当前帧类型
			 */
			csf_h264_nalu::h264_nalu_type m_nalu_type = csf_h264_nalu::h264_nalu_nal;

		};

	}

}
#endif // !defined(CSF_HIOBJECT_VIDEO_H_INCLUDED_)
