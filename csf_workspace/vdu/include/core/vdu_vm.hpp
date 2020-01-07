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
*Date: 23-9��-2018 18:32:42
*
*Description: Class(vdu_vm) ��ʾʸ�����ݴ���Ԫ��vector data unit�������͡���Ҫʵ��һ����������ѡ�������ܣ����ݲ�ͬ��Ҫ���ֱ�ѡ��ͬ����Ⱦ��ʽ����ʽ������opengl\opengl es \ open vg ��
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
		 * ��ʾʸ�����ݴ���Ԫ��vector data
		 * unit�������͡���Ҫʵ��һ����������ѡ�������ܣ����ݲ�ͬ��Ҫ���ֱ�ѡ��ͬ����Ⱦ��ʽ����ʽ������opengl\opengl es \ open vg ��
		 * @author fangzhenmu
		 * @version 1.0
		 * @created 23-9��-2018 18:32:42
		 */
		class vdu_vm : public csf::core::module::csf_vm
		{

		public:
			vdu_vm();
			virtual ~vdu_vm();

		private:
			/**
			 * ��ʾһ��ͼ�δ�����
			 */
			vdu::core::vdu_canvas m_canvas;

		};

	}

}
#endif // !defined(VDU_VM_H_INCLUDED_)
