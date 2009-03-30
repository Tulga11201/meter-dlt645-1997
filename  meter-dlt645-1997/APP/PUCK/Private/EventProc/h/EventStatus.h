#ifndef EVENTSTATUS_VAR
#define EVENTSTATUS_VAR  


#ifndef EVENTSTATUS_C
#define EVENTSTATUS_C_EXT  extern
#else
#define EVENTSTATUS_C_EXT 
#endif


const INT16U Const_End_Time[]=
{
  14400,
  600,
  0
};

#define MAX_END_TIME_NUM (sizeof(Const_End_Time)/sizeof(INT16U))

typedef struct{
  INT8U  DoubleFlag:1;      //�¼�������ԣ�0-------���ɶ��¼�,���ⲿ����������߶�ʱǿ�����;1-------�ɶԳ��ֵ��¼�(�¼��ɶԳ���,���ܻ�ͳ�Ƹ�ʱ��ε������)
  INT8U  StartSave:1;       //�¼���ʼ�洢ʹ��
  INT8U  EndSave:1;         //�¼���ʼ�洢ʹ��
  INT8U  StartUnit:1;       //�¼���������������λ��0-----�룻1---------��
  INT8U  EndUnit:1;         //�¼���������������λ��0-----�룻1---------��
  INT8U  ForbitEnd:1;       //���ڳɶ��¼����¼������󣬰���EndCount��ֵ����һ��ʱ��ǿ�������
  INT8U  EndIndex:1;        //ǿ�н����¼�ʱ������
  INT8U  DisEvent;
  INT8U StartCount;         //�¼���������������λ����
  INT8U EndCount;           //�Գ��¼���0��ʾ�¼�һ������������Ͻ�������ʾ�¼����������������ڷǳɶ��¼�����ʱǿ���������������λ����
  void (* const GetInstStatus)(void);
  INT8U const *EventName;
}EventProperty;           //�¼��ͱ������Խṹ��


/*********************�����������ע��ļ�������*********************************************************
1�����ں����ж�ʧѹ��ʧ�����¼�������ʱ��>����ʱ�䣬�ҷ���ʱ��=1.5������ʱ��
2��

*********************************************************************************************************/
EVENTSTATUS_C_EXT const EventProperty EventPropertyVar[MAX_EVENT_NUM]={
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=0,.EndCount=0,.GetInstStatus=0,.EventName="NONE",\
  },
   
#ifdef ID_EVENT_A_LOSS_VOLT                               //A��ʧѹ------------------1
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Volt,.EventName="A Parse Loss Volt",\
  },
#endif

#ifdef ID_EVENT_B_LOSS_VOLT                               //B��ʧѹ------------------2
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Volt,.EventName="B Parse Loss Volt",\
  },
#endif  

#ifdef ID_EVENT_C_LOSS_VOLT                             //C��ʧѹ------------------3
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Volt,.EventName="C Parse Loss Volt",\
  },
#endif
#ifdef ID_EVENT_A_LOSS_CURR                                //A��ʧ��--------------4
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Curr,.EventName="A Parse Loss Curr",\
  },
  #endif  
  
#ifdef ID_EVENT_B_LOSS_CURR                               //B��ʧ��--------------5
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Curr,.EventName="B Parse Loss Curr",\
  },
  #endif
  
#ifdef ID_EVENT_C_LOSS_CURR                               //C��ʧ��--------------6
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Curr,.EventName="C Parse Loss Curr",\
  },
  #endif
  
#ifdef ID_EVENT_CUR_NEG_SEQ                               //����������-----------7
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Volt_Curr_Seq,.EventName="Curr Neg Sequence",\
  },
  #endif  
  
#ifdef ID_EVENT_VOLT_NEG_SEQ                              //��ѹ������-----------8
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=10,.EndCount=10,.GetInstStatus=&Check_Volt_Curr_Seq,.EventName="Volt Neg Sequence",\
  },
  #endif  
  
#ifdef ID_EVENT_A_VOLT_MAX
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="A Parse Volt OverLimted",\
   },    //A���ѹ����ѹ--------9----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_B_VOLT_MAX
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="B Parse Volt OverLimted",\
   },    //B���ѹ����ѹ--------10----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_C_VOLT_MAX
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="C Parse Volt OverLimted",\
    },    //C���ѹ����ѹ--------11----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_A_VOLT_MIN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="A Parse Volt LowerLimted",\
   },    //A���ѹ����ѹ--------12----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_B_VOLT_MIN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="B Parse Volt LowerLimted",\
   },    //B���ѹ����ѹ-------13----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_C_VOLT_MIN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="C Parse Volt LowerLimted",\
   },    //C���ѹ����ѹ--------14----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_DEMAND_ALARM
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=0,.EventName="OverLimted Demand Alarm",\
   },    //����������-----------15----HUCK  done
  #endif  
  
#ifdef ID_EVENT_DEMAND_SWITCH
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=0,.EventName="OverLimted Demand Switch Toggle",\
   },    //��������բ-----------16----HUCK  done
  #endif
  
#ifdef ID_EVENT_NC
  {.DoubleFlag=0,.StartSave=0,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Meter NC Event",\
   },       //�տտ�--------17
  #endif
  
#ifdef ID_EVENT_RESET
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=0,.EventName="Meter Reset Event",\
   },      //��λ-----------------18----��Ҫ���Ӻ���----PUCK
  #endif 
  
#ifdef ID_EVENT_CLR_DEMAND_COM
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=1,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=10,.GetInstStatus=0,.EventName="Clr Demand With COM",\
   },    //ͨ��������-----------19----HUCK Will do
  #endif  
#ifdef ID_EVENT_CLR_DEMAND_MAN
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=1,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=10,.GetInstStatus=0,.EventName="Clr Demand With Manul",\
   },    //�ֶ�������-----------20----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_CLR_PROCESS
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Clr Process",\
    },    //�����---------------21----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_CLR_VOLT_PASS
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Clr Volt Rate",\
   },    //���ѹ�ϸ���---------22----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_SET_ENERG
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Set Init Energ",\
   },    //���ó�ʼ����---------23----HUCK not do
  #endif  
  
#ifdef ID_EVENT_UP_COVER_OPEN
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=3,.EndCount=3,.GetInstStatus=&Check_UpCover,.EventName="Up Cover Opened",\
   },    //�����(ǰ�˸�)--------24
  #endif  
  
#ifdef ID_EVENT_LEAD_COVER_OPEN
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=3,.EndCount=3,.GetInstStatus=&Check_DownCover,.EventName="Lead Door Opened",\
   },    //��Ǧ����-------------25  
  #endif  
  
#ifdef ID_EVENT_RTC_BAT_LOW                   //ʱ�ӵ��Ƿѹ---------26
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_RTCBat_Low,.EventName="RTC Bat Low",\
  },
  #endif  
  
#ifdef ID_EVENT_LOWPWR_BAT_LOW                    //�͹��ĵ��Ƿѹ-------27
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_LPWBat_Low,.EventName="Low_Power Bat Low",\
  },
  #endif  
  
#ifdef ID_EVENT_ADJUST_TIME
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=1,.GetInstStatus=0,.EventName="Adjust RTC",\
   },    //Уʱ-----------------28----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_RTCERR_RUN                          //����ʱ����-----------29----HUCK Will do
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=0,.EventName="RTC Error During Running",\
  },
#endif  
  
#ifdef ID_EVENT_RTCERR_PWRON                        //�ϵ�ʱ����-----------30----HUCK Will do
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=0,.EventName="RTC Error With Power On",\
  },
#endif

#ifdef ID_EVENT_EPPROM_FAULT                //EEPROM��-------------31----HUCK Will do(ֻ���ϵ�ʱ���)
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=20,.EndCount=0,.GetInstStatus=0,.EventName="Inter Memory Error",\
  },
#endif 

#ifdef ID_EVENT_ADJUST_MEASU
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=1,.GetInstStatus=0,.EventName="Adjust Measure",\
  },          //У��-----------------32----PUCK Will do
#endif

#ifdef ID_EVENT_MODI_ENERG  
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=20,.EndCount=0,.GetInstStatus=0,.EventName="Remedy Energ Error",\
  },           //��������-------------33----HUCK Will do
#endif

#ifdef ID_EVENT_A_VOLT_OVERLOAD                     //A���ѹ��ѹ----------34
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Overload_Volt,.EventName="A Parse Overload",\
  },
#endif

#ifdef ID_EVENT_B_VOLT_OVERLOAD                     //B���ѹ��ѹ----------35
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Overload_Volt,.EventName="B Parse Overload",\
  },
#endif

#ifdef ID_EVENT_C_VOLT_OVERLOAD                     //C���ѹ��ѹ----------36
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Overload_Volt,.EventName="C Parse Overload",\
  },
#endif

#ifdef ID_EVENT_ENERG_FREEZ  
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Energ Freeze",\
  },    //��������-------------37----HUCK Will do
#endif

#ifdef ID_EVENT_POWER_ALARM  
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="Overlimted Power Alarm",\
  },    //������-----------38-ͬ�������������ʣ�HUCK)
#endif

#ifdef ID_EVENT_POWER_SWITCH  
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="Overlimted Power Switch Toggle",\
  },    //��������բ-----------39  
#endif

#ifdef ID_EVENT_A_LOSS_PARSE                               //A�����--------------40  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Parse,.EventName="A Parse Loss Parse",\
  },
#endif

#ifdef ID_EVENT_B_LOSS_PARSE                                //B�����--------------41  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Parse,.EventName="B Parse Loss Parse",\
  },
#endif

#ifdef ID_EVENT_C_LOSS_PARSE                           //C�����--------------42  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Parse,.EventName="C Parse Loss Parse",\
  },
#endif

#ifdef ID_EVENT_A_NEG_CURR                        //A���������----------43 
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Neg_Curr,.EventName="A Curr Neg Direction",\
  },
#endif

#ifdef ID_EVENT_B_NEG_CURR               //B���������----------44  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Neg_Curr,.EventName="B Curr Neg Direction",\
  },
#endif

#ifdef ID_EVENT_C_NEG_CURR                  //C���������----------45 
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Neg_Curr,.EventName="C Curr Neg Direction",\
  },
#endif 

#ifdef ID_EVENT_KEY_SWITCH
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=2,.EndCount=2,.GetInstStatus=&Check_Key_Switch,.EventName="Key Switch On",\
  },    //���߶̽�-------------46
#endif 

#ifdef ID_EVENT_ERR_DI  
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=20,.EndCount=0,.GetInstStatus=0,.EventName="Illegal Data Identification",\
  },    //���ݱ�ʶ��-----------47----HUCK Will do
#endif  
#ifdef ID_EVENT_ERR_PASSWD
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=1,.GetInstStatus=0,.EventName="Password Error",\
  },    //�����---------------48----HUCK Will do
#endif  

#ifdef ID_EVENT_YEAR_FLOW
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Time Zone Overflow",\
  },    //��ʱ������-----------49----HUCK Will do 
#endif

#ifdef ID_EVENT_DATE_FLOW  
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Date Zone Overflow",\
  },    //��ʱ������---------------50----HUCK Will do
#endif  

#ifdef ID_EVENT_TRRI_FLOW
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Trri Num Error",\
  },    //��������-----------------51----HUCK Will do  
#endif  

#ifdef ID_EVENT_PRGKEY_ON
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=1,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_Prg_Key,.EventName="Prog Key Pressed",\
  },    //��̼���-----------52--�˰�ť��Ҫ�ж�֧��
#endif  

#ifdef ID_EVENT_FAC_ON
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=1,.EndIndex=0,.DisEvent=0,.StartCount=2,.EndCount=2,.GetInstStatus=&Check_Fac_Status,.EventName="Switch Key Shutcircuit",\
  },  //���߶̽�(���ֳ�����ģʽ)-----------53 
#endif 

#ifdef ID_EVENT_METER_LOCK
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=2,.EndCount=2,.GetInstStatus=0,.EventName="Prg Meter Event",\
  },     //�Ե����(������Ҫ����)ʱ����������������������ڵ���5�κ�--------54
#endif  

#ifdef ID_EVENT_AB_FUNC_KEY
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=3,.EndCount=1,.GetInstStatus=&Check_AB_Func_Key,.EventName="Func AB Mode Switch Key",\
  },    //���ܼ�ʶ��ABģʽ�л���ť--------55
#endif    

#ifdef ID_EVENT_POWER_OFF                                    //�ϵ��¼�--------56----PUCK 
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Get_Meter_PowerOn,.EventName="Meter Power On Or Power Off",\
  },
#endif    

#ifdef ID_DEMAND_ARRIVE                                    //������--------57----HUCK Will do 
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Demand Time Expired!",\
  },
#endif  
  
#ifdef ID_OVER_LOAD                                    //���ɿ��Ʊ���--------58-ͬ�������������ʣ�HUCK)
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=20,.EndCount=0,.GetInstStatus=0,.EventName="OverLoad Ctrol Alarm",\
  },
#endif  
  
#ifdef ID_NOT_CHARGE                                   //Ƿ�ѱ���--------59----HUCK Will do 
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=20,.EndCount=0,.GetInstStatus=0,.EventName="Fees Not Enough",\
  },
#endif

#ifdef ID_PARSE_SWITCH                                 //ʱ���л�--------60----HUCK Will do 
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Time Prase Switch",\
  },
#endif

#ifdef ID_MEASURE_ERROR                               //��������(˲̬��)--------61
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=20,.EndCount=0,.GetInstStatus=0,.EventName="Measure Error Event",\
  },
#endif

#ifdef ID_METER_ADDR_EN  
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_MeterAddr_Key,.EventName="Set Meter Addr Key",\
  },    //���ñ��ַ��ť----------62
#endif

#ifdef ID_EVENT_ALL_LOSS_VOLT                           //ȫʧѹ--------63
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=30,.EndCount=20,.GetInstStatus=0,.EventName="A Parse Loss Volt",\
  },
#endif  

#ifdef ID_EVENT_AB_LOSS_VOLT                               //ABʧѹ------------------64
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Volt,.EventName="A_B Parse Loss Volt",\
  },
#endif

#ifdef ID_EVENT_AC_LOSS_VOLT                               //ACʧѹ------------------65
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Volt,.EventName="A_C Parse Loss Volt",\
  },
#endif

#ifdef ID_EVENT_BC_LOSS_VOLT                               //BCʧѹ------------------66
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Volt,.EventName="B_C Parse Loss Volt",\
  },
#endif

#ifdef ID_EVENT_ABC_LOSS_VOLT                               //ABCʧѹ------------------67
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Volt,.EventName="A_B_C Parse Loss Volt",\
  },
#endif

#ifdef ID_EVENT_PROG                                      //����¼������ò���-----------68
  {.DoubleFlag=0,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=1,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=10,.GetInstStatus=0,.EventName="Prog Data Event",\
  },
#endif


#ifdef ID_EVENT_CLR_ALL_DATA                                   //��������-----------69
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=1,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=5,.GetInstStatus=0,.EventName="All Data Clear Event",\
  },
#endif


#ifdef ID_EVENT_UP_COVER_CLOSE                                   //�ش��(ǰ�˸�)--------70(HUCK����) 
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=3,.EndCount=3,.GetInstStatus=&Check_UpCover,.EventName="Up Cover Closed",\
  },
#endif

#ifdef ID_EVENT_LEAD_COVER_CLOSE
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=3,.EndCount=3,.GetInstStatus=&Check_DownCover,.EventName="Lead Door Closed",\
   },    //��Ǧ����------------71(HUCK����)  
#endif 

#ifdef ID_EVENT_AB_LOSS_CURR                                //AB��ʧ��--------------72
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Curr,.EventName="A_B Parse Loss Curr",\
  },
#endif  
  
#ifdef ID_EVENT_AC_LOSS_CURR                                //AC��ʧ��--------------73
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Curr,.EventName="A_C Parse Loss Curr",\
  },
#endif  
  
#ifdef ID_EVENT_BC_LOSS_CURR                                //BC��ʧ��--------------74
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Curr,.EventName="B_C Parse Loss Curr",\
  },
#endif  

#ifdef ID_EVENT_ALL_LOSS_CURR                                //ȫʧ��--------75
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Loss_Curr,.EventName="Loss All Cur",\
 },
#endif 

#ifdef ID_EVENT_DOWN_COVER_OPEN                           //���˸�(��˸�)--------76
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=3,.EndCount=3,.GetInstStatus=&Check_DownCover,.EventName="Down Cover Opened",\
  },
#endif

#ifdef ID_EVENT_DOWN_COVER_CLOSE                         //�ض˸�(��˸�)--------77(HUCK����)
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=3,.EndCount=3,.GetInstStatus=&Check_DownCover,.EventName="Down Cover Closed",\
  },
#endif


#ifdef ID_EVENT_DOOR_OPEN                                  //������װ����--------78
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=20,.EndCount=0,.GetInstStatus=0,.EventName="Door Opened",\
  },
#endif

#ifdef ID_EVENT_DOOR_CLOSE                                //�ؼ���װ����--------79(HUCK����)
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=20,.EndCount=0,.GetInstStatus=0,.EventName="Door Closed",\
  },
#endif
  
#ifdef ID_SLIP_ARRIVE                                 //���--------80
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=0,.GetInstStatus=0,.EventName="Slipe Time Arrived",\
  },
#endif 

#ifdef ID_ALARM_OUT               //�Ƿ��б����¼������������������LCD_LED�����������ű���--------81
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=3,.EndCount=1,.GetInstStatus=&Sound_LED_LCD_Port_Alarm,.EventName="Event Alarm Exist",\
  },
#endif

#ifdef ID_CLR_DEMAND_KEY
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=3,.EndCount=1,.GetInstStatus=&Check_ClrDemand_Key,.EventName="Clr Demand Key Press",\
  },                          //�ֶ���������ť--------81
#endif
  
#ifdef ID_EVENT_EXT_PROG
  {.DoubleFlag=0,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=1,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=10,.GetInstStatus=0,.EventName="Extern Prog Data Event",\
  },                           //����¼������ò���--------82(ͬ ID_EVENT_PROG,ӦHUCKGD��������)
#endif
  
#ifdef ID_EVENT_LOSS_VOL           //ʧѹ�仯��--------83(ӦHUCKGD�������ӣ�˲̬����HUCKά��)
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Get_Loss_Volt_Change,.EventName="Loss Volt Change",\
  },
#endif

#ifdef ID_EVENT_LOSS_CUR    //ʧ���仯��--------84(ӦHUCKGD�������ӣ�˲̬����HUCKά��)
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Get_Loss_Curr_Change,.EventName="Loss Curr Change",\
  }, 
#endif
  
#ifdef ID_EVENT_NEG_CUR      //���ʷ���仯��--------85(ӦHUCKGD�������ӣ�˲̬����HUCKά��)
  {.DoubleFlag=0,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Get_Curr_Neg_Change,.EventName="Curr Negative Change",\
  },
#endif
 

#ifdef ID_EVENT_OSC_ERR      //��Ƭ��ʱ��ϵͳ����--------86
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartUnit=0,.EndUnit=0,.ForbitEnd=0,.EndIndex=0,.DisEvent=0,.StartCount=1,.EndCount=1,.GetInstStatus=&Monitor_Meter_System_Osc,.EventName="MCU Osc System Error",\
  }                     
#endif  
};

#endif