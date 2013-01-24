//------------------------------------- Leitura dos stamps
void parametros()
{
  int i;
  do{
    Open_channel(ph1);
    Serial2.print(tempC); //Para se obter um valor compensado pode-se enviar um valor de temperatura da água.
    Serial2.print('\r');
    delay(500);

    if(Serial2.available() > 3) 
    {
      holding = Serial2.available();
      for(i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial2.read();
      }

      if(holding ==5)
      {
        PHT = ((sensorstring[1]-48)*100 + (sensorstring[3]-48)*10 + (sensorstring[4]-48));
        PHA = PHT/100;
      }
      else
      {
        PHT = ((sensorstring[1]-48)*1000 + (sensorstring[2]-48)*100 + (sensorstring[4]-48)*10 + (sensorstring[5]-48));
        PHA = PHT/100;
      }  
      PHT=0;
      Serial2.flush();
      break;
    }
  } 
  while (done==1);
  done=0;

  do{
    Open_channel(ph2);
    Serial2.print(tempC); //Para se obter um valor compensado pode-se enviar um valor de temperatura da água.
    Serial2.print('\r');
    delay(500);

    if(Serial2.available() > 3) 
    {
      holding = Serial2.available();
      for(i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial2.read();
      }
      if(holding ==5)
      {
        PHT = ((sensorstring[1]-48)*100 + (sensorstring[3]-48)*10 + (sensorstring[4]-48));
        PHR = PHT/100;
      }
      else
      {
        PHT = ((sensorstring[1]-48)*1000 + (sensorstring[2]-48)*100 + (sensorstring[4]-48)*10 + (sensorstring[5]-48));
        PHR = PHT/100;
      }  
      PHT=0;
      Serial2.flush();
      break;
    }

  } 
  while (done==1);
  done=0;

  do{
    Open_channel(orp);
    Serial2.print("r"),
    Serial2.print('\r');
    delay(500);

    if(Serial2.available() > 3) 
    {
      holding = Serial2.available();
      for(i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial2.read();
      }

      ORPT = ((sensorstring[1]-48)*100 + (sensorstring[2]-48)*10 + (sensorstring[3]-48));
      ORP = ORPT; 
      ORPT=0;
      Serial2.flush();      
      break;
    }
  } 
  while (done==1);
  done=0;
/*
  do{
    Open_channel(ec);
    Serial2.print(tempC); //Para se obter um valor compensado pode-se enviar um valor de temperatura da água.
    Serial2.print('\r');
    delay(500);
    if(Serial2.available() > 3) 
    {
      Serial.print("Densidade:");
      holding = Serial2.available();
      for(i=1; i <= 15; i++)
      {
        sensorstring[i]= Serial2.read();
        Serial.print(sensorstring[i]);
      }
      Serial.println();
      Serial2.flush();
      break;
    }  
  } 
  while (done==1);
  done=0;
*/
}

void Open_channel(short channel)
{
  switch (channel) 
  {
  case 0:
    //open channel Y0
    //S0=0
    //S1=0
    digitalWrite(multiplexadorS0Pin, LOW);
    digitalWrite(multiplexadorS1Pin, LOW);
    break;

  case 1:
    //open channel Y1
    //S0=1
    //S1=0
    digitalWrite(multiplexadorS0Pin, HIGH);
    digitalWrite(multiplexadorS1Pin, LOW);
    break;

  case 2:
    //open channel Y2
    //S0=0
    //S1=1
    digitalWrite(multiplexadorS0Pin, LOW);
    digitalWrite(multiplexadorS1Pin, HIGH);
    break;

  case 3:
    //open channel Y3
    //S0=1
    //S1=1
    digitalWrite(multiplexadorS0Pin, HIGH);
    digitalWrite(multiplexadorS1Pin, HIGH);
    break;
  }
  Serial2.print('\r');
  return;
}
