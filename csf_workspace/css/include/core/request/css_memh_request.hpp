/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_memh_request.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:29
*
*Description: Class(css_memh_request) 表示memh的请求内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_MEMH_REQUEST_H_INCLUDED_)
#define CSS_MEMH_REQUEST_H_INCLUDED_

#include "css_request.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示memh的请求内容
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:29
		 */
		class css_memh_request : public css::core::css_request
		{

		public:
			css_memh_request();
			virtual ~css_memh_request();

			/**
			 * 表示memh结构体内容
			 */
			gmp_gmph_memh_t* get_memh();
			/**
			 * 表示memh结构体内容
			 * 
			 * @param newVal
			 */
			void set_memh(gmp_gmph_memh_t* newVal);

		private:
			/**
			 * 表示memh结构体内容
			 */
			gmp_gmph_memh_t* m_memh = csf_null;

		};

	}

}
#endif // !defined(CSS_MEMH_REQUEST_H_INCLUDED_)
