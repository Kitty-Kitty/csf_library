/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_exception_warning.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:27
*
*Description: Class(csf_attribute_exception_warning)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_EXCEPTION_WARNING_INCLUDED_)
#define CSF_ATTRIBUTE_EXCEPTION_WARNING_INCLUDED_

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
				 * �����쳣��ӡ�澯��Ϣ
				 * @author Administrator
				 * @version 1.0
				 * @created 05-7��-2018 20:09:27
				 */
				class csf_attribute_exception_warning : public csf::core::system::attribute::csf_attribute_exception
				{

				public:
					explicit csf_attribute_exception_warning()
						: csf_attribute_exception([](csf_attribute& attr) {
						csf_log_ex(warning, csf_log_code_warning
							, "%s process exception."
							, attr.to_string().c_str());
					}) {

					}

					/**
					*
					* @param callback    ��ʾ�쳣�ص�����
					*
					*/
					explicit csf_attribute_exception_warning(const csf::core::system::attribute::csf_attribute_exception_callback callback)
						: csf_attribute_exception(callback) {
					}

					virtual ~csf_attribute_exception_warning() {

					}

					csf_void print_warning(csf::core::system::attribute::csf_attribute &attribute) {

					}
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_EXCEPTION_WARNING_INCLUDED_)
