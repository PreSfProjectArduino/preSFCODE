int readLed=8;
int writeLed=9;
int standbyLed=10;
int pinRead=2;
int pinWrite=3;
int debounce=20;
boolean readState=LOW;
boolean writeState=LOW;
boolean readFlag=0;
boolean writeFlag=0;

void setup() 
{
  pinMode(pinRead,INPUT);
  pinMode(pinWrite,INPUT);
  pinMode(readLed,OUTPUT);
  pinMode(writeLed,OUTPUT);
  pinMode(standbyLed,OUTPUT);
  digitalWrite(readLed,LOW);
  digitalWrite(writeLed,LOW);
  digitalWrite(standbyLed,HIGH);
}

void loop() 
{
  if(!writeFlag)
  {
    readState=digitalRead(pinRead);
    if(readState==HIGH)
    {
      delay(debounce);
      readState=digitalRead(pinRead);
      if(readState==HIGH)
      {
        digitalWrite(standbyLed,LOW);
        digitalWrite(readLed,HIGH);
        while(digitalRead(pinRead==HIGH);
        readFlag=1;
        do
        {
          readState=digitalRead(pinRead);
          if(readState==HIGH)
          {
            delay(debounce);
            readState=digitalRead(pinRead);
            if(readState==HIGH)
            {
              readFlag=0;
              digitalWrite(readLed,LOW);
              digitalWrite(standbyLed,HIGH);
            }
          }
        }while(readFlag);
      }
    }
  }
  if(!readFlag)
  {
    writeState=digitalRead(pinWrite);
    if(writeState==HIGH)
    {
      delay(debounce);
      writeState=digitalRead(pinWrite);
      if(writeState==HIGH)
      {
        digitalWrite(standbyLed,LOW);
        digitalWrite(writeLed,HIGH);
        while(digitalRead(pinWrite==HIGH);
        writeFlag=1;
        do
        {
          writeState=digitalRead(pinWrite);
          if(writeState==HIGH)
          {
            delay(debounce);
            writeState=digitalRead(pinWrite);
            if(writeState==HIGH)
            {
              writeFlag=0;
              digitalWrite(writeLed,LOW);
              digitalWrite(standbyLed,HIGH);
            }
          }
        }while(writeFlag);
      }
    }
  }
}
