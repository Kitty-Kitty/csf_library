﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7月-2018 22:23:05
*
*Description: Class(csf_serial_url) 表示串口地址信息
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_SERIAL_URL_INCLUDED_)
#define CSF_SERIAL_URL_INCLUDED_

#include "csf_url.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示串口地址信息
				 * @author f
				 * @version 1.0
				 * @created 11-7月-2018 22:23:05
				 */
				class csf_serial_url : public csf_url
				{

				public:
					/**
					 * 表示串口的流控制类型
					 * @author f
					 * @version 1.0
					 * @created 11-7月-2018 22:23:05
					 */
					enum csf_serial_flow_control_type
					{
						/**
						 * 表示未知的串口流控制类型
						 */
						csf_serial_flow_control_type_none = 0,
						/**
						 * 表示软控制
						 */
						csf_serial_flow_control_type_software,
						/**
						 * 表示硬控制
						 */
						csf_serial_flow_control_type_hardware
					};

					/**
					 * 表示奇遇校验类型
					 * @author f
					 * @version 1.0
					 * @created 11-7月-2018 22:23:05
					 */
					enum csf_serial_parity_type
					{
						/**
						 * 表示未知的奇遇校验
						 */
						csf_serial_parity_type_none = 0,
						/**
						 * 表示未知的奇校验
						 */
						csf_serial_parity_type_odd,
						/**
						 * 表示未知的遇校验
						 */
						csf_serial_parity_type_even
					};

					/**
					 * 表示停止位类型
					 * @author f
					 * @version 1.0
					 * @created 11-7月-2018 22:23:05
					 */
					enum csf_serial_stop_bits_type
					{
						/**
						 * 表示未知的停止位
						 */
						csf_serial_stop_bits_type_none = 0,
						/**
						 * 表示1位停止位
						 */
						csf_serial_stop_bits_type_one,
						/**
						 * 表示1.5位停止位
						 */
						csf_serial_stop_bits_type_one_point_five,
						/**
						 * 表示2位停止位
						 */
						csf_serial_stop_bits_type_two
					};

					inline explicit csf_serial_url()
						: csf_url(csf_url::csf_url_type::csf_url_type_serial)
						, m_baud_rate(0)
						, m_character_size(0)
						, m_flow_control(csf_serial_flow_control_type_none)
						, m_dev("")
						, m_parity(csf_serial_parity_type_none)
						, m_stop_bits(csf_serial_stop_bits_type_none)
						, m_port(0) {

					}

					virtual ~csf_serial_url() {

					}

					/**
					 * 表示串口的波特数值
					 */
					inline csf_int32 get_baud_rate() {

						return m_baud_rate;
					}
					/**
					 * 表示字符的长度
					 */
					inline csf_uchar get_character_size() {

						return m_character_size;
					}
					/**
					 * 表示串口的波特数值
					 * 
					 * @param newVal
					 */
					inline void set_baud_rate(const csf_int32 newVal) {

						m_baud_rate = newVal;
					}
					/**
					 * 表示字符的长度
					 * 
					 * @param newVal
					 */
					inline void set_character_size(const csf_uchar newVal) {

						m_character_size = newVal;
					}
					/**
					 * 表示串口设备
					 */
					inline csf_string & get_dev() {

						return m_dev;
					}
					/**
					 * 表示解析地址函数
					 * 
					 * @param url    表示url地址字符串数据
					 */
					inline virtual csf_int32 parse(csf_string& url) {

						return 0;
					}
					/**
					 * 表示串口设备
					 * 
					 * @param newVal
					 */
					inline void set_dev(const csf_char* newVal) {

						m_dev = newVal;
					}
					/**
					 * 表示流控类型
					 */
					inline csf_serial_flow_control_type get_flow_control() {

						return m_flow_control;
					}
					/**
					 * 表示流控类型
					 * 
					 * @param newVal
					 */
					inline void set_flow_control(const csf_serial_flow_control_type newVal) {

						m_flow_control = newVal;
					}
					/**
					 * 表示奇偶校验类型
					 */
					inline csf_serial_parity_type get_parity() {

						return m_parity;
					}
					/**
					 * 表示奇偶校验类型
					 * 
					 * @param newVal
					 */
					inline void set_parity(const csf_serial_parity_type newVal) {

						m_parity = newVal;
					}
					/**
					 * 表示停止位类型
					 */
					inline csf_serial_stop_bits_type get_stop_bits() {

						return m_stop_bits;
					}
					/**
					 * 表示停止位类型
					 * 
					 * @param newVal
					 */
					inline void set_stop_bits(const csf_serial_stop_bits_type newVal) {

						m_stop_bits = newVal;
					}
					/**
					 * 表示串口的端口号
					 */
					inline csf_uint32 get_port() {

						return m_port;
					}
					/**
					 * 表示串口的端口号
					 * 
					 * @param newVal
					 */
					inline void set_port(const csf_uint32 newVal) {

						m_port = newVal;
					}
					/**
					 * 表示串口设备
					 * 
					 * @param newVal
					 */
					inline void set_dev(csf_string& newVal) {

						m_dev = newVal;
					}
					/**
					 * 表示解析地址函数
					 * 
					 * @param url    表示url地址字符串数据
					 */
					inline virtual csf_int32 parse(const csf_char* url) {

						return 0;
					}

				private:
					/**
					 * 表示串口的波特数值
					 */
					csf_int32 m_baud_rate = 0;
					/**
					 * 表示字符的长度
					 */
					csf_uchar m_character_size = 0;
					/**
					 * 表示流控类型
					 */
					csf_serial_flow_control_type m_flow_control = csf_serial_flow_control_type_none;
					/**
					 * 表示串口设备
					 */
					csf_string m_dev = "";
					/**
					 * 表示奇偶校验类型
					 */
					csf_serial_parity_type m_parity = csf_serial_parity_type_none;
					/**
					 * 表示停止位类型
					 */
					csf_serial_stop_bits_type m_stop_bits = csf_serial_stop_bits_type_none;
					/**
					 * 表示串口的端口号
					 */
					csf_uint32 m_port = 0;

				};

			}

		}

	}

}
#endif // !defined(CSF_SERIAL_URL_INCLUDED_)
