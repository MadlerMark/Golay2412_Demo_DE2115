#include <sys/alt_stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "lcd.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//NOTES TO BUILD PRESENTATION FROM:
/*
-MATRIX MATH IS HARD WITHOU C99 COMPILER!
-TESTING DECODER IS DIFFICULT
-RANDOM NUMBER GENERATION IS DIFFICULT
*/


//GLOBAL VARIABLES FOR GOLAY(24,12) CODE:

//GOLAY CODE GENERATOR MATRIX:
//GUIDE:    	 0 1 2 3 4 5 6 7 8 9 a b 0 1 2 3 4 5 6 7 8 9 a b
int G[12][24] ={{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,1,0,1},
				{0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1},
				{0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,1,1},
				{0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,1,0,1},
				{0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1},
				{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,1,1,1},
				{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1},
				{0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,0,1},
				{0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,0,1,1,1,0,0,1},
				{0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,1,1,0,0,0,1},
				{0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1,0,0,0,1,1},
				{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0}};
//GOLAY CODE A MATRIX:
//GUIDE:		 0 1 2 3 4 5 6 7 8 9 a b
int A[12][12] ={{1,1,0,1,1,1,0,0,0,1,0,1},
				{1,0,1,1,1,0,0,0,1,0,1,1},
				{0,1,1,1,0,0,0,1,0,1,1,1},
				{1,1,1,0,0,0,1,0,1,1,0,1},
				{1,1,0,0,0,1,0,1,1,0,1,1},
				{1,0,0,0,1,0,1,1,0,1,1,1},
				{0,0,0,1,0,1,1,0,1,1,1,1},
				{0,0,1,0,1,1,0,1,1,1,0,1},
				{0,1,0,1,1,0,1,1,1,0,0,1},
				{1,0,1,1,0,1,1,1,0,0,0,1},
				{0,1,1,0,1,1,1,0,0,0,1,1},
				{1,1,1,1,1,1,1,1,1,1,1,0}};
//GOLAY CODE H MATRIX:
			   //0 1 2 3 4 5 6 7 8 9 a b
int H[24][12] ={{1,0,0,0,0,0,0,0,0,0,0,0},
				{0,1,0,0,0,0,0,0,0,0,0,0},
				{0,0,1,0,0,0,0,0,0,0,0,0},
				{0,0,0,1,0,0,0,0,0,0,0,0},
				{0,0,0,0,1,0,0,0,0,0,0,0},
				{0,0,0,0,0,1,0,0,0,0,0,0},
				{0,0,0,0,0,0,1,0,0,0,0,0},
				{0,0,0,0,0,0,0,1,0,0,0,0},
				{0,0,0,0,0,0,0,0,1,0,0,0},
				{0,0,0,0,0,0,0,0,0,1,0,0},
				{0,0,0,0,0,0,0,0,0,0,1,0},
				{0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,0,1,1,1,0,0,0,1,0,1},
				{1,0,1,1,1,0,0,0,1,0,1,1},
				{0,1,1,1,0,0,0,1,0,1,1,1},
				{1,1,1,0,0,0,1,0,1,1,0,1},
				{1,1,0,0,0,1,0,1,1,0,1,1},
				{1,0,0,0,1,0,1,1,0,1,1,1},
				{0,0,0,1,0,1,1,0,1,1,1,1},
				{0,0,1,0,1,1,0,1,1,1,0,1},
				{0,1,0,1,1,0,1,1,1,0,0,1},
				{1,0,1,1,0,1,1,1,0,0,0,1},
				{0,1,1,0,1,1,1,0,0,0,1,1},
				{1,1,1,1,1,1,1,1,1,1,1,0}};
//END GLOBAL VARIABLES

//DEFINE MATRIX SIZES
#define M 1
#define N 12
#define P 24

//MINI LINEAR ALGEBRA/ MATRIX LIBRARY:
//Description: prints out a MxN array to the console
void print(int *arr, int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++){
      for (j = 0; j < n; j++)
        printf("%d ", *((arr+i*n) + j));
      printf("\n");
    }
}

//Description: prints out a 2D array to the LCD on the DE2-115
void print2D_toLCD(int *arr, int m, int n)
{
    int i, j;
    set_position(0x00);
    for (i = 0; i < m; i++){
      for (j = 0; j < n; j++){
    	  if(j == 16)
    	  {
    		  set_position(0x40);
    	  }
        write_char(*((arr+i*n) + j) + 0x30);
      }
      //printf("\n");
    }
}
//Matrix Mx12 * Nx24 = N*12x24
//Description: multiplies a 12
void matrixMultiply12_24(int mat1[][12], int mat2[][24], int res[][24], int ROW1, int ROW2)  {
   int row, col, i;
   int sum;
   for (row = 0; row < ROW1; row++) {
      for (col = 0; col < 24; col++) {
         sum = 0;
         for (i = 0; i < ROW2; i++) {
            sum += (*(*(mat1 + row) + i)) * (*(*(mat2 + i) + col));
         }
         *(*(res + row) + col) = sum %2;
      }
   }
}
void matrixMultiply24_12(int mat1[][24], int mat2[][12], int res[][12], int ROW1, int ROW2)  {
   int row, col, i;
   int sum;
   for (row = 0; row < ROW1; row++) {
      for (col = 0; col < 12; col++) {
         sum = 0;
         for (i = 0; i < ROW2; i++) {
            sum += (*(*(mat1 + row) + i)) * (*(*(mat2 + i) + col));
         }
         *(*(res + row) + col) = sum %2;
      }
   }
}
void matrixMultiply12_12(int mat1[][12], int mat2[][12], int res[][12], int ROW1, int ROW2)  {
   int row, col, i;
   int sum;
   for (row = 0; row < ROW1; row++) {
      for (col = 0; col < 12; col++) {
         sum = 0;
         for (i = 0; i < ROW2; i++) {
            sum += (*(*(mat1 + row) + i)) * (*(*(mat2 + i) + col));
         }
         *(*(res + row) + col) = sum %2;
      }
   }
}

void Array_Add(int arr1[][12],int arr2[][12],int result[][12],int row)
{
	for(int i=0; i < 12;i++)
	{
		result[0][i] = (arr1[0][i] + arr2[row][i])%2;
	}
}
void Array_Add24(int arr1[][24],int arr2[][24],int result[][24],int row)
{
	for(int i=0; i < 24;i++)
	{
		result[0][i] = (arr1[0][i] + arr2[row][i])%2;
	}
}

void transpose(int *arr, int m, int n,int *res)
{
    int i, j;
    set_position(0x00);
    for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
    	  *((res+j*n) + i) = *((arr+i*n) + j);
}

int weight(int *arr, int n)
{
	int count = 0;
	for (int i=0;i<n;i++)
		if (*(arr+i) == 1)
			count++;
	return count;
}
//END LINEAR ALGEBRA FUNCTIONS




//binary base = 0x101000

int main()
{
	Init_LCD();
	int rand_counter = 0;
	int startKey_pressed = 1;
	clear_display();
	set_position(0x00);
	write_string("Press KEY2");
	set_position(0x40);
	write_string("to begin");
	while(1)
	{
		delay1ms(1);
		rand_counter++;
		startKey_pressed = IORD_ALTERA_AVALON_PIO_DATA(0x101010); //start_base
		if (startKey_pressed == 0)
		{
			printf("start program... \n");
			break;
		}
	}
	int a[M][N];
	//the all zero codeword:
	for(int i =0; i<M;i++)
	{
		for(int j=0;j<N;j++)
		{
			a[i][j] = 0;
			if (j == 11)
			{
				//a[i][j] = 1;
			}
		}
	}
	int b = 0;
	clear_display();
	set_position(0x00);
	write_string("input in KEY1,3:");
	set_position(0x40);
	while(1)
	{
		int bin_in = IORD_ALTERA_AVALON_PIO_DATA(0x101000);
		//printf("bin_in: %d \n", bin_in);
		if (bin_in != 0x03)
		{
			if (bin_in == 2)
			{
				a[0][b++] = 0;
				write_char('0');
				delay1ms(7);
			}
			else if(bin_in  == 1)
			{
				a[0][b++] = 1;
				write_char('1');
				delay1ms(7);
			}
		}
		if( b == 12)
			break;
		//delay1ms(15);
	}

	//INITIALIZATION FROM BLINKY PROJ:
	int switch_data;
	int delay=0;
	int led_pattern=0x0;
	clear_display();
	set_position(0x00);
	write_string("Max Error SW0-2");
	set_position(0x40);
	write_string("KEY2 to advance");
	alt_putstr("Ciao from Nios II!\n");

	while(1)
	{
		delay1ms(1);
		rand_counter++;
		startKey_pressed = IORD_ALTERA_AVALON_PIO_DATA(0x101010); //start_base
		if (startKey_pressed == 0)
		{
			printf("start error... \n");
			break;
		}
	}

	//Begin Input Routine:


	//Begin Error Routine:
	switch_data = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);



	//LCD TESTING:
//	char* str = "Mark";
//	char* str2 = "Talarico";
//
//	write_string(str);
//	delay1ms(15);
//	//clear_display();
//	set_position(0x40);
//	write_string(str2);


	//DECLARATION FOR MATRIX STUFF:

	//int b[N][M];
	int c[M][P];
	int cop[M][P];




	//SOME TEST MATRICES:
	int testa[2][3] = {{1,2,3},{0,0,4}};
	int testb[3][2] = {{2,3},{2,1},{1,5}};
	//printf("Golay Generator Matrix: \n");
	//print(&G,24,12);
	printf("Input Codeword: c:\n");
	print(&a, M,N );

	//ENCODE A USING GOLAY(24,12);
	//c = aG
	matrixMultiply12_24(a,G,c,M,N);

	printf("Encoded word: \n");
	print(&c,M,P);
	clear_display();
	set_position(0x40);
	write_string("INPUT WORD");
	print2D_toLCD(&c,M,P-12); //just first 12 bits are codeword
	delay1ms(40);
	set_position(0x00);
	clear_display();
	write_string("Beginning");
	set_position(0x40);
	write_string("Noise simul");

  //copy encoded message to copy
  for(int i=0; i<M;i++){
	  for(int j=0; j<P;j++)
		  cop[i][j] = c[i][j];
  }

  //CHANNEL
  //create random errors:
  srand(rand_counter); //time() does not work on this system, seed always same
  for (int i=0; i< switch_data; i++ ){
	  int r = rand()%24;
	  //printf("rand = %d",r);
	  c[0][r] = !c[0][r];
//	  if(!r)
//	  {
//		  c[0][i] = !c[0][i];
//	  }
  }


  printf("NOISE ADDED\n");
//  for (int i =0; i < 24; i++){
//	  if ((i == 12)|(i==13)|(i==18))
//	  {
//		  c[0][i] = 1;
//	  }
//	  else
//		  c[0][i] = 0;
//  }
  //c[1][10] = 0; c[1][12] = 0; c[1][13] = 1; c[1][14] = 0;
  printf("received: \n");
  print(&c, 1, 24);
  delay1ms(10);
  clear_display();
  print2D_toLCD(&c,M,P);
  //printf("\n");
  //END CHANNEL

  //SHOW RECEIVED
  //delay1ms(10);
  //clear_display();
  //print2D_toLCD(&c,M,P);
  //END SHOW RECEIVED

  //CALCULATE NUMBER OF ERRORS:
  delay1ms(40);
  int count =0;
  for(int i=0; i<M;i++){
	  for(int j=0; j<P;j++)
		  if(cop[i][j] != c[i][j])
			  count++;
  }
  set_position(0x00);
  clear_display();
  write_string("# of Error: ");
  write_char(count +0x30);
  printf("# of Error: %d \n", count);
  //END NUMBER OF ERRORS
  delay1ms(40);
  //calculate syndrome:
  int syndrome[1][12];
  int syndrome_2[1][12];


  matrixMultiply24_12(c,H,syndrome,1,24); //this works as expected now
  //calculate second syndrome!
  matrixMultiply12_12(syndrome,A,syndrome_2,1,12);
  printf("Syndrome\n");
  print(&syndrome, 1, 12);
  printf("Weight of Syndrome: %d", weight(&syndrome,12));
  int s1_weight = weight(&syndrome,12);
  int s2_weight;
  int correction_pattern[1][24];
  int flag =0;
  for(int i=0;i<24;i++){
	  correction_pattern[0][i] = 0;
  }

  //THE GOLAY DECODING ALGORITHM:
  if (s1_weight <=3) //CASE 1 weight <3
  {
	  printf("\n case 1 \n");
	  for(int i=0; i<12;i++){
		  correction_pattern[0][i] = syndrome[0][i];
	  }
  }
  else
  {	 //check each row in the A matrix
	  for(int j=0; j<12; j++)
	  {
		  int result[1][12];
		  Array_Add(syndrome,A,result,j);
		  if(weight(&result,12)<=2){
			  printf("\n case loop 1 \n");
			  for (int i=0; i<12; i++)
			  {
				  correction_pattern[0][i] = result[0][i];
			  }
			  correction_pattern[0][j+12] = 1;
			  flag = 1;
			  break;
		  }
	  }
	  if((weight(syndrome_2,12)<=3)&&(flag ==0))
	  {
		  printf("\n case 2 \n");
		  for(int i = 12; i<24; i++)
			  correction_pattern[0][i] = syndrome_2[0][i-12];
	  }
	  else if(flag ==0)
	  {			  //check each row in the A matrix again
		  for(int k=0; k<12;k++)
		  {
			  int result[1][12];
			  Array_Add(syndrome_2,A,result,k);
			  if(weight(&result,12)<=2){
				  printf("\n case loop 2 \n");
				  for (int i=12; i<24; i++)
				  {

					  correction_pattern[0][i] = result[0][i-12];
				  }
				  correction_pattern[0][k] = 1;
				  flag = 1;
				  break;
			  }
		  }
	  }
  }
  //CORRECTION CODEWORD = correction_pattern + received_codeword in GF(2)
  int corrected[1][24];
  Array_Add24(correction_pattern,c,corrected,0);
  //printf("\n");
  printf("Corrected Encoded Word:\n");
  print(&corrected,1,24);
  printf("Corrected Codeword:\n");
  print(&corrected,1,12);

  delay1ms(4);
  clear_display();
  set_position(0x40);
  write_string("corrected code");
  delay1ms(4);
  print2D_toLCD(&corrected,M,P-12);

while(1) {
	switch_data = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, switch_data & led_pattern);
	delay = 0;
	while(delay < 200000)
	{
		delay++;
	}
	led_pattern ^= switch_data; // toggle LEDs on selected switches
}
return 0;
}
