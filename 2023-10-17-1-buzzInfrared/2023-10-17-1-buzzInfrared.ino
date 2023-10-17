int buzzPin=16;
int inPin=17;
int val;

void setup() 
{
  pinMode(buzzPin,OUTPUT);
  pinMode(inPin,INPUT);

}

void loop() {
  val=digitalRead(inPin);
  if(val==HIGH){
    digitalWrite(buzzPin,HIGH);
  }
  else{
    digitalWrite(buzzPin,LOW);
  }
}
