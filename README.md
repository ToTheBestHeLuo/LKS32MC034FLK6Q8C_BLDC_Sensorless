# LKS32MC034FLK6Q8C_BLDC_Sensorless
主内容位于Master分支下，Main分支只有README.md文件
# 适用说明
这份代码适用的电机是BLDC无刷电机（其反电动势为梯形波），目前测试过的电机kV值有两个：高转速低扭矩的2450kV以及低转速高扭矩的100kV，都需要确保其能够工作在较高的初始转速才能正常工作。最大能够支持的电气频率在4K（目前已测试），暂时还未做其他协议的适配。
# 调参说明
这部分暂时不做叙述，等日后代码支持的协议足够多了以后再添加这部分的介绍。
# 硬件说明
为了精简无感六步换相BLDC的电路和软件结构、同时减少硬件成本，这里使用了凌鸥创新（LKS）的集成电机驱动与控制为一体的芯片LKS32MC03x系列的LKS32MC034FLK6Q8C,集成了相电压检测网络、耐压200V的三相桥驱动电路以及LKS32MC03x的Cortex-M0内核，目前在立创商城上的售价为3元/片左右（10片以下）。在实际测试中选择的MOS管型号为NCE40H12K，主降压芯片为LV2842XLVDDCR(40V最大耐压，45V极限耐压)，电路板为双层板，尺寸可以优化到4cm*4cm以下，取决于电机三相线采用焊接式还是拔插式等，整体硬件成本较低，如果在嘉立创白嫖双层板，则硬件部分的成本在15元左右.
# 软件说明
## 外设初始化
这部分内容包括有PGA（负责母线电流采样以及过流信号输出）、比较器1（负责过流信号触发急停保护事件）、比较器0（负责换相逻辑的检测）、HALL（负责换相时间的检测）、UTimer0（负责安全任务的调度）、UTimer1（负责协议的处理）、MCPWM（负责三相控制信号的生成以及电机启动任务的调度）、DAC（负责过流保护阈值）、TemperatrueSensor（负责温度检测）
## 中断说明
### 1.HALL中断
当处在eBLDC_Run_Mode_COMP_Polling，当电机堵转时间超过20ms，会触发HALL中断，并将错误标志设置为eBLDC_Sys_Error_RotorBlock，进一步触发电机重启；而当处在eBLDC_Run_Mode_COMP_Int，当换相间隔超过0.833ms，则认为发生换相错误事件，从而触发电机重启。
### 2.MCPWM中断
这里有刹车中断以及电机启动任务的调度中断。当电机出现过流，会触发刹车中断，并将错误标志设置为eBLDC_Sys_Error_DriverBrake，进一步触发电机重启。调度中断本质是定时器轮询，轮询任务仅当错误标志为eBLDC_Sys_Error_None且当前工作在eBLDC_Run_Mode_COMP_Polling模式时才会有效。
### 3.ADC中断
当UTimer达到1ms时产生溢出事件，溢出事件同时会触发ADC采样（包括母线电压采样、母线电流采样、温度传感器采样），当采样完成后触发ADC中断，在这里完成安全任务的调度。
### 4.COMP中断
在比较器中断中完成换相，仅当错误标志为eBLDC_Sys_Error_None且当前工作在eBLDC_Run_Mode_COMP_Int模式时才会有效，若发生错误，则会将错误标志设置为eBLDC_Sys_Error_RotorBlock或者eBLDC_Sys_Error_Commutation，但错误发生一般只会设置为eBLDC_Sys_Error_Commutation，这是因为触发eBLDC_Sys_Error_RotorBlock事件需要20ms窗口，而eBLDC_Sys_Error_Commutation事件需要的窗口更短。
### 5.其余中断
将于后续添加，预计的有协议解析相关的中断。
## 安全任务的调度
1.复位全局变量<br>
2.检查母线电压是否合理<br>
3.等待自举电容充电完成<br>
4.等待电机起动命令<br>
5.进入轮询状态，监测系统变量，当发生严重故障时进入复位状态<br>
## 电机启动任务的调度
1.转子预定位<br>
2.固定占空比、递减频率，开环实现电机加速<br>
3.固定占空比、固定频率，检测电机是否进入稳定自旋，同时检测换相事件，若发生错误则进入重启<br>
4.切入无感换相，稳定旋转多圈后切入由比较器中断控制的无感换相逻辑，自此，若电机工作正常，将不再进入这个调度任务<br>
# ========华丽的分割线=========
# 修订日志
## 2024.12.2
### 异常描述
当电机工作在高转速环境下会误触发换相错误事件eBLDC_Sys_Error_Commutation
### 解决措施
减少eBLDC_Run_Mode_COMP_Int模式下HALL溢出的阈值，使其能够捕获到低速异常，而低速异常容易导致换相错误，在发生这个事件以后会自动重启电机。
## 2024.12.5
### 新增内容
添加对dShot协议的支持，具体内容还在等待后续测试。目前还在完善协议部分的内容，由于LKS32MC034系列的逻辑电平是5V，其逻辑信号1的触发阈值在70%*5V=3.5V以上，因此需要重新设计一个新的Demo板子来验证（5V与3.3V通信逻辑的转换），此外，针对后续可能的4合1版本，需要将电流采样部分从MCU内部OPA转移到外部OPA来进行实现。
## 2024.12.6
### 异常描述
针对低kV值（测试电机为kV=100rpm/V）电机存在比较器中断换相失败的问题。
### 解决措施
调整启动电压（增大初始油门占空比）和开环频率，调整HALL阈值（进入CMP中断后HALL阈值更大）。
## 2024.12.8
### 新增内容
添加对dShot协议的部分支持（支持单向dShot600,dShot300,dShot150），上电后系统根据发送端的dShot信号自匹配相应的dShotXXX协议。但需要注意的是当使用dShot600时，误码率会增加，建议的是使用dShot300或者dShot150。
## 2024.12.24
### 更改内容
摸了两个星期的🐟，由于没找到BLHeli32的Bootloader程序，尽管可以通过飞控程序定位到serial_4way.c等文件，但短期内依然无法准确解析出飞控与电调之间的单线通信协议，因此打算对dShot进行魔改，代码中将其重命令为sGxxx(xxx=600,300,150)，双方通信采用开漏输出+上拉电阻形式以避免一方输出1、一方输出0的问题（尽管有输出内阻，但还是应当考虑），魔改的sGxxx支持参数修改和保存（这里包括起动油门、起动频率、rpm滤波等参数的直接修改，并直接保存到片内flash）、电机蜂鸣等功能。关于sGxxx后续的协议暂时还没想好。
### 异常描述
电机从丢步进入复位重启存在失败的异常
### 解决措施
根本原因在于有一些关键寄存器的值没得到复位，因此在HALL中断中添加了一系列复位的函数
## 2025.1.6
### 新增内容
最近在自定义sGxxx的协议，目前暂定其为16位，每位的发送速率为300KHz。新版本中添加了基本的文件支持，后续调试好sG后将其作为一个核心功能，sG最大的特点就是单工通信，并通过一系列机制来处理错误消息，分Slave和Master两种代码。此外，将几个核心的电机起动和闭环运行参数皆提取出来作为可调整量，实际上，后面打算通过sG协议来调整，并将其存储到Flash区域。
