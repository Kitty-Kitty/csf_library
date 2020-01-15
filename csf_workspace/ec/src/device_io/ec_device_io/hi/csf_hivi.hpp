/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hivi.hpp
*
*Version: 1.0
*
*Date: 05-12月-2019 11:06:21
*
*Description: Class(csf_hivi) 表示视频编码处理类，采集获取视频数据
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HIVI_H_INCLUDED_)
#define CSF_HIVI_H_INCLUDED_

#include "csf_hivdev.hpp"
#include "hivideo_channel_conf.hpp"
#include "csf_hipool_video.hpp"
#include "csf_hiobject_video.hpp"

#ifdef WIN32
#define FILE_TEST 1
#endif

namespace ec
{
	namespace core
	{
		/**
		 * 表示视频编码处理类，采集获取视频数据
		 * @author f
		 * @version 1.0
		 * @created 05-12月-2019 11:06:21
		 */
		class csf_hivi : public ec::core::csf_hivdev
		{
		public:
			typedef struct hi_vdev_attribute_s
			{
				int						dev_id;				//表示设备id
				int						dev_channel;		//表示设备通道id
				int						coder_channel;		//表示编码通道id
#if defined(HI_BUILD_PLATFORM)
				PAYLOAD_TYPE_E			payload;			//表示有效载荷
				HI_U32					profile;			//表示场景类型定义
				ROTATE_E				rotate;				//表示视频画面旋转
				VIDEO_NORM_E			video_norm;			//表示视频模式
				PIC_SIZE_E				pic_size;			//表示视频画面大小
				SAMPLE_RC_E				rc;					//表示压缩方式
				VPSS_GRP				vpss_group;			//表示vpss组
				VPSS_GRP_ATTR_S			vpss_group_attr;	//表示vpss组属性
				VPSS_CHN				vpss_channel;		//表示vpss通道id
				VPSS_CHN_ATTR_S			vpss_channel_attr;	//表示vpss通道属性
				VPSS_CHN_MODE_S			vpss_channel_mode;	//表示vpss通道工作模式信息
				VENC_GOP_MODE_E			gop_mode;			//表示定义Gop Mode类型
				VENC_CHN_ATTR_S			venc_channel_attr;	//表示编码器通道属性
				union
				{
					VENC_GOP_ATTR_S		gop_attr;			//表示编码通道属性
				};
				union
				{
					SAMPLE_VI_CONFIG_S	config;				//表示视频采样配置内容
				};
#endif
			}hi_vdev_attribute;

		public:
			csf_hivi();
			/**
			* 功能：
			*    使用参数创建对象
			*
			* @param hiproc    表示海思处理模块对象
			* @param hiconf    表示海思通道配置信息
			*/
			explicit csf_hivi(csf_hiprocessor* hiproc, const hichannel_conf * hiconf = csf_nullptr);
			virtual ~csf_hivi();

			/**
			 * 表示视频采集参数配置
			 */
			inline hivideo_channel_conf* get_viconf() {

				return m_viconf;
			}
			/**
			 * 功能：
			 *    初始化通道
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 *
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			virtual int init(csf_hiprocessor* hiproc, const hichannel_conf * hiconf);
			/**
			 * 表示视频采集参数配置
			 *
			 * @param newVal
			 */
			inline void set_viconf(hivideo_channel_conf* newVal) {

				m_viconf = newVal;
			}
			/**
			 * 功能：
			 *    启动通道
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 *
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			virtual int start(csf_hiprocessor* hiproc, const hichannel_conf * hiconf);
			/**
			 * 功能：
			 *    停止通道
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 *
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			virtual int stop(csf_hiprocessor* hiproc, const hichannel_conf * hiconf);


		protected:
			/**
			 * 功能：
			 *    初始化设备
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 */
			virtual bool init_dev();
			/**
			 * 功能：
			 *    启动设备
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 */
			virtual bool start_dev();
			/**
			 * 功能：
			 *    停止设备
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 */
			virtual bool stop_dev();
			/**
			 * 功能：
			 *    初始化编解码器
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 */
			virtual bool init_coder();
			/**
			 * 功能：
			 *    启动编解码器
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 */
			virtual bool start_coder();
			/**
			 * 功能：
			 *    启动编解码处理线程
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param hichannel    表示当前的csf_hivdev设备对象指针
			 */
			virtual bool start_coder_thread(csf_hivdev* hichannel);
			/**
			 * 功能：
			 *    编解码线程处理函数
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param hichannel    表示当前的csf_hivdev设备对象指针
			 */
			virtual bool coder_thread_process(csf_hivdev* hichannel);

#ifdef FILE_TEST
			unsigned char *preload(const char *path, int *data_size);
			int get_nal_size(unsigned char *buf, int size);
			/**
			* 功能：
			*    测试编解码线程处理函数
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param hichannel    表示当前的csf_hivdev设备对象指针
			*/
			virtual bool test_coder_thread_process(csf_hivdev* hichannel);
#endif
			/**
			 * 功能：
			 *    绑定设备和编码器设备
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param id    表示设备id
			 * @param channel    表示设备通道
			 * @param coder_channel    表示编码器设备通道
			 */
			virtual bool bind_dev_coder(int id, int channel, int coder_channel);
			/**
			 * 功能：
			 *    解除绑定设备和编码器设备
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param id    表示设备id
			 * @param channel    表示设备通道
			 * @param coder_channel    表示编码器设备通道
			 */
			virtual bool unbind_dev_coder(int id, int channel, int coder_channel);
			/**
			* 功能：
			*    绑定vi、vpss、venc设备
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool bind_vi_vpss_venc();
			/**
			* 功能：
			*    解除绑定vi、vpss、venc设备
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool unbind_vi_vpss_venc();
			/**
			 * 功能：
			 *    停止编解码器
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 */
			virtual bool stop_coder();
			/**
			* 功能：
			*    停止编解码处理线程
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param hichannel    表示当前的csf_hivdev设备对象指针
			*/
			virtual bool stop_coder_thread(csf_hivdev* hichannel);
			/**
			* 功能：
			*    初始化视频处理子系统
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool init_vpss();
			/**
			* 功能：
			*    启动视频处理子系统
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool start_vpss();
			/**
			* 功能：
			*    停止视频处理子系统
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool stop_vpss();
		private:
			/**
			* 表示处理需要的设备参数
			*/
			inline hi_vdev_attribute& get_attribute() {

				return m_attribute;
			}
			/**
			* 表示处理需要的设备参数
			*
			* @param newVal
			*/
			inline void set_attribute(hi_vdev_attribute& newVal) {

				m_attribute = newVal;
			}
#if defined(HI_BUILD_PLATFORM)
			/**
			* 功能：
			*    从逻辑内存中获取流数据
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param hipool    表示保存数据的内存池
			* @param mdslot    表示获取后的数据存放入的数据槽
			* @param stream    表示海思的流描述信息结构
			*/
			bool get_stream_by_memory_stream(csf_hipool* hipool, csf_mdslot* mdslot, VENC_STREAM_S* stream);
			/**
			* 功能：
			*    从物理内存中获取流数据
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param hipool    表示保存数据的内存池
			* @param mdslot    表示获取后的数据存放入的数据槽
			* @param stream_buf_info    定义码流 buffer信息的结构体
			* @param stream    表示海思的流描述信息结构
			*/
			bool get_stream_by_physical_stream(csf_hipool* hipool
				, csf_mdslot* mdslot
				, VENC_STREAM_BUF_INFO_S* stream_buf_info
				, VENC_STREAM_S* stream);
			/**
			* 功能：
			*    设置nalu帧数据的类型
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param object    表示需要被设置的帧数据对象
			* @param data_type    表示海思指定的帧类型
			*/
			void set_nalu_type(csf_hiobject_video* object, VENC_DATA_TYPE_U &data_type);
#endif
		private:
			/**
			 * 表示视频采集参数配置
			 */
			hivideo_channel_conf* m_viconf = NULL;
			/**
			* 表示处理需要的设备参数
			*/
			hi_vdev_attribute m_attribute{ 0, };

		};

	}

}
#endif // !defined(CSF_HIVI_H_INCLUDED_)
