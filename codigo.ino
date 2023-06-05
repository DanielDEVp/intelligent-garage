#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
Servo myservo;  

int vel = 0;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   
const int LED =13;
const int BOTON = 7;
int val = 0; 
int state = 0; 
int old_val = 0; 
const int pir = 5;
const int luces = 12;


void setup() 
{
  Serial.begin(9600);  
  SPI.begin();     
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(2, OUTPUT);
  myservo.attach(6);
  pinMode(LED,OUTPUT); 
  pinMode(BOTON,INPUT); 
  pinMode(pir, INPUT);
  pinMode(luces, OUTPUT);
  pinMode(4, OUTPUT);
}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  digitalWrite(2, HIGH);
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "25 0E 1C 77") 
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(4, HIGH);
    digitalWrite(2, LOW);  
    vel = 0;
    myservo.write(vel);              
    delay(400);
    digitalWrite(2,LOW);
    delay (2600);
    vel = 90;
    myservo.write(vel);              
    delay (6000);
    vel = 180;
    myservo.write(vel);
    delay (3000);
    vel = 90;
    myservo.write(vel); 
    digitalWrite(4, LOW);
       
  }
 
 else   {
    Serial.println(" Access denied");
    delay(450);
    digitalWrite(2,LOW);
  }

val= digitalRead(BOTON); 
if ((val == HIGH) && (old_val == LOW)){
state=1-state;
delay(10);
}
old_val = val; 
if (state==1){
 digitalWrite(LED, HIGH);
}
else{
 digitalWrite(LED,LOW);
}

int valorpir = digitalRead(pir);
if (valorpir == HIGH)
  {
    digitalWrite(luces, HIGH);

  }
  else
  {
    digitalWrite(luces, LOW);
  }


} 