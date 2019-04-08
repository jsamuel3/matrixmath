#define distPinL 3
#define distPinR 3
#define drivePinR 6
#define drivePinL 9

#define baseLine 5
#define wheelRad 2
#define gearRatio 75

float cir = 2*PI*wheelRad;
int r_tick = 0;
int l_tick = 0;

void tickR(){
  r_tick++;
}
void tickL(){
  l_tick++;
}

float getDist(int tickDir){
  return cir*float(gearRatio*2)/float(tickDir);
}

void right(double angle){
  float dist = getDist(l_tick);
  while(dist <= cir/((angle/float(2*PI)))){
    analogWrite(drivePinL, 255);
  }
  l_tick = 0;
  analogWrite(drivePinL, 0);
}

void left(double angle){
  float dist = getDist(r_tick);
  while(dist <= cir/((angle/float(2*PI)))){
    analogWrite(drivePinR, 255);
  }
  r_tick = 0;
  analogWrite(drivePinR, 0);
  
}

void straight(double driveDist){
  float dist = getDist(l_tick);
  while(dist <= driveDist){
    analogWrite(drivePinL, 255);
    analogWrite(drivePinR, 255);
  }
  l_tick = 0;
  analogWrite(drivePinL, 0);
  analogWrite(drivePinR, 0);
}


void setup() {
  Serial.begin(9600);
  pinMode(drivePinR, OUTPUT);
  pinMode(drivePinL, OUTPUT);
  pinMode(revPinR, OUTPUT);
  pinMode(revPinL, OUTPUT);
  pinMode(distPinL, INPUT_PULLUP);
  pinMode(distPinR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(distPinL), tickR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(distPinR), tickL, CHANGE);
}

void loop() {
  
  // put your main code here, to run repeatedly:

}
