/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_error.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/26
*
*Description: create (cp_vdu_error.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_STATUS_H_
#define _CP_VDU_STATUS_H_




#ifdef __cplusplus
extern "C" {
#endif



//��ʾ��ֵ����
#define	cp_vdu_negative_value(x)			(-(x))



typedef	enum cp_vdu_status_enum									cp_vdu_status_e;
typedef	enum cp_vdu_status_name_enum							cp_vdu_status_name_e;



/************************************************************************/
/* ����������                                                          */
/************************************************************************/
enum cp_vdu_status_enum
{
	cp_vdu_status_success = 0x000000,
	cp_vdu_status_failed = cp_vdu_negative_value(0x0F0000),
	cp_vdu_status_null_pointer,
	cp_vdu_status_invalid_parametes,
	cp_vdu_status_system_error,
	cp_vdu_status_module_not_ready,
	cp_vdu_status_unsupport_pixel_format,
	cp_vdu_status_not_more_buffer,
	cp_vdu_status_channel_index_existed,
	cp_vdu_status_create_source_failed,
	cp_vdu_status_operation_option_failed,
};





/* Expand this list if necessary. */
/************************************************************************/
/* �������˵������                                                      */
/************************************************************************/
#define CP_VDU_STATUS_NAME_MAP(CP_VDU_STATUS)												\
	CP_VDU_STATUS(null_pointer, "null pointer error")										\
	CP_VDU_STATUS(invalid_parametes, "invalid parametes")									\
	CP_VDU_STATUS(system_error, "system error")												\
	CP_VDU_STATUS(module_not_ready, "library module not ready")								\
	CP_VDU_STATUS(unsupport_pixel_format, "system unsupport pixel format")					\
	CP_VDU_STATUS(not_more_buffer, "input not more process buffer")							\
	CP_VDU_STATUS(channel_index_existed, "this index of channel existed")					\
	CP_VDU_STATUS(create_source_failed, "create source failed")								\




enum cp_vdu_status_name_enum {
#define CP_VDU_STATUS(type, _) cp_vdu_status_name_ ## type = cp_vdu_status_ ## type,
	CP_VDU_STATUS_NAME_MAP(CP_VDU_STATUS)
#undef CP_VDU_STATUS
};



/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_strstatus
*
* ����ȫ��: cp_vdu_strstatus
*
* ��������: public 
*
* ����˵��: ��ȡ״̬���Ӧ���ַ�����
*
* ��    ��: cp_vdu_status_e						[in/out]����˵��
*
* �� �� ֵ: const char*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-5 17:08:10
********************************************************************************/
const char* cp_vdu_strstatus(cp_vdu_status_e status);


#ifdef __cplusplus
}
#endif


#endif //_CP_VDU_STATUS_H_

