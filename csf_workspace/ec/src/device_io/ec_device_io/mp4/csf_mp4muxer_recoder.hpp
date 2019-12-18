/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mp4muxer_recoder.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 13:15:01
*
*Description: Class(csf_mp4muxer_recoder) 表示使用mp4muxer库实现mp4的记录功能
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MP4MUXER_RECODER_H_INCLUDED_)
#define CSF_MP4MUXER_RECODER_H_INCLUDED_

#include "csf_mp4recoder.hpp"
#include "csf_mdbuffer.hpp"
#include "csf_mp4_file.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示使用mp4muxer库实现mp4的记录功能
		 * @author f
		 * @version 1.0
		 * @created 07-12月-2019 13:15:01
		 */
		class csf_mp4muxer_recoder : public ec::core::csf_mp4recoder
		{

		public:
			explicit csf_mp4muxer_recoder();
			/**
			* 功能：
			*    根据processor、video、audio对象，创建recoder对象
			*
			* @param processor    表示当前媒体的processor对象
			* @param video    表示视频通道
			*
			* @param audio    表示音频通道
			*/
			explicit csf_mp4muxer_recoder(csf_hiprocessor* processor
				, csf_hichannel* video
				, csf_hichannel* audio);

			virtual ~csf_mp4muxer_recoder();

			/**
			 * 功能：
			 *    模块初始化，进行模块启动前的准备工作。
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 *
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
			/**
			 * 功能：
			 *    模块启动，进行模块启动工作。表示模块已经正常运行。
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 *
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
			/**
			 * 功能：
			 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 *
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
		protected:
			/**
			* 功能：
			*    初始化mp4muxer处理相关内容
			* 返回：
			*    true ：表示成功
			*    false：表示失败
			*/
			virtual bool init_mp4muxer();
			/**
			* 功能：
			*    启动mp4muxer处理相关内容
			* 返回：
			*    true ：表示成功
			*    false：表示失败
			*/
			virtual bool start_mp4muxer();
			/**
			* 功能：
			*    停止mp4muxer处理相关内容
			* 返回：
			*    true ：表示成功
			*    false：表示失败
			*/
			virtual bool stop_mp4muxer();
			/**
			* 功能：
			*    启动mp4处理线程
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool start_thread();
			/**
			* 功能：
			*    mp4线程处理函数
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param recoder    表示mp4记录对象指针
			*/
			virtual bool thread_process(csf_mp4recoder* recoder);
			/**
			* 功能：
			*    停止mp4处理线程
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool stop_thread();
		private:

			/**
			* 表示当前需要处理的音频数据通道
			*/
			inline csf_hichannel* get_audio_channel() {

				return m_audio_channel;
			}
			/**
			* 表示当前需要处理的音频数据通道
			*
			* @param newVal
			*/
			inline void set_audio_channel(csf_hichannel* newVal) {

				m_audio_channel = newVal;
			}
			/**
			* 表示当前需要处理的视频数据通道
			*/
			inline csf_hichannel* get_video_channel() {

				return m_video_channel;
			}
			/**
			* 表示当前需要处理的视频数据通道
			*
			* @param newVal
			*/
			inline void set_video_channel(csf_hichannel* newVal) {

				m_video_channel = newVal;
			}
			/**
			* 表示当前mp4文件处理对象
			*/
			inline csf_mp4_file* get_mp4() {

				return m_mp4;
			}
			/**
			* 表示当前mp4文件处理对象
			*
			* @param newVal
			*/
			inline void set_mp4(csf_mp4_file* newVal) {

				m_mp4 = newVal;
			}
			/**
			* 功能：
			*    创建mp4文件
			* 返回：
			*    true ：表示成功
			*    false：表示失败
			*/
			bool open_mp4();
			/**
			* 功能：
			*    关闭mp4文件
			* 返回：
			*    true ：表示成功
			*    false：表示失败
			*/
			bool close_mp4();
		private:
			/**
			* 功能：
			*    生成一个格式化的文件名
			* 返回：
			*    一个文件名字符串
			*/
			std::string make_file_name();
			/**
			* 功能：
			*    生成保存视频文件的目录
			* 返回：
			*    true  ：  表示创建成功
			*    false ：  表示创建失败
			*/
			bool make_directory();
		private:
			/**
			* 表示当前mp4文件处理对象
			*/
			csf_mp4_file* m_mp4 = NULL;
			/**
			* 表示当前需要处理的视频数据通道
			*/
			csf_hichannel* m_video_channel = NULL;
			/**
			* 表示当前需要处理的音频数据通道
			*/
			csf_hichannel* m_audio_channel = NULL;
		};

	}

}
#endif // !defined(CSF_MP4MUXER_RECODER_H_INCLUDED_)
