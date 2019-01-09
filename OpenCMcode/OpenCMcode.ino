/* Control table defines */
#define MOVING 46
#include <OLLO.h>
OLLO myOLLO;


Dynamixel Dxl(1);

  

byte isMoving = 0;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int a2 = 0;
int b2 = 0;
int c2 = 0;
int d2 = 0;
int x=0;
int goalPosition = 0;
int tcount=0, tcount1=0;
const long interval = 2000;

void press(){
  while(1){
    unsigned long startTime = millis();

    while(1){
      Dxl.writeWord(1,32,1023);
      Dxl.writeWord(2,32,2047);
      Dxl.writeWord(3,32,1023);
      Dxl.writeWord(4,32,2047);
      //          press();
      unsigned long curMillis = millis();
      if(curMillis - startTime >= interval){
        Dxl.writeWord(1,32,0);
        Dxl.writeWord(2,32,0);
        Dxl.writeWord(3,32,0);
        Dxl.writeWord(4,32,0);
        //          break;
        loop();
      }
    }
  }
}
void setup() {
  // Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  Dxl.wheelMode(1);
  Dxl.wheelMode(2);
  Dxl.wheelMode(3);
  Dxl.wheelMode(4);
  myOLLO.begin(1, IR_SENSOR);
  pinMode(18, INPUT);
  pinMode(20, INPUT);
  pinMode(22, OUTPUT);

}

void loop() {


  isMoving = Dxl.readByte(1, MOVING);
  Dxl.writeWord(1,32,400);
  Dxl.writeWord(2,32,1423);
  Dxl.writeWord(3,32,1423);
  Dxl.writeWord(4,32,400);

  a=Dxl.readWord(1, 36);
  b=Dxl.readWord(2, 36);
  c=Dxl.readWord(3, 36);
  d=Dxl.readWord(4, 36);
  delay (300);
  a2=Dxl.readWord(1, 36);
  b2=Dxl.readWord(2, 36);
  c2=Dxl.readWord(3, 36);
  d2=Dxl.readWord(4, 36);
  delay(300);
  //  while(1){

  if(((a2!=1023)&&(a!=1023)&&(a2!=0)&&(a!=0)&&(a2==a))||((b2!=1023)&&(b!=1023)&&(b2!=0)&&(b!=0)&&(b2==b))||((c2!=1023)&&(c!=1023)&&(c2!=0)&&(c!=0)&&(c2==c))||((d2!=1023)&&(d!=1023)&&(d2!=0)&&(d!=0)&&(d2==d)))
  {
    SerialUSB.println("a");
    up();
  }
  else{
    SerialUSB.println("b");
  }
}

void up() {
  while(1){

    Dxl.writeWord(1,32,1273);
    Dxl.writeWord(2,32,250);
    Dxl.writeWord(3,32,250);
    Dxl.writeWord(4,32,1273);
    a=Dxl.readWord(1, 36);
    b=Dxl.readWord(2, 36);
    c=Dxl.readWord(3, 36);
    d=Dxl.readWord(4, 36);
    delay (500);
    a2=Dxl.readWord(1, 36);
    b2=Dxl.readWord(2, 36);
    c2=Dxl.readWord(3, 36);
    d2=Dxl.readWord(4, 36);


    if(((a2!=1023)&&(a!=1023)&&(a2!=0)&&(a!=0)&&(a2==a))||((b2!=1023)&&(b!=1023)&&(b2!=0)&&(b!=0)&&(b2==b))||((c2!=1023)&&(c!=1023)&&(c2!=0)&&(c!=0)&&(c2==c))||((d2!=1023)&&(d!=1023)&&(d2!=0)&&(d!=0)&&(d2==d))){
      SerialUSB.println("stop\n");
      stop();
    }
    // if(x==1){
    //    x=0;
    //    loop();
    //  }
  }
}


void stop(){

  Dxl.writeWord(1,32,0);
  Dxl.writeWord(2,32,0);
  Dxl.writeWord(3,32,0);
  Dxl.writeWord(4,32,0);
  while(1){
    int value=myOLLO.read(1, IR_SENSOR);
    SerialUSB.println(value);
    //    if(value>=900){
    //      unsigned long curMillis = millis();
    //      unsigned long preMillis = 0;
    //      if(curMillis - preMillis >= interval){ 
    //        preMillis = curMillis;
    //        press();
    //      }
    //      break;
    //    }

    if(value>=800){
      unsigned long startTime = millis();
      digitalWrite(22, HIGH);
      while(1){
        Dxl.writeWord(1,32,500);
        Dxl.writeWord(2,32,1524);
        Dxl.writeWord(3,32,1524);
        Dxl.writeWord(4,32,500);
        //          press();
        unsigned long curMillis = millis();
        if(curMillis - startTime >= interval){
          Dxl.writeWord(1,32,0);
          Dxl.writeWord(2,32,0);
          Dxl.writeWord(3,32,0);
          Dxl.writeWord(4,32,0);
          //          break;
          loop();
        }
      }
      //      loop();
    }
    else if(digitalRead(18) == HIGH){ 
      SerialUSB.println("Do Press");
      loop();
    }
    else if(digitalRead(20) == HIGH){
      SerialUSB.println("Do Detach");
      press();
    }

  }
  loop();
}








