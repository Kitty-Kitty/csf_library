/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mp4muxer_file.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 20:09:59
*
*Description: Class(csf_mp4muxer_file) 表示mp4muxer文件保存处理
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MP4MUXER_FILE_H_INCLUDED_)
#define CSF_MP4MUXER_FILE_H_INCLUDED_

#include <stdio.h>
#include <iostream>
#include "csf_mdbuffer.hpp"
#include "csf_mdframe.hpp"
#include "csf_mp4_file.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示mp4muxer文件保存处理
		 * @author f
		 * @version 1.0
		 * @updated 07-12月-2019 20:45:31
		 */
		class csf_mp4muxer_file : public csf_mp4_file
		{

		public:
			csf_mp4muxer_file();
			virtual ~csf_mp4muxer_file();

			/**
			 * 表示视频长度，单位为秒
			 */
			inline int get_duration() {

				return m_duration;
			}
			/**
			 * 表示视频长度，单位为秒
			 *
			 * @param newVal
			 */
			inline void set_duration(int newVal) {

				m_duration = newVal;
			}
			/**
			 * 表示视频分辨率宽度
			 */
			inline int get_width() {

				return m_width;
			}
			/**
			 * 表示视频分辨率宽度
			 *
			 * @param newVal
			 */
			inline void set_width(int newVal) {

				m_width = newVal;
			}
			/**
			 * 表示视频分辨率宽度
			 */
			inline int get_height() {

				return m_height;
			}
			/**
			 * 表示视频分辨率宽度
			 *
			 * @param newVal
			 */
			inline void set_height(int newVal) {

				m_height = newVal;
			}
			/**
			 * 表示视频帧率
			 */
			inline int get_frame_rate() {

				return m_frame_rate;
			}
			/**
			 * 表示视频帧率
			 *
			 * @param newVal
			 */
			inline void set_frame_rate(int newVal) {

				m_frame_rate = newVal;
			}
			/**
			 * 表示视频I帧之间的间隔
			 */
			inline int get_gop() {

				return m_gop;
			}
			/**
			 * 表示视频I帧之间的间隔
			 *
			 * @param newVal
			 */
			inline void set_gop(int newVal) {

				m_gop = newVal;
			}
			/**
			 * 表示音频通道数量
			 */
			inline int get_channel_number() {

				return m_channel_number;
			}
			/**
			 * 表示音频通道数量
			 *
			 * @param newVal
			 */
			inline void set_channel_number(int newVal) {

				m_channel_number = newVal;
			}
			/**
			 * 表示音频采样率
			 */
			inline int get_sample_rate() {

				return m_sample_rate;
			}
			/**
			 * 表示音频采样率
			 *
			 * @param newVal
			 */
			inline void set_sample_rate(int newVal) {

				m_sample_rate = newVal;
			}
			/**
			 * 表示音频采样精度
			 */
			inline int get_sample_bits() {
				return m_sample_bits;
			}
			/**
			 * 表示音频采样精度
			 *
			 * @param newVal
			 */
			inline void set_sample_bits(int newVal) {
				m_sample_bits = newVal;
			}
			/**
			 * 表示音频采样点数
			 */
			inline int get_sample_number() {
				return m_sample_number;
			}
			/**
			 * 表示音频采样点数
			 *
			 * @param newVal
			 */
			inline void set_sample_number(int newVal) {
				m_sample_number = newVal;
			}
			/**
			 * 表示保存的当前mp4流的sps数据内容，数据缓存大小为32字节
			 */
			inline csf_buffer& get_sps() {

				return m_sps;
			}
			/**
			 * 表示保存的当前mp4流的sps数据内容，数据缓存大小为32字节
			 *
			 * @param newVal
			 */
			inline void set_sps(csf_buffer& newVal) {

				m_sps = newVal;
			}
			/**
			 * 表示保存的当前mp4流的sps数据内容，数据缓存大小为32字节
			 */
			inline csf_buffer& get_pps() {

				return m_pps;
			}
			/**
			 * 表示保存的当前mp4流的sps数据内容，数据缓存大小为32字节
			 *
			 * @param newVal
			 */
			inline void set_pps(csf_buffer& newVal) {

				m_pps = newVal;
			}
			/**
			 * 表示需要处理的mp4muxer对象
			 */
			inline void* get_mp4muxer() {

				return m_mp4muxer;
			}
			/**
			 * 表示需要处理的mp4muxer对象
			 *
			 * @param newVal
			 */
			inline void set_mp4muxer(void* newVal) {

				m_mp4muxer = newVal;
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
			inline bool set_video(int duration, int width, int height, int frame_rate, int gop) {
				set_duration(duration);
				set_width(width);
				set_height(height);
				set_frame_rate(frame_rate);
				set_gop(gop);
				set_max_frames(duration * frame_rate);
				return true;
			}
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
			inline bool set_audio(int channel_number, int sample_rate, int sample_bits, int sample_number) {
				set_channel_number(channel_number);
				set_sample_rate(sample_rate);
				set_sample_bits(sample_bits);
				set_sample_number(sample_number);
				return true;
			}
			/**
			 * 功能：
			 *    创建一个新的mp4文件
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 *
			 * @param name    表示需要创建的文件名称
			 */
			bool open(std::string name);
			/**
			 * 功能：
			 *    写入视频帧数据
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 *
			 * @param mdframe_ptr
			 */
			bool write_video(csf_mdframe_ptr mdframe_ptr);
			/**
			 * 功能：
			 *    写入音频帧数据
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 *
			 * @param mdframe_ptr
			 */
			bool write_audio(csf_mdframe_ptr mdframe_ptr);
			/**
			 * 功能：
			 *    关闭文件
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 */
			bool close();
			/**
			 * 表示当前文件写入的帧数量
			 */
			inline int get_frames() {

				return m_frames;
			}
			/**
			 * 表示当前文件写入的帧数量
			 *
			 * @param newVal
			 */
			inline void set_frames(int newVal) {

				m_frames = newVal;
			}
			/**
			 * 表示当前写入的文件大小，单位：字节数（B）
			 */
			inline int get_size() {

				return m_size;
			}
			/**
			 * 表示当前写入的文件大小，单位：字节数（B）
			 *
			 * @param newVal
			 */
			inline void set_size(int newVal) {

				m_size = newVal;
			}
			/**
			 * 表示当前文件写入的最大帧数量
			 */
			inline int get_max_frames() {

				return m_max_frames;
			}
			/**
			 * 表示当前文件写入的最大帧数量
			 *
			 * @param newVal
			 */
			inline void set_max_frames(int newVal) {

				m_max_frames = newVal;
			}
			/**
			 * 表示当前写入的最大文件大小，单位：字节数（B）
			 */
			inline int get_max_size() {

				return m_max_size;
			}
			/**
			 * 表示当前写入的最大文件大小，单位：字节数（B）
			 *
			 * @param newVal
			 */
			inline void set_max_size(int newVal) {

				m_max_size = newVal;
			}
			/**
			 * 功能：
			 *    重置文件保存对象
			 * 返回：
			 *    true ： 表示成功
			 *    false： 表示失败
			 */
			bool reset();
			/**
			* 功能：
			*    表示文件是否已经保存完成
			* 返回：
			*    true ： 表示成功
			*    false： 表示失败
			*/
			virtual bool isfinish();
			/**
			* 功能：
			*    表示文件是否已经打开
			* 返回：
			*    true ： 表示成功
			*    false： 表示失败
			*/
			inline bool isopen() {

				if (get_mp4muxer()) {
					return true;
				}
				return false;
			}
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
			int compare_pts(csf_mdframe_ptr video_ptr, csf_mdframe_ptr audio_ptr);
		protected:
			/**
			* 功能：
			*    设置sps和pps数据
			* 返回：
			*    true ： 表示成功
			*    false： 表示失败
			*/
			bool set_mp4muxer_spspps();
			/**
			* 功能：
			*    设置sps和pps缓存数据
			* 返回：
			*    true ： 表示成功
			*    false： 表示失败
			*
			* @param buf    表示数据内存地址
			* @param len    表示数据的长度
			*/
			bool set_spspps(unsigned char* buf, unsigned int len);
			/**
			* 功能：
			*    设置aac的dsi数据
			* 返回：
			*    true ： 表示成功
			*    false： 表示失败
			*/
			bool set_aacdecspecinfo();
			/**
			* 表示是否需要设置sps\pps数据，用来初始化mp4文件。其中true表示需要设置；false表示不需要设置；
			*/
			inline bool isspspps() {

				return m_spspps;
			}
			/**
			* 表示是否需要设置sps\pps数据，用来初始化mp4文件。其中true表示需要设置；false表示不需要设置；
			*
			* @param newVal
			*/
			inline void set_spspps(bool newVal) {

				m_spspps = newVal;
			}
			/**
			* 功能：
			*    表示帧数量已经满足
			* 返回：
			*    true ： 表示成功
			*    false： 表示失败
			*/
			inline bool frame_finish() {

				if (get_frames() >= get_max_frames()) {
					return true;
				}
				return false;
			}
			/**
			* 功能：
			*    表示文件大小已经满足
			* 返回：
			*    true ： 表示成功
			*    false： 表示失败
			*/
			inline bool size_finish() {

				if (get_size() >= get_max_size()) {
					return true;
				}
				return false;
			}
			/**
			* 表示媒体文件的起始时间戳
			*/
			inline csf_int64 get_base_pts() {

				return m_base_pts;
			}
			/**
			* 表示媒体文件的起始时间戳
			*
			* @param newVal
			*/
			inline void set_base_pts(csf_int64 newVal) {

				m_base_pts = newVal;
			}
		private:
			/**
			 * 表示视频长度，单位为秒
			 */
			int m_duration = 300;
			/**
			 * 表示视频分辨率宽度
			 */
			int m_width = 1920;
			/**
			 * 表示视频分辨率高度
			 */
			int m_height = 1080;
			/**
			 * 表示视频帧率
			 */
			int m_frame_rate = 30;
			/**
			 * 表示视频I帧之间的间隔
			 */
			int m_gop = 30;
			/**
			 * 表示音频通道数量
			 */
			int m_channel_number = 2;
			/**
			 * 表示音频采样率
			 */
			int m_sample_rate = 44100;
			/**
			 * 表示音频采样精度
			 */
			int m_sample_bits = 16;
			/**
			 * 表示音频采样点数
			 */
			int m_sample_number = 1024;
			/**
			 * 表示保存的当前mp4流的sps数据内容，数据缓存大小为32字节
			 */
			csf_buffer m_sps;
			/**
			 * 表示保存的当前mp4流的pps数据内容，数据缓存大小为32字节
			 */
			csf_buffer m_pps;
			/**
			 * 表示需要处理的mp4muxer对象
			 */
			void* m_mp4muxer = NULL;
			/**
			 * 表示当前文件写入的帧数量
			 */
			int m_frames = 0;
			/**
			 * 表示当前写入的文件大小，单位：字节数（B）
			 */
			int m_size = 0;
			/**
			 * 表示当前文件写入的最大帧数量
			 */
			int m_max_frames = 9000;
			/**
			 * 表示当前写入的最大文件大小，单位：字节数（B）
			 */
			int m_max_size = 200 * 1024 * 1024;
			/**
			* 表示是否需要设置sps\pps数据，用来初始化mp4文件。其中true表示需要设置；false表示不需要设置；
			*/
			bool m_spspps = true;
			/**
			* 表示媒体文件的起始时间戳
			*/
			csf_int64 m_base_pts = 0;
#ifdef FILE_TEST
			FILE *m_fd = NULL;
#endif
		};

	}

}
#endif // !defined(CSF_MP4MUXER_FILE_H_INCLUDED_)
