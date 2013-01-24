/*
 * Este programa lista os arquivos armazenados no cartão SD.
 */

#include <SdFat.h>
#include <SdFatUtil.h>
const int chipselect = 4; // Altera para 53 caso esteja usando o leitor do LCD.

/************ SDCARD ************/
Sd2Card card;
SdVolume volume;
SdFile root;

// Armazenar seqüências de erros na flash para economizar memória RAM

#define error(s) error_P(PSTR(s))

void error_P(const char* str) {
  PgmPrint("Erro: ");
  SerialPrintln_P(str);
  if (card.errorCode()) {
    PgmPrint("SD Erro: ");
    Serial.print(card.errorCode(), HEX);
    Serial.print(',');
    Serial.println(card.errorData(), HEX);
  }
  while(1);
}

void setup() {
  Serial.begin(38400);
 
  PgmPrint("Memoria livre: ");
  Serial.println(FreeRam());  
  
  if (!card.init(SPI_HALF_SPEED, chipselect)) error("card.init falhou!");
  
  // Inicia um volume FAT 
  if (!volume.init(&card)) error("vol.init Falhou!");

  PgmPrint("Volume e FAT");
  Serial.println(volume.fatType(),DEC);
  Serial.println();
  
  if (!root.openRoot(&volume)) error("openRoot falhou!");

  // Lista arquivos na raiz com data e tamanho.
  PgmPrintln("Arquivos encontrados na raiz:");
  root.ls(LS_DATE | LS_SIZE);
  Serial.println();
  
  // Lista todos os arquivos encontrados
  PgmPrintln("Arquivos encontrados em todos os diretorios:");
  root.ls(LS_R);
  
  Serial.println();
  PgmPrintln("Concluido");
}
void loop()
{
}
