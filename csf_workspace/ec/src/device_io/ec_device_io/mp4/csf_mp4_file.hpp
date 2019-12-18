/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mp4_file.hpp
*
*Version: 1.0
*
*Date: 11-12月-2019 18:31:40
*
*Description: Class(csf_mp4_file) 表示mp4文件保存处理
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MP4_FILE_H_INCLUDED_)
#define CSF_MP4_FILE_H_INCLUDED_

#include <iostream>
#include "csf_mdframe.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示mp4文件保存处理
		 * @author f
		 * @version 1.0
		 * @created 11-12月-2019 18:31:40
		 */
		class csf_mp4_file
		{

		public:
			csf_mp4_file() {

			}
			virtual ~csf_mp4_file() {

			}

			/**
			 * 功能：
			 *    设置视频参数信息
			 * 返回：
			 *    true ： 表示设置成功
			 *    false： 表示设置失败
			 * 
			 * @param duration    表示视频长度，单位为秒
			 * @param width    表示视频分辨率宽度
			 * @param height    表示视频分辨率高度
			 * @param frame_rate    表示视频帧率
			 * @param gop    表示视频I帧间隔
			 */
			virtual bool set_video(int duration, int width, int height, int frame_rate, int gop) = 0;
			/**
			 * 功能：
			 *    设置音频参数信息
			 * 返回：
			 *    true ： 表示设置成功
			 *    false： 表示设置失败
			 * 
			 * @param channel_number    表示音频通道数量
			 * @param sample_rate    表示音频采样率
			 * @param sample_bits    表示音频采样精度
			 * @param sample_number    表示音频采样点数
			 */
			virtual bool set_audio(int channel_number, int sample_rate, int sample_bits, int sample_number) = 0;
			/**
			 * 功能：
			 *    创建一个新的mp4文件
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 * 
			 * @param name    表示需要创建的文件名称
			 */
			virtual bool open(std::string name) = 0;
			/**
			 * 功能：
			 *    写入视频帧数据
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 * 
			 * @param mdframe_ptr
			 */
			virtual bool write_video(csf_mdframe_ptr mdframe_ptr) = 0;
			/**
			 * 功能：
			 *    写入音频帧数据
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 * 
			 * @param mdframe_ptr
			 */
			virtual bool write_audio(csf_mdframe_ptr mdframe_ptr) = 0;
			/**
			 * 功能：
			 *    关闭文件
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 */
			virtual bool close() = 0;
			/**
			 * 功能：
			 *    重置文件保存对象
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 */
			virtual bool reset() = 0;
			/**
			 * 功能：
			 *    表示文件是否已经保存完成
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 */
			virtual bool isfinish() = 0;
			/**
			 * 功能：
			 *    表示文件是否已经打开
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 */
			virtual bool isopen() = 0;
			/**
			 * 功能：
			 *    判断视频与音频时间戳的大小。根据时间戳大小返回不同的数值
			 * 返回：
			 *    1： 表示视频时间戳大于音频时间戳
			 *    0： 表示视频时间戳等于音频时间戳
			 *   -1： 表示视频时间戳小于音频时间戳
			 * 
			 * @param video_ptr
			 * @param audio_ptr
			 */
			virtual int compare_pts(csf_mdframe_ptr video_ptr, csf_mdframe_ptr audio_ptr) = 0;

		};

	}

}
#endif // !defined(CSF_MP4_FILE_H_INCLUDED_)
