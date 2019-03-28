/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_version.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 30-6月-2018 17:49:52
*
*Description: Class(csf_module_version)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_VERSION_INCLUDED_)
#define CSF_MODULE_VERSION_INCLUDED_

#include "csf_version.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示模块版本信息
			 * @author fz
			 * @version 1.0
			 * @created 30-6月-2018 17:49:52
			 */
			class csf_module_version : public csf::core::base::_csf_version_
			{

			public:
				inline csf_module_version() {

				}
				/**
				* @param version    模块的版本数值信息
				* @param strver    模块的版本字符串信息
				* @param compile    表示模块编译器信息
				* @param build    模块编译相关信息，主要是时间信息
				* @param description    模块的其他描述信息
				*/
				inline csf_module_version(const csf_int32 version
					, const csf_string strver
					, const csf_string compile
					, const csf_string build
					, const csf_string description = "")

					: _csf_version_(version, strver, compile, build, description) {

				}
				inline virtual ~csf_module_version() {

				}
			};

		}

	}

}
#endif // !defined(CSF_MODULE_VERSION_INCLUDED_)
