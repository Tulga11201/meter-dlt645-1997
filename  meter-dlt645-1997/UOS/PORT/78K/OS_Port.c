#define OS_PORT_C
#include "OS_Core.h"

//������ϵͳ��һ��Tickʱ���Ƿ�,�ú������ڲ�ʵ���жϲ���Tickʱ��ѯTickʱ���Ƿ���
//����1��ʾһ��Tickʱ�䵽�����򷵻�0
OS_INT8U OS_Check_Tick()
{
  return 1;
  /*
  if(TIM_FlagStatus(TIM0,TIM_OCFA)!=SET)
    return 0;
  
  TIM_FlagClear(TIM0,TIM_OCFA);//���жϱ�־�������
  TIM_CounterConfig(TIM0,TIM_CLEAR);//�������
  return 1;
*/  
}
