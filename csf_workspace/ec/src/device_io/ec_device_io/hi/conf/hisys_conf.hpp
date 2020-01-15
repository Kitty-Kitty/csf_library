/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hisys_conf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:48
*
*Description: Class(hisys_conf) 表示海思系统配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HISYS_CONF_H_INCLUDED_)
#define HISYS_CONF_H_INCLUDED_

#include <iostream>
#include <map>

namespace ec
{
	namespace core
	{
		/**
		 * 表示海思系统配置信息
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:31:48
		 */
		class hisys_conf
		{
		public:
			/**
			* 平台的功耗场景类型
			* @author f
			* @version 1.0
			* @updated 05-12月-2019 10:27:05
			*/
			enum hiprofile_type
			{
				/**
				* 表示未知的功耗场景类型
				*/
				hiprofile_type_none = 0x00,
				/**
				* 表示1080p@30的功耗场景类型
				*/
				hiprofile_type_1080p_30 = 0x01,
				/**
				* 表示1080p@60的功耗场景类型
				*/
				hiprofile_type_1080p_60 = 0x02,
				/**
				* 表示3m@30的功耗场景类型
				*/
				hiprofile_type_3m_30 = 0x03,
				/**
				* 表示5m@30的功耗场景类型
				*/
				hiprofile_type_5m_30 = 0x04
				
			};

		public:
			hisys_conf();
			virtual ~hisys_conf();

			/**
			 * 表示系统内存的对齐方式
			 */
			inline int get_align_width() {

				return m_align_width;
			}
			/**
			 * 表示系统内存的对齐方式
			 * 
			 * @param newVal
			 */
			inline void set_align_width(int newVal) {

				m_align_width = newVal;
			}
			/**
			 * 最大内存池数量
			 */
			inline int get_max_pool_count() {

				return m_max_pool_count;
			}
			/**
			 * 最大内存池数量
			 * 
			 * @param newVal
			 */
			inline void set_max_pool_count(int newVal) {

				m_max_pool_count = newVal;
			}
			/**
			* 表示硬件平台的功耗场景类型
			*/
			inline std::string get_profile() {

				return m_profile;
			}
			/**
			* 表示硬件平台的功耗场景类型名称与索引的对应表
			*/
			inline const std::map<std::string, hiprofile_type>& get_profile_map() {

				return m_profile_map;
			}
			/**
			* 表示硬件平台的功耗场景类型
			*
			* @param newVal
			*/
			inline void set_profile(std::string newVal) {

				m_profile = newVal;
			}
			/**
			* 功能：
			*    获取当前对象的功耗场景类型索引
			* 返回：
			*    索引数值
			*/
			inline hiprofile_type get_profile_index() {
				return get_profile(get_profile());
			}
			/**
			* 功能：
			*     根据配置文件名称获取类型索引数值
			* 返回：
			*     索引数值
			*
			* @param name    表示功耗场景类型名称
			*/
			inline hiprofile_type get_profile(std::string name) {

				auto tmp_iter = get_profile_map().find(name);
				if (tmp_iter != get_profile_map().end()) {
					return tmp_iter->second;
				}

				return hiprofile_type_none;
			}
		private:
			/**
			 * 表示系统内存的对齐方式
			 */
			int m_align_width = 16;
			/**
			 * 最大内存池数量
			 */
			int m_max_pool_count = 128;
			/**
			* 表示硬件平台的功耗场景类型
			*/
			std::string m_profile = "";
			/**
			* 表示硬件平台的功耗场景类型名称与索引的对应表
			*/
			static const std::map<std::string, hiprofile_type> m_profile_map;
		};

	}

}
#endif // !defined(HISYS_CONF_H_INCLUDED_)
