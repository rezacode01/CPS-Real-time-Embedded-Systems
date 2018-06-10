const int left = 14;
const int top = 12;
const int right = 13;

int l = 0;
int t = 0;
int r = 0;

const int timeSlice = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(left,INPUT);
  pinMode(top,INPUT);
  pinMode(right,INPUT);

  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  l = digitalRead(left);
  t = digitalRead(top);
  r = digitalRead(right);

  Serial.print(l);
  Serial.print(" -- ");
  Serial.print(t);
  Serial.print(" -- ");
  Serial.println(r);
  
  delay(timeSlice);
}
