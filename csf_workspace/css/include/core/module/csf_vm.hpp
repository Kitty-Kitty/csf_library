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
*Date: 27-6��-2018 17:28:54
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
			 * ��ʾcsf������������
			 * �����������ģ�����ͣ���Ҫ����app��һ������ݣ��䵱һ��������ɫ����Ŀ�����ͷ�app�����app��device��device_io�ܹ�������ҵ����
			 * csf_vm�Ĵ����߼���Թ̶�����Ҫ��ʼ������������Ϊϵͳ���д������Ļ��������磺��ʼ��־ϵͳ�����������ļ��ȡ�
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:28:54
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
