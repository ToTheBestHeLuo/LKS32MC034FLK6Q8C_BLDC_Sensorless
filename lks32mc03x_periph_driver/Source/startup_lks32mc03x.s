;/*******************************************************************************
; * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
; *
; * 文件名称： startup_lks32mc061.s
; * 文件标识：
; * 内容摘要： 启动代码
; * 其它说明： 无
; * 当前版本： V 1.0
; * 作    者： 李鹏
; * 完成日期： 2015年11月5日
; *
; * 修改记录1：
; * 修改日期：2015年11月5日
; * 版 本 号：V 1.0
; * 修 改 人：李鹏
; * 修改内容：创建
; *
; * 修改记录2：
; * 修改日期：
; * 版 本 号：
; * 修 改 人：
; * 修改内容：
; *
; *******************************************************************************/
;* <<< Use Configuration Wizard in Context Menu >>>   
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
                ; 0-3
                DCD     TIMER0_IRQHandler;
                DCD     TIMER1_IRQHandler;
                DCD     MCPWM0_IRQHandler;
                DCD     MCPWM1_IRQHandler;

                ;4-7
                DCD     I2C_IRQHandler;
                DCD     SPI_IRQHandler;
                DCD     GPIO_IRQHandler;
                DCD     HALL_IRQHandler;

                ;8-11
                DCD     UART_IRQHandler;
                DCD     CMP_IRQHandler;
                DCD     ADC_IRQHandler;
                DCD     DMA_IRQHandler;

                ;12-15
                DCD     WAKE_IRQHandler;
                DCD     SW_IRQHandler;
                DCD     0;
                DCD     0;

                ;16-19
                DCD     0;
                DCD     0;
                DCD     0;
                DCD     0;

                ;20-23
                DCD     0;
                DCD     0;
                DCD     0;
                DCD     0;

                ;24-27
                DCD     0;
                DCD     0;
                DCD     0;
                DCD     0;

                ;28-31
                DCD     0;
                DCD     0;
                DCD     0;
                DCD     0;
					
;				;user add
;				DCD 	0;
;				DCD 	0;
;				DCD 	0;
;				DCD 	0;
                
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler   PROC
				EXPORT  Reset_Handler                 [WEAK]
				IMPORT  __main
				IMPORT  SystemInit



				LDR     R0, =__initial_sp          ; set stack pointer 
				MSR     MSP, R0  


ApplicationStart         
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  TIMER0_IRQHandler             [WEAK]
                EXPORT  TIMER1_IRQHandler             [WEAK]
                EXPORT  MCPWM0_IRQHandler             [WEAK]
                EXPORT  MCPWM1_IRQHandler             [WEAK]
                EXPORT  I2C_IRQHandler           	  [WEAK]
                EXPORT  SPI_IRQHandler           	  [WEAK]
                EXPORT  GPIO_IRQHandler               [WEAK]
                EXPORT  HALL_IRQHandler               [WEAK]
                EXPORT  UART_IRQHandler               [WEAK]
                EXPORT  CMP_IRQHandler                [WEAK]
                EXPORT  ADC_IRQHandler                [WEAK]
                EXPORT  DMA_IRQHandler                [WEAK]
                EXPORT  WAKE_IRQHandler               [WEAK]
                EXPORT  SW_IRQHandler                 [WEAK]
                    
TIMER0_IRQHandler   
TIMER1_IRQHandler   
MCPWM0_IRQHandler   
MCPWM1_IRQHandler   
I2C_IRQHandler 
SPI_IRQHandler 
GPIO_IRQHandler     
HALL_IRQHandler     
UART_IRQHandler    
CMP_IRQHandler     
ADC_IRQHandler     
DMA_IRQHandler     
WAKE_IRQHandler      
SW_IRQHandler    
                  

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;************************ (C) COPYRIGHT LINKO Semiconductor *****END OF FILE*****
