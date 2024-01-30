CPEN 430 Final Project: Golay (24,12) Encoder/Decoder
Mark Madler, Joel Vincent

Our project will have a Golay (24,12) encoder/decoder using the NIOSII embedded processor and the DE2115 Atera board.
Making use of the available software provided by the NIOSII, we were able to make code for a Golay encoder and decoder.
The program will take user input from a board, simulate noise on the user input, and run it through the Golay so show its
ability to fix the errors and output the users original input.

Instructions on setting up the program on your machine:

1)  Download golay.zip
2)  Extract to desktop(or whichever location you desire)
3)  Open the Quartus .QPF file
4)  On Quartus, go to Tools -> Programmer
5)  Make sure to use the included .SOF file to JTAG program the DE2115 FPGA
6)  Make sure USB-Blaster is selected and the DE2115 board is on, then press Start
7)  Back on Quartus, select Tools -> Nios II Software Build Tools for Eclipse
8)  In Eclipse, click on File->Switch Workplace->Other...
9)  Select Browse and navigate to the software folder in desktop(or whichever file you extracted the zip to) and press ok.
10) After Eclipse restarts, right click on the project explorer and select Import...
11) In the General file, select "Existing Projects into Workspace" then select next
12) Select Browse again and select the software folder located in the unzipped project
13) Press ok and then Finish
14) Back in Eclipse, right click blinky-sw_bsp and select NIOS II->generate BSP
15) Right click blinky-sw_bsp and select build
16) Right click blinky-sw and select build
17) right click blinky-sw and select Run As-> NIOSII Hardware
18) Once you see “Initialization Done!” the project is ready to be used.

For instructions that include pictures, please see the "NIOSII_On_DE2_Project_Initialization_Guide.docx" file



Instructions on how to run the program:

The project starts by showing the prompt:
"Press KEY2 to begin"

It will then show "Input in Key1,3:"

You will then input 1's and 0's by using the KEY3 and KEY1 buttons respectively. 

Once you've typed 12 bits, the program will automatically input the 12 bits and then
print on the LCD: "Max Error SW0-2 KEY2 to advance"

You will then flip any of SW0-2 to give the program the number of errors you want to simulate.
These switches work in a traditional binary format, flipping SW1 will give you up to 2 errors,
flipping SW1 and SW0 will give you up to 3 errors, etc. Once you are satisfied with your number 
of errors, press KEY2 to continue.

The LCD will show your word, then it will add simulated noise error to it. It will then display 24 bits 
showing your inputted word with error caused by noise along with another 12 bits made by the Golay.
It will show you the number of errors within your input, and it will fix those errors, showing you
the corrected code which should match your original input.

You can hit KEY0 at anytime during the program to reset it to the beginning.

