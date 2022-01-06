/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    22-April-2016
  * @brief   Main program body
  ******************************************************************************
  */

#include "main.h"

volatile unsigned int SysTick_Count = 0;
volatile unsigned int TimingDelay = 0;

int main(void)
{	
	int vol=0; 	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	GPIO_Configuration();
	Init_SysTick();
	UART7_Configuration(115200);
	SPI2_Configuration();
	get_RCCCLOCK();
	
	log_info("hardware init ok!\r\n");
	LOG_D("hardware init ok!");
	LOG_W("hardware init ok!");
	LOG_E("hardware init ok!");
	Delay_ms(200);
	
	get_temp();
	get_temp();
	get_temp();
	get_temp();
	get_temp();
	
	
	//测试DAC波形输出
	{
		
		WAVE_InitTypeDef WAVE_Init;
		
		DAC_DeInit(); 			//初始化DAC
		
		//设置波形参数
		WAVE_Init.wave_type=SINWAVE;
		WAVE_Init.freq = 1;
		WAVE_Init.am = 1;
		WAVE_Init.phase =0;
		WAVE_Init.duty_cycle =50;
		WAVE_Init.polarity=0;
		
		//WaveGeneration(&WAVE_Init);	//输出波形
		//Dac1_Set_fixed_Vol(vol);		//设置恒定电平
	}
	
	
	
	
	{
			//DDS_test();
	}
	
	
	
	
	while (1)
	{
		//vol+=100;
//		DDS_LED_ON();
//		Delay_ms(200);
//		DDS_LED_OFF();
//		Delay_ms(200);
		
		get_temp();
		Delay_ms(1000);
		
	

	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
