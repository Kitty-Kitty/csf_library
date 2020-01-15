/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hiai.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:50:13
*
*Description: Class(csf_hiai) 表示音频编码处理类，采集获取音频数据
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HIAI_H_INCLUDED_)
#define CSF_HIAI_H_INCLUDED_

#include "csf_hiadev.hpp"
#include "csf_hiprocessor.hpp"
#include "hiaudio_aiconf.hpp"

//#define HISIV_AAC

namespace ec
{
	namespace core
	{
		/**
		 * 表示音频编码处理类，采集获取音频数据
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:50:13
		 */
		class csf_hiai : public ec::core::csf_hiadev
		{
		public:
			typedef struct hi_adev_attribute_s
			{
				int						dev_id;				//表示设备id
				int						dev_channel;		//表示设备通道id
				int						coder_channel;		//表示编码通道id
#if defined(HI_BUILD_PLATFORM)
				PAYLOAD_TYPE_E			payload_type;		//表示编码类型
				AIO_ATTR_S				aio_attr;			//表示ai和ao属性
				union
				{
					AENC_CHN_ATTR_S		aenc_attr;			//表示编码通道属性
					ADEC_CHN_ATTR_S		adec_attr;			//表示解码通道属性
				};
				union
				{
					AENC_ATTR_ADPCM_S	aenc_adpcm;			//表示编码adpcm属性
					AENC_ATTR_G711_S	aenc_g711;			//表示编码g711属性
					AENC_ATTR_G726_S	aenc_g726;			//表示编码g726属性
					AENC_ATTR_LPCM_S	aenc_lpcm;			//表示编码lpcm属性
#ifdef HISIV_AAC
					AENC_ATTR_AAC_S		aenc_aac;			//表示编码aac属性
#endif
					ADEC_ATTR_ADPCM_S	adec_adpcm;			//表示解码adpcm属性
					ADEC_ATTR_G711_S	adec_g711;			//表示解码g711属性
					ADEC_ATTR_G726_S	adec_g726;			//表示解码g726属性
					ADEC_ATTR_LPCM_S	adec_lpcm;			//表示解码lpcm属性
				};
#endif
			}hi_adev_attribute;

		public:
			virtual ~csf_hiai();

			/**
			 * 功能：
			 *    使用参数创建对象
			 *
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			explicit csf_hiai(csf_hiprocessor* hiproc, const hichannel_conf * hiconf);
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
			*    启动设备的复杂实现
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			bool start_dev_large();
			/**
			 * 功能：
			 *    启动设备重新采样处理
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param id    表示设备id
			 * @param channel    表示设备通道
			 */
			virtual bool start_dev_resample(int id, int channel);
			/**
			 * 功能：
			 *    启动设备质量增强功能。
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param id    表示设备id
			 * @param channel    表示设备通道
			 */
			virtual bool start_dev_vqe(int id, int channel);
			/**
			* 功能：
			*    设置设备的音量大小。
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param id    表示设备id
			* @param channel    表示设备通道
			* @param volume    表示音频音量大小数值
			*/
			virtual bool set_dev_vqe_volume(int id, int channel, int volume);
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
			*    停止设备复杂实现
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool stop_dev_large();
			/**
			 * 功能：
			 *    停止设备重新采样处理
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param id    表示设备id
			 * @param channel    表示设备通道
			 */
			virtual bool stop_dev_resample(int id, int channel);
			/**
			 * 功能：
			 *    停止设备质量增强功能。
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param id    表示设备id
			 * @param channel    表示设备通道
			 */
			virtual bool stop_dev_vqe(int id, int channel);
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
			*    初始化编码器参数
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param adev_attr    表示需要被初始化参数
			*/
			virtual bool init_coder(hi_adev_attribute& adev_attr);
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
			*    启动编解码器的复杂实现
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			bool start_coder_large();
			/**
			 * 功能：
			 *    启动编解码处理线程
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param hichannel    表示当前的csf_hiadev设备对象指针
			 */
			virtual bool start_coder_thread(csf_hiadev* hichannel);
			/**
			 * 功能：
			 *    编解码线程处理函数
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param hichannel    表示当前的csf_hiadev设备对象指针
			 */
			virtual bool coder_thread_process(csf_hiadev* hichannel);
			/**
			* 功能：
			*    测试编解码线程处理函数
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*
			* @param hichannel    表示当前的csf_hiadev设备对象指针
			*/
			virtual bool test_coder_thread_process(csf_hiadev* hichannel);
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
			 *    停止编解码器
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 */
			virtual bool stop_coder();
			/**
			* 功能：
			*    停止编解码器复杂实现
			* 返回：
			*    true：表示成功；
			*    false：表示失败；
			*/
			virtual bool stop_coder_large();
			/**
			 * 功能：
			 *    停止编解码处理线程
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param hichannel    表示当前的csf_hiadev设备对象指针
			 */
			virtual bool stop_coder_thread(csf_hiadev* hichannel);
		private:
			/**
			* 表示ai采集参数配置
			*/
			inline hiaudio_aiconf* get_aiconf() {

				return m_aiconf;
			}
			/**
			* 表示ai采集参数配置
			*
			* @param newVal
			*/
			inline void set_aiconf(hiaudio_aiconf* newVal) {

				m_aiconf = newVal;
			}
			/**
			* 表示当前通道所属的通道处理器
			*/
			inline csf_hiprocessor* get_processor() {

				return m_processor;
			}
			/**
			* 表示当前通道所属的通道处理器
			*
			* @param newVal
			*/
			inline void set_processor(csf_hiprocessor* newVal) {

				m_processor = newVal;
			}
			/**
			* 表示编码器通道数量
			*/
			inline int get_coder_channel_count() {

				return m_coder_channel_count;
			}
			/**
			* 表示通道数量
			*/
			inline int get_dev_channel_count() {

				return m_dev_channel_count;
			}
			/**
			* 表示编码器通道数量
			*
			* @param newVal
			*/
			inline void set_coder_channel_count(int newVal) {

				m_coder_channel_count = newVal;
			}
			/**
			* 表示通道数量
			*
			* @param newVal
			*/
			inline void set_dev_channel_count(int newVal) {

				m_dev_channel_count = newVal;
			}
			/**
			* 表示当前需要被设置的设备参数
			*/
			inline hi_adev_attribute& get_attribute() {

				return m_attribute;
			}
		private:
			/**
			* 表示ai采集参数配置
			*/
			hiaudio_aiconf* m_aiconf = NULL;
			/**
			* 表示当前通道所属的通道处理器
			*/
			csf_hiprocessor* m_processor = NULL;
			/**
			* 表示通道数量
			*/
			int m_dev_channel_count = 1;
			/**
			* 表示编码器通道数量
			*/
			int m_coder_channel_count = 1;
			/**
			* 表示当前需要被设置的设备参数
			*/
			hi_adev_attribute m_attribute{ 0, };
		};

	}

}
#endif // !defined(CSF_HIAI_H_INCLUDED_)
