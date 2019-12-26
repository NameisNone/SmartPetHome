#include "key.h"
#include "delay.h"


/*******************************************************************************
** ��������: KEY_Init
** ��������: 
** ����˵��: None
** ����˵��: None
** ������Ա: temp_duan
** ��������: 2019-07-09
**------------------------------------------------------------------------------
** �޸���Ա:
** �޸�����:
** �޸�����:
**------------------------------------------------------------------------------
********************************************************************************/
void KEY_Init(void) //IO��ʼ��
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//�ر�swj��jtag���Թ���
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//PA15����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0||KEY2==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
	}else if(KEY1==1&&KEY2==1)key_up=1; 	    
 	return 0;// �ް�������
}


