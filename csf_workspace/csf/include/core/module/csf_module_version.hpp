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
*Date: 30-6��-2018 17:49:52
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
			 * ��ʾģ��汾��Ϣ
			 * @author fz
			 * @version 1.0
			 * @created 30-6��-2018 17:49:52
			 */
			class csf_module_version : public csf::core::base::_csf_version_
			{

			public:
				inline csf_module_version() {

				}
				/**
				* @param version    ģ��İ汾��ֵ��Ϣ
				* @param strver    ģ��İ汾�ַ�����Ϣ
				* @param compile    ��ʾģ���������Ϣ
				* @param build    ģ����������Ϣ����Ҫ��ʱ����Ϣ
				* @param description    ģ�������������Ϣ
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
