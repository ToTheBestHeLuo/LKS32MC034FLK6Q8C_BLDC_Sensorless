/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_cmp.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� CMP������������ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author        <th>Description
 * <tr><td>2021��11��09�� <td>1.0  <td>YangZJ        <td>����
 * </table>
 */
#ifndef __LKS32MC03x_CMP_H
#define __LKS32MC03x_CMP_H
/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

// �Ƚ����ز�ѡ��
#define CMP_HYS_20mV         0        /**< 20mV*/
#define CMP_HYS_0mV          1        /**< 20mV*/

// �Ƚ����ź�����ѡ��
#define CMP_SELP_IP0        0         /**< P��IP0���� */    
#define CMP_SELP_OPA0_IP    1         /**< P��OPA0 IP���� */  
#define CMP_SELP_OPA0_OUT   2         /**< P��OPA0 OUT */ 
#define CMP_SELP_IP1        3         /**< P��IP1���� */ 
#define CMP_SELP_IP2        4         /**< P��IP2���� */ 
#define CMP_SELP_IP3        5         /**< P��IP3���� */ 

// �Ƚ����źŸ���ѡ��
#define CMP_SELN_IN         0         /**< �Ƚ���N�ˣ�N������ */
#define CMP_SELN_REF        1         /**< �Ƚ���N�ˣ�N���ڲ��ο�REF���� */
#define CMP_SELN_DAC        2         /**< �Ƚ���N�ˣ�N���ڲ�DAC���� */
#define CMP_SELN_HALL_MID   3         /**< �Ƚ���N�ˣ�N�˷����ƹ����е����� */       
/** 
 *@brief CMP�Ĵ����ṹ����
 */
typedef struct
{
    __IO uint32_t IE;                 /**< �Ƚ����ж�ʹ�ܼĴ���*/
    __IO uint32_t IF;                 /**< �Ƚ����жϱ�־�Ĵ���*/
    __IO uint32_t TCLK;               /**< �Ƚ�����Ƶʱ�ӿ��ƼĴ���*/
    __IO uint32_t CFG;                /**< �Ƚ������ƼĴ���*/
    __IO uint32_t BLCWIN;             /**< �Ƚ����������ƼĴ���*/
    __IO uint32_t DATA;               /**< �Ƚ��������ֵ�Ĵ���*/
} CMP_TypeDef;
/**
 * CMP�ṹ�����ַ����
 */
#ifndef CMP
#define CMP             ((CMP_TypeDef *) CMP_BASE)
#endif
/**
 * �Ƚ���0
 */
#define CMP0            0
/**
 * �Ƚ���1
 */
#define CMP1            1
/** 
 *@brief CMP��ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */
typedef struct
{
    /**
     * @brief CMP �˲�ʱ��Ƶ��Freq(CMP_Filter) = (Freq(MCLK)/2^FIL_CLK10_DIV2)/(FIL_CLK10_DIV16+1) ��
     * ����MCLK Ϊϵͳ����ʱ�ӡ���Ҫע����ǣ����� CMP �˲�ʱ����Ҫʹ��CLK10_EN��
     */
    u32         FIL_CLK10_DIV16;    /**< �Ƚ��� 1/0 �˲�ʱ�ӷ�Ƶ\n ��ֵ��Χ0-0xF*/
    FuncState   CLK10_EN;           /**< �Ƚ��� 1/0 �˲�ʱ��ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
    /**
     * @brief CMP �˲�ʱ��Ƶ��Freq(CMP_Filter) = (Freq(MCLK)/2^FIL_CLK10_DIV2)/(FIL_CLK10_DIV16+1) ��
     * ����MCLK Ϊϵͳ����ʱ�ӡ���Ҫע����ǣ����� CMP �˲�ʱ����Ҫʹ��CLK10_EN��
     */
    u32         FIL_CLK10_DIV2;     /**< �Ƚ��� 1/0 �˲�ʱ�ӷ�Ƶ\n 0x0:1��Ƶ,0x1:2��Ƶ,0x2:4��Ƶ,0x3:8��Ƶ,0x4:16��Ƶ��0x5:32��Ƶ,0x6:64��Ƶ,0x7:128��Ƶ*/
    FuncState   CMP_FT;             /**< �Ƚ������ٱȽ�ʹ��\n  DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    u32         CMP_HYS;            /**< �Ƚ����ز�ѡ��\n @see CMP_HYS_0mV \n  @see CMP_HYS_20mV  */
    
    FuncState   CMP0_EN;            /**< �Ƚ��� 0 ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    /**
     * @brief �Ƚ��� 0 �ź�����ѡ��
     * @see CMP_SELP_IP0           
     * @see CMP_SELP_OPA0_IP       
     * @see CMP_SELP_OPA0_OUT      
     * @see CMP_SELP_IP1           
     * @see CMP_SELP_IP2           
     * @see CMP_SELP_IP3            
     */
    u32         CMP0_SELP;
    /**
     * @brief �Ƚ��� 0 �źŸ���ѡ��
     * @see CMP_SELN_IN                   
     * @see CMP_SELN_REF                 
     * @see CMP_SELN_DAC                 
     * @see CMP_SELN_HALL_MID 
     */ 
    u32         CMP0_SELN;     
    
    FuncState   CMP0_IE;            /**<�Ƚ��� 0 �ж�ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    FuncState   CMP0_RE;            /**<�Ƚ��� 0 DMA ����ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    u32         CMP0_W_PWM_POL;     /**<�Ƚ��� 0 ���� PWM �źż���ѡ�� 0:�ߵ�ƽ��Ч��1:�͵�ƽ��Ч*/
    FuncState   CMP0_IRQ_TRIG;      /**<�Ƚ��� 0 ���ش���ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    FuncState   CMP0_IN_EN;         /**<�Ƚ��� 0 �ź�����ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    u32         CMP0_POL;           /**< �Ƚ��� 0 ����ѡ�� 0:�ߵ�ƽ��Ч��1:�͵�ƽ��Ч*/
    FuncState   CMP0_CHN3P_WIN_EN;  /**< MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 0 ���� DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
    FuncState   CMP0_CHN2P_WIN_EN;  /**< MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 0 ���� DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
    FuncState   CMP0_CHN1P_WIN_EN;  /**< MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 0 ���� DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
    FuncState   CMP0_CHN0P_WIN_EN;  /**< MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 0 ���� DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
    
 
    FuncState   CMP1_EN;            /**< �Ƚ��� 1 ʹ��\n ʹ�� DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
     /**
     * @brief �Ƚ��� 1 �ź�����ѡ��
     * @see CMP_SELP_IP0           
     * @see CMP_SELP_OPA0_IP       
     * @see CMP_SELP_OPA0_OUT      
     * @see CMP_SELP_IP1           
     * @see CMP_SELP_IP2           
     * @see CMP_SELP_IP3            
     */
    u32         CMP1_SELP;          
    /**
     * @brief �Ƚ��� 0 �źŸ���ѡ��
     * @see CMP_SELN_IN                   
     * @see CMP_SELN_REF                 
     * @see CMP_SELN_DAC                 
     * @see CMP_SELN_HALL_MID 
     */ 
    u32         CMP1_SELN;          
    FuncState   CMP1_RE;            /**<�Ƚ��� 1 �ж�ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    FuncState   CMP1_IE;            /**<�Ƚ��� 1 DMA ����ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    u32         CMP1_W_PWM_POL;     /**<�Ƚ��� 1 ���� PWM �źż���ѡ�� 0:�ߵ�ƽ��Ч��1:�͵�ƽ��Ч*/
    FuncState   CMP1_IRQ_TRIG;      /**<�Ƚ��� 1 ���ش���ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    FuncState   CMP1_IN_EN;         /**<�Ƚ��� 1 �ź�����ʹ��\n DISABLE:ʧ�ܣ�ENABLE��ʹ��*/
    u32         CMP1_POL;           /**< �Ƚ��� 1 ����ѡ�� 0:�ߵ�ƽ��Ч��1:�͵�ƽ��Ч*/
    FuncState   CMP1_CHN3P_WIN_EN;  /**< MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 1 ���� DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
    FuncState   CMP1_CHN2P_WIN_EN;  /**< MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 1 ���� DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
    FuncState   CMP1_CHN1P_WIN_EN;  /**< MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 1 ���� DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
    FuncState   CMP1_CHN0P_WIN_EN;  /**< MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 1 ���� DISABLE:ʧ�ܣ�ENABLE��ʹ�� */
}CMP_InitTypeDef;

void CMP_Init(CMP_InitTypeDef *);           // �Ƚ�����ʼ��
void CMP_StructInit(CMP_InitTypeDef *);     // �Ƚ������ýṹ���ʼ��
u8 GET_CMP_data(u8 CMPx,u8 GET_CMP_val);		// ��ȡ�Ƚ������
void CMP_ClearIRQFlag(u8 CMPx);             // ��CMP�ж�
u8   CMP_GetIRQFlag(u8 CMPx);               // ��CMP�ж�

#endif /*__lks32mc03x_cmp_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
