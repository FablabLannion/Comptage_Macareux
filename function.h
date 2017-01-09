void watchdog3(){
  
   
   MCUSR = 0;     
   WDTCSR = _BV (WDCE) | _BV (WDE); 
   WDTCSR = bit (WDIE) | bit (WDP3) | bit (WDP0); //set 8sec   //WDTCSR = _BV (WDIE) | _BV (WDP2) | _BV (WDP1);    // set WDIE, and 1 second delay
   wdt_reset();  // pat the dog
    digitalWrite(dividerpin, LOW);

    set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
    sleep_enable();

    MCUCR = _BV (BODS) | _BV (BODSE); 
    MCUCR = _BV (BODS);      
  
  
  }
  
   void GetLight(){         //--------------get light intencity
   pinMode(A1, OUTPUT);    digitalWrite(A1, HIGH);
    Sun=analogRead(A2);
   //display.showFloat(Sun, 0, true);  delay(200);
   digitalWrite(A1, LOW);   pinMode(A1, INPUT);
}

  
  void getadd(){
  pinMode(A0, OUTPUT);  digitalWrite(A0, HIGH); //activate add power
  for(x=13 ; x>6 ;x--){
        pinMode(x, OUTPUT); digitalWrite(x, LOW);  pinMode(x, INPUT);
        }
 
   K=1;  add=0;
   for( x=13 ; x>6 ;x--){
       D = digitalRead(x);
       add= int(add + D*pow(2,K)+0.1);
       K++;
       }
 digitalWrite(A0, LOW);  pinMode(A0, INPUT); // desactivate add power
 Serial.print("physic address"); Serial.print(add); Serial.println();
 display.showFloat(add, 0, true);  delay(1000); 
 }
 
 
 void EEPROMWritelong(int address, long value){
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address*4, four);
      EEPROM.write(address*4 + 1, three);
      EEPROM.write(address*4 + 2, two);
      EEPROM.write(address*4 + 3, one);
      }
      
long EEPROMReadlong(long address)
      {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address*4);
      long three = EEPROM.read(address*4 + 1);
      long two = EEPROM.read(address*4 + 2);
      long one = EEPROM.read(address*4 + 3);

      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
      }
