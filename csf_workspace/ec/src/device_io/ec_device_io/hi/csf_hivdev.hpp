/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hivdev.hpp
*
*Version: 1.0
*
*Date: 05-12月-2019 11:06:20
*
*Description: Class(csf_hivdev) 表示视频采集编码处理类
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HIVDEV_H_INCLUDED_)
#define CSF_HIVDEV_H_INCLUDED_

#include "csf_thread.hpp"
#include "csf_hichannel.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示视频采集编码处理类
		 * @author f
		 * @version 1.0
		 * @created 05-12月-2019 11:06:20
		 */
		class csf_hivdev : public ec::core::csf_hichannel
		{

		public:
			csf_hivdev();
			virtual ~csf_hivdev();

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
			/**
			 * 功能：
			 *    使用参数创建对象
			 *
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			inline explicit csf_hivdev(csf_hiprocessor* hiproc, const hichannel_conf * hiconf = csf_nullptr)
				: csf_hichannel(hiproc, hiconf) {

			}

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
			 *    停止编解码处理线程
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param hichannel    表示当前的csf_hivdev设备对象指针
			 */
			virtual bool stop_coder_thread(csf_hivdev* hichannel);
			/**
			 * 表示处理线程对象指针
			 */
			inline csf_thread* get_thread() {

				return m_thread;
			}
			/**
			 * 表示处理线程对象指针
			 *
			 * @param newVal
			 */
			inline void set_thread(csf_thread* newVal) {

				m_thread = newVal;
			}

		private:
			/**
			 * 表示处理线程对象指针
			 */
			csf_thread* m_thread = NULL;
		};

	}

}
#endif // !defined(CSF_HIVDEV_H_INCLUDED_)
