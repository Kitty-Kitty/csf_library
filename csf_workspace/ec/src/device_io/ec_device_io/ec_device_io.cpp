/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: ec_device_io.hpp
*
*Version: 1.0
*
*Date: 26-11月-2019 21:35:52
*
*Description: Class(ec_device_io)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "ec_device_io.hpp"
#include "hivideo_channel_conf.hpp"

using ec::device_io::ec_device_io;


ec_device_io::~ec_device_io() {

}





/**
 * * 主要功能是：主要实现模块的配置信息处理接口。
 * * 返回：0表示成功；非0表示失败；
 * *
 * * @param element    表示模块的配置信息
 * *
 * * 常用的配置信息保存结构为：
 * * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
 * * <module>
 * *        <!--***表示模块对应的模块名称信息***-->
 * *        <name>csf_connection</name>
 * *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
 * *        <mid>02000000-0000001</mid>
 * *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
 * *        <configure>
 * *                <!--表示线程数量-->
 * *                <thread_number>4</thread_number>
 * *        </configure>
 * * </module>
 *
 */
csf_int32 ec_device_io::configure(const csf_element& element) {

	//根配置信息
	get_attribute_manager().set_root_element(&element);

	return 0;
}


/**
 * 模块初始化
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 ec_device_io::init(const csf_configure_manager* conf_mg) {

	//设置海思相关配置
	parse_hiprocessor_configure(*get_attribute_manager().get_root_element());
	return 0;
}


/**
 * 模块启动
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 ec_device_io::start(const csf_configure_manager* conf_mg) {

	csf_int32		tmp_ret = 0;


	//启动hiprocessor,
	tmp_ret = start_hiprocessor(conf_mg);
	if (tmp_ret) {
		csf_log(error, "start hiprocessor failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "start hiprocessor succeed!");
	}

	return 0;
}


/**
 * 模块停止
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 ec_device_io::stop(const csf_configure_manager* conf_mg) {

	return 0;
}


/**
* 模块启动
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 ec_device_io::start_hiprocessor(const csf_configure_manager* conf_mg) {

	csf_int32		tmp_ret = 0;


	//初始化hiprocessor,
	tmp_ret = get_hiprocessor().init(conf_mg);
	if (tmp_ret) {
		csf_log(error, "hiprocessor init failed!");
		return csf_failure;
	}
	//启动hiprocessor,
	tmp_ret = get_hiprocessor().start(conf_mg);
	if (tmp_ret) {
		csf_log(error, "hiprocessor start failed!");
		return csf_failure;
	}

	return 0;
}


/**
* 模块停止
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 ec_device_io::stop_hiprocessor(const csf_configure_manager* conf_mg) {
	
	csf_int32		tmp_ret = 0;


	//停止hiprocessor,
	tmp_ret = get_hiprocessor().stop(conf_mg);
	if (tmp_ret) {
		csf_log(error, "hiprocessor stop failed!");
		return csf_failure;
	}
	return 0;
}


/**
* * 主要功能是：主要海思设备相关的配置信息处理接口。
* * 返回：0表示成功；非0表示失败；
* *
* * @param element    表示模块的配置信息
* *
* * 常用的配置信息保存结构为：
* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
* * <module>
* *        <!--***表示模块对应的模块名称信息***-->
* *        <name>csf_connection</name>
* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
* *        <mid>02000000-0000001</mid>
* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
* *        <configure>
* *                <!--表示线程数量-->
* *                <thread_number>4</thread_number>
* *        </configure>
* * </module>
*
*/
csf_int32 ec_device_io::parse_hiprocessor_configure(const csf_element& element) {

	parse_hiroot_configure(element);
	parse_hisiv_video_configure(element);
	parse_hisiv_audio_configure(element);

	return csf_succeed;
}


/**
* * 主要功能是：海思主要配置文件。
* * 返回：0表示成功；非0表示失败；
* *
* * @param element    表示模块的配置信息
* *
* * 常用的配置信息保存结构为：
* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
* * <module>
* *        <!--***表示模块对应的模块名称信息***-->
* *        <name>csf_connection</name>
* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
* *        <mid>02000000-0000001</mid>
* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
* *        <configure>
* *                <!--表示线程数量-->
* *                <thread_number>4</thread_number>
* *        </configure>
* * </module>
*
* @param element    表示模块的配置信息
*/
csf_int32 ec_device_io::parse_hiroot_configure(const csf_element& element) {

	//表示海思平台的功耗场景类型
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_system_profile)
		, csf_attribute_string(std::list<csf_string>{ "hisiv_configure", "system", "profile" }
		, csf_attribute_exception()));

	//表示对齐方式
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_system_align_width)
		, csf_attribute_int(std::list<csf_string>{ "hisiv_configure", "system", "align_width" }
		, csf_attribute_boundary("(0, 32)")
		, csf_attribute_default_value<csf_attribute_int, csf_int32>(16)));

	//表示最大内存池数量
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_system_max_pool_count)
		, csf_attribute_int(std::list<csf_string>{ "hisiv_configure", "system", "max_pool_count" }
	, csf_attribute_boundary("(0, 256)")
		, csf_attribute_default_value<csf_attribute_int, csf_int32>(64)));

	//设置配置信息
	get_hiprocessor().get_hiconf().get_sys_conf().set_profile(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(hisiv_system_profile))
		);
	get_hiprocessor().get_hiconf().get_sys_conf().set_align_width(
		get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(hisiv_system_align_width))
	);
	get_hiprocessor().get_hiconf().get_sys_conf().set_max_pool_count(
		get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(hisiv_system_max_pool_count))
	);

	return csf_succeed;
}
/**
* * 主要功能是：海思视频配置文件。
* * 返回：0表示成功；非0表示失败；
* *
* * @param element    表示模块的配置信息
* *
* * 常用的配置信息保存结构为：
* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
* * <module>
* *        <!--***表示模块对应的模块名称信息***-->
* *        <name>csf_connection</name>
* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
* *        <mid>02000000-0000001</mid>
* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
* *        <configure>
* *                <!--表示线程数量-->
* *                <thread_number>4</thread_number>
* *        </configure>
* * </module>
*/
csf_int32 ec_device_io::parse_hisiv_video_configure(const csf_element& element) {

	//表示存储文件的目录地址

 	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_video_storage_path)
 		, csf_attribute_string(std::list<csf_string>{ "storage", "path" }
 		, csf_attribute_exception_critical()));

	//表示单文件回滚最大大小
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_video_storage_rotation_size)
		, csf_attribute_space_size(std::list<csf_string>{ "storage", "rotation_size" }
		, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
		, csf_attribute_boundary("(1000, n)")
		, csf_attribute_exception_critical()));

	//表示日志占用磁盘最大大小
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_video_stored_max_size)
		, csf_attribute_space_size(std::list<csf_string>{ "storage", "stored_max_size" }
		, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
		, csf_attribute_boundary("(1000, n)")
		, csf_attribute_exception_critical()));

	//表示磁盘空间最小多大的时候才能写日志
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_video_stored_disk_min_free_size)
		, csf_attribute_space_size(std::list<csf_string>{ "storage", "disk_min_free_size" }
		, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
		, csf_attribute_boundary("(1000, n)")
		, csf_attribute_exception_critical()));

	//表示视频文件的播放时间长度
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_video_duration)
		, csf_attribute_time(std::list<csf_string>{ "video", "duration" }
		, csf_attribute_time::csf_time_unit_s
		, csf_attribute_boundary("(60, n)")
		, csf_attribute_exception_critical()));



	hivideo_channel_conf *tmp_conf = new hivideo_channel_conf();

	get_attribute_manager().get_value<csf_attribute_space_size>(CSF_LOGGER_ATTRIBUTE_NAME(rotation_size));

	//表示存储文件的目录地址
	//get_hiprocessor().get_hiconf().get_video_conf().
	tmp_conf->get_disk_storage().set_path(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(hisiv_video_storage_path))
	);
	tmp_conf->get_disk_storage().set_rotation_size(
		get_attribute_manager().get_value<csf_attribute_space_size>(CSF_ATTRIBUTE_NAME(hisiv_video_storage_rotation_size))
	);
	tmp_conf->get_disk_storage().set_stored_max_size(
		get_attribute_manager().get_value<csf_attribute_space_size>(CSF_ATTRIBUTE_NAME(hisiv_video_stored_max_size))
	);
	tmp_conf->get_disk_storage().set_disk_min_free_size(
		get_attribute_manager().get_value<csf_attribute_space_size>(CSF_ATTRIBUTE_NAME(hisiv_video_stored_disk_min_free_size))
	);


	tmp_conf->get_video_storage().set_duration(
		get_attribute_manager().get_value<csf_attribute_time>(CSF_ATTRIBUTE_NAME(hisiv_video_duration))
	);



	get_hiprocessor().get_hiconf().get_video_conf().add("video_configure", tmp_conf);

	return csf_succeed;
}
/**
* * 主要功能是：海思音频配置文件。
* * 返回：0表示成功；非0表示失败；
* *
* * @param element    表示模块的配置信息
* *
* * 常用的配置信息保存结构为：
* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
* * <module>
* *        <!--***表示模块对应的模块名称信息***-->
* *        <name>csf_connection</name>
* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
* *        <mid>02000000-0000001</mid>
* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
* *        <configure>
* *                <!--表示线程数量-->
* *                <thread_number>4</thread_number>
* *        </configure>
* * </module>
*
* @param element    表示模块的配置信息
*/
csf_int32 ec_device_io::parse_hisiv_audio_configure(const csf_element& element) {

	//表示采集设备编号
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_device_id)
		, csf_attribute_int(std::list<csf_string>{ "hisiv_audio", "device_id" }
		, csf_attribute_boundary("[0, 10)")
		, csf_attribute_exception()));

	//表示采集设备通道编号
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_device_channel)
		, csf_attribute_int(std::list<csf_string>{ "hisiv_audio", "device_channel" }
		, csf_attribute_boundary("[0, 10)")
		, csf_attribute_exception()));

	//表示采集设备编码器通道编号
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_encode_channel)
		, csf_attribute_int(std::list<csf_string>{ "hisiv_audio", "encode_channel" }
		, csf_attribute_boundary("[0, 10)")
		, csf_attribute_exception()));

	//表示编码类型名称
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_encode_tpe)
		, csf_attribute_string(std::list<csf_string>{ "hisiv_audio", "encode_tpe" }
		, csf_attribute_exception()));

	//表示音频采样
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_sample_rate)
		, csf_attribute_int(std::list<csf_string>{ "hisiv_audio", "sample_rate" }
		, csf_attribute_boundary("[8000, 96000]")
		, csf_attribute_exception()));

	//音频采样精度
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_bit_width)
		, csf_attribute_int(std::list<csf_string>{ "hisiv_audio", "bit_width" }
		, csf_attribute_boundary("(0, 32]")
		, csf_attribute_exception()));

	//音频声道模式
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_sound_mode)
		, csf_attribute_string(std::list<csf_string>{ "hisiv_audio", "sound_mode" }
		, csf_attribute_exception()));
	
	//表示音频音量数值大小
	//
 	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_volume)
 		, csf_attribute_int(std::list<csf_string>{ "hisiv_audio", "volume" }
 		, csf_attribute_boundary("[0, 100]")
 		, csf_attribute_default_value<csf_attribute_int, csf_int32>(50)));
	//音频是否重采样
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_resample)
		, csf_attribute_bool(std::list<csf_string>{ "hisiv_audio", "resample" }
		, csf_attribute_exception()));

	//音频是否重采样
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(hisiv_audio_use_vqe)
		, csf_attribute_bool(std::list<csf_string>{ "hisiv_audio", "use_vqe" }
		, csf_attribute_exception()));


	//设置配置参数
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_dev_id(
		get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(hisiv_audio_device_id))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_dev_channel(
		get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(hisiv_audio_device_channel))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_coder_channel(
		get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(hisiv_audio_encode_channel))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_encode_type(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(hisiv_audio_encode_tpe))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_sample_rate(
		get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(hisiv_audio_sample_rate))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_bit_width(
		get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(hisiv_audio_bit_width))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_sound_mode(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(hisiv_audio_sound_mode))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_volume(
		get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(hisiv_audio_volume))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_resample(
		get_attribute_manager().get_value<csf_attribute_bool>(CSF_ATTRIBUTE_NAME(hisiv_audio_resample))
	);
	get_hiprocessor().get_hiconf().get_audio_conf().get_ai_conf().set_use_vqe(
		get_attribute_manager().get_value<csf_attribute_bool>(CSF_ATTRIBUTE_NAME(hisiv_audio_use_vqe))
	);



	return csf_succeed;
}




/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* 表示模块的create 和 destroy 句柄定义。                                              */
/* 每个需要通过模块工厂创建的模块都需要添加该宏定义。                                    */
/* 其中module_type表示该模块的类名称，该类实现了构造方法为：                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(ec_device_io)