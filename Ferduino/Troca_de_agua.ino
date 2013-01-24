void checktpa()
{
  tempo = (duracaomaximatpa * 60000ul);

  if ((segunda==t.dow) && (hora==t.hour) && (minuto==t.min) && (t.sec<=5) && (falha_tpa == false))
  {
    tpa=1;
    if ((4294967295ul - tempo) < millis())
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }

  if ((terca==t.dow) && (hora==t.hour) && (minuto==t.min) && (t.sec<=5))
  {
    tpa=1;
    if ((4294967295ul - tempo) < millis())
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }

  if ((quarta==t.dow) && (hora==t.hour) && (minuto==t.min) && (t.sec<=5))
  {
    tpa=1;
    if ((4294967295ul - tempo) < millis())
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }

  if ((quinta==t.dow) && (hora==t.hour) && (minuto==t.min) && (t.sec<=5))
  {
    tpa=1;
    if ((4294967295ul - tempo) < millis())
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }

  if ((sexta==t.dow) && (hora==t.hour) && (minuto==t.min) && (t.sec<=5))
  {
    tpa=1;
    if ((4294967295ul - tempo) < millis())
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }

  if ((sabado==t.dow) && (hora==t.hour) && (minuto==t.min) && (t.sec<=5))
  {
    tpa=1;
    if ((4294967295ul - tempo) < millis())
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }

  if ((domingo==t.dow) && (hora==t.hour) && (minuto==t.min) && (t.sec<=5))
  {
    tpa=1;
    if ((4294967295ul - tempo) < millis())
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }

  if ((4294967295ul - tempo) < millis())
  {
    shiftedmillis= millis() - (tempo*2);
  }
  else
  {
    shiftedmillis= millis();
  }

  if ((analogRead(sensor1)<100) && (analogRead(sensor2)>400) && (analogRead(sensor3)<100) && tpa==1 && (analogRead(sensor4)>400) && ((shiftedmillis - marcadoriniciotpa) < tempo))
  {
    digitalWrite(bomba1Pin,HIGH); //estagio 1
    digitalWrite(bomba2Pin,LOW);
    digitalWrite(bomba3Pin,LOW);
    tpa=2;
    tpa_em_andamento =true;
    if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }
  else if ((analogRead(sensor1)>400) && (analogRead(sensor2)>400) && tpa==2 && ((shiftedmillis - marcadoriniciotpa) < tempo))
  {
    digitalWrite(bomba1Pin,LOW); //estagio 2
    digitalWrite(bomba2Pin,HIGH);
    digitalWrite(bomba3Pin,LOW);
    tpa=3;
    tpa_em_andamento =true;
    if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }
  else if ((analogRead(sensor2)<100) && (analogRead(sensor1)==0) && (analogRead(sensor3)>400) && tpa==3 && ((shiftedmillis - marcadoriniciotpa) < tempo))
  {
    digitalWrite(bomba1Pin,LOW); // estagio 3
    digitalWrite(bomba2Pin,LOW);
    digitalWrite(bomba3Pin,HIGH);
    tpa=4;
    tpa_em_andamento =true;
    if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }
  else if ((analogRead(sensor3)<100) && (analogRead(sensor2)>400) && (analogRead(sensor1)<100) && tpa==4 && ((shiftedmillis - marcadoriniciotpa) < tempo))
  {
    digitalWrite(bomba1Pin,LOW); // estagio 0
    digitalWrite(bomba2Pin,LOW);
    digitalWrite(bomba3Pin,LOW);
    tpa_em_andamento = false;
  }
  else if (((shiftedmillis - marcadoriniciotpa) >= tempo) && (tpa_em_andamento == true))
  {
    digitalWrite(bomba1Pin,LOW); //desliga as bombas todas e mete tpa=0 para não entrar no ciclo outra vez
    digitalWrite(bomba2Pin,LOW);
    digitalWrite(bomba3Pin,LOW);
    tpa=0;
    tpa_em_andamento = false;
    falha_tpa = true;
  }
}

