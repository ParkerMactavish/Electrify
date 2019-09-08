#define pOut0 2
#define pOut1 3
#define pLed 13
#define pResCon0 4
#define pResCon1 5
#define pResCon2 6
#define pResCon3 7
#define sInit 0
#define sRead 1
#define sOutput 2
#define mHigh 0xff
#define mLow  0x11

int Frequency = 0;
int delayTimeHighinuS = 0;
long int delayTimeLowinuS = 0;
int delayTimeLowinmS = 0;
int Voltage = 0;
int HitTime = 0;
int State = sInit;
int sResCon0 = 0;
int sResCon1 = 0;
int sResCon2 = 0;
int sResCon3 = 0;

////    1 1 1 0 13.0
////    1 1 0 1 14.9
////    1 1 0 0 17.5
////    1 0 1 1 20.1
////    1 0 1 0 22.6
////    1 0 0 0 27.1
////    0 1 1 1 37.1
////    0 0 0 0 53.8
void set_Res(int stage){
  switch(stage){
    case 1:
      digitalWrite(pResCon0, LOW);
      digitalWrite(pResCon1, LOW);
      digitalWrite(pResCon2, LOW);
      digitalWrite(pResCon3, LOW);      
    break;
    case 2:
      digitalWrite(pResCon0, LOW);
      digitalWrite(pResCon1, HIGH);
      digitalWrite(pResCon2, HIGH);
      digitalWrite(pResCon3, HIGH);
    break;
    case 3:
      digitalWrite(pResCon0, HIGH);
      digitalWrite(pResCon1, LOW);
      digitalWrite(pResCon2, LOW);
      digitalWrite(pResCon3, LOW);
    break;
    case 4:
      digitalWrite(pResCon0, HIGH);
      digitalWrite(pResCon1, LOW);
      digitalWrite(pResCon2, HIGH);
      digitalWrite(pResCon3, LOW);
    break;
    case 5:
      digitalWrite(pResCon0, HIGH);
      digitalWrite(pResCon1, LOW);
      digitalWrite(pResCon2, HIGH);
      digitalWrite(pResCon3, HIGH);
    break;
    case 6:
      digitalWrite(pResCon0, HIGH);
      digitalWrite(pResCon1, HIGH);
      digitalWrite(pResCon2, LOW);
      digitalWrite(pResCon3, LOW);
    break;
    case 7:
      digitalWrite(pResCon0, HIGH);
      digitalWrite(pResCon1, HIGH);
      digitalWrite(pResCon2, LOW);
      digitalWrite(pResCon3, HIGH);
    break;
    case 8:
      digitalWrite(pResCon0, HIGH);
      digitalWrite(pResCon1, HIGH);
      digitalWrite(pResCon2, HIGH);
      digitalWrite(pResCon3, LOW);
    break;
    default:
      HitTime = 0;
      digitalWrite(pResCon0, LOW);
      digitalWrite(pResCon1, LOW);
      digitalWrite(pResCon2, LOW);
      digitalWrite(pResCon3, LOW);      
    break;
  }
}

int read_Int(){
  int retVal = 0;
  while(Serial.peek() != -1 && Serial.peek() != ' ' && Serial.peek() != '\n'){
    retVal*=10;
    retVal += Serial.read() - '0';
    Serial.println(retVal);
  }
  Serial.read();
  Serial.println();
  return retVal;
}

void electrify(int mode){
  if(mode == mHigh){
    digitalWrite(pOut0, HIGH);
  }
  else{
    digitalWrite(pOut1, HIGH);
  }
  delayMicroseconds(delayTimeHighinuS);
  if(mode == mHigh){
    digitalWrite(pOut0, LOW);
  }
  else{
    digitalWrite(pOut1, LOW);
  }
  delay(delayTimeLowinmS);
  delayMicroseconds(delayTimeLowinuS);
}

void setup() {
  pinMode(pOut0, OUTPUT);
  pinMode(pOut1, OUTPUT);
  digitalWrite(pOut0, LOW);
  digitalWrite(pOut1, LOW);
  pinMode(pResCon0, OUTPUT);
  pinMode(pResCon1, OUTPUT);
  pinMode(pResCon2, OUTPUT);
  pinMode(pResCon3, OUTPUT);
  digitalWrite(pResCon0, LOW);
  digitalWrite(pResCon1, LOW);
  digitalWrite(pResCon2, LOW);
  digitalWrite(pResCon3, LOW);
  
  Serial.begin(9600);
  State = sRead;
}

void loop() {
  switch(State){
    case sInit:
      break;
    case sRead:
      if(Serial.peek()>-1){
        Frequency = read_Int();
        delayTimeHighinuS = 100;
        delayTimeLowinuS = (long int)(1000000.0/Frequency)-delayTimeHighinuS;
        delayTimeLowinmS = delayTimeLowinuS/16383;
        Voltage = read_Int();
        HitTime = read_Int();
        set_Res(Voltage);
        Serial.read();
        Serial.print(Serial.peek());
        State = sOutput;
      }
      Serial.println();
      Serial.println(delayTimeLowinuS);
      Serial.println(Voltage);
      Serial.println(HitTime);
      break;
    case sOutput:
      for(int i = 0; i < HitTime && Serial.peek() == -1; i++){
        electrify(mHigh);
      }
      if(Serial.peek()>-1){
        State = sRead;
        delay(10);
        break;
      }
      for(int i = 0; i < HitTime && Serial.peek() == -1; i++){
        electrify(mLow);
      }
      if(Serial.peek()>-1){
        State = sRead;
        delay(10);
        break;
      }
      break;
  }
}
//void loop(){
//  if(Serial.peek()!=-1){
//    delay(10);
//    sResCon0 = Serial.read()-'0';
//    if(sResCon0) digitalWrite(pResCon0, HIGH);
//    else digitalWrite(pResCon0, LOW);
//    Serial.read();
//    
//    sResCon1 = Serial.read()-'0';
//    if(sResCon1) digitalWrite(pResCon1, HIGH);
//    else digitalWrite(pResCon1, LOW);
//    Serial.read();
//    
//    sResCon2 = Serial.read()-'0';
//    if(sResCon2) digitalWrite(pResCon2, HIGH);
//    else digitalWrite(pResCon2, LOW);
//    Serial.read();
//    
//    sResCon3 = Serial.read()-'0';
//    if(sResCon3) digitalWrite(pResCon3, HIGH);
//    else digitalWrite(pResCon3, LOW);
//    Serial.read();
//
//    Serial.print(sResCon0);
//    Serial.print(sResCon1);
//    Serial.print(sResCon2);
//    Serial.print(sResCon3);
//
////    1 1 1 0 13.0
////    1 1 0 1 14.9
////    1 1 0 0 17.5
////    1 0 1 1 20.1
////    1 0 1 0 22.6
////    1 0 0 0 27.1
////    0 1 1 1 37.1
////    0 0 0 0 53.8
////    
//    1 0 1 1 20.1
//  }
//}
