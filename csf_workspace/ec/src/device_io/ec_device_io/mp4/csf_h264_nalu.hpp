/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_h264_nalu.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 16:30:52
*
*Description: Class(csf_h264_nalu) 表示h264的NALU结构信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_H264_NALU_H_INCLUDED_)
#define CSF_H264_NALU_H_INCLUDED_

#include <iostream>

namespace ec
{
	namespace core
	{
		/**
		 * 表示h264的NALU结构信息
		 * @author f
		 * @version 1.0
		 * @created 07-12月-2019 16:30:52
		 */
		class csf_h264_nalu
		{
		public:

			// H.264 NAL type
			/**
			* 表示h264的nalu类型
			* @author f
			* @version 1.0
			* @created 07-12月-2019 16:30:52
			*/
			enum h264_nalu_type
			{
				h264_nalu_nal = 0,					//
				h264_nalu_slice,					//非idr图像的编码条带(p 帧)
				h264_nalu_slice_dpa,				//编码条带数据分割块a
				h264_nalu_slice_dpb,				//编码条带数据分割块b
				h264_nalu_slice_dpc,				//编码条带数据分割块c
				h264_nalu_slice_idr,				//idr图像的编码条带(i 帧)
				h264_nalu_sei,						//补充增强信息单元
				h264_nalu_sps,						//序列参考集
				h264_nalu_pps,						//图象参考集
				h264_nalu_aud,						//分界符
				h264_nalu_eoseq,					//序列结束
				h264_nalu_eostream,					//码流结束
				h264_nalu_fill,						//填充
													//13..23	保留
													//24..31	未使用
			};

		public:
			csf_h264_nalu();
			virtual ~csf_h264_nalu();

			/**
			 * 表示当前nalu的数据内存起始地址，该起始数据为nalu标识 00 00 00 01 数据
			 */
			inline unsigned char* get_buffer() {

				return m_buffer;
			}
			/**
			 * 表示当前nalu的数据内存起始地址，该起始数据为nalu标识 00 00 00 01 数据
			 *
			 * @param newVal
			 */
			inline void set_buffer(unsigned char* newVal) {

				m_buffer = newVal;
			}
			/**
			 * 表示当前nalu数据帧的数据长度，如果数据包含00 00 00 001，则该长度为也包含该数据的长度
			 */
			inline unsigned int get_length() {

				return m_length;
			}
			/**
			 * 表示当前nalu数据帧的数据长度，如果数据包含00 00 00 001，则该长度为也包含该数据的长度
			 *
			 * @param newVal
			 */
			inline void set_length(unsigned int newVal) {

				m_length = newVal;
			}
			/**
			 * 表示当前nalu的类型
			 */
			inline h264_nalu_type get_nalu_type() {

				return m_nalu_type;
			}
			/**
			 * 表示当前nalu的类型
			 *
			 * @param newVal
			 */
			inline void set_nalu_type(h264_nalu_type newVal) {

				m_nalu_type = newVal;
			}
			/**
			 * 表示类型，可以用于判断是否为图像帧
			 */
			inline unsigned char get_flag_type() {

				return m_flag_type;
			}
			/**
			 * 表示类型，可以用于判断是否为图像帧
			 *
			 * @param newVal
			 */
			inline void set_flag_type(unsigned char newVal) {

				m_flag_type = newVal;
			}
			/**
			 * 表示nalu标识头的长度
			 */
			inline unsigned int get_head_length() {

				return m_head_length;
			}
			/**
			 * 表示nalu标识头的长度
			 *
			 * @param newVal
			 */
			inline void set_head_length(unsigned int newVal) {

				m_head_length = newVal;
			}
			/**
			 * 功能：
			 *    解析传入的nalu数据内容
			 * 返回：
			 *    true ：表示解析成功；
			 *    false：表示解析失败；
			 *
			 * @param buf    表示数据内存起始地址
			 * @param len    表示数据长度
			 */
			bool parse(unsigned char* buf, unsigned int len);
			/**
			* 功能：
			*    判断是否为sps类型
			* 返回：
			*    true ：表示是；
			*    false：表示不是；
			*
			* @param buf    表示数据内存起始地址
			* @param len    表示数据长度
			*/
			inline static bool issps(unsigned char* buf, unsigned int len) {
				if (h264_nalu_sps == get_nalu_type(buf, len)) {
					return true;
				}
				return false;
			}
			/**
			* 功能：
			*    判断是否为pps类型
			* 返回：
			*    true ：表示是；
			*    false：表示不是；
			*
			* @param buf    表示数据内存起始地址
			* @param len    表示数据长度
			*/
			inline static bool ispps(unsigned char* buf, unsigned int len) {
				if (h264_nalu_pps == get_nalu_type(buf, len)) {
					return true;
				}
				return false;
			}
			/**
			* 功能：
			*    判断是否为sps或pps类型
			* 返回：
			*    true ：表示是；
			*    false：表示不是；
			*
			* @param buf    表示数据内存起始地址
			* @param len    表示数据长度
			*/
			inline static bool isspspps(unsigned char* buf, unsigned int len) {

				h264_nalu_type		tmp_nalu_type = h264_nalu_nal;


				tmp_nalu_type = get_nalu_type(buf, len);
				if (h264_nalu_sps == tmp_nalu_type 
						|| h264_nalu_pps == tmp_nalu_type) {
					return true;
				}
				return false;
			}
			/**
			* 功能：
			*    判断是否为i帧
			* 返回：
			*    true ：表示是；
			*    false：表示不是；
			*
			* @param buf    表示数据内存起始地址
			* @param len    表示数据长度
			*/
			inline static bool isidr(unsigned char* buf, unsigned int len) {
				if (h264_nalu_slice_idr == get_nalu_type(buf, len)) {
					return true;
				}
				return false;
			}
			/**
			* 功能：
			*    判断是否为图像帧
			* 返回：
			*    true ：表示是；
			*    false：表示不是；
			*
			* @param buf    表示数据内存起始地址
			* @param len    表示数据长度
			*/
			inline static bool ispicture(unsigned char* buf, unsigned int len) {

				int		tmp_size = nalu_head_size(buf, len);


				if (tmp_size <= 0) {
					return false;
				}

				if ((h264_nalu_nal < (buf[tmp_size] & 0x1f))
					&& ((buf[tmp_size] & 0x1f) < h264_nalu_sei)
					&& ((buf[tmp_size + 1] & 0x80) > 0)) {

					//表示为图像帧数据
					return true;
				}
				return false;
			}
			/**
			* 功能：
			*    表示获取nalu类型
			* 返回：
			*    nalu类型
			*
			* @param buf    表示数据内存起始地址
			* @param len    表示数据长度
			*/
			inline static h264_nalu_type get_nalu_type(unsigned char* buf, unsigned int len) {

				int		tmp_nalu_head_size = nalu_head_size(buf, len);

				if (tmp_nalu_head_size <= 0) {
					return h264_nalu_nal;
				}
				else {
					return (h264_nalu_type)(buf[tmp_nalu_head_size] & 0x1f);
				}
			}
			/**
			* 功能：
			*    表示nalu头的长度
			* 返回：
			*    nalu头的长度，如果不是则返回0
			*
			* @param buf    表示数据内存起始地址
			* @param len    表示数据长度
			*/
			inline static int nalu_head_size(unsigned char* buf, unsigned int len) {
				if (len >= 3) {
					if (buf[0] == 0 && buf[1] == 0 && buf[2] == 1) {
						return 3;
					}
				}
				if (len >= 4) {
					if (buf[0] == 0 && buf[1] == 0 && buf[2] == 0 && buf[3] == 1) {
						return 4;
					}
				}
				return 0;
			}
		private:
			/**
			* 功能：
			*    查找nalu head的起始位置
			* 返回：
			*    nalu head的起始位置
			*
			* @param buf    表示数据内存起始地址
			* @param len    表示数据长度
			*/
			inline unsigned int find_nalu_head(unsigned char* buf, unsigned int len);
		private:
			/**
			 * 表示当前nalu的数据内存起始地址，该起始数据为nalu标识 00 00 00 01 数据
			 */
			unsigned char* m_buffer = NULL;
			/**
			 * 表示当前nalu数据帧的数据长度，如果数据包含00 00 00 001，则该长度为也包含该数据的长度
			 */
			unsigned int m_length = 0;
			/**
			 * 表示当前nalu的类型
			 */
			h264_nalu_type m_nalu_type = h264_nalu_nal;
			/**
			 * 表示类型，可以用于判断是否为图像帧
			 */
			unsigned char m_flag_type = 0;
			/**
			 * 表示nalu标识头的长度
			 */
			unsigned int m_head_length = 0;

		};

	}

}
#endif // !defined(CSF_H264_NALU_H_INCLUDED_)
