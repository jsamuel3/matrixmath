#define distPinL 3
#define distPinR 3
#define drivePinR 6
#define drivePinL 9

#define baseLine 5
#define wheelRad 2
#define gearRatio 75

float cir = 2*PI*wheelRad;
float tickDist = wheelRad * deg2rad( 90 / gearRatio );
float zTheta = 0, _zTheta = tickDist/baseLine;

float x = 0, _x = ( baseLine / 2 ) * sin ( _zTheta ), _xdiff;
float y = 0, _y = ( baseLine / 2 ) * ( 1 - cos ( _zTheta ) ), _ydiff;


Matrix<4,4> rotateR = {
  cos(_zTheta),-sin(_zTheta),0,0,
  sin(_zTheta),cos(_zTheta),0,baseLine/2,
  0,0,1,0,
  0,0,0,1
};
Matrix<4,4> rotateL = {
  cos(-_zTheta),-sin(-_zTheta),0,0,
  sin(-_zTheta),cos(-_zTheta),0,-baseLine/2,
  0,0,0,0,
  0,0,0,1
};
Matrix<4,4> transR = {
  1,0,0,0,
  0,1,0,-baseLine,
  0,0,1,0,
  0,0,0,1
};
Matrix<4,4> transL = {
  1,0,0,0,
  0,1,0,baseLine,
  0,0,1,0,
  0,0,0,1
};

Matrix<4,4> trxR = rotateR*transR;
Matrix<4,4> trxL = rotateL*transL;

Matrix<4,4> ident = {
  1,0,0,0,
  0,1,0,0,
  0,0,1,0,
  0,0,0,1
};

void rtick()
{ 
  ident = ident * trxR;
}

void ltick()
{ 
  ident = ident * trxL;
}

void setup() {
  Serial.begin(9600);
  pinMode(drivePinR, OUTPUT);
  pinMode(drivePinL, OUTPUT);
  pinMode(revPinR, OUTPUT);
  pinMode(revPinL, OUTPUT);
  pinMode(distPinL, INPUT_PULLUP);
  pinMode(distPinR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(distPinL), rtick, CHANGE);
  attachInterrupt(digitalPinToInterrupt(distPinR), ltick, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:

}
