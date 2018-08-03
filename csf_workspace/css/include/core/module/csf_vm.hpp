/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_vm.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:54
*
*Description: Class(csf_vm)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_VM_INCLUDED_)
#define CSF_VM_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示csf的虚拟主机。
			 * 这是新引入的模块类型，主要处理app上一层次内容，充当一种容器角色。其目的是释放app概念，让app、device、device_io能够的用于业务处理。
			 * csf_vm的处理逻辑相对固定，主要初始化环境操作，为系统运行搭建最基础的环境。例如：初始日志系统、解析配置文件等。
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:54
			 */
			class csf_vm
			{

			public:
				csf_vm();
				virtual ~csf_vm();

			};

		}

	}

}
#endif // !defined(CSF_VM_INCLUDED_)
