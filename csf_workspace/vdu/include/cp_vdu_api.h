/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_api.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_vdu_api.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_API_H_
#define _CP_VDU_API_H_



#include "cp_vdu.h"
#include "cp_vdu_status.h"



#ifdef __cplusplus
extern "C" {
#endif


	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_create
	*
	* ����ȫ��: cp_vdu_create
	*
	* ��������: public
	*
	* ����˵��: ����һ��cp_vdu_t����
	*
	*
	* �� �� ֵ: cp_vdu_t *
	*         ��NULL: �ɹ�
	*         NULL  : ʧ��
	*
	* ��    ע:��
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-2 15:10:45
	********************************************************************************/
	cp_extern cp_vdu_t *cp_vdu_create();

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_destroy
	*
	* ����ȫ��: cp_vdu_destroy
	*
	* ��������: public
	*
	* ����˵��: ����cp_vdu����
	*
	* ��    ��: cp_vdu_t       *vdu    [in]��Ҫ�����vdu��Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:56:18
	********************************************************************************/
	cp_extern int cp_vdu_destroy(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_version
	*
	* ����ȫ��: cp_vdu_get_version
	*
	* ��������: public
	*
	* ����˵��: ��ȡ�汾��Ϣ
	*
	* ��    ��: cp_vdu_t * vdu						[in/out]����˵��
	*
	* �� �� ֵ: cp_vdu_version_t
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 16:53:47
	********************************************************************************/
	cp_vdu_version_t cp_vdu_get_version(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_status
	*
	* ����ȫ��: cp_vdu_get_status
	*
	* ��������: public
	*
	* ����˵��: ��ʾ��ȡ��ǰ��״̬��
	*
	* ��    ��: cp_vdu_t * vdu						[in/out]����˵��
	*
	* �� �� ֵ: cp_vdu_status_e
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 17:10:50
	********************************************************************************/
	cp_vdu_status_e cp_vdu_get_status(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_set_coordinate
	*
	* ����ȫ��: cp_vdu_set_coordinate
	*
	* ��������: public
	*
	* ����˵��: ����������Ϣ,������Ϊģ��������ϵ�е�ԭ�����ꡣ
	*
	* ��    ��: cp_vdu_t       *vdu    [in]��Ҫ�����vdu��Ϣ
	* ��    ��: cp_vdu_coordinate_t coordinate		[in]��ʼ������Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:
	*			1���ýӿڿ��Բ�ʹ��ʱ��Ĭ��λ��Ϊ(0, 0, 0)
	*			2�����ʹ�øýӿڣ������е�roi��rect��ʹ���Դ�Ϊԭ�����������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:57:24
	********************************************************************************/
	cp_extern int cp_vdu_set_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t coordinate);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_coordinate
	*
	* ����ȫ��: cp_vdu_get_coordinate
	*
	* ��������: public
	*
	* ����˵��: ��ȡ��ʼ������Ϣ
	*
	* ��    ��: cp_vdu_t       *vdu    [in]��Ҫ�����vdu��Ϣ
	* ��    ��: cp_vdu_coordinate_t *coordinate    [in]��Ҫ�����vdu��Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:57:32
	********************************************************************************/
	cp_extern int cp_vdu_get_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t *coordinate);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_set_type
	*
	* ����ȫ��: cp_vdu_set_type
	*
	* ��������: public
	*
	* ����˵��: �豸vdu������
	*
	* ��    ��: cp_vdu_t * vdu						[in/out]����˵��
	* ��    ��: cp_vdu_type_e type						[in/out]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 11:17:07
	********************************************************************************/
	cp_extern int cp_vdu_set_type(cp_vdu_t *vdu, cp_vdu_type_e type);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_type
	*
	* ����ȫ��: cp_vdu_get_type
	*
	* ��������: public
	*
	* ����˵��: ��ȡvdu������
	*
	* ��    ��: cp_vdu_t * vdu						[in/out]����˵��
	*
	* �� �� ֵ: cp_vdu_type_e
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 11:17:28
	********************************************************************************/
	cp_vdu_type_e cp_vdu_get_type(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_set_roi
	*
	* ����ȫ��: cp_vdu_set_roi
	*
	* ��������: public
	*
	* ����˵��: ���ø���Ȥ����
	*
	* ��    ��: cp_vdu_t       *vdu				[in]��Ҫ�����vdu��Ϣ
	* ��    ��: cp_vdu_rect_t	rect			[in]���ø���Ȥ����λ����Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:57:35
	********************************************************************************/
	cp_extern int cp_vdu_set_roi(cp_vdu_t *vdu, cp_vdu_rect_t rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_roi
	*
	* ����ȫ��: cp_vdu_get_roi
	*
	* ��������: public
	*
	* ����˵��: ��ȡ����Ȥ����
	*
	* ��    ��: cp_vdu_t       *vdu             [in]��Ҫ�����vdu��Ϣ
	* ��    ��: cp_vdu_rect_t *rect             [in]��Ҫ�����vdu��Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:57:40
	********************************************************************************/
	cp_extern int cp_vdu_get_roi(cp_vdu_t *vdu, cp_vdu_rect_t *rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_clear_roi
	*
	* ����ȫ��: cp_vdu_clear_roi
	*
	* ��������: public
	*
	* ����˵��: �������Ȥ����
	*
	* ��    ��: cp_vdu_t       *vdu             [in]��Ҫ�����vdu��Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:00
	********************************************************************************/
	cp_extern int cp_vdu_clear_roi(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_roi_pixel
	*
	* ����ȫ��: cp_vdu_get_roi_pixel
	*
	* ��������: public
	*
	* ����˵��: ��ȡ����Ȥ����λͼ��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]��Ҫ�����vdu��Ϣ
	* ��    ��: char * buf						[out]����˵��
	* ��    ��: int len							[in]����˵��
	* ��    ��: cp_vdu_pixel_format_e vpf		[in]����˵��
	* ��    ��: cp_vdu_rect_t *scale_rect		[in]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:05
	********************************************************************************/
	cp_extern int cp_vdu_get_roi_pixel(cp_vdu_t *vdu,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_rect_pixel
	*
	* ����ȫ��: cp_vdu_get_rect_pixel
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]��Ҫ�����vdu��Ϣ
	* ��    ��: char * buf						[out]����˵��
	* ��    ��: int len							[in]����˵��
	* ��    ��: cp_vdu_pixel_format_e vpf		[in]����˵��
	* ��    ��: cp_vdu_rect_t rect				[in]����˵��
	* ��    ��: cp_vdu_rect_t *scale_rect		[in]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:14
	********************************************************************************/
	cp_extern int cp_vdu_get_rect_pixel(cp_vdu_t *vdu,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t rect,
		cp_vdu_rect_t *scale_rect);






	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_create_channel
	*
	* ����ȫ��: cp_vdu_create_channel
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]��Ҫ�����vdu��Ϣ
	* ��    ��: cp_vdu_channel_type_e channel_type             [in]������ͨ������
	*
	* �� �� ֵ: cp_vdu_channel_t*
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:17
	********************************************************************************/
	cp_vdu_channel_t* cp_vdu_create_channel(cp_vdu_t *vdu, cp_vdu_channel_type_e channel_type);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_destroy_all_channels
	*
	* ����ȫ��: cp_vdu_destroy_all_channels
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]��Ҫ�����vdu��Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:23
	********************************************************************************/
	cp_extern int cp_vdu_destroy_all_channels(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_destroy_channel
	*
	* ����ȫ��: cp_vdu_destroy_channel
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel						[in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:28
	********************************************************************************/
	cp_extern int cp_vdu_destroy_channel(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_status
	*
	* ����ȫ��: cp_vdu_channel_get_status
	*
	* ��������: public
	*
	* ����˵��: ��ʾ��ȡ��ǰ��״̬��
	*
	* ��    ��: cp_vdu_t * vdu						[in/out]����˵��
	*
	* �� �� ֵ: cp_vdu_status_e
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 17:13:32
	********************************************************************************/
	cp_extern cp_vdu_status_e cp_vdu_channel_get_status(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_insert_channel
	*
	* ����ȫ��: cp_vdu_insert_channel
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]��Ҫ�����vdu��Ϣ
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:34
	********************************************************************************/
	cp_extern int cp_vdu_insert_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_remove_channel
	*
	* ����ȫ��: cp_vdu_remove_channel
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]��Ҫ�����vdu��Ϣ
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:39
	********************************************************************************/
	cp_extern int cp_vdu_remove_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_set_index
	*
	* ����ȫ��: cp_vdu_channel_set_index
	*
	* ��������: public
	*
	* ����˵��: �ú�����Ҫ�����豸ͨ�������š�
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: const int index						[in/out]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:
	*			1��ͨ�������ţ���ʾͨ����cp_vdu�еĲ�ι�ϵ��������Խ��Խ�����ϲ㡣
	*			2��ͨ��������ȡֵ��[0, 65535)
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:42
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_index(cp_vdu_channel_t *vdu_channel, const int index);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_index
	*
	* ����ȫ��: cp_vdu_channel_get_index
	*
	* ��������: public
	*
	* ����˵��: ��ȡͨ����������Ϣ
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 11:07:16
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_index(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_set_vector_stream
	*
	* ����ȫ��: cp_vdu_channel_set_vector_stream
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_vector_stream_type_e vs_type						[in/out]����˵��
	* ��    ��: const char * buf						[in/out]����˵��
	* ��    ��: const int len						[in/out]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 11:14:51
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_vector_stream(cp_vdu_channel_t *vdu_channel,
		cp_vdu_vector_stream_type_e vs_type, const char *buf, const int len);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_set_roi
	*
	* ����ȫ��: cp_vdu_channel_set_roi
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_rect_t rect						[in/out]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:51
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_roi
	*
	* ����ȫ��: cp_vdu_channel_get_roi
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_rect_t *roi_rect      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: cp_vdu_rect_t
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:56
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t *roi_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_clear_roi
	*
	* ����ȫ��: cp_vdu_channel_clear_roi
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:01
	********************************************************************************/
	cp_extern int cp_vdu_channel_clear_roi(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_roi_pixel
	*
	* ����ȫ��: cp_vdu_channel_get_roi_pixel
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: char * buf						[in/out]����˵��
	* ��    ��: int len						[in/out]����˵��
	* ��    ��: cp_vdu_pixel_format_e vpf						[in/out]����˵��
	* ��    ��: cp_vdu_rect_t *scale_rect						[in/out]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi_pixel(cp_vdu_channel_t *vdu_channel,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_roi_pixel_by_image_info
	*
	* ����ȫ��: cp_vdu_channel_get_roi_pixel_by_image_info
	*
	* ��������: public
	*
	* ����˵��: ����image info��rectָ��������ͼ������imageͼƬ
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_image_info_t *image_info						[in/out]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi_pixel_by_image_info(
		cp_vdu_channel_t *vdu_channel,
		cp_vdu_image_info_t *image_info);


	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_rect_pixel
	*
	* ����ȫ��: cp_vdu_channel_get_rect_pixel
	*
	* ��������: public
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: char * buf						[in/out]����˵��
	* ��    ��: int len						[in/out]����˵��
	* ��    ��: cp_vdu_rect_t rect						[in/out]����˵��
	* ��    ��: cp_vdu_pixel_format_e vpf						[in/out]����˵��
	* ��    ��: cp_vdu_rect_t *scale_rect						[in/out]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:09
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_rect_pixel(cp_vdu_channel_t *vdu_channel,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t rect,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_rect_pixel_by_image_info
	*
	* ����ȫ��: cp_vdu_channel_get_rect_pixel_by_image_info
	*
	* ��������: public
	*
	* ����˵��: ����image info��rectָ��������ͼ������imageͼƬ
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_image_info_t *image_info						[in/out]����˵��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_rect_pixel_by_image_info(
		cp_vdu_channel_t *vdu_channel,
		cp_vdu_image_info_t *image_info);








#ifdef __cplusplus
}
#endif


#endif //_CP_VDU_API_H_


