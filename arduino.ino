#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1);

int M1_FWD = 2;
int M1_BWD = 3;

int M2_FWD = 4;
int M2_BWD = 5;

unsigned long lastCommandTime = 0;
const unsigned long commandTimeout = 100;

void setup()
{
  pinMode(M1_FWD, OUTPUT);
  pinMode(M1_BWD, OUTPUT);
  pinMode(M2_FWD, OUTPUT);
  pinMode(M2_BWD, OUTPUT);

  BT.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if (BT.available())
  {
    char command = BT.read();
    Serial.println(command);
    lastCommandTime = millis();

    if (command == 'W' || command == 'w')
    {
      moveForward();
    }
    else if (command == 'S' || command == 's')
    {
      moveBackward();
    }
    else if (command == 'F' || command == 'f')
    {
      stopMotors();
    }
    else if (command == 'D' || command == 'd')
    {
      turnRight();
    }
    else if (command == 'A' || command == 'a')
    {
      turnLeft();
    }
  }

  if (millis() - lastCommandTime > commandTimeout)
  {
    stopMotors();
  }
}

void moveForward()
{
  digitalWrite(M1_FWD, HIGH);
  digitalWrite(M1_BWD, LOW);
  digitalWrite(M2_FWD, HIGH);
  digitalWrite(M2_BWD, LOW);
}

void moveBackward()
{
  digitalWrite(M1_FWD, LOW);
  digitalWrite(M1_BWD, HIGH);
  digitalWrite(M2_FWD, LOW);
  digitalWrite(M2_BWD, HIGH);
}

void stopMotors()
{
  digitalWrite(M1_FWD, LOW);
  digitalWrite(M1_BWD, LOW);
  digitalWrite(M2_FWD, LOW);
  digitalWrite(M2_BWD, LOW);
}

void turnRight()
{
  digitalWrite(M1_FWD, HIGH);
  digitalWrite(M1_BWD, LOW);
  digitalWrite(M2_FWD, LOW);
  digitalWrite(M2_BWD, HIGH);
}

void turnLeft()
{
  digitalWrite(M1_FWD, LOW);
  digitalWrite(M1_BWD, HIGH);
  digitalWrite(M2_FWD, HIGH);
  digitalWrite(M2_BWD, LOW);
}