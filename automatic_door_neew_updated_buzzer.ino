#include <LiquidCrystal_I2C.h>

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27,20,4);

Servo myservo1;  
Servo myservo2; 

#define red 13
#define haha 4
#define PIR_sensor 4
int pos1,pos2;
int pirstat = 0;
const int buzzer = 9;
void setup() {
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(haha,INPUT);
  pinMode(13, OUTPUT);
  pinMode(4, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(PIR_sensor, INPUT);
  myservo1.attach(7);  
  myservo2.attach(8); 
  myservo1.write(90);
  myservo2.write(90);
  mlx.begin();  
 
  lcd.init();
  lcd.backlight();
 

}

void loop() {
  
        int montion = digitalRead(haha);
        
        if(montion == 1){
          
          Serial.print("made");
          Serial.print("\n");
          lcd.setCursor(0,0);
          lcd.print("ObjectTemp:");
          lcd.setCursor(13,3);
          lcd.print("INVICTA");          

          read();
          }   
}
          
void read()
{
  int temp_obj=35;
  while(temp_obj!=0)
   { 
    int temp_obj = mlx.readObjectTempC();
   Serial.print(temp_obj);
   Serial.print("\n");
   if(digitalRead(PIR_sensor))
{
 
          if(temp_obj < 31){
           lcd.setCursor(0,1);
           lcd.print(temp_obj);
           lcd.setCursor(0,2);
           lcd.print("Not detected,retest!");
              
          }if(temp_obj > 30 && temp_obj <38){
           
           lcd.setCursor(0,1);
           lcd.print(temp_obj);
           lcd.setCursor(0,2);
           lcd.print("body temperature ok "); 
           for(pos1 = 90; pos1 <= 180; pos1 += 1)
          {                                 
            myservo1.write(pos1);
            myservo2.write(180-pos1);         
            delay(15);
          }
            delay(5000);

           for(pos1 = 180; pos1>=90; pos1 -=1)
           {
            myservo1.write(pos1);
            myservo2.write(180-pos1);     
            delay(15);                     
           }

          } 
          if(temp_obj>37){
            digitalWrite(red,HIGH);
            lcd.setCursor(0,1);
            lcd.print(temp_obj);
            lcd.setCursor(0,2);
            tone(buzzer, 1000);
            delay(1000);
            noTone(buzzer);
            delay(1000);
            lcd.print("     Keep out!       ");
            delay(1000);
            
  }}}
  digitalWrite(red,LOW);
  }
  digitalWrite(red,LOW);
  }
