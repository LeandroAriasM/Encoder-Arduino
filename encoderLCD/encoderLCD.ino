#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // la direccion depende del chip de la 
                                    // pantalla y los puentes.
//int val;
#define CLK 3 
#define DT 4 

#define CLK2 5 
#define DT2 6 

#define SW 8
#define SW2 9

float Posicion = 0;
float Posicion2 = 0;
 
int CLKanterior = LOW; 
int CLKanterior2 = LOW; 
int n = LOW; 
int n2 = LOW;

float paso1 = 0.25;
float paso2 = 0.5;

void setup() { 
      pinMode (CLK,INPUT); 
      pinMode (DT, INPUT);
      pinMode (CLK2,INPUT); 
      pinMode (DT2, INPUT);
            
      pinMode (SW, INPUT);
      pinMode (SW2, INPUT);      
//############################################  
//LCD
//#############################################  
Wire.begin(); // Inicia el puerto I2C 
lcd.init(); 
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("ENCODER");
lcd.backlight();
//############################################
Posicion = Posicion - paso1;    
Posicion2 = Posicion2 - paso2;    
mostrar();


          //Serial.begin (9600);
}
 
void loop() { 
leerPines();

}

void leerPines(){
        n = digitalRead(CLK); 
      if ((CLKanterior == LOW) && (n == HIGH)) { 
      if (digitalRead(DT) == LOW) { Posicion = Posicion - paso1;} 
      else { Posicion = Posicion + paso1;} 
mostrar(); 
      }

      
      n2 = digitalRead(CLK2); 
      if ((CLKanterior2 == LOW) && (n2 == HIGH)) { 
      if (digitalRead(DT2) == LOW) {Posicion2 = Posicion2 - paso2;} 
      else {Posicion2 = Posicion2 + paso2;} 
mostrar();  
      } 


      CLKanterior = n;
      CLKanterior2 = n2;
if ((digitalRead(SW) == LOW)) {Posicion = 0; 
mostrar();

}
if ((digitalRead(SW2) == LOW)) {Posicion2 = 0; 
mostrar();

    }
}

void mostrar(){
   lcd.setCursor(0, 1);
   lcd.print("                ");
   lcd.setCursor(0, 1);
   lcd.print(Posicion);
   lcd.print("mm  ");
   lcd.print(Posicion2);
   lcd.print("mm"); 
}

    
