//Initialize Digital Pins
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

const int motorTimeSlice = 2000;

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
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);

  delay(motorTimeSlice);
}

void goForward() {
  // run forward
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);

//  Serial.println("forward");
  delay(motorTimeSlice);  
}

void goBackward() {  
  // run backward
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,HIGH);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,HIGH);

  Serial.println("backward");
  delay(motorTimeSlice);
}

void turnRight() {
  // run right
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);

  Serial.println("right");
  delay(motorTimeSlice);
  
}

void turnLeft() {
  // run left
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);

  Serial.println("left");
  delay(motorTimeSlice);
}

void loop() {
  // put your main code here, to run repeatedly:

  ls = digitalRead(left);
  ts = digitalRead(top);
  rs = digitalRead(right);

  if(ls == 0){
    turnRight();
  }
  else if(rs == 0){
    turnRight();
  }
  else if(ts == 0){
    goBackward();

    turnLeft();
  }
  else{
    goForward();
  }

}
