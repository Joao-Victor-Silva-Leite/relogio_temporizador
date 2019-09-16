#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>

const byte ROWS = 4; //define as 3 linhas do teclado
const byte COLS = 3; //define as 4 colunas do teclado
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {3,4,5,6}; //conecta os pinos das linhas do teclado
byte colPins[COLS] = {7,8,9};//conecta os pinos da coluna do teclado

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

boolean inicio = false; 
boolean final = false; //variáveis de controle

String num1, num2, num3, num4, num5;

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //define o endereço 0x27 para o teclado I2c

int asegundo,aminuto, ahora, adia, ames,aano; //variáveis para o alarme
int buzzer = 11; //define o pino para o buzzer
char daysOfTheWeek[7][13] = {"Domingo", "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sabado"}; //dias da semana
const int menu = 2;//definição do pino 2 que irá receber valor alto ou baixo do botão que mostra o dia da semana
int estadomenu = 0;//definição da variável que armazena o estado do pino 2
const int alarme = 10;//definição do pino 10 que irá receber valor alto ou baixo do botão que mostra o alarme
int estadoalarme = 0;//definição da variável que armazena o estado do pino 10

void setup () {
lcd.begin(16,2);//inicia o lcd
  
aminuto=00;  //zera as variáveis do alarme
ahora=00;  
adia=00;  
ames=00;  
aano=00; 
  pinMode(12, OUTPUT); //pino de saída do relé
  pinMode(13, OUTPUT); //pino de saída do LED
  pinMode(2,INPUT_PULLUP);//define o pino 2 como entrada, sem necessidade física de um resistor de pull-up
 pinMode(10,INPUT_PULLUP);//define o pino 10 como entrada, sem necessidade física de um resistor de pull-up

delay(500); // espera o RTC iniciar

  if (! rtc.begin()) {
    Serial.println("RTC não encontrado"); //mensagem que aparecerá, caso o RTC não estiver presente
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("Ajuste o tempo");
   //para setar o RTC se esse perder dados da memória
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // essa linha seta o RTC com data e hora
   
  }
//Configura o minuto para alarme  
lcd.clear();  
lcd.setCursor(0,0);
lcd.print("*");
lcd.setCursor(4,0); 
lcd.print("Relogio");
lcd.setCursor(3,1); 
lcd.print("EduArduino");
lcd.setCursor(15,0); 
lcd.print("*");
delay(5000);
lcd.clear();  
lcd.setCursor(0,0); 
lcd.print("Ajuste o alarme");
delay(3000);
lcd.clear();  
lcd.setCursor(0,0);  
lcd.print("1)Entre Minuto:"); 
lcd.setCursor(0,1);  
lcd.print("2) pressione *"); 
while(aminuto==0)   {    
    char key = keypad.getKey();
     if (key != NO_KEY && (key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9' || key=='0'))
  {
    if(inicio == false)
      {num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(16-numLength,0);
      lcd.print(num1); 
      final = true;
      
     
  }
  
}
if (final == true && key !=NO_KEY && key == '*')
{
   aminuto=num1.toInt();    
}
 
}  
lcd.clear();
lcd.print(aminuto);  
delay(1000);

//-------------------------------------------------------

//Configura a hora para alarme
lcd.clear();  
lcd.setCursor(0,0);  
lcd.print("1)Entre hora:"); 
lcd.setCursor(0,1);  
lcd.print("2) pressione *"); 

while(ahora==0)   {    
    char key = keypad.getKey();
     if (key != NO_KEY && (key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9' || key=='0'))
  {
    if(inicio == false)
      {num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(16-numLength,0);
      lcd.print(num2); 
      final = true;
      
     
  }
  
}
if (final == true && key !=NO_KEY && key == '*')
{
   ahora=num2.toInt();    
}
 
}  
lcd.clear();
lcd.print(ahora);  
delay(1000);
//-------------------------------------
//Configura o dia para alarme
lcd.clear();  
lcd.setCursor(0,0);  
lcd.print("1)Entre dia:");
lcd.setCursor(0,1);  
lcd.print("2)pressione *");   

while(adia==0)   {    
    char key = keypad.getKey();
     if (key != NO_KEY && (key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9' || key=='0'))
  {
    if(inicio == false)
      {num3 = num3 + key;
      int numLength = num3.length();
      lcd.setCursor(16-numLength,0);
      lcd.print(num3); 
      final = true;
      
     
  }
  
}
if (final == true && key !=NO_KEY && key == '*')
{
   adia=num3.toInt();    
}
 
}  
lcd.clear();
lcd.print(adia);  
delay(1000);
//--------------------------------------------------------------

//Configura o mes para alarme
lcd.clear();  
lcd.setCursor(0,0);  
lcd.print("1)Entre mes:"); 
lcd.setCursor(0,1);  
lcd.print("2)pressione *"); 

while(ames==0)   {    
    char key = keypad.getKey();
     if (key != NO_KEY && (key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9' || key=='0'))
  {
    if(inicio == false)
      {num4 = num4 + key;
      int numLength = num4.length();
      lcd.setCursor(16-numLength,0);
      lcd.print(num4); 
      final = true;
      
     
  }
  
}
if (final == true && key !=NO_KEY && key == '*')
{
   ames=num4.toInt();    
}
 
}  
lcd.clear();
lcd.print('0'); 
lcd.print(ames);  
delay(1000);


//--------------------------------------------------------------

//Configura o ano para alarme
lcd.clear();  
lcd.setCursor(0,0);  
lcd.print("1)Entre ano:"); 
lcd.setCursor(0,1);  
lcd.print("2)pressione *"); 

while(aano==0)   {    
    char key = keypad.getKey();
     if (key != NO_KEY && (key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9' || key=='0'))
  {
    if(inicio == false)
      {num5 = num5 + key;
      int numLength = num5.length();
      lcd.setCursor(16-numLength,0);
      lcd.print(num5); 
      final = true;
      
     
  }
  
}
if (final == true && key !=NO_KEY && key == '*')
{
   aano=num5.toInt();    
}
 
}  
lcd.clear();
lcd.print(aano);  
delay(1000);

//--------------------------------------------------------------
//mostra no LCD o alarme que foi setado
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Alm. "); 
lcd.setCursor(5,0);  
lcd.print(adia); 
lcd.setCursor(7,0); 
lcd.print("/"); 
lcd.setCursor(8,0); 
lcd.print(ames); 
lcd.setCursor(10,0); 
lcd.print("/");  
lcd.print(aano);  


lcd.setCursor(5,1);    
lcd.print(ahora);
lcd.setCursor(7,1);  
lcd.print(":");  
lcd.setCursor(8,1);
lcd.print(aminuto);
//colocar um zero a frente quando for menor que 10 horas
if(ahora < 10){
  lcd.setCursor(5,1);
  lcd.print('0');
  lcd.print(ahora);}
  
//colocar um zero a frente quando for menor que 10 minutos
if(aminuto < 10){
  lcd.setCursor(8,1);
  lcd.print('0');
  lcd.print(aminuto);}

  //colocar um zero a frente quando o mes for menor que 10
  if(ames < 10){
  lcd.setCursor(8,0);
  lcd.print('0');
  lcd.print(ames);}

//colocar um zero a frente quando o dia for menor que 10
  if(adia < 10){
  lcd.setCursor(5,0);
  lcd.print('0');
  lcd.print(adia);}
  
delay(3000); 


}
//-------------------------------------------------------

void loop () {
    DateTime now = rtc.now();//mostra a hora e data atual do RTC
    
lcd.setCursor(0,0);  
lcd.print("Data ");
lcd.setCursor(5,0);
lcd.print(now.day(), DEC);
lcd.setCursor(7,0);
lcd.print('/');
lcd.setCursor(8,0);
lcd.print(now.month(), DEC);
lcd.setCursor(10,0);
lcd.print('/');
lcd.print(now.year(), DEC); 

 //------------------------------------- 
 //colocar um zero a frente quando o mês for menor que 10 
  int mes = now.month();
if(mes < 10){
  lcd.setCursor(8,0);
  lcd.print('0');
  lcd.print(now.month(), DEC);}
//------------------------------------- 

   lcd.setCursor(0,1);  
   lcd.print("Hora ");
   lcd.setCursor(5,1);
   lcd.print(now.hour(), DEC);
   lcd.setCursor(7,1);
   lcd.print(':');
   lcd.setCursor(8,1);
   lcd.print(now.minute(), DEC);
   lcd.setCursor(10,1);
   lcd.print(':');
   lcd.setCursor(11,1);
   lcd.print(now.second(), DEC);
    
//colocar um zero a frente quando for menor que 10 segundos
int sec = now.second();
if(sec < 10){
  lcd.setCursor(11,1);
  lcd.print('0');
  lcd.print(now.second(), DEC);
}
//----------------------------------
//colocar um zero a frente quando for menor que 10 horas
int hora = now.hour();
if(hora < 10){
  lcd.setCursor(5,1);
  lcd.print('0');
  lcd.print(now.hour(), DEC);
}
//----------------------------------
//colocar um zero a frente quando for menor que 10 minutos
int minuto = now.minute();
if(minuto < 10){
  lcd.setCursor(8,1);
  lcd.print('0');
  lcd.print(now.minute(), DEC);
}
//----------------------------------
int dia=now.day();
if(dia < 10){
  lcd.setCursor(5,0);
  lcd.print('0');
  lcd.print(now.day(), DEC);}
int ano=now.year();

estadomenu = digitalRead(menu);//Ler o estado do pino 2
 if(estadomenu == LOW)//Condição: se o valor do pino 2 for baixo, então faça:
      {
        lcd.clear();//mostra o dia da semana
        lcd.setCursor(0,0);  
        lcd.print("Dia da semana:");
        lcd.setCursor(0,1);  
        lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
        delay(3000);
        lcd.clear();
        }
estadoalarme = digitalRead(alarme);//Ler o estado do pino 10
 if(estadoalarme == LOW)//Condição: se o valor do pino 10 for baixo, então faça:
      {
//mostra no LCD o alarme que foi setado
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Alm. "); 
lcd.setCursor(5,0);  
lcd.print(adia); 
lcd.setCursor(7,0); 
lcd.print("/"); 
lcd.setCursor(8,0); 
lcd.print(ames); 
lcd.setCursor(10,0); 
lcd.print("/");  
lcd.print(aano);  


lcd.setCursor(5,1);    
lcd.print(ahora);
lcd.setCursor(7,1);  
lcd.print(":");  
lcd.setCursor(8,1);
lcd.print(aminuto);
//colocar um zero a frente quando for menor que 10 horas
if(ahora < 10){
  lcd.setCursor(5,1);
  lcd.print('0');
  lcd.print(ahora);}
  
//colocar um zero a frente quando for menor que 10 minutos
if(aminuto < 10){
  lcd.setCursor(8,1);
  lcd.print('0');
  lcd.print(aminuto);}

  //colocar um zero a frente quando o mes for menor que 10
  if(ames < 10){
  lcd.setCursor(8,0);
  lcd.print('0');
  lcd.print(ames);}

//colocar um zero a frente quando o dia for menor que 10
  if(adia < 10){
  lcd.setCursor(5,0);
  lcd.print('0');
  lcd.print(adia);}
  
delay(3000);


        }
     //compara o alarme com a hora atual, caso seja positivo, ativa o buzzer e desativa o relé   
if(minuto == aminuto && hora == ahora && dia == adia && mes == ames && ano == aano)
{  tone(buzzer,4000);
   delay(1000);
   digitalWrite(12,HIGH);
   digitalWrite(13,HIGH);
   noTone(buzzer);
   delay(1000);
    
   }

}
