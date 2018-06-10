//Initialize Digital Pins
const int leftForward = 5;
const int leftBackward = 4;
const int rightForward = 0;
const int rightBackward = 2;


const int timeSlice = 2000;

void setup() {
  // set control pins as Output
  pinMode(leftForward,OUTPUT);
  pinMode(leftBackward,OUTPUT);
  pinMode(rightForward,OUTPUT);
  pinMode(rightBackward,OUTPUT);

}

void stopp() {
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);

  delay(timeSlice);
}

void forward() {
  // run forward
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);

//  Serial.println("forward");
  delay(timeSlice);  
}

void backward() {  
  // run backward
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,HIGH);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,HIGH);

  Serial.println("backward");
  delay(timeSlice);
}

void right() {
  // run right
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);

  Serial.println("right");
  delay(timeSlice);
  
}

void left() {
  // run left
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);

  Serial.println("left");
  delay(timeSlice);
}

void loop() {

  right();

  stopp();

  forward();

  stopp();
  
  left();

  stopp();

}


