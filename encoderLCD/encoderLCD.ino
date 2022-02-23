#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // la direccion depende del chip de la 
                                    // pantalla y los puentes.

#define DT 3  // pines 3 y 4 se puede cambiar.
#define CLK 4

// VARIABLES
int valorAnt =0;
int valor = 0;

byte valorBinario =0;

boolean valorDT = false;
boolean  valorCLK = false;

boolean valorDTant = false;
boolean  valorCLKant = false;

int cantidad =0; //iniciamos en 0 
boolean cambio = false;


void setup(){
//############################################  
//LCD
//#############################################  
Wire.begin(); // Inicia el puerto I2C 
lcd.init(); 
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("PARA VOS MAniA");
lcd.backlight();
//############################################
pinMode(DT,INPUT);   
pinMode(CLK,INPUT);

  // se ejecuta solo al resetear
  valorDT = digitalRead(DT);
  valorCLK = digitalRead(CLK);
  
  cantidad =0; //iniciamos en 0
  
   if(valorDT == 1){
    bitSet(valorBinario,0);
   }
   else{
    bitClear(valorBinario,0);
   }
   if(valorCLK == 1){
    bitSet(valorBinario,1);
   }
   else{
    bitClear(valorBinario,1);
   }
   valorAnt = int(valorBinario);  // conversion de binario a entero
      lcd.setCursor(0, 1);
   lcd.print("               ");
   lcd.setCursor(0, 1);
   lcd.print(cantidad);
   lcd.print("mm");
   delay(2000);
}

void loop() {
  
leerPines();
delay(2000);  

}


void leerPines(){
  
  valorDT = digitalRead(DT);
  valorCLK = digitalRead(CLK);

  if(valorDT != valorDTant || valorCLK != valorCLKant){ // si cambia alguno de los valores                    
    cambio = true;  // si cambio el valor
        sentido();
    
    valorDTant = valorDT; // guardamos el lo valores actuales
    valorCLKant = valorCLK; 
  }
  else{
    cambio = false; //no cambio
  }
  
}


void sentido(){
  
   if(valorDT == 1){
    bitSet(valorBinario,0);
   }
   else{
    bitClear(valorBinario,0);
   }
   if(valorCLK == 1){
    bitSet(valorBinario,1);
   }
   else{
    bitClear(valorBinario,1);
   }

   valor = int(valorBinario);  // conversion de binario a entero

   if( valor > valorAnt){
        if(valor == 3){
          if(valorAnt ==1){
            cantidad--;
          }
          else{
            cantidad ++;
          }
        }else{
          cantidad++;
        }
        
   }
   else{
        if(valor == 0){
          if(valorAnt ==1){
            cantidad++;
          }
          else{
            cantidad --;
          }
        }else{
          cantidad--;   
        }
   }



   valorAnt =valor;

   lcd.setCursor(0, 1);
   lcd.print("               ");
   lcd.setCursor(0, 1);
   lcd.print(cantidad);
   lcd.print("mm");

 
}
