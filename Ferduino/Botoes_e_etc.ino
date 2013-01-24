//**********************************************************************************************
//*********************** Botões dos menus *****************************************************
//**********************************************************************************************
const int temM[]= {90,35,115,60};           //temp. minus
const int temP[]= {205,35,230,60};          //temp. plus
const int offM[]= {90,85,115,110};          //offset minus
const int offP[]= {205,85,230,110};         //offset plus
const int almM[]= {90,135,115,160};         //alarm minus
const int almP[]= {205,135,230,160};        //alarm plus
const int iniC[]= {325,2,393,42};           // inicio
const int menU[]= {325, 52, 393, 92};       // Botao menu
const int prOK[]= {325,200,393,238};        //ok
const int salV[]= {325,150,393,190};        //salvar dosagem
// const int xxx[]= {325,151,393,190};
//const int xxxx[]= {325,200,393,239};
const int savE[]= {180,188,300,220};        //Save Eeprom
//------------------menu----------------------------
const int tanD[]= {10, 20, 150, 60};        //hora e data
const int tesT[]= {10, 70, 150, 110};       //testar LED
const int temC[]= {10, 120, 150, 160};      // controle de temperatura
const int graF[]= {10, 170, 150, 210};      // Graficos
const int ledW[]= {170, 20, 310, 60};        //alterar valores led
const int tpaA[]= {170, 70, 310, 110};         //TPA automÃ¡tica
const int dosA[]= {170, 120, 310, 160};        //Bomba dosadora
const int wavM[]= {170, 170, 310, 210};        // Wavemaker
const int volT[]= {325,200,393,238};         //voltar
//-----------botoes graficos e parametros--------------------
const int tempG[]= {10, 20, 150, 60};        //parametro/grafico de temperatura
const int phA[]= {10, 70, 150, 110};       //parametro/grafico de ph do aqua
const int phR[]= {10, 120, 150, 160};      //parametro/grafico de ph do aqua
const int orP[]= {10, 170, 150, 210};      // parametro/grafico de orp
const int denS[]= {170, 20, 310, 60};        //parametro/grafico de densidade
//const int []= {170, 70, 310, 110};         
//const int []= {170, 120, 310, 160};        

const int manU[]= {10, 20, 150, 60};        // Dosagem manual
const int autO[]= {10, 70, 150, 110};       //Dosagem automatica
const int perS[]= {10, 120, 150, 160};      //Dosagem personalizada
const int reV[]= {10, 170, 150, 210};     // rever cofig. dosagem personalizada
const int atiV[]= {170, 20, 310, 60};    //Ativar/desativar dosadoras   
//const int []= {170, 70, 310, 110};         
//const int []= {170, 120, 310, 160};          

const int dosa1[]= {10, 20, 150, 60};       //Bomba dosadora 1
const int dosa2[]= {10, 70, 150, 110};         //Bomba dosadora 2
const int dosa3[]= {10, 120, 150, 160};      // Bomba dosadora 3
const int dosa4[]= {170, 20, 310, 60};       //Bomba dosadora 4
const int dosa5[]= {170, 70, 310, 110};         //Bomba dosadora 5
const int dosa6[]= {170, 120, 310, 160};      // Bomba dosadora 6
//----------------------------------------------------
const int leWB[]= {5, 188, 90, 220};        //LED values show whites or blues
const int leST[]= {100, 188, 170, 220};       //LED values change
const int leSh[]= {325,200,393,238};       //white LED show table
const int houU[]= {70, 18, 95, 43};          //hour up
const int minU[]= {160, 18, 185, 43};        //min up
const int minUT[]= {120, 18, 145, 43};        //minutotpa mais
const int minDT[]= {120, 69, 145, 92};       //minutotpa menos
const int houD[]= {70, 69, 95, 92};         //hour down
const int minD[]= {160, 69, 185, 92};       //min down
const int dayU[]= {70, 102, 95, 127};       //day up
const int monU[]= {160, 102, 185, 127};     //month up
const int yeaU[]= {250, 102, 275, 127};     //year up
const int dayD[]= {70, 152, 95, 177};       //day down
const int monD[]= {160, 152, 185, 177};     //month down
const int yeaD[]= {250, 152, 275, 177};     //year down
const int stsT[]= {90, 105, 220, 175};     //start/stop
const int tenM[]= {10, 120, 80, 160};       //-10s
const int tenP[]= {230, 120, 300, 160};     //+10s
const int segC[]= {250, 18, 275, 43};        //segundo para cima
const int segB[]= {250, 69, 275, 92};        // segundo para baixo
const int durC[]= {275, 18, 300, 43};        //duracao tpa para cima
const int durB[]= {275, 69, 300, 92};        // duracao tpa para baixo
const int segU[]= {30, 99, 110, 139};       //segunda
const int terC[]= {120, 99, 200, 139};       //terca
const int quaR[]= {210, 99, 290, 139};       //quarta
const int quiN[]= {30, 146, 110, 186};        // quinta
const int sexT[]= {120, 146, 200, 186};      //sexta
const int sabA[]= {210, 146, 290, 186};      //sabado
const int domI[]= {120, 193, 200, 233};      //domingo
const int caliB[]= {170, 170, 310, 210};     // calibrar
const int iniciaR[]= {120, 193, 200, 233};   //Iniciar calibracao
const int anT[]= {30, 193, 110, 233};        // anterior
const int proX[]= {210, 193, 290, 233};      //proximo
//----------------botoes solicitacao de senha-------------------------------------------------
const int boT1[]= {10, 20, 62, 60};        //Botao um
const int boT2[]= {72, 20, 124, 60};        //Botao dois
const int boT3[]= {134, 20, 186, 60};        //Botao tres
const int boT4[]= {196, 20, 248, 60};        //Botao quatro
const int boT5[]= {258, 20, 310, 60};        //Botao cinco
const int boT6[]= {10, 70, 62,110};        //Botao seis
const int boT7[]= {72, 70, 124, 110};        //Botao sete
const int boT8[]= {134, 70, 186, 110};       //Botao oito
const int boT9[]= {196, 70, 248, 110};        //Botao nove
const int boT0[]= {258, 70, 310, 110};        //Botao zero
const int boTL[]= {10, 120, 155, 160};        //Botao limpar
const int boTE[]= {165, 120, 310, 160};        //Botao entrar

//**********************************************************************************************
//***************************** funcoes ********************************************************
//**********************************************************************************************
void clearScreen()
{
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(0, 0, 400, 240); 
}

void printButton(char* text, int x1, int y1, int x2, int y2, boolean setFont = false)
{
  int stl = strlen(text);
  int fx, fy;

  myGLCD.setColor(0, 0, 200);
  myGLCD.fillRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);

  myGLCD.setBackColor(0, 0, 200);
  if (setFont) {
    myGLCD.setFont(BigFont); 
    fx = x1+(((x2 - x1+1)-(stl*16))/2);
    fy = y1+(((y2 - y1+1)-16)/2);
    myGLCD.print(text, fx, fy);
  }
  else {
    myGLCD.setFont(SmallFont); 
    fx = x1+(((x2 - x1)-(stl*8))/2);
    fy = y1+(((y2 - y1-1)-8)/2);
    myGLCD.print(text, fx, fy);
  }
}
void printButton_verde(char* text, int x1, int y1, int x2, int y2, boolean setFont = false)
{
  int stl = strlen(text);
  int fx, fy;

  myGLCD.setColor(0, 150, 86);
  myGLCD.fillRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);

  myGLCD.setBackColor(0, 150, 86);
  if (setFont) {
    myGLCD.setFont(BigFont); 
    fx = x1+(((x2 - x1+1)-(stl*16))/2);
    fy = y1+(((y2 - y1+1)-16)/2);
    myGLCD.print(text, fx, fy);
  }
  else {
    myGLCD.setFont(SmallFont); 
    fx = x1+(((x2 - x1)-(stl*8))/2);
    fy = y1+(((y2 - y1-1)-8)/2);
    myGLCD.print(text, fx, fy);
  }
}
void printButton_vermelho(char* text, int x1, int y1, int x2, int y2, boolean setFont = false)
{
  int stl = strlen(text);
  int fx, fy;

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);

  myGLCD.setBackColor(255, 0, 0);
  if (setFont) {
    myGLCD.setFont(BigFont); 
    fx = x1+(((x2 - x1+1)-(stl*16))/2);
    fy = y1+(((y2 - y1+1)-16)/2);
    myGLCD.print(text, fx, fy);
  }
  else {
    myGLCD.setFont(SmallFont); 
    fx = x1+(((x2 - x1)-(stl*8))/2);
    fy = y1+(((y2 - y1-1)-8)/2);
    myGLCD.print(text, fx, fy);
  }
}
void printHeader(char* headline)
{
  setFont(SMALL, 255, 255, 0, 255, 255, 0);
  myGLCD.fillRect (1, 1, 319, 14);
  myGLCD.setColor(0, 0, 0);
  myGLCD.print(headline, LEFT+5, 2);   
}

void setFont(boolean font, byte cr, byte cg, byte cb, byte br, byte bg, byte bb)
{
  myGLCD.setBackColor(br, bg, bb);    //font background black
  myGLCD.setColor(cr, cg, cb);      //font colour white
  if (font==LARGE)
    myGLCD.setFont(BigFont);     //font size LARGE
  else if (font==SMALL)
    myGLCD.setFont(SmallFont);
}

// Draw a red frame while a button is touched
void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable()) {
    myTouch.read(); 
  }
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

int NumMins(uint8_t ScheduleHour, uint8_t ScheduleMinute)
{
  return (ScheduleHour*60) + ScheduleMinute;
}
