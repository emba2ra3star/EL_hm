int buzzpin=15;
int inpin=16;
int val;
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzpin,OUTPUT);
  pinMode(inpin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val=digitalRead(inpin);
  Serial.println(val);
  if(val==0){
    digitalWrite(buzzpin,0);
  }
  else{
    digitalWrite(buzzpin,1);
  }
}
