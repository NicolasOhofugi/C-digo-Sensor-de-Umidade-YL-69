/*BRASÍLIA, 16/07/2018; 16/11/2018 (Ultima Atualização) (Verificado)
/*
PROGRAMA: 4 Sensores de Umidade com LED's
Resistências dos leds : 1200 ohm (Marrom - Vermelho - Vermelho)
SD Card Ligado em 3.3V
Sensor de Umidade ligado em 5V
Sensor 1 ligado em 4cm - A0
Sensor 2 ligado em 13cm - A1
Sensor 3 ligado em 22cm - A2
Sensor 4 lingado em -- - A3
//Autor: Nícolas Ohofugi
*/

#include <SPI.h>         //Biblioteca do SD Card
#include <SD.h>          //Biblioteca do SD Card
#include <Wire.h>        //Biblioteca para manipulação do protocolo I2C
#include "RTClib.h"      //Biblioteca para manipulação do DS1307

#define sensor_1 A0                //Definindo Sensor de Umidade no pino analógico A0 - 4cm
#define sensor_2 A1                //Definindo Sensor de Umidade no pino analógico A1 - 13cm
#define sensor_3 A2                //Definindo Sensor de Umidade no pino analógico A2 - 22cm
#define sensor_4 A3                //Definindo Sensor de Umidade no pino analógico A3 - --cm
#define pino_led_vermelho_1 31        //Definindo Led Vemelho do sensor 1 no pino digital 31
#define pino_led_amarelo_1 32         //Definindo Led Amarelo do sensor 1 no pino digital 32
#define pino_led_verde_1 33           //Definindo Led Verde do sensor 1 no pino digital 33
#define pino_led_vermelho_2 25        //Definindo Led Vemelho do sensor 2 no pino digital 25
#define pino_led_amarelo_2 24         //Definindo Led Amarelo do sensor 2 no pino digital 24
#define pino_led_verde_2 23           //Definindo Led Verde do sensor 2 no pino digital 23
#define pino_led_vermelho_3 36        //Definindo Led Vemelho do sensor 3 no pino digital 36
#define pino_led_amarelo_3 37         //Definindo Led Amarelo do sensor 3 no pino digital 37
#define pino_led_verde_3 38           //Definindo Led Verde do sensor 3 no pino digital 38
#define pino_led_vermelho_4 41        //Definindo Led Vemelho do sensor 4 no pino digital 41
#define pino_led_amarelo_4 42         //Definindo Led Amarelo do sensor 4 no pino digital 42
#define pino_led_verde_4 43           //Definindo Led Verde do sensor 4 no pino digital 43


int valor_analogico;
int valor_analogico_2;
int valor_analogico_3;
int valor_analogico_4;
const int chipSelect = 53;
int numero = 0;

RTC_DS1307 rtc;            //Criação do objeto do tipo DS1307
//char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};

File myFile;

void setup() {
 
  Serial.begin(9600);             //Inicialização da comunicação serial
  rtc.begin();                    //Inicialização do RTC DS3231
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  pinMode(sensor_3, INPUT);
  pinMode(sensor_4, INPUT);
  pinMode(pino_led_vermelho_1, OUTPUT);
  pinMode(pino_led_amarelo_1, OUTPUT);
  pinMode(pino_led_verde_1, OUTPUT);
  pinMode(pino_led_vermelho_2, OUTPUT);
  pinMode(pino_led_amarelo_2, OUTPUT);
  pinMode(pino_led_verde_2, OUTPUT);
  pinMode(pino_led_vermelho_3, OUTPUT);
  pinMode(pino_led_amarelo_3, OUTPUT);
  pinMode(pino_led_verde_3, OUTPUT);
  pinMode(pino_led_vermelho_4, OUTPUT);
  pinMode(pino_led_amarelo_4, OUTPUT);
  pinMode(pino_led_verde_4, OUTPUT);

  rtc.adjust(DateTime(2019, 02, 20, 11, 00, 0));   //Configurando valores iniciais 
                                                 //do RTC DS3231
  
  while (!Serial) {
    ; // Esperando a comunicação serial com a porta USB. 
  }

  Serial.print("Initializing SD Card...");

  if (!SD.begin(53)) {
    Serial.println("Initialization failed!");
    while (1);
  }
  else {
  Serial.println("Initialization done.");
  }
  if (SD.exists("C4SU.txt")) {
    Serial.println("C4SU.txt exists.");
  } else {
    Serial.println("C4SU.txt doesn't exists.");
  }
   // Escrevendo no SD Card e no Monitor Serial
  myFile = SD.open("C4SU.txt", FILE_WRITE);
  Serial.print("N. Leituras:        ");
  myFile.print("N. Leituras:      ");
  Serial.print("Data:            ");
  myFile.print("Data:            ");
  Serial.print("Hora:            ");
  myFile.print("Hora:            ");
  Serial.print("Sensor 1:            ");
  myFile.print("Sensor 1:            ");
  Serial.print("Sensor 2:            ");
  myFile.print("Sensor 2:       0     ");
  Serial.print("Sensor 3:        ");
  myFile.print("Sensor 3:        ");
  Serial.println("Sensor 4:        ");
  myFile.println("Sensor 4:        ");
  myFile.close();
}

void loop() {
    DateTime now = rtc.now();     //Atribuindo valores instantâneos de 
                                       //data e hora à instância dataehora
    myFile = SD.open("C4SU.txt", FILE_WRITE);
  
     valor_analogico = analogRead(sensor_1);       //Le o valor do pino A0 do sensor
     valor_analogico_2 = analogRead(sensor_2);       //Le o valor do pino A1 do sensor
     valor_analogico_3 = analogRead(sensor_3);       //Le o valor do pino A2 do sensor
     valor_analogico_4 = analogRead(sensor_4);       //Le o valor do pino A3 do sensor

      Serial.print(numero);
      Serial.print("                  ");
      Serial.print(now.year(), DEC);     //Imprimindo o Ano   
      Serial.print("/");
      Serial.print(now.month(), DEC);    //Imprimindo o Mês
      Serial.print("/");
      Serial.print(now.day(), DEC);      //Imprimindo o Dia
      //Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);     //Imprimindo o dia da Semana
      Serial.print("        ");
      Serial.print(now.hour(), DEC);     //Imprimindo a Hora
      Serial.print(":");
      Serial.print(now.minute(), DEC);   //Imprimindo o Minuto
      Serial.print(":");
      Serial.print(now.second(), DEC);   //Imprimindo o Segundo
      Serial.print("              ");
      Serial.print(valor_analogico);       //Grava dados no Serial Monitor 
      Serial.print("                 ");
      Serial.print(valor_analogico_2);     //Grava dados no Serial Monitor 
      Serial.print("                 ");
      Serial.print(valor_analogico_3);   //Grava dados no Serial Monitor
      Serial.print("                 ");
      Serial.println(valor_analogico_4);   //Grava dados no Serial Monitor  
      myFile.print(numero);
      myFile.print("                    ");
      myFile.print(now.year(), DEC);     //Imprimindo o Ano   
      myFile.print("/");
      myFile.print(now.month(), DEC);    //Imprimindo o Mês
      myFile.print("/");
      myFile.print(now.day(), DEC);      //Imprimindo o Dia
      //myFile.print(daysOfTheWeek[now.dayOfTheWeek()]);     //Imprimindo o dia da Semana
      myFile.print("        ");
      myFile.print(now.hour(), DEC);      //Imprimindo a Hora
      myFile.print(":");
      myFile.print(now.minute(), DEC);   //Imprimindo o Minuto
      myFile.print(":");
      myFile.print(now.second(), DEC);   //Imprimindo o Segundo
      myFile.print("              ");
      myFile.print(valor_analogico);  //Grava dados da porta analógica no arquivo
      myFile.print("                 ");
      myFile.print(valor_analogico_2);  //Grava dados da porta analógica no arquivo
      myFile.print("                 ");
      myFile.print(valor_analogico_3);  //Grava dados da porta analógica no arquivo
      myFile.print("                 ");
      myFile.println(valor_analogico_4);  //Grava dados da porta analógica no arquivo
      
//----------------------------------------SENSOR 1---------------------------------------------------------     
    //Solo umido, acende o led verde do sensor 1
    if (valor_analogico > 0 && valor_analogico < 440)
    {
      apagaleds1();
      digitalWrite(pino_led_verde_1, HIGH);}
   
    //Solo com umidade moderada, acende led amarelo do sensor 1
    if (valor_analogico > 440 && valor_analogico < 880)
    {
      apagaleds1();
      digitalWrite(pino_led_amarelo_1, HIGH);}
   
    //Solo seco, acende led vermelho do sensor 1
    if (valor_analogico > 880 && valor_analogico < 1024)
    {
      apagaleds1();
      digitalWrite(pino_led_vermelho_1, HIGH);}
      

//----------------------------------------SENSOR 2-------------------------------------------------------------------
    //Solo umido, acende o led verde do sensor 
    if (valor_analogico_2 > 0 && valor_analogico_2 < 440)
    {
      apagaleds2();
      digitalWrite(pino_led_verde_2, HIGH);}
   
    //Solo com umidade moderada, acende led amarelo do sensor 2
    if (valor_analogico_2 > 440 && valor_analogico_2 < 880)
    {
      apagaleds2();
      digitalWrite(pino_led_amarelo_2, HIGH);}
   
    //Solo seco, acende led vermelho do sensor 2
    if (valor_analogico_2 > 880 && valor_analogico_2 < 1024)
    {
      apagaleds2();
      digitalWrite(pino_led_vermelho_2, HIGH);}
      

//----------------------------------------SENSOR 3------------------------------------------------------------------
    //Solo umido, acende o led verde do sensor 3
    if (valor_analogico_3 > 0 && valor_analogico_3 < 440)
    {
      apagaleds3();
      digitalWrite(pino_led_verde_3, HIGH);}
   
    //Solo com umidade moderada, acende led amarelo do sensor 3
    if (valor_analogico_3 > 440 && valor_analogico_3 < 880)
    {
      apagaleds3();
      digitalWrite(pino_led_amarelo_3, HIGH);}
   
    //Solo seco, acende led vermelho do sensor 3
    if (valor_analogico_3 > 880 && valor_analogico_3 < 1024)
    {
      apagaleds3();
      digitalWrite(pino_led_vermelho_3, HIGH);}

//----------------------------------------SENSOR 4------------------------------------------------------------------
    //Solo umido, acende o led verde do sensor 4
    if (valor_analogico_4 > 0 && valor_analogico_4 < 440)
    {
      apagaleds4();
      digitalWrite(pino_led_verde_4, HIGH);}
   
    //Solo com umidade moderada, acende led amarelo do sensor 4
    if (valor_analogico_4 > 440 && valor_analogico_4 < 880)
    {
      apagaleds4();
      digitalWrite(pino_led_amarelo_4, HIGH);}
   
    //Solo seco, acende led vermelho do sensor 4
    if (valor_analogico_4 > 880 && valor_analogico_4 < 1024)
    {
      apagaleds4();
      digitalWrite(pino_led_vermelho_4, HIGH);}

//-------------------------------------------DELAY-------------------------------------------------------------
    delay(5000);                  //Tempo para atualização do valor enviado pela porta serial
    numero = numero + 1;
    myFile.close();
}

void apagaleds1()
{
  digitalWrite(pino_led_vermelho_1, LOW);
  digitalWrite(pino_led_amarelo_1, LOW);
  digitalWrite(pino_led_verde_1, LOW);}

void apagaleds2(){
  digitalWrite(pino_led_vermelho_2, LOW);
  digitalWrite(pino_led_amarelo_2, LOW);
  digitalWrite(pino_led_verde_2, LOW);}

void apagaleds3(){
  digitalWrite(pino_led_vermelho_3, LOW);
  digitalWrite(pino_led_amarelo_3, LOW);
  digitalWrite(pino_led_verde_3, LOW);}

void apagaleds4(){
  digitalWrite(pino_led_vermelho_4, LOW);
  digitalWrite(pino_led_amarelo_4, LOW);
  digitalWrite(pino_led_verde_4, LOW);}
