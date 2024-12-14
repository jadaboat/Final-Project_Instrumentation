
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
const int cold_ref = 8;
const int hot_ref = 9;
const int mot = 7;
int cold;
int hot;
int count = 0;
bool lastState = LOW;
static unsigned long lastUpdateTime = 0; // Timer for temperature message
static unsigned long messageDuration = 2000; // Duration to display the message (2 seconds)
static bool displayingMessage = false;   // Flag to track if a message is being displayed


void setup() {
  pinMode(cold_ref,INPUT_PULLUP);
  pinMode(hot_ref,INPUT_PULLUP);
  pinMode(mot,OUTPUT);
  pinMode(6,INPUT);
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  Serial.begin(9600);
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Hello world!");
  
  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("LCD Tutorial");
}

void loop() {
   // Print a message on both lines of the LCD.
   cold = digitalRead(cold_ref);
   hot = digitalRead(hot_ref);


  if(cold== HIGH && hot == LOW){
  lcd.clear(); 
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Temperature");
  lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
  lcd.print("within range");
   digitalWrite(mot,HIGH);
  delay(2000);
  }

else if(cold== LOW && hot == LOW){
  lcd.clear(); 
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Temperature");
  lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
  lcd.print("below range");
  digitalWrite(mot,HIGH);
  delay(2000);
}

else if (cold== HIGH && hot == HIGH){
  lcd.clear(); 
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Temperature");
  lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
  lcd.print("above range");
  digitalWrite(mot,LOW);
  delay(2000);

   bool currentState = digitalRead(6);  
  // Check for a transition from LOW to HIGH
  if (lastState == LOW && currentState == HIGH) {
    count++;
    Serial.print("Count: ");
    Serial.println(count);
  }

  lastState = currentState; // Updates to last value read from pin.  
  delay(10);  
  lcd.clear(); 
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print(count);
  lcd.setCursor(0,1);   //Set cursor to character 2 on line 0
  delay(2000);

  }
  else{

  }
 
 Serial.println(hot);
 Serial.println( cold);
 Serial.println("-----");