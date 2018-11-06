/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-27

Description:std defined

**************************************************************************/







#ifndef	_PROT_GMP_SEMH_COMMAND_H_
#define _PROT_GMP_SEMH_COMMAND_H_







//********************中心服务器接口指令(10000--19999)*********************
//////////////////////////////////////////////////////////////////////////
//============================基础接口===================================
//--注册--
#define	GMP_SEMH_CENTER_CMD_REGISTER									10000
#define	GMP_SEMH_CENTER_CMD_REGISTER_RETURN								10001


//--取消注册--
#define	GMP_SEMH_CENTER_CMD_CANCEL_REGISTER								10002
#define	GMP_SEMH_CENTER_CMD_CANCEL_REGISTER_RETURN						10003


//--心跳保活--
#define	GMP_SEMH_CENTER_CMD_LIFE_HEART									10004
#define	GMP_SEMH_CENTER_CMD_LIFE_HEART_RETURN							10005


//--异常上报--
#define	GMP_SEMH_CENTER_CMD_EXCEPTION									10006
#define	GMP_SEMH_CENTER_CMD_EXCEPTION_RETURN							10007


//--广播查询信息--
#define	GMP_SEMH_CENTER_CMD_BROADCAST_QUERY								10008
#define	GMP_SEMH_CENTER_CMD_BROADCAST_QUERY_RETURN						10009




//============================媒体接口(12000--12999)=====================
//-------------------媒体管理接口(12000--12099)--------------------------



//-------------------媒体播放接口(12100--12199)--------------------------
//--媒体播放请求--
#define	GMP_SEMH_CENTER_CMD_MEDIA_PLAY_REQUEST							12100
#define	GMP_SEMH_CENTER_CMD_MEDIA_PLAY_REQUEST_RETURN					12101


//--媒体更新播放请求--
#define	GMP_SEMH_CENTER_CMD_MEDIA_PLAY_UPDATE							12102
#define	GMP_SEMH_CENTER_CMD_MEDIA_PLAY_UPDATE_RETURN					12103


//--媒体更新播放层请求--
#define	GMP_SEMH_CENTER_CMD_MEDIA_LAYER_UPDATE							12104
#define	GMP_SEMH_CENTER_CMD_MEDIA_LAYER_UPDATE_RETURN					12105


//--媒体停止请求--
#define	GMP_SEMH_CENTER_CMD_MEDIA_STOP									12106
#define	GMP_SEMH_CENTER_CMD_MEDIA_STOP_RETURN							12107


//--媒体关闭通知--
#define	GMP_SEMH_CENTER_CMD_MEDIA_CLOSE_NOTIFY							12108
#define	GMP_SEMH_CENTER_CMD_MEDIA_CLOSE_NOTIFY_RETURN					12109












//********************中间件服务器接口指令(20000--29999)******************
//////////////////////////////////////////////////////////////////////////
//============================基础接口(20000--20999)======================
//--心跳保活--
#define	GMP_SEMH_ACCESS_SERVER_CMD_LIFE_HEART							20000
#define	GMP_SEMH_ACCESS_SERVER_CMD_LIFE_HEART_RETURN					20001




//============================配置接口(21000--21999)=====================
//--获取设备信息--
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_DEV_INFO							21000
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_DEV_INFO_RETURN					21001


//--设置设备信息--
#define	GMP_SEMH_ACCESS_SERVER_CMD_SET_DEV_INFO							21002
#define	GMP_SEMH_ACCESS_SERVER_CMD_SET_DEV_INFO_RETURN					21003


//--启用设备--
#define	GMP_SEMH_ACCESS_SERVER_CMD_START_DEV							21004
#define	GMP_SEMH_ACCESS_SERVER_CMD_START_DEV_RETURN						21005


//--停用设备--
#define	GMP_SEMH_ACCESS_SERVER_CMD_STOP_DEV								21006
#define	GMP_SEMH_ACCESS_SERVER_CMD_STOP_DEV_RETURN						21007


//--网络配置--
#define	GMP_SEMH_ACCESS_SERVER_CMD_SET_NETWORK							21200
#define	GMP_SEMH_ACCESS_SERVER_CMD_SET_NETWORK_RETURN					21201




//============================媒体接口(22000--22999)=====================
//-----------------------媒体管理接口(22000--22099)----------------------
//--媒体添加请求--
#define	GMP_SEMH_ACCESS_SERVER_CMD_MEDIA_ADD							22000
#define	GMP_SEMH_ACCESS_SERVER_CMD_MEDIA_ADD_RETURN						22001


//--媒体删除请求--
#define	GMP_SEMH_ACCESS_SERVER_CMD_MEDIA_REMOVE							22002
#define	GMP_SEMH_ACCESS_SERVER_CMD_MEDIA_REMOVE_RETURN					22003


//--媒体获取信息请求--
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_MEDIA_INFO						22004
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_MEDIA_INFO_RETURN				22005


//--媒体更新请求--
#define	GMP_SEMH_ACCESS_SERVER_CMD_UPDATE_MEDIA_INFO					22006
#define	GMP_SEMH_ACCESS_SERVER_CMD_UPDATE_MEDIA_INFO_RETURN				22007




//-----------------------媒体播放接口(22100--22199)----------------------
//--媒体分配通道请求--
#define	GMP_SEMH_ACCESS_SERVER_CMD_CREATE_CHANNEL						22100
#define	GMP_SEMH_ACCESS_SERVER_CMD_CREATE_CHANNEL_RETURN				22101


//--媒体通道确认请求--
#define	GMP_SEMH_ACCESS_SERVER_CMD_ACCEPT_CHANNEL						22102
#define	GMP_SEMH_ACCESS_SERVER_CMD_ACCEPT_CHANNEL_RETURN				22103


//--媒体释放通道请求--
#define	GMP_SEMH_ACCESS_SERVER_CMD_FREE_CHANNEL							22104
#define	GMP_SEMH_ACCESS_SERVER_CMD_FREE_CHANNEL_RETURN					22105


//--媒体关闭通道通知--
#define	GMP_SEMH_ACCESS_SERVER_CMD_CLOSE_CHANNEL_NOTIFY					22106
#define	GMP_SEMH_ACCESS_SERVER_CMD_CLOSE_CHANNEL_NOTIFY_RETURN			22107


//--媒体通道信息查询--
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_CHANNEL_INFO						22108
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_CHANNEL_INFO_RETURN				22109













//*******************媒体服务器接口指令(30000--39999)**********************
//////////////////////////////////////////////////////////////////////////
//============================基础接口(30000--30999)======================
//--心跳保活--
#define	GMP_SEMH_MEDIA_SERVER_CMD_LIFE_HEART							30000
#define	GMP_SEMH_MEDIA_SERVER_CMD_LIFE_HEART_RETURN						30001



//============================配置接口(31000--31999)=====================
//--获取设备信息--
#define	GMP_SEMH_MEDIA_SERVER_CMD_GET_DEV_INFO							31000
#define	GMP_SEMH_MEDIA_SERVER_CMD_GET_DEV_INFO_RETURN					31001


//--设置设备信息--
#define	GMP_SEMH_MEDIA_SERVER_CMD_SET_DEV_INFO							31002
#define	GMP_SEMH_MEDIA_SERVER_CMD_SET_DEV_INFO_RETURN					31003


//--启用设备--
#define	GMP_SEMH_MEDIA_SERVER_CMD_START_DEV								31004
#define	GMP_SEMH_MEDIA_SERVER_CMD_START_DEV_RETURN						31005


//--停用设备--
#define	GMP_SEMH_MEDIA_SERVER_CMD_STOP_DEV								31006
#define	GMP_SEMH_MEDIA_SERVER_CMD_STOP_DEV_RETURN						31007


//--网络配置--
#define	GMP_SEMH_MEDIA_SERVER_CMD_SET_NETWORK							31200
#define	GMP_SEMH_MEDIA_SERVER_CMD_SET_NETWORK_RETURN					31201


//============================媒体接口(32000--32999)=====================
//-------------------媒体播放转发接口(32100--32199)----------------------
//--媒体播放请求--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_PLAY							32100
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_PLAY_RETURN						32101


//--媒体更新播放请求--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_PLAY_UPDATE						32102
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_PLAY_UPDATE_RETURN				32103


//--媒体更新播放层请求--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_LAYER_UPDATE					32104
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_LAYER_UPDATE_RETURN				32105


//--媒体停止请求--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_STOP							32106
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_STOP_RETURN						32107


//--媒体关闭通知--	
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_CLOSE_NOTIFY					32108
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_CLOSE_NOTIFY_RETURN				32109


//-------------------媒体信息查询接口(32200--32299)----------------------
//--媒体播放通道查询--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_GET_CHANNEL_INFO				32200
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_GET_CHANNEL_INFO_RETURN			32201












//*************控制客户端背景服务器接口指令(60000--69999)*****************
//////////////////////////////////////////////////////////////////////////
//============================基础接口(60000--60999)======================
//--心跳保活--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_LIFE_HEART						60000
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_LIFE_HEART_RETURN				60001



//============================配置接口(61000--61999)=====================
//--获取设备信息--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_GET_DEV_INFO						61000
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_GET_DEV_INFO_RETURN				61001


//--设置设备信息--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SET_DEV_INFO						61002
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SET_DEV_INFO_RETURN				61003


//--启用设备--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_START_DEV						61004
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_START_DEV_RETURN					61005


//--停用设备--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_STOP_DEV							61006
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_STOP_DEV_RETURN					61007


//--网络配置--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SET_NETWORK						61200
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SET_NETWORK_RETURN				61201



//============================媒体接口(62000--62999)=====================
//--接收背景图片块请求--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_PLAYER_PICTURE					62000
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_PLAYER_PICTURE_RETURN			62001


//--媒体客户端背景图片请求--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_CLIENT_PICTURE					62002
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_CLIENT_PICTURE_RETURN			62003


//--媒体实时发送背景图片请求--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SEND_PICTURE						62004
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SEND_PICTURE_RETURN				62005












#endif












