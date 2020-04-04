//LIBRARIES
#include "TouchScreen.h"
#include "Adafruit_TFTLCD.h"
#include "avr/pgmspace.h"
#include "math.h"
#include "EEPROM.h"

//_________________________________________________________________TOUCHSCREEN
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin


#define TS_MINX 914// must be an analog pin, use "An" notation!
#define TS_MINY 118 // must be an analog pin, use "An" notation!
#define TS_MAXY 912// can be a digital pin
#define TS_MAXX 124
//-----------------------------------------------------------------

//_________________________________________________________________LCD
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
//-----------------------------------------------------------------

//_________________________________________________________________DEFINE LCD
#define LCD_RESET A4

#define BACKGROUND_EX    0x2000//loop's external background
#define BACKGROUND_IN    0x2000//loop's internal background 

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define WHITE 0xFFFF
#define BOMBCOLOR 0xFFDF
//-----------------------------------------------------------------

//_________________________________________________________________TOUCHSCREEN'S AND LCD'S INIZIALIZATION 
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
//-----------------------------------------------------------------

//_________________________________________________________________GLOBAL VARIABLES
const uint16_t   spriteCat[20][25]  =
{
  {0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    } ,
  {0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x94D6    , 0xFFFF    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    } ,
  {0xF800    , 0xF800    , 0x10A2    , 0x528E    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0xFEC8    , 0xFCC0    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    } ,
  {0xF800    , 0x10A2    , 0x6B50    , 0x8C75    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0x10A2    , 0x39CB    , 0xDB80    , 0xB200    , 0x6B50    , 0x10A2    , 0xF800    , 0xF800    } ,
  {0xF800    , 0x10A2    , 0x5AEF    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0x39CB    , 0x39CB    , 0x4A2C    , 0x6B50    , 0x6B50    , 0x73B2    , 0x10A2    , 0xF800    , 0xF800    } ,
  {0xF800    , 0x10A2    , 0x528E    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0x39CB    , 0x39CB    , 0x4A2C    , 0x4A2C    , 0x6B50    , 0xAD78    , 0x94D6    , 0x39CB    , 0x10A2    , 0xF800    } ,
  {0xF800    , 0x10A2    , 0x6B50    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x39CB    , 0x39CB    , 0x4A2C    , 0x5AEF    , 0x6B50    , 0xAD78    , 0xFFFF    , 0x08B1    , 0xD6BC    , 0x10A2    , 0xF800    } ,
  {0xF800    , 0xF800    , 0x10A2    , 0x6B50    , 0x10A2    , 0x10A2    , 0x10A2    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0x39CB    , 0x5AEF    , 0x39CB    , 0x73B2    , 0x39CB    , 0xAD78    , 0xFFFF    , 0x0007    , 0xEF5E    , 0xFDC4    , 0x10A2    } ,
  {0xF800    , 0xF800    , 0x10A2    , 0x10A2    , 0x39CB    , 0x4A2C    , 0x4A2C    , 0x4A2C    , 0x10A2    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0x39CB    , 0x39CB    , 0x94D6    , 0xD6BC    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xD6BC    , 0x10A2    } ,
  {0xF800    , 0xF800    , 0xF800    , 0x39CB    , 0x4A2C    , 0x5AEF    , 0x5AEF    , 0x5AEF    , 0x39CB    , 0x39CB    , 0x10A2    , 0x10A2    , 0x10A2    , 0x39CB    , 0x39CB    , 0x4A2C    , 0x73B2    , 0x73B2    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0x10A2    } ,
  {0xF800    , 0xF800    , 0x10A2    , 0x5AEF    , 0xFFFF    , 0xFFFF    , 0x8C75    , 0x5AEF    , 0x5AEF    , 0x4A2C    , 0x4A2C    , 0x39CB    , 0x39CB    , 0x39CB    , 0x5AEF    , 0x5AEF    , 0x94D6    , 0xAD78    , 0xD6BC    , 0xEF5E    , 0xEF5E    , 0xEF5E    , 0xEF5E    , 0x10A2    , 0xF800    } ,
  {0xF800    , 0xF800    , 0x10A2    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0x5AEF    , 0x5AEF    , 0x5AEF    , 0x5AEF    , 0x5AEF    , 0x5AEF    , 0x5AEF    , 0x5AEF    , 0xD6BC    , 0xD6BC    , 0x94D6    , 0xAD78    , 0xEF5E    , 0xD6BC    , 0x10A2    , 0x10A2    , 0xF800    , 0xF800    } ,
  {0xF800    , 0xF800    , 0x10A2    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0x5AEF    , 0x8C75    , 0xFFFF    , 0x8C75    , 0x5AEF    , 0x8C75    , 0xEF5E    , 0xEF5E    , 0xEF5E    , 0xD6BC    , 0xD6BC    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    } ,
  {0xF800    , 0xF800    , 0x10A2    , 0xEF5E    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0x8C75    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0x8C75    , 0xFFFF    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xEF5E    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    } ,
  {0xF800    , 0xF800    , 0x10A2    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xEF5E    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xEF5E    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    } ,
  {0xF800    , 0x10A2    , 0x10A2    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xEF5E    , 0xD6BC    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xFFFF    , 0xEF5E    , 0xD6BC    , 0xEF5E    , 0xFFFF    , 0xFFFF    , 0xD6BC    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    } ,
  {0xF800    , 0x10A2    , 0x39CB    , 0xAD78    , 0xEF5E    , 0xFFFF    , 0xEF5E    , 0xD6BC    , 0xAD78    , 0xD6BC    , 0xEF5E    , 0xEF5E    , 0xEF5E    , 0xD6BC    , 0x10A2    , 0xEF5E    , 0xFFFF    , 0xEF5E    , 0x39CB    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    } ,
  {0x10A2    , 0x73B2    , 0x528E    , 0x10A2    , 0x10A2    , 0xEF5E    , 0xFFFF    , 0x10A2    , 0xFFFF    , 0x10A2    , 0x10A2    , 0x10A2    , 0x10A2    , 0x10A2    , 0xAD78    , 0xFFFF    , 0x8C75    , 0x10A2    , 0x5AEF    , 0x10A2    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    } ,
  {0x10A2    , 0x7C13    , 0x528E    , 0xF800    , 0xF800    , 0x10A2    , 0xAD78    , 0xEF5E    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xAD78    , 0xEF5E    , 0xFFFF    , 0x10A2    , 0x39CB    , 0x73B2    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    } ,
  {0xF800    , 0x10A2    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0x10A2    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0x10A2    , 0x10A2    , 0x10A2    , 0xF800    , 0x10A2    , 0x10A2    , 0xF800    , 0xF800    , 0xF800    , 0xF800    , 0xF800    }
 };

typedef struct bomb//New type for the bombs
{
  unsigned int x;// bomb's coordinates
  unsigned int y;
  _Bool on;//bomb's status, on or off
} Bomb;

TSPoint oldposition;// Cat's coordinates    
TSPoint p; // Point touched by user   
TSPoint stampa;//point used for score's print

unsigned long timeScore;//time for score
unsigned long timeFrequency;//time for bomb's frequency
unsigned long timeStart;//master time for each match

unsigned long preTimeCat;// Cat's time
unsigned long curTimeCat;

unsigned long preTimeBomb;//Bomb's time
unsigned long curTimeBomb;

Bomb arrayBombeSx[12];// Array for each bomb
Bomb arrayBombeDx[12];
float frequency[9]={700,400,300,150,70,30,10,5,1};//millisec 

float arrayRecordStampa[5];//arrays for print each digit
float arrayRecord[5];// Record's array

int randNumber;// Rand number for generate the bomb    int randNumber;//rand numer for generate the bomb
float score;// Float number for the score of each match

int speedBomb;

_Bool esci;//boolean for the match's end
_Bool flagexit;
int i,j;//counter

char charpunteggio[5]={'0','0','0','0','0'};//char for each digit of the score
int prossimo;//variable for inserion sort
int minimo;//variable for the score
int array[5];//digit for each record

int dimx0, dimx1, dimx2;// Triangles' coordinates 'Loop Game'
int spostamento;//position of each digits for record print

//Variables for the title's screen

int  x1, y1, x2, y2,h,w;

//Variable for Cat's drawing
unsigned short int x;

//Variables for eeprom's reading and writing
unsigned char k,mom;
//-----------------------------------------------------------------

//_________________________________________________________________FUNCTION'S DECLARATIONS
void drawCat(TSPoint p);
void deleteCat(TSPoint p);
void drawBomb();
void deleteBomb();
void title();
void bombFrequency();
void from_eeprom (void *ptr,unsigned char dim,unsigned char start_position);
void to_eeprom (void *ptr,unsigned char dim,unsigned char start_position);

void startGame();
void loopGame();
void gameover();
//-----------------------------------------------------------------

//________________________________________________________________________________________________________________________________________________________
//_________________________________________________________________MAIN
void setup(){
}
void loop() {

  startGame();
  loopGame();
  gameover();
}
//-----------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------


void startGame()
{
//COMPONENT'S INIZIALIZATION
  //Touch screen and LCD
  tft.reset();
  tft.begin(0x9341);
  Serial.begin(9600);

  //Bombs
  arrayBombeSx[0].y = 20;
  arrayBombeSx[0].on = false;
  arrayBombeSx[0].x = 5;
  arrayBombeDx[0].y = 20;
  arrayBombeDx[0].on = false;
  arrayBombeDx[0].x = 5;
  for (i = 1; i < 12; i++)
  {
    arrayBombeSx[i].y = 20;
    arrayBombeSx[i].on = false;
    arrayBombeSx[i].x = arrayBombeSx[i - 1].x + 20;
    arrayBombeDx[i].y = 20;
    arrayBombeDx[i].on = false;
    arrayBombeDx[i].x = arrayBombeDx[i - 1].x + 20;
  }

  //Points
  oldposition.x = 170;//Inizialization of Cat's coordinates      
  oldposition.y = 130;  
  p.x = 0;            //Inizialization of Cat's coordinates
  p.y = 0;

  //Other
  esci = true;        //Exit condition
  score=0;            // Score

  //Opening and record
  title();            //Opening Screen
  from_eeprom(arrayRecord,20,0x00);//Record to eeprom

  //Time
  timeScore=millis();
  timeFrequency=millis();
  timeStart=millis();
  preTimeCat = 0;
  preTimeBomb = 0;

  //Playing field
  tft.fillScreen(BLACK);
  tft.setRotation(0);
  tft.fillScreen(BACKGROUND_EX);
  tft.fillRect(0, 40, 240, 240, BACKGROUND_IN);

  //Cannons
  dimx0=10;
  dimx1=5;
  dimx2=15;
  for(i=0;i<12;i++)
  {
    tft.fillTriangle(dimx0, 9, dimx1, 0, dimx2, 0,  0xE73C);
    tft.drawTriangle(dimx0, 9, dimx1, 0, dimx2, 0,  WHITE);
    dimx0+=20;
    dimx1+=20;
    dimx2+=20;
  }

  //First bombs' generation and Cat's drawing
  generateBomb();     
  p.x = 170;       //Inizialization of Cat's coordinates
  p.y = 130;
  drawCat(p);
}
void loopGame()
{
  //Fuctions for each frame
  do {
    //Point given by user
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);

    //Bomb's drawing
    drawBomb();

    if (p.z > ts.pressureThreshhold && (p.x - oldposition.x) < 60 && (p.y - oldposition.y) < 60)//Condition for the Cat's drawing
    {
      curTimeCat = millis();//Frequency of Cat's frame
      if ((unsigned long)(curTimeCat - preTimeCat) >= 125)
      {
        // Conditions for the Boarders
        if (p.x < 65)
        {
          p.x = 65;
        }
        else if (p.x >= 280)
        {
          p.x = 278;
        }
        if (p.y <= 20)
        {
          p.y = 20;
        }

        //Cat's drawing
        deleteCat(oldposition);
        oldposition.y = p.y;
        oldposition.x = p.x;
        oldposition.z = p.z;
        drawCat(p);

        //Delay
        preTimeCat = curTimeCat;
      }
      //Delete bombs and verify exit's conditions
      deleteBomb();
      delay(10);
    }
    else
    {
      //If the touched point isn't valid the Cat will be drawed one time only
      if (oldposition.z != -1)
      {
        drawCat(oldposition);
        oldposition.z = -1;//value to avoid Cat's drawing
      }
      //Delete bombs and verify exit's conditions
      deleteBomb();
      delay(65);
    }

    //Generate a new bomb's wave based on frequency
    bombFrequency();

  } while (esci == true);//until the Cat's death
}
void bombFrequency()
{
  //Time from the begining of the match
  timeFrequency=millis()-timeStart;

  //Speed based on time's match
  if(timeFrequency<15000)
  {
      speedBomb=frequency[0];
  }
  if(timeFrequency>=15000&&timeFrequency<30000)
  {
      speedBomb=frequency[1];
  }
  if(timeFrequency>=30000&&timeFrequency<50000)
  {
      speedBomb=frequency[2];
  }
  if(timeFrequency>=50000&&timeFrequency<70000)
  {
      speedBomb=frequency[3];
  }
  if(timeFrequency>=70000&&timeFrequency<90000)
  {
      speedBomb=frequency[4];
  }
  if(timeFrequency>=90000&&timeFrequency<120000)
  {
      speedBomb=frequency[5];
  }
  if(timeFrequency>=120000&&timeFrequency<150000)
  {
      speedBomb=frequency[6];
  }
  if(timeFrequency>=150000&&timeFrequency<170000)
  {
      speedBomb=frequency[7];
  }
  if(timeFrequency>=170000&&timeFrequency<190000)
  {
      speedBomb=frequency[8];
  }

  // bombs' delay
  curTimeBomb = millis();
  if ((unsigned long)(curTimeBomb - preTimeBomb) >= speedBomb)
  {
     generateBomb();
     preTimeBomb = curTimeBomb;
  }
}
void gameover()
{
  timeScore=millis()-timeScore;//score's time
  timeScore=timeScore/1000;//from millisec to sec

  //Score based on time
  if(timeScore<=10)
  {
    score=timeScore*1.5;
  }
  if(timeScore<=20&&timeScore>10)
  {
    score=timeScore*4.5;
  }
  if(timeScore<=50&&timeScore>20)
  {
    score=timeScore*9.5;
  }
  if(timeScore<=100&&timeScore>50)
  {
    score=timeScore*13.7;
  }
  if(timeScore>100)
  {
    score=timeScore*23.5;
  }

  //Screen Game Over
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  tft.setCursor(55, 90);
  tft.setTextColor(RED);
  tft.setTextSize(4);
  tft.print("Game Over");

  //Search the minimum score
  minimo=0;
  for(i=0;i<5;i++){
    if(arrayRecord[i]<=arrayRecord[minimo]){
        minimo=i;
    }
  }

  //If arrayRecord[minimo]<score then the record array will be update
  if(arrayRecord[minimo]<score){
    arrayRecord[minimo]=score;
  }

  //Insertion Sort on the arrayRecord
  for(i=1; i<5; i++){
    prossimo=arrayRecord[i];
    for(j=i-1; j>=0; j--){
      if(prossimo<arrayRecord[j]){
        arrayRecord[j+1]=arrayRecord[j];
      }
      else{
        break;
      }
    }
    arrayRecord[j+1]=prossimo;
  }

  //Copy the values of record in a temporary array from maximum to minimum
  for(i=0;i<5;i++){
    arrayRecordStampa[i]=arrayRecord[4-i];
  }

  //Score's print
  tft.setCursor(45, 140);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Il tuo punteggio e':");

  stampa.x=123;
  for(i=4;i>=0;i--)
  {
    array[i]=score/(pow(10,i));//extract the digit
    score=score-(array[i]*pow(10,i));//update the score
    charpunteggio[i]=array[i]+48;//convert the digit in a char
    tft.drawChar(stampa.x, 170, charpunteggio[i], WHITE, BLACK, 2);//print the digit
    stampa.x=stampa.x+14;//traslate the position of the next digit
  }
  delay(3000);

  //Record's print
  tft.fillScreen(BLACK);
  tft.drawRoundRect(63, 10, 190, 220, 3, WHITE);
  tft.drawRoundRect(62, 12, 192, 220, 3, WHITE);
  tft.setRotation(1);
  tft.setCursor(107, 18);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Record");

  spostamento=65;
  for(i=0;i<5;i++)
  {
    tft.setCursor(75, spostamento);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Pl.");
    tft.drawChar(113, spostamento, (i+49), WHITE, BLACK, 2);
    tft.setCursor(128, spostamento);
    tft.setTextSize(2);
    tft.print(": ");
    stampa.x=165;
    for(j=4;j>=0;j--)//this loop prints every score on the eeprom
    {
      array[j]=arrayRecordStampa[i]/(pow(10,j));
      arrayRecordStampa[i]=arrayRecordStampa[i]-(array[j]*pow(10,j));
      charpunteggio[j]=array[j]+48;
      tft.drawChar(stampa.x, spostamento, charpunteggio[j], WHITE, BLACK, 2);
      stampa.x=stampa.x+14;
    }
    spostamento+=30;
  }
  delay(500);

  //Press to continue and reset button
  tft.setCursor(100, 217);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("(Press to continue)");

  tft.drawRoundRect(285, 200, 20, 20, 3, WHITE);
  tft.setCursor(290, 203);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("R");

  tft.setCursor(281, 225);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Reset");

  do{
    flagexit=false;
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);

    if(p.z > ts.pressureThreshhold&&p.x>283&&p.x<313&&p.y<42&&p.y>12)
    {
      tft.setCursor(290, 203);
      tft.setTextColor(RED);
      tft.setTextSize(2);
      tft.print("R");
        for(i=0;i<5;i++)
        {
          arrayRecord[i]=0;
        }
        delay(1000);
    }
    else
    {
      if(p.z > ts.pressureThreshhold)
      {
        flagexit=true;
      }
    }
  }while(flagexit==false);

  //Score on the eeprom
  to_eeprom(arrayRecord,20,0x00);

}
void title()
{
  tft.setRotation(1);

  //Videogame's name
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  tft.setCursor(20, 95);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("DJANNI BOMBS");

  //Blue rays
  w = tft.width(),
  h = tft.height();
  x1 = y1 = 0;
  y2    = h - 1;
 
  for(x2=0; x2<w; x2+=6)
  {
      tft.drawLine(x1, y1, x2, y2, BLUE);
  }
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6)
  {
      tft.drawLine(x1, y1, x2, y2, BLUE);
  }
  

  //Videogame's name again
  tft.setRotation(1);
  tft.setCursor(20, 95);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("DJANNI BOMBS");
  delay(1000);

  //Press start to begin
  tft.setCursor(79,180 );
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Press 'Start Game' to begin");

  //Cat's sketch
  tft.setRotation(0);
  p.x =282;
  p.y=165;
  drawCat(p);
  tft.setRotation(1);

  //Start Game button
  tft.drawRoundRect(63, 195, 190, 30, 3, WHITE);
  tft.drawRoundRect(62, 197, 192, 30, 3, WHITE);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(70, 200);
  tft.print("Start Game");

  do
  {
    flagexit=true;
    p = ts.getPoint();
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
    if(p.z > ts.pressureThreshhold)
    {
      if(p.y>15&&p.y<45&&p.x>63&&p.x<253)
      {
        flagexit=false;
      }
    }
  }while(flagexit==true);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

}
void generateBomb()
{
  //This function generate the active bombs trought a random number
  for (i = 0; i < 12; i++)
  {
    if (arrayBombeSx[i].on == false)
    {
      randNumber=random(36);
      if(randNumber%5==0)
      {
        arrayBombeSx[i].on = true;
      }
    }
      if (arrayBombeDx[i].on == false)
      {
        randNumber=random(36);
        if(randNumber%5==0)
        {
          arrayBombeDx[i].on = true;
        }
      }
  }

}
void deleteBomb()
{
  // The bomb will be delected after every frame 
  for (i = 0; i < 12; i++)
  {
    if (arrayBombeSx[i].on == true)
    {
      //Game over condition
      if (abs((oldposition.x - 10) - (arrayBombeSx[i].y - 5)) <= 25 && abs((oldposition.y - 12) - (arrayBombeSx[i].x - 5)) <= 20)
      {
        esci = false;
      }
      //External and internal background's restore
      if (arrayBombeSx[i].y <= 40 || arrayBombeSx[i].y >= 290)
      {
        tft.fillRect(arrayBombeSx[i].x, arrayBombeSx[i].y - 10, 10, 10, BACKGROUND_EX);
      }
      else
      {
        tft.fillRect(arrayBombeSx[i].x, arrayBombeSx[i].y - 10, 10, 10, BACKGROUND_IN);
      }

      //Change bomb coordinates and status
      arrayBombeSx[i].y += 10;
      if (arrayBombeSx[i].y == 330)//Bomb out of the screen
      {
        arrayBombeSx[i].on = false;
        arrayBombeSx[i].y = 20;
      }
    }
      if (arrayBombeDx[i].on == true)
      {
        //Game over condition
        if (abs((oldposition.x - 10) - (arrayBombeDx[i].y - 5)) <= 25 && abs((oldposition.y - 12) - (arrayBombeDx[i].x - 5)) <= 20)
        {
          esci = false;
        }
        //External and internal background's restore
        if (arrayBombeDx[i].y <= 40 || arrayBombeDx[i].y >= 290)
        {
          tft.fillRect(arrayBombeDx[i].x, arrayBombeDx[i].y - 10, 10, 10, BACKGROUND_EX);
        }
        else
        {
          tft.fillRect(arrayBombeDx[i].x, arrayBombeDx[i].y - 10, 10, 10, BACKGROUND_IN);
        }
  
        //Change bomb coordinates and status
        arrayBombeDx[i].y += 10;
        if (arrayBombeDx[i].y == 330)//Bomb out of the screen
        {
          arrayBombeDx[i].on = false;
          arrayBombeDx[i].y = 20;
        }
      }
  }
}
void drawBomb()
{
  //Bomb's drawing
  for (i = 0; i < 12; i++)
  {
    if (arrayBombeSx[i].on == true)
    {
      tft.fillRect(arrayBombeSx[i].x, arrayBombeSx[i].y, 10, 10, BOMBCOLOR);
    }
    if (arrayBombeDx[i].on == true)
    {
      tft.fillRect(arrayBombeDx[i].x, arrayBombeDx[i].y, 10, 10, BOMBCOLOR);
    }
  }
}
void drawCat(TSPoint p)
{
  //Cat's drawing based on the matrix of pixel spriteCat
  x = p.x;
  for (i = 0; i < 20; i++)
  {
    for (j = 0; j < 25; j++)
    {
      if (spriteCat[i][j] != RED)
      {
        tft.drawPixel(p.y, p.x, spriteCat[i][j]);
      }
      p.x--;
    }
    p.y--;
    p.x = x;
  }
}
void deleteCat(TSPoint p)
{
  x = p.x;
  for (i = 0; i < 20; i++)
  {
    for (j = 0; j < 25; j++)
    {
      if (spriteCat[i][j] != RED)
      {
        tft.drawPixel(p.y, p.x, BACKGROUND_IN);
      }
      p.x--;
    }
    p.y--;
    p.x = x;
  }
}
void to_eeprom (void *ptr,unsigned char dim,unsigned char start_position)
{

 for (k=0;k<dim;k++)
 {
    mom = ((unsigned char*) ptr)[k];
    EEPROM.write(start_position+k,mom);
 }

 return;
}
void from_eeprom (void *ptr,unsigned char dim,unsigned char start_position)
{

  for (k=0;k<dim;k++)
  {
    mom = EEPROM.read(start_position+k);
    ((unsigned char*) ptr)[k]=mom;
  }

 return;
}

