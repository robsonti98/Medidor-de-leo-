#include  <TimerOne.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

float pulsos = 0;
float litros = 0;
float contador = 0;
float fluxo_contador = 0;
float fluxo = 0;
int segundos = 0;
float media_fluxo = 0;
float contador2 = 0;
float fluxo_medido = 0;

void interrupcao_externa()
{
  pulsos = pulsos + 1;
}

void interrupcao()
{
  segundos = segundos + 1; 
}


void setup() 
{
  pinMode(3,OUTPUT);
  pinMode(2,INPUT);
  pinMode(1,OUTPUT);

  pinMode(A0,INPUT);

  digitalWrite(1,HIGH);
  digitalWrite(3,LOW);

  lcd.begin(16,2);

  lcd.setCursor(0,0);
  lcd.print("Medidor de");
  lcd.setCursor(0,1);
  lcd.print("Oleo Vegetal");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" SANTEC");
  lcd.setCursor(0,1);
  lcd.print(" AMBIENTAL");
  delay(3000);
  lcd.clear();

  attachInterrupt(0,interrupcao_externa,RISING);
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(interrupcao);
}

void loop() 
{   
    lcd.setCursor(0,0);
    lcd.print("Litros:");
    lcd.setCursor(0,1);
    lcd.print("L/min:");

    if(litros < 10)
    {
      lcd.setCursor(8,0);
      lcd.print("0"); 
      lcd.setCursor(9,0);
      lcd.print(litros,2);  
    }
    if(litros >= 10)
    {
      lcd.setCursor(8,0);
      lcd.print(litros,2);  
    }

    if(fluxo < 10)
    {
      lcd.setCursor(7,1);
      lcd.print("0"); 
      lcd.setCursor(8,1);
      lcd.print(fluxo,2);  
    }
    if(fluxo >= 10)
    {
       lcd.setCursor(7,1);
       lcd.print(fluxo,2);  
    }
      
       if(segundos >= 1)
       { 
         segundos = 0;
         
         detachInterrupt(interrupcao_externa);
         fluxo = (pulsos)/5.5;
         // 5.5 para o sensor de fluxo maior e preto ; 67.5 para o sensor de fluxo menor e branco
         litros = litros + (fluxo/60.0);
      
         pulsos = 0;
         contador = 0;
       }
     
       attachInterrupt(0,interrupcao_externa,RISING);

       

       

    if(analogRead(A0) > 400 && analogRead(A0) < 600)
    {
       litros = 0;  
    }
}


