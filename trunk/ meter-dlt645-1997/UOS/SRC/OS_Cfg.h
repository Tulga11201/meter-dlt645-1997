#ifndef OS_CFG_H
#define OS_CFG_H

//#ifdef TEST_MODE
#define OS_TASK_NUM 5 //����������,����ܳ���255
//#else
//#define OS_TASK_NUM 4 //����������,����ܳ���255
//#endif

#define OS_SEM_NUM 16 //����ź�������,����ܳ���32��

#define OS_USE_LIB        1 //0��ʾʹ���Լ��������ת����,1��ʾʹ�ÿ⺯��setjmp��longjmp
#define OS_USE_TICK_ISR   1 //0��ʾʹ��OS_Check_Tick()��ѯ��ʱ���ķ�ʽ����ʱ����1��ʾʹ���ж�OS_Tick_ISR����ʱ��
#define OS_USE_IDLE_TASK  0 //0��ʾ��ʹ�ÿ�������1��ʾʹ�ÿ�������,�������������ͳ��cpu��������
#define OS_USE_TASK_NAME  1 //0��ʾ�������������ֹ���,1��ʾ����
#define OS_USE_CS         1 //����ϵͳ�Ƿ�����ڴ����CSУ��
#define OS_RST_CHK_STK    1 //����ϵͳ��λ���Ƿ��鸴λǰ������Ķ�ջʣ�����,�ù�����Ҫ�������ջ�ռ�������__no_init����
                            //��Ҫ�����ڷ����쳣��λǰ�ĺ�����ջʹ�����
                            //�ڴ�������ĺ����У��Ὣ������λǰ�Ķ�ջʹ���������ŵ�Task_Stk_Leftȫ�ֱ�����
#define OS_SEM_LOCK_CHK   1 //�Ƿ���ź���������������ͱ���
#define OS_SEM_CHK_LOCK_TIME 1//��������ô��ʱ��û�����뵽�ź����������������������λΪ��

#define OS_STK_GROWTH     1 //���ö�ջ��������1��ʾ�ɸߵ�ַ��͵�ַ�ݼ���0�෴

#define OS_MS_PER_TICK    10 //ÿ��Tick�������ms
#define OS_CS_BYTES       2//У��ʹ�С
#define OS_CS_TYPE        CS_CRC16_1//����CRCУ��
#define OS_TASK_NAME_SIZE 7 //�������ִ�С

#define OS_ASSERT_CTRL_EN 1//1��ʾ���Կ�ͨ���������أ�0 ��ʾ���Թ��ܲ���ͨ���������أ�һֱ�򿪡���ʽ����ʱӦ��
#define OS_ASSERT_FUNC_EN 1
#define OS_ASSERT_HOOK_EN 0
#define OS_PRINT_TYPE     OS_PRINT_COMM//���������Ϣ�����ʽ������Ϊ��׼IO���(�����)
#define OS_ASSERT_NUM     10//���Ժ������ٵĸ���
#define OS_ASSERT_BUF_LEN 15//ÿ�����Լ�¼���ݳ���
#endif
