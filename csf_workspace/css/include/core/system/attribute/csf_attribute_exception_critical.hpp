/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_exception_critical.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:27
*
*Description: Class(csf_attribute_exception_critical)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_EXCEPTION_CRITICAL_INCLUDED_)
#define CSF_ATTRIBUTE_EXCEPTION_CRITICAL_INCLUDED_

#include "csf_attribute_exception.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * 表示出现错误，除非配置回调，否则直接抛出异常。
				 * @author Administrator
				 * @version 1.0
				 * @created 05-7月-2018 20:09:27
				 */
				class csf_attribute_exception_critical : public csf::core::system::attribute::csf_attribute_exception
				{

				public:
					csf_attribute_exception_critical() : csf_attribute_exception([](csf_attribute& attr) {

						csf_char				tmp_buf[csf_attribute_exception_string_length] = { 0, };

						csf_snprintf(tmp_buf, csf_sizeof(tmp_buf)
							, "%s critical exception."
							, attr.to_string().c_str());

						csf_log_ex(warning, csf_log_code_warning , "%s", tmp_buf);

						//这里通过退出程度的方式处理，以达到严重错误的特点
						//throw tmp_buf;
						exit(1);
					}) {

					}

					/**
					*
					* @param callback    表示异常回调函数
					*
					*/
					explicit csf_attribute_exception_critical(const csf::core::system::attribute::csf_attribute_exception_callback callback)
						: csf_attribute_exception(callback) {
					}
					virtual ~csf_attribute_exception_critical() {

					}

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_EXCEPTION_CRITICAL_INCLUDED_)
