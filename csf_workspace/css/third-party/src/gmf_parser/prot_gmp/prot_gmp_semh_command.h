/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-27

Description:std defined

**************************************************************************/







#ifndef	_PROT_GMP_SEMH_COMMAND_H_
#define _PROT_GMP_SEMH_COMMAND_H_







//********************���ķ������ӿ�ָ��(10000--19999)*********************
//////////////////////////////////////////////////////////////////////////
//============================�����ӿ�===================================
//--ע��--
#define	GMP_SEMH_CENTER_CMD_REGISTER									10000
#define	GMP_SEMH_CENTER_CMD_REGISTER_RETURN								10001


//--ȡ��ע��--
#define	GMP_SEMH_CENTER_CMD_CANCEL_REGISTER								10002
#define	GMP_SEMH_CENTER_CMD_CANCEL_REGISTER_RETURN						10003


//--��������--
#define	GMP_SEMH_CENTER_CMD_LIFE_HEART									10004
#define	GMP_SEMH_CENTER_CMD_LIFE_HEART_RETURN							10005


//--�쳣�ϱ�--
#define	GMP_SEMH_CENTER_CMD_EXCEPTION									10006
#define	GMP_SEMH_CENTER_CMD_EXCEPTION_RETURN							10007


//--�㲥��ѯ��Ϣ--
#define	GMP_SEMH_CENTER_CMD_BROADCAST_QUERY								10008
#define	GMP_SEMH_CENTER_CMD_BROADCAST_QUERY_RETURN						10009




//============================ý��ӿ�(12000--12999)=====================
//-------------------ý�����ӿ�(12000--12099)--------------------------



//-------------------ý�岥�Žӿ�(12100--12199)--------------------------
//--ý�岥������--
#define	GMP_SEMH_CENTER_CMD_MEDIA_PLAY_REQUEST							12100
#define	GMP_SEMH_CENTER_CMD_MEDIA_PLAY_REQUEST_RETURN					12101


//--ý����²�������--
#define	GMP_SEMH_CENTER_CMD_MEDIA_PLAY_UPDATE							12102
#define	GMP_SEMH_CENTER_CMD_MEDIA_PLAY_UPDATE_RETURN					12103


//--ý����²��Ų�����--
#define	GMP_SEMH_CENTER_CMD_MEDIA_LAYER_UPDATE							12104
#define	GMP_SEMH_CENTER_CMD_MEDIA_LAYER_UPDATE_RETURN					12105


//--ý��ֹͣ����--
#define	GMP_SEMH_CENTER_CMD_MEDIA_STOP									12106
#define	GMP_SEMH_CENTER_CMD_MEDIA_STOP_RETURN							12107


//--ý��ر�֪ͨ--
#define	GMP_SEMH_CENTER_CMD_MEDIA_CLOSE_NOTIFY							12108
#define	GMP_SEMH_CENTER_CMD_MEDIA_CLOSE_NOTIFY_RETURN					12109












//********************�м���������ӿ�ָ��(20000--29999)******************
//////////////////////////////////////////////////////////////////////////
//============================�����ӿ�(20000--20999)======================
//--��������--
#define	GMP_SEMH_ACCESS_SERVER_CMD_LIFE_HEART							20000
#define	GMP_SEMH_ACCESS_SERVER_CMD_LIFE_HEART_RETURN					20001




//============================���ýӿ�(21000--21999)=====================
//--��ȡ�豸��Ϣ--
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_DEV_INFO							21000
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_DEV_INFO_RETURN					21001


//--�����豸��Ϣ--
#define	GMP_SEMH_ACCESS_SERVER_CMD_SET_DEV_INFO							21002
#define	GMP_SEMH_ACCESS_SERVER_CMD_SET_DEV_INFO_RETURN					21003


//--�����豸--
#define	GMP_SEMH_ACCESS_SERVER_CMD_START_DEV							21004
#define	GMP_SEMH_ACCESS_SERVER_CMD_START_DEV_RETURN						21005


//--ͣ���豸--
#define	GMP_SEMH_ACCESS_SERVER_CMD_STOP_DEV								21006
#define	GMP_SEMH_ACCESS_SERVER_CMD_STOP_DEV_RETURN						21007


//--��������--
#define	GMP_SEMH_ACCESS_SERVER_CMD_SET_NETWORK							21200
#define	GMP_SEMH_ACCESS_SERVER_CMD_SET_NETWORK_RETURN					21201




//============================ý��ӿ�(22000--22999)=====================
//-----------------------ý�����ӿ�(22000--22099)----------------------
//--ý���������--
#define	GMP_SEMH_ACCESS_SERVER_CMD_MEDIA_ADD							22000
#define	GMP_SEMH_ACCESS_SERVER_CMD_MEDIA_ADD_RETURN						22001


//--ý��ɾ������--
#define	GMP_SEMH_ACCESS_SERVER_CMD_MEDIA_REMOVE							22002
#define	GMP_SEMH_ACCESS_SERVER_CMD_MEDIA_REMOVE_RETURN					22003


//--ý���ȡ��Ϣ����--
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_MEDIA_INFO						22004
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_MEDIA_INFO_RETURN				22005


//--ý���������--
#define	GMP_SEMH_ACCESS_SERVER_CMD_UPDATE_MEDIA_INFO					22006
#define	GMP_SEMH_ACCESS_SERVER_CMD_UPDATE_MEDIA_INFO_RETURN				22007




//-----------------------ý�岥�Žӿ�(22100--22199)----------------------
//--ý�����ͨ������--
#define	GMP_SEMH_ACCESS_SERVER_CMD_CREATE_CHANNEL						22100
#define	GMP_SEMH_ACCESS_SERVER_CMD_CREATE_CHANNEL_RETURN				22101


//--ý��ͨ��ȷ������--
#define	GMP_SEMH_ACCESS_SERVER_CMD_ACCEPT_CHANNEL						22102
#define	GMP_SEMH_ACCESS_SERVER_CMD_ACCEPT_CHANNEL_RETURN				22103


//--ý���ͷ�ͨ������--
#define	GMP_SEMH_ACCESS_SERVER_CMD_FREE_CHANNEL							22104
#define	GMP_SEMH_ACCESS_SERVER_CMD_FREE_CHANNEL_RETURN					22105


//--ý��ر�ͨ��֪ͨ--
#define	GMP_SEMH_ACCESS_SERVER_CMD_CLOSE_CHANNEL_NOTIFY					22106
#define	GMP_SEMH_ACCESS_SERVER_CMD_CLOSE_CHANNEL_NOTIFY_RETURN			22107


//--ý��ͨ����Ϣ��ѯ--
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_CHANNEL_INFO						22108
#define	GMP_SEMH_ACCESS_SERVER_CMD_GET_CHANNEL_INFO_RETURN				22109













//*******************ý��������ӿ�ָ��(30000--39999)**********************
//////////////////////////////////////////////////////////////////////////
//============================�����ӿ�(30000--30999)======================
//--��������--
#define	GMP_SEMH_MEDIA_SERVER_CMD_LIFE_HEART							30000
#define	GMP_SEMH_MEDIA_SERVER_CMD_LIFE_HEART_RETURN						30001



//============================���ýӿ�(31000--31999)=====================
//--��ȡ�豸��Ϣ--
#define	GMP_SEMH_MEDIA_SERVER_CMD_GET_DEV_INFO							31000
#define	GMP_SEMH_MEDIA_SERVER_CMD_GET_DEV_INFO_RETURN					31001


//--�����豸��Ϣ--
#define	GMP_SEMH_MEDIA_SERVER_CMD_SET_DEV_INFO							31002
#define	GMP_SEMH_MEDIA_SERVER_CMD_SET_DEV_INFO_RETURN					31003


//--�����豸--
#define	GMP_SEMH_MEDIA_SERVER_CMD_START_DEV								31004
#define	GMP_SEMH_MEDIA_SERVER_CMD_START_DEV_RETURN						31005


//--ͣ���豸--
#define	GMP_SEMH_MEDIA_SERVER_CMD_STOP_DEV								31006
#define	GMP_SEMH_MEDIA_SERVER_CMD_STOP_DEV_RETURN						31007


//--��������--
#define	GMP_SEMH_MEDIA_SERVER_CMD_SET_NETWORK							31200
#define	GMP_SEMH_MEDIA_SERVER_CMD_SET_NETWORK_RETURN					31201


//============================ý��ӿ�(32000--32999)=====================
//-------------------ý�岥��ת���ӿ�(32100--32199)----------------------
//--ý�岥������--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_PLAY							32100
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_PLAY_RETURN						32101


//--ý����²�������--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_PLAY_UPDATE						32102
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_PLAY_UPDATE_RETURN				32103


//--ý����²��Ų�����--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_LAYER_UPDATE					32104
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_LAYER_UPDATE_RETURN				32105


//--ý��ֹͣ����--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_STOP							32106
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_STOP_RETURN						32107


//--ý��ر�֪ͨ--	
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_CLOSE_NOTIFY					32108
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_CLOSE_NOTIFY_RETURN				32109


//-------------------ý����Ϣ��ѯ�ӿ�(32200--32299)----------------------
//--ý�岥��ͨ����ѯ--
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_GET_CHANNEL_INFO				32200
#define	GMP_SEMH_MEDIA_SERVER_CMD_MEDIA_GET_CHANNEL_INFO_RETURN			32201












//*************���ƿͻ��˱����������ӿ�ָ��(60000--69999)*****************
//////////////////////////////////////////////////////////////////////////
//============================�����ӿ�(60000--60999)======================
//--��������--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_LIFE_HEART						60000
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_LIFE_HEART_RETURN				60001



//============================���ýӿ�(61000--61999)=====================
//--��ȡ�豸��Ϣ--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_GET_DEV_INFO						61000
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_GET_DEV_INFO_RETURN				61001


//--�����豸��Ϣ--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SET_DEV_INFO						61002
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SET_DEV_INFO_RETURN				61003


//--�����豸--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_START_DEV						61004
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_START_DEV_RETURN					61005


//--ͣ���豸--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_STOP_DEV							61006
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_STOP_DEV_RETURN					61007


//--��������--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SET_NETWORK						61200
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SET_NETWORK_RETURN				61201



//============================ý��ӿ�(62000--62999)=====================
//--���ձ���ͼƬ������--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_PLAYER_PICTURE					62000
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_PLAYER_PICTURE_RETURN			62001


//--ý��ͻ��˱���ͼƬ����--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_CLIENT_PICTURE					62002
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_CLIENT_PICTURE_RETURN			62003


//--ý��ʵʱ���ͱ���ͼƬ����--
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SEND_PICTURE						62004
#define	GMP_SEMH_CLIENT_BACKGROUND_CMD_SEND_PICTURE_RETURN				62005












#endif












