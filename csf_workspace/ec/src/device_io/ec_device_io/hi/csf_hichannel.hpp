/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hichannel.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:50:14
*
*Description: Class(csf_hichannel) 表示海思媒体流处理类型
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HICHANNEL_H_INCLUDED_)
#define CSF_HICHANNEL_H_INCLUDED_

#include "csf_hichannel_interface.hpp"
#include "csf_mdpipe.hpp"

using namespace ec::core;

namespace ec
{
	namespace core
	{
		/**
		 * 表示海思媒体流处理类型
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:50:14
		 */
		class csf_hichannel : public ec::core::csf_hichannel_interface
		{

		public:
			csf_hichannel();
			virtual ~csf_hichannel();

			/**
			 * 功能：
			 *    使用参数创建对象
			 * 
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			inline explicit csf_hichannel(csf_hiprocessor* hiproc, const hichannel_conf * hiconf = csf_nullptr)
				: m_processor(hiproc)
				, m_configure(const_cast<hichannel_conf *>(hiconf)) {

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
			 * 表示通道所属的处理模块
			 */
			inline csf_hiprocessor* get_processor() {

				return m_processor;
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
			 * 表示通道所属的处理模块
			 * 
			 * @param newVal
			 */
			inline void set_processor(csf_hiprocessor* newVal) {

				m_processor = newVal;
			}
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
			 * 表示通道配置信息对象
			 */
			inline hichannel_conf* get_configure() {

				return m_configure;
			}
			/**
			 * 表示当前媒体通道的数据流通道
			 */
			inline csf_mdpipe& get_mdpipe() {

				return m_mdpipe;
			}
			/**
			 * 表示通道配置信息对象
			 * 
			 * @param newVal
			 */
			inline void set_configure(hichannel_conf* newVal) {

				m_configure = newVal;
			}

		private:
			/**
			 * 表示当前媒体通道的数据流通道
			 */
			csf_mdpipe m_mdpipe;
			/**
			 * 表示通道所属的处理模块
			 */
			csf_hiprocessor* m_processor = NULL;
			/**
			 * 表示通道配置信息对象
			 */
			hichannel_conf* m_configure = NULL;

		};

	}

}
#endif // !defined(CSF_HICHANNEL_H_INCLUDED_)
