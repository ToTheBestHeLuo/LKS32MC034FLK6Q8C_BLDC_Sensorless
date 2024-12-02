# LKS32MC034FLK6Q8C_BLDC_Sensorless
主内容位于Master分支下，Main分支只有README.md文件
# 硬件说明
为了精简无感六步换相BLDC的电路和软件结构、同时减少硬件成本，这里使用了凌鸥创新（LKS）的集成电机驱动与控制为一体的芯片LKS32MC03x系列的LKS32MC034FLK6Q8C,集成了相电压检测网络、耐压200V的三相桥驱动电路以及LKS32MC03x的Cortex-M0内核，目前在立创商城上的售价为3元/片左右（10片以下）。在实际测试中选择的MOS管型号为NCE40H12K，主降压芯片为LV2842XLVDDCR(40V最大耐压，45V极限耐压)，电路板为双层板，尺寸可以优化到4cm*4cm以下，取决于电机三相线采用焊接式还是拔插式等，整体硬件成本较低，如果在嘉立创白嫖双层板，则硬件部分的成本在15元左右.
# 软件说明
## 外设初始化
这部分内容包括有PGA（负责母线电流采样以及过流信号输出）、比较器1（负责过流信号触发急停保护事件）、比较器0（负责换相逻辑的检测）、HALL（负责换相时间的检测）、UTimer0（负责安全任务的调度）、UTimer1（负责协议的处理）、MCPWM（负责三相控制信号的生成以及电机启动任务的调度）、DAC（负责过流保护阈值）、TemperatrueSensor（负责温度检测）
## 中断说明
### 1.HALL中断
当电机堵转时间超过20ms，会触发HALL中断，并将错误标志设置为eBLDC_Sys_Error_RotorBlock，进一步触发电机重启。
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
