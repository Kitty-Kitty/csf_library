/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hiprocessor.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 8:46:35
*
*Description: Class(csf_hiprocessor) 表示海思媒体处理器，主要用于处理海思相关
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HIPROCESSOR_H_INCLUDED_)
#define CSF_HIPROCESSOR_H_INCLUDED_

#include "csf_mdpipe_manager.hpp"
#include "csf_hichannel_manager.hpp"
#include "csf_interface.hpp"
#include "hiconfigure.hpp"
#include "csf_hisystem.hpp"

using namespace ec::core;

namespace ec
{
	namespace core
	{
		class csf_mp4recoder;
		/**
		 * 表示海思媒体处理器，主要用于处理海思相关
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 8:46:35
		 */
		class csf_hiprocessor : public csf::core::module::csf_interface
		{

		public:
			csf_hiprocessor();
			virtual ~csf_hiprocessor();

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
			 * 表示处理器中包含的媒体通道管理器，方便媒体通道管理。
			 */
			inline csf_hichannel_manager& get_hichannel_manager() {

				return m_hichannel_manager;
			}
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
			/**
			* 表示处理器所拥有的所有配置信息
			*/
			inline hiconfigure& get_hiconf() {

				return m_hiconf;
			}
		private:
			/**
			* 功能：
			*    启动海思通道对象。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param hichannel    表示需要被启动的hichannel对象
			* @param hiconfigure    表示hichannel对象对应的配置信息对象
			*/
			virtual csf::core::base::csf_int32 start_hichannel(csf_hichannel * hichannel, hichannel_conf* hiconfigure);
			/**
			* 功能：
			*    停止指定名称的通道对象。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param name    表示需要停止的通道对象名称
			*/
			virtual csf::core::base::csf_int32 stop_hichannel(const std::string name);
			/**
			* 功能：
			*    停止海思通道对象。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param hichannel    表示需要被启动的hichannel对象
			*/
			virtual csf::core::base::csf_int32 stop_hichannel(csf_hichannel * hichannel);
			/**
			* 功能：
			*    启动音频采集编码通道。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 start_hiai(const csf_configure_manager * conf_mg = csf_nullptr);
			/**
			* 功能：
			*    停止音频采集编码通道。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 stop_hiai(const csf_configure_manager * conf_mg = csf_nullptr);
			/**
			* 功能：
			*    启动视频采集编码通道。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 start_hivi(const csf_configure_manager * conf_mg = csf_nullptr);
			/**
			* 功能：
			*    停止视频采集编码通道。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 stop_hivi(const csf_configure_manager * conf_mg = csf_nullptr);
			/**
			* 功能：
			*    启动海思系统
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*/
			virtual csf::core::base::csf_int32 start_hisystem();

			/**
			* 功能：
			*    停止海思系统
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*/
			virtual csf::core::base::csf_int32 stop_hisystem();
			/**
			* 功能：
			*    启动数据记录保存对象。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 start_recoder(const csf_configure_manager * conf_mg = csf_nullptr);
			/**
			* 功能：
			*    停止数据记录保存对象。
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 stop_recoder(const csf_configure_manager * conf_mg = csf_nullptr);
			/**
			* 表示海思系统处理类
			*/
			inline csf_hisystem& get_hisystem() {

				return m_hisystem;
			}
			/**
			* 表示mp4文件保存对象
			*/
			inline csf_mp4recoder* get_mp4recoder() {

				return m_mp4recoder;
			}
			/**
			* 表示mp4文件保存对象
			*
			* @param newVal
			*/
			inline void set_mp4recoder(csf_mp4recoder* newVal) {

				m_mp4recoder = newVal;
			}
		private:
			/**
			 * 表示处理器中包含的媒体通道管理器，方便媒体通道管理。
			 */
			csf_hichannel_manager m_hichannel_manager;
			/**
			* 表示处理器所拥有的所有配置信息
			*/
			hiconfigure m_hiconf;
			/**
			* 表示海思系统处理类
			*/
			csf_hisystem m_hisystem;
			/**
			* 表示mp4文件保存对象
			*/
			csf_mp4recoder* m_mp4recoder = NULL;
		};

	}

}
#endif // !defined(CSF_HIPROCESSOR_H_INCLUDED_)
