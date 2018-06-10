//Initialize Digital Pins
const int leftForward = 5;
const int leftBackward = 4;
const int rightForward = 0;
const int rightBackward = 2;

void setup() {
  // set control pins as Output
  pinMode(leftForward,OUTPUT);
  pinMode(leftBackward,OUTPUT);
  pinMode(rightForward,OUTPUT);
  pinMode(rightBackward,OUTPUT);

  Serial.println("HELLO");

}

void loop() {
  // run forward
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);

  Serial.println("forward");
  delay(5000);

  // run left
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);

  Serial.println("left");
  delay(5000);
  
  // run right
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);

  Serial.println("right");
  delay(5000);
  
  // run backward
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,HIGH);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,HIGH);

  Serial.println("backward");
  delay(5000);

}
