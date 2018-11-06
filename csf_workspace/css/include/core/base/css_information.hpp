/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_information.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:28
*
*Description: Class(css_information) ��ʾcss������Ϣ
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_INFORMATION_H_INCLUDED_)
#define CSS_INFORMATION_H_INCLUDED_

namespace css
{
	namespace core
	{
		/**
		 * ��ʾcss������Ϣ
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:28
		 */
		class css_information
		{

		public:
			css_information();
			virtual ~css_information();

			/**
			 * <font color="#008000">���Ĵ��̿ռ䣨�ٷֱȣ�0~100��</font>
			 */
			inline csf_uint32 get_limit_disk() {

				return m_limit_disk;
			}
			/**
			 * <font color="#008000">���Ĵ��̿ռ䣨�ٷֱȣ�0~100��</font>
			 * 
			 * @param newVal
			 */
			inline void set_limit_disk(const csf_uint32 newVal) {

				m_limit_disk = newVal;
			}
			/**
			 * <font color="#008000">�����ڴ�ռ䣨�ٷֱȣ�0~100��</font>
			 */
			inline csf_uint32 get_limit_memory() {

				return m_limit_memory;
			}
			/**
			 * <font color="#008000">�����ڴ�ռ䣨�ٷֱȣ�0~100��</font>
			 * 
			 * @param newVal
			 */
			inline void set_limit_memory(const csf_uint32 newVal) {

				m_limit_memory = newVal;
			}
			/**
			 * <font color="#008000">����cpuʹ���ʣ��ٷֱȣ�0~100��</font>
			 */
			inline csf_uint32 get_limit_cpu() {

				return m_limit_cpu;
			}
			/**
			 * <font color="#008000">����cpuʹ���ʣ��ٷֱȣ�0~100��</font>
			 * 
			 * @param newVal
			 */
			inline void set_limit_cpu(const csf_uint32 newVal) {

				m_limit_cpu = newVal;
			}
			/**
			 * <font color="#008000">�������������λ���ֽڣ�</font>
			 */
			inline csf_uint32 get_limit_bandwidth() {

				return m_limit_bandwidth;
			}
			/**
			 * <font color="#008000">�������������λ���ֽڣ�</font>
			 * 
			 * @param newVal
			 */
			inline void set_limit_bandwidth(const csf_uint32 newVal) {

				m_limit_bandwidth = newVal;
			}
			/**
			 * <font color="#008000">������������������λ������</font>
			 */
			inline csf_uint32 get_limit_connect() {

				return m_limit_connect;
			}
			/**
			 * <font color="#008000">������������������λ������</font>
			 * 
			 * @param newVal
			 */
			inline void set_limit_connect(const csf_uint32 newVal) {

				m_limit_connect = newVal;
			}
			/**
			 * <font color="#008000">��ǰ�Ĵ��̿ռ䣨�ٷֱȣ�0~100��</font>
			 */
			inline csf_uint32 get_current_disk() {

				return m_current_disk;
			}
			/**
			 * <font color="#008000">��ǰ�Ĵ��̿ռ䣨�ٷֱȣ�0~100��</font>
			 * 
			 * @param newVal
			 */
			inline void set_current_disk(const csf_uint32 newVal) {

				m_current_disk = newVal;
			}
			inline csf_uint32 get_current_memory() {

				return m_current_memory;
			}
			/**
			 * 
			 * @param newVal
			 */
			inline void set_current_memory(const csf_uint32 newVal) {

				m_current_memory = newVal;
			}
			/**
			 * <font color="#008000">��ǰ��cpuʹ���ʣ��ٷֱȣ�0~100��</font>
			 */
			inline csf_uint32 get_current_cpu() {

				return m_current_cpu;
			}
			/**
			 * <font color="#008000">��ǰ��cpuʹ���ʣ��ٷֱȣ�0~100��</font>
			 * 
			 * @param newVal
			 */
			inline void set_current_cpu(const csf_uint32 newVal) {

				m_current_cpu = newVal;
			}
			/**
			 * <font color="#008000">��ǰ�����������λ���ֽڣ�</font>
			 */
			inline csf_uint32 get_current_bandwidth() {

				return m_current_bandwidth;
			}
			/**
			 * <font color="#008000">��ǰ�����������λ���ֽڣ�</font>
			 * 
			 * @param newVal
			 */
			inline void set_current_bandwidth(const csf_uint32 newVal) {

				m_current_bandwidth = newVal;
			}
			/**
			 * <font color="#008000">��ǰ����������������λ������</font>
			 */
			inline csf_uint32 get_current_connect() {

				return m_current_connect;
			}
			/**
			 * <font color="#008000">��ǰ����������������λ������</font>
			 * 
			 * @param newVal
			 */
			inline void set_current_connect(const csf_uint32 newVal) {

				m_current_connect = newVal;
			}

		private:
			/**
			 * <font color="#008000">���Ĵ��̿ռ䣨�ٷֱȣ�0~100��</font>
			 */
			csf_uint32 m_limit_disk = 0;
			/**
			 * <font color="#008000">�����ڴ�ռ䣨�ٷֱȣ�0~100��</font>
			 */
			csf_uint32 m_limit_memory = 0;
			/**
			 * <font color="#008000">����cpuʹ���ʣ��ٷֱȣ�0~100��</font>
			 */
			csf_uint32 m_limit_cpu = 0;
			/**
			 * <font color="#008000">�������������λ���ֽڣ�</font>
			 */
			csf_uint32 m_limit_bandwidth = 0;
			/**
			 * <font color="#008000">������������������λ������</font>
			 */
			csf_uint32 m_limit_connect = 0;
			/**
			 * <font color="#008000">��ǰ�Ĵ��̿ռ䣨�ٷֱȣ�0~100��</font>
			 */
			csf_uint32 m_current_disk = 0;
			csf_uint32 m_current_memory = 0;
			/**
			 * <font color="#008000">��ǰ��cpuʹ���ʣ��ٷֱȣ�0~100��</font>
			 */
			csf_uint32 m_current_cpu = 0;
			/**
			 * <font color="#008000">��ǰ�����������λ���ֽڣ�</font>
			 */
			csf_uint32 m_current_bandwidth = 0;
			/**
			 * <font color="#008000">��ǰ����������������λ������</font>
			 */
			csf_uint32 m_current_connect = 0;

		};

	}

}
#endif // !defined(CSS_INFORMATION_H_INCLUDED_)
