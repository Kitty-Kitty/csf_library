/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mp4recoder.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 12:47:48
*
*Description: Class(csf_mp4recoder) 表示mp4的记录功能实现
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MP4RECODER_H_INCLUDED_)
#define CSF_MP4RECODER_H_INCLUDED_

#include "csf_interface.hpp"
#include "csf_hiprocessor.hpp"
#include "csf_thread.hpp"

using namespace csf::core::utils;

namespace ec
{
	namespace core
	{
		/**
		 * 表示mp4的记录功能实现
		 * @author f
		 * @version 1.0
		 * @created 07-12月-2019 12:47:48
		 */
		class csf_mp4recoder : public csf::core::module::csf_interface
		{

		public:
			csf_mp4recoder()
				: m_processor(NULL)
				, m_thread(NULL) {

			}
			/**
			* 功能：
			*    根据processor对象创建一个mp4recoder
			*
			* @param processor    表示海思处理对象，可以从处理对象中获取需要的所需要的流内容
			*
			*/
			explicit csf_mp4recoder(csf_hiprocessor* processor)
				: m_processor(processor)
				, m_thread(NULL) {

			}

			virtual ~csf_mp4recoder() {

			}

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
			/**
			* 表示海思处理对象，可以从处理对象中获取需要的所需要的流内容
			*/
			inline csf_hiprocessor* get_processor() {

				return m_processor;
			}


		protected:
			/**
			* 表示海思处理对象，可以从处理对象中获取需要的所需要的流内容
			*
			* @param newVal
			*/
			inline void set_processor(csf_hiprocessor* newVal) {

				m_processor = newVal;
			}
			/**
			* 表示当前处理槽数据的线程
			*/
			inline csf_thread* get_thread() {

				return m_thread;
			}
			/**
			* 表示当前处理槽数据的线程
			*
			* @param newVal
			*/
			inline void set_thread(csf_thread* newVal) {

				m_thread = newVal;
			}
		private:
			/**
			* 表示海思处理对象，可以从处理对象中获取需要的所需要的流内容
			*/
			csf_hiprocessor* m_processor = NULL;
			/**
			* 表示当前处理槽数据的线程
			*/
			csf_thread* m_thread = NULL;
		};

	}

}
#endif // !defined(CSF_MP4RECODER_H_INCLUDED_)
