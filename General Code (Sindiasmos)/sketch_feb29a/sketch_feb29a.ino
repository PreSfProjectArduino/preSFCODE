//===========Button Variable=======
int table[2] = {0, 0}; // Dixni tis katastasi ton buttons 0->Learn 1->Read
bool state = 0; // Flag gia ta buttons
//===========Button Variable=======

//===========Gyro Variable===========
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
//int moves[120];
//int nm = 0;
int moves[3]={4,3,6};
int nm=3;
//Raw data values (x.y.z)
int value[3];
//Predefined avarages for each axis
int Mo[3] = {4, 6, 10};
//Tolerance per axis
int tol[3] = {110, 110, 110};
//Sum of predefined avarage+raw data values
int sumMo[3] = {4, 6, 10};
//How many raw data sets we have
int n = 1;
//If flagMove==0 ->regular mode
//If flagMove==1 ->x axis transient
//If flagMove==2 ->y axis transient
//If flagMove==3 ->z axis transient
int flagMove = 0;
//The maximum difference is used to define the flag number
int MaxDiffer[3] = {0, 0, 0};

int Error = 0; // Possa error exoun gini
int MaxError = 3; // Ara Epitrepete ena error
int CountNM = 0;
int Timi;
//===========Gyro Variable===========

void setup()
{
  //=======Buttons=========
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  //=======Buttons=========

  //======Gyro============s
  Serial.begin(9600);
  // Try to initialise and warn if we couldn't detect the chip
  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
    //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
    //if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
  //======Gyro============

  Serial.begin(9600);
}



void loop()
{
  for (int loop = 12; loop >= 11; loop--)
  {
    //Serial.println(digitalRead(loop));
    if (digitalRead(loop) == LOW)
    {

      while (state == 0)
      {
        if (digitalRead(loop) == HIGH)
        {
          table[12 - loop]++; // Tha pigeni eos to 2 kai apo alo meros tha epistrefi sto 0 kateftian
          state = 1;
          //Debug();
        }

      }
      delayMicroseconds(1500);
      state = 0;
    }
  }
  /*Serial.print(table[0]);
  Serial.print("  ");
  Serial.println(table[1]);*/
  if (table[0] == 1) // Edo tha bi o algorithmos ekmathisis Kidika
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
          Serial.print("First ");
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
    delay(80); //Digmatolipsia ton timon

  }
  else if (table[1] == 1) // Edo tha bi o algorithmos gia ton elenxo an einai sostos o kodikas pou topothetithike
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
        //Serial.println(value[i]);
        n++;
        sumMo[i] += value[i];
        Mo[i] = sumMo[i] / n;
        if (flagMove == i + 1) // gia na stamatisi kai na grapsi tin kinisi
        {

          //Serial.println(flagMove);
          int temp;
          if (MaxDiffer[i] < 0)
            temp = 1;
          else
            temp = 0;

          Timi = flagMove * 2 - temp;
          Serial.print("Second ");
          Serial.println(Timi);

          CountNM = CountNM + 1;
          if (moves[CountNM] != Timi)
            Error = Error + 1; // if Error==MaxError+1
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
    delay(80); //Digmatolipsia ton timon
  }

  if (table[0] == 2)
  {
    /*Serial.println();
      for (int i=1;i<=nm;i++) // DEBUG
      Serial.println(moves[i]);*/

    table[0] = 0; // To xanaepistrefi gia xrisi
    flagMove = 0;
  }
  if (table[1] == 2)
  {
    if (Error <= MaxError) // Tote bori na kani kati Alios aporiptete
    {
      /*for (int i = 1; i <= nm; i++) // DEBUG
        Serial.println(moves[i]);*/
        //Serial.println("Login sucesfull");
        Serial.println("#S|CODEBANK|[sfhmmy]#");
        Serial.println("#S|CODEBANK|[sfhmmy]#");
    }
    table[1] = 0; // To xanaepistrefi gia xrisi
    flagMove = 0;
  }

  delay(10);
}

/*void Debug()
  {
  for (int loop1 = 0; loop1 <= 1; loop1++)
  {
    Serial.print(" ");Serial.print(table[loop1]);Serial.print(" ");
  }
  Serial.println("");
  }*/







