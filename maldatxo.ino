/*
 * ***********************
 * * LED AC animations  *
 * ***********************
 * 
 * By: Joseba Egia, Hirikilabs hiri laborategia, Tabakalera.
 * http://hirikilabs.tabakalera.eu/
 * Date: 18/05/2016 
 * V1.1 GNU General Public License v3.0 http://www.gnu.org/licenses/gpl-3.0.html 
 * 
 * This project is made to Olatu Talka festival (an event within Donostia 2016 European city of culture year, to light up a dark tunnel of Donostia-San Sebastian city.
 * Tunnel location = https://www.google.es/maps/@43.3186897,-1.9745292,3a,75y,99.7h,91.95t/data=!3m7!1e1!3m5!1sRalsiEKO-MsOvPg1OQ4R-g!2e0!6s%2F%2Fgeo3.ggpht.com%2Fcbk%3Fpanoid%3DRalsiEKO-MsOvPg1OQ4R-g%26output%3Dthumbnail%26cb_client%3Dmaps_sv.tactile.gps%26thumb%3D2%26w%3D203%26h%3D100%26yaw%3D34.23772%26pitch%3D0!7i13312!8i6656 
 * 
 * The sketch controls 10 AC led system with a AC led controller with zero cross detection making then shine with some animations at night and lighing up the tunel at daylight.
 * Also, it fades up when a ongoing passerby is detected by the PIR detectors at night.
 * 
 * AC led controller http://www.inmojo.com/store/krida-electronics/ (we use one of 8 channel and another with 2 channel.
 * PIR detector https://es.rs-online.com/web/p/detectores-de-alarma-de-seguridad-y-sensores-de-proximidad/4931289/?searchTerm=493-1289&relevancy-data=636F3D3126696E3D4931384E525353746F636B4E756D6265724D504E266C753D656E266D6D3D6D61746368616C6C26706D3D5E5C647B337D5B5C732D2F255C2E2C5D5C647B332C347D2426706F3D313426736E3D592673743D52535F53544F434B5F4E554D4245522677633D4E4F4E45267573743D3439332D31323839267374613D3439333132383926
*/

#include <TimerOne.h>

unsigned char ledPins[] = {13,12,11,10,9,8,7,6,5,4};
unsigned char CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9;
unsigned char CH[]={CH0,CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9};

unsigned char dim_level[]={5,8,10,12,15,18,20,25,30,35,45,50,55,60,65,70,75,80,82,85,88,92,95};   // don't use this massive for 60Hz
                                                                                                  // create new massive for 60Hz
int i=0;
int generator;
int delay_time;     // delay ms or flashing SPEED
unsigned char clock_tick;        // variable for Timer1
unsigned char CHANNEL_SELECT;    // variable for channel select

unsigned char low = 70;
unsigned char high = 5;
unsigned char off = 95;

const byte PIR = 3; // Pir sensors at Pin 3
const byte sync = 2; // Zero cross sync at pin 2
const byte LDR = 0; //LDR to Analog 0 pin

const int threshold = 100; // Treshold value to start get the ligths up
int lightLevel, highlight = 0, lowligh = 1023; //LDR light levels at start


void setup() {

  for(i = 0; i <= 9; i++)      // Set AC Load pins as output
  {
    pinMode(ledPins[i],OUTPUT);
  }

  pinMode(PIR, INPUT);
  pinMode(sync, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR), peoplegoing, LOW);
  attachInterrupt(digitalPinToInterrupt(sync), zero_crosss_int, RISING);  
  Timer1.initialize(100); // set a timer of length 100 microseconds for 50Hz or 83 microseconds for 60Hz; 
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
    
}

void loop() {

lightLevel = analogRead(LDR);
autoTune();

if (lightLevel < threshold){
attachInterrupt(digitalPinToInterrupt(PIR), peoplegoing, LOW);

generator = random(5);  //select randomly between the animations
switch (generator){
  case 0: onebyone(); 
  break;          
  case 1: oneanother();
  break;
  case 2: centertocorners();
  break;
  case 3: snake();
  break;
  case 4: evenodds();
  break;
  case 5: randomLED();
  break; 
}
}
/*else{
  detachInterrupt(digitalPinToInterrupt(PIR));
  daylight();
}*/
}

void autoTune()
{
    if (lightLevel < lowligh)
  {
    lowligh = lightLevel;
  }

  if (lightLevel > highlight)
  {
    highlight = lightLevel;
  }

  lightLevel = map(lightLevel, lowligh+30, highlight-30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);

}

void timerIsr()
{    
    clock_tick++;
   
      if (CH[0]==clock_tick)
    {
      digitalWrite(ledPins[0], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[0], LOW);    // triac Off 
    }  
    
      if (CH[1]==clock_tick)
    {
      digitalWrite(ledPins[1], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[1], LOW);    // triac Off 
    }  
        
      if (CH[2]==clock_tick)
    {
      digitalWrite(ledPins[2], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[2], LOW);    // triac Off 
    }  
    
      if (CH[3]==clock_tick)
    {
      digitalWrite(ledPins[3], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[3], LOW);    // triac Off 
    }   
      if (CH[4]==clock_tick)
    {
      digitalWrite(ledPins[4], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[4], LOW);    // triac Off 
    }   
      if (CH[5]==clock_tick)
    {
      digitalWrite(ledPins[5], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[5], LOW);    // triac Off 
    }   
      if (CH[6]==clock_tick)
    {
      digitalWrite(ledPins[6], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[6], LOW);    // triac Off 
    }   
      if (CH[7]==clock_tick)
    {
      digitalWrite(ledPins[7], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[7], LOW);    // triac Off 
    }   
      if (CH[8]==clock_tick)
    {
      digitalWrite(ledPins[8], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[8], LOW);    // triac Off 
    }
      if (CH[9]==clock_tick)
    {
      digitalWrite(ledPins[9], HIGH);   // triac firing
      delayMicroseconds(10);           // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ledPins[9], LOW);    // triac Off 
    }   
}

 

void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{
  // Every zerocrossing interrupt: For 50Hz (1/2 Cycle) => 10ms  ; For 60Hz (1/2 Cycle) => 8.33ms 
  // 10ms=10000us , 8.33ms=8330us
  
    clock_tick=0;        
}

void oneanother(){

delay_time = 150;

for (CHANNEL_SELECT=0;CHANNEL_SELECT<10;CHANNEL_SELECT++)  // fade up
 {
  for (i=23;i>1;i--)
  {
    CH[CHANNEL_SELECT]=dim_level[i];
    delay(delay_time);
  } 
 }
delay(2000);
for (CHANNEL_SELECT=0;CHANNEL_SELECT<10;CHANNEL_SELECT++)  // fade down
 {
  for (i=0;i<23;i++)
  {
    CH[CHANNEL_SELECT]=dim_level[i];
    delay(delay_time);
  } 
 }
delay(2000);
}


void onebyone() {

delay_time = 500;

for (i=0; i<=10;i++){
 
 for (CHANNEL_SELECT=0;CHANNEL_SELECT<10;CHANNEL_SELECT++) 
 {
    CH[CHANNEL_SELECT]=high;
    delay(delay_time);
    CH[CHANNEL_SELECT]=off;
  }
 for (CHANNEL_SELECT=10;CHANNEL_SELECT>=0;CHANNEL_SELECT--) 
 {
    CH[CHANNEL_SELECT]=high;
    delay(delay_time);
    CH[CHANNEL_SELECT]=off;
  }  
 }
}


void centertocorners() {

delay_time = 500;

for (i=0;i<=5;i++){

  CH0=off;CH1=off;CH2=off;CH3=off;CH4=off;CH5=off;CH6=off;CH7=off;CH8=off;CH9=off;
  delay(delay_time);
  CH0=off;CH1=off;CH2=off;CH3=off;CH4=low;CH5=low;CH6=off;CH7=off;CH8=off;CH9=off;
  delay(delay_time);
  CH0=off;CH1=off;CH2=off;CH3=low;CH4=low;CH5=low;CH6=low;CH7=off;CH8=off;CH9=off; 
  delay(delay_time);
  CH0=off;CH1=off;CH2=low;CH3=low;CH4=low;CH5=low;CH6=low;CH7=low;CH8=off;CH9=off;
  delay(delay_time);
  CH0=off;CH1=low;CH2=low;CH3=low;CH4=low;CH5=low;CH6=low;CH7=low;CH8=low;CH9=off;
  delay(delay_time);
  CH0=low;CH1=low;CH2=low;CH3=low;CH4=low;CH5=low;CH6=low;CH7=low;CH8=low;CH9=low;
  delay(delay_time);

  CH0=low;CH1=low;CH2=low;CH3=low;CH4=high;CH5=high;CH6=low;CH7=low;CH8=low;CH9=low;
  delay(delay_time);
  CH0=low;CH1=low;CH2=low;CH3=high;CH4=off;CH5=off;CH6=high;CH7=low;CH8=low;CH9=low;
  delay(delay_time);
  CH0=low;CH1=low;CH2=high;CH3=off;CH4=off;CH5=off;CH6=off;CH7=high;CH8=low;CH9=low;
  delay(delay_time);
  CH0=low;CH1=high;CH2=off;CH3=high;CH4=off;CH5=off;CH6=off;CH7=off;CH8=high;CH9=low;
  delay(delay_time);
  CH0=high;CH1=off;CH2=off;CH3=high;CH4=off;CH5=off;CH6=off;CH7=off;CH8=off;CH9=high;
  delay(delay_time);

  CH0=low;CH1=high;CH2=off;CH3=high;CH4=off;CH5=off;CH6=off;CH7=off;CH8=high;CH9=low;
  delay(delay_time);
  CH0=low;CH1=low;CH2=high;CH3=off;CH4=off;CH5=off;CH6=off;CH7=high;CH8=low;CH9=low;
  delay(delay_time);
  CH0=low;CH1=low;CH2=low;CH3=high;CH4=off;CH5=off;CH6=high;CH7=low;CH8=low;CH9=low;
  delay(delay_time);
  CH0=low;CH1=low;CH2=low;CH3=low;CH4=high;CH5=high;CH6=low;CH7=low;CH8=low;CH9=low;
  delay(delay_time);

  CH0=low;CH1=low;CH2=low;CH3=low;CH4=low;CH5=low;CH6=low;CH7=low;CH8=low;CH9=low;
  delay(delay_time);
  CH0=off;CH1=low;CH2=low;CH3=low;CH4=low;CH5=low;CH6=low;CH7=low;CH8=low;CH9=off;
  delay(delay_time);
  CH0=off;CH1=off;CH2=low;CH3=low;CH4=low;CH5=low;CH6=low;CH7=low;CH8=off;CH9=off;
   delay(delay_time);
  CH0=off;CH1=off;CH2=off;CH3=low;CH4=low;CH5=low;CH6=low;CH7=off;CH8=off;CH9=off;
  delay(delay_time);
  CH0=off;CH1=off;CH2=off;CH3=off;CH4=low;CH5=low;CH6=off;CH7=off;CH8=off;CH9=off;
  delay(delay_time);
  CH0=off;CH1=off;CH2=off;CH3=off;CH4=off;CH5=off;CH6=off;CH7=off;CH8=off;CH9=off;
  delay(delay_time);
  }
}

void snake(){

  delay_time = 500;
  
  for (i=0;i<=5;i++){
    
    for (CHANNEL_SELECT=0;CHANNEL_SELECT<10;CHANNEL_SELECT++) 
    {
      CH[CHANNEL_SELECT]=high;
      delay(delay_time);
      CH[CHANNEL_SELECT-1]=low;
    }
    CH8=off;
    for (CHANNEL_SELECT=9;CHANNEL_SELECT>=0;CHANNEL_SELECT--) 
    {
      CH[CHANNEL_SELECT]=high;
      delay(delay_time);
      CH[CHANNEL_SELECT+1]=low;
    }
    CH1=off;
  }
}

void evenodds(){

  delay_time = 1000;
  
  for (i=0;i<=5;i++){
  
    CH0=low;CH1=high;CH2=low;CH3=high;CH4=low;CH5=high;CH6=low;CH7=high;CH8=low;CH9=high;
    delay(delay_time);
    CH0=high;CH1=high;CH2=high;CH3=high;CH4=5;CH5=high;CH6=5;CH7=high;CH8=high;CH9=high;
    delay(150);
    CH0=low;CH1=high;CH2=low;CH3=high;CH4=low;CH5=high;CH6=low;CH7=high;CH8=low;CH9=high;
    delay(delay_time);

    CH0=high;CH1=low;CH2=high;CH3=low;CH4=high;CH5=low;CH6=high;CH7=low;CH8=high;CH9=low;
    delay(delay_time);
    CH0=high;CH1=high;CH2=high;CH3=5;CH4=high;CH5=high;CH6=high;CH7=5;CH8=high;CH9=high;
    delay(150);
    CH0=high;CH1=low;CH2=high;CH3=low;CH4=high;CH5=low;CH6=high;CH7=low;CH8=high;CH9=low;
    delay(delay_time);
    }  
}

void randomLED(){

  for (i=0;i<=50;i++){
    
    i = random(10);    
    delay_time = random(500,3000);

    ledPins[i] = high;
    delay(delay_time);                    
    ledPins[i]= low; 
  }
}

void daylight(){
   
   CH0=high;CH1=high;CH2=high;CH3=5;CH4=high;CH5=high;CH6=high;CH7=5;CH8=high;CH9=high;
   delay(delay_time);
   lightLevel = analogRead(LDR);
   autoTune();
   
   while (lightLevel >= threshold){
   lightLevel = analogRead(LDR);
   autoTune();
   }
   CH0=off;CH1=off;CH2=off;CH3=off;CH4=off;CH5=off;CH6=off;CH7=off;CH8=off;CH9=off;
   delay(delay_time);
}

void peoplegoing(){

delay_time = 50;

for (i=23;i>16;i--){          //no total light
  for (CHANNEL_SELECT=0;CHANNEL_SELECT<10;CHANNEL_SELECT++) {
    CH[CHANNEL_SELECT]=dim_level[i];
    }
  delay(delay_time);
  }  
delay(60000);
}
