# CoolBox
STM32F7 project (compatible with stm32F746g-disco board) with touchgfx and Freertos.

Peripheral enabled ==> IWDG, ADC, LWIP and Modbus tcp/ip.

Collect and convert analog voltages (ADC1), store the result in modbus input register (30001 & 30002). To test this project, you can can read the data using "ModBus tool" like modbus poll through ethernet (TCP/IP).

For testing you can modifiy the ip adress directly in lwip/app/lwip.c file.

Displays the conversion result on touchscreen thanks to touchgfx.



                               Vcc=5v
                                |              -------------------
                               | |             |                 |
                               | |             |                 |
                                |  Vcc/2       |                 |
                                | ------------>| A0              |--> ethernet
                               | |             |                 |
                               | |             |                 |
                                |              |                 |
                               Gnd             |                 |
                                               |                 |
                               Vcc=12v         |                 |
                                |              |                 |
                               | |             |                 |
                               | |             |                 |         
                                |  Vcc/4       |                 |
                                |------------->| A5              |
                               | |             |                 |
                               | |             | SMT32F746ZGT6   |--> Touchscreen (Gauges:5v & 12V)
                                |              |                 |
                               Gnd             -------------------
                               
Software compatibility:
STM32CubeIDE ==> V1.2.1
STM32CubeMX ==> V5.6
TouchGFX ==> V4.13

To customize or modify the program open .cproject in STM32CubeIDE workspace. 
In linker setting don't forget to add gcc library path if different, by default gcc library path is: "C:/TouchGFXProjects/CoolBox_CubeIDE_V1.1/Middlewares/ST/touchgfx/lib/core/cortex_m7/gcc"
