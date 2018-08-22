#include <SoftwareSerial.h>
#define digital 0
#define analog 1
#define input 2
byte pad[6][3] {//[pad][an/dg/mode]
  { -1, -1, -1},
  {4, A1, input},
  {7, A2, input},
  {8, A3, input},
  {11, A4, input},
  {12, A5, input}
};

//SoftwareSerial RasPi(A4, A5); // RX, TX

String Stroke;
byte counter = 0, dst = 0;
volatile int get_data[255];
unsigned long lastCommand, lastMeasure;
int nextCommand = 0, data = 0, padNum = 0, pin = 0;
char in;
void setup()
{
  Serial.begin(57600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

}

void loop()
{
  while (Serial.available())// Пока есть данные в буфере
  {
    switch (nextCommand)
    {
      case 0:// Если nextCommand == 0, то принимаем первый символ из пакета, означающий, какая команда должна выполниться далее
        in = Serial.read();
        switch (in)
        {
          case '0':
            nextCommand = 5;
            break;
          case '1':
            nextCommand = 6;
            break;
          case '2':
            nextCommand = 7;
            break;
          case '3':
            nextCommand = 8;
            break;
          case '4':
            nextCommand = 9;
            break;
          case '5':
            nextCommand = 10;
            break;
          case '6':
            nextCommand = 11;
            break;
          case 'a':
            nextCommand = 1;
            break;
          case 'b':
            nextCommand = 2;
            break;
          case 'c':
            nextCommand = 3;
            break;
          case 'd':
            nextCommand = 4;
            break;
        }
        break;
      //Если первый символ == a/b/c/d, то принимаем параметр скорости мотора черех функцию getNextData() и вращаем мотор в нужную сторону
      case 1: //первый символ 'a'
        motor(0, getNextData(), 0);
        nextCommand = 0;
        break;
      case 2: //первый символ 'b'
        motor(0, getNextData(), 1);
        nextCommand = 0;
        break;
      case 3: //первый символ 'c'
        motor(1, getNextData(), 0);
        nextCommand = 0;
        break;
      case 4: //первый символ 'd'
        motor(1, getNextData(), 1);
        nextCommand = 0;
        break;
      //Если первый символ == 0/1, то принимаем номер пада на котором находится фонарик и меняем его состояние
      case 5: //flash off /первый символ '0'
        pin = pad[getNextData()][0];
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 0);
        nextCommand = 0;
        break;
      case 6: //flash on /первый символ '1'
        pin = pad[getNextData()][0];
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 1);
        nextCommand = 0;
        break;
      //Если первый символ == 2/3/4/5, то принимаем номер пада на котором находится датчик, узнаем с него значение и отправляем на RasPi
      case 7: //digital sensor /первый символ '2'
        Serial.print(dSensor(getNextData()));
        nextCommand = 0;
        break;
      case 8: //ultrasonic /первый символ '3'
        Serial.print(ultrasonic(getNextData()));
        nextCommand = 0;
        break;
      case 9: //sharp /первый символ '4'
        Serial.print(sharp(getNextData()));
        nextCommand = 0;
        break;
      case 10: //roulette /первый символ '5'
        Serial.print(measure(getNextData()));
        nextCommand = 0;
        break;
      case 11: //analog sensor /первый символ '6'
        Serial.print(aSensor(getNextData()));
        nextCommand = 0;
        break;

    }
  }
}
int getNextData()// Функция приняти параметра
{
  while (true)
  {
    int inChar = Serial.read();
    Stroke += (char)inChar;
    if (inChar == '\n')
    {
      data = atoi(Stroke.c_str());
      Stroke = "";
      return (data);
    }
  }
}
byte sharp(byte padInput)
{
  padInput = pad[padInput][1];
  pinMode(padInput, INPUT);
  return pow(analogRead(padInput), -1.5) * 87700;
}
byte measure(byte padInput)
{
  padInput = pad[padInput][1];
  pinMode(padInput, INPUT);
  return (analogRead(padInput));
}
byte ultrasonic(byte padInput)
{
  padInput = pad[padInput][0];
  if (millis() - lastMeasure > 40)
  {
    pinMode(padInput, OUTPUT);
    digitalWrite(padInput, LOW);
    delayMicroseconds(2);
    digitalWrite(padInput, HIGH);
    delayMicroseconds(10);
    digitalWrite(padInput, LOW);
    pinMode(padInput, INPUT);
    dst = pulseIn(padInput, HIGH) / 58;
    lastMeasure = millis();
  }
  return dst;
}
byte dSensor(byte padInput)
{
  padInput = pad[padInput][1];
  pinMode(padInput, INPUT);
  return digitalRead(padInput);
}
byte aSensor(byte padInput)
{
  padInput = pad[padInput][1];
  pinMode(padInput, INPUT);
  return analogRead(padInput);
}
void motor(bool mNumber, byte speed, bool direction)
{

  if (mNumber)
  {
    if (direction)
    {
      digitalWrite(5, LOW);
      analogWrite(6, speed);
    }
    else
    {
      analogWrite(5, speed);
      digitalWrite(6, LOW);
    }
  }
  else
  {
    if (direction)
    {
      digitalWrite(9, LOW);
      analogWrite(10, speed);
    }
    else
    {
      analogWrite(9, speed);
      digitalWrite(10, LOW);
    }
  }
}
/*
  void Data()
  {
  for (int k = 0; k < 255; k++)
  {
    get_data[k] = -1;
  }
  while (RasPi.available())
  {
    int inChar = RasPi.read();
    Stroke += (char)inChar;
    if (inChar == '?')
    {
      counter = 0;
      for (int k = 1; k < 20; k++)
      {
        Serial.print(get_data[k]);
        Serial.print(" ");
      }
      Serial.println();
    }
    else if (inChar == '\n')
    {
      get_data[counter] = atoi(Stroke.c_str());
      counter ++;
      Stroke = "";
      //Serial.println(Stroke);
    }

  }
  }*/
/*void Get_Marker()
  {
  for (int k = 0; k < 255; k++)
  {
    get_data[k] = -1;
  }
  while(RasPi.available())
  {
    int inChar = RasPi.read();
    Stroke += (char)inChar;
    if (inChar == '\n')
    {
      char input[255];
      byte sn = 0;
      for (int j = 0; j < Stroke.length(); j++)
      {
        input[j] = Stroke[j];
      }
      Stroke = "";
      int i = 0;
      while (input[i] && input[i] != '\n')
      {
        if (input[i] == ',')
        {
          i++;
          String oper_save;
          while (input[i] && input[i] != ',')
          {
            //Serial.print(input[i]);
            oper_save += input[i];
            i++;
          }
          get_data[sn] = atoi(oper_save.c_str());
          sn++;
        }
        i++;
      }
      for (int k = sn; k < 255; k++)
      {
        get_data[k] = -1;
      }
      //Вывод данных в монитор
      for (int k = 0; k < 20; k++)
      {
        Serial.print(get_data[k]);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
  }*/
