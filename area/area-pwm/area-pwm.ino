//Initialize Digital Pins
const int MOTOR_ON = 1000;

const int leftForward = 5;
const int leftBackward = 4;
const int rightForward = 0;
const int rightBackward = 2;

const int left = 14;
const int top = 12;
const int right = 13;

int ls = 0;
int ts = 0;
int rs = 0;

int prevDirection = 0;
const int LEFT = 0;
const int RIGHT = 1;

const int motorTimeSlice = 1000;
const int rotationTimeSlice = 1300;
const int LOOP_TIME_SLICE = 500;

void setup() {
  // set motor pins as Output
  pinMode(leftForward,OUTPUT);
  pinMode(leftBackward,OUTPUT);
  pinMode(rightForward,OUTPUT);
  pinMode(rightBackward,OUTPUT);


  // sensor control pin as input
  pinMode(left,INPUT);
  pinMode(top,INPUT);
  pinMode(right,INPUT);

  Serial.begin(9600);
}

void stopp() {
  analogWrite(leftForward,0);
  analogWrite(leftBackward,0);
  analogWrite(rightForward,0);
  analogWrite(rightBackward,0);

  delay(motorTimeSlice);
}

void goForward() {
  // run forward
  analogWrite(leftForward,MOTOR_ON);
  analogWrite(leftBackward,0);
  analogWrite(rightForward,MOTOR_ON);
  analogWrite(rightBackward,0);

//  Serial.println("forward");
//  delay(motorTimeSlice);  
}

void goBackward() {  
  // run backward
  analogWrite(leftForward,0);
  analogWrite(leftBackward,MOTOR_ON);
  analogWrite(rightForward,0);
  analogWrite(rightBackward,MOTOR_ON);

  Serial.println("backward");
  delay(motorTimeSlice);
}

void turnRight() {
  // run right
  analogWrite(leftForward,MOTOR_ON);
  analogWrite(leftBackward,0);
  analogWrite(rightForward,0);
  analogWrite(rightBackward,0);

  Serial.println("right");
  delay(rotationTimeSlice);
  
}

void turnLeft() {
  // run left
  analogWrite(leftForward,0);
  analogWrite(leftBackward,0);
  analogWrite(rightForward,MOTOR_ON);
  analogWrite(rightBackward,0);

  Serial.println("left");
  delay(rotationTimeSlice);
}

void loop() {
  // put your main code here, to run repeatedly:

  ls = digitalRead(left);
  ts = digitalRead(top);
  rs = digitalRead(right);

  Serial.print(ls);
  Serial.print(" -- ");
  Serial.print(ts);
  Serial.print(" -- ");
  Serial.println(rs);

  
  if(ls == 0){
    goBackward();
    
    turnRight();
    prevDirection = RIGHT;
  }
  else if(rs == 0){
    goBackward();
    
    turnLeft();
    prevDirection = LEFT;
  }
  else if(ts == 0){
    goBackward();
    goBackward();
    if(prevDirection == LEFT)
      turnLeft();
    else
      turnRight();
  }
  else{
    goForward();
  }

  
  delay(LOOP_TIME_SLICE);

}
