//created by: Ramneet Kaur
 char x;
 int led=false;
 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

 pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  
 // put your main code here, to run repeatedly:
//Serial.println("HELLO");

if (Serial.available())
{ 
   x= Serial.read();
  
  if(x=='a')
  {
    led=!led;
    digitalWrite(LED_BUILTIN,led);   // turn the LED on (HIGH is the voltage level)
    delay(100); 
    Serial.print("LED IS = ");
    Serial.println(led);
     }
}
}
