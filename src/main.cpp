#include <Arduino.h>

int TRIG = 4;  // (RX)
int ECO = 3;   // (TX)
int DURACION;
int DISTANCIA;
int VELOCIDAD;

int IN1 = 9;      // IN1 a pin (D7)
int IN2 = 8;      // IN2 a pin (D6)
int ENA = 10;      // ENA a pin (D8)
int IN3 = 6;      // IN3 a pin (D5)
int IN4 = 7;      // IN4 a pin  (D3)
int ENB = 5;      // ENA a pin  (D2)

unsigned long espera1 = 750;
unsigned long espera2 = 500;
unsigned long espera3 = 880;
unsigned long espera4 = 500;

unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long tiempo3 = 0;
unsigned long tiempo4 = 0;

void setup() {
  pinMode( TRIG, OUTPUT);
  pinMode ( ECO, INPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  Serial.begin (9600);
}

void loop() {
  VELOCIDAD = 100;    // valor de velocidad para PWM de ENA y ENB
  digitalWrite (TRIG, HIGH);
  //delay (100);
  digitalWrite (TRIG, LOW);
  DURACION = pulseIn (ECO, HIGH);
  DISTANCIA = DURACION / 58.2;
  
  if (DISTANCIA == 0) {
    DISTANCIA = 30;
  }
  if (DISTANCIA <= 15) { //&& DISTANCIA >=0

     Serial.println("distancia: ");
     if (millis()-tiempo1> espera1){
//La logica en el if esta mal. 
//Te lo pongo con un ejemplo:
//millis arranca en 0 cuando encendes el micro. Cuando paso un segundo, tiene el valor 1000
//en ese momento: 1000-0 > 750 --> true, se ejecuta esto y deja a tiempo1 = 1000.
//supongamos que paso otro segunto, millis ahora vale 2000 =>
//2000-1000 > 750 es true, se ejecuta y deja tiempo1 = 1000+2000 = 3000
//PERO ahora supone que paso un segundo mas, entonces millis = 3000
//entonces 3000-3000 > 750 es false, no se ejecuta, y de hecho no se ejecuta nunca mas (O al menos hasta que millis de la vuelta dentro de ~50 dias)
      analogWrite(ENA, 80);  
      digitalWrite(IN1, LOW); 
      digitalWrite(IN2, HIGH);
      analogWrite(ENB, 80);  
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH); 
      Serial.println("primer espera: ");
      tiempo1 += millis();
    }
    
     if (millis() - tiempo1 > espera2){
      analogWrite(ENA,0);
      analogWrite(ENB,0);
      Serial.println("segunda espera: ");
      tiempo2 += millis();
    }
    

     if (millis() - tiempo2 > espera3){
      analogWrite(ENB, 80);  
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH);
      Serial.println ("tercer espera: ");
      tiempo3 += millis();
    }
    if (millis() - tiempo3 > espera4){
      analogWrite(ENA,0);
      analogWrite(ENB,0);
      Serial.println("cuarta espera: ");
      tiempo4 += millis();
    }
   /* if (millis()<= tiempo1 + espera1){
      //tiempo1 += espera1 ;
      analogWrite(ENA, 100);  
      digitalWrite(IN1, LOW); 
      digitalWrite(IN2, HIGH);
      analogWrite(ENB, 100);  
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH);    
    }

    if (tiempo1 + espera1 < millis() <= tiempo1 + espera2 ){
      tiempo2 += espera2;
      analogWrite(ENA,0);
      analogWrite(ENB,0);
    }

    if (tiempo1 + espera2 < millis() <= tiempo1 + espera3){
      tiempo1 += espera3 ;
      tiempo2 += espera2;
      tiempo3 += espera3;
      analogWrite(ENB, 100);  
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH);
    }
    */
   /* detieneAmbos();   
    delay(100);      
    bAvance(VELOCIDAD);   
    delay(880);      
    detieneAmbos();   
    delay(100);      
    aAvance(VELOCIDAD);   
    bAvance(VELOCIDAD);   
    delay(750);      
    detieneAmbos();   
    delay(100);      
    aAvance(VELOCIDAD);   
    delay(750);      
    detieneAmbos();  
    delay(100);      
    aAvance(VELOCIDAD);   
    bAvance(VELOCIDAD);   
    delay(800);      
    detieneAmbos();   
    delay(100);      
    aAvance(VELOCIDAD);   
    delay(700);      
    detieneAmbos();   
    delay(100);      
    aAvance(VELOCIDAD);  
    bAvance(VELOCIDAD);   
    delay(750);      
    detieneAmbos();   
    delay(100);      
    bAvance(VELOCIDAD);   
    delay(750);      
    detieneAmbos();   
    delay(100);      
  */
 }
}
/*
void aAvance(int veloc) { 
  analogWrite(ENA, veloc);  
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);  
}

void bAvance(int veloc) { 
  analogWrite(ENB, veloc);  
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);  
}

void detieneAmbos() {   
  analogWrite(ENA, 0);    
  analogWrite(ENB, 0);    
}*/
