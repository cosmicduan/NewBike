#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <time.h>

#define READ 0b10000000
#define WRITE 0b00000000

#define CTRL_REG1_G 0x10
#define CTRL_REG6_XL 0x20

#define OUT_TEMP_L 0x15
#define OUT_TEMP_H 0x16

#define OUT_X_L_G 0x18
#define OUT_X_H_G 0x19
#define OUT_Y_L_G 0x1A
#define OUT_Y_H_G 0x1B
#define OUT_Z_L_G 0x1C
#define OUT_Z_H_G 0x1D

#define STATUS_REG 0x27
#define WHO_AM_I 0x0F

#define SPI_WRITE(REG, DATA) ((((WRITE | REG) << 8) & 0xFF00) | DATA)
#define SPI_READ(REG) (((READ | REG) << 8) & 0xFF00)

unsigned char data[8];

int main()
{
  clock_t start,end;

  wiringPiSetup();
  int i = 0;
  printf("SPI Setup Status: %d\n", wiringPiSPISetupMode(0, 10000000, 3));

  //  *data = SPI_WRITE(CTRL_REG1_G, 4);
  data[0] = WRITE | CTRL_REG1_G;
  data[1] = 0xC0;
  printf("REG:0x%x COM:%x\n", data[0], data[1]);
  wiringPiSPIDataRW(0, data, 2);

  start = clock();
  for(i = 0; ; i++)
    {
      /*
      data[0] = READ | STATUS_REG;
      data[1] = 0;
      printf("%d:\tREG:0x%x COM:%x\t", i++, data[0], data[1]);
      wiringPiSPIDataRW(0, data, 2);
      printf("RT:%x\n", data[1]);
      */

      data[0] = READ | OUT_X_L_G;
      data[1] = 0;
      printf("\tREG:0x%x COM:%x\t", data[0], data[1]);
      wiringPiSPIDataRW(0, data, 2);
      printf("RT:%x\n", data[1]);

      data[0] = READ | OUT_X_H_G;
      data[1] = 0;
      printf("\tREG:0x%x COM:%x\t", data[0], data[1]);
      wiringPiSPIDataRW(0, data, 2);
      printf("RT:%x\n", data[1]);

      delay(200);
    }
  end = clock();
  printf("************** TIME INTERVAL %d COUNTS\n", (end-start));
  printf("%d\n", CLOCKS_PER_SEC);
  return 0;
}
