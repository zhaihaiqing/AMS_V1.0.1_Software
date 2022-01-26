/**
  ******************************************************************************
  * @file    Project/BSP/bsp_i2c_port.c 
  * @author  zhaihaiqing
  * @version V1.0.0
  * @date    5-April-2020
  * @brief   ʹ��IOģ��I2C
  ******************************************************************************
  */
#include "main.h"

void i2c_port_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOBʱ��

	//GPIOE11,E10��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
	I2C_PORT_SCL_H();
	I2C_PORT_SDA_H();
}

//����IIC��ʼ�ź�
void i2c_port_start(void)
{
	SET_I2C_PORT_SDA_OUT();     //sda�����
	I2C_PORT_SDA_H();	  	  
	I2C_PORT_SCL_H();
	rt_hw_us_delay(4);
 	I2C_PORT_SDA_L();//START:when CLK is high,DATA change form high to low 
	rt_hw_us_delay(4);
	I2C_PORT_SCL_L();//ǯסI2C���ߣ�׼�����ͻ�������� 
}
//����IICֹͣ�ź�
void i2c_port_stop(void)
{
	SET_I2C_PORT_SDA_OUT();//sda�����
	I2C_PORT_SCL_L();
	I2C_PORT_SDA_L();//STOP:when CLK is high DATA change form low to high
 	rt_hw_us_delay(4);
	I2C_PORT_SCL_H();
	I2C_PORT_SDA_H();//����I2C���߽����ź�
	rt_hw_us_delay(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
unsigned char i2c_port_wait_ack(void)
{
	u8 ucErrTime=0;
	SET_I2C_PORT_SDA_IN();      //SDA����Ϊ����  
	I2C_PORT_SDA_H();rt_hw_us_delay(1);	   
	I2C_PORT_SCL_H();rt_hw_us_delay(1);	 
	while(I2C_PORT_READ_SDA())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			i2c_port_stop();
			return 1;
		}
	}
	I2C_PORT_SCL_L();//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void i2c_port_ack(void)
{
	I2C_PORT_SCL_L();
	SET_I2C_PORT_SDA_OUT();
	I2C_PORT_SDA_L();
	rt_hw_us_delay(2);
	I2C_PORT_SCL_H();
	rt_hw_us_delay(2);
	I2C_PORT_SCL_L();
}
//������ACKӦ��		    
void i2c_port_nack(void)
{
	I2C_PORT_SCL_L();
	SET_I2C_PORT_SDA_OUT();
	I2C_PORT_SDA_H();
	rt_hw_us_delay(2);
	I2C_PORT_SCL_H();
	rt_hw_us_delay(2);
	I2C_PORT_SCL_L();
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void i2c_port_send_byte(unsigned char txd)
{                        
    unsigned char t;   
	SET_I2C_PORT_SDA_OUT();	    
    I2C_PORT_SCL_L();//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        if((txd&0x80)>>7)I2C_PORT_SDA_H();
		else	I2C_PORT_SDA_L();
        txd<<=1; 	  
		rt_hw_us_delay(2);   //��TEA5767��������ʱ���Ǳ����
		I2C_PORT_SCL_H();
		rt_hw_us_delay(2); 
		I2C_PORT_SCL_L();
		rt_hw_us_delay(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
unsigned char i2c_port_read_byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SET_I2C_PORT_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        I2C_PORT_SCL_L(); 
        rt_hw_us_delay(2);
		I2C_PORT_SCL_H();
        receive<<=1;
        if(I2C_PORT_READ_SDA())receive++;   
		rt_hw_us_delay(2); 
    }					 
    if (!ack)
        i2c_port_nack();//����nACK
    else
        i2c_port_ack(); //����ACK   
    return receive;
}
















