/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_semh_command.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:31
*
*Description: Enumeration(css_semh_command) 表示semh的命令
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_SEMH_COMMAND_H_INCLUDED_)
#define CSS_SEMH_COMMAND_H_INCLUDED_

namespace css
{
	namespace core
	{
		/**
		 * 表示semh的命令
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:31
		 */
		enum css_semh_command
		{
			/**
			 * 表示未知的指令编码
			 */
			m_css_semh_command_none = 0x00000000
		};

	}

}
#endif // !defined(CSS_SEMH_COMMAND_H_INCLUDED_)
