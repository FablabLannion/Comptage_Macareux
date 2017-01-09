#include <avr/sleep.h>  //http://heliosoph.mit-links.info/arduino-powered-by-capacitor-optimized-tests/
#include <avr/wdt.h>
#include <EEPROM.h>

#include <AC_TM1637.h>
#define pinCLK 6
#define pinDIO 5
AC_TM1637 display(pinCLK, pinDIO);
int x;

int Sun=501; int Day=1; int Nday=1; int H=0; int Aff=0;
long a=0;  long b=0;  long c=0;  long d=0; long  e=0; long  f=0;  long  g=0; long  h=0; long  i=0; 
long a1=0; long b1=0; long  c1=0; long d1=0; long  e1=0; long  f1=0; long g1=0; long  h1=0; long  i1=0;

long Dmemo=0;
int D=0; int add=0;  

volatile int K=0; volatile int K1=0;
int M=0; int M1=0;
int N=0; int N1=0;

unsigned int voltage;
byte keep_ADCSRA;
int dividerpin = 8;
int voltagepin = 0;

ISR (WDT_vect) {    //disable watchdog
  wdt_disable(); }  

#include "function.h"


void setup() {
   Serial.begin(9600);
   display.begin(); display.setBrightness(8); 
         
         display.showFloat(EEPROM. read(0)*100, 0, true);
     delay(2000);
   getadd();   
 
 // clear memory--------
      pinMode(4, OUTPUT);  digitalWrite(4, LOW);pinMode(4, INPUT); delay(2);
     if (digitalRead(4)==1){
       delay(5000);
         if (digitalRead(4)==1){   //demande de reset exprimé
         display.showFloat(3333, 0, true);  
         for( int x=0 ; x<1024 ;x++){            // clear all 1024 mmory
       EEPROM.write(x, 0); }  
     }delay(20); EEPROM.write(0, 1);   //  EEPROM.write(addr, val);
   
 }
 
    

     Serial.print("Last day saved");   Serial.print(EEPROM.read(0)); Serial.println("  "); 
      for( x=0 ; x<255 ;x++){           // display all 255 memoire long
         Serial.print(EEPROMReadlong(x));
         Serial.println();
          }
    delay(20);
   
  display.showFloat(5555, 0, true);  delay(500);
}

void loop() {
   
   GetLight();

    
    if(Sun >800 & Day==0){  // debut du jour au dessus de 800
    Day=1; H=0; Aff=0;
   a=0;  b=0;  c=0;  d=0;  e=0; f=0; g=0; h=0; i=0;
   a1=0; b1=0; c1=0; d1=0; e1=0; f1=0; g1=0; h1=0; i1=0;
   }
    
    
    
    
         if(Sun<200 & Day==1){  //nuit noir en dessous de 80
    display.showFloat(7777, 0, true);  delay(500);
     Day=0;  
     Nday=   EEPROM. read(0); // get the last day
     
   Dmemo= i+10*h+100*g+1000*f+10000*e +100000*d +1000000*c+10000000*b+100000000*a  ;
   EEPROMWritelong(Nday, Dmemo);
      
   Dmemo= i1+10*h1+100*g1+1000*f1+10000*e1 +100000*d1 +1000000*c1+10000000*b1+100000000*a1  ;
   EEPROMWritelong(Nday+128, Dmemo); 
              
     Nday++;   
     EEPROM.write(0, Nday); 
    display.showFloat(4444, 0, true);  
    delay(200); 
    }
    

   // Dmemo=d1 +10*c1+100*b1+1000*a1;
     //display.showFloat(Dmemo, 0, true);
    //
    if ( Nday>125 ){
   while(1){      set_sleep_mode(SLEEP_MODE_IDLE);       sleep_cpu ();       } }  // data full 4 mois
    
    //---------------------
    if(H>992){    //992.72 = 2H    une impulsion toutes les 7.253 secondes // 2H changement d'affectation--------------------------------
           Aff++;
           H=0;    M=0; M1=0; K=0; K1=0; N=0; N1=0;   }
    //-----------------------
    
    
     if (M<K){                        //detection d'une interupt sur pin2
   M=K;         
   N++; 
 
  if(Aff==0 & a<9) a++;   if(Aff==1 & b<9) b++;  if(Aff==2 & c<9) c++;  if(Aff==3 & d<9) d++; 
  if(Aff==4 & e<9) e++;  if(Aff==5 & f<9) f++;  if(Aff==6 & g<9) g++;  if(Aff==6 & h<9) h++;  if(Aff==6 & i<9) i++;  // id crennaux de 2H
  H++;
 // display.showFloat(a, 0, true); 
 display.showFloat(N*10, 0, true);
//delay(8000);   // wait 8 second  min entre 2 comptage
watchdog3();   sleep_cpu();  sleep_disable(); 
   } 
   
   
   if (M1<K1){                        //detection d'une interupt sur pin3
   M1=K1;         
   N1++;        
 if(Aff==0 & a1<9) a1++; if(Aff==1 & b1<9) b1++; if(Aff==2 & c1<9) c1++; if(Aff==3 & d1<9) d1++; 
 if(Aff==4 & e1<9) e1++; if(Aff==5 & f1<9) f1++;  if(Aff==6 & g1<9) g1++;  if(Aff==6 & h1<9) h1++;  if(Aff==6 & i1<9) i1++;  // id crennaux de 2H   
 
  H++;   
 display.showFloat(N1*100, 0, true);  
//delay(800);
 watchdog3();   sleep_cpu();  sleep_disable(); 
     // wait 8 second  min entre 2 comptage
 }
 
     
H++; 
 display.showFloat(H, 0, true); 
 
keep_ADCSRA = ADCSRA;
ADCSRA = 0;

 watchdog3();       
    attachInterrupt(0, kompting0, FALLING); //Interrupt 0 is digital pin 2
    attachInterrupt(1, kompting1, FALLING);
    interrupts ();
    sleep_cpu();
 
//herre sleeping

    sleep_disable();
    detachInterrupt(0);
    detachInterrupt(1);

    ADCSRA = keep_ADCSRA;
    digitalWrite(dividerpin, HIGH);
  
}
   void kompting0() {  K++;  }
  void kompting1() {  K1++;   }
