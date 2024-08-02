char dizi; // to store incoming byte 
int inc;
int result;
void setup() {
  Serial.begin(9600); // Seri Portu başlat.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
      if (Serial.available() > 0) {       
        dizi = Serial.read();

        if(dizi == 'x'){
          digitalWrite(LED_BUILTIN, HIGH);
        }
        if(dizi == 'y'){
          digitalWrite(LED_BUILTIN, LOW);
        }
        if(dizi == 'z'){
          for(int i = 0;i<3;i++){
            digitalWrite(LED_BUILTIN, HIGH);
            delay(250);
            digitalWrite(LED_BUILTIN, LOW);
            delay(250);
          }
      }

          
  }
}
