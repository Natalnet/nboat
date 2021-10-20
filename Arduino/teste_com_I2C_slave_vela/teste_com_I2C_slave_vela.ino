#include<Wire.h>
#define led 13

volatile byte x1, x2;
int y1, y2, y3;
bool flag1 = false;

void setup()
{
  Wire.begin(10);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop()
{
  if (flag1 == true)
  {
    Serial.print("Recived a: ");
    Serial.println(y1, DEC);        //Serial Monitor shows: 300
    //-------------------------
    Serial.print("Recived b: ");
    Serial.println(y2, DEC);
    //-------------------------
    Serial.print("Recived c: ");
    Serial.println(y3, DEC);
    //-------------------------
    flag1 = false;   //reday for next cycle
  }
}

void receiveEvent(int howMany)
{
  x1 = Wire.read();  //x1 hilds upper byte of received a
  x2 = Wire.read();  //x2 holds lower byte of received a
  y1 = (int)x1 << 8 | (int)x2;
  //------------------------
  x1 = Wire.read();  //x1 hilds upper byte of received b
  x2 = Wire.read();  //x2 holds lower byte of received b
  y2 = (int)x1 << 8 | (int)x2;
  //---------------------------
  x1 = Wire.read();  //x1 hilds upper byte of received b
  x2 = Wire.read();  //x2 holds lower byte of received b
  y3 = (int)x1 << 8 | (int)x2;
  //---------------------------
  flag1 = true; //to indicate recevieEvent() handler is visited; do all print in loop()
}
