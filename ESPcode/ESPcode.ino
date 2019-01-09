#include <ESP8266WiFi.h>
#include <Blynk.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "671d4c96e49b4705be3eb8f8d81c649c";
char ssid[] = "START_UP_CAMPUS";
char pass[] = "";

int tcount=0, tcount1=0;
int countA=0, temp=0, loop1=0, temp1=0;

int fullval=5;
int blycompress=0, compress=16;
int blyemit=0, emit=4;

BLYNK_WRITE(V1){
  blyemit=param.asInt();
}
BLYNK_WRITE(V0){
  blycompress=param.asInt();
}
void setup() {
  pinMode(compress, OUTPUT);
  pinMode(fullval, INPUT);
  pinMode(emit, OUTPUT);

  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  delay(10);

  //  Serial.println();
  //  Serial.println();
  //  Serial.print("Connecting to ");
  //  Serial.println(ssid);
  //
  //  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //Blynk Service Connection
  while(Blynk.connect() == false){
    tcount=millis()/1000;
    if(tcount>tcount1){
      Serial.println("Blynk Not Connected");
    }
    tcount1=tcount;
  }
}

void loop() {
  Blynk.run();

  tcount=millis()/100;
  if((tcount*10)>tcount1){
    countA++;
    Serial.println(countA);
    fullval=digitalRead(5);
    if(fullval==HIGH)
      Blynk.notify("Trash Can is Full!");
  }

  //
  //    if((blycompress==1)||(loop1==1)){
  //      if(temp1==0){
  //        temp1=1;
  //        temp=tcount; }
  //        
  //      loop1 = (temp++>=tcount)?(1):(0);
  //      Serial.println("blycompress");
  //      digitalWrite(compress, HIGH);
  //    }
  //    digitalWrite(compress, LOW);
  //    loop1=0;
  //    temp1=0;
  if(blycompress==1){
    Serial.println("blycompress==1");
    digitalWrite(compress, HIGH);
  }
  else
    digitalWrite(compress, LOW);

  //
  //    if((blyemit==1)||(loop1==1)){
  //      if(temp1==0){
  //        temp1=1;
  //        temp=tcount; }
  //
  //        loop1 = (temp++>=tcount)?(1):(0);
  //        digitalWrite(emit, HIGH);
  //        Serial.println("blyemit");
  //      }
  //      digitalWrite(emit, LOW);
  //      loop1=0;
  //      temp1=0;

  if(blyemit==1){
    Serial.println("blyemit==1");
    digitalWrite(emit, HIGH);
  }
  else
    digitalWrite(emit, LOW);

  tcount1=tcount;
}

//D0 = send.Compress -- 18.openCM -- D5.blynk
//D1 = receive.fullvalue -- 22.openCM
//D2 = send.Emit -- 20.openCM -- D7.blynk

