/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_configure_supply.hpp
*
*Version: 1.0
*
*Date: 25-2月-2019 19:08:38
*
*Description: Class(csf_configure_supply) 表示模块的补充配置信息。该类主要解决csf_configure_manager的信息不易扩展的问题。
csf_configure_manager主要保存配置文件信息，没有保存程序运行时的配置信息，当需要传输运行时的参数时，可能有三种处理方式：
1、扩展csf_configure_manager类，生成独立配置对象
2、保持csf_configure_manager一致，可以使用csf_configure_supply扩展对象的方式进行。
3、将需要的运行时对象附加到csf_configure_manager的附加对象列表中，使用时查找。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONFIGURE_SUPPLY_H_INCLUDED_)
#define CSF_CONFIGURE_SUPPLY_H_INCLUDED_

#include "csf_app.hpp"
#include "csf_vm.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * 表示模块的补充配置信息。该类主要解决csf_configure_manager的信息不易扩展的问题。
			 * csf_configure_manager主要保存配置文件信息，没有保存程序运行时的配置信息，当需要传输运行时的参数时，可能有三种处理方式：
			 * 1、扩展csf_configure_manager类，生成独立配置对象
			 * 2、保持csf_configure_manager一致，可以使用csf_configure_supply扩展对象的方式进行。
			 * 3、将需要的运行时对象附加到csf_configure_manager的附加对象列表中，使用时查找。
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 25-2月-2019 19:08:38
			 */
			class csf_configure_supply
			{

			public:
				csf_configure_supply();
				virtual ~csf_configure_supply();

				/**
				 * 表示当前程序所拥有的虚拟机对象地址。
				 */
				inline csf_vm* get_vm() {

					return m_vm;
				}
				/**
				 * 表示当前程序所拥有的虚拟机对象地址。
				 * 
				 * @param new_value
				 */
				inline void set_vm(csf_vm* new_value) {

					m_vm = new_value;
				}
				/**
				 * 表示当前程序所拥有的app对象地址，如果多个app对象则表示最后一个app对象。
				 */
				inline csf_app* get_app() {

					return m_app;
				}
				/**
				 * 表示当前程序所拥有的app对象地址，如果多个app对象则表示最后一个app对象。
				 * 
				 * @param new_value
				 */
				inline void set_app(csf_app* new_value) {

					m_app = new_value;
				}

			private:
				/**
				 * 表示当前程序所拥有的虚拟机对象地址。
				 */
				csf_vm* m_vm = csf_nullptr;
				/**
				 * 表示当前程序所拥有的app对象地址，如果多个app对象则表示最后一个app对象。
				 */
				csf_app* m_app = csf_nullptr;

			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_SUPPLY_H_INCLUDED_)
