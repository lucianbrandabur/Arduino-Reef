//------------------------setup------------------------------
void setup()
{
  Serial.begin(38400); //Inicia a comunicação com a  porta serial 0 para obter mensagens de depuração.
  Serial2.begin(38400); //Inicia a comunicação com a  porta serial 2 onde estão conectados os "stamps".
  pinMode(ledPinBlue, OUTPUT);
  pinMode(ledPinWhite, OUTPUT);
  pinMode(ledPinMoon, OUTPUT); 
  pinMode(aquecedorPin, OUTPUT);
  pinMode(chillerPin, OUTPUT);
  pinMode(alarmPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(bomba1Pin, OUTPUT);
  pinMode(bomba2Pin, OUTPUT);
  pinMode(bomba3Pin, OUTPUT);
  pinMode(reatorPin, OUTPUT);
  pinMode(ozonizadorPin, OUTPUT);
  pinMode(solenoide1Pin, OUTPUT);
  pinMode(multiplexadorS0Pin, OUTPUT);
  pinMode(multiplexadorS1Pin, OUTPUT);
  pinMode (4, OUTPUT);  //sd card
  digitalWrite (4, HIGH);
  pinMode (dosadora1, OUTPUT);
  pinMode (dosadora2, OUTPUT);
  pinMode (dosadora3, OUTPUT);
  pinMode (dosadora4, OUTPUT);
  pinMode (dosadora5, OUTPUT);
  pinMode (dosadora6, OUTPUT);
  pinMode (temporizador1, OUTPUT);
  pinMode (temporizador2, OUTPUT);
  pinMode (temporizador3, OUTPUT);
  pinMode (temporizador4, OUTPUT);
  pinMode (temporizador5, OUTPUT);

  myGLCD.InitLCD(LANDSCAPE); // Orientação da imagem no LCD.
  myGLCD.clrScr(); // Limpa o LCD.

  myTouch.InitTouch(LANDSCAPE); // Orientação do "touch screen".
  myTouch.setPrecision(PREC_MEDIUM); // Define a precisão do "touch screen".

  sensors.begin();     //Inicia as leituras das sondas de temperatura.
  sensors.setResolution(sensor_agua, 10); // Define a resolução em 10 bits.
  sensors.setResolution(sensor_dissipador, 10); // Define a resolução em 10 bits.

  if(Ethernet_Shield == true)
  {
    if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) // Inicia a comunicação com o "ethernet shield".
    {
      Serial.println( "Failed to access Ethernet controller");
    }
    ether.staticSetup(myip,gwip); // Seta o IP e o "Gateway".
  }

  rtc.halt(false); // Inicia o funcionamento do RTC.
  
  //Lê a variáveis guardadas na EEPROM.
  ReadFromEEPROM();
  lertpaEEPROM();
  lerPHAEEPROM();
  lerPHREEPROM();
  lerORPEEPROM();
  lerDENEEPROM();
  ler_dosadora_EEPROM();
  ler_luz_noturna_EEPROM();
  ler_timers_EEPROM();
  
  card.init(SPI_QUARTER_SPEED,chipselect); // Inicia a comunicação com o cartão SD.
  volume.init(&card);
  root.openRoot(&volume);
  
  mainScreen(true); // Exibe a tela inicial no LCD.
  
  Open_channel(ph1); 
  delay(50);
  Serial2.print("e"); // Envia um comando para que o "stamp" pare de enviar as leituras.
  Serial2.print('\r');
  delay(1000);
  Serial2.flush();
  Serial2.print("L0"); // Envia um comando para que o "stamp" apague o led de depuração.
  Serial2.print('\r');
  delay(1000);
  Open_channel(ph2);
  delay(50);
  Serial2.print("e"); // Envia um comando para que o "stamp" pare de enviar as leituras.
  Serial2.print('\r');
  delay(1000);
  Serial2.flush();
  Serial2.print("L0"); // Envia um comando para que o "stamp" apague o led de depuração.
  Serial2.print('\r');
  delay(1000);
  Open_channel(orp);
  delay(50);
  Serial2.print("e"); // Envia um comando para que o "stamp" pare de enviar as leituras.
  Serial2.print('\r');
  delay(1000);
  Serial2.flush();
  Serial2.print("L0"); // Envia um comando para que o "stamp" apague o led de depuração.
  Serial2.print('\r');
  delay(1000);    
  Open_channel(ec);
  delay(50);
  Serial2.print("e"); // Envia um comando para que o "stamp" pare de enviar as leituras.
  Serial2.print('\r');
  delay(1000);
  Serial2.flush();
  Serial2.print("L0"); // Envia um comando para que o "stamp" apague o led de depuração.
  Serial2.print('\r');
  delay(1000);

}

