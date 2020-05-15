/**
  ******************************************************************************
  * @file    stm32fxxx_it.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    17-March-2018
  * @brief   Main Interrupt Service Routines.
  *          This file provides all exceptions handler and peripherals interrupt
  *          service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      <http://www.st.com/SLA0044>
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include "stm32fxxx_it.h"
#include "sd_card.h"
#include "FreeRTOS.h"
#include "task.h"
/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
/* Private function prototypes ----------------------------------------------- */
volatile uint32_t ms_ticks = 0;

extern USB_OTG_CORE_HANDLE USB_OTG_dev;
extern uint32_t USBD_OTG_ISR_Handler(USB_OTG_CORE_HANDLE * pdev);

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
extern uint32_t USBD_OTG_EP1IN_ISR_Handler(USB_OTG_CORE_HANDLE * pdev);
extern uint32_t USBD_OTG_EP1OUT_ISR_Handler(USB_OTG_CORE_HANDLE * pdev);
#endif

extern CanRxMsg CAN1_RxMessage;
extern CanRxMsg CAN2_RxMessage;

extern void xPortSysTickHandler(void);

/******************************************************************************/
/* Cortex-M Processor Exceptions Handlers */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

///**
//  * @brief  This function handles SVCall exception.
//  * @param  None
//  * @retval None
//  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

///**
//  * @brief  This function handles PendSVC exception.
//  * @param  None
//  * @retval None
//  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
	{
		xPortSysTickHandler();	
	}
	else
	{
		ms_ticks++;
	}
}

/**
  * @brief  Configure a SysTick Base time to 1 ms.
  * @param  None
  * @retval None
  */
void SysTickConfig(void)
{
  /* Setup SysTick Timer for 10ms interrupts  */
  if (SysTick_Config(SystemCoreClock / 1000))
  {
    /* Capture error */
    while (1);
  }

  /* Configure the SysTick handler priority */
  NVIC_SetPriority(SysTick_IRQn, 0x0);
}

uint32_t GetSysTick(void)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
	{
		return xTaskGetTickCount();
	}
	else
	{
		return ms_ticks;
	}
}


/**
  * @brief  This function handles EXTI15_10_IRQ Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_FS
void OTG_FS_WKUP_IRQHandler(void)
{
  if (USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *) (0xE000ED10) &= 0xFFFFFFF9;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
  EXTI_ClearITPendingBit(EXTI_Line18);
}
#endif

/**
  * @brief  This function handles EXTI15_10_IRQ Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_HS
void OTG_HS_WKUP_IRQHandler(void)
{
  if (USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *) (0xE000ED10) &= 0xFFFFFFF9;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
  EXTI_ClearITPendingBit(EXTI_Line20);
}
#endif

/**
  * @brief  This function handles OTG_HS Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_HS
void OTG_HS_IRQHandler(void)
#else
void OTG_FS_IRQHandler(void)
#endif
{
  USBD_OTG_ISR_Handler(&USB_OTG_dev);
}

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
/**
  * @brief  This function handles EP1_IN Handler.
  * @param  None
  * @retval None
  */
void OTG_HS_EP1_IN_IRQHandler(void)
{
  USBD_OTG_EP1IN_ISR_Handler(&USB_OTG_dev);
}

/**
  * @brief  This function handles EP1_OUT Handler.
  * @param  None
  * @retval None
  */
void OTG_HS_EP1_OUT_IRQHandler(void)
{
  USBD_OTG_EP1OUT_ISR_Handler(&USB_OTG_dev);
}
#endif


/******************************************************************************/
/* STM32Fxxx Peripherals Interrupt Handlers */
/* Add here the Interrupt Handler for the used peripheral(s) (PPP), for the */
/* available peripheral interrupt handler's name please refer to the startup */
/* file (startup_stm32fxxx.s).  */
/******************************************************************************/
///**
//  * @brief  This function handles CAN1 RX0 request.
//  * @param  None
//  * @retval None
//  */
//void CAN1_RX0_IRQHandler(void)
//{
//  CAN_Receive(CAN1, CAN_FIFO0, &CAN1_RxMessage);
//  
//  if ((CAN1_RxMessage.StdId == 0x321)&&(CAN1_RxMessage.IDE == CAN_ID_STD) && (CAN1_RxMessage.DLC == 1))
//  {
////    LED_Display(RxMessage.Data[0]);
////    ubKeyNumber = RxMessage.Data[0];
//  }
//}

//void CAN1_TX_IRQHandler(void) //CAN TX
//{
//	if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
//	{
//		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
//	}
//}

///**
//  * @brief  This function handles CAN2 RX0 request.
//  * @param  None
//  * @retval None
//  */
//void CAN2_RX0_IRQHandler(void)
//{
//  CAN_Receive(CAN2, CAN_FIFO0, &CAN2_RxMessage);
//  
//  if ((CAN2_RxMessage.StdId == 0x321)&&(CAN2_RxMessage.IDE == CAN_ID_STD) && (CAN2_RxMessage.DLC == 1))
//  {
////    LED_Display(RxMessage.Data[0]);
////    ubKeyNumber = RxMessage.Data[0];
//  }
//}

//void CAN2_TX_IRQHandler(void) //CAN TX
//{
//	if (CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
//	{
//		CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
//	}
//}

//void USART1_IRQHandler(void)
//{
//	static uint32_t this_time_rx_len = 0;
//	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
//	{
//		USART_ClearITPendingBit(USART1, USART_IT_TXE);
//	}
//}

void SDIO_IRQHandler(void)
{
	SD_ProcessIRQSrc();
}

void SD_SDIO_DMA_IRQHANDLER(void)
{
	SD_ProcessDMAIRQ();
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/* void PPP_IRQHandler(void) { } */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
