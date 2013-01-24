//**********************************************************************************************
//********************** Funcoes fase da lua* **************************************************
//**********************************************************************************************
float moonPhase(int moonYear, int moonMonth, int moonDay)
{ 
  float phase;
  double IP; 
  long YY, MM, K1, K2, K3, JulianDay; 
  YY = moonYear - floor((12 - moonMonth) / 10); 
  MM = moonMonth + 9;
  if (MM >= 12)
  { 
    MM = MM - 12; 
  }
  K1 = floor(365.25 * (YY + 4712));
  K2 = floor(30.6 * MM + 0.5);
  K3 = floor(floor((YY / 100) + 49) * 0.75) - 38;
  JulianDay = K1 + K2 + moonDay + 59;
  if (JulianDay > 2299160)
  { 
    JulianDay = JulianDay - K3; 
  }
  IP = MyNormalize((JulianDay - 2451550.1) / LC);
  AG = IP*LC;
  phase = 0; 

  //Determine the Moon Illumination %
  if ((AG >= 0) && (AG <= LC/2))            //FROM New Moon 0% TO Full Moon 100%
  { 
    phase = (2*AG)/LC; 
  }
  if ((AG > LC/2) && (AG <= LC))            //FROM Full Moon 100% TO New Moon 0%
  { 
    phase = 2*(LC-AG)/LC; 
  }
  //Determine the Lunar Phase
  if ((AG >= 0) && (AG <= 5.54))         // 0 a 35%        
  { 
    LP = tabela_textos[67];  // "LUA NOVA"
  }
  if ((AG > 5.17) && (AG <= 14.32))       //35 a 97%  
  { 
    LP = tabela_textos[68];  // "LUA CRESCENTE"
  }
  if ((AG > 14.32) && (AG <= 15.21))      // 97 a 100 e de 100 a 97%     
  { 
    LP = tabela_textos[69]; // "LUA CHEIA"
  }    
  if ((AG > 15.21) && (AG <= 24.36))     //97 a 35%    
  { 
    LP = tabela_textos[132]; // "LUA MINGUANTE"
  }
  if ((AG >= 24.36) && (AG <= LC))       //35 a 0%
  { 
    LP = tabela_textos[67];  // "LUA NOVA"
  }

  return phase; 
}

/******* Normalization Function *******/
double MyNormalize(double v) 
{ 
  v = v - floor(v);
  if (v < 0)
    v = v + 1;
  return v;
}

byte validateDate(byte d, byte m, word y)
{
  byte mArr[12] = {31,0,31,30,31,30,31,31,30,31,30,31};
  byte od;

  if (m==2)
  {
    if ((y % 4)==0)
    {
      if (d==30)
        od=1;
      else if (d==0)
        od=29;
      else
        od=d;
    }
    else
    {
      if (d==29)
        od=1;
      else if (d==0)
        od=28;
      else
        od=d;
    }
  }
  else
  {
    if (d==0)
      od=mArr[m-1];
    else if (d==(mArr[m-1]+1))
      od=1;
    else
      od=d;
  }

  return od;
}
