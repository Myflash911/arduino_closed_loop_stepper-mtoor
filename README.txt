Closed loop step motor controller

Pin       Function                     ESP-8266 Pin                Arduino ProMini pins (main branch)
TX        TXD                          TXD                         
RX        RXD                          RXD                         
A0        Analog input, max 3.3V input A0                          
D0        IO                           GPIO16    PIN_STEP_OUT      A0 
D1*       IO, SCL                      GPIO5     PIN_IN_A          D2 
D2*       IO, SDA                      GPIO4     PIN_IN_B          D3 
D3        IO, 10k Pull-up              GPIO0     PIN_EN_OUT        A2 
D4        IO, 10k Pull-up,BUILTIN_LED  GPIO2     PIN_LED           D7 
D5*       IO, SCK                      GPIO14    PIN_STEP_IN       D8   
D6*       IO, MISO                     GPIO12    PIN_DIR_IN        D9 
D7*       IO, MOSI                     GPIO13    PIN_EN_IN         D10
D8        IO, 10k Pull-down, SS	       GPIO15    PIN_DIR_OUT       A1  
G         Ground                       GND
5V        5V                          -
3V3       3.3V                         3.3V
RST       Reset                        RST

Architecture of closed loop step motor controller:

                                             +---------+--------+
                        +---------------+    | Rotary  |  Step  |
                        | ESP2866       |    | encoder |  Motor |
                        |               |    |         |        |
                        |               |    |         |        |
           stepIn------>|GPIO14         |    |         |        |
                        |               |    |         |        |
           dirIn------->|GPIO12         |    |  A   B  |        |
                        |               |    +---------+--------+
           EnIn-------->|GPIO13         |       |   |     ^^^^
                        |               |IN_A   |   |     ||||
           LED---------<|GPIO2     GPIO5|<------+   |     ||||
                        |               |           |     ||||
                        |          GPIO4|IN_B       |     ||||
                        |               |<----------+     ||||
                        |GPIO GPIO GPIO |                 ||||
                        | 0    15   16  |                 ||||
                        +---------------+                 ||||
                           |   |   |                      ||||
                           |   |   |                      ||||
                           V   V   V                      ||||
                        +---------------+                 ||||
                        | !EN DIR  STEP |                 ||||
                        |               |                 ||||
                        |  Standard    A|-----red---------+|||
                        |              _|                  ||| 
                        |  Stepmotor   A|-----blue---------+||
                        |               |                   ||  
                        |  controller  B|-----green---------+|
                        |              _|                    |
                        |  e.g. TB6600 B|-----black----------+
                        |               |
                        |               |
                        +---------------+                   

Block diagram (STEP_LOSS_COMPENSATION-mode)
                   +----------------------------------+  
                   |   +----------+                   |  
 Input(Step,En,Dir)|   | Input    |                   |                                             
 ------------------+-->| counter  |                   |                                                  
                       |          |                   |              +--------------+       +--------------+
                   +---|          |                   |              |              |       | Step Motor   |
                   |   +----------+                   V    (Switch)  | Step         |       |              |
                   |                                  +----O         | Motor        |------>|              |
                   |   +----------+   +----------+         ------O-->| Driver       |       |              |
                   +-->|Deviation |   |          |    +----O  ^      | (e.g TB6600) |       |              |
                       |counter   |-->| >n steps |    ^       |      |              |       |              |
                   +-->|          |   |          |    |       |      +--------------+       +--------------+
                   |   +----------+   +---------+     |       |                             | Rotary       |
                   |                        |         |       |                             | encorer      |
                   |                        V         |       |                             |              |
                   |   +----------+      +----------------+   |                             |              |
                   +---|Rotation  |      |                |   |                             +--------------+
                       |position  |      | Fix position   |   |                                    |
                       |counter   |      | (Generate      |---+                                    |     
                   +-->|          |      |step,dir pulses)|                                        |     
                   |   +----------+      +----------------+                                        |     
                   |                                                                               |  
                   +-------------------------------------------------------------------------------+


                                   

 Compatible with:
     * ESP2866
     * a standard step motor controller (e.g. a4988 and TB6600)
     * a standard rotary incremental encoder (e.g HN3806-AB-400N, AS5040 or similar)
               +---+   +---+   +---+   +---+
            A -+   +---+   +---+   +---+

              ---+   +---+   +---+   +---+  
            B    +---+   +---+   +---+   +--
     * NEMA xx Stepper motor

HOX!
  * You can still use the same PCB board (as in the main branch), but you need an adapter. The adapter converts the pinout for ESP2866.
    https://github.com/arttupii/CLSMB/blob/ESP2866/AS5040/ArduinoProMiniESP2866Adapter_GERBER.zip
  * Use Geekcreit?? D1 mini with the adapter
    https://www.banggood.com/Geekcreit-D1-mini-V2_2_0-WIFI-Internet-Development-Board-Based-ESP8266-4MB-FLASH-ESP-12S-Chip-p-1143874.html?rmmds=myorder&cur_warehouse=CN

Demo video: 
https://youtu.be/jLogS5AQ-yQ (AS5040 encoder and A4988 step motor controller)
https://youtu.be/jxansaLNb5I (Serial Plotter view. #define ENABLE_PRINTS 100)

Useful links:
https://www.banggood.com/Geekcreit-D1-mini-V2_2_0-WIFI-Internet-Development-Board-Based-ESP8266-4MB-FLASH-ESP-12S-Chip-p-1143874.html?rmmds=myorder&cur_warehouse=CN
https://www.banggood.com/TB6600-Upgraded-Stepper-Motor-Driver-Controller-for-4A-940V-TTL-32-Micro-Step-2-or-4-Phase-of-4257-Stepper-Motor-3D-Printer-CNC-Part-p-1453122.html?rmmds=search&cur_warehouse=CN
https://www.banggood.com/3D-Printer-42-Stepper-Motor-Drive-Expansion-Board-8825-A4988-p-1028319.html?rmmds=search&cur_warehouse=CN
https://www.banggood.com/Geeetech-Stepper-Driver-A4988-With-Heatsink-And-Sticker-For-3D-Printer-p-1229214.html?rmmds=search&cur_warehouse=CN
