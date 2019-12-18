/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: hiaudio_common_conf.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:31:47
*
*Description: Class(hiaudio_common_conf) 表示音频通用配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(HIAUDIO_COMMON_CONF_H_INCLUDED_)
#define HIAUDIO_COMMON_CONF_H_INCLUDED_

#include <iostream>
#include <map>
#include "hichannel_conf.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示音频通用配置信息
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 13:31:47
		 */
		class hiaudio_common_conf : public ec::core::hichannel_conf
		{

		public:
			/**
			* 表示音频编码类型
			* @author f
			* @version 1.0
			* @updated 04-12月-2019 12:39:08
			*/
			enum hiaudio_encode_tpe
			{
				/**
				* 表示无效的音频编码格式
				*/
				hiaudio_encode_type_none = 0x00,
				/**
				* 表示aac音频编码格式
				*/
				hiaudio_encode_type_aac = 0x01
			};

			/**
			* 音频声道模式
			* @author f
			* @version 1.0
			* @updated 04-12月-2019 12:39:08
			*/
			enum hiaudio_sound_mode
			{
				/**
				* 表示无效的音频模式
				*/
				hiaudio_sound_mode_none = 0x00,
				/**
				* 表示单声道音频模式
				*/
				hiaudio_sound_mode_mono = 0x01,
				/**
				* 表示双声道音频模式
				*/
				hiaudio_sound_mode_stereo = 0x02
			};


			hiaudio_common_conf();
			virtual ~hiaudio_common_conf();

			/**
			* 表示设备id
			*/
			inline int get_dev_id() {

				return m_dev_id;
			}
			/**
			* 表示设备id
			*
			* @param newVal
			*/
			inline void set_dev_id(int newVal) {

				m_dev_id = newVal;
			}
			/**
			* 表示设备通道id
			*/
			inline int get_dev_channel() {

				return m_dev_channel;
			}
			/**
			* 表示设备通道id
			*
			* @param newVal
			*/
			inline void set_dev_channel(int newVal) {

				m_dev_channel = newVal;
			}
			/**
			* 表示编解码器通道
			*/
			inline int get_coder_channel() {

				return m_coder_channel;
			}
			/**
			* 表示编解码器通道
			*
			* @param newVal
			*/
			inline void set_coder_channel(int newVal) {

				m_coder_channel = newVal;
			}
			/**
			 * 表示音频采样频率
			 */
			inline int get_sample_rate() {

				return m_sample_rate;
			}
			/**
			 * 表示音频采样频率
			 *
			 * @param newVal
			 */
			inline void set_sample_rate(int newVal) {

				m_sample_rate = newVal;
			}
			/**
			* 音频采样精度
			*/
			inline int get_bit_width() {

				return m_bit_width;
			}
			/**
			* 音频采样精度
			*
			* @param newVal
			*/
			inline void set_bit_width(int newVal) {

				m_bit_width = newVal;
			}
			/**
			 * 表示音频编码名称
			 */
			inline std::string get_encode_type() {

				return m_encode_type;
			}
			/**
			 * 表示音频声道模式
			 */
			inline std::string get_sound_mode() {

				return m_sound_mode;
			}
			/**
			 * 表示音频编码名称
			 *
			 * @param newVal
			 */
			inline void set_encode_type(std::string newVal) {

				m_encode_type = newVal;
			}
			/**
			 * 表示音频声道模式
			 *
			 * @param newVal
			 */
			inline void set_sound_mode(std::string newVal) {

				m_sound_mode = newVal;
			}
			/**
			* 表示是否重新采样。true表示需要重新采样；false表示不需要重新采样；
			*/
			inline bool isresample() {

				return m_resample;
			}
			/**
			* 表示是否重新采样。true表示需要重新采样；false表示不需要重新采样；
			*
			* @param newVal
			*/
			inline void set_resample(bool newVal) {

				m_resample = newVal;
			}
			/**
			* 表示音频音量大小
			*/
			inline int get_volume() {

				return m_volume;
			}
			/**
			* 表示音频音量大小
			*
			* @param newVal
			*/
			inline void set_volume(int newVal) {

				m_volume = newVal;
			}
			/**
			* 表示是否使用音频增强
			*/
			inline bool isuse_vqe() {

				return m_use_vqe;
			}
			/**
			* 表示是否使用音频增强
			*
			* @param newVal
			*/
			inline void set_use_vqe(bool newVal) {

				m_use_vqe = newVal;
			}
			/**
			* 表示音频编码名称
			*/
			inline hiaudio_encode_tpe get_encode_type_index() {
				return get_encode_type(get_encode_type());
			}
			/**
			* 表示音频编码名称
			*/
			inline hiaudio_sound_mode get_sound_mode_index() {
				return get_sound_mode(get_sound_mode());
			}

			/**
			* 表示音频编码名称
			*
			* @param name    表示音频编码类型名称
			*/
			inline hiaudio_encode_tpe get_encode_type(std::string name) {

				auto tmp_iter = get_encode_type_map().find(name);
				if (tmp_iter != get_encode_type_map().end()) {
					return tmp_iter->second;
				}

				return hiaudio_encode_type_none;
			}
			/**
			* 表示音频编码名称
			*
			* @param name    表示音频模式名称
			*/
			inline hiaudio_sound_mode get_sound_mode(std::string name) {

				auto tmp_iter = get_sound_mode_map().find(name);
				if (tmp_iter != get_sound_mode_map().end()) {
					return tmp_iter->second;
				}

				return hiaudio_sound_mode_none;
			}
		private:
			/**
			* 表示编码类型名称与索引的对应表
			*/
			inline static const std::map<std::string, hiaudio_encode_tpe>& get_encode_type_map() {

				return m_encode_type_map;
			}
			/**
			* 表示通道类型名称与索引的对应表
			*/
			inline static const std::map<std::string, hiaudio_sound_mode>& get_sound_mode_map() {

				return m_sound_mode_map;
			}
		private:
			/**
			* 表示设备id
			*/
			int m_dev_id = 0;
			/**
			* 表示设备通道id
			*/
			int m_dev_channel = 0;
			/**
			* 表示编解码器通道
			*/
			int m_coder_channel = 0;
			/**
			 * 表示音频编码名称
			 */
			std::string m_encode_type = "";
			/**
			 * 表示音频采样频率
			 */
			int m_sample_rate = 44100;
			/**
			* 音频采样精度
			*/
			int m_bit_width = 0;
			/**
			 * 表示音频声道模式
			 */
			std::string m_sound_mode = "";
			/**
			* 表示是否重新采样。true表示需要重新采样；false表示不需要重新采样；
			*/
			bool m_resample = false;
			/**
			* 表示音频音量大小
			*/
			int m_volume = 50;
			/**
			* 表示是否使用音频增强
			*/
			bool m_use_vqe = false;
			/**
			* 表示编码类型名称与索引的对应表
			*/
			static const std::map<std::string, hiaudio_encode_tpe> m_encode_type_map;
			/**
			* 表示通道类型名称与索引的对应表
			*/
			static const std::map<std::string, hiaudio_sound_mode> m_sound_mode_map;
		};

	}

}
#endif // !defined(HIAUDIO_COMMON_CONF_H_INCLUDED_)
