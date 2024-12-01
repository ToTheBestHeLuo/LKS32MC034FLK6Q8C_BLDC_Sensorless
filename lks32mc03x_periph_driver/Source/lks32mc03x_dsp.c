
 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_dsp.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� DSP�������� \n
 * ����˵���� �� \n
 *@par 
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��4��18�� <td>1.0     <td>Zhu Jie   <td>����
 * </table>
 */
#include "lks32mc03x_dsp.h"

static volatile u8 dsp_flg; /**< ��־λ�������жϳ����Ƿ񱻴��*/

 /**
 *@brief @b ��������:   void DSP_Cmd(FuncState state)
 *@brief @b ��������:   DSPʹ�ܺ͹ر�
 *@see���������ݣ�       SYS_ModuleClockCmd()
 *@param���������       state��ENABLE��ʹ�� ��DISABLE��ʧ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
			DSP_Cmd(ENABLE);//ʹ��DSPʱ��
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��4��18�� <td>1.0     <td>Zhu Jie          <td>����
 * </table>
 */
void DSP_Cmd(FuncState state)
{
   SYS_ModuleClockCmd(SYS_Module_DSP, state); /* DSPʱ��ʹ�� */
}

 /**
 *@brief @b ��������:   void DSP_CalcDivision(stru_DiviComponents * stru_Divi)
 *@brief @b ��������:   DSP��������
 *@see���������ݣ�       stru_DiviComponents ��SYS_SoftResetModule()
 *@param���������       .nDID,������   .nDIS����
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        
                        1������10������������� \n
                        2��������DividendΪ32λ��С������Χ�� -(2^31 - 1) ~ (2^31 - 1) \n
                        3������DivisorΪ16λ��С������Χ�� -(2^15 - 1) ~ (2^15 - 1) \n
                        4����������֧�ָ�ֵΪ-2^31��������֧�ָ�ֵΪ-2^15 \n
                        5����QuotientΪ32λ��С \n
                        6������RemainderΪ16λ��С
 *@warning              ��
 *@par ʾ�����룺
 *@code    
            stru_DiviComponents DiviData; //���������������ṹ�����
            DiviData.Dividend = 100;//��������ֵ
            DiviData.Divisor = 10;  //������ֵ
			DSP_CalcDivision(&DiviData);
            �������̴���λ�ã�DiviData.Quotient
            ��������������λ�ã�DiviData.Remainder
  @endcode
 *@par �޸���־:      
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��4��18�� <td>1.0     <td>Zhu Jie          <td>����
 * </table>
 */
void DSP_CalcDivision(stru_DiviComponents *stru_Divi)
{
	 u8 dsp_flg_old;
    do
    {
        dsp_flg++;
        dsp_flg_old = dsp_flg;
        SYS_SoftResetModule(SYS_Module_DSP);
        DSP_DID = stru_Divi->Dividend; /* �������Ĵ�����ֵ */
		DSP_DIS = stru_Divi->Divisor;  /* �����Ĵ�����ֵ   */

		stru_Divi->Quotient = DSP_QUO;  /* ȡ���̼Ĵ���ֵ */
		stru_Divi->Remainder = DSP_REM;/* ȡ�������Ĵ���ֵ */
    } while (dsp_flg_old != dsp_flg);  /* ��ֹDSP���㱻��� */
}

 /**
 *@brief @b ��������:   uint32_t DSP_GetSqrt(uint32_t Data)
 *@brief @b ��������:   DSP��ƽ������
 *@see���������ݣ�       SYS_SoftResetModule()
 *@param���������       ��������
 *@param���������       ��
 *@return�� �� ֵ��      ������
 *@note����˵����        
                        1������8������������� \n
                        2����������DataΪ32λ�޷�����������Χ��(0 ~ (2^31)) \n
                        3��������sqrt(Data)Ϊ16λ�޷�����������Χ��(0 ~ (2^15)) \n
 *@warning              ��
 *@par ʾ�����룺
 *@code    
            u16 GetSqrt_Value = 0;
            GetSqrt_Value = DSP_GetSqrt(100);//sqrt(100) 100�����Ž��Ϊ10
  @endcode   
 *@par �޸���־:    
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��4��18�� <td>1.0     <td>Zhu Jie          <td>�޸�
 * </table>
 */
static volatile u8 dsp_flg2; /**< ��־λ�������жϳ����Ƿ񱻴��*/
uint32_t DSP_GetSqrt(uint32_t Data)
{
	  uint8_t dsp_flg_old;
      uint32_t  tdsp_sqrt;
    do
    {
        dsp_flg2++;
        dsp_flg_old = dsp_flg2;
        DSP_RAD = Data;  /*�������Ĵ�����ֵ*/
       tdsp_sqrt = DSP_SQRT;
    } while (dsp_flg_old != dsp_flg2);  /* ��ֹDSP���㱻��� */
	 
   return tdsp_sqrt ;
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
