#include <MPU6050_tockn.h>//библиотека для датчика MPU6050 https://github.com/tockn/MPU6050_tockn //librory for sensor MPU6050 https://github.com/tockn/MPU6050_tockn
#include <Wire.h>

MPU6050 mpu6050(Wire);
float ugol;//переменая для значений с датчика по оси Z //variable for writing values from sensor along the axis Z
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
}

void loop() {

  mpu6050.update();//для улучшения функциональности программы //for improvement the functionality of the progrom
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
  for (int i = 0; i <= 100000000000; i++)
  {
    mpu6050.update();
    ugol=mpu6050.getAngleZ();//присвоения значений переменой 'ugol'// assigning values variable 'ugol'
    analogWrite(5, 100);//включения моторов //motor starters
    Serial.print("\tangleZ : ");
    Serial.println(mpu6050.getAngleZ());//запись значений с датчика на монитор порта//write values from the sensor to the monetor porta 
    if (ugol < 0)//условия //conditions
    {
      while (ugol <= 0)
      {
        analogWrite(9, 0);
        mpu6050.update();
        Serial.print("\tangleZ : ");
        Serial.println(mpu6050.getAngleZ());
        mpu6050.update();
        ugol=mpu6050.getAngleZ();//присвоения значений переменой//assigning values variable
      }
    }
    analogWrite(5, 100);
    analogWrite(9, 100);
    mpu6050.update();
    ugol=mpu6050.getAngleZ();
    if (ugol > 0)
    {
      while (ugol >= 0)
      {
        mpu6050.update();
        Serial.print("\tangleZ : ");
        Serial.println(mpu6050.getAngleZ());
        analogWrite(5, 0);
        mpu6050.update();
        ugol=mpu6050.getAngleZ();
      }
    }

    Serial.println();
  }
}
