/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_vm.hpp
*
*Version: 1.0
*
*Date: 23-9月-2018 18:32:42
*
*Description: Class(vdu_vm) 表示矢量数据处理单元（vector data unit）主类型。主要实现一个处理类型选择器功能，根据不同需要，分别选择不同的渲染方式，方式包括：opengl\opengl es \ open vg 等
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_VM_H_INCLUDED_)
#define VDU_VM_H_INCLUDED_

#include "csf_vm.hpp"
#include "vdu_canvas.hpp"

namespace vdu
{
	namespace core
	{
		/**
		 * 表示矢量数据处理单元（vector data
		 * unit）主类型。主要实现一个处理类型选择器功能，根据不同需要，分别选择不同的渲染方式，方式包括：opengl\opengl es \ open vg 等
		 * @author fangzhenmu
		 * @version 1.0
		 * @created 23-9月-2018 18:32:42
		 */
		class vdu_vm : public csf::core::module::csf_vm
		{

		public:
			vdu_vm();
			virtual ~vdu_vm();

		private:
			/**
			 * 表示一个图形处理画布
			 */
			vdu::core::vdu_canvas m_canvas;

		};

	}

}
#endif // !defined(VDU_VM_H_INCLUDED_)
