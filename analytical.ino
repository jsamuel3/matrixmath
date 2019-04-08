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
  r_tick++; //counts rising edges on right side
}
void tickL(){
  l_tick++; //counts rising edges on left side
}

float getDist(int tickDir){
  /*
   * Distance is arc length,
   * 2* GearRatio is amount of rising edges in 1 rotation
   * ticks are the amount of actual rising edges go by
   * ratio of rising edges to in 1 rotation, times the distance that 1 rotation
   * moves
   */
  return cir*float(tickDir)/float(gearRatio*2);
}

void right(double angle){
  /*
   * circumfrence times angle percentage is arc length
   * if it hasnt moved the proper arc length, keep going
   * (this applies to left)
   */
  float dist = getDist(l_tick);
  while(dist <= cir*((angle/float(2*PI)))){
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

/*
 * this us unneed but may help with robot
 */
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
