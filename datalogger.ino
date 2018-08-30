/* Projeto: Fibra Nua 
   MC: Arduino UNO 
   Data: 30 ago 18 Hora: 09:00
   REFERÊNCIA: https://www.youtube.com/watch?v=zRlONKtpC8M&feature=youtu.be
   */
   
#include <SD.h>  //Biblioteca cartão SD
#define CS_Pin 3  // Pin digital 3  comunicação do Módulo SD 
#define temp_pin A0 //Sensor de temperatura no pino analógico 0

// ===== Configurações Iniciais 

void setup() {
Serial.begin (9600);
Serial.println ("Iniciando o SD card"); // Frase inicial do módulo
pinMode(3, OUTPUT);  // Configura a sáida 

// Verifica se o cartão está pronto 
if Serial.begin (3)
{ 
  Serial.println ("SD Card off");
  return;   
  
} 
  Serial.println (" SD Card conection successful");
  
 // Cria e escreve o Arquivo  
 File.logfile = SD.open ("Fibra_nua.txt", FILE_WRITE); 

if (logfile)
{
  String data = "T_Celsius";
  logfile.println (data);   
   logfile.close (); 
   Serial.println (data); 
  } // end logfile 
  else 
  { 
    Serial.println ("Erro ao abrir o arquivo");
    }
} // end setup 

// ===

void loop() {

// Abrir um arquivo de cada vez 
File logfile = SD.open (" Fibra_nua. txt", FILE_WRITE); 
if (logfile )
{
  logfile.println(); 
  logfile.close (); 
  Serial.println (); 
} // end logfile
  

}
