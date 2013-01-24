//-----------------------main loop------------------------------
void loop()
{
   t = rtc.getTime(); // Atualiza as variáveis que usam o RTC.
  /*  int valor1=0;
   int valor2=0;
   int valor3=0;
   int valor4=0;
   int valor5=0;
   int valor6=0;
   
   valor1 = analogRead(sensor1);
   valor2 = analogRead(sensor2);
   valor3 = analogRead(sensor3);
   valor4 = analogRead(sensor4);
   valor5 = analogRead(sensor5);
   valor6 = analogRead(sensor6);*/

  if (millis() - previousMillis > 5000)    // Verifica as funções a cada 5 segundos.
  {
    previousMillis = millis();  
    checkTempC(); // Verifica as temperaturas.
    min_cnt= NumMins(t.hour,t.min); // Atualiza o intervalo para determinar a potência dos leds.
    LED_levels_output(); // Atualiza a potência de saída dos leds
    reposicao_agua_doce(); // Verifica se há a necessidade reposição da água doce.
    check_nivel(); // Verifica se há algum problema com os níveis dos aquários.
    check_PH_reator(); // Verifica o PH do reatpr de cálcio.
    check_PH_aquario(); // Verifica o PH do aquário.
    check_densidade(); // Verifica a densidade.
    check_ORP(); // Verifica o ORP;
    check_alarme(); // Verifica os alarmes.
    check_temporizadores(); // Ativa ou desativa os timers.

    if (dispScreen == 0)
    {
      mainScreen();  // Atualiza tela inicial.  
    }

    
    /*
     Serial.println("Dia da semana");  
     Serial.println(rtc.getDOWStr()); 
     
     Serial.println("Horario");
     Serial.println(rtc.getTimeStr(FORMAT_LONG));*/

    Serial.print ("Memoria livre:");
    Serial.println (FreeRam());

/*     Serial.println("Sensor 1:");    
     Serial.println(valor1);
     
     Serial.println("Sensor 2:");
     Serial.println(valor2);
     
     Serial.println("Sensor 3:");
     Serial.println(valor3);
     
     Serial.println("Sensor 4:");
     Serial.println(valor4);
     
     Serial.println("Sensor 5:");    
     Serial.println(valor5);      
     
     Serial.println("Sensor 6:");
     Serial.println(valor6);
     
     Serial.println("marcadoriniciotpa:");
     Serial.println(marcadoriniciotpa);
     
     Serial.println("shiftedmillis:");
     Serial.println(shiftedmillis);
     
     Serial.println("Tempo:");
     Serial.println(tempo);
     
     if (digitalRead(bomba1Pin)==HIGH)
     {
     Serial.println("Bomba1: ligada");
     }
     else
     {
     Serial.println("Bomba1: desligada");
     }
     if (digitalRead(bomba2Pin)==HIGH)
     {
     Serial.println("Bomba2: ligada");
     }
     else
     {
     Serial.println("Bomba2: desligada");
     }
     if (digitalRead(bomba3Pin)==HIGH)
     {
     Serial.println("Bomba3: ligada");
     }
     else
     {
     Serial.println("Bomba3: desligada");
     }*/
  }
  checktpa(); // Verifica e executa a TPA automática.
  check_status(); // Atualiza os valores para envio ao cosm.com.
  logtempgraf(); // Grava temperatura no cartão SD.
  logphagraf(); // Grava o PH do aquário no cartão SD.
  logphrgraf(); // Grava o PH do reator de cálcio no cartão SD.
  logdengraf(); // Grava densidade no cartão SD.
  logorpgraf(); // Grava o ORP no cartão SD.
  
   if(Ethernet_Shield == true)
  {
    ether.packetLoop(ether.packetReceive()); // Envie e recebe os dados da internet.
  }

  if (myTouch.dataAvailable())  
  { 
    processMyTouch();  // Verifica se o LCD está sendo tocado e faz o processamento.
  }

  if(Stamps == true)
  {
    if((millis() - millis_antes) >= 120000) // Executa as funções a cada 2 minutos.
    {
    millis_antes = millis();        
   parametros(); // Verifica os "stamps".
    }
  }

  if((Ethernet_Shield == true) && (tpa_em_andamento == false)) // Condições para o envio de dados para o cosm.com.
  {
    cosm (); // Envia dados para o cosm.com.
  }

  if (millis() - logtempminutoantes > 300000) // Grava parametros a cada 5 minutos no cartao SD.
  {
    logtempminutoantes = millis();
    logparametros();// Grava todos parêmtros no cartão SD.
  }
  if(dosadoras == true) // Verifica e executa as dosagens.
  {
  check_dosagem_automatica_1(); // Dosadora 1 - Dosagem automática automática
  check_dosagem_personalizada_1(); // Dosadora 1 - Dosagem personalizado
  check_dosagem_automatica_2(); // Dosadora 2 - Dosagem automática
  check_dosagem_personalizada_2(); // Dosadora 2 - Dosagem personalizado
  check_dosagem_automatica_3(); // Dosadora 3 - Dosagem automática
  check_dosagem_personalizada_3(); //Dosadora 3 - Dosagem personalizado
  check_dosagem_automatica_4(); // Dosadora 4 - Dosagem automática automática
  check_dosagem_personalizada_4(); // Dosadora 4 - Dosagem personalizado
  check_dosagem_automatica_5(); // Dosadora 5 - Dosagem automática
  check_dosagem_personalizada_5(); // Dosadora 5 - Dosagem personalizado
  check_dosagem_automatica_6(); // Dosadora 6 - Dosagem automática
  check_dosagem_personalizada_6(); //Dosadora 6 - Dosagem personalizado
  }
} //-------------------end of main loop
