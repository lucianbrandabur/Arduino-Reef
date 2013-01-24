//Write CR LF to a file

void writeCRLF(SdFile& f) 
{
  f.write((uint8_t*)"\r\n", 2);
}

void logtempgraf() //Grava dados no SD CARD para gerar  grafico de temperatura.
{
  char oldminuto1;
  oldminuto1 = time1;
  time1 = t.min;

  digitalWrite (4, LOW);  

  if (oldminuto1!=time1)
  {
    file.open(&root, "LOGTDIA.TXT", O_CREAT | O_APPEND | O_WRITE);

    if ((tempC<=1.0) || (tempC>99.9))
    {
      file.print("00.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.print(tempC);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGTDIA.TXT", O_WRITE);
    file.remove();
  } 
  digitalWrite (4, HIGH);  
}

void logphagraf() //Grava dados no SD CARD para gerar  gráfico de PH do aquário.
{ 
  char oldminuto2;
  oldminuto2 = time2;
  time2 = t.min;

  digitalWrite (4, LOW);

  if (oldminuto2!=time2)
  {
    if((PHA < 1.00) || (PHA > 9.99))
    {
      file.print("0.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.open(&root, "LOGPDIA.TXT", O_CREAT | O_APPEND | O_WRITE);   
      file.print(PHA);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGPDIA.TXT", O_WRITE);
    file.remove();
  } 
  digitalWrite (4, HIGH); 
}

void logphrgraf() //Grava dados no SD CARD para gerar  gráfico de PH do reator de calcio.
{
  char oldminuto3;
  oldminuto3 = time3;
  time3 = t.min;

  digitalWrite (4, LOW);

  if (oldminuto3!=time3)
  {
    if((PHR < 1.00) || (PHR > 9.99))
    {
      file.print("0.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.open(&root, "LOGRDIA.TXT", O_CREAT | O_APPEND | O_WRITE);   
      file.print(PHR);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGRDIA.TXT", O_WRITE);
    file.remove();
  }
  digitalWrite (4, HIGH);
}

void logorpgraf() //Grava dados no SD CARD para gerar  grafico de ORP.
{
  char oldminuto4;
  oldminuto4 = time4;
  time4 = t.min;

  digitalWrite (4, LOW);

  if (oldminuto4!=time4)
  {

    if ((ORP<=100) || (tempC>999))
    {
      file.print("000");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.open(&root, "LOGODIA.TXT", O_CREAT | O_APPEND | O_WRITE);   
      file.print(ORP);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGODIA.TXT", O_WRITE);
    file.remove();
  } 
  digitalWrite (4, HIGH); 
}

void logdengraf() //Grava dados no SD CARD para gerar  grafico de PH do aquario.
{
  char oldminuto5;
  oldminuto5 = time5;
  time5  = t.min;

  digitalWrite (4, LOW);

  if (oldminuto5!=time5)
  {
    if( (DEN<1000) || (DEN>9999))
    {
      file.print("0000");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {    
      file.open(&root, "LOGDDIA.TXT", O_CREAT | O_APPEND | O_WRITE);   
      file.print(DEN);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGDDIA.TXT", O_WRITE);
    file.remove();
  }
  digitalWrite (4, HIGH);   
}


void logparametros() //Grava parametros no SD CARD para consultas posteriores
{
  digitalWrite (4, LOW);

  file.open(&root, "LOGPAR.TXT", O_CREAT | O_APPEND | O_WRITE);
  file.print(rtc.getDateStr(FORMAT_SHORT)); 
  writeCRLF(file);
  file.print(rtc.getTimeStr(FORMAT_LONG));
  writeCRLF(file);
  file.print(tempC);
  writeCRLF(file);
  file.print(PHA);
  writeCRLF(file);
  file.print(PHR);
  writeCRLF(file);
  file.print(DEN);
  writeCRLF(file);
  file.print(ORP);
  writeCRLF(file);
  file.close();

  digitalWrite (4, HIGH);
}
