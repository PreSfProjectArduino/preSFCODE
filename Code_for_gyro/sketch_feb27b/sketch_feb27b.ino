/***************************************************
  This is an example for the Adafruit Triple-Axis Gyro sensor

  Designed specifically to work with the Adafruit L3GD20 Breakout
  ----> https://www.adafruit.com/products/1032

  These sensors use I2C or SPI to communicate, 2 pins (I2C)
  or 4 pins (SPI) are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Kevin "KTOWN" Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_L3GD20.h>

// Comment this next line to use SPI
//#define USE_I2C

#ifdef USE_I2C
// The default constructor uses I2C
Adafruit_L3GD20 gyro;
#else
// To use SPI, you have to define the pins
#define GYRO_CS 4 // labeled CS
#define GYRO_DO 5 // labeled SA0
#define GYRO_DI 6  // labeled SDA
#define GYRO_CLK 7 // labeled SCL
Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
#endif

int x; int y; int z;
int MoX = 4; int MoY = 6; int MoZ = 10;
//Password and counter of the position in the password array
int moves[120];
int nm = 0;
//Raw data values (x.y.z)
int value[3];
//Predefined avarages for each axis
int Mo[3] = {1, 3, 0};
//Tolerance per axis
int tol[3] = {150, 150, 150};
//Sum of predefined avarage+raw data values
int sumMo[3] = {1, 3, 0};
//How many raw data sets we have
int n = 1;
//If flagMove==0 ->regular mode
//If flagMove==1 ->x axis transient
//If flagMove==2 ->y axis transient
//If flagMove==3 ->z axis transient
int flagMove = 0;
//The maximum difference is used to define the flag number
int MaxDiffer[3] = {0, 0, 0};

void setup()
{
  Serial.begin(9600);
  // Try to initialise and warn if we couldn't detect the chip
  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
    //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
    //if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
}

void loop()
{
  gyro.read();
  value[0] = ((int)gyro.data.x);
  value[1] = ((int)gyro.data.y);
  value[2] = ((int)gyro.data.z);
  //Deciding for each axis if we are in regular mode or in move read mode
  for (int i = 0; i < 3; i++)
  {
    //Regular mode
    if ((abs(value[i] - Mo[i])) <= tol[i])
    {
      n++;
      sumMo[i] += value[i];
      Mo[i] = sumMo[i] / n;
      if (flagMove == i + 1) // gia na stamatisi kai na grapsi tin kinisi
      {
        int temp;
        if (MaxDiffer[i] < 0)
          temp = 1;
        else
          temp = 0;
        nm++;
        moves[nm] = flagMove * 2 - temp;
        Serial.println(moves[nm]);
        flagMove = 0;
      }
    }
    else//Read move mode
    {
      flagMove = 4;
      break;
    }
  }
  if (flagMove == 4)
  {
    for (int i = 0; i < 3; i++)
    {
      MaxDiffer[i] = value[i] - Mo[i];
    }
    int maxim = abs(MaxDiffer[0]);
    int point = 0;
    for (int i = 1; i < 3; i++)
    {
      if (abs(MaxDiffer[i]) > maxim)
      {
        maxim = abs(MaxDiffer[i]);
        point = i;
      }
    }
    flagMove = point + 1;
  }
  delay(120); //Digmatolipsia ton timon
}
















