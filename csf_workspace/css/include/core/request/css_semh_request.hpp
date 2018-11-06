/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_semh_request.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:31
*
*Description: Class(css_semh_request) 表示semh请求结构体
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_SEMH_REQUEST_H_INCLUDED_)
#define CSS_SEMH_REQUEST_H_INCLUDED_

#include "css_request.hpp"
#include "prot_gmp_core.h"

namespace css
{
	namespace core
	{
		/**
		 * 表示semh请求结构体
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:31
		 */
		class css_semh_request : public css::core::css_request
		{

		public:
			css_semh_request();
			virtual ~css_semh_request();

			/**
			 * 表示semh结构体内容
			 */
			gmp_gmph_semh_t* get_semh();
			/**
			 * 表示semh结构体内容
			 * 
			 * @param newVal
			 */
			void set_semh(gmp_gmph_semh_t* newVal);
			/**
			 * 表示gmf结构体内容
			 */
			gmp_gmf_t* get_gmf();
			/**
			 * 表示gmf结构体内容
			 * 
			 * @param newVal
			 */
			void set_gmf(gmp_gmf_t* newVal);

		private:
			/**
			 * 表示semh结构体内容
			 */
			gmp_gmph_semh_t* m_semh = csf_null;
			/**
			 * 表示gmf结构体内容
			 */
			gmp_gmf_t* m_gmf = csf_null;

		};

	}

}
#endif // !defined(CSS_SEMH_REQUEST_H_INCLUDED_)
