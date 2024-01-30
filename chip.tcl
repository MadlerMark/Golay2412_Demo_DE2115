# CLOCK
set_location_assignment PIN_Y2 -to clk
set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to clk
# RESET_n
set_location_assignment PIN_M23 -to reset_n
set_instance_assignment -name IO_STANDARD "2.5 V" -to reset_n
# MOST LEFT SWITCH (hard-wired)
set_location_assignment PIN_Y23 -to sw
set_instance_assignment -name IO_STANDARD "2.5 V" -to sw
# GREEN LEDS (through PIO)
set_location_assignment PIN_E21 -to leds[0]
set_location_assignment PIN_E22 -to leds[1]
set_instance_assignment -name IO_STANDARD "2.5 V" -to leds[0]
set_instance_assignment -name IO_STANDARD "2.5 V" -to leds[1]
# SWITCHES (through PIO)
set_location_assignment PIN_AB28 -to switches[0]
set_location_assignment PIN_AC28 -to switches[1]
set_instance_assignment -name IO_STANDARD "2.5 V" -to switches[0]
set_instance_assignment -name IO_STANDARD "2.5 V" -to switches[1]
set_location_assignment PIN_AC27 -to switches[2]
# RED LED (hard-wired)
set_location_assignment PIN_G19 -to rled
set_instance_assignment -name IO_STANDARD "2.5 V" -to rled
# LCD DATA lines + Enables and such
set_location_assignment PIN_M5 -to lcd[7]
set_location_assignment PIN_M3 -to lcd[6]
set_location_assignment PIN_K2 -to lcd[5]
set_location_assignment PIN_K1 -to lcd[4]
set_location_assignment PIN_K7 -to lcd[3]
set_location_assignment PIN_L2 -to lcd[2]
set_location_assignment PIN_L1 -to lcd[1]
set_location_assignment PIN_L3 -to lcd[0]
#DATA
set_location_assignment PIN_L4 -to lcd[11]
#EN
set_location_assignment PIN_M1 -to lcd[8]
#RW
set_location_assignment PIN_M2 -to lcd[9]
#RS
set_location_assignment PIN_L5 -to lcd[10]
#on 


set_location_assignment PIN_N21 -to start

set_location_assignment PIN_M21 -to bin[0]
set_location_assignment PIN_R24 -to bin[1]