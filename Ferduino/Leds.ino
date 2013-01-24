int LedToPercent (int Led_out)        //returns LED output in %
{
  int result;

  if (Led_out==0) {
    result = 0; 
  }
  else {
    result = map(Led_out, 1, 255, 1, 100);  
  }

  return result; 
}
//---------------------------LED levels---------------------------
void LED_levels_output()
{
  int sector, sstep, t1, t2 ;
  int b_out, w_out, moon_out;

  if (min_cnt>=1440) {
    min_cnt=1;
  }   // 24 hours of minutes 
  sector = min_cnt/15;              // divided by gives sector -- 15 minute
  sstep = min_cnt%15;               // remainder gives add on to sector value 

  t1 =sector;
  if (t1==95) {
    t2=0;
  }
  else {
    t2 = t1+1;
  }

  if (sstep==0) {
    bled_out = bled[t1];
    wled_out = wled[t1];
  } 
  else {
    bled_out = check(&bled[t1], &bled[t2], sstep);
    wled_out = check(&wled[t1], &wled[t2], sstep);
  }
     float lunarCycle = moonPhase(t.year, t.mon, t.date); //get a value for the lunar cycle
     moonled_out = (MinI *(1 - lunarCycle)) + (MaxI * lunarCycle) + 0.5;  

  if (MeanWell == true) {
    b_out = bled_out;
    w_out = wled_out;
    moon_out = moonled_out;
  } 
  else {
    b_out = 255 - bled_out;
    w_out = 255 - wled_out;
    moon_out = 255 - moonled_out;
  }

  analogWrite(ledPinBlue, b_out);
  analogWrite(ledPinWhite, w_out);
  analogWrite(ledPinMoon, moon_out);
}

int check( byte *pt1, byte *pt2, int lstep)
{
  int result;
  float fresult;

  if (*pt1==*pt2) {
    result = *pt1;
  }   // No change
  else if (*pt1<*pt2)                //Increasing brightness
  { 
    fresult = ((float(*pt2-*pt1)/15.0) * float(lstep))+float(*pt1);
    result = int(fresult);
  }
  //Decreasing brightness
  else {
    fresult = -((float(*pt1-*pt2)/15.0) * float(lstep))+float(*pt1);
    result = int(fresult);                     
  } 
  return result;
}
