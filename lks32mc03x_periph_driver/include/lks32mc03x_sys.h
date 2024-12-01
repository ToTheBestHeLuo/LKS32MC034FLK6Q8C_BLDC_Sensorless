/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_sys.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� sys����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
 
#ifndef __LKS32MC03x_SYS_H
#define __LKS32MC03x_SYS_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief ϵͳ��ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */
typedef struct
{
	uint32_t PLL_SrcSel;                      /**< PLL�ź�����Դѡ��RCʱ�ӻ��ⲿ����*/
	uint32_t PLL_DivSel;                      /**< ѡ��8��ʱ�������У��ĸ��������ʱ��*/
	uint32_t Clk_Sel;						  /**ѡ��4MHz HSʱ�ӻ���PLL��Ϊ��ʱ��*/

	uint32_t Clk_DivI2C;                      /**< SPI I2Cʱ�ӷ�Ƶ*/
	uint32_t Clk_DivUART;                     /**< UARTʱ�ӷ�Ƶ*/
	uint32_t Clk_FEN;                         /**< ģ��ʱ��ʹ��*/

}SYS_InitTypeDef;

/**
 * ϵͳ�ṹ�����ַ����
 */
#ifndef MISC_BASE
#define MISC_BASE           0x40000000
#endif

/** 
 *@brief �͹���ʱ�������м����
 */
typedef struct
{
  uint32_t AFE_REG0_RECORD;
  uint32_t CLK_CFG_RECORD;
	
}WAKE_InitTypeDef;

/** 
 *@brief �͹���IO���ѵ�ƽö�ٳ�Ա
 */
typedef enum
{
	WAKETRIG_LOW,  //����IO�͵�ƽ����
	WAKETRIG_HIGH, //����IO�ߵ�ƽ����
}enumWakeTrigLevel;

/*PLL�ź�����Դѡ��*/
#define SYS_PLLSRSEL_RCH        0x00          /**<ʹ��4MHz RCʱ��*/
#define SYS_PLLSRSEL_CRYSTAL    0x01          /**<ʹ�þ���ʱ��*/

/* PLL ���� HS ʱ��ѡ��*/
#define CLK_SEL_HS				0x00
#define CLK_SEL_PLL				0x01

/*SPIʱ�ӷ�Ƶ*/
#define SYS_Clk_SPIDiv1          0     /**< SPIʱ�ӷ�Ƶ��ռʱδʹ��*/
#define SYS_Clk_SPIDiv2          1     /**< SPIʱ�ӷ�Ƶ��ռʱδʹ��*/
#define SYS_Clk_SPIDiv4          2     /**< SPIʱ�ӷ�Ƶ��ռʱδʹ��*/
#define SYS_Clk_SPIDiv8          3     /**< SPIʱ�ӷ�Ƶ��ռʱδʹ��*/

/*UARTʱ�ӷ�Ƶ*/
#define SYS_Clk_UARTDiv1         0     /**< UARTʱ�ӷ�Ƶ��ռʱδʹ��*/
#define SYS_Clk_UARTDiv2         1     /**< UARTʱ�ӷ�Ƶ��ռʱδʹ��*/
#define SYS_Clk_UARTDiv4         2     /**< UARTʱ�ӷ�Ƶ��ռʱδʹ��*/
#define SYS_Clk_UARTDiv8         3     /**< UARTʱ�ӷ�Ƶ��ռʱδʹ��*/

/*����ģ��λ����*/
#define SYS_Module_I2C          BIT0   /**<I2Cģ��*/
#define SYS_Module_HALL         BIT1   /**<HALLģ��*/
#define SYS_Module_UART         BIT2   /**<UARTģ��*/
#define SYS_Module_CMP          BIT3   /**<CMPģ��*/
#define SYS_Module_MCPWM        BIT4   /**<MCPWMģ��*/
#define SYS_Module_TIMER0       BIT5   /**<TIMER0ģ��*/
#define SYS_Module_TIMER1       BIT6   /**<TIMER1ģ��*/
#define SYS_Module_GPIO         BIT7   /**<GPIOģ��*/
#define SYS_Module_DSP          BIT8   /**<DSPģ��*/
#define SYS_Module_ADC          BIT9   /**<ADCģ��*/
#define SYS_Module_SPI          BIT10  /**<SPIģ��*/
#define SYS_Module_DMA          BIT11  /**<DMAģ��*/

/*ģ��ģ�鶨��*/
#define SYS_AnalogModule_ADC    BIT8   /**< ADCģ��*/
#define SYS_AnalogModule_OPA    BIT9   /**< OPAģ��*/
#define SYS_AnalogModule_BGP    BIT10  /**< BGPģ��*/
#define SYS_AnalogModule_DAC    BIT11  /**< DACģ��*/
#define SYS_AnalogModule_TMP    BIT12  /**< TMPģ��*/
#define SYS_AnalogModule_CMP0   BIT13  /**< CMP0ģ��*/
#define SYS_AnalogModule_CMP1   BIT14  /**< CMP1ģ��*/
#define SYS_AnalogModule_PLL    BIT15  /**< PLLģ��*/

/*���Ź���ʱʱ��*/
#define SYS_WD_TimeOut2s  0         /**<���Ź���ʱʱ��2s��λ*/
#define SYS_WD_TimeOut4s  1         /**<���Ź���ʱʱ��4s��λ*/
#define SYS_WD_TimeOut8s  2         /**<���Ź���ʱʱ��8s��λ*/
#define SYS_WD_TimeOut64s 3         /**<���Ź���ʱʱ��64s��λ*/

/*��λ�ź�Դ����*/
#define SYS_RstSrc_LPOR        0x01     /**< ��λ�ź�Դ���ڲ�1.5V��Դ����λ*/
#define SYS_RstSrc_HPOR        0x02     /**< ��λ�ź�Դ���ڲ�3.3V��Դ����*/
#define SYS_RstSrc_KEYBOARD    0x04     /**< ��λ�ź�Դ��������λ*/
#define SYS_RstSrc_WDT         0x08     /**< ��λ�ź�Դ��WDT��λ*/

/*���߻��Ѽ��ʱ��*/
#define SYS_WakeInterval_025s  0x00     /**< ���߻��Ѽ��ʱ��0.25s*/  
#define SYS_WakeInterval_05s   0x01     /**< ���߻��Ѽ��ʱ��0.5s*/
#define SYS_WakeInterval_1s    0x02     /**< ���߻��Ѽ��ʱ��1s*/
#define SYS_WakeInterval_2s    0x03     /**< ���߻��Ѽ��ʱ��2s*/
#define SYS_WakeInterval_4s    0x04     /**< ���߻��Ѽ��ʱ��4s*/
#define SYS_WakeInterval_8s    0x05     /**< ���߻��Ѽ��ʱ��8s*/
#define SYS_WakeInterval_16s   0x06     /**< ���߻��Ѽ��ʱ��16s*/
#define SYS_WakeInterval_32s   0x07     /**< ���߻��Ѽ��ʱ��32s*/

/*�͹��Ļ���IO�˲�*/
#define IOWK_FLT_EN    0x02 /**< ʹ��IO�˲�*/
#define IOWK_FLT_DI    0x00 /**< �ر�IO�˲�*/

/*�͹��Ļ���IOѡ��*/
#define WAKEIO_P0_0	   BIT0  /**< P0.0 ��Ϊ����IO*/
#define WAKEIO_P0_2	   BIT1  /**< P0.2 ��Ϊ����IO*/
#define WAKEIO_P0_8	   BIT2  /**< P0.8 ��Ϊ����IO*/
#define WAKEIO_P0_9	   BIT3  /**< P0.9 ��Ϊ����IO*/
#define WAKEIO_P0_10   BIT4  /**< P0.10��Ϊ����IO*/
#define WAKEIO_P1_5	   BIT5  /**< P1.5 ��Ϊ����IO*/
#define WAKEIO_P1_8	   BIT6  /**< P1.8 ��Ϊ����IO*/
#define WAKEIO_P1_9	   BIT7  /**< P1.9 ��Ϊ����IO*/

/*ϵͳ����*/
void SYS_Init(SYS_InitTypeDef* SYS_InitStruct);         // sysģ���ʼ��
void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct);   // SYS�ṹ���ʼ��

/*��λԴ*/
void SYS_ClearRst(void);                                // SYS�����λ��־

/*����8·ʱ��ʹ��*/
void SYS_ModuleClockCmd(uint32_t,FuncState);            // ����ģ��ʱ��ʹ�ܺ�ֹͣ

/*����ģ��ģ��ʱ��ʹ��*/
void SYS_AnalogModuleClockCmd(uint32_t, FuncState);     // ģ��ģ��ʹ�ܺ�ֹͣ

/*��λ��ģ��*/
void SYS_SoftResetModule(uint32_t nModule);             // ģ����λ
void SYS_VolSelModule(uint32_t Vol);                    // ʱ��У��
u32 SYS_GetRstSource(void);                             // ���SYS��λԴ�ź�

/*���ߡ�����*/
void SYS_EVTCLRSleep(void);
void SYS_FallSleep(void);
void SYS_SetWakeInterval(uint32_t rth , uint32_t wth , uint8_t ena);
void Switch2PLL(void);
void Switch2HRC(void);
void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt , uint8_t ena);
/*DSPģ���ʼ��*/
void DSP_Init(void);
#endif /*__lks32mc03x_SYS_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
