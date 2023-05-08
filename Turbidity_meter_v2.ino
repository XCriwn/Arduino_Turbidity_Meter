#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

const int buttonPin = 3;
int buttonState = 0;
volatile int buzz = 1;
int stop_repetition = 0;

int led_Rosu = 10;
int led_Verde = 11;
int led_Albastru = 12;
boolean i=0;
int luminozitate_led = 20;

int debug_int=50;
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(1, ISR_button, RISING);

  pinMode(led_Rosu, OUTPUT);
  pinMode(led_Verde, OUTPUT);
  pinMode(led_Albastru, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  setColor(20, 20, 20);
}

void loop() {
  int sensorValue = analogRead(A0);
  int turbidity = map(sensorValue, 0,640, 100, 0);
  if(turbidity < 0) turbidity = 0;
  //for debugging only:
  //if(i == 0) turbidity = 30;
  //if(i != 0) {turbidity = debug_int*10; debug_int++;}
  //if(i != 0 && debug_int>=10){turbidity = 0; debug_int=0;}
  //end of debugging section

  if(i==0){
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stan Alex's");
  tone(13, 261, 200); //Middle C
  setColor(luminozitate_led, luminozitate_led, luminozitate_led);
  delay(200);
  tone(13, 277, 200); //C#
  delay(200);
  tone(13, 294, 200); //D
  delay(200);
  tone(13, 311, 200); //D#
  delay(200);
  setColor(luminozitate_led, luminozitate_led, 0);
  tone(13, 370, 200); //F#
  delay(400);
  setColor(0, luminozitate_led, luminozitate_led);
  tone(13, 370, 200); //F#
  delay(400);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Turbidity Meter");
  setColor(0, luminozitate_led, 0);
  tone(13, 349, 200); //F
  delay(200);
  tone(13, 311, 200); //D#
  delay(200);
  tone(13, 294, 200); //D
  delay(200);
  setColor(0, 0, luminozitate_led);
  tone(13, 370, 200); //F#
  delay(400);
  setColor(luminozitate_led, 0, 0);
  tone(13, 370, 200); //F#
  delay(400);
  setColor(0, 0, 0);
  i=1;
  }
  delay(3000);

  if(turbidity < 21){
    setColor(luminozitate_led, 0, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("It's dirty");
    lcd.setCursor(0, 1);
    lcd.print("Procent: "); lcd.print(turbidity);lcd.print(" %");

    //red
   	if(buzz==1 && stop_repetition != 40){
      tone(13, 330, 200); //E
      delay(200);
      tone(13, 294, 200); //D
      delay(200);
      tone(13, 261, 200); //Middle C
      delay(200);
      stop_repetition = 40;
      }

    } else if(turbidity < 51){
    setColor(luminozitate_led, luminozitate_led, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("It's cloudy");
    lcd.setCursor(0, 1);
    lcd.print("Procent: "); lcd.print(turbidity);lcd.print(" %");

    //yellow:
	  if(buzz==1 && stop_repetition != 20){
      setColor(luminozitate_led, luminozitate_led, 0);
      tone(13, 349, 200); //F
      delay(200);
      tone(13, 311, 200); //D#
      delay(250);
      tone(13, 311, 200); //D#
      delay(150);

      stop_repetition = 20;
      }
    setColor(luminozitate_led, luminozitate_led, 0);
    } else{
    setColor(0, luminozitate_led, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("It's clean");
    lcd.setCursor(0, 1);
    lcd.print("Procent: "); lcd.print(turbidity);lcd.print(" %");
    setColor(0, luminozitate_led, 0);
    //green:
  	if(buzz==1 && stop_repetition != 30){
      setColor(0, luminozitate_led, 0);
      tone(13, 392, 200); //G
      delay(200);
      tone(13, 370, 200); //F#
      delay(200);
	    tone(13, 392, 200); //G
      delay(200);

      stop_repetition = 30;
      }
      setColor(0, luminozitate_led, 0);
    }
    
}
void setColor(int redValue, int greenValue, int blueValue) {
  //255 este inversat cu 0 din nst ce motiv asa ca 255-valoare e necesar 
  analogWrite(led_Rosu, 255-redValue);
  analogWrite(led_Verde, 255-greenValue);
  analogWrite(led_Albastru, 255-blueValue);
}

void ISR_button(){
  if(buzz == 1){
  	buzz =0;
  }
  else{buzz = 1;}
}