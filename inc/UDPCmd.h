#pragma once

//ϵͳ�Լ��� ����������Ե�ID
#define SYS_CK  3 // �̿ع�����
#define SYS_ZHDY 4 //�ۺϵ�Դ


//�̿ع����� ������ CK
enum CK_CMD
{
	CK_CMD_HEARD_BEAT = 0x1000,//����
	CK_CMD_VERSION = 0x1001,//�汾
	CK_CMD_SELF_CHECK=0x1002,//�Լ�
	CK_CMD_POWER_CONTROL=0x1003,//��Դ����
	CK_CMD_POWER_STATUS=0x1004,//��Դ״̬
	CK_CMD_TEST_IO=0x1005,//����IO��
};
//���ݴ�����
enum HEC_CMD
{
	HEC_CMD_HEARD_BEAT = 0x1800,//����
	HEC_CMD_VERSION = 0x1801,//�汾
	HEC_CMD_SELF_CHECK = 0x1802,//�Լ�
	HEC_CMD_POWER_CONTROL = 0x1803,//��Դ����
};
//�ۺϵ�Դ 
enum ZHDY_CMD
{
	ZHDY_CMD_HEARD_BEAT = 0x1100,//����
	ZHDY_CMD_VERSION = 0x1101,//�汾
	ZHDY_CMD_SELF_CHECK = 0x1102,//�Լ�
	ZHDY_CMD_POWER_CONTROL = 0x1103,//��Դ����
	ZHDY_CMD_POWER_STATUS = 0x1104,//��Դ״̬
};
//ȼ�ͼ����
enum RYJCY_CMD
{
	RYJCY_CMD_HEARD_BEAT = 0x1b00,//����
	RYJCY_CMD_VERSION = 0x1b01,//�汾
	RYJCY_CMD_SELF_CHECK = 0x1b02,//�Լ�
	RYJCY_CMD_POWER_CONTROL = 0x1b03,//����״̬
};
//������Ƶ��Դ
enum SXZPDY_CMD
{
	SXZPDY_CMD_HEARD_BEAT = 0x1200,//����
	SXZPDY_CMD_VERSION = 0x1201,//�汾
	SXZPDY_CMD_SELF_CHECK = 0x1202,//�Լ�
	SXZPDY_CMD_POWER_STATUS = 0x1204,//��Դ״̬
};
//s������
enum SPQ_CMD
{
	SPQ_CMD_HEARD_BEAT = 0x1500,//����
	SPQ_CMD_VERSION = 0x1501,//�汾
	SPQ_CMD_SELF_CHECK = 0x1502,//�Լ�
	SPQ_CMD_POWER_CONTROL = 0x1503,//��·״̬
	
};
//�����ź�ģ����
enum DHXHMNQ_CMD
{
	DHXHMNQ_CMD_HEARD_BEAT = 0x1300,//����
	DHXHMNQ_CMD_VERSION = 0x1301,//�汾
	DHXHMNQ_CMD_SELF_CHECK = 0x1302,//�Լ�
	DHXHMNQ_CMD_POWER_CONTROL = 0x1303,//�������ݿ���
	DHXHMNQ_CMD_POWER_STATUS = 0x1304,//����״̬
};
//�ɼ�������ģ����
enum KJGXSMNQ_CMD
{
	KJGXSMNQ_CMD_HEARD_BEAT = 0x1600,//����
	KJGXSMNQ_CMD_VERSION = 0x1601,//�汾
	KJGXSMNQ_CMD_SELF_CHECK = 0x1602,//�Լ�
	KJGXSMNQ_CMD_POWER_CONTROL = 0x1603,//����ͼƬ����
	KJGXSMNQ_CMD_POWER_STATUS = 0x1604,//��ȡ�նȵ�λ״̬
};
//�״�߶ȱ�
enum LDGDB_CMD
{
	LDGDB_CMD_HEARD_BEAT = 0x1400,//����
	LDGDB_CMD_VERSION = 0x1401,//�汾
	LDGDB_CMD_SELF_CHECK = 0x1402,//�Լ�
	LDGDB_CMD_POWER_CONTROL = 0x1403,//�״����ݿ���
	LDGDB_CMD_POWER_STATUS = 0x1404,//�״�״̬
};
//��2
enum Dan2_CMD
{
	Dan2_CMD_HEARD_BEAT = 0x1f00,//����
	Dan2_CMD_VERSION = 0x1f01,//�汾
	Dan2_CMD_SELF_CHECK = 0x1f02,//�Լ�
	Dan2_CMD_POWER_CONTROL = 0x1f03,//���Ƕ�λ��Ϣ
	Dan2_CMD_POWER_STATUS = 0x1f04,//����ͼƬʶ����Ϣ
};
//��
enum Dan_CMD
{
	Dan_CMD_HEARD_BEAT = 0x1700,//����
	Dan_CMD_VERSION = 0x1701,//�汾
	Dan_CMD_SELF_CHECK = 0x1702,//�Լ�
	Dan_CMD_POWER_CONTROL = 0x1703,//�¶���Ϣ
	Dan_CMD_POWER_STATUS = 0x1704,//������Ϣ
	Dan_CMD_LAMP_CONTROL =0x1705,//�������Ϣ
	Dan_CMD_SOUND_CONTROL=0x1706,//��������
	Dan_CMD_TAIL_CONTROL=0x1707,//β�����
	Dan_CMD_LINE_INFO=0x1708,//��·����״̬
	Dan_CMD_EED_INFO=0x1709,//��Ʒ����
};
