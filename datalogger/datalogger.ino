/* Projeto: Fibra Nua 
   MC: Arduino UNO 
   Data: 30 ago 18 Hora: 09:00
   REFERÊNCIA: https://www.youtube.com/watch?v=zRlONKtpC8M&feature=youtu.be
   */

// --- Bibliotecas Auxiliares ---
#include <SD.h>                      //Biblioteca cartão SD


// --- Mapeamento de Hardware ---
#define CS_pin      10               //Comunicação SPI, CS_pin no digital 10
#define temp_pin    A0               //Sensor de temperatura no pino analógico 0
#define voltage_pin A1               //Sensor de tensão no pino analógico 1

// --- Protótipo das Funções Auxiliares ---
float AVG_TEMP();                  //Função para calcular a média de temperatura
float AVG_VOLTAGE();               //Função para calcular a média de tensão


// --- Variáveis Globais ---
const int voltage = 5;              //Alimentação do Arduino
const int celsius_unity = 100;      //Variação em Celsius
const int ad_resolution = 1023;     //Resolução do conversor AD utilizada (10 bits)

float temp_celsius;               //Variável de armazenamento
float ts_volts;

// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(9600);                     //Inicia comunicação serial com 9600 de baud rate
  Serial.println("Iniciando SD Card");    //Imprime frase
  
  pinMode(CS_pin, OUTPUT);                //Configura o pino CS como saída
  
  // -- Verifica se cartão SD está pronto --
  if(!SD.begin(CS_pin))
  {
    Serial.println("Falha ao abrir cartao SD");
    return;
  }
    
  Serial.println("Cartao SD iniciado com sucesso!");
  
  
  //Cria e escreve arquivo CSV
  File logFile = SD.open("LOG5.csv", FILE_WRITE);
  if(logFile)
  {
    logFile.println(","); // 
    String header = "T_Celsius, Voltage";
    logFile.println(header);
    logFile.close();
    Serial.println(header);
  } //end if logFile
  else
  {
    Serial.println("Erro ao abrir arquivo");
  }
  
} //end void setup


// --- Loop Infinito ---
void loop()
{
  //Cálculo de resolução AD e conversão Celsius ---------------- |
  temp_celsius = AVG_TEMP() * voltage * celsius_unity / ad_resolution;
  ts_volts = AVG_VOLTAGE() * voltage / ad_resolution;
  
  //Cria string de dados para armazenar no cartão SD
  //Utilizando arquivo do tipo Comma Separete Value
  String dataString = String(temp_celsius) + ", " + String(ts_volts);
  
  //Abre o arquivo para escrita
  //Apenas um arquivo pode ser aberto de cada vez
  File logFile = SD.open("LOG5.csv", FILE_WRITE);
  if(logFile)
  {
    logFile.println(dataString);
    logFile.close();
    Serial.println(dataString);
  } //end if logFile
  else
  {
    Serial.println("Erro ao abrir arquivo para escrita final");
  }
  
  delay(3000);
  

} //end void loop

float AVG_TEMP() //retorna a média entre 60 leituras de temperatura
{
  float temp_store = 0;
  
  for(int i=0; i<60; i++)
  {
    temp_store += analogRead(temp_pin);
  }
  
  return(temp_store/60);
}
float AVG_VOLTAGE() //retorna a média entre 60 leituras de tensão
{
  float ts_store = 0;
  
  for(int i=0; i<60; i++)
  {
    ts_store += analogRead(voltage_pin);
  }
  return(ts_store/60);
}
