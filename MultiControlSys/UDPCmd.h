#pragma once
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
