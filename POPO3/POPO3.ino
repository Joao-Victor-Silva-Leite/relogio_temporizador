#include "Wire.h"

#define DS1307_ADDRESS 0x68

int segundos;
int minutos;
int horas;
int diadasemana;
int diadomes;
int mes;
int ano;

byte zero = 0x00;

int rele = 7;

bool cafeteiraLigada;

void setup()
{
pinMode(rele, OUTPUT);
digitalWrite(rele, HIGH);
cafeteiraLigada = false;
Wire.begin();
Serial.begin(9600);
}

byte ConverteParaBCD(byte val){ //Converte o número de decimal para BCD
return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val) { //Converte de BCD para decimal
return ( (val/16*10) + (val%16) );
}

void Mostrarelogio()
{
Wire.beginTransmission(DS1307_ADDRESS);
Wire.write(zero);
Wire.endTransmission();
Wire.requestFrom(DS1307_ADDRESS, 7);
int segundos = ConverteparaDecimal(Wire.read());
int minutos = ConverteparaDecimal(Wire.read());
int horas = ConverteparaDecimal(Wire.read() & 0b111111);
int diadasemana = ConverteparaDecimal(Wire.read());
int diadomes = ConverteparaDecimal(Wire.read());
int mes = ConverteparaDecimal(Wire.read());
int ano = ConverteparaDecimal(Wire.read());
//Mostra a data no Serial Monitor
Serial.print("Data: ");
Serial.print(diadomes);
Serial.print("/");
Serial.print(mes);
Serial.print("/");
Serial.print(ano);
Serial.print(" ");
Serial.print("Hora : ");
Serial.print(horas);
Serial.print(":");
Serial.print(minutos);
Serial.print(":");
Serial.print(segundos);
switch(diadasemana)
{
case 0:Serial.println(", Domingo");
break;
case 1:Serial.println(", Segunda");
break;
case 2:Serial.println(", Terca");
break;
case 3:Serial.println(", Quarta");
break;
case 4:Serial.println(", Quinta");
break;
case 5:Serial.println(", Sexta");
break;
case 6:Serial.println(", Sabado");
}

if ((horas >= 6) and (minutos >= 15)) {
    digitalWrite(rele, LOW);
}

}

void loop()
{
Mostrarelogio();
delay(1000);
}
